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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Simplex/TriangleEdges.definitions.hpp>

#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/LazyCollection.hpp>
#include <OpenSolid/Core/Triangle.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        TriangleEdges<iNumDimensions>::TriangleEdges(const Triangle<iNumDimensions>& triangle) :
            _triangle(triangle) {
        }

        template <int iNumDimensions>
        inline
        const Triangle<iNumDimensions>&
        TriangleEdges<iNumDimensions>::triangle() const {
            return _triangle;
        }

        template <int iNumDimensions>
        inline
        IndexIterator<TriangleEdges<iNumDimensions>>
        TriangleEdges<iNumDimensions>::begin() const {
            return IndexIterator<TriangleEdges<iNumDimensions>>::Begin(this);
        }

        template <int iNumDimensions>
        inline
        IndexIterator<TriangleEdges<iNumDimensions>>
        TriangleEdges<iNumDimensions>::end() const {
            return IndexIterator<TriangleEdges<iNumDimensions>>::End(this);
        }

        template <int iNumDimensions>
        inline
        bool
        TriangleEdges<iNumDimensions>::isEmpty() const {
            return false;
        }

        template <int iNumDimensions>
        inline
        std::int64_t
        TriangleEdges<iNumDimensions>::size() const {
            return 3;
        }

        template <int iNumDimensions>
        inline
        LineSegment<iNumDimensions>
        TriangleEdges<iNumDimensions>::operator[](std::int64_t index) const {
            return triangle().edge(index);
        }
    }
}
