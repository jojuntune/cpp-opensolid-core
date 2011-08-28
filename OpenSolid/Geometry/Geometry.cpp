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

#include <OpenSolid/Scalar/Comparison.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>

namespace OpenSolid
{   
    Geometry Geometry::Line(const VectorXd& start, const VectorXd& end) {
        return Geometry(start + Function::t * (end - start), Interval(0, 1));
    }
    
    Geometry Geometry::Arc(double radius, const Interval& angle) {
        Vector2d x_vector = radius * Vector2d::UnitX();
        Vector2d y_vector = radius * Vector2d::UnitY();
        return Geometry(cos(Function::t) * x_vector + sin(Function::t) * y_vector, angle);
    }
    
    Geometry Geometry::Arc(
        const Vector2d& center,
        const Vector2d& start,
        const Vector2d& end,
        bool counterclockwise
    ) {
        Vector2d start_radial = start - center;
        double radius = start_radial.norm();
        Vector2d end_radial = end - center;
        assert(end_radial.norm() == Approx(radius));
        Vector2d perpendicular = start_radial.unitOrthogonal() * radius;
        if (!counterclockwise) {perpendicular = -perpendicular;}
        double angle = atan2(end_radial.dot(perpendicular), end_radial.dot(start_radial));
        if (angle <= Zero()) {angle += 2 * M_PI;}
        return Geometry(
            center + cos(Function::t) * start_radial + sin(Function::t) * perpendicular,
            Interval(0, angle)
        );
    }
    
    Geometry Geometry::Arc(
        const Axis3d& axis,
        const Vector3d& start,
        const Vector3d& end
    ) {
        Vector3d center = (start / axis) * axis;
        Vector3d start_radial = start - center;
        Vector3d end_radial = end - center;
        assert(end_radial.isOrthogonal(axis.vector()));
        double radius = start_radial.norm();
        assert(end_radial.norm() == Approx(radius));
        Vector3d perpendicular = axis.vector().cross(start_radial).normalized() * radius;
        double angle = atan2(end_radial.dot(perpendicular), end_radial.dot(start_radial));
        if (angle <= Zero()) {angle += 2 * M_PI;}
        return Geometry(
            center + cos(Function::t) * start_radial + sin(Function::t) * perpendicular,
            Interval(0, angle)
        );
    }
    
    Geometry Geometry::Circle(double radius) {
        Interval angle(0, 2 * M_PI);
        Function theta = Function::Parameter(1, 0);
        return Geometry(Function(radius * cos(theta), radius * sin(theta)), angle);
    }
    
    Geometry Geometry::Helix(double radius, double pitch, const Interval& angle) {
        Function theta = Function::Parameter(1, 0);
        return Geometry(
            Function(radius * cos(theta), radius * sin(theta), theta * (pitch / (2 * M_PI))),
            angle
        );
    }
    
    Geometry operator*(const Geometry& geometry, const DatumXd& datum) {
        return Geometry(geometry.function() * datum, geometry.domain());
    }
    
    Geometry operator/(const Geometry& geometry, const DatumXd& datum) {
        return Geometry(geometry.function() / datum, geometry.domain());
    }
}
