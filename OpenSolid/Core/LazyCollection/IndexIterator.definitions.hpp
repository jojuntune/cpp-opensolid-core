/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#include <OpenSolid/Core/LazyCollection/IndexIterator.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TCollection>
        class IndexIterator:
            public boost::iterator_facade<
                IndexIterator<TCollection>,
                typename ItemType<TCollection>::Type,
                boost::random_access_traversal_tag,
                typename ItemReferenceType<TCollection>::Type
            >
        {
        private:
            const TCollection* _collection;
            std::size_t _index;

            friend class boost::iterator_core_access;

            void
            increment();

            void
            decrement();

            void
            advance(std::ptrdiff_t distance);

            std::ptrdiff_t
            distance_to(const IndexIterator<TCollection>& other) const;

            bool
            equal(const IndexIterator<TCollection>& other) const;

            typename ItemReferenceType<TCollection>::Type
            dereference() const;

            IndexIterator(const TCollection* collection, std::size_t index);
        public:
            static
            IndexIterator
            begin(const TCollection* collection);

            static
            IndexIterator
            end(const TCollection* collection);
        };
    }
}
