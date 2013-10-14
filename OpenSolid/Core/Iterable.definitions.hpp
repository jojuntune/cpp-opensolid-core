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

#include <vector>
#include <set>
#include <unordered_set>

namespace opensolid
{
    template <class TDerived>
    class Iterable
    {
    private:
        const TDerived&
        derived() const;
    public:
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

        // TODO map

        template <class TFunction>
        typename ElementType<TDerived>::Type
        reduce(TFunction function) const;

        // TOOD where

        operator std::vector<typename ElementType<TDerived>>() const;

        operator std::set<typename ElementType<TDerived>>() const;
        
        operator std::unordered_set<typename ElementType<TDerived>>() const;
    };
}
