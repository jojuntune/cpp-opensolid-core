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

#include <OpenSolid/Core/Iterable/FilteredIterabled.declarations.hpp>

#include <OpenSolid/Core/Iterable.definitions.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    template <class TIterable, class TPredicate>
    class FilteredIterable :
        public Iterable<FilteredIterable<TIterable, TPredicate>>
    {
    private:
        TIterable _baseIterable;
        TPredicate _predicate;
    public:
        typedef FilteredIterableIterator<TIterable, TPredicate> Iterator;

        FilteredIterable(const TIterable& baseIterable, const TPredicate& predicate);

        FilteredIterableIterator
        begin() const;

        FilteredIterableIterator
        end() const;

        bool
        empty() const;

        std::int64_t
        size() const;
    };

    template <class TIterable, class TPredicate>
    class FilteredIterableIterator :
        public boost::iterator_facade<
            FilteredSetIterator<TElement, TBoundsPredicate>,
            const TElement,
            boost::forward_traversal_tag
        >
    {
    private:
        const TIterable* _baseIterable;
        const TPredicate* _predicate;
    public:
        FilteredIterableIterator(const TIterable* baseIterable, const TPredicate* predicate);
    };
}
