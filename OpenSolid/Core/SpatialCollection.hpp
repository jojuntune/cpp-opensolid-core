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

#include <OpenSolid/Core/SpatialCollection.definitions.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/SpatialCollection/FilteredCollection.hpp>

#include <algorithm>
#include <numeric>

namespace opensolid
{
    template <class TDerived>
    inline
    const TDerived&
    SpatialCollection<TDerived>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline
    typename IteratorType<TDerived>::Type
    SpatialCollection<TDerived>::begin() const {
        return derived().beginImpl();
    }

    template <class TDerived>
    inline
    typename IteratorType<TDerived>::Type
    SpatialCollection<TDerived>::end() const {
        return derived().endImpl();
    }

    template <class TDerived>
    inline
    bool
    SpatialCollection<TDerived>::isEmptyDefaultImpl() const {
        return begin() == end();
    }

    template <class TDerived>
    inline
    std::int64_t
    SpatialCollection<TDerived>::sizeDefaultImpl() const {
        return std::distance(begin(), end());
    }

    template <class TDerived>
    inline
    typename BoundsType<typename ItemType<TDerived>::Type>::Type
    SpatialCollection<TDerived>::boundsDefaultImpl() const {
        typedef typename ItemType<TDerived>::Type ItemType;
        typedef typename BoundsType<ItemType>::Type BoundsType;

        typename IteratorType<TDerived>::Type iterator = this->begin();
        typename IteratorType<TDerived>::Type end = this->end();
        
        if (iterator == end) {
            return BoundsType();
        } else {
            BoundsFunction<ItemType> boundsFunction;
            BoundsType result = boundsFunction(*iterator);
            while (++iterator != end) {
                result = result.hull(*iterator);
            }
            return result;
        }
    }

    template <class TDerived>
    inline
    bool
    SpatialCollection<TDerived>::isEmpty() const {
        return derived().isEmptyImpl();
    }

    template <class TDerived>
    inline
    std::int64_t
    SpatialCollection<TDerived>::size() const {
        return derived().sizeImpl();
    }

    template <class TDerived>
    inline
    typename BoundsType<typename ItemType<TDerived>::Type>::Type
    SpatialCollection<TDerived>::bounds() const {
        return derived().boundsImpl();
    }

    template <class TDerived> template <class TPredicate>
    inline
    bool
    SpatialCollection<TDerived>::any(TPredicate predicate) const {
        return std::any_of(begin(), end(), predicate);
    }

    template <class TDerived> template <class TPredicate>
    inline
    bool
    SpatialCollection<TDerived>::all(TPredicate predicate) const {
        return std::all_of(begin(), end(), predicate);
    }

    template <class TDerived> template <class TValue, class TFunction>
    inline
    TValue
    SpatialCollection<TDerived>::fold(const TValue& initialValue, TFunction function) const {
        return std::accumulate(begin(), end(), initialValue, function);
    }

    template <class TDerived> template <class TFunction>
    inline
    void
    SpatialCollection<TDerived>::forEach(TFunction function) const {
        std::for_each(begin(), end(), function);
    }

    template <class TDerived> template <class TFunction>
    inline
    typename ItemType<TDerived>::Type
    SpatialCollection<TDerived>::reduce(TFunction function) const {
        typename IteratorType<TDerived>::Type begin = this->begin();
        typename IteratorType<TDerived>::Type end = this->end();

        if (begin == end) {
            throw PlaceholderError();
        } else {
            const typename ItemType<TDerived>::Type& firstItem = *begin;
            return std::accumulate(++begin, end, firstItem, function);
        }
    }

    template <class TDerived> template <class TPredicate>
    inline
    detail::FilteredCollection<TDerived, TPredicate>
    SpatialCollection<TDerived>::where(TPredicate predicate) const {
        return detail::FilteredCollection<TDerived, TPredicate>(derived(), predicate);
    }

    template <class TDerived>
    inline
    SpatialCollection<TDerived>::operator std::vector<typename ItemType<TDerived>::Type>() const {
        return std::vector<typename ItemType<TDerived>::Type>(begin(), end());
    }
}
