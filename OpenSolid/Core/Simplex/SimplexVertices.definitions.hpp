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

#include <OpenSolid/Core/Simplex/SimplexVertices.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/LazyCollection.definitions.hpp>
#include <OpenSolid/Core/LazyCollection/IndexIterator.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <class TSimplex, int iNumVertices>
    struct ItemType<detail::SimplexVertices<TSimplex, iNumVertices>>
    {
        typedef Point<NumDimensions<TSimplex>::Value> Type;
    };

    template <class TSimplex, int iNumVertices>
    struct ItemReferenceType<detail::SimplexVertices<TSimplex, iNumVertices>>
    {
        typedef const Point<NumDimensions<TSimplex>::Value>& Type;
    };

    namespace detail
    {
        template <class TSimplex, int iNumVertices>
        class SimplexVertices :
            public LazyCollection<SimplexVertices<TSimplex, iNumVertices>>
        {
        private:
            TSimplex _simplex;
        public:
            SimplexVertices(const TSimplex& simplex);

            const TSimplex&
            simplex() const;

            IndexIterator<SimplexVertices<TSimplex, iNumVertices>>
            begin() const;

            IndexIterator<SimplexVertices<TSimplex, iNumVertices>>
            end() const;

            bool
            isEmpty() const;

            std::size_t
            size() const;

            const Point<NumDimensions<TSimplex>::Value>&
            operator[](std::size_t index) const;
        };
    }
}
