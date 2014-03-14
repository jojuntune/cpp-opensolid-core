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

#pragma once

#include <OpenSolid/Core/Simplex/TriangleBase.definitions.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.hpp>
#include <OpenSolid/Core/Simplex/TriangleEdges.hpp>
#include <OpenSolid/Core/Triangle.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        const Triangle<iNumDimensions>&
        TriangleBase<iNumDimensions>::derived() const {
            return static_cast<const Triangle<iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        TriangleBase<iNumDimensions>::TriangleBase() {
        }

        template <int iNumDimensions>
        inline
        TriangleBase<iNumDimensions>::TriangleBase(
            const Point<iNumDimensions>& firstVertex,
            const Point<iNumDimensions>& secondVertex,
            const Point<iNumDimensions>& thirdVertex
        ) {
            _vertices[0] = firstVertex;
            _vertices[1] = secondVertex;
            _vertices[2] = thirdVertex;
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        TriangleBase<iNumDimensions>::vertex(std::int64_t index) const {
            assert(index >= 0 && index < 3);
            return _vertices[index];
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>&
        TriangleBase<iNumDimensions>::vertex(std::int64_t index) {
            assert(index >= 0 && index < 3);
            return _vertices[index];
        }

        template <int iNumDimensions>
        inline
        SimplexVertices<Triangle<iNumDimensions>, 3>
        TriangleBase<iNumDimensions>::vertices() const {
            return SimplexVertices<Triangle<iNumDimensions>, 3>(derived());
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        TriangleBase<iNumDimensions>::centroid() const {
            return Point<iNumDimensions>(
                (vertex(0).components() + vertex(1).components() + vertex(2).components()) / 3.0
            );
        }

        template <int iNumDimensions>
        inline
        LineSegment<iNumDimensions>
        TriangleBase<iNumDimensions>::edge(std::int64_t oppositeIndex) const {
            assert(oppositeIndex >= 0 && oppositeIndex < 3);
            return LineSegment<iNumDimensions>(
                vertex((oppositeIndex + 2) % 3),
                vertex((oppositeIndex + 1) % 3)
            );
        }

        template <int iNumDimensions>
        inline
        TriangleEdges<iNumDimensions>
        TriangleBase<iNumDimensions>::edges() const {
            return TriangleEdges<iNumDimensions>(derived());
        }

        template <int iNumDimensions>
        inline
        CoordinateSystem<iNumDimensions, 2>
        TriangleBase<iNumDimensions>::coordinateSystem() const {
            return CoordinateSystem<iNumDimensions, 2>(
                vertex(0),
                vertex(1) - vertex(0),
                vertex(2) - vertex(0)
            );
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        TriangleBase<iNumDimensions>::bounds() const {
            return vertex(0).hull(vertex(1)).hull(vertex(2));
        }

        template <int iNumDimensions>
        inline
        bool
        TriangleBase<iNumDimensions>::operator==(const Triangle<iNumDimensions>& other) const {
            return vertex(0) == other.vertex(0) &&
                vertex(1) == other.vertex(1) &&
                vertex(2) == other.vertex(2);
        }
    }
}
