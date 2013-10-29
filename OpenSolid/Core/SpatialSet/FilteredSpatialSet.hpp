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
        template <class TItem, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>
        FilteredSpatialSet<TItem, TBoundsPredicate>::beginImpl() const {
            return FilteredSpatialSetIterator<TItem, TBoundsPredicate>(
                _set.rootNode(),
                &_boundsPredicate
            );
        }

        template <class TItem, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>
        FilteredSpatialSet<TItem, TBoundsPredicate>::endImpl() const {
            return FilteredSpatialSetIterator<TItem, TBoundsPredicate>(
                nullptr,
                &_boundsPredicate
            );
        }

        template <class TItem, class TBoundsPredicate>
        inline
        bool
        FilteredSpatialSet<TItem, TBoundsPredicate>::isEmptyImpl() const {
            return this->begin() == this->end();
        }

        template <class TItem, class TBoundsPredicate>
        inline
        std::int64_t
        FilteredSpatialSet<TItem, TBoundsPredicate>::sizeImpl() const {
            return std::distance(this->begin(), this->end());
        }

        template <class TItem, class TBoundsPredicate>
        inline
        FilteredSpatialSet<TItem, TBoundsPredicate>::FilteredSpatialSet(
            const FilteredSpatialSet<TItem, TBoundsPredicate>& other
        ) : _set(other._set),
            _boundsPredicate(other._boundsPredicate) {
        }

        template <class TItem, class TBoundsPredicate>
        inline
        FilteredSpatialSet<TItem, TBoundsPredicate>::FilteredSpatialSet(
            const SpatialSet<TItem>& set,
            TBoundsPredicate boundsPredicate
        ) : _set(set),
            _boundsPredicate(boundsPredicate) {
        }

        template <class TItem, class TBoundsPredicate>
        inline
        void
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::descendFrom(
            const SpatialSetNode<TItem>* candidateNode
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

        template <class TItem, class TBoundsPredicate>
        inline
        void
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::increment() {
            descendFrom(_currentNode->next);
        }

        template <class TItem, class TBoundsPredicate>
        inline
        bool
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::equal(
            const FilteredSpatialSetIterator<TItem, TBoundsPredicate>& other
        ) const {
            return _currentNode == other._currentNode;
        }

        template <class TItem, class TBoundsPredicate>
        inline
        const TItem&
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::dereference() const {
            return *(_currentNode->item);
        }

        template <class TItem, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::FilteredSpatialSetIterator() :
            _currentNode(nullptr) {
        }

        template <class TItem, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::FilteredSpatialSetIterator(
            const SpatialSetNode<TItem>* rootNode,
            const TBoundsPredicate* boundsPredicate
        ) : _currentNode(nullptr),
            _boundsPredicate(boundsPredicate) {

            if (rootNode) {
                descendFrom(rootNode);
            }
        }
    }
}
