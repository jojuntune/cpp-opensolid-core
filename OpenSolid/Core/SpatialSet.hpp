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

#include <OpenSolid/Core/SpatialSet.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/LazyCollection.hpp>
#include <OpenSolid/Core/LazyCollection/ContainPredicate.hpp>
#include <OpenSolid/Core/LazyCollection/FilteredSpatialSet.hpp>
#include <OpenSolid/Core/LazyCollection/OverlapPredicate.hpp>
#include <OpenSolid/Core/LazyCollection/SpatialSetData.hpp>
#include <OpenSolid/Core/LazyCollection/SpatialSetNode.hpp>
#include <OpenSolid/Core/Transformable.hpp>

#include <algorithm>

namespace opensolid
{
    namespace detail
    {
        template <class TBounds>
        inline
        bool
        hasLesserMedian(
            const TBounds& firstBounds,
            const TBounds& secondBounds,
            int index
        ) {
            Interval difference = firstBounds(index) - secondBounds(index);
            return difference.upperBound() < -difference.lowerBound();
        }

        inline
        bool
        hasLesserMedian(Interval firstInterval, Interval secondInterval, int index) {
            assert(index == 0);
            Interval difference = firstInterval - secondInterval;
            return difference.upperBound() < -difference.lowerBound();
        }

        template <class TBounds>
        inline
        bool
        hasGreaterMedian(
            const TBounds& firstBounds,
            const TBounds& secondBounds,
            int index
        ) {
            Interval difference = firstBounds(index) - secondBounds(index);
            return difference.upperBound() > -difference.lowerBound();
        }

        inline
        bool
        hasGreaterMedian(Interval firstInterval, Interval secondInterval, int index) {
            assert(index == 0);
            Interval difference = firstInterval - secondInterval;
            return difference.upperBound() > -difference.lowerBound();
        }
    }

    template <class TItem>
    void
    SpatialSet<TItem>::init(
        detail::SpatialSetNode<TItem>* nodePtr,
        detail::SpatialSetNode<TItem>* nextPtr,
        BoundsData** begin,
        BoundsData** end,
        int sortIndex
    ) {
        nodePtr->nextPtr = nextPtr;
        std::size_t size = end - begin;
        if (size == 1) {
            // Leaf node
            nodePtr->bounds = (*begin)->bounds;
            nodePtr->leftChildPtr = nullptr;
            nodePtr->itemPtr = (*begin)->itemPtr;
        } else if (size == 2) {
            // Node with two leaf children
            detail::SpatialSetNode<TItem>* leftChildPtr = nodePtr + 1;
            detail::SpatialSetNode<TItem>* rightChildPtr = nodePtr + 2;
            BoundsData* firstBoundsDataPtr = *begin;
            BoundsData* secondBoundsDataPtr = *(begin + 1);
            typename BoundsType<TItem>::Type firstBounds = firstBoundsDataPtr->bounds;
            typename BoundsType<TItem>::Type secondBounds = secondBoundsDataPtr->bounds;

            nodePtr->bounds = firstBounds.hull(secondBounds);
            nodePtr->leftChildPtr = leftChildPtr;
            nodePtr->itemPtr = nullptr;

            leftChildPtr->leftChildPtr = nullptr;
            rightChildPtr->leftChildPtr = nullptr;
            bool reversed = detail::hasLesserMedian(secondBounds, firstBounds, sortIndex);
            if (reversed) {
                leftChildPtr->bounds = secondBounds;
                rightChildPtr->bounds = firstBounds;

                leftChildPtr->itemPtr = secondBoundsDataPtr->itemPtr;
                rightChildPtr->itemPtr = firstBoundsDataPtr->itemPtr;
            } else {
                leftChildPtr->bounds = firstBounds;
                rightChildPtr->bounds = secondBounds;

                leftChildPtr->itemPtr = firstBoundsDataPtr->itemPtr;
                rightChildPtr->itemPtr = secondBoundsDataPtr->itemPtr;
            }
            leftChildPtr->nextPtr = rightChildPtr;
            rightChildPtr->nextPtr = nextPtr;
        } else {
            // Compute overall bounds
            typename BoundsType<TItem>::Type overallBounds = (*begin)->bounds;
            for (BoundsData** iterator = begin + 1; iterator != end; ++iterator) {
                overallBounds = overallBounds.hull((*iterator)->bounds);
            }
            nodePtr->bounds = overallBounds;

            // Partition child nodes
            std::size_t leftSize = size / 2;
            BoundsData** mid = begin + leftSize;
            std::nth_element(
                begin,
                mid,
                end,
                [sortIndex] (BoundsData* firstBoundsDataPtr, BoundsData* secondBoundsDataPtr) {
                    return detail::hasLesserMedian(
                        firstBoundsDataPtr->bounds,
                        secondBoundsDataPtr->bounds,
                        sortIndex
                    );
                }
            );

            // Recurse into chid nodes
            int nextSortIndex = (sortIndex + 1) % NumDimensions<TItem>::Value;
            
            detail::SpatialSetNode<TItem>* leftChildPtr = nodePtr + 1;
            detail::SpatialSetNode<TItem>* rightChildPtr = leftChildPtr + (2 * leftSize - 1);
            
            nodePtr->leftChildPtr = leftChildPtr;
            nodePtr->itemPtr = nullptr;
            
            init(leftChildPtr, rightChildPtr, begin, mid, nextSortIndex);
            init(rightChildPtr, nextPtr, mid, end, nextSortIndex);
        }
    }

    template <class TItem>
    void
    SpatialSet<TItem>::init() {
        std::size_t numItems = _dataPtr->items.size();

        if (numItems == 0) {
            _dataPtr->nodes.clear();
            return;
        }

        // Initialize bounds data
        std::vector<BoundsData> boundsData(numItems);
        std::vector<BoundsData*> boundsDataPtrs(numItems);
        BoundsFunction<TItem> boundsFunction;
        for (std::size_t i = 0; i < numItems; ++i) {
            typename BoundsType<TItem>::Type bounds = boundsFunction(_dataPtr->items[i]);

            boundsData[i].bounds = bounds;
            boundsData[i].itemPtr = &(_dataPtr->items[i]);
            boundsDataPtrs[i] = &boundsData[i];
        }

        // Recursively construct tree
        _dataPtr->nodes.resize(2 * numItems - 1);
        init(
            _dataPtr->nodes.data(),
            nullptr,
            &boundsDataPtrs.front(),
            &boundsDataPtrs.back() + 1,
            0
        );
    }

    template <class TItem>
    inline
    SpatialSet<TItem>::SpatialSet() {
    }

    template <class TItem>
    inline
    SpatialSet<TItem>::SpatialSet(const SpatialSet<TItem>& other) :
        _dataPtr(other._dataPtr) {
    }

    template <class TItem>
    inline
    SpatialSet<TItem>::SpatialSet(SpatialSet<TItem>&& other) :
        _dataPtr(std::move(other._dataPtr)) {
    }

    template <class TItem>
    inline
    SpatialSet<TItem>::SpatialSet(const std::vector<TItem>& items) :
        _dataPtr(new detail::SpatialSetData<TItem>()) {

        _dataPtr->items = items;
        init();
    }

    template <class TItem>
    inline
    SpatialSet<TItem>::SpatialSet(std::vector<TItem>&& items) :
        _dataPtr(new detail::SpatialSetData<TItem>()) {

        _dataPtr->items = std::move(items);
        init();
    }

    template <class TItem> template <class TDerived>
    inline
    SpatialSet<TItem>::SpatialSet(const LazyCollection<TDerived>& collection) :
        _dataPtr(new detail::SpatialSetData<TItem>()) {

        _dataPtr->items = std::vector<TItem>(collection.begin(), collection.end());
        init();        
    }
    
    template <class TItem> template <class TIterator>
    inline
    SpatialSet<TItem>::SpatialSet(TIterator begin, TIterator end) :
        _dataPtr(new detail::SpatialSetData<TItem>()) {

        _dataPtr->items = std::vector<TItem>(begin, end);
        init();
    }
    
    template <class TItem>
    inline
    void
    SpatialSet<TItem>::operator=(const SpatialSet<TItem>& other) {
        _dataPtr = other._dataPtr;
    }
    
    template <class TItem>
    inline
    void
    SpatialSet<TItem>::operator=(SpatialSet<TItem>&& other) {
        _dataPtr = std::move(other._dataPtr);
    }

    template <class TItem>
    inline
    void
    SpatialSet<TItem>::swap(SpatialSet<TItem>& other) {
        _dataPtr.swap(other._dataPtr);
    }

    template <class TItem>
    inline
    const detail::SpatialSetNode<TItem>*
    SpatialSet<TItem>::rootNode() const {
        if (isEmpty()) {
            return nullptr;
        } else {
            return _dataPtr->nodes.data();
        }
    }

    template <class TItem>
    inline
    typename std::vector<TItem>::const_iterator
    SpatialSet<TItem>::begin() const {
        if (isEmpty()) {
            return _emptyVector.begin();
        } else {
            return _dataPtr->items.begin();
        }
    }

    template <class TItem>
    inline
    typename std::vector<TItem>::const_iterator
    SpatialSet<TItem>::end() const {
        if (isEmpty()) {
            return _emptyVector.end();
        } else {
            return _dataPtr->items.end();
        }
    }

    template <class TItem>
    inline
    bool
    SpatialSet<TItem>::isEmpty() const {
        return !_dataPtr || _dataPtr->items.empty();
    }
    
    template <class TItem>
    inline
    std::size_t
    SpatialSet<TItem>::size() const {
        if (isEmpty()) {
            return 0;
        } else {
            return _dataPtr->items.size();
        }
    }

    template <class TItem>
    inline
    typename BoundsType<TItem>::Type
    SpatialSet<TItem>::bounds() const {
        if (isEmpty()) {
            return typename BoundsType<TItem>::Type();
        } else {
            return _dataPtr->nodes.front().bounds;
        }
    }

    template <class TItem>
    inline
    const TItem&
    SpatialSet<TItem>::operator[](std::size_t index) const {
        assert(!isEmpty());
        return _dataPtr->items[index];
    }

    template <class TItem>
    inline
    void
    SpatialSet<TItem>::clear() {
        _dataPtr.reset();
    }

    template <class TItem>
    inline
    detail::FilteredSpatialSet<TItem, detail::OverlapPredicate<TItem>>
    SpatialSet<TItem>::overlapping(
        const typename BoundsType<TItem>::Type& predicateBounds,
        double precision
    ) const {
        return detail::FilteredSpatialSet<TItem, detail::OverlapPredicate<TItem>>(
            *this,
            detail::OverlapPredicate<TItem>(predicateBounds, precision)
        );
    }

    template <class TItem>
    inline
    detail::FilteredSpatialSet<TItem, detail::ContainPredicate<TItem>>
    SpatialSet<TItem>::containing(
        const typename BoundsType<TItem>::Type& predicateBounds,
        double precision
    ) const {
        return detail::FilteredSpatialSet<TItem, detail::ContainPredicate<TItem>>(
            *this,
            detail::ContainPredicate<TItem>(predicateBounds, precision)
        );
    }

    template <class TItem> template <class TBoundsPredicate>
    inline
    detail::FilteredSpatialSet<TItem, TBoundsPredicate>
    SpatialSet<TItem>::filtered(TBoundsPredicate boundsPredicate) const {
        return detail::FilteredSpatialSet<TItem, TBoundsPredicate>(*this, boundsPredicate);
    }

    template <class TItem>
    inline
    typename std::vector<TItem>::const_iterator
    SpatialSet<TItem>::find(const TItem& item, double precision) const {
        if (isEmpty()) {
            return end();
        } else {
            typedef detail::FilteredSpatialSetIterator<TItem, detail::OverlapPredicate<TItem>>
                FilteredIterator;
            
            BoundsFunction<TItem> boundsFunction;
            detail::OverlapPredicate<TItem> overlapPredicate(boundsFunction(item), precision);
            FilteredIterator filteredIterator(rootNode(), &overlapPredicate);
            FilteredIterator filteredEnd(nullptr, &overlapPredicate);
            while (filteredIterator != filteredEnd) {
                if (equalityFunction(item, *filteredIterator, precision)) {
                    return begin() + (&(*filteredIterator) - _dataPtr->items.data());
                }
                ++filteredIterator;
            }
            return end();
        }
    }

    namespace detail
    {
        template <class TItem>
        const SpatialSetNode<TItem>*
        nextLeafNode(const SpatialSetNode<TItem>* leafNodePtr) {
            assert(leafNodePtr);
            assert(leafNodePtr->itemPtr);
            const SpatialSetNode<TItem>* nodePtr = leafNodePtr->nextPtr;
            if (!nodePtr) {
                return nodePtr;
            }
            while (nodePtr->leftChildPtr) {
                nodePtr = nodePtr->leftChildPtr;
            }
            return nodePtr;
        }

        template <class TItem>
        void
        markDuplicateItems(
            const SpatialSetNode<TItem>* anchorNodePtr,
            const TItem* anchorItemPtr,
            std::size_t uniqueIndex,
            const TItem* firstItemPtr,
            double precision,
            std::vector<std::size_t>& mapping
        ) {
            const SpatialSetNode<TItem>* candidateNodePtr = anchorNodePtr->nextPtr;
            while (candidateNodePtr) {
                if (candidateNodePtr->bounds.overlaps(anchorNodePtr->bounds)) {
                    const SpatialSetNode<TItem>* leftChildPtr = candidateNodePtr->leftChildPtr;
                    if (leftChildPtr) {
                        // Internal node: descend into left child
                        candidateNodePtr = leftChildPtr;
                    } else {
                        // Leaf node: check for duplicate items, then move to next node
                        const TItem* candidateItemPtr = candidateNodePtr->itemPtr;
                        if (equalityFunction(*anchorItemPtr, *candidateItemPtr, precision)) {
                            std::size_t candidateItemIndex = candidateItemPtr - firstItemPtr;
                            assert(mapping[candidateItemIndex] == std::size_t(-1));
                            mapping[candidateItemIndex] = uniqueIndex;
                        }
                        candidateNodePtr = candidateNodePtr->nextPtr;
                    }
                } else {
                    candidateNodePtr = candidateNodePtr->nextPtr;
                }
            }
        }
    }

    template <class TItem>
    inline
    std::vector<TItem>
    SpatialSet<TItem>::uniqueItems(double precision) const {
        std::vector<std::size_t> dummy;
        return uniqueItems(dummy, precision);
    }

    template <class TItem>
    inline
    std::vector<TItem>
    SpatialSet<TItem>::uniqueItems(std::vector<std::size_t>& mapping, double precision) const {
        if (isEmpty()) {
            mapping.clear();
            return std::vector<TItem>();
        } else {
            // Initialize unique item mapping
            mapping.resize(size());
            std::fill(mapping.begin(), mapping.end(), std::size_t(-1));
            std::size_t uniqueIndex = 0;

            // Get first item for calculating item indices
            const TItem* firstItemPtr = _dataPtr->items.data();

            // Descend to left-most node
            const detail::SpatialSetNode<TItem>* nodePtr = rootNode();
            while (nodePtr->leftChildPtr) {
                nodePtr = nodePtr->leftChildPtr;
            }

            std::vector<TItem> results;
            do {
                const TItem* itemPtr = nodePtr->itemPtr;
                std::size_t itemIndex = itemPtr - firstItemPtr;
                if (mapping[itemIndex] == std::size_t(-1)) {
                    results.push_back(*itemPtr);
                    mapping[itemIndex] = uniqueIndex;
                    detail::markDuplicateItems(
                        nodePtr,
                        itemPtr,
                        uniqueIndex,
                        firstItemPtr,
                        precision,
                        mapping
                    );
                    ++uniqueIndex;
                }
                nodePtr = detail::nextLeafNode(nodePtr);
            } while (nodePtr);
            return results;
        }
    }
    
    template <class TItem>
    std::ostream&
    operator<<(std::ostream& stream, const SpatialSet<TItem>& set) {
        stream << "{";
        if (!set.isEmpty()) {
            std::for_each(
                set.begin(),
                set.end() - 1,
                [&stream] (const TItem& item) {
                    stream << item << ",";
                }
            );
            stream << set.back();
        }
        stream << "}";
        return stream;
    }
}
