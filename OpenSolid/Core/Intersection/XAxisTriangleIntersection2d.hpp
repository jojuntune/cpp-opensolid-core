/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Intersection/XAxisTriangleIntersection2d.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        inline
        bool
        XAxisTriangleIntersection2d::exists() const {
            return _type != NONE;
        }

        inline
        bool
        XAxisTriangleIntersection2d::isPoint() const {
            return _type == POINT;
        }

        inline
        bool
        XAxisTriangleIntersection2d::isLineSegment() const {
            return _type == LINE_SEGMENT;
        }

        inline
        bool
        XAxisTriangleIntersection2d::isCoincident() const {
            return _type == COINCIDENT;
        }

        inline
        const Point2d&
        XAxisTriangleIntersection2d::point() const {
            assert(_type == POINT);
            return _point;
        }

        inline
        const LineSegment2d&
        XAxisTriangleIntersection2d::lineSegment() const {
            assert(_type == LINE_SEGMENT);
            return _lineSegment;
        }
    }
}
