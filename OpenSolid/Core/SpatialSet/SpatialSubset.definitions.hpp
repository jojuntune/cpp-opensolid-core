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
        template <class TElement>
        class SpatialSubset :
            public Iterable<SpatialSubset<TElement>>
        {
        private:
            std::vector<std::vector<TElement>::const_iterator> _elementPositions;

            template <class TDerived>
            friend class Iterable;

            friend class SpatialSet<TElement>;

            SpatialSubsetIterator<TElement>
            beginImpl() const;

            SpatialSubsetIterator<TElement>
            endImpl() const;

            bool
            isEmptyImpl() const;

            std::int64_t
            sizeImpl() const;

            SpatialSubset();

            // Not implemented - copying not allowed
            SpatialSubset(const SpatialSubset<TElement>& other);

            SpatialSubset(SpatialSubset<TElement>&& other);
        public:
            SpatialSubset(std::vector<std::vector<TElement>::const_iterator>&& elementPositions);
        };

        template <class TElement>
        class SpatialSubsetIterator :
            public boost::iterator_facade<
                SpatialSubsetIterator<TElement>,
                const TElement,
                boost::forward_traversal_tag
            >
        {
        private:
            std::vector<std::vector<TElement>::const_iterator>::const_iterator _iterator;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(const SpatialSubsetIterator<TElement>& other) const;

            const TElement&
            dereference() const;
        public:
            SpatialSubsetIterator();

            SpatialSubsetIterator(
                std::vector<std::vector<TElement>::const_iterator>::const_iterator iterator
            );
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
    template <class TElement>
    struct ElementType<detail::SpatialSubset<TElement>>
    {
        typedef TElement Type;
    };

    template <class TElement>
    struct IteratorType<detail::SpatialSubset<TElement>>
    {
        typedef detail::SpatialSubsetIterator<TElement> Type;
    };
}
