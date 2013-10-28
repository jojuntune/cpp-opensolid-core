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

#include <OpenSolid/Core/Iterable.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TElement>
        inline
        SpatialSubsetIterator<TElement>
        SpatialSubset<TElement>::beginImpl() const {
            return SpatialSubsetIterator<TElement>(_elementPositions.begin());
        }

        template <class TElement>
        inline
        SpatialSubsetIterator<TElement>
        SpatialSubset<TElement>::endImpl() const {
            return SpatialSubsetIterator<TElement>(_elementPositions.end());
        }

        template <class TElement>
        inline
        bool
        SpatialSubset<TElement>::isEmptyImpl() const {
            return _elementPositions.empty();
        }

        template <class TElement>
        inline
        std::int64_t
        SpatialSubset<TElement>::sizeImpl() const {
            return _elementPositions.size();
        }

        template <class TElement>
        inline
        SpatialSubset<TElement>::SpatialSubset() {
            // Do nothing
        }

        template <class TElement>
        inline
        SpatialSubset<TElement>::SpatialSubset(SpatialSubset<TElement>&& other) :
            _elementPositions(std::move(other._elementPositions)) {
        }

        template <class TElement>
        inline
        SpatialSubset<TElement>::SpatialSubset(
            std::vector<std::vector<TElement>::const_iterator>&& elementPositions
        ) : _elementPositions(std::move(elementPositions)) {
        }

        template <class TElement>
        inline
        void
        SpatialSubsetIterator<TElement>::increment() {
            ++_iterator;
        }

        template <class TElement>
        inline
        bool
        SpatialSubsetIterator<TElement>::equal(const SpatialSubsetIterator<TElement>& other) const {
            return _iterator == other._iterator;
        }

        template <class TElement>
        inline
        const TElement&
        SpatialSubsetIterator<TElement>::dereference() const {
            return *(*_iterator);
        }

        template <class TElement>
        inline
        SpatialSubsetIterator<TElement>::SpatialSubsetIterator() {
            // Do nothing
        }

        template <class TElement>
        inline
        SpatialSubsetIterator<TElement>::SpatialSubsetIterator(
            std::vector<std::vector<TElement>::const_iterator>::const_iterator iterator
        ) : _iterator(iterator) {
        }
    }
}
