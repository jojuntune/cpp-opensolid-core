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

#include <OpenSolid/Core/SpatialCollection/IndexIterator.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TCollection>
        inline
        void
        IndexIterator<TCollection>::increment() {
            ++_index;
        }

        template <class TCollection>
        inline
        void
        IndexIterator<TCollection>::decrement() {
            --_index;
        }

        template <class TCollection>
        inline
        void
        IndexIterator<TCollection>::advance(std::int64_t distance) {
            _index += distance;
        }

        template <class TCollection>
        inline
        std::int64_t
        IndexIterator<TCollection>::distance_to(const IndexIterator<TCollection>& other) const {
            assert(_collection == other._collection);
            return other._index - _index;
        }

        template <class TCollection>
        inline
        bool
        IndexIterator<TCollection>::equal(const IndexIterator<TCollection>& other) const {
            assert(_collection == other._collection);
            return _index == other._index;
        }

        template <class TCollection>
        inline
        typename ItemReferenceType<TCollection>::Type
        IndexIterator<TCollection>::dereference() const {
            return (*_collection)[_index];
        }

        template <class TCollection>
        inline
        IndexIterator<TCollection>::IndexIterator(
            const TCollection* collection,
            std::int64_t index
        ) : _collection(collection),
            _index(index) {
        }

        template <class TCollection>
        inline
        IndexIterator<TCollection>
        IndexIterator<TCollection>::Begin(const TCollection* collection) {
            return IndexIterator<TCollection>(collection, 0);
        }

        template <class TCollection>
        inline
        IndexIterator<TCollection>
        IndexIterator<TCollection>::End(const TCollection* collection) {
            return IndexIterator<TCollection>(collection, collection->size());
        }
    }
}
