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

#include <OpenSolid/Core/SpatialSet/SetNode.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace spatialset
    {
        template <class TElement, class TBoundsPredicate>
        class FilteredSet
        {
        private:
            const SetNode<TElement>* _rootNode;
            TBoundsPredicate _boundsPredicate;
        public:
            typedef FilteredSetIterator<TElement, TBoundsPredicate> Iterator;

            FilteredSet(
                const SetNode<TElement>* rootNode,
                TBoundsPredicate boundsPredicate
            );

            FilteredSetIterator<TElement, TBoundsPredicate>
            begin() const;

            FilteredSetIterator<TElement, TBoundsPredicate>
            end() const;
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
