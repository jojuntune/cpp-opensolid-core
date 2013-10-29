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
#include <OpenSolid/Core/Iterable.hpp>
#include <OpenSolid/Core/SpatialSet/ContainPredicate.hpp>
#include <OpenSolid/Core/SpatialSet/FilteredSpatialSet.hpp>
#include <OpenSolid/Core/SpatialSet/OverlapPredicate.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSetData.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSetNode.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSubset.hpp>
#include <OpenSolid/Core/Transformable.hpp>

#include <algorithm>

namespace opensolid
{
    template <class TElement>
    inline
    typename std::vector<TElement>::const_iterator
    SpatialSet<TElement>::beginImpl() const {
        if (this->isEmpty()) {
            return typename std::vector<TElement>::const_iterator();
        } else {
            return _data->elements.begin();
        }
    }

    template <class TElement>
    inline
    typename std::vector<TElement>::const_iterator
    SpatialSet<TElement>::endImpl() const {
        if (this->isEmpty()) {
            return typename std::vector<TElement>::const_iterator();
        } else {
            return _data->elements.end();
        }
    }

    template <class TElement>
    inline
    bool
    SpatialSet<TElement>::isEmptyImpl() const {
        return !_data || _data->elements.empty();
    }
    
    template <class TElement>
    inline
    std::int64_t
    SpatialSet<TElement>::sizeImpl() const {
        if (this->isEmpty()) {
            return 0;
        } else {
            return _data->elements.size();
        }
    }

    namespace detail
    {
        template <class TBounds>
        inline bool
        hasLesserMedian(
            const TBounds& firstBounds,
            const TBounds& secondBounds,
            std::int64_t index
        ) {
            Interval difference = firstBounds(index) - secondBounds(index);
            return difference.upperBound() < -difference.lowerBound();
        }

        inline bool
        hasLesserMedian(
            Interval firstInterval,
            Interval secondInterval,
            std::int64_t index
        ) {
            assert(index == 0);
            Interval difference = firstInterval - secondInterval;
            return difference.upperBound() < -difference.lowerBound();
        }

        template <class TBounds>
        inline bool
        hasGreaterMedian(
            const TBounds& firstBounds,
            const TBounds& secondBounds,
            std::int64_t index
        ) {
            Interval difference = firstBounds(index) - secondBounds(index);
            return difference.upperBound() > -difference.lowerBound();
        }

        inline bool
        hasGreaterMedian(
            Interval firstInterval,
            Interval secondInterval,
            std::int64_t index
        ) {
            assert(index == 0);
            Interval difference = firstInterval - secondInterval;
            return difference.upperBound() > -difference.lowerBound();
        }
    }

    template <class TElement>
    void
    SpatialSet<TElement>::init(
        detail::SpatialSetNode<TElement>* node,
        detail::SpatialSetNode<TElement>* next,
        BoundsData** begin,
        BoundsData** end,
        typename BoundsType<TElement>::Type& overallBounds,
        std::int64_t sortIndex
    ) {
        node->bounds = overallBounds;
        node->next = next;
        std::int64_t size = end - begin;
        if (size == 1) {
            // Leaf node
            node->leftChild = nullptr;
            node->element = (*begin)->element;
        } else if (size == 2) {
            // Node with two leaf children
            detail::SpatialSetNode<TElement>* leftChild = node + 1;
            detail::SpatialSetNode<TElement>* rightChild = node + 2;

            node->leftChild = leftChild;
            node->element = nullptr;

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

                leftChild->element = secondBoundsData->element;
                rightChild->element = firstBoundsData->element;
            } else {
                leftChild->bounds = firstBoundsData->bounds;
                rightChild->bounds = secondBoundsData->bounds;

                leftChild->element = firstBoundsData->element;
                rightChild->element = secondBoundsData->element;
            }
            leftChild->next = rightChild;
            rightChild->next = next;
        } else {
            // Partition bounds data and find left/right bounds
            std::int64_t leftSize = 0;
            std::int64_t rightSize = 0;
            typename BoundsType<TElement>::Type leftBounds;
            typename BoundsType<TElement>::Type rightBounds;
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
            std::int64_t nextSortIndex = (sortIndex + 1) % NumDimensions<TElement>::Value;
            
            detail::SpatialSetNode<TElement>* leftChild = node + 1;
            detail::SpatialSetNode<TElement>* rightChild = leftChild + (2 * leftSize - 1);
            
            node->leftChild = leftChild;
            node->element = nullptr;
            
            init(leftChild, rightChild, begin, lower, leftBounds, nextSortIndex);
            init(rightChild, next, lower, end, rightBounds, nextSortIndex);
        }
    }

    template <class TElement>
    void
    SpatialSet<TElement>::init(const BoundsFunction<TElement>& boundsFunction) {
        std::int64_t numElements = _data->elements.size();

        if (numElements == 0) {
            _data->nodes.clear();
            return;
        }

        // Initialize bounds data
        std::vector<BoundsData> boundsData(numElements);
        std::vector<BoundsData*> boundsDataPointers(numElements);
        typename BoundsType<TElement>::Type overallBounds;
        for (std::int64_t i = 0; i < numElements; ++i) {
            typename BoundsType<TElement>::Type bounds = boundsFunction(_data->elements[i]);

            boundsData[i].bounds = bounds;
            boundsData[i].element = &(_data->elements[i]);
            boundsDataPointers[i] = &boundsData[i];
            if (i == 0) {
                overallBounds = bounds;
            } else {
                overallBounds = overallBounds.hull(bounds);
            }
        }

        // Recursively construct tree
        _data->nodes.resize(2 * numElements - 1);
        init(
            _data->nodes.data(),
            nullptr,
            &boundsDataPointers.front(),
            &boundsDataPointers.back() + 1,
            overallBounds,
            0
        );
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet() {
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(const SpatialSet<TElement>& other) :
        _data(other._data) {
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(SpatialSet<TElement>&& other) :
        _data(std::move(other._data)) {
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(
        const std::vector<TElement>& elements,
        BoundsFunction<TElement> boundsFunction
    ) : _data(new detail::SpatialSetData<TElement>()) {

        _data->elements = elements;
        init(boundsFunction);
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(
        std::vector<TElement>&& elements,
        BoundsFunction<TElement> boundsFunction
    ) : _data(new detail::SpatialSetData<TElement>()) {

        _data->elements = std::move(elements);
        init(boundsFunction);
    }
    
    template <class TElement> template <class TIterator>
    inline
    SpatialSet<TElement>::SpatialSet(
        TIterator begin,
        TIterator end,
        BoundsFunction<TElement> boundsFunction
    ) : _data(new detail::SpatialSetData<TElement>()) {

        _data->elements = std::vector<TElement>(begin, end);
        init(boundsFunction);
    }

    template <class TElement>
    inline
    const detail::SpatialSetNode<TElement>*
    SpatialSet<TElement>::rootNode() const {
        if (this->isEmpty()) {
            return nullptr;
        } else {
            return _data->nodes.data();
        }
    }

    template <class TElement>
    inline
    typename std::vector<TElement>::const_iterator
    SpatialSet<TElement>::begin() const {
        return beginImpl();
    }

    template <class TElement>
    inline
    typename std::vector<TElement>::const_iterator
    SpatialSet<TElement>::end() const {
        return endImpl();
    }

    template <class TElement>
    inline
    const TElement&
    SpatialSet<TElement>::first() const {
        assert(!this->isEmpty());
        return _data->elements.front();
    }

    template <class TElement>
    inline
    const TElement&
    SpatialSet<TElement>::last() const {
        assert(!this->isEmpty());
        return _data->elements.back();
    }

    template <class TElement>
    inline
    const TElement&
    SpatialSet<TElement>::operator[](std::int64_t index) const {
        assert(!this->isEmpty());
        return _data->elements[index];
    }

    template <class TElement>
    inline
    void
    SpatialSet<TElement>::swap(SpatialSet<TElement>& other) {
        _data.swap(other._data);
    }
    
    template <class TElement>
    inline
    void
    SpatialSet<TElement>::operator=(const SpatialSet<TElement>& other) {
        _data = other._data;
    }
    
    template <class TElement>
    inline
    void
    SpatialSet<TElement>::operator=(SpatialSet<TElement>&& other) {
        _data = std::move(other._data);
    }

    template <class TElement>
    inline
    typename BoundsType<TElement>::Type
    SpatialSet<TElement>::bounds() const {
        if (this->isEmpty()) {
            return typename BoundsType<TElement>::Type();
        } else {
            return _data->nodes.front().bounds;
        }
    }

    template <class TElement>
    inline
    void
    SpatialSet<TElement>::clear() {
        if (!this->isEmpty()) {
            _data->elements.clear();
            _data->nodes.clear();
        }
    }

    template <class TElement>
    inline
    detail::FilteredSpatialSet<TElement, detail::OverlapPredicate<TElement>>
    SpatialSet<TElement>::overlapping(
        const typename BoundsType<TElement>::Type& predicateBounds
    ) const {
        return detail::FilteredSpatialSet<TElement, detail::OverlapPredicate<TElement>>(
            *this,
            detail::OverlapPredicate<TElement>(predicateBounds)
        );
    }

    template <class TElement>
    inline
    detail::FilteredSpatialSet<TElement, detail::ContainPredicate<TElement>>
    SpatialSet<TElement>::containing(
        const typename BoundsType<TElement>::Type& predicateBounds
    ) const {
        return detail::FilteredSpatialSet<TElement, detail::ContainPredicate<TElement>>(
            *this,
            detail::ContainPredicate<TElement>(predicateBounds)
        );
    }

    template <class TElement> template <class TBoundsPredicate>
    inline
    detail::FilteredSpatialSet<TElement, TBoundsPredicate>
    SpatialSet<TElement>::filtered(TBoundsPredicate boundsPredicate) const {
        return detail::FilteredSpatialSet<TElement, TBoundsPredicate>(*this, boundsPredicate);
    }

    namespace detail
    {
        template <class TElement>
        const SpatialSetNode<TElement>*
        nextLeafNode(const SpatialSetNode<TElement>* leafNode) {
            assert(leafNode);
            assert(leafNode->element);
            const SpatialSetNode<TElement>* node = leafNode->next;
            if (!node) {
                return node;
            }
            while (node->leftChild) {
                node = node->leftChild;
            }
            return node;
        }

        template <class TElement, class TElementComparator>
        void
        markDuplicateElements(
            const SpatialSetNode<TElement>* anchorNode,
            const TElement* firstElement,
            const TElementComparator& elementComparator,
            std::vector<const TElement*>& elementMap
        ) {
            // Ensure anchor node is a valid leaf node
            assert(anchorNode);
            assert(anchorNode->element);

            const TElement* anchorElement = anchorNode->element;
            std::int64_t anchorIndex = anchorElement - firstElement;
            elementMap[anchorIndex] = anchorElement;
            const SpatialSetNode<TElement>* candidateNode = anchorNode->next;
            while (candidateNode && candidateNode->bounds.overlaps(anchorNode->bounds)) {
                if (candidateNode->leftChild) {
                    // Internal node: descend into left child
                    candidateNode = candidateNode->leftChild;
                } else {
                    // Leaf node: check for duplicate elements, then move to next node
                    if (elementComparator(*anchorElement, *candidateNode->element)) {
                        std::int64_t candidateIndex = candidateNode->element - firstElement;
                        assert(elementMap[candidateIndex] == nullptr);
                        elementMap[candidateIndex] = anchorElement;
                    }
                    candidateNode = candidateNode->next;
                }
            }
        }

        template <class TElement, class TElementComparator, class TVisitor>
        void
        visitUniqueElements(
            const SpatialSetNode<TElement>* rootNode,
            const TElement* firstElement,
            std::int64_t numElements,
            const TElementComparator& elementComparator,
            const TVisitor& visitor
        ) {
            std::vector<const TElement*> elementMap(numElements);
            std::fill(elementMap.begin(), elementMap.end(), nullptr);

            const SpatialSetNode<TElement>* node = rootNode;
            while (node->leftChild) {
                node = node->leftChild;
            }
            do {
                std::int64_t elementIndex = node->element - firstElement;
                if (elementMap[elementIndex] == nullptr) {
                    markDuplicateElements(node, firstElement, elementComparator, elementMap);
                }
                visitor(node->element, elementMap[elementIndex]);
            } while (node = nextLeafNode(node));
        }
    }

    template <class TElement> template <class TElementComparator>
    detail::SpatialSubset<TElement>
    SpatialSet<TElement>::uniqueElements(TElementComparator elementComparator) const {
        if (isEmpty()) {
            return detail::SpatialSubset<TElement>();
        } else {
            std::vector<const TElement*> elements;
            auto visitor = [&elements] (
                const TElement* element,
                const TElement* anchorElement
            ) {
                if (element == anchorElement) {
                    elements.push_back(element);
                }
            };
            detail::visitUniqueElements(
                rootNode(),
                &_data->elements.front(),
                size(),
                elementComparator,
                visitor
            );
            return detail::SpatialSubset<TElement>(std::move(elements));
        }
    }

    template <class TElement> template <class TElementComparator>
    std::vector<std::int64_t>
    SpatialSet<TElement>::uniqueMapping(TElementComparator elementComparator) const {
        if (isEmpty()) {
            return std::vector<std::int64_t>();
        } else {
            const TElement* firstElement = &_data->elements.front();
            std::vector<std::int64_t> results(size());
            auto visitor = [&results, firstElement] (
                const TElement* element,
                const TElement* anchorElement
            ) {
                std::int64_t elementIndex = element - firstElement;
                std::int64_t anchorIndex = anchorElement - firstElement;
                results[elementIndex] = anchorIndex;
            };
            detail::visitUniqueElements(
                rootNode(),
                firstElement,
                size(),
                elementComparator,
                visitor
            );
            return results;
        }
    }
    
    template <class TElement>
    std::ostream&
    operator<<(std::ostream& stream, const SpatialSet<TElement>& set) {
        stream << "{";
        if (!set.isEmpty()) {
            std::for_each(
                set.begin(),
                set.end() - 1,
                [&stream] (const TElement& element) {
                    stream << element << ",";
                }
            );
            stream << set.back();
        }
        stream << "}";
        return stream;
    }

    template <class TElement>
    SpatialSet<TElement>
    ScalingFunction<SpatialSet<TElement>>::operator()(
        const SpatialSet<TElement>& set,
        double scale
    ) const {
        std::vector<TElement> scaledElements(set.size());
        std::transform(
            set.begin(),
            set.end(),
            scaledElements.begin(),
            [scale] (const TElement& element) -> TElement {
                return Transformable<TElement>::scaling(element, scale);
            }
        );
        return SpatialSet<TElement>(std::move(scaledElements));
    }

    template <class TElement> template <class TVector>
    SpatialSet<TElement>
    TranslationFunction<SpatialSet<TElement>>::operator()(
        const SpatialSet<TElement>& set,
        const EigenBase<TVector>& vector
    ) const {
        std::vector<TElement> translatedElements(set.size());
        std::transform(
            set.begin(),
            set.end(),
            translatedElements.begin(),
            [&vector] (const TElement& element) -> TElement {
                return Transformable<TElement>::translation(element, vector.derived());
            }
        );
        return SpatialSet<TElement>(std::move(translatedElements));
    }

    template <class TElement, int iNumResultDimensions> template <class TMatrix>
    SpatialSet<typename ChangeDimensions<TElement, iNumResultDimensions>::Type>
    TransformationFunction<SpatialSet<TElement>, iNumResultDimensions>::operator()(
        const SpatialSet<TElement>& set,
        const EigenBase<TMatrix>& matrix
    ) const {
        typedef typename ChangeDimensions<TElement, iNumResultDimensions>::Type TransformedElement;
        std::vector<TransformedElement> transformedElements(set.size());
        std::transform(
            set.begin(),
            set.end(),
            transformedElements.begin(),
            [&matrix] (const TElement& element) -> TransformedElement {
                return Transformable<TElement>::transformation(element, matrix.derived());
            }
        );
        return SpatialSet<TransformedElement>(std::move(transformedElements));
    }

    template <class TElement, int iNumResultDimensions>
    SpatialSet<typename ChangeDimensions<TElement, iNumResultDimensions>::Type>
    MorphingFunction<SpatialSet<TElement>, iNumResultDimensions>::operator()(
        const SpatialSet<TElement>& set,
        const Function<iNumResultDimensions, NumDimensions<TElement>::Value>& function
    ) const {
        typedef typename ChangeDimensions<TElement, iNumResultDimensions>::Type MorphedElement;
        std::vector<MorphedElement> morphedElements(set.size());
        std::transform(
            set.begin(),
            set.end(),
            morphedElements.begin(),
            [&function] (const TElement& element) -> MorphedElement {
                return Transformable<TElement>::morphing(element, function);
            }
        );
        return SpatialSet<MorphedElement>(std::move(morphedElements));
    }
}
