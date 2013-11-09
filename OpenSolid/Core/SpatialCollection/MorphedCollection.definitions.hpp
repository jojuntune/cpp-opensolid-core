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

#include <OpenSolid/Core/SpatialCollection/MorphedCollection.declarations.hpp>

#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection, int iNumResultDimensions>
        class MorphedCollection :
            public SpatialCollection<MorphedCollection<TBaseCollection, iNumResultDimensions>>
        {
        private:
            typename NestedType<TBaseCollection>::Type _baseCollection;
            Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value> _function;

            template <class TDerived>
            friend class opensolid::SpatialCollection;

            MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>
            beginImpl() const;

            MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>
            endImpl() const;

            bool
            isEmptyImpl() const;

            std::int64_t
            sizeImpl() const;

            typename MorphedType<
                typename BoundsType<TBaseCollection>::Type,
                iNumResultDimensions
            >::Type
            boundsImpl() const;
        public:
            MorphedCollection(
                const TBaseCollection& baseCollection,
                const Function<
                    iNumResultDimensions,
                    NumDimensions<TBaseCollection>::Value
                >& function
            );

            const TBaseCollection&
            baseCollection() const;

            const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>&
            function() const;
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
            const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>* _function;

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
                const Function<
                    iNumResultDimensions,
                    NumDimensions<TBaseCollection>::Value
                >* function
            );
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
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
            const Function<iNumOuterResultDimensions, iNumInnerResultDimensions>& function
        ) const;
    };
}
