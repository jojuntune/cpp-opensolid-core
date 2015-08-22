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

#include <OpenSolid/Core/LineSegment.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        class XAxisTriangleIntersection2d
        {
        private:
            enum IntersectionType
            {
                NONE,
                POINT,
                LINE_SEGMENT,
                COINCIDENT
            };

            IntersectionType _type;
            Point<2> _point;
            LineSegment<2> _lineSegment;
        public:
            OPENSOLID_CORE_EXPORT
            XAxisTriangleIntersection2d(const Triangle<2>& triangle, double precision = 1e-12);

            bool
            exists() const;

            bool
            isPoint() const;

            bool
            isLineSegment() const;

            bool
            isCoincident() const;

            const Point<2>&
            point() const;

            const LineSegment<2>&
            lineSegment() const;
        };
    }
}
