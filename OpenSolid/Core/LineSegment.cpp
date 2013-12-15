/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#include <OpenSolid/Core/LineSegment.hpp>

#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    Intersection<LineSegment3d, Plane3d>::Intersection(
        const LineSegment3d& lineSegment,
        const Plane3d& plane,
        double precision
    ) : _lineSegment(lineSegment),
        _plane(plane),
        _precision(precision),
        _startHeight(lineSegment.startVertex().distanceTo(plane)),
        _endHeight(lineSegment.endVertex().distanceTo(plane)),
        _type(0) {

        if (_startHeight < Zero(_precision)) {
            if (_endHeight < Zero(_precision)) {
                _type = NO_INTERSECTION | BELOW;
            } else if (_endHeight > Zero(_precision)) {
                _type = INTERSECTION | CROSSING | UPWARDS;
            } else {
                _type = INTERSECTION | BELOW | UPWARDS | CONTACT_END;
            }
        } else if (_startHeight > Zero(_precision)) {
            if (_endHeight < Zero(_precision)) {
                _type = INTERSECTION | CROSSING | DOWNWARDS;
            } else if (_endHeight > Zero(_precision)) {
                _type = NO_INTERSECTION | ABOVE;
            } else {
                _type = INTERSECTION | ABOVE | DOWNWARDS | CONTACT_END;
            }
        } else {
            if (_endHeight < Zero(_precision)) {
                _type = INTERSECTION | DOWNWARDS | BELOW | CONTACT_START;
            } else if (_endHeight > Zero(_precision)) {
                _type = INTERSECTION | UPWARDS | ABOVE | CONTACT_START;
            } else {
                _type = INTERSECTION | COINCIDENT;
            }
        }
    }

    Point3d
    Intersection<LineSegment3d, Plane3d>::point() const {
        if (_type & CROSSING) {
            const Vector3d& startVector = lineSegment().startVertex().vector();
            const Vector3d& endVector = lineSegment().endVertex().vector();
            return Point3d(
                (_startHeight * endVector - _endHeight * startVector) / (_startHeight - _endHeight)
            );
        } else if (_type & CONTACT_START) {
            return lineSegment().startVertex();
        } else if (_type & CONTACT_END) {
            return lineSegment().endVertex();
        } else {
            assert(false);
            return Point3d();
        }
    }
}
