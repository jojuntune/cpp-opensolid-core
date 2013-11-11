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

#include <OpenSolid/Core/SpatialCollection/TransformedCollection.declarations.hpp>

#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection, int iNumResultDimensions>
        class TransformedCollection :
            public SpatialCollection<TransformedCollection<TBaseCollection, iNumResultDimensions>>
        {
        private:
            const TBaseCollection& _baseCollection;

            Matrix<
                double,
                iNumResultDimensions,
                NumDimensions<TBaseCollection>::Value
            > _transformationMatrix;

            template <class TDerived>
            friend class opensolid::SpatialCollection;

            TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>
            beginImpl() const;

            TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>
            endImpl() const;

            bool
            isEmptyImpl() const;

            std::int64_t
            sizeImpl() const;

            typename TransformedType<
                typename BoundsType<TBaseCollection>::Type,
                iNumResultDimensions
            >::Type
            boundsImpl() const;
        public:
            template <class TMatrix>
            TransformedCollection(
                const TBaseCollection& baseCollection,
                const EigenBase<TMatrix>& transformationMatrix
            );

            const TBaseCollection&
            baseCollection() const;

            const Matrix<double, iNumResultDimensions, NumDimensions<TBaseCollection>::Value>&
            transformationMatrix() const;
        };

        template <class TBaseCollection, int iNumResultDimensions>
        class TransformedCollectionIterator :
            public boost::iterator_facade<
                TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>,
                typename TransformedType<
                    typename ItemType<TBaseCollection>::Type,
                    iNumResultDimensions
                >::Type,
                boost::forward_traversal_tag,
                typename TransformedType<
                    typename ItemType<TBaseCollection>::Type,
                    iNumResultDimensions
                >::Type
            >
        {
        private:
            typename IteratorType<TBaseCollection>::Type _baseIterator;

            const Matrix<
                double,
                iNumResultDimensions,
                NumDimensions<TBaseCollection>::Value
            >* _transformationMatrix;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(
                const TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>& other
            ) const;

            typename TransformedType<
                typename ItemType<TBaseCollection>::Type,
                iNumResultDimensions
            >::Type
            dereference() const;
        public:
            TransformedCollectionIterator();

            TransformedCollectionIterator(
                typename IteratorType<TBaseCollection>::Type baseIterator,
                const Matrix<
                    double,
                    iNumResultDimensions,
                    NumDimensions<TBaseCollection>::Value
                >* transformationMatrix
            );
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
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
    struct BoundsType<detail::TransformedCollection<TBaseCollection, iNumResultDimensions>>
    {
        typedef typename TransformedType<
            typename BoundsType<TBaseCollection>::Type,
            iNumResultDimensions
        >::Type Type;
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

    template <class TBaseCollection, int iNumResultDimensions>
    struct ScalingFunction<detail::TransformedCollection<TBaseCollection, iNumResultDimensions>>
    {
        detail::TransformedCollection<TBaseCollection, iNumResultDimensions>
        operator()(
            const detail::TransformedCollection<
                TBaseCollection,
                iNumResultDimensions
            >& transformedCollection,
            double scale
        ) const;
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct TranslationFunction<
        detail::TransformedCollection<TBaseCollection, iNumResultDimensions>
    > : public TranslationFunction<
            SpatialCollection<
                detail::TransformedCollection<TBaseCollection, iNumResultDimensions>
            >
        >
    {
    };

    template <class TBaseCollection, int iNumInnerResultDimensions, int iNumOuterResultDimensions>
    struct TransformationFunction<
        detail::TransformedCollection<TBaseCollection, iNumInnerResultDimensions>,
        iNumOuterResultDimensions
    >
    {
        template <class TMatrix>
        detail::TransformedCollection<TBaseCollection, iNumOuterResultDimensions>
        operator()(
            const detail::TransformedCollection<
                TBaseCollection,
                iNumInnerResultDimensions
            >& transformedCollection,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <class TBaseCollection, int iNumInnerResultDimensions, int iNumOuterResultDimensions>
    struct MorphingFunction<
        detail::TransformedCollection<TBaseCollection, iNumInnerResultDimensions>,
        iNumOuterResultDimensions
    > : public MorphingFunction<
            SpatialCollection<
                detail::TransformedCollection<TBaseCollection, iNumInnerResultDimensions>
            >,
            iNumOuterResultDimensions
        >
    {
    };
}
