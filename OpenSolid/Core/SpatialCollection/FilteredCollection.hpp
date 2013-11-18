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
        FilteredCollection<TBaseCollection, TPredicate>::FilteredCollection(
            const FilteredCollection<TBaseCollection, TPredicate>& other
        ) : _baseCollection(other._baseCollection),
            _predicate(other._predicate) {
        }

        template <class TBaseCollection, class TPredicate>
        inline
        FilteredCollection<TBaseCollection, TPredicate>::FilteredCollection(
            FilteredCollection<TBaseCollection, TPredicate>&& other
        ) : _baseCollection(std::move(other._baseCollection)),
            _predicate(other._predicate) {
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
        FilteredCollection<TBaseCollection, TPredicate>::FilteredCollection(
            TBaseCollection&& baseCollection,
            TPredicate predicate
        ) : _baseCollection(std::move(baseCollection)),
            _predicate(predicate) {
        }

        template <class TBaseCollection, class TPredicate>
        inline
        FilteredCollectionIterator<TBaseCollection, TPredicate>
        FilteredCollection<TBaseCollection, TPredicate>::begin() const {
            return FilteredCollectionIterator<TBaseCollection, TPredicate>(
                _baseCollection.begin(),
                _baseCollection.end(),
                &_predicate
            );
        }

        template <class TBaseCollection, class TPredicate>
        inline
        FilteredCollectionIterator<TBaseCollection, TPredicate>
        FilteredCollection<TBaseCollection, TPredicate>::end() const {
            return FilteredCollectionIterator<TBaseCollection, TPredicate>(
                _baseCollection.end(),
                _baseCollection.end(),
                &_predicate
            );
        }

        template <class TBaseCollection, class TPredicate>
        inline
        bool
        FilteredCollection<TBaseCollection, TPredicate>::isEmpty() const {
            return this->isEmptyDefaultImpl();
        }

        template <class TBaseCollection, class TPredicate>
        inline
        std::int64_t
        FilteredCollection<TBaseCollection, TPredicate>::size() const {
            return this->sizeDefaultImpl();
        }

        template <class TBaseCollection, class TPredicate>
        inline
        typename BoundsType<typename ItemType<TBaseCollection>::Type>::Type
        FilteredCollection<TBaseCollection, TPredicate>::bounds() const {
            return this->boundsDefaultImpl();
        }

        template <class TBaseCollection, class TPredicate>
        inline
        void
        FilteredCollectionIterator<TBaseCollection, TPredicate>::increment() {
            do {
                ++_baseIterator;
            } while (_baseIterator != _baseEnd && !(*_predicatePtr)(*_baseIterator));
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
            _predicatePtr(nullptr) {
        }

        template <class TBaseCollection, class TPredicate>
        inline
        FilteredCollectionIterator<TBaseCollection, TPredicate>::FilteredCollectionIterator(
            typename IteratorType<TBaseCollection>::Type baseIterator,
            typename IteratorType<TBaseCollection>::Type baseEnd,
            const TPredicate* predicatePtr
        ) : _baseIterator(baseIterator),
            _baseEnd(baseEnd),
            _predicatePtr(predicatePtr) {

            while (_baseIterator != _baseEnd && !(*_predicatePtr)(*_baseIterator)) {
                ++_baseIterator;
            }
        }
    }
}
