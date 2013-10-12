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
            _nodeStack =  std::stack<const SetNode<TElement>*>();
            return FilteredSetIterator<TElement, TBoundsPredicate>(
                _rootNode,
                _boundsPredicate,
                &_nodeStack
            );
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>
        FilteredSet<TElement, TBoundsPredicate>::end() const {
            return FilteredSetIterator<TElement, TBoundsPredicate>(
                nullptr,
                _boundsPredicate,
                &_nodeStack
            );
        }

        template <class TElement, class TBoundsPredicate>
        inline
        void
        FilteredSetIterator<TElement, TBoundsPredicate>::descendFrom(
            const SetNode<TElement>* candidateNode
        ) {
            do {
                if (_boundsPredicate(candidateNode->bounds)) {
                    if (candidateNode->left) {
                        // Get child nodes
                        const SetNode<TElement>* leftChild =
                            static_cast<const SetNode<TElement>*>(candidateNode->left);
                        const SetNode<TElement>* rightChild =
                            static_cast<const SetNode<TElement>*>(candidateNode->right);

                        // Push right child node onto stack for future iteration
                        _nodeStack->push(rightChild);

                        // Recurse into left child
                        candidateNode = leftChild;
                    } else {
                        // Found first filtered leaf node
                        _currentNode = candidateNode;
                    }
                } else if (!_nodeStack->empty()) {
                    // Get next candidate node from stack
                    candidateNode = _nodeStack->top();
                    _nodeStack->pop();
                } else {
                    // No more candidate nodes
                    candidateNode = nullptr;
                }
            } while (candidateNode && !_currentNode);
        }

        template <class TElement, class TBoundsPredicate>
        inline
        void
        FilteredSetIterator<TElement, TBoundsPredicate>::increment() {
            _currentNode = nullptr;
            if (_nodeStack && !_nodeStack->empty()) {
                const SetNode<TElement>* candidateNode = _nodeStack->top();
                _nodeStack->pop();
                descendFrom(candidateNode);
            }
        }

        template <class TElement, class TBoundsPredicate>
        inline
        bool
        FilteredSetIterator<TElement, TBoundsPredicate>::equal(
            const FilteredSetIterator<TElement, TBoundsPredicate>& other
        ) const {
            assert(_nodeStack == other._nodeStack);
            return _currentNode == other._currentNode;
        }

        template <class TElement, class TBoundsPredicate>
        inline
        const TElement&
        FilteredSetIterator<TElement, TBoundsPredicate>::dereference() const {
            return *static_cast<const TElement*>(_currentNode->right);
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>::FilteredSetIterator() :
            _currentNode(nullptr),
            _nodeStack(nullptr) {
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>::FilteredSetIterator(
            const SetNode<TElement>* rootNode,
            TBoundsPredicate boundsPredicate,
            std::stack<const SetNode<TElement>*>* nodeStack
        ) : _currentNode(nullptr),
            _boundsPredicate(boundsPredicate),
            _nodeStack(nodeStack) {

            if (rootNode) {
                descendFrom(rootNode);
            }
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>::FilteredSetIterator(
            const FilteredSetIterator<TElement, TBoundsPredicate>& other
        ) : _currentNode(other._currentNode),
            _boundsPredicate(other._boundsPredicate),
            _nodeStack(other._nodeStack) {
            
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSetIterator<TElement, TBoundsPredicate>::FilteredSetIterator(
            FilteredSetIterator<TElement, TBoundsPredicate>&& other
        ) : _currentNode(other._currentNode),
            _boundsPredicate(other._boundsPredicate),
            _nodeStack(other._nodeStack) {
        }

        template <class TElement, class TBoundsPredicate>
        inline
        void
        FilteredSetIterator<TElement, TBoundsPredicate>::operator=(
            const FilteredSetIterator<TElement, TBoundsPredicate>& other
        ) {
            _currentNode = other._currentNode;
            _boundsPredicate = other._boundsPredicate;
            _nodeStack = other._nodeStack;
        }

        template <class TElement, class TBoundsPredicate>
        inline
        void
        FilteredSetIterator<TElement, TBoundsPredicate>::operator=(
            FilteredSetIterator<TElement, TBoundsPredicate>&& other
        ) {
            _currentNode = other._currentNode;
            _boundsPredicate = other._boundsPredicate;
            _nodeStack = other._nodeStack;
        }
    }
}
