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

#include <OpenSolid/Core/Iterable/FilteredIterable.declarations.hpp>

#include <OpenSolid/Core/Iterable.definitions.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseIterable, class TPredicate>
        class FilteredIterable :
            public Iterable<FilteredIterable<TBaseIterable, TPredicate>>
        {
        private:
            const TBaseIterable& _baseIterable;
            TPredicate _predicate;

            template <class TDerived>
            friend class opensolid::Iterable;

            FilteredIterableIterator<TBaseIterable, TPredicate>
            beginImpl() const;

            FilteredIterableIterator<TBaseIterable, TPredicate>
            endImpl() const;

            bool
            isEmptyImpl() const;

            std::int64_t
            sizeImpl() const;

            FilteredIterable(const FilteredIterable<TBaseIterable, TPredicate>& other);
        public:
            FilteredIterable(const TBaseIterable& baseIterable, TPredicate predicate);
        };

        template <class TBaseIterable, class TPredicate>
        class FilteredIterableIterator :
            public boost::iterator_facade<
                FilteredIterableIterator<TBaseIterable, TPredicate>,
                const typename ItemType<TBaseIterable>::Type,
                boost::forward_traversal_tag
            >
        {
        private:
            typename IteratorType<TBaseIterable>::Type _baseIterator;
            typename IteratorType<TBaseIterable>::Type _baseEnd;
            const TPredicate* _predicate;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(const FilteredIterableIterator<TBaseIterable, TPredicate>& other) const;

            const typename ItemType<TBaseIterable>::Type&
            dereference() const;
        public:
            FilteredIterableIterator();

            FilteredIterableIterator(
                typename IteratorType<TBaseIterable>::Type baseIterator,
                typename IteratorType<TBaseIterable>::Type baseEnd,
                const TPredicate* predicate
            );
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
    template <class TBaseIterable, class TPredicate>
    struct ItemType<detail::FilteredIterable<TBaseIterable, TPredicate>>
    {
        typedef typename ItemType<TBaseIterable>::Type Type;
    };

    template <class TBaseIterable, class TPredicate>
    struct IteratorType<detail::FilteredIterable<TBaseIterable, TPredicate>>
    {
        typedef detail::FilteredIterableIterator<TBaseIterable, TPredicate> Type;
    };
}
