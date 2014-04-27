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

#include <OpenSolid/Core/Simplex/SimplexVertices.definitions.hpp>

#include <OpenSolid/Core/LazyCollection.hpp>
#include <OpenSolid/Core/LazyCollection/IndexIterator.hpp>
#include <OpenSolid/Core/Point.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TSimplex, int iNumVertices>
        inline
        SimplexVertices<TSimplex, iNumVertices>::SimplexVertices(const TSimplex& simplex) :
            _simplex(simplex) {
        }

        template <class TSimplex, int iNumVertices>
        inline
        const TSimplex&
        SimplexVertices<TSimplex, iNumVertices>::simplex() const {
            return _simplex;
        }

        template <class TSimplex, int iNumVertices>
        inline
        IndexIterator<SimplexVertices<TSimplex, iNumVertices>>
        SimplexVertices<TSimplex, iNumVertices>::begin() const {
            return IndexIterator<SimplexVertices<TSimplex, iNumVertices>>::Begin(this);
        }

        template <class TSimplex, int iNumVertices>
        inline
        IndexIterator<SimplexVertices<TSimplex, iNumVertices>>
        SimplexVertices<TSimplex, iNumVertices>::end() const {
            return IndexIterator<SimplexVertices<TSimplex, iNumVertices>>::End(this);
        }

        template <class TSimplex, int iNumVertices>
        inline
        bool
        SimplexVertices<TSimplex, iNumVertices>::isEmpty() const {
            return false;
        }

        template <class TSimplex, int iNumVertices>
        inline
        std::size_t
        SimplexVertices<TSimplex, iNumVertices>::size() const {
            return iNumVertices;
        }

        template <class TSimplex, int iNumVertices>
        inline
        const Point<NumDimensions<TSimplex>::Value>&
        SimplexVertices<TSimplex, iNumVertices>::operator[](std::size_t index) const {
            return simplex().vertex(int(index));
        }
    }
}
