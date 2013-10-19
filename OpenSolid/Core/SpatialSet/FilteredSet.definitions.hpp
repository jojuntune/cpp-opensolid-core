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

#include <OpenSolid/Core/SpatialSet/FilteredSet.declarations.hpp>

#include <OpenSolid/Core/Iterable.definitions.hpp>
#include <OpenSolid/Core/SpatialSet.definitions.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace spatialset
    {
        template <class TElement, class TBoundsPredicate>
        class FilteredSet :
            public Iterable<FilteredSet<TElement, TBoundsPredicate>>
        {
        private:
            const SpatialSet<TElement>& _set;
            TBoundsPredicate _boundsPredicate;

            template <class TDerived>
            friend class Iterable;

            friend class SpatialSet<TElement>;

            FilteredSetIterator<TElement, TBoundsPredicate>
            beginImpl() const;

            FilteredSetIterator<TElement, TBoundsPredicate>
            endImpl() const;

            bool
            isEmptyImpl() const;

            std::int64_t
            sizeImpl() const;

            FilteredSet(const FilteredSet<TElement, TBoundsPredicate>& other);
        public:
            FilteredSet(
                const SpatialSet<TElement>& set,
                TBoundsPredicate boundsPredicate
            );
        };

        template <class TElement, class TBoundsPredicate>
        class FilteredSetIterator :
            public boost::iterator_facade<
                FilteredSetIterator<TElement, TBoundsPredicate>,
                const TElement,
                boost::forward_traversal_tag
            >
        {
        private:
            const SetNode<TElement>* _currentNode;
            const TBoundsPredicate* _boundsPredicate;

            friend class boost::iterator_core_access;

            void
            descendFrom(const SetNode<TElement>* candidateNode);

            void
            increment();

            bool
            equal(const FilteredSetIterator<TElement, TBoundsPredicate>& other) const;;

            const TElement&
            dereference() const;
        public:
            FilteredSetIterator();

            FilteredSetIterator(
                const SetNode<TElement>* rootNode,
                const TBoundsPredicate* boundsPredicate
            );
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
    template <class TElement, class TBoundsPredicate>
    struct ElementType<spatialset::FilteredSet<TElement, TBoundsPredicate>>
    {
        typedef TElement Type;
    };

    template <class TElement, class TBoundsPredicate>
    struct IteratorType<spatialset::FilteredSet<TElement, TBoundsPredicate>>
    {
        typedef spatialset::FilteredSetIterator<TElement, TBoundsPredicate> Type;
    };
}
