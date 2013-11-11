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

#include <OpenSolid/Core/SpatialCollection/TranslatedCollection.declarations.hpp>

#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection>
        class TranslatedCollection :
            public SpatialCollection<TranslatedCollection<TBaseCollection>>
        {
        private:
            const TBaseCollection& _baseCollection;
            Matrix<double, NumDimensions<TBaseCollection>::Value, 1> _vector;

            template <class TDerived>
            friend class opensolid::SpatialCollection;

            TranslatedCollectionIterator<TBaseCollection>
            beginImpl() const;

            TranslatedCollectionIterator<TBaseCollection>
            endImpl() const;

            bool
            isEmptyImpl() const;

            std::int64_t
            sizeImpl() const;

            typename TranslatedType<typename BoundsType<TBaseCollection>::Type>::Type
            boundsImpl() const;

            TranslatedCollection();
        public:
            TranslatedCollection(const TranslatedCollection<TBaseCollection>& other);

            template <class TVector>
            TranslatedCollection(
                const TBaseCollection& baseCollection,
                const EigenBase<TVector>& vector
            );

            const TBaseCollection&
            baseCollection() const;

            const Matrix<double, NumDimensions<TBaseCollection>::Value, 1>&
            vector() const;
        };

        template <class TBaseCollection>
        class TranslatedCollectionIterator :
            public boost::iterator_facade<
                TranslatedCollectionIterator<TBaseCollection>,
                typename TranslatedType<typename ItemType<TBaseCollection>::Type>::Type,
                boost::forward_traversal_tag,
                typename TranslatedType<typename ItemType<TBaseCollection>::Type>::Type
            >
        {
        private:
            typename IteratorType<TBaseCollection>::Type _baseIterator;
            const Matrix<double, NumDimensions<TBaseCollection>::Value, 1>* _vector;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(const TranslatedCollectionIterator<TBaseCollection>& other) const;

            typename TranslatedType<typename ItemType<TBaseCollection>::Type>::Type
            dereference() const;
        public:
            TranslatedCollectionIterator();

            TranslatedCollectionIterator(
                typename IteratorType<TBaseCollection>::Type baseIterator,
                const Matrix<double, NumDimensions<TBaseCollection>::Value, 1>* vector
            );
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
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
    struct BoundsType<detail::TranslatedCollection<TBaseCollection>>
    {
        typedef typename TranslatedType<typename BoundsType<TBaseCollection>::Type>::Type Type;
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

    template <class TBaseCollection>
    struct ScalingFunction<detail::TranslatedCollection<TBaseCollection>> :
        public ScalingFunction<SpatialCollection<detail::TranslatedCollection<TBaseCollection>>>
    {
    };

    template <class TBaseCollection>
    struct TranslationFunction<detail::TranslatedCollection<TBaseCollection>>
    {
        template <class TVector>
        detail::TranslatedCollection<TBaseCollection>
        operator()(
            const detail::TranslatedCollection<TBaseCollection>& translatedCollection,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct TransformationFunction<
        detail::TranslatedCollection<TBaseCollection>,
        iNumResultDimensions
    > : public TransformationFunction<
            SpatialCollection<detail::TranslatedCollection<TBaseCollection>>,
            iNumResultDimensions
        >
    {
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct MorphingFunction<detail::TranslatedCollection<TBaseCollection>, iNumResultDimensions> :
        public MorphingFunction<
            SpatialCollection<detail::TranslatedCollection<TBaseCollection>>,
            iNumResultDimensions
        >
    {
    };
}
