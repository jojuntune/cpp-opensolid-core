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

#include <OpenSolid/Core/Iterable/FilteredIterable.definitions.hpp>

#include <OpenSolid/Core/Iterable.hpp>

namespace opensolid
{
    namespace iterable
    {
        template <class TBaseIterable, class TPredicate>
        inline
        FilteredIterable<TBaseIterable, TPredicate>::FilteredIterable(
            const TBaseIterable& baseIterable,
            TPredicate predicate
        ) : _baseIterable(baseIterable),
            _predicate(predicate) {
        }

        template <class TBaseIterable, class TPredicate>
        inline
        FilteredIterable<TBaseIterable, TPredicate>::FilteredIterable(
            TBaseIterable&& baseIterable,
            TPredicate predicate
        ) : _baseIterable(std::move(baseIterable)),
            _predicate(predicate) {
        }

        template <class TBaseIterable, class TPredicate>
        inline
        FilteredIterableIterator<TBaseIterable, TPredicate>
        FilteredIterable<TBaseIterable, TPredicate>::begin() const {
            return FilteredIterableIterator<TBaseIterable, TPredicate>(
                _baseIterable.begin(),
                _baseIterable.end(),
                &_predicate
            );
        }

        template <class TBaseIterable, class TPredicate>
        inline
        FilteredIterableIterator<TBaseIterable, TPredicate>
        FilteredIterable<TBaseIterable, TPredicate>::end() const {
            return FilteredIterableIterator<TBaseIterable, TPredicate>(
                _baseIterable.end(),
                _baseIterable.end(),
                &_predicate
            );
        }

        template <class TBaseIterable, class TPredicate>
        inline
        bool
        FilteredIterable<TBaseIterable, TPredicate>::empty() const {
            return begin() == end();
        }

        template <class TBaseIterable, class TPredicate>
        inline
        std::int64_t
        FilteredIterable<TBaseIterable, TPredicate>::size() const {
            return std::distance(begin(), end());
        }

        template <class TBaseIterable, class TPredicate>
        inline
        void
        FilteredIterableIterator<TBaseIterable, TPredicate>::increment() {
            do {
                ++_baseIterator;
            } while (_baseIterator != _baseEnd && !(*_predicate)(*_baseIterator));
        }

        template <class TBaseIterable, class TPredicate>
        inline
        bool
        FilteredIterableIterator<TBaseIterable, TPredicate>::equal(
            const FilteredIterableIterator<TBaseIterable,
            TPredicate>& other
        ) const {
            return _baseIterator == other._baseIterator;
        }

        template <class TBaseIterable, class TPredicate>
        inline
        const typename ElementType<TBaseIterable>::Type&
        FilteredIterableIterator<TBaseIterable, TPredicate>::dereference() const {
            return *_baseIterator;
        }

        template <class TBaseIterable, class TPredicate>
        inline
        FilteredIterableIterator<TBaseIterable, TPredicate>::FilteredIterableIterator() :
            _predicate(nullptr) {
        }

        template <class TBaseIterable, class TPredicate>
        inline
        FilteredIterableIterator<TBaseIterable, TPredicate>::FilteredIterableIterator(
            typename IteratorType<TBaseIterable>::Type baseIterator,
            typename IteratorType<TBaseIterable>::Type baseEnd,
            const TPredicate* predicate
        ) : _baseIterator(baseIterator),
            _baseEnd(baseEnd),
            _predicate(predicate) {

            while (_baseIterator != _baseEnd && !(*_predicate)(*_baseIterator)) {
                ++_baseIterator;
            }
        }
    }
}
