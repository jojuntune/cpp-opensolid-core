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

#include <OpenSolid/Core/Simplex/TriangleBase.declarations.hpp>

#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.declarations.hpp>
#include <OpenSolid/Core/Simplex/TriangleEdges.declarations.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class TriangleBase
        {
        private:
            Point<iNumDimensions> _vertices[3];

            const Triangle<iNumDimensions>&
            derived() const;
        protected:
            TriangleBase();

            TriangleBase(
                const Point<iNumDimensions>& firstVertex,
                const Point<iNumDimensions>& secondVertex,
                const Point<iNumDimensions>& thirdVertex
            );
        public:
            const Point<iNumDimensions>&
            vertex(int index) const;

            Point<iNumDimensions>&
            vertex(int index);

            SimplexVertices<Triangle<iNumDimensions>, 3>
            vertices() const;

            Point<iNumDimensions>
            centroid() const;

            LineSegment<iNumDimensions>
            edge(int oppositeIndex) const;

            TriangleEdges<iNumDimensions>
            edges() const;

            CoordinateSystem<iNumDimensions, 2>
            coordinateSystem() const;

            Box<iNumDimensions>
            bounds() const;

            bool
            operator==(const Triangle<iNumDimensions>& other) const;
        };
    }
}
