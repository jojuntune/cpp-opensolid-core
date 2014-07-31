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

#include <OpenSolid/Core/LazyCollection/FilteredSpatialSet.declarations.hpp>

#include <OpenSolid/Core/LazyCollection.definitions.hpp>
#include <OpenSolid/Core/LazyCollection/SpatialSetNode.declarations.hpp>
#include <OpenSolid/Core/SpatialSet.definitions.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    template <class TItem, class TBoundsPredicate>
    struct IteratorType<detail::FilteredSpatialSet<TItem, TBoundsPredicate>>
    {
        typedef detail::FilteredSpatialSetIterator<TItem, TBoundsPredicate> Type;
    };

    namespace detail
    {
        template <class TItem, class TBoundsPredicate>
        class FilteredSpatialSet :
            public LazyCollection<FilteredSpatialSet<TItem, TBoundsPredicate>>
        {
        private:
            SpatialSet<TItem> _set;
            TBoundsPredicate _boundsPredicate;
        public:
            FilteredSpatialSet(const FilteredSpatialSet<TItem, TBoundsPredicate>& other);
            
            FilteredSpatialSet(FilteredSpatialSet<TItem, TBoundsPredicate>&& other);

            FilteredSpatialSet(
                const SpatialSet<TItem>& set,
                TBoundsPredicate boundsPredicate
            );

            FilteredSpatialSet(
                SpatialSet<TItem>&& set,
                TBoundsPredicate boundsPredicate
            );

            FilteredSpatialSetIterator<TItem, TBoundsPredicate>
            begin() const;

            FilteredSpatialSetIterator<TItem, TBoundsPredicate>
            end() const;

            bool
            isEmpty() const;

            std::size_t
            size() const;
        };

        template <class TItem, class TBoundsPredicate>
        class FilteredSpatialSetIterator :
            public boost::iterator_facade<
                FilteredSpatialSetIterator<TItem, TBoundsPredicate>,
                TItem,
                boost::forward_traversal_tag,
                const TItem&
            >
        {
        private:
            const SpatialSetNode<TItem>* _currentNodePtr;
            const TBoundsPredicate* _boundsPredicatePtr;

            friend class boost::iterator_core_access;

            void
            descendFrom(const SpatialSetNode<TItem>* candidateNodePtr);

            void
            increment();

            bool
            equal(const FilteredSpatialSetIterator<TItem, TBoundsPredicate>& other) const;

            const TItem&
            dereference() const;
        public:
            FilteredSpatialSetIterator();

            FilteredSpatialSetIterator(
                const SpatialSetNode<TItem>* rootNodePtr,
                const TBoundsPredicate* boundsPredicatePtr
            );
        };
    }
}
