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

#include <OpenSolid/Core/SpatialSet/SpatialSubset.definitions.hpp>

#include <OpenSolid/Core/SpatialCollection.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TItem>
        inline
        SpatialSubset<TItem>::SpatialSubset() {
        }

        template <class TItem>
        inline
        SpatialSubset<TItem>::SpatialSubset(const SpatialSubset<TItem>& other) :
            _set(other._set),
            _items(std::move(other._items)) {
        }

        template <class TItem>
        inline
        SpatialSubset<TItem>::SpatialSubset(SpatialSubset<TItem>&& other) :
            _set(std::move(other._set)),
            _items(std::move(other._items)) {
        }

        template <class TItem>
        inline
        SpatialSubset<TItem>::SpatialSubset(
            const SpatialSet<TItem>& set,
            std::vector<const TItem*>&& items
        ) : _set(set),
            _items(std::move(items)) {
        }

        template <class TItem>
        inline
        SpatialSubset<TItem>::SpatialSubset(
            SpatialSet<TItem>&& set,
            std::vector<const TItem*>&& items
        ) : _set(std::move(set)),
            _items(std::move(items)) {
        }

        template <class TItem>
        inline
        SpatialSubsetIterator<TItem>
        SpatialSubset<TItem>::begin() const {
            return SpatialSubsetIterator<TItem>(_items.begin());
        }

        template <class TItem>
        inline
        SpatialSubsetIterator<TItem>
        SpatialSubset<TItem>::end() const {
            return SpatialSubsetIterator<TItem>(_items.end());
        }

        template <class TItem>
        inline
        bool
        SpatialSubset<TItem>::isEmpty() const {
            return _items.empty();
        }

        template <class TItem>
        inline
        std::int64_t
        SpatialSubset<TItem>::size() const {
            return _items.size();
        }

        template <class TItem>
        inline
        typename BoundsType<TItem>::Type
        SpatialSubset<TItem>::bounds() const {
            return this->boundsDefaultImpl();
        }

        template <class TItem>
        inline
        void
        SpatialSubsetIterator<TItem>::increment() {
            ++_iterator;
        }

        template <class TItem>
        inline
        bool
        SpatialSubsetIterator<TItem>::equal(const SpatialSubsetIterator<TItem>& other) const {
            return _iterator == other._iterator;
        }

        template <class TItem>
        inline
        const TItem&
        SpatialSubsetIterator<TItem>::dereference() const {
            return *(*_iterator);
        }

        template <class TItem>
        inline
        SpatialSubsetIterator<TItem>::SpatialSubsetIterator() {
            // Do nothing
        }

        template <class TItem>
        inline
        SpatialSubsetIterator<TItem>::SpatialSubsetIterator(
            typename std::vector<const TItem*>::const_iterator iterator
        ) : _iterator(iterator) {
        }
    }
}
