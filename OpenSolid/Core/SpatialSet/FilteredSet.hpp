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

#include <OpenSolid/Core/SpatialSet/FilteredSet.definitions.hpp>

namespace opensolid
{
    namespace spatialset
    {
        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSet<TElement, TBoundsPredicate>::FilteredSet(
            const SetNode<TElement>* rootNode,
            TBoundsPredicate boundsPredicate
        ) : _rootNode(rootNode),
            _boundsPredicate(boundsPredicate) {
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>
        FilteredSet<TElement, TBoundsPredicate>::begin() const {
            return FilteredSetIterator<TElement, TBoundsPredicate>(_rootNode, &_boundsPredicate);
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>
        FilteredSet<TElement, TBoundsPredicate>::end() const {
            return FilteredSetIterator<TElement, TBoundsPredicate>(nullptr, &_boundsPredicate);
        }

        template <class TElement, class TBoundsPredicate>
        inline
        void
        FilteredSetIterator<TElement, TBoundsPredicate>::descendFrom(
            const SetNode<TElement>* candidateNode
        ) {
            _currentNode = candidateNode;
            while (candidateNode) {
                if ((*_boundsPredicate)(candidateNode->bounds)) {
                    _currentNode = candidateNode;
                    candidateNode = candidateNode->leftChild;
                } else {
                    candidateNode = candidateNode->next;
                    _currentNode = candidateNode;
                }
            }
        }

        template <class TElement, class TBoundsPredicate>
        inline
        void
        FilteredSetIterator<TElement, TBoundsPredicate>::increment() {
            descendFrom(_currentNode->next);
        }

        template <class TElement, class TBoundsPredicate>
        inline
        bool
        FilteredSetIterator<TElement, TBoundsPredicate>::equal(
            const FilteredSetIterator<TElement, TBoundsPredicate>& other
        ) const {
            return _currentNode == other._currentNode;
        }

        template <class TElement, class TBoundsPredicate>
        inline
        const TElement&
        FilteredSetIterator<TElement, TBoundsPredicate>::dereference() const {
            return *(_currentNode->element);
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>::FilteredSetIterator() :
            _currentNode(nullptr) {
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>::FilteredSetIterator(
            const SetNode<TElement>* rootNode,
            const TBoundsPredicate* boundsPredicate
        ) : _currentNode(nullptr),
            _boundsPredicate(boundsPredicate) {

            if (rootNode) {
                descendFrom(rootNode);
            }
        }
    }
}
