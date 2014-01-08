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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/LazyCollection/FilteredSpatialSet.definitions.hpp>

#include <OpenSolid/Core/LazyCollection.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>

namespace opensolid
{
    namespace detail
    {
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
            FilteredSpatialSet<TItem, TBoundsPredicate>&& other
        ) : _set(std::move(other._set)),
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
        FilteredSpatialSet<TItem, TBoundsPredicate>::FilteredSpatialSet(
            SpatialSet<TItem>&& set,
            TBoundsPredicate boundsPredicate
        ) : _set(std::move(set)),
            _boundsPredicate(boundsPredicate) {
        }

        template <class TItem, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>
        FilteredSpatialSet<TItem, TBoundsPredicate>::begin() const {
            return FilteredSpatialSetIterator<TItem, TBoundsPredicate>(
                _set.rootNode(),
                &_boundsPredicate
            );
        }

        template <class TItem, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>
        FilteredSpatialSet<TItem, TBoundsPredicate>::end() const {
            return FilteredSpatialSetIterator<TItem, TBoundsPredicate>(
                nullptr,
                &_boundsPredicate
            );
        }

        template <class TItem, class TBoundsPredicate>
        inline
        bool
        FilteredSpatialSet<TItem, TBoundsPredicate>::isEmpty() const {
            return this->isEmptyDefaultImpl();
        }

        template <class TItem, class TBoundsPredicate>
        inline
        std::int64_t
        FilteredSpatialSet<TItem, TBoundsPredicate>::size() const {
            return this->sizeDefaultImpl();
        }

        template <class TItem, class TBoundsPredicate>
        inline
        void
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::descendFrom(
            const SpatialSetNode<TItem>* candidateNodePtr
        ) {
            _currentNodePtr = candidateNodePtr;
            while (candidateNodePtr) {
                if ((*_boundsPredicatePtr)(candidateNodePtr->bounds)) {
                    _currentNodePtr = candidateNodePtr;
                    candidateNodePtr = candidateNodePtr->leftChildPtr;
                } else {
                    candidateNodePtr = candidateNodePtr->nextPtr;
                    _currentNodePtr = candidateNodePtr;
                }
            }
        }

        template <class TItem, class TBoundsPredicate>
        inline
        void
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::increment() {
            descendFrom(_currentNodePtr->nextPtr);
        }

        template <class TItem, class TBoundsPredicate>
        inline
        bool
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::equal(
            const FilteredSpatialSetIterator<TItem, TBoundsPredicate>& other
        ) const {
            return _currentNodePtr == other._currentNodePtr;
        }

        template <class TItem, class TBoundsPredicate>
        inline
        const TItem&
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::dereference() const {
            return *(_currentNodePtr->itemPtr);
        }

        template <class TItem, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::FilteredSpatialSetIterator() :
            _currentNodePtr(nullptr),
            _boundsPredicatePtr(nullptr) {
        }

        template <class TItem, class TBoundsPredicate>
        inline
        FilteredSpatialSetIterator<TItem, TBoundsPredicate>::FilteredSpatialSetIterator(
            const SpatialSetNode<TItem>* rootNodePtr,
            const TBoundsPredicate* boundsPredicatePtr
        ) : _currentNodePtr(nullptr),
            _boundsPredicatePtr(boundsPredicatePtr) {

            if (rootNodePtr) {
                descendFrom(rootNodePtr);
            }
        }
    }
}
