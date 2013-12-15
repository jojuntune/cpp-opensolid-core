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

#include <OpenSolid/Core/SpatialCollection/FilteredCollection.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    template <class TBaseCollection, class TPredicate>
    struct BoundsType<detail::FilteredCollection<TBaseCollection, TPredicate>>
    {
        typedef typename BoundsType<TBaseCollection>::Type Type;
    };

    template <class TBaseCollection, class TPredicate>
    struct NumDimensions<detail::FilteredCollection<TBaseCollection, TPredicate>>
    {
        static const int Value = NumDimensions<TBaseCollection>::Value;
    };

    template <class TBaseCollection, class TPredicate>
    struct ScaledType<detail::FilteredCollection<TBaseCollection, TPredicate>> :
        public ScaledType<
            SpatialCollection<detail::FilteredCollection<TBaseCollection, TPredicate>>
        >
    {
    };

    template <class TBaseCollection, class TPredicate>
    struct TranslatedType<detail::FilteredCollection<TBaseCollection, TPredicate>> :
        public TranslatedType<
            SpatialCollection<detail::FilteredCollection<TBaseCollection, TPredicate>>
        >
    {
    };

    template <class TBaseCollection, class TPredicate, int iNumResultDimensions>
    struct TransformedType<
        detail::FilteredCollection<TBaseCollection, TPredicate>,
        iNumResultDimensions
    > : public TransformedType<
            SpatialCollection<detail::FilteredCollection<TBaseCollection, TPredicate>>,
            iNumResultDimensions
        >
    {
    };


    template <class TBaseCollection, class TPredicate, int iNumResultDimensions>
    struct MorphedType<
        detail::FilteredCollection<TBaseCollection, TPredicate>,
        iNumResultDimensions
    > : public MorphedType<
            SpatialCollection<detail::FilteredCollection<TBaseCollection, TPredicate>>,
            iNumResultDimensions
        >
    {
    };

    template <class TBaseCollection, class TPredicate>
    struct IteratorType<detail::FilteredCollection<TBaseCollection, TPredicate>>
    {
        typedef detail::FilteredCollectionIterator<TBaseCollection, TPredicate> Type;
    };

    namespace detail
    {
        template <class TBaseCollection, class TPredicate>
        class FilteredCollection :
            public SpatialCollection<FilteredCollection<TBaseCollection, TPredicate>>
        {
        private:
            TBaseCollection _baseCollection;
            TPredicate _predicate;
        public:
            FilteredCollection(const FilteredCollection<TBaseCollection, TPredicate>& other);

            FilteredCollection(FilteredCollection<TBaseCollection, TPredicate>&& other);

            FilteredCollection(const TBaseCollection& baseCollection, TPredicate predicate);

            FilteredCollection(TBaseCollection&& baseCollection, TPredicate predicate);

            FilteredCollectionIterator<TBaseCollection, TPredicate>
            begin() const;

            FilteredCollectionIterator<TBaseCollection, TPredicate>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            typename BoundsType<typename ItemType<TBaseCollection>::Type>::Type
            bounds() const;
        };

        template <class TBaseCollection, class TPredicate>
        class FilteredCollectionIterator :
            public boost::iterator_facade<
                FilteredCollectionIterator<TBaseCollection, TPredicate>,
                typename ItemType<TBaseCollection>::Type,
                boost::forward_traversal_tag,
                typename ItemReferenceType<TBaseCollection>::Type
            >
        {
        private:
            typename IteratorType<TBaseCollection>::Type _baseIterator;
            typename IteratorType<TBaseCollection>::Type _baseEnd;
            const TPredicate* _predicatePtr;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(const FilteredCollectionIterator<TBaseCollection, TPredicate>& other) const;

            typename ItemReferenceType<TBaseCollection>::Type
            dereference() const;
        public:
            FilteredCollectionIterator();

            FilteredCollectionIterator(
                typename IteratorType<TBaseCollection>::Type baseIterator,
                typename IteratorType<TBaseCollection>::Type baseEnd,
                const TPredicate* predicatePtr
            );
        };
    }

    template <class TBaseCollection, class TPredicate>
    struct ScalingFunction<detail::FilteredCollection<TBaseCollection, TPredicate>> :
        public ScalingFunction<
            SpatialCollection<detail::FilteredCollection<TBaseCollection, TPredicate>>
        >
    {
    };

    template <class TBaseCollection, class TPredicate>
    struct TranslationFunction<detail::FilteredCollection<TBaseCollection, TPredicate>> :
        public TranslationFunction<
            SpatialCollection<detail::FilteredCollection<TBaseCollection, TPredicate>>
        >
    {
    };

    template <class TBaseCollection, class TPredicate, int iNumResultDimensions>
    struct TransformationFunction<
        detail::FilteredCollection<TBaseCollection, TPredicate>,
        iNumResultDimensions
    > : public TransformationFunction<
            SpatialCollection<detail::FilteredCollection<TBaseCollection, TPredicate>>,
            iNumResultDimensions
        >
    {
    };

    template <class TBaseCollection, class TPredicate, int iNumResultDimensions>
    struct MorphingFunction<
        detail::FilteredCollection<TBaseCollection, TPredicate>,
        iNumResultDimensions
    > : public MorphingFunction<
            SpatialCollection<detail::FilteredCollection<TBaseCollection, TPredicate>>,
            iNumResultDimensions
        >
    {
    };
}
