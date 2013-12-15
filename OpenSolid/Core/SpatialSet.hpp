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
#include <OpenSolid/Core/SpatialCollection.hpp>
#include <OpenSolid/Core/SpatialCollection/ContainPredicate.hpp>
#include <OpenSolid/Core/SpatialCollection/FilteredSpatialSet.hpp>
#include <OpenSolid/Core/SpatialCollection/OverlapPredicate.hpp>
#include <OpenSolid/Core/SpatialCollection/SpatialSetData.hpp>
#include <OpenSolid/Core/SpatialCollection/SpatialSetNode.hpp>
#include <OpenSolid/Core/SpatialList.hpp>
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
            std::int64_t index
        ) {
            Interval difference = firstBounds(index) - secondBounds(index);
            return difference.upperBound() < -difference.lowerBound();
        }

        inline
        bool
        hasLesserMedian(Interval firstInterval, Interval secondInterval, std::int64_t index) {
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
            std::int64_t index
        ) {
            Interval difference = firstBounds(index) - secondBounds(index);
            return difference.upperBound() > -difference.lowerBound();
        }

        inline
        bool
        hasGreaterMedian(Interval firstInterval, Interval secondInterval, std::int64_t index) {
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
        typename BoundsType<TItem>::Type& overallBounds,
        std::int64_t sortIndex
    ) {
        nodePtr->bounds = overallBounds;
        nodePtr->nextPtr = nextPtr;
        std::int64_t size = end - begin;
        if (size == 1) {
            // Leaf node
            nodePtr->leftChildPtr = nullptr;
            nodePtr->itemPtr = (*begin)->itemPtr;
        } else if (size == 2) {
            // Node with two leaf children
            detail::SpatialSetNode<TItem>* leftChildPtr = nodePtr + 1;
            detail::SpatialSetNode<TItem>* rightChildPtr = nodePtr + 2;

            nodePtr->leftChildPtr = leftChildPtr;
            nodePtr->itemPtr = nullptr;

            leftChildPtr->leftChildPtr = nullptr;
            rightChildPtr->leftChildPtr = nullptr;
            BoundsData* firstBoundsDataPtr = *begin;
            BoundsData* secondBoundsDataPtr = *(begin + 1);
            bool reversed = detail::hasLesserMedian(
                secondBoundsDataPtr->bounds,
                firstBoundsDataPtr->bounds,
                sortIndex
            );
            if (reversed) {
                leftChildPtr->bounds = secondBoundsDataPtr->bounds;
                rightChildPtr->bounds = firstBoundsDataPtr->bounds;

                leftChildPtr->itemPtr = secondBoundsDataPtr->itemPtr;
                rightChildPtr->itemPtr = firstBoundsDataPtr->itemPtr;
            } else {
                leftChildPtr->bounds = firstBoundsDataPtr->bounds;
                rightChildPtr->bounds = secondBoundsDataPtr->bounds;

                leftChildPtr->itemPtr = firstBoundsDataPtr->itemPtr;
                rightChildPtr->itemPtr = secondBoundsDataPtr->itemPtr;
            }
            leftChildPtr->nextPtr = rightChildPtr;
            rightChildPtr->nextPtr = nextPtr;
        } else {
            // Partition bounds data and find left/right bounds
            std::int64_t leftSize = 0;
            std::int64_t rightSize = 0;
            typename BoundsType<TItem>::Type leftBounds;
            typename BoundsType<TItem>::Type rightBounds;
            BoundsData** lower = begin;
            BoundsData** upper = end - 1;
            for (BoundsData** i = lower; i <= upper; ++i) {
                if (detail::hasLesserMedian((*i)->bounds, overallBounds, sortIndex)) {
                    if (leftSize == 0) {
                        leftBounds = (*i)->bounds;
                    } else {
                        leftBounds = leftBounds.hull((*i)->bounds);
                    }

                    ++leftSize;
                    if (i != lower) {
                        std::swap(*i, *lower);
                    }
                    ++lower;
                }
            }
            for (BoundsData** i = upper; i >= lower; --i) {
                if (detail::hasGreaterMedian((*i)->bounds, overallBounds, sortIndex)) {
                    if (rightSize == 0) {
                        rightBounds = (*i)->bounds;
                    } else {
                        rightBounds = rightBounds.hull((*i)->bounds);
                    }
                    ++rightSize;
                    if (i != upper) {
                        std::swap(*i, *upper);
                    }
                    --upper;
                }
            }
            while (leftSize < size / 2 && lower <= upper) {
                if (leftSize == 0) {
                    leftBounds = (*lower)->bounds;
                } else {
                    leftBounds = leftBounds.hull((*lower)->bounds);
                }
                ++leftSize;
                ++lower;
            }
            while (rightSize < size - size / 2 && lower <= upper) {
                if (rightSize == 0) {
                    rightBounds = (*upper)->bounds;
                } else {
                    rightBounds = rightBounds.hull((*upper)->bounds);
                }
                ++rightSize;
                --upper;
            }

            // Recurse into chid nodes
            std::int64_t nextSortIndex = (sortIndex + 1) % NumDimensions<TItem>::Value;
            
            detail::SpatialSetNode<TItem>* leftChildPtr = nodePtr + 1;
            detail::SpatialSetNode<TItem>* rightChildPtr = leftChildPtr + (2 * leftSize - 1);
            
            nodePtr->leftChildPtr = leftChildPtr;
            nodePtr->itemPtr = nullptr;
            
            init(leftChildPtr, rightChildPtr, begin, lower, leftBounds, nextSortIndex);
            init(rightChildPtr, nextPtr, lower, end, rightBounds, nextSortIndex);
        }
    }

    template <class TItem>
    void
    SpatialSet<TItem>::init() {
        std::int64_t numItems = _dataPtr->items.size();

        if (numItems == 0) {
            _dataPtr->nodes.clear();
            return;
        }

        // Initialize bounds data
        std::vector<BoundsData> boundsData(numItems);
        std::vector<BoundsData*> boundsDataPtrs(numItems);
        BoundsFunction<TItem> boundsFunction;
        typename BoundsType<TItem>::Type overallBounds;
        for (std::int64_t i = 0; i < numItems; ++i) {
            typename BoundsType<TItem>::Type bounds = boundsFunction(_dataPtr->items[i]);

            boundsData[i].bounds = bounds;
            boundsData[i].itemPtr = &(_dataPtr->items[i]);
            boundsDataPtrs[i] = &boundsData[i];
            if (i == 0) {
                overallBounds = bounds;
            } else {
                overallBounds = overallBounds.hull(bounds);
            }
        }

        // Recursively construct tree
        _dataPtr->nodes.resize(2 * numItems - 1);
        init(
            _dataPtr->nodes.data(),
            nullptr,
            &boundsDataPtrs.front(),
            &boundsDataPtrs.back() + 1,
            overallBounds,
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
    SpatialSet<TItem>::SpatialSet(const SpatialCollection<TDerived>& collection) :
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
    std::int64_t
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
    SpatialSet<TItem>::operator[](std::int64_t index) const {
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
            std::int64_t uniqueIndex,
            const TItem* firstItemPtr,
            double precision,
            std::vector<std::int64_t>& mapping
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
                            std::int64_t candidateItemIndex = candidateItemPtr - firstItemPtr;
                            assert(mapping[candidateItemIndex] == -1);
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
    SpatialList<TItem>
    SpatialSet<TItem>::uniqueItems(double precision) const {
        std::vector<std::int64_t> dummy;
        return uniqueItems(dummy, precision);
    }

    template <class TItem>
    inline
    SpatialList<TItem>
    SpatialSet<TItem>::uniqueItems(std::vector<std::int64_t>& mapping, double precision) const {
        if (isEmpty()) {
            mapping.clear();
            return SpatialList<TItem>();
        } else {
            // Initialize unique item mapping
            mapping.resize(size());
            std::fill(mapping.begin(), mapping.end(), -1);
            std::int64_t uniqueIndex = 0;

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
                std::int64_t itemIndex = itemPtr - firstItemPtr;
                if (mapping[itemIndex] == -1) {
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
            return SpatialList<TItem>(std::move(results));
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
