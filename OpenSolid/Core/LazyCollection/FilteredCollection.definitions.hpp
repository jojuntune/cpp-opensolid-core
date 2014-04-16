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

#include <OpenSolid/Core/LazyCollection/FilteredCollection.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/LazyCollection.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    template <class TBaseCollection, class TPredicate>
    struct IteratorType<detail::FilteredCollection<TBaseCollection, TPredicate>>
    {
        typedef detail::FilteredCollectionIterator<TBaseCollection, TPredicate> Type;
    };

    namespace detail
    {
        template <class TBaseCollection, class TPredicate>
        class FilteredCollection :
            public LazyCollection<FilteredCollection<TBaseCollection, TPredicate>>
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
}
