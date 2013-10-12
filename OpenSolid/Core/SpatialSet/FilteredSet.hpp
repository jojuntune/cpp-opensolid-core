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
            const boost::intrusive_ptr<SpatialSetData<TElement>>& setData,
            TBoundsPredicate boundsPredicate
        ) : _setData(setData),
            _boundsPredicate(boundsPredicate) {
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>
        FilteredSet<TElement, TBoundsPredicate>::begin() const {
            if (_setData->nodes.empty()) {
                return end();
            } else {
                return FilteredSetIterator<TElement, TBoundsPredicate>(
                    &_setData->nodes.front(),
                    _boundsPredicate
                );
            }
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>
        FilteredSet<TElement, TBoundsPredicate>::end() const {
            return FilteredSetIterator<TElement, TBoundsPredicate>();
        }

        template <class TElement, class TBoundsPredicate>
        void
        FilteredSetIterator<TElement, TBoundsPredicate>::increment() {
            // TODO
        }

        template <class TElement, class TBoundsPredicate>
        inline
        bool
        FilteredSetIterator<TElement, TBoundsPredicate>::equal(
            const FilteredSetIterator<TElement, TBoundsPredicate>& other
        ) const {
            return 
            return _node == other._node && _boundsPredicate == other._boundsPredicate;
        }

        template <class TElement, class TBoundsPredicate>
        inline
        const TElement&
        FilteredSetIterator<TElement, TBoundsPredicate>::dereference() const {
            return *((const TElement*) _node->right);
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>::FilteredSetIterator() :
            _node(nullptr) {
        }

        template <class TElement, class TBoundsPredicate>
        FilteredSetIterator<TElement, TBoundsPredicate>::FilteredSetIterator(
            SetNode<TElement>* root,
            TBoundsPredicate boundsPredicate
        ) : _node(nullptr), 
            _boundsPredicate(boundsPredicate) {

            Node* candidateNode = root;
            while (candidateNode && !_node) {
                if (_boundsPredicate(candidateNode->bounds)) {
                    if (candidateNode->left) {
                        // Push right child node onto stack
                        _stack.push(candidateNode->right);
                        // Recurse into left child
                        candidateNode = candidateNode->left;
                    } else {
                        // Found first filtered leaf node
                        _node = candidateNode;
                    }
                } else if (!_stack.empty()) {
                    // Get next candidate node from stack
                    node = _stack.pop();
                } else {
                    // No more candidate nodes
                    node = nullptr;
                }
            }
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>::FilteredSetIterator(
            const FilteredSetIterator<TElement, TBoundsPredicate>& other
        ) : _node(other._node),
            _boundsPredicate(other._boundsPredicate),
            _stack(other._stack) {
            
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>::FilteredSetIterator(
            FilteredSetIterator<TElement, TBoundsPredicate>&& other
        ) : _node(other._node),
            _boundsPredicate(other._boundsPredicate),
            _stack(std::move(other._stack)) {
        }

        template <class TElement, class TBoundsPredicate>
        inline
        void
        FilteredSetIterator<TElement, TBoundsPredicate>::operator=(
            const FilteredSetIterator<TElement, TBoundsPredicate>& other
        ) {
            _node = other._node;
            _boundsPredicate = other._boundsPredicate;
            _stack = other._stack;
        }

        template <class TElement, class TBoundsPredicate>
        inline
        void
        FilteredSetIterator<TElement, TBoundsPredicate>::operator=(
            FilteredSetIterator<TElement, TBoundsPredicate>&& other
        ) {
            _node = other._node;
            _boundsPredicate = other._boundsPredicate;
            _stack = std::move(other._stack);
        }
    }
}
