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

#include <OpenSolid/Core/SpatialSet.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/SpatialCollection.hpp>
#include <OpenSolid/Core/SpatialSet/ContainPredicate.hpp>
#include <OpenSolid/Core/SpatialSet/FilteredSpatialSet.hpp>
#include <OpenSolid/Core/SpatialSet/OverlapPredicate.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSetData.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSetNode.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSubset.hpp>
#include <OpenSolid/Core/TolerantComparator.hpp>
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
        detail::SpatialSetNode<TItem>* node,
        detail::SpatialSetNode<TItem>* next,
        BoundsData** begin,
        BoundsData** end,
        typename BoundsType<TItem>::Type& overallBounds,
        std::int64_t sortIndex
    ) {
        node->bounds = overallBounds;
        node->next = next;
        std::int64_t size = end - begin;
        if (size == 1) {
            // Leaf node
            node->leftChild = nullptr;
            node->item = (*begin)->item;
        } else if (size == 2) {
            // Node with two leaf children
            detail::SpatialSetNode<TItem>* leftChild = node + 1;
            detail::SpatialSetNode<TItem>* rightChild = node + 2;

            node->leftChild = leftChild;
            node->item = nullptr;

            leftChild->leftChild = nullptr;
            rightChild->leftChild = nullptr;
            BoundsData* firstBoundsData = *begin;
            BoundsData* secondBoundsData = *(begin + 1);
            bool reversed = detail::hasLesserMedian(
                secondBoundsData->bounds,
                firstBoundsData->bounds,
                sortIndex
            );
            if (reversed) {
                leftChild->bounds = secondBoundsData->bounds;
                rightChild->bounds = firstBoundsData->bounds;

                leftChild->item = secondBoundsData->item;
                rightChild->item = firstBoundsData->item;
            } else {
                leftChild->bounds = firstBoundsData->bounds;
                rightChild->bounds = secondBoundsData->bounds;

                leftChild->item = firstBoundsData->item;
                rightChild->item = secondBoundsData->item;
            }
            leftChild->next = rightChild;
            rightChild->next = next;
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
            
            detail::SpatialSetNode<TItem>* leftChild = node + 1;
            detail::SpatialSetNode<TItem>* rightChild = leftChild + (2 * leftSize - 1);
            
            node->leftChild = leftChild;
            node->item = nullptr;
            
            init(leftChild, rightChild, begin, lower, leftBounds, nextSortIndex);
            init(rightChild, next, lower, end, rightBounds, nextSortIndex);
        }
    }

    template <class TItem>
    void
    SpatialSet<TItem>::init() {
        std::int64_t numItems = _data->items.size();

        if (numItems == 0) {
            _data->nodes.clear();
            return;
        }

        // Initialize bounds data
        std::vector<BoundsData> boundsData(numItems);
        std::vector<BoundsData*> boundsDataPointers(numItems);
        BoundsFunction<TItem> boundsFunction;
        typename BoundsType<TItem>::Type overallBounds;
        for (std::int64_t i = 0; i < numItems; ++i) {
            typename BoundsType<TItem>::Type bounds = boundsFunction(_data->items[i]);

            boundsData[i].bounds = bounds;
            boundsData[i].item = &(_data->items[i]);
            boundsDataPointers[i] = &boundsData[i];
            if (i == 0) {
                overallBounds = bounds;
            } else {
                overallBounds = overallBounds.hull(bounds);
            }
        }

        // Recursively construct tree
        _data->nodes.resize(2 * numItems - 1);
        init(
            _data->nodes.data(),
            nullptr,
            &boundsDataPointers.front(),
            &boundsDataPointers.back() + 1,
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
        _data(other._data) {
    }

    template <class TItem>
    inline
    SpatialSet<TItem>::SpatialSet(SpatialSet<TItem>&& other) :
        _data(std::move(other._data)) {
    }

    template <class TItem>
    inline
    SpatialSet<TItem>::SpatialSet(const std::vector<TItem>& items) :
        _data(new detail::SpatialSetData<TItem>()) {

        _data->items = items;
        init();
    }

    template <class TItem>
    inline
    SpatialSet<TItem>::SpatialSet(std::vector<TItem>&& items) :
        _data(new detail::SpatialSetData<TItem>()) {

        _data->items = std::move(items);
        init();
    }

    template <class TItem> template <class TDerived>
    inline
    SpatialSet<TItem>::SpatialSet(const SpatialCollection<TDerived>& collection) :
        _data(new detail::SpatialSetData<TItem>()) {

        _data->items = std::vector<TItem>(collection.derived());
        init();        
    }
    
    template <class TItem> template <class TIterator>
    inline
    SpatialSet<TItem>::SpatialSet(TIterator begin, TIterator end) :
        _data(new detail::SpatialSetData<TItem>()) {

        _data->items = std::vector<TItem>(begin, end);
        init();
    }

    template <class TItem>
    inline
    const detail::SpatialSetNode<TItem>*
    SpatialSet<TItem>::rootNode() const {
        if (isEmpty()) {
            return nullptr;
        } else {
            return _data->nodes.data();
        }
    }

    template <class TItem>
    inline
    typename std::vector<TItem>::const_iterator
    SpatialSet<TItem>::begin() const {
        if (isEmpty()) {
            return typename std::vector<TItem>::const_iterator();
        } else {
            return _data->items.begin();
        }
    }

    template <class TItem>
    inline
    typename std::vector<TItem>::const_iterator
    SpatialSet<TItem>::end() const {
        if (isEmpty()) {
            return typename std::vector<TItem>::const_iterator();
        } else {
            return _data->items.end();
        }
    }

    template <class TItem>
    inline
    bool
    SpatialSet<TItem>::isEmpty() const {
        return !_data || _data->items.empty();
    }
    
    template <class TItem>
    inline
    std::int64_t
    SpatialSet<TItem>::size() const {
        if (isEmpty()) {
            return 0;
        } else {
            return _data->items.size();
        }
    }

    template <class TItem>
    inline
    typename BoundsType<TItem>::Type
    SpatialSet<TItem>::bounds() const {
        if (isEmpty()) {
            return typename BoundsType<TItem>::Type();
        } else {
            return _data->nodes.front().bounds;
        }
    }

    template <class TItem>
    inline
    const TItem&
    SpatialSet<TItem>::operator[](std::int64_t index) const {
        assert(!isEmpty());
        return _data->items[index];
    }

    template <class TItem>
    inline
    void
    SpatialSet<TItem>::swap(SpatialSet<TItem>& other) {
        _data.swap(other._data);
    }
    
    template <class TItem>
    inline
    void
    SpatialSet<TItem>::operator=(const SpatialSet<TItem>& other) {
        _data = other._data;
    }
    
    template <class TItem>
    inline
    void
    SpatialSet<TItem>::operator=(SpatialSet<TItem>&& other) {
        _data = std::move(other._data);
    }

    template <class TItem>
    inline
    void
    SpatialSet<TItem>::clear() {
        if (!isEmpty()) {
            _data->items.clear();
            _data->nodes.clear();
        }
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
            BoundsFunction<TItem> boundsFunction;
            detail::OverlapPredicate<TItem> overlapPredicate(boundsFunction(item), precision);
            detail::FilteredSpatialSetIterator<TItem, detail::OverlapPredicate<TItem>> filteredIterator(
                rootNode(),
                &overlapPredicate
            );
            detail::FilteredSpatialSetIterator<TItem, detail::OverlapPredicate<TItem>> filteredEnd(
                nullptr,
                &overlapPredicate
            );
            TolerantComparator<TItem> itemComparator(precision);
            while (filteredIterator != filteredEnd) {
                if (itemComparator(item, *filteredIterator)) {
                    return begin() + (&(*filteredIterator) - _data->items.data());
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
        nextLeafNode(const SpatialSetNode<TItem>* leafNode) {
            assert(leafNode);
            assert(leafNode->item);
            const SpatialSetNode<TItem>* node = leafNode->next;
            if (!node) {
                return node;
            }
            while (node->leftChild) {
                node = node->leftChild;
            }
            return node;
        }

        template <class TItem>
        void
        markDuplicateItems(
            const SpatialSetNode<TItem>* anchorNode,
            const TItem* firstItem,
            const TolerantComparator<TItem>& itemComparator,
            std::vector<const TItem*>& itemMap
        ) {
            // Ensure anchor node is a valid leaf node
            assert(anchorNode);
            assert(anchorNode->item);

            const TItem* anchorItem = anchorNode->item;
            std::int64_t anchorIndex = anchorItem - firstItem;
            itemMap[anchorIndex] = anchorItem;
            const SpatialSetNode<TItem>* candidateNode = anchorNode->next;
            while (candidateNode && candidateNode->bounds.overlaps(anchorNode->bounds)) {
                if (candidateNode->leftChild) {
                    // Internal node: descend into left child
                    candidateNode = candidateNode->leftChild;
                } else {
                    // Leaf node: check for duplicate items, then move to next node
                    if (itemComparator(*anchorItem, *candidateNode->item)) {
                        std::int64_t candidateIndex = candidateNode->item - firstItem;
                        assert(itemMap[candidateIndex] == nullptr);
                        itemMap[candidateIndex] = anchorItem;
                    }
                    candidateNode = candidateNode->next;
                }
            }
        }

        template <class TItem, class TVisitor>
        void
        visitUniqueItems(
            const SpatialSetNode<TItem>* rootNode,
            double precision,
            const TItem* firstItem,
            std::int64_t numItems,
            const TVisitor& visitor
        ) {
            std::vector<const TItem*> itemMap(numItems);
            std::fill(itemMap.begin(), itemMap.end(), nullptr);

            const SpatialSetNode<TItem>* node = rootNode;
            while (node->leftChild) {
                node = node->leftChild;
            }

            TolerantComparator<TItem> itemComparator(precision);
            do {
                std::int64_t itemIndex = node->item - firstItem;
                if (itemMap[itemIndex] == nullptr) {
                    markDuplicateItems(node, firstItem, itemComparator, itemMap);
                }
                visitor(node->item, itemMap[itemIndex]);
                node = nextLeafNode(node);
            } while (node);
        }
    }

    template <class TItem>
    inline
    detail::SpatialSubset<TItem>
    SpatialSet<TItem>::uniqueItems(double precision) const {
        if (isEmpty()) {
            return detail::SpatialSubset<TItem>();
        } else {
            std::vector<const TItem*> items;
            auto visitor = [&items] (
                const TItem* item,
                const TItem* anchorItem
            ) {
                if (item == anchorItem) {
                    items.push_back(item);
                }
            };
            detail::visitUniqueItems(
                rootNode(),
                precision,
                &_data->items.front(),
                size(),
                visitor
            );
            return detail::SpatialSubset<TItem>(*this, std::move(items));
        }
    }

    template <class TItem>
    inline
    std::vector<std::int64_t>
    SpatialSet<TItem>::uniqueMapping(double precision) const {
        if (isEmpty()) {
            return std::vector<std::int64_t>();
        } else {
            const TItem* firstItem = &_data->items.front();
            std::vector<std::int64_t> results(size());
            auto visitor = [&results, firstItem] (
                const TItem* item,
                const TItem* anchorItem
            ) {
                std::int64_t itemIndex = item - firstItem;
                std::int64_t anchorIndex = anchorItem - firstItem;
                results[itemIndex] = anchorIndex;
            };
            detail::visitUniqueItems(
                rootNode(),
                precision,
                firstItem,
                size(),
                visitor
            );
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
