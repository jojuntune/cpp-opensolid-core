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

#include <OpenSolid/Datum/Frame.hpp>
#include <OpenSolid/Geometry/Arc.hpp>

namespace OpenSolid
{
    Geometry Arc2d(const Vector2d& center, double radius, double start_angle, double end_angle) {
        if (end_angle - start_angle == Zero()) {
            return Geometry(
                Function::Elliptical(Frame2d(center).scaled(radius, center)),
                Interval(0, 2 * M_PI)
            );
        } else if (end_angle > start_angle) {
            return Geometry(
                Function::Elliptical(Frame2d(center).scaled(radius, center)),
                Interval(start_angle, end_angle)
            );
        } else {
            return Geometry(
                Function::Elliptical(Frame2d(center).scaled(radius, center).xReversed()),
                Interval(M_PI - start_angle, M_PI - end_angle)
            );
        }
    }
    
    Geometry Arc2d(
        const Vector2d& center,
        const Vector2d& start,
        const Vector2d& end,
        bool counterclockwise
    ) {
        Vector2d radial = start - center;
        double radius = radial.norm();
        Datum2d datum = Frame2d(center, radial).scaled(radius, center);
        if (!counterclockwise) {datum = datum.yReversed();}
        Vector2d local_end = end / datum;
        double angle = atan2(local_end.y(), local_end.x());
        if (angle <= Zero()) {angle += 2 * M_PI;}
        return Geometry(Function::Elliptical(datum), Interval(0, angle));
    }
    
    Geometry Arc3d(const Plane3d& plane, double radius, double start_angle, double end_angle) {
        return Arc2d(Vector2d::Zero(), radius, start_angle, end_angle) * plane;
    }

    Geometry Arc3d(const Axis3d& axis, const Vector3d& start, const Vector3d& end) {
        Vector3d center = start % axis;
        Plane3d plane = Plane3d(center, axis.direction());
        return Arc2d(Vector2d::Zero(), start / plane, end / plane, true) * plane;
    }
}
