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

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection>
        class TranslatedCollection;

        template <class TBaseCollection>
        class TranslatedCollectionIterator;
    }

    template <class TBaseCollection>
    struct BoundsType<detail::TranslatedCollection<TBaseCollection>>
    {
        typedef typename TranslatedType<typename BoundsType<TBaseCollection>::Type>::Type Type;
    };
    
    template <class TBaseCollection>
    struct ItemType<detail::TranslatedCollection<TBaseCollection>>
    {
        typedef typename TranslatedType<typename ItemType<TBaseCollection>::Type>::Type Type;
    };

    template <class TBaseCollection>
    struct IteratorType<detail::TranslatedCollection<TBaseCollection>>
    {
        typedef detail::TranslatedCollectionIterator<TBaseCollection> Type;
    };

    template <class TBaseCollection>
    struct NumDimensions<detail::TranslatedCollection<TBaseCollection>>
    {
        static const int Value = NumDimensions<TBaseCollection>::Value;
    };

    template <class TBaseCollection>
    struct ScaledType<detail::TranslatedCollection<TBaseCollection>> :
        public ScaledType<SpatialCollection<detail::TranslatedCollection<TBaseCollection>>>
    {
    };

    template <class TBaseCollection>
    struct TranslatedType<detail::TranslatedCollection<TBaseCollection>>
    {
        typedef detail::TranslatedCollection<TBaseCollection> Type;
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct TransformedType<detail::TranslatedCollection<TBaseCollection>, iNumResultDimensions> :
        public TransformedType<
            SpatialCollection<detail::TranslatedCollection<TBaseCollection>>,
            iNumResultDimensions
        >
    {
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct MorphedType<detail::TranslatedCollection<TBaseCollection>, iNumResultDimensions> :
        public MorphedType<
            SpatialCollection<detail::TranslatedCollection<TBaseCollection>>,
            iNumResultDimensions
        >
    {
    };
}
