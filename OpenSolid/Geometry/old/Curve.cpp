/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "Curve.hpp"

namespace opensolid
{
    template<int SpatialDimension>
    class Tangent : public Function<1, SpatialDimension>
    {
        private:
            const shared_ptr<Function<1, SpatialDimension> > _function;
        public:
            Tangent(
                const shared_ptr<Function<1, SpatialDimension> >& function
            );

            void getValue(
                const double& parameter_value,
                typename Value<SpatialDimension>::type& result
            ) const;

            void getBounds(
                const Interval& parameter_bounds,
                typename Bounds<SpatialDimension>::type& result
            ) const;
    };

    template<int SpatialDimension>
    Tangent<SpatialDimension>::Tangent(const shared_ptr<Curve<SpatialDimension> > curve)
    : _derivative(curve->derivative())
    {
    }

    template<int SpatialDimension>
    void Tangent<SpatialDimension>::getValue(const double& parameter_value, typename Value<SpatialDimension>& result) const
    {
        _derivative->getValue(parameter_value, result);
        result.normalize();
    }

    template<int SpatialDimension>
    void Tangent<SpatialDimension>::getBounds(const Interval& parameter_bounds, typename Bounds<SpatialDimension>& result) const
    {
        _derivative->getBounds(parameter_bounds, result);
        result.normalize();
    }

    template<int SpatialDimension>
    shared_ptr<Curve<SpatialDimension> > Curve<SpatialDimension>::tangent() const
    {
        return shared_ptr<Curve<SpatialDimension> >(new Tangent(shared_from_this()));
    }

    template<int SpatialDimension>
    bool Curve<SpatialDimension>::isLinear(
        typename Value<SpatialDimension>::type& point,
        typename Value<SpatialDimension>::type& direction
    ) const
    {
        point = Value<SpatialDimension>::zero();
        direction = Value<SpatialDimension>::zero();
        return false;
    }

    template<int SpatialDimension>
    bool Curve<SpatialDimension>::isCircular(
        typename Value<SpatialDimension>::type& point,
        typename Value<SpatialDimension>::type& first_unit_vector,
        typename Value<SpatialDimension>::type& second_unit_vector,
        double& radius
    ) const
    {
        point = Value<SpatialDimension>::zero();
        first_unit_vector = Value<SpatialDimension>::zero();
        second_unit_vector = Value<SpatialDimension>::zero();
        radius = 0.0;
        return false;
    }

    inline double quadraticRootIntegral(double a, double b, double c)
    {
        double abc12 = 2 * sqrt(a + b + c);
        double a12 = sqrt(a);
        double a32 = 2 * a * a12;
        double c12 = 2 * sqrt(c);
        double ba12 = b / a12;
        return (a32 * abc12 + a12 * b * (abc12 - c12) + (4 * c * a - b * b) * log((2 * a12 + ba12 + abc12)/(ba12 + c12)))/(4 * a32);
    }

    template<int SpatialDimension>
    double Curve<SpatialDimension>::length() const
    {
        double result = 0.0;
        vector<Interval> segment_intervals;
        segment_intervals.push_back(Interval(0.0, 1.0));
        Interval segment_interval;
        shared_ptr<Curve<SpatialDimension> > first_derivative = derivative();
        shared_ptr<Curve<SpatialDimension> > second_derivative = first_derivative->derivative();
        while (!segment_intervals.empty())
        {
            segment_interval = segment_intervals.back();
            segment_intervals.pop_back();
            double width = segment_interval.width();

            typename Value<SpatialDimension>::type start_derivative, end_derivative;
            first_derivative->getValue(segment_interval.lower(), start_derivative);
            first_derivative->getValue(segment_interval.upper(), end_derivative);

            typename Bounds<SpatialDimension>::type second_derivative_bounds;
            second_derivative->getBounds(segment_interval, second_derivative_bounds);
            second_derivative_bounds -= (end_derivative - start_derivative) / width;
            double max_norm = sqrt(second_derivative_bounds.squaredNorm().upper());
            double error = max_norm * width * width / 4;

            if (error < Tolerance::convergence() * width / 2)
            {
                typename Value<SpatialDimension>::type difference = end_derivative - start_derivative;
                double a = difference.squaredNorm();
                double b = 2 * start_derivative.dot(difference);
                double c = start_derivative.squaredNorm();
                result += width * quadraticRootIntegral(a, b, c);
            }
            else
            {
                double median = segment_interval.median();
                segment_intervals.push_back(Interval(segment_interval.lower(), median));
                segment_intervals.push_back(Interval(median, segment_interval.upper()));
            }
        }
        return result;
    }
}