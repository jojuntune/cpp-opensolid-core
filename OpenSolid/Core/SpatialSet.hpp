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
#include <OpenSolid/Core/Transformable.hpp>

#include <algorithm>

namespace opensolid
{
    namespace spatialset
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
    typename SpatialSet<TElement>::Node*
    SpatialSet<TElement>::init(
        Node* node,
        BoundsData** begin,
        BoundsData** end,
        typename BoundsType<TElement>::Type& overallBounds,
        std::int64_t sortIndex
    ) {
        node->bounds = overallBounds;
        std::int64_t size = end - begin;
        if (size == 1) {
            // Leaf node
            node->left = nullptr;
            node->right = (*begin)->element;
            return node + 1;
        } else if (size == 2) {
            // Node with two leaf children
            Node* leftNode = node + 1;
            Node* rightNode = node + 2;
            node->left = leftNode;
            node->right = rightNode;
            leftNode->left = nullptr;
            rightNode->left = nullptr;
            BoundsData* firstBoundsData = *begin;
            BoundsData* secondBoundsData = *(begin + 1);
            bool reversed = spatialset::hasLesserMedian(
                secondBoundsData->bounds,
                firstBoundsData->bounds,
                sortIndex
            );
            if (reversed) {
                leftNode->bounds = secondBoundsData->bounds;
                rightNode->bounds = firstBoundsData->bounds;

                leftNode->right = secondBoundsData->element;
                rightNode->right = firstBoundsData->element;
            } else {
                leftNode->bounds = firstBoundsData->bounds;
                rightNode->bounds = secondBoundsData->bounds;

                leftNode->right = firstBoundsData->element;
                rightNode->right = secondBoundsData->element;
            }
            return node + 3;
        } else {
            // Partition bounds data and find left/right bounds
            std::int64_t leftSize = 0;
            std::int64_t rightSize = 0;
            typename BoundsType<TElement>::Type leftBounds;
            typename BoundsType<TElement>::Type rightBounds;
            BoundsData** lower = begin;
            BoundsData** upper = end - 1;
            for (BoundsData** i = lower; i <= upper; ++i) {
                if (spatialset::hasLesserMedian((*i)->bounds, overallBounds, sortIndex)) {
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
                if (spatialset::hasGreaterMedian((*i)->bounds, overallBounds, sortIndex)) {
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
            Node* leftNode = node + 1;
            Node* rightNode = init(leftNode, begin, lower, leftBounds, nextSortIndex);
            Node* nextNode = init(rightNode, lower, end, rightBounds, nextSortIndex);

            // Store child indices and return next available node index to parent
            node->left = leftNode;
            node->right = rightNode;
            return nextNode;
        }
    }

    template <class TElement>
    void
    SpatialSet<TElement>::init(const BoundsFunction<TElement>& boundsFunction) {
        std::int64_t numElements = _elements.size();

        if (numElements == 0) {
            _nodes.clear();
            return;
        }

        // Initialize bounds data
        std::vector<BoundsData> boundsData(numElements);
        std::vector<BoundsData*> boundsDataPointers(numElements);
        typename BoundsType<TElement>::Type overallBounds;
        for (std::int64_t i = 0; i < numElements; ++i) {
            typename BoundsType<TElement>::Type bounds = boundsFunction(_elements[i]);

            boundsData[i].bounds = bounds;
            boundsData[i].element = &_elements[i];
            boundsDataPointers[i] = &boundsData[i];
            overallBounds = i == 0 ? bounds : overallBounds.hull(bounds);
        }

        // Recursively construct tree
        _nodes.resize(2 * numElements - 1);
        Node* endNode = init(
            _nodes.data(),
            &boundsDataPointers.front(),
            &boundsDataPointers.back() + 1,
            overallBounds,
            0
        );
        assert(endNode == &_nodes.back() + 1);
    }

    template <class TElement>
    inline
    const typename SpatialSet<TElement>::Node*
    SpatialSet<TElement>::rootNode() const {
        return _nodes.data();
    }

    template <class TElement> template <class TPredicate, class TVisitor>
    void
    SpatialSet<TElement>::visit(
        const Node* node,
        const TPredicate& predicate,
        const TVisitor& visitor
    ) const {
        if (predicate(node->bounds)) {
            if (!node->left) {
                const_cast<TVisitor&>(visitor)(*((const TElement*) node->right));
            } else {
                visit((const Node*) node->left, predicate, visitor);
                visit((const Node*) node->right, predicate, visitor);
            }
        }
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet() {
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(const SpatialSet<TElement>& otherSet) {
        copy(otherSet);
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(SpatialSet<TElement>&& otherSet) :
        _elements(std::move(otherSet._elements)),
        _nodes(std::move(otherSet._nodes)) {
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(
        const std::vector<TElement>& elements,
        BoundsFunction<TElement> boundsFunction
    ) : _elements(elements) {

        init(boundsFunction);
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(
        std::vector<TElement>&& elements,
        BoundsFunction<TElement> boundsFunction
    ) : _elements(std::move(elements)) {

        init(boundsFunction);
    }
    
    template <class TElement> template <class TIterator>
    inline
    SpatialSet<TElement>::SpatialSet(
        TIterator begin,
        TIterator end,
        BoundsFunction<TElement> boundsFunction
    ) : _elements(begin, end) {

        init(boundsFunction);
    }

    template <class TElement>
    inline
    typename SpatialSet<TElement>::Iterator
    SpatialSet<TElement>::begin() const {
        return _elements.begin();
    }

    template <class TElement>
    inline
    typename SpatialSet<TElement>::Iterator
    SpatialSet<TElement>::end() const {
        return _elements.end();
    }

    template <class TElement>
    inline
    const TElement&
    SpatialSet<TElement>::front() const {
        assert(!isEmpty());
        return _elements.front();
    }

    template <class TElement>
    inline
    const TElement&
    SpatialSet<TElement>::back() const {
        assert(!isEmpty());
        return _elements.back();
    }

    template <class TElement>
    inline
    const TElement&
    SpatialSet<TElement>::operator[](std::int64_t index) const {
        return _elements[index];
    }

    template <class TElement>
    inline
    void
    SpatialSet<TElement>::swap(SpatialSet<TElement>& otherSet) {
        _elements.swap(otherSet._elements);
        _nodes.swap(otherSet._nodes);
    }
    
    template <class TElement>
    inline
    void
    SpatialSet<TElement>::operator=(const SpatialSet<TElement>& otherSet) {
        copy(otherSet);
    }
    
    template <class TElement>
    inline
    void
    SpatialSet<TElement>::operator=(SpatialSet<TElement>&& otherSet) {
        _elements = std::move(otherSet._elements);
        _nodes = std::move(otherSet._nodes);
    }
    
    template <class TElement>
    inline
    std::int64_t
    SpatialSet<TElement>::size() const {
        return _elements.size();
    }

    template <class TElement>
    inline
    bool
    SpatialSet<TElement>::isEmpty() const {
        return _elements.empty();
    }

    template <class TElement>
    inline
    typename BoundsType<TElement>::Type
    SpatialSet<TElement>::bounds() const {
        if (isEmpty()) {
            return typename BoundsType<TElement>::Type();
        } else {
            return _nodes.front().bounds;
        }
    }

    template <class TElement>
    void
    SpatialSet<TElement>::clear() {
        _elements.clear();
        _nodes.clear();
    }


    template <class TElement> template <class TVisitor>
    void
    SpatialSet<TElement>::forEachOverlapping(
        const typename BoundsType<TElement>::Type& predicateBounds,
        const TVisitor& visitor
    ) const {
        if (isEmpty()) {
            return;
        }
        visit(
            rootNode(),
            [&predicateBounds] (const typename BoundsType<TElement>::Type& elementBounds) -> bool {
                return elementBounds.overlaps(predicateBounds);
            },
            visitor
        );
    }

    template <class TElement>
    std::vector<TElement>
    SpatialSet<TElement>::overlapping(
        const typename BoundsType<TElement>::Type& predicateBounds
    ) const {
        std::vector<TElement> results;
        forEachOverlapping(
            predicateBounds,
            [&results] (const TElement& element) -> void {
                results.push_back(element);
            }
        );
        return results;
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
        return SpatialSet<TElement>(scaledElements);
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
        return SpatialSet<TElement>(translatedElements);
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
        return SpatialSet<TransformedElement>(transformedElements);
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
        return SpatialSet<MorphedElement>(morphedElements);
    }
}
