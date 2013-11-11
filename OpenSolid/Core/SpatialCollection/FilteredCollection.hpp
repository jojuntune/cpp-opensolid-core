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

#include <OpenSolid/Core/SpatialCollection/FilteredCollection.definitions.hpp>

#include <OpenSolid/Core/SpatialCollection.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection, class TPredicate>
        inline
        FilteredCollectionIterator<TBaseCollection, TPredicate>
        FilteredCollection<TBaseCollection, TPredicate>::beginImpl() const {
            return FilteredCollectionIterator<TBaseCollection, TPredicate>(
                detail::begin(_baseCollection),
                detail::end(_baseCollection),
                &_predicate
            );
        }

        template <class TBaseCollection, class TPredicate>
        inline
        FilteredCollectionIterator<TBaseCollection, TPredicate>
        FilteredCollection<TBaseCollection, TPredicate>::endImpl() const {
            return FilteredCollectionIterator<TBaseCollection, TPredicate>(
                detail::end(_baseCollection),
                detail::end(_baseCollection),
                &_predicate
            );
        }

        template <class TBaseCollection, class TPredicate>
        inline
        bool
        FilteredCollection<TBaseCollection, TPredicate>::isEmptyImpl() const {
            return this->isEmptyDefaultImpl();
        }

        template <class TBaseCollection, class TPredicate>
        inline
        std::int64_t
        FilteredCollection<TBaseCollection, TPredicate>::sizeImpl() const {
            return this->sizeDefaultImpl();
        }

        template <class TBaseCollection, class TPredicate>
        inline
        typename BoundsType<typename ItemType<TBaseCollection>::Type>::Type
        FilteredCollection<TBaseCollection, TPredicate>::boundsImpl() const {
            return this->boundsDefaultImpl();
        }

        template <class TBaseCollection, class TPredicate>
        inline
        FilteredCollection<TBaseCollection, TPredicate>::FilteredCollection(
            const TBaseCollection& baseCollection,
            TPredicate predicate
        ) : _baseCollection(baseCollection),
            _predicate(predicate) {
        }

        template <class TBaseCollection, class TPredicate>
        inline
        void
        FilteredCollectionIterator<TBaseCollection, TPredicate>::increment() {
            do {
                ++_baseIterator;
            } while (_baseIterator != _baseEnd && !(*_predicate)(*_baseIterator));
        }

        template <class TBaseCollection, class TPredicate>
        inline
        bool
        FilteredCollectionIterator<TBaseCollection, TPredicate>::equal(
            const FilteredCollectionIterator<TBaseCollection,
            TPredicate>& other
        ) const {
            return _baseIterator == other._baseIterator;
        }

        template <class TBaseCollection, class TPredicate>
        inline
        const typename ItemType<TBaseCollection>::Type&
        FilteredCollectionIterator<TBaseCollection, TPredicate>::dereference() const {
            return *_baseIterator;
        }

        template <class TBaseCollection, class TPredicate>
        inline
        FilteredCollectionIterator<TBaseCollection, TPredicate>::FilteredCollectionIterator() :
            _predicate(nullptr) {
        }

        template <class TBaseCollection, class TPredicate>
        inline
        FilteredCollectionIterator<TBaseCollection, TPredicate>::FilteredCollectionIterator(
            typename IteratorType<TBaseCollection>::Type baseIterator,
            typename IteratorType<TBaseCollection>::Type baseEnd,
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
