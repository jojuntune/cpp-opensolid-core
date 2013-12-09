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
        template <int iNumDimensions>
        class BoxVertices;
    }

    template <int iNumDimensions>
    struct NumDimensions<detail::BoxVertices<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions>
    struct ItemType<detail::BoxVertices<iNumDimensions>>
    {
        typedef Point<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ItemReferenceType<detail::BoxVertices<iNumDimensions>>
    {
        typedef Point<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ScaledType<detail::BoxVertices<iNumDimensions>>
    {
        typedef detail::BoxVertices<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct TranslatedType<detail::BoxVertices<iNumDimensions>>
    {
        typedef detail::BoxVertices<iNumDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<detail::BoxVertices<iNumDimensions>, iNumResultDimensions>
    {
        typedef typename TransformedType<
            SpatialCollection<detail::BoxVertices<iNumDimensions>>,
            iNumResultDimensions
        >::Type Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<detail::BoxVertices<iNumDimensions>, iNumResultDimensions>
    {
        typedef typename MorphedType<
            SpatialCollection<detail::BoxVertices<iNumDimensions>>,
            iNumResultDimensions
        >::Type Type;
    };

    template <int iNumDimensions>
    struct BoundsType<detail::BoxVertices<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };
}
