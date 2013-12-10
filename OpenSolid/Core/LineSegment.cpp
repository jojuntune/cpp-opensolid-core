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
    LineSegmentPlaneIntersection3d::LineSegmentPlaneIntersection3d(
        const LineSegment3d& lineSegment,
        const Plane3d& plane,
        double precision
    ) : _lineSegment(lineSegment),
        _plane(plane),
        _precision(precision),
        _startHeight(lineSegment.startVertex().distanceTo(plane)),
        _endHeight(lineSegment.endVertex().distanceTo(plane)) {
    }

    int
    LineSegmentPlaneIntersection3d::type() const {
        if (_startHeight < Zero(_precision)) {
            if (_endHeight < Zero(_precision)) {
                return NO_INTERSECTION | BELOW;
            } else if (_endHeight > Zero(_precision)) {
                return INTERSECTION | CROSSING;
            } else {
                return INTERSECTION | BELOW | CONTACT_END;
            }
        } else if (_startHeight > Zero(_precision)) {
            if (_endHeight < Zero(_precision)) {
                return INTERSECTION | CROSSING;
            } else if (_endHeight > Zero(_precision)) {
                return NO_INTERSECTION | ABOVE;
            } else {
                return INTERSECTION | ABOVE | CONTACT_END;
            }
        } else {
            if (_endHeight < Zero(_precision)) {
                return INTERSECTION | BELOW | CONTACT_START;
            } else if (_endHeight > Zero(_precision)) {
                return INTERSECTION | ABOVE | CONTACT_START;
            } else {
                return INTERSECTION | COINCIDENT;
            }
        }
    }

    Point3d
    LineSegmentPlaneIntersection3d::point() const {
        if (_startHeight < Zero(_precision)) {
            if (_endHeight < Zero(_precision)) {
                assert(false);
                return Point3d();
            } else if (_endHeight > Zero(_precision)) {
                return Point3d(
                    (_startHeight * lineSegment().endVertex().vector() -
                        _endHeight * lineSegment().startVertex().vector()) /
                            (_startHeight - _endHeight)
                );
            } else {
                return lineSegment().endVertex();
            }
        } else if (_startHeight > Zero(_precision)) {
            if (_endHeight < Zero(_precision)) {
                return Point3d(
                    (_startHeight * lineSegment().endVertex().vector() -
                        _endHeight * lineSegment().startVertex().vector()) /
                            (_startHeight - _endHeight)
                );
            } else if (_endHeight > Zero(_precision)) {
                assert(false);
                return Point3d();
            } else {
                return lineSegment().endVertex();
            }
        } else {
            if (_endHeight < Zero(_precision)) {
                return lineSegment().startVertex();
            } else if (_endHeight > Zero(_precision)) {
                return lineSegment().startVertex();
            } else {
                assert(false);
                return Point3d();
            }
        }
    }
}
