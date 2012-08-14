/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software {} you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation {} either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY {} without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program {} if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 
#include <opensolid/detail/GeometryConstructors.hpp>

#include <opensolid/Domain.hpp>
#include <opensolid/Geometry.hpp>

namespace opensolid
{
    Geometry GeometryConstructors::Arc2d(
        const Frame2d& frame,
        double radius,
        double start_angle,
        double end_angle
    ) {
        Datum2d datum = frame.scaled(radius);
        Function angle;
        if (end_angle - start_angle == Zero()) {
            angle = 2 * M_PI * Function::Parameter();
            datum = frame.scaled(radius);
        } else if (end_angle > start_angle) {
            angle = start_angle + (end_angle - start_angle) * Function::Parameter();
            datum = frame.scaled(radius);
        } else {
            datum = frame.scaled(radius).xReversed();
            angle = M_PI - start_angle + (start_angle - end_angle) * Function::Parameter();
        }
        return Geometry(Function::Elliptical(datum)(angle), Interval(0, 1));
    }
        
    Geometry GeometryConstructors::Arc2d(
        const Vector2d& center,
        bool counterclockwise,
        const Vector2d& start,
        const Vector2d& end
    ) {
        Vector2d radial = start - center;
        double radius = radial.norm();
        Datum2d datum = Frame2d(center, radial).scaled(radius);
        if (!counterclockwise) {datum = datum.yReversed();}
        Vector2d local_end = end / datum;
        double swept_angle = atan2(local_end.y(), local_end.x());
        if (swept_angle <= Zero()) {swept_angle += 2 * M_PI;}
        Function angle = swept_angle * Function::Parameter();
        return Geometry(Function::Elliptical(datum)(angle), Interval(0, 1));
    }

    Geometry GeometryConstructors::Arc2d(
        const Vector2d& start_point,
        const Vector2d& inner_point,
        const Vector2d& end_point
    ) {
        double a = (inner_point - start_point).norm();
        double b = (end_point - inner_point).norm();
        double c = (start_point - end_point).norm();
        double s = (a + b + c) / 2;
        assert(s - a > Zero() && s - b > Zero() && s - c > Zero());
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
        Vector2d center = t1 * end_point + t2 * start_point + t3 * inner_point;
        Vector2d first_leg = inner_point - start_point;
        Vector2d second_leg = end_point - inner_point;
        bool counterclockwise = (first_leg.x() * second_leg.y() - first_leg.y() - second_leg.x()) >= Zero();
        Vector2d start_radial_vector = start_point - center;
        Vector2d end_radial_vector = end_point - center;
        double start_angle = atan2(start_radial_vector.y(), start_radial_vector.x());
        double end_angle = atan2(end_radial_vector.y(), end_radial_vector.x());
        if (counterclockwise && end_angle < start_angle) {
            end_angle += 2 * M_PI;
        } else if (!counterclockwise && end_angle > start_angle) {
            end_angle -= 2 * M_PI;
        }
        return Geometry::Arc2d(Frame2d(center), radius, start_angle, end_angle);
    }

    Geometry GeometryConstructors::Arc3d(
        const Plane3d& plane,
        double radius,
        double start_angle,
        double end_angle
    ) {return Geometry::Arc2d(Frame2d(), radius, start_angle, end_angle) * plane;}

    Geometry GeometryConstructors::Arc3d(
        const Axis3d& axis,
        const Vector3d& start,
        const Vector3d& end
    ) {
        Vector3d center = start % axis;
        Plane3d plane = Plane3d(center, axis.direction());
        return Geometry::Arc2d(Vector2d::Zero(), true, start / plane, end / plane) * plane;
    }

    Geometry GeometryConstructors::Arc3d(
        const Vector3d& start_point,
        const Vector3d& inner_point,
        const Vector3d& end_point
    ) {
        Plane3d plane(inner_point, start_point - inner_point, end_point - inner_point);
        return Geometry::Arc2d(start_point / plane, inner_point / plane, end_point / plane) * plane;
    }

    Geometry GeometryConstructors::Circle2d(
        const Vector2d& center,
        double radius,
        bool filled
    ) {
        if (filled) {
            Function arc_function = Geometry::Arc2d(Frame2d(), radius, 0, 2 * M_PI).function();
            Function u = Function::Parameter(2, 0);
            Function v = Function::Parameter(2, 1);
            Function circle_function = center + u * arc_function(v);
            return Geometry(circle_function, Domain(Interval(0, 1), Interval(0, 1)));
        } else {
            return Geometry::Arc2d(Frame2d(center), radius, 0, 2 * M_PI);
        }
    }

    Geometry GeometryConstructors::Circle3d(
        const Axis3d& axis,
        double radius,
        bool filled
    ) {return Geometry::Circle2d(Vector2d::Zero(), radius, filled) * axis.normalPlane();}

    Geometry GeometryConstructors::Circle3d(
        const Plane3d& plane,
        double radius,
        bool filled
    ) {return Geometry::Circle2d(Vector2d::Zero(), radius, filled) * plane;}
        
    Geometry GeometryConstructors::Helix3d(
        const Frame3d& frame,
        double radius,
        double pitch,
        const Interval& turns
    ) {
        Function angle = 2 * M_PI * Function::Parameter();
        Function planar = Function::Elliptical(frame.xyPlane().scaled(radius))(angle);
        Function axial = Function::Linear(frame.zAxis().scaled(pitch));
        return Geometry(planar + axial, turns);
    }
}
