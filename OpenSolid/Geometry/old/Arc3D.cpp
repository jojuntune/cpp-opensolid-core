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

#include "Arc3D.hpp"

namespace opensolid
{
    Arc3D::Arc3D(const Vector3D& center, const Vector3D& first_unit_vector, const Vector3D& second_unit_vector, double radius, double angle)
    :
    _center(center),
    _first_unit_vector(first_unit_vector),
    _second_unit_vector(second_unit_vector),
    _radius(radius),
    _angle(angle),
    _binormal(first_unit_vector.cross(second_unit_vector))
    {
    }

    shared_ptr<Arc3D> Arc3D::fromCenterAndEndpoints(const Vector3D& center, const Vector3D& first_endpoint, const Vector3D& second_endpoint, bool natural)
    {
        Vector3D first_radial_vector = first_endpoint - center;
        Vector3D second_radial_vector = second_endpoint - center;
        double first_radius = first_radial_vector.norm();
        double second_radius = second_radial_vector.norm();
        if (abs(first_radius - second_radius) > Tolerance::roundoff())
        {
            throw UnequalRadii();
        }
        double radius = (first_radius + second_radius) / 2;
        Vector3D first_unit_vector = first_radial_vector / radius;
        Vector3D binormal;
        if (natural)
        {
            binormal = first_radial_vector.cross(second_radial_vector).normalized();
        }
        else
        {
            binormal = second_radial_vector.cross(first_radial_vector).normalized();
        }
        Vector3D second_unit_vector = binormal.cross(first_unit_vector);
        double angle = atan2(second_radial_vector.dot(second_unit_vector), second_radial_vector.dot(first_unit_vector));
        if (angle < 0)
        {
            angle = angle + 2 * M_PI;
        }
        return shared_ptr<Arc3D>(new Arc3D(center, first_unit_vector, second_unit_vector, radius, angle));
    }

    shared_ptr<Arc3D> Arc3D::circle(const Vector3D& center, const Vector3D& binormal, double radius)
    {
        int index;
        binormal.minCoeff(&index);
        Vector3D second_unit_vector = binormal.cross(Vector3D::Unit(index)).normalized();
        Vector3D first_unit_vector = second_unit_vector.cross(binormal).normalized();
        return shared_ptr<Arc3D>(new Arc3D(center, first_unit_vector, second_unit_vector, radius, 2 * M_PI));
    }

    shared_ptr<Arc3D> Arc3D::fromThreePoints(const Vector3D& start_point, const Vector3D& inner_point, const Vector3D& end_point)
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
        Vector3D center = t1 * end_point + t2 * start_point + t3 * inner_point;

        Vector3D binormal = (inner_point - start_point).cross(end_point - inner_point).normalized();
        Vector3D start_radial_vector = start_point - center;
        Vector3D end_radial_vector = end_point - center;
        Vector3D first_unit_vector = start_radial_vector / radius;
        Vector3D second_unit_vector = binormal.cross(first_unit_vector);

        double angle = atan2(end_radial_vector.dot(second_unit_vector), end_radial_vector.dot(first_unit_vector));
        if (angle < 0)
        {
            angle = angle + 2 * M_PI;
        }
        return shared_ptr<Arc3D>(new Arc3D(center, first_unit_vector, second_unit_vector, radius, angle));
    }

    void Arc3D::getCenter(Vector3D& result) const
    {
        result = _center;
    }

    Vector3D Arc3D::center() const
    {
        return _center;
    }

    void Arc3D::getFirstUnitVector(Vector3D& result) const
    {
        result = _first_unit_vector;
    }

    Vector3D Arc3D::firstUnitVector() const
    {
        return _first_unit_vector;
    }

    void Arc3D::getSecondUnitVector(Vector3D& result) const
    {
        result = _second_unit_vector;
    }

    Vector3D Arc3D::secondUnitVector() const
    {
        return _second_unit_vector;
    }

    double Arc3D::radius() const
    {
        return _radius;
    }

    double Arc3D::angle() const
    {
        return _angle;
    }

    void Arc3D::getBinormal(Vector3D& result) const
    {
        result = _binormal;
    }

    Vector3D Arc3D::binormal() const
    {
        return _binormal;
    }

    bool Arc3D::isCircular(Vector3D& center, Vector3D& binormal, double& radius) const
    {
        center = _center;
        binormal = _binormal;
        radius = _radius;
        return true;
    }

    void Arc3D::getValue(double parameter_value, Vector3D& result) const
    {
        double angle = _angle * parameter_value;
        result = _center + _radius * (cos(angle) * _first_unit_vector + sin(angle) * _second_unit_vector);
    }

    void Arc3D::getDerivative(int n, double parameter_value, Vector3D& result) const
    {
        double angle = _angle * parameter_value;
        double coefficient = _radius;
        for (int i = 0; i < n; ++i)
        {
            coefficient *= _angle;
        }
        switch (n % 4)
        {
            case 0:
                result = cos(angle) * coefficient * _first_unit_vector + sin(angle) * coefficient * _second_unit_vector;
                break;
            case 1:
                result = -sin(angle) * coefficient * _first_unit_vector + cos(angle) * coefficient * _second_unit_vector;
                break;
            case 2:
                result = -cos(angle) * coefficient * _first_unit_vector - sin(angle) * coefficient * _second_unit_vector;
                break;
            case 3:
                result = sin(angle) * coefficient * _first_unit_vector - cos(angle) * coefficient * _second_unit_vector;
                break;
        }
    }

    void Arc3D::getBounds(const Interval& parameter_bounds, Box3D& result) const
    {
        Interval angle = _angle * parameter_bounds;
        result = _center + cos(angle) * (_radius * _first_unit_vector) + sin(angle) * (_radius * _second_unit_vector);
    }

    void Arc3D::getDerivativeBounds(int n, const Interval& parameter_bounds, Box3D& result) const
    {
        Interval angle = _angle * parameter_bounds;
        double coefficient = _radius;
        for (int i = 0; i < n; ++i)
        {
            coefficient *= _angle;
        }
        switch (n % 4)
        {
            case 0:
                result = cos(angle) * (coefficient * _first_unit_vector) + sin(angle) * (coefficient * _second_unit_vector);
                break;
            case 1:
                result = -sin(angle) * (coefficient * _first_unit_vector) + cos(angle) * (coefficient * _second_unit_vector);
                break;
            case 2:
                result = -cos(angle) * (coefficient * _first_unit_vector) - sin(angle) * (coefficient * _second_unit_vector);
                break;
            case 3:
                result = sin(angle) * (coefficient * _first_unit_vector) - cos(angle) * (coefficient * _second_unit_vector);
                break;
        }
    }

    void Arc3D::getTangent(double parameter_value, Vector3D& result) const
    {
        double angle = _angle * parameter_value;
        result = -sin(angle) * _first_unit_vector + cos(angle) * _second_unit_vector;
    }

    void Arc3D::getTangentBounds(const Interval& parameter_bounds, Box3D& result) const
    {
        Interval angle = _angle * parameter_bounds;
        result = -sin(angle) * _first_unit_vector + cos(angle) * _second_unit_vector;
    }
}
