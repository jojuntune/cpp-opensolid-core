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

#include <OpenSolid/Core/SpatialSet/FilteredSpatialSet.declarations.hpp>

#include <OpenSolid/Core/Iterable.definitions.hpp>
#include <OpenSolid/Core/SpatialSet.declarations.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSetNode.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TItem, class TBoundsPredicate>
        class FilteredSpatialSet :
            public Iterable<FilteredSpatialSet<TItem, TBoundsPredicate>>
        {
        private:
            const SpatialSet<TItem>& _set;
            TBoundsPredicate _boundsPredicate;

            template <class TDerived>
            friend class Iterable;

            friend class SpatialSet<TItem>;

            FilteredSpatialSetIterator<TItem, TBoundsPredicate>
            beginImpl() const;

            FilteredSpatialSetIterator<TItem, TBoundsPredicate>
            endImpl() const;

            bool
            isEmptyImpl() const;

            std::int64_t
            sizeImpl() const;

            FilteredSpatialSet(const FilteredSpatialSet<TItem, TBoundsPredicate>& other);
        public:
            FilteredSpatialSet(
                const SpatialSet<TItem>& set,
                TBoundsPredicate boundsPredicate
            );
        };

        template <class TItem, class TBoundsPredicate>
        class FilteredSpatialSetIterator :
            public boost::iterator_facade<
                FilteredSpatialSetIterator<TItem, TBoundsPredicate>,
                const TItem,
                boost::forward_traversal_tag
            >
        {
        private:
            const SpatialSetNode<TItem>* _currentNode;
            const TBoundsPredicate* _boundsPredicate;

            friend class boost::iterator_core_access;

            void
            descendFrom(const SpatialSetNode<TItem>* candidateNode);

            void
            increment();

            bool
            equal(const FilteredSpatialSetIterator<TItem, TBoundsPredicate>& other) const;

            const TItem&
            dereference() const;
        public:
            FilteredSpatialSetIterator();

            FilteredSpatialSetIterator(
                const SpatialSetNode<TItem>* rootNode,
                const TBoundsPredicate* boundsPredicate
            );
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
    template <class TItem, class TBoundsPredicate>
    struct ItemType<detail::FilteredSpatialSet<TItem, TBoundsPredicate>>
    {
        typedef TItem Type;
    };

    template <class TItem, class TBoundsPredicate>
    struct IteratorType<detail::FilteredSpatialSet<TItem, TBoundsPredicate>>
    {
        typedef detail::FilteredSpatialSetIterator<TItem, TBoundsPredicate> Type;
    };
}
