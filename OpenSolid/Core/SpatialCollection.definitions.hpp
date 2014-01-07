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

#include <OpenSolid/Core/BoundsType.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/FilteredCollection.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection/IndexIterator.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection/MappedCollection.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection/MorphedCollection.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection/ScaledCollection.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection/TransformedCollection.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection/TranslatedCollection.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <iterator>
#include <vector>

namespace opensolid
{
    template <class TDerived>
    struct BoundsType<SpatialCollection<TDerived>>
    {
        typedef typename BoundsType<typename ItemType<TDerived>::Type>::Type Type;
    };

    template <class TDerived>
    struct NumDimensions<SpatialCollection<TDerived>>
    {
        static const int Value = NumDimensions<typename ItemType<TDerived>::Type>::Value;
    };

    template <class TDerived>
    struct ScaledType<SpatialCollection<TDerived>>
    {
        typedef detail::ScaledCollection<TDerived> Type;
    };

    template <class TDerived>
    struct TranslatedType<SpatialCollection<TDerived>>
    {
        typedef detail::TranslatedCollection<TDerived> Type;
    };

    template <class TDerived, int iNumResultDimensions>
    struct TransformedType<SpatialCollection<TDerived>, iNumResultDimensions>
    {
        typedef detail::TransformedCollection<TDerived, iNumResultDimensions> Type;
    };

    template <class TDerived, int iNumResultDimensions>
    struct MorphedType<SpatialCollection<TDerived>, iNumResultDimensions>
    {
        typedef detail::MorphedCollection<TDerived, iNumResultDimensions> Type;
    };
    
    template <class TCollection>
    struct IteratorType
    {
        typedef detail::IndexIterator<TCollection> Type;
    };

    template <class TCollection>
    struct ItemType
    {
        typedef typename std::iterator_traits<
            typename IteratorType<TCollection>::Type
        >::value_type Type;
    };

    template <class TCollection>
    struct ItemReferenceType
    {
        typedef typename std::iterator_traits<
            typename IteratorType<TCollection>::Type
        >::reference Type;
    };

    namespace detail
    {
        template <class TDerived, bool bItemIsTransformable>
        class TransformableCollectionBase;

        template <class TDerived>
        class TransformableCollectionBase<TDerived, true> :
            public Transformable<TDerived>
        {
        };

        template <class TDerived>
        class TransformableCollectionBase<TDerived, false>
        {
        };

        template <class TDerived, bool bItemIsBounded>
        class BoundedCollectionBase;

        template <class TDerived>
        class BoundedCollectionBase<TDerived, true>
        {
        private:
            const TDerived&
            derived() const;
        protected:
            typename BoundsType<typename ItemType<TDerived>::Type>::Type
            boundsDefaultImpl() const;
        public:
            typename BoundsType<typename ItemType<TDerived>::Type>::Type
            bounds() const;
        };

        template <class TDerived>
        class BoundedCollectionBase<TDerived, false>
        {
        };
    }

    template <class TDerived>
    class SpatialCollection :
        public detail::TransformableCollectionBase<
            TDerived,
            IsTransformable<typename ItemType<TDerived>::Type>::Value
        >,
        public detail::BoundedCollectionBase<
            TDerived,
            IsBounded<typename ItemType<TDerived>::Type>::Value
        >
    {
    protected:
        bool
        isEmptyDefaultImpl() const;

        std::int64_t
        sizeDefaultImpl() const;
    public:
        const TDerived&
        derived() const;

        typename IteratorType<TDerived>::Type
        begin() const;

        typename IteratorType<TDerived>::Type
        end() const;

        bool
        isEmpty() const;

        std::int64_t
        size() const;

        template <class TPredicate>
        bool
        any(TPredicate predicate) const;

        template <class TPredicate>
        bool
        all(TPredicate predicate) const;

        template <class TValue, class TFunction>
        TValue
        fold(const TValue& initialValue, TFunction function) const;

        template <class TFunction>
        void
        forEach(TFunction function) const;

        template <class TFunction>
        typename ItemType<TDerived>::Type
        reduce(TFunction function) const;

        template <class TPredicate>
        detail::FilteredCollection<TDerived, TPredicate>
        where(TPredicate predicate) const;

        template <class TMappingFunction>
        detail::MappedCollection<TDerived, TMappingFunction>
        map(TMappingFunction mappingFunction) const;

        operator std::vector<typename ItemType<TDerived>::Type>() const;
    };

    template <class TDerived>
    struct ScalingFunction<SpatialCollection<TDerived>>
    {
        detail::ScaledCollection<TDerived>
        operator()(const SpatialCollection<TDerived>& collection, double scale) const;
    };

    template <class TDerived>
    struct TranslationFunction<SpatialCollection<TDerived>>
    {
        template <class TVector>
        detail::TranslatedCollection<TDerived>
        operator()(
            const SpatialCollection<TDerived>& collection,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <class TDerived, int iNumResultDimensions>
    struct TransformationFunction<SpatialCollection<TDerived>, iNumResultDimensions>
    {
        template <class TMatrix>
        detail::TransformedCollection<TDerived, iNumResultDimensions>
        operator()(
            const SpatialCollection<TDerived>& collection,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <class TDerived, int iNumResultDimensions>
    struct MorphingFunction<SpatialCollection<TDerived>, iNumResultDimensions>
    {
        detail::MorphedCollection<TDerived, iNumResultDimensions>
        operator()(
            const SpatialCollection<TDerived>& collection,
            const ParametricExpression<
                iNumResultDimensions,
                NumDimensions<TDerived>::Value
            >& morphingExpression
        ) const;
    };
}

#include <OpenSolid/Core/SpatialCollection/MappedCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/MorphedCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/ScaledCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/TransformedCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/TranslatedCollection.definitions.hpp>
