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

#include <OpenSolid/Core/SpatialCollection.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TSimplex, int iNumVertices>
        class SimplexVertices;
    }

    template <class TSimplex, int iNumVertices>
    struct NumDimensions<detail::SimplexVertices<TSimplex, iNumVertices>>
    {
        static const int Value = NumDimensions<TSimplex>::Value;
    };

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

    template <class TSimplex, int iNumVertices>
    struct ScaledType<detail::SimplexVertices<TSimplex, iNumVertices>>
    {
        typedef detail::SimplexVertices<TSimplex, iNumVertices> Type;
    };

    template <class TSimplex, int iNumVertices>
    struct TranslatedType<detail::SimplexVertices<TSimplex, iNumVertices>>
    {
        typedef detail::SimplexVertices<TSimplex, iNumVertices> Type;
    };

    template <class TSimplex, int iNumVertices, int iNumResultDimensions>
    struct TransformedType<detail::SimplexVertices<TSimplex, iNumVertices>, iNumResultDimensions>
    {
        typedef detail::SimplexVertices<
            typename TransformedType<TSimplex, iNumResultDimensions>::Type,
            iNumVertices
        > Type;
    };

    template <class TSimplex, int iNumVertices, int iNumResultDimensions>
    struct MorphedType<detail::SimplexVertices<TSimplex, iNumVertices>, iNumResultDimensions>
    {
        typedef detail::SimplexVertices<
            typename MorphedType<TSimplex, iNumResultDimensions>::Type,
            iNumVertices
        > Type;
    };

    template <class TSimplex, int iNumVertices>
    struct BoundsType<detail::SimplexVertices<TSimplex, iNumVertices>>
    {
        typedef typename BoundsType<TSimplex>::Type Type;
    };
}
