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

#include <OpenSolid/Core/SpatialSet/FilteredSpatialSet.definitions.hpp>

#include <OpenSolid/Core/Iterable.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TElement, TBoundsPredicate>
        FilteredSpatialSet<TElement, TBoundsPredicate>::beginImpl() const {
            return FilteredSpatialSetIterator<TElement, TBoundsPredicate>(
                _set.rootNode(),
                &_boundsPredicate
            );
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TElement, TBoundsPredicate>
        FilteredSpatialSet<TElement, TBoundsPredicate>::endImpl() const {
            return FilteredSpatialSetIterator<TElement, TBoundsPredicate>(
                nullptr,
                &_boundsPredicate
            );
        }

        template <class TElement, class TBoundsPredicate>
        inline
        bool
        FilteredSpatialSet<TElement, TBoundsPredicate>::isEmptyImpl() const {
            return this->begin() == this->end();
        }

        template <class TElement, class TBoundsPredicate>
        inline
        std::int64_t
        FilteredSpatialSet<TElement, TBoundsPredicate>::sizeImpl() const {
            return std::distance(this->begin(), this->end());
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSpatialSet<TElement, TBoundsPredicate>::FilteredSpatialSet(
            const FilteredSpatialSet<TElement, TBoundsPredicate>& other
        ) : _set(other._set),
            _boundsPredicate(other._boundsPredicate) {
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSpatialSet<TElement, TBoundsPredicate>::FilteredSpatialSet(
            const SpatialSet<TElement>& set,
            TBoundsPredicate boundsPredicate
        ) : _set(set),
            _boundsPredicate(boundsPredicate) {
        }

        template <class TElement, class TBoundsPredicate>
        inline
        void
        FilteredSpatialSetIterator<TElement, TBoundsPredicate>::descendFrom(
            const SpatialSetNode<TElement>* candidateNode
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
        FilteredSpatialSetIterator<TElement, TBoundsPredicate>::increment() {
            descendFrom(_currentNode->next);
        }

        template <class TElement, class TBoundsPredicate>
        inline
        bool
        FilteredSpatialSetIterator<TElement, TBoundsPredicate>::equal(
            const FilteredSpatialSetIterator<TElement, TBoundsPredicate>& other
        ) const {
            return _currentNode == other._currentNode;
        }

        template <class TElement, class TBoundsPredicate>
        inline
        const TElement&
        FilteredSpatialSetIterator<TElement, TBoundsPredicate>::dereference() const {
            return *(_currentNode->element);
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TElement, TBoundsPredicate>::FilteredSpatialSetIterator() :
            _currentNode(nullptr) {
        }

        template <class TElement, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TElement, TBoundsPredicate>::FilteredSpatialSetIterator(
            const SpatialSetNode<TElement>* rootNode,
            const TBoundsPredicate* boundsPredicate
        ) : _currentNode(nullptr),
            _boundsPredicate(boundsPredicate) {

            if (rootNode) {
                descendFrom(rootNode);
            }
        }
    }
}
