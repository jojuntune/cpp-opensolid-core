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

#include <OpenSolid/Core/Iterable.definitions.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Iterable/FilteredIterable.hpp>

#include <algorithm>
#include <numeric>

namespace opensolid
{
    template <class TDerived>
    inline
    const TDerived&
    Iterable<TDerived>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline
    typename IteratorType<TDerived>::Type
    Iterable<TDerived>::begin() const {
        return derived().beginImpl();
    }

    template <class TDerived>
    inline
    typename IteratorType<TDerived>::Type
    Iterable<TDerived>::end() const {
        return derived().endImpl();
    }

    template <class TDerived>
    inline
    bool
    Iterable<TDerived>::isEmpty() const {
        return derived().isEmptyImpl();
    }

    template <class TDerived>
    inline
    std::int64_t
    Iterable<TDerived>::size() const {
        return derived().sizeImpl();
    }

    template <class TDerived> template <class TPredicate>
    inline
    bool
    Iterable<TDerived>::any(TPredicate predicate) const {
        return std::any_of(begin(), end(), predicate);
    }

    template <class TDerived> template <class TPredicate>
    inline
    bool
    Iterable<TDerived>::every(TPredicate predicate) const {
        return std::all_of(begin(), end(), predicate);
    }

    template <class TDerived> template <class TValue, class TFunction>
    inline
    TValue
    Iterable<TDerived>::fold(const TValue& initialValue, TFunction function) const {
        return std::accumulate(begin(), end(), initialValue, function);
    }

    template <class TDerived> template <class TFunction>
    inline
    void
    Iterable<TDerived>::forEach(TFunction function) const {
        std::for_each(begin(), end(), function);
    }

    template <class TDerived> template <class TFunction>
    inline
    typename ElementType<TDerived>::Type
    Iterable<TDerived>::reduce(TFunction function) const {
        if (isEmpty()) {
            throw PlaceholderError();
        } else {
            typename IteratorType<TDerived>::Type begin = this->begin();
            const typename ElementType<TDerived>::Type& firstElement = *begin;
            return std::accumulate(++begin, end(), firstElement, function);
        }
    }

    template <class TDerived> template <class TPredicate>
    inline
    detail::FilteredIterable<TDerived, TPredicate>
    Iterable<TDerived>::where(TPredicate predicate) const {
        return detail::FilteredIterable<TDerived, TPredicate>(derived(), predicate);
    }

    template <class TDerived>
    inline
    Iterable<TDerived>::operator std::vector<typename ElementType<TDerived>::Type>() const {
        return std::vector<typename ElementType<TDerived>::Type>(begin(), end());
    }
}
