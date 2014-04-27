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

#include <OpenSolid/Core/LazyCollection.declarations.hpp>

#include <OpenSolid/Core/LazyCollection/FilteredCollection.declarations.hpp>
#include <OpenSolid/Core/LazyCollection/IndexIterator.declarations.hpp>
#include <OpenSolid/Core/LazyCollection/MappedCollection.declarations.hpp>

#include <iterator>
#include <vector>

namespace opensolid
{   
    template <class TCollection>
    struct IteratorType
    {
        typedef detail::IndexIterator<TCollection> Type;
    };

    template <class TCollection>
    struct ItemType
    {
        typedef typename std::iterator_traits<
            typename IteratorType<TCollection>::Type
        >::value_type Type;
    };

    template <class TCollection>
    struct ItemReferenceType
    {
        typedef typename std::iterator_traits<
            typename IteratorType<TCollection>::Type
        >::reference Type;
    };

    template <class TDerived>
    class LazyCollection
    {
    protected:
        bool
        isEmptyDefaultImpl() const;

        std::size_t
        sizeDefaultImpl() const;
    public:
        const TDerived&
        derived() const;

        typename IteratorType<TDerived>::Type
        begin() const;

        typename IteratorType<TDerived>::Type
        end() const;

        bool
        isEmpty() const;

        std::size_t
        size() const;

        template <class TPredicate>
        bool
        any(TPredicate predicate) const;

        template <class TPredicate>
        bool
        all(TPredicate predicate) const;

        template <class TValue, class TFunction>
        TValue
        fold(const TValue& initialValue, TFunction function) const;

        template <class TFunction>
        void
        forEach(TFunction function) const;

        template <class TFunction>
        typename ItemType<TDerived>::Type
        reduce(TFunction function) const;

        template <class TPredicate>
        detail::FilteredCollection<TDerived, TPredicate>
        where(TPredicate predicate) const;

        template <class TMappingFunction>
        detail::MappedCollection<TDerived, TMappingFunction>
        map(TMappingFunction mappingFunction) const;

        operator std::vector<typename ItemType<TDerived>::Type>() const;
    };
}

#include <OpenSolid/Core/LazyCollection/FilteredCollection.definitions.hpp>
#include <OpenSolid/Core/LazyCollection/MappedCollection.definitions.hpp>
