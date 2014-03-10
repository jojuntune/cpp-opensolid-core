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

#include <OpenSolid/Core/Position/BoxVertices.definitions.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/LazyCollection.hpp>
#include <OpenSolid/Core/LazyCollection/IndexIterator.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        BoxVertices<iNumDimensions>::BoxVertices(const Box<iNumDimensions>& box) :
            _box(box) {
        }

        template <int iNumDimensions>
        inline
        const Box<iNumDimensions>&
        BoxVertices<iNumDimensions>::box() const {
            return _box;
        }

        template <int iNumDimensions>
        inline
        IndexIterator<BoxVertices<iNumDimensions>>
        BoxVertices<iNumDimensions>::begin() const {
            return IndexIterator<BoxVertices<iNumDimensions>>::Begin(this);
        }

        template <int iNumDimensions>
        inline
        IndexIterator<BoxVertices<iNumDimensions>>
        BoxVertices<iNumDimensions>::end() const {
            return IndexIterator<BoxVertices<iNumDimensions>>::End(this);
        }

        template <int iNumDimensions>
        inline
        bool
        BoxVertices<iNumDimensions>::isEmpty() const {
            return false;
        }

        template <int iNumDimensions>
        inline
        std::int64_t
        BoxVertices<iNumDimensions>::size() const {
            return 1 << iNumDimensions;
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        BoxVertices<iNumDimensions>::operator[](std::int64_t index) const {
            return box().vertex(index);
        }
    }
}
