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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection, int iNumResultDimensions>
        class MorphedCollection;

        template <class TBaseCollection, int iNumResultDimensions>
        class MorphedCollectionIterator;
    }

    template <class TBaseCollection, int iNumResultDimensions>
    struct BoundsType<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>>
    {
        typedef typename MorphedType<
            typename BoundsType<TBaseCollection>::Type,
            iNumResultDimensions
        >::Type Type;
    };
    
    template <class TBaseCollection, int iNumResultDimensions>
    struct ItemType<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>>
    {
        typedef typename MorphedType<
            typename ItemType<TBaseCollection>::Type,
            iNumResultDimensions
        >::Type Type;
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct IteratorType<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>>
    {
        typedef detail::MorphedCollectionIterator<TBaseCollection, iNumResultDimensions> Type;
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct NumDimensions<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>>
    {
        static const int Value = iNumResultDimensions;
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct ScaledType<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>> :
        public ScaledType<
            SpatialCollection<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>>
        >
    {
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct TranslatedType<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>> :
        public TranslatedType<
            SpatialCollection<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>>
        >
    {
    };

    template <class TBaseCollection, int iNumInnerResultDimensions, int iNumOuterResultDimensions>
    struct TransformedType<
        detail::MorphedCollection<TBaseCollection, iNumInnerResultDimensions>,
        iNumOuterResultDimensions
    > : public TransformedType<
            SpatialCollection<
                detail::MorphedCollection<TBaseCollection, iNumInnerResultDimensions>
            >,
            iNumOuterResultDimensions
        >
    {
    };

    template <class TBaseCollection, int iNumInnerResultDimensions, int iNumOuterResultDimensions>
    struct MorphedType<
        detail::MorphedCollection<TBaseCollection, iNumInnerResultDimensions>,
        iNumOuterResultDimensions
    >
    {
        typedef detail::MorphedCollection<TBaseCollection, iNumOuterResultDimensions> Type;
    };
}
