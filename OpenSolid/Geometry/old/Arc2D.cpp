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

#include <config.hpp>

#include "Arc2D.hpp"

namespace opensolid
{
    Arc2D::Arc2D(const Vector2D& center, double radius, double start_angle, double end_angle)
    :
    _center(center),
    _radius(radius),
    _start_angle(start_angle),
    _end_angle(end_angle),
    _swept_angle(end_angle - start_angle)
    {
    }

    shared_ptr<Arc2D> Arc2D::fromCenterAndEndpoints(const Vector2D& center, const Vector2D& first_endpoint, const Vector2D& second_endpoint, bool natural)
    {
        Vector2D first_radial_vector = first_endpoint - center;
        Vector2D second_radial_vector = second_endpoint - center;
        double first_radius = first_radial_vector.norm();
        double second_radius = second_radial_vector.norm();
        if (abs(first_radius - second_radius) > Tolerance::roundoff())
        {
            throw UnequalRadii();
        }
        double radius = (first_radius + second_radius) / 2;
        double start_angle = atan2(first_radial_vector.y(), first_radial_vector.x());
        double end_angle = atan2(second_radial_vector.y(), second_radial_vector.x());
        bool counterclockwise = ((first_radial_vector.x() * second_radial_vector.y() - first_radial_vector.y() - second_radial_vector.x()) > -Tolerance::roundoff()) == natural;
        if (counterclockwise && end_angle < start_angle)
        {
            end_angle += 2 * M_PI;
        }
        else if (!counterclockwise && end_angle > start_angle)
        {
            end_angle -= 2 * M_PI;
        }
        return shared_ptr<Arc2D>(new Arc2D(center, radius, start_angle, end_angle));
    }

    shared_ptr<Arc2D> Arc2D::circle(const Vector2D& center, double radius)
    {
        return shared_ptr<Arc2D>(new Arc2D(center, radius, 0, 2 * M_PI));
    }

    shared_ptr<Arc2D> Arc2D::fromThreePoints(const Vector2D& start_point, const Vector2D& inner_point, const Vector2D& end_point)
    {
        double a = (inner_point - start_point).norm();
        double b = (end_point - inner_point).norm();
        double c = (start_point - end_point).norm();
        double s = (a + b + c) / 2;
        if ((s - a < Tolerance::roundoff()) || (s - b < Tolerance::roundoff()) || (s - c < Tolerance::roundoff()))
        {
            throw CollinearPoints();
        }
        double radius = a * b * c / sqrt((a + b + c) * (b + c - a) * (c + a - b) * (a + b - c));
        double a2 = a * a;
        double b2 = b * b;
        double c2 = c * c;
        double t1 = a2 * (b2 + c2 - a2);
        double t2 = b2 * (c2 + a2 - b2);
        double t3 = c2 * (a2 + b2 - c2);
        double sum = t1 + t2 + t3;
        t1 /= sum;
        t2 /= sum;
        t3 /= sum;
        Vector2D center = t1 * end_point + t2 * start_point + t3 * inner_point;
        Vector2D first_leg = inner_point - start_point;
        Vector2D second_leg = end_point - inner_point;
        bool counterclockwise = (first_leg.x() * second_leg.y() - first_leg.y() - second_leg.x()) > -Tolerance::roundoff();
        Vector2D start_radial_vector = start_point - center;
        Vector2D end_radial_vector = end_point - center;
        double start_angle = atan2(start_radial_vector.y(), start_radial_vector.x());
        double end_angle = atan2(end_radial_vector.y(), end_radial_vector.x());
        if (counterclockwise && end_angle < start_angle)
        {
            end_angle += 2 * M_PI;
        }
        else if (!counterclockwise && end_angle > start_angle)
        {
            end_angle -= 2 * M_PI;
        }
        return shared_ptr<Arc2D>(new Arc2D(center, radius, start_angle, end_angle));
    }

    void Arc2D::getCenter(Vector2D& result) const
    {
        result = _center;
    }

    Vector2D Arc2D::center() const
    {
        return _center;
    }

    double Arc2D::radius() const
    {
        return _radius;
    }

    double Arc2D::startAngle() const
    {
        return _start_angle;
    }

    double Arc2D::endAngle() const
    {
        return _end_angle;
    }

    bool Arc2D::isCircular(Vector2D& center, double& radius) const
    {
        center = _center;
        radius = _radius;
        return true;
    }

    void Arc2D::getValue(double parameter_value, Vector2D& result) const
    {
        double angle = _start_angle + parameter_value * _swept_angle;
        result = _center + _radius * Vector2D(cos(angle), sin(angle));
    }

    void Arc2D::getDerivative(int n, double parameter_value, Vector2D& result) const
    {
        double angle = _start_angle + parameter_value * _swept_angle;
        double coefficient = _radius;
        for (int i = 0; i < n; ++i)
        {
            coefficient *= _swept_angle;
        }
        switch (n % 4)
        {
            case 0:
                result = coefficient * Vector2D(cos(angle), sin(angle));
                break;
            case 1:
                result = coefficient * Vector2D(-sin(angle), cos(angle));
                break;
            case 2:
                result = coefficient * Vector2D(-cos(angle), -sin(angle));
                break;
            case 3:
                result = coefficient * Vector2D(sin(angle), -cos(angle));
                break;
        }
    }

    void Arc2D::getBounds(const Interval& parameter_bounds, Box2D& result) const
    {
        Interval angle = _start_angle + parameter_bounds * _swept_angle;
        result.x() = cos(angle);
        result.y() = sin(angle);
        result *= _radius;
        result += _center;
    }

    void Arc2D::getDerivativeBounds(int n, const Interval& parameter_bounds, Box2D& result) const
    {
        Interval angle = _start_angle + parameter_bounds * _swept_angle;
        switch (n % 4)
        {
            case 0:
                result.x() = cos(angle);
                result.y() = sin(angle);
                break;
            case 1:
                result.x() = -sin(angle);
                result.y() = cos(angle);
                break;
            case 2:
                result.x() = -cos(angle);
                result.y() = -sin(angle);
                break;
            case 3:
                result.x() = sin(angle);
                result.y() = -cos(angle);
                break;
        }
        double coefficient = _radius;
        for (int i = 0; i < n; ++i)
        {
            coefficient *= _swept_angle;
        }
        result *= coefficient;
    }

    void Arc2D::getTangent(double parameter_value, Vector2D& result) const
    {
        double angle = _start_angle + parameter_value * _swept_angle;
        result.x() = -sin(angle);
        result.y() = cos(angle);
    }

    void Arc2D::getTangentBounds(const Interval& parameter_bounds, Box2D& result) const
    {
        Interval angle = _start_angle + parameter_bounds * _swept_angle;
        result.x() = -sin(angle);
        result.y() = cos(angle);
    }
}
