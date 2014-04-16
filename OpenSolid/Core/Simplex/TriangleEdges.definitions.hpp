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

#include <OpenSolid/Core/Simplex/TriangleEdges.declarations.hpp>

#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/LazyCollection.definitions.hpp>
#include <OpenSolid/Core/Triangle.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct ItemType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef LineSegment<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ItemReferenceType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef LineSegment<iNumDimensions> Type;
    };

    namespace detail
    {
        template <int iNumDimensions>
        class TriangleEdges :
            public LazyCollection<TriangleEdges<iNumDimensions>>
        {
        private:
            Triangle<iNumDimensions> _triangle;
        public:
            TriangleEdges(const Triangle<iNumDimensions>& triangle);

            const Triangle<iNumDimensions>&
            triangle() const;

            IndexIterator<TriangleEdges<iNumDimensions>>
            begin() const;

            IndexIterator<TriangleEdges<iNumDimensions>>
            end() const;

            bool
            isEmpty() const;

            std::size_t
            size() const;

            LineSegment<iNumDimensions>
            operator[](std::size_t index) const;
        };
    }
}
