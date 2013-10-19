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

#include <OpenSolid/Core/Iterable.declarations.hpp>

#include <OpenSolid/Core/Iterable/FilteredIterable.declarations.hpp>

#include <vector>

namespace opensolid
{
    template <class TDerived>
    class Iterable
    {
    private:
        const TDerived&
        derived() const;
    protected:
        template <class TBaseIterable, class TPredicate>
        friend class iterable::FilteredIterable;

        typename IteratorType<TDerived>::Type
        begin() const;

        typename IteratorType<TDerived>::Type
        end() const;
    public:
        bool
        isEmpty() const;

        std::int64_t
        size() const;

        template <class TPredicate>
        bool
        any(TPredicate predicate) const;

        template <class TPredicate>
        bool
        every(TPredicate predicate) const;

        template <class TValue, class TFunction>
        TValue
        fold(const TValue& initialValue, TFunction function) const;

        template <class TFunction>
        void
        forEach(TFunction function) const;

        template <class TFunction>
        typename ElementType<TDerived>::Type
        reduce(TFunction function) const;

        template <class TPredicate>
        iterable::FilteredIterable<TDerived, TPredicate>
        where(TPredicate predicate) const;

        operator std::vector<typename ElementType<TDerived>::Type>() const;
    };
}
