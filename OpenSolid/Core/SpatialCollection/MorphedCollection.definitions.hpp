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

#include <OpenSolid/Core/SpatialCollection/MorphedCollection.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    template <class TBaseCollection, int iNumResultDimensions>
    struct BoundsType<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>>
    {
        typedef typename MorphedType<
            typename BoundsType<TBaseCollection>::Type,
            iNumResultDimensions
        >::Type Type;
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

    template <class TBaseCollection, int iNumResultDimensions>
    struct IteratorType<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>>
    {
        typedef detail::MorphedCollectionIterator<TBaseCollection, iNumResultDimensions> Type;
    };

    namespace detail
    {
        template <class TBaseCollection, int iNumResultDimensions>
        class MorphedCollection :
            public SpatialCollection<MorphedCollection<TBaseCollection, iNumResultDimensions>>
        {
        private:
            TBaseCollection _baseCollection;

            ParametricExpression<
                iNumResultDimensions,
                NumDimensions<TBaseCollection>::Value
            > _morphingExpression;
        public:
            MorphedCollection(
                const MorphedCollection<TBaseCollection, iNumResultDimensions>& other
            );

            MorphedCollection(
                MorphedCollection<TBaseCollection, iNumResultDimensions>&& other
            );

            MorphedCollection(
                const TBaseCollection& baseCollection,
                const ParametricExpression<
                    iNumResultDimensions,
                    NumDimensions<TBaseCollection>::Value
                >& morphingExpression
            );

            MorphedCollection(
                TBaseCollection&& baseCollection,
                const ParametricExpression<
                    iNumResultDimensions,
                    NumDimensions<TBaseCollection>::Value
                >& morphingExpression
            );

            const TBaseCollection&
            baseCollection() const;

            const ParametricExpression<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>&
            morphingExpression() const;

            MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>
            begin() const;

            MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            typename MorphedType<
                typename BoundsType<TBaseCollection>::Type,
                iNumResultDimensions
            >::Type
            bounds() const;
        };

        template <class TBaseCollection, int iNumResultDimensions>
        class MorphedCollectionIterator :
            public boost::iterator_facade<
                MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>,
                typename MorphedType<
                    typename ItemType<TBaseCollection>::Type,
                    iNumResultDimensions
                >::Type,
                boost::forward_traversal_tag,
                typename MorphedType<
                    typename ItemType<TBaseCollection>::Type,
                    iNumResultDimensions
                >::Type
            >
        {
        private:
            typename IteratorType<TBaseCollection>::Type _baseIterator;

            const ParametricExpression<
                iNumResultDimensions,
                NumDimensions<TBaseCollection>::Value
            >* _morphingExpressionPtr;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(
                const MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>& other
            ) const;

            typename MorphedType<
                typename ItemType<TBaseCollection>::Type,
                iNumResultDimensions
            >::Type
            dereference() const;
        public:
            MorphedCollectionIterator();

            MorphedCollectionIterator(
                typename IteratorType<TBaseCollection>::Type baseIterator,
                const ParametricExpression<
                    iNumResultDimensions,
                    NumDimensions<TBaseCollection>::Value
                >* morphingExpressionPtr
            );
        };
    }
    
    template <class TBaseCollection, int iNumResultDimensions>
    struct ScalingFunction<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>> :
        public ScalingFunction<
            SpatialCollection<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>>
        >
    {
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct TranslationFunction<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>> :
        public TranslationFunction<
            SpatialCollection<detail::MorphedCollection<TBaseCollection, iNumResultDimensions>>
        >
    {
    };

    template <class TBaseCollection, int iNumInnerResultDimensions, int iNumOuterResultDimensions>
    struct TransformationFunction<
        detail::MorphedCollection<TBaseCollection, iNumInnerResultDimensions>,
        iNumOuterResultDimensions
    > : public TransformationFunction<
            SpatialCollection<
                detail::MorphedCollection<TBaseCollection, iNumInnerResultDimensions>
            >,
            iNumOuterResultDimensions
        >
    {
    };

    template <class TBaseCollection, int iNumInnerResultDimensions, int iNumOuterResultDimensions>
    struct MorphingFunction<
        detail::MorphedCollection<TBaseCollection, iNumInnerResultDimensions>,
        iNumOuterResultDimensions
    > 
    {
        detail::MorphedCollection<TBaseCollection, iNumOuterResultDimensions>
        operator()(
            const detail::MorphedCollection<
                TBaseCollection,
                iNumInnerResultDimensions
            >& morphedCollection,
            const ParametricExpression<
                iNumOuterResultDimensions,
                iNumInnerResultDimensions
            >& morphingExpression
        ) const;
    };
}
