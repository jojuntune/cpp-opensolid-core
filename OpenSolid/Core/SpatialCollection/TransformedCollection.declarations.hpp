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
        template <class TBaseCollection, int iNumResultDimensions>
        class TransformedCollection;

        template <class TBaseCollection, int iNumResultDimensions>
        class TransformedCollectionIterator;
    }

    template <class TBaseCollection, int iNumResultDimensions>
    struct BoundsType<detail::TransformedCollection<TBaseCollection, iNumResultDimensions>>
    {
        typedef typename TransformedType<
            typename BoundsType<TBaseCollection>::Type,
            iNumResultDimensions
        >::Type Type;
    };
    
    template <class TBaseCollection, int iNumResultDimensions>
    struct ItemType<detail::TransformedCollection<TBaseCollection, iNumResultDimensions>>
    {
        typedef typename TransformedType<
            typename ItemType<TBaseCollection>::Type,
            iNumResultDimensions
        >::Type Type;
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct IteratorType<detail::TransformedCollection<TBaseCollection, iNumResultDimensions>>
    {
        typedef detail::TransformedCollectionIterator<TBaseCollection, iNumResultDimensions> Type;
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct NumDimensions<detail::TransformedCollection<TBaseCollection, iNumResultDimensions>>
    {
        static const int Value = iNumResultDimensions;
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct ScaledType<detail::TransformedCollection<TBaseCollection, iNumResultDimensions>>
    {
        typedef detail::TransformedCollection<TBaseCollection, iNumResultDimensions> Type;
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct TranslatedType<detail::TransformedCollection<TBaseCollection, iNumResultDimensions>> :
        public TranslatedType<
            SpatialCollection<
                detail::TransformedCollection<TBaseCollection, iNumResultDimensions>
            >
        >
    {
    };

    template <class TBaseCollection, int iNumInnerResultDimensions, int iNumOuterResultDimensions>
    struct TransformedType<
        detail::TransformedCollection<TBaseCollection, iNumInnerResultDimensions>,
        iNumOuterResultDimensions
    >
    {
        typedef detail::TransformedCollection<TBaseCollection, iNumOuterResultDimensions> Type;
    };

    template <class TBaseCollection, int iNumInnerResultDimensions, int iNumOuterResultDimensions>
    struct MorphedType<
        detail::TransformedCollection<TBaseCollection, iNumInnerResultDimensions>,
        iNumOuterResultDimensions
    > : public MorphedType<
            SpatialCollection<
                detail::TransformedCollection<TBaseCollection, iNumInnerResultDimensions>
            >,
            iNumOuterResultDimensions
        >
    {
    };
}
