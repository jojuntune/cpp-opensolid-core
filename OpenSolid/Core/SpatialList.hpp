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

#include <OpenSolid/Core/SpatialList.definitions.hpp>

#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/SpatialCollection.hpp>
#include <OpenSolid/Core/SpatialList/SpatialListData.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <class TItem>
    inline
    SpatialList<TItem>::SpatialList() {
    }

    template <class TItem>
    inline
    SpatialList<TItem>::SpatialList(const SpatialList<TItem>& other) :
        _dataPtr(other._dataPtr) {
    }

    template <class TItem>
    inline
    SpatialList<TItem>::SpatialList(SpatialList<TItem>&& other) :
        _dataPtr(std::move(other._dataPtr)) {
    }

    template <class TItem>
    inline
    SpatialList<TItem>::SpatialList(const std::vector<TItem>& items) :
        _dataPtr(new detail::SpatialListData<TItem>()) {

        _dataPtr->items = items;
    }

    template <class TItem>
    inline
    SpatialList<TItem>::SpatialList(std::vector<TItem>&& items) :
        _dataPtr(new detail::SpatialListData<TItem>()) {

        _dataPtr->items = std::move(items);
    }

    template <class TItem> template <class TDerived>
    inline
    SpatialList<TItem>::SpatialList(const SpatialCollection<TDerived>& collection) :
        _dataPtr(new detail::SpatialListData<TItem>()) {

        _dataPtr->items = std::vector<TItem>(collection.begin(), collection.end());
    }

    template <class TItem> template <class TIterator>
    inline
    SpatialList<TItem>::SpatialList(TIterator begin, TIterator end) :
        _dataPtr(new detail::SpatialListData<TItem>()) {

        _dataPtr->items = std::vector<TItem>(begin, end);
    }
    
    template <class TItem>
    inline
    void
    SpatialList<TItem>::operator=(const SpatialList<TItem>& other) {
        _dataPtr = other._dataPtr;
    }
    
    template <class TItem>
    inline
    void
    SpatialList<TItem>::operator=(SpatialList<TItem>&& other) {
        _dataPtr = std::move(other._dataPtr);
    }

    template <class TItem>
    inline
    typename std::vector<TItem>::const_iterator
    SpatialList<TItem>::begin() const {
        if (isEmpty()) {
            return typename std::vector<TItem>::const_iterator();
        } else {
            return _dataPtr->items.begin();
        }
    }

    template <class TItem>
    inline
    typename std::vector<TItem>::const_iterator
    SpatialList<TItem>::end() const {
        if (isEmpty()) {
            return typename std::vector<TItem>::const_iterator();
        } else {
            return _dataPtr->items.end();
        }
    }

    template <class TItem>
    inline
    bool
    SpatialList<TItem>::isEmpty() const {
        return !_dataPtr || _dataPtr->items.empty();
    }
    
    template <class TItem>
    inline
    std::int64_t
    SpatialList<TItem>::size() const {
        if (isEmpty()) {
            return 0;
        } else {
            return _dataPtr->items.size();
        }
    }

    template <class TItem>
    inline
    typename BoundsType<TItem>::Type
    SpatialList<TItem>::bounds() const {
        return this->boundsDefaultImpl();
    }

    template <class TItem>
    inline
    const TItem&
    SpatialList<TItem>::operator[](std::int64_t index) const {
        assert(!isEmpty());
        return _dataPtr->items[index];
    }

    template <class TItem>
    inline
    void
    SpatialList<TItem>::swap(SpatialList<TItem>& other) {
        _dataPtr.swap(other._dataPtr);
    }

    template <class TItem>
    inline
    void
    SpatialList<TItem>::clear() {
        _dataPtr.reset();
    }
}
