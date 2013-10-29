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

#include <OpenSolid/Core/SpatialSet/SpatialSubset.declarations.hpp>

#include <OpenSolid/Core/Iterable.definitions.hpp>
#include <OpenSolid/Core/SpatialSet.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <vector>

namespace opensolid
{
    namespace detail
    {
        template <class TItem>
        class SpatialSubset :
            public Iterable<SpatialSubset<TItem>>
        {
        private:
            std::vector<const TItem*> _items;

            template <class TDerived>
            friend class Iterable;

            friend class SpatialSet<TItem>;

            SpatialSubsetIterator<TItem>
            beginImpl() const;

            SpatialSubsetIterator<TItem>
            endImpl() const;

            bool
            isEmptyImpl() const;

            std::int64_t
            sizeImpl() const;

            SpatialSubset();

            // Not implemented - copying not allowed
            SpatialSubset(const SpatialSubset<TItem>& other);

            SpatialSubset(SpatialSubset<TItem>&& other);
        public:
            SpatialSubset(std::vector<const TItem*>&& items);
        };

        template <class TItem>
        class SpatialSubsetIterator :
            public boost::iterator_facade<
                SpatialSubsetIterator<TItem>,
                const TItem,
                boost::forward_traversal_tag
            >
        {
        private:
            typename std::vector<const TItem*>::const_iterator _iterator;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(const SpatialSubsetIterator<TItem>& other) const;

            const TItem&
            dereference() const;
        public:
            SpatialSubsetIterator();

            SpatialSubsetIterator(typename std::vector<const TItem*>::const_iterator iterator);
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
    template <class TItem>
    struct ItemType<detail::SpatialSubset<TItem>>
    {
        typedef TItem Type;
    };

    template <class TItem>
    struct IteratorType<detail::SpatialSubset<TItem>>
    {
        typedef detail::SpatialSubsetIterator<TItem> Type;
    };
}
