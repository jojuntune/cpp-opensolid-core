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
#include <OpenSolid/Core/SpatialSet/FilteredSet.hpp>
#include <OpenSolid/Core/SpatialSet/OverlapPredicate.hpp>
#include <OpenSolid/Core/SpatialSet/SetData.hpp>
#include <OpenSolid/Core/SpatialSet/SetNode.hpp>
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
    void
    SpatialSet<TElement>::init(
        spatialset::SetNode<TElement>* node,
        spatialset::SetNode<TElement>* next,
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
            spatialset::SetNode<TElement>* leftChild = node + 1;
            spatialset::SetNode<TElement>* rightChild = node + 2;

            node->leftChild = leftChild;
            node->element = nullptr;

            leftChild->leftChild = nullptr;
            rightChild->leftChild = nullptr;
            BoundsData* firstBoundsData = *begin;
            BoundsData* secondBoundsData = *(begin + 1);
            bool reversed = spatialset::hasLesserMedian(
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
            
            spatialset::SetNode<TElement>* leftChild = node + 1;
            spatialset::SetNode<TElement>* rightChild = leftChild + (2 * leftSize - 1);
            
            node->leftChild = leftChild;
            node->element = nullptr;
            
            init(leftChild, rightChild, begin, lower, leftBounds, nextSortIndex);
            init(rightChild, next, lower, end, rightBounds, nextSortIndex);
        }
    }

    template <class TElement>
    void
    SpatialSet<TElement>::init(const BoundsFunction<TElement>& boundsFunction) {
        std::int64_t numElements = _setData->elements.size();

        if (numElements == 0) {
            _setData->nodes.clear();
            return;
        }

        // Initialize bounds data
        std::vector<BoundsData> boundsData(numElements);
        std::vector<BoundsData*> boundsDataPointers(numElements);
        typename BoundsType<TElement>::Type overallBounds;
        for (std::int64_t i = 0; i < numElements; ++i) {
            typename BoundsType<TElement>::Type bounds = boundsFunction(_setData->elements[i]);

            boundsData[i].bounds = bounds;
            boundsData[i].element = &(_setData->elements[i]);
            boundsDataPointers[i] = &boundsData[i];
            if (i == 0) {
                overallBounds = bounds;
            } else {
                overallBounds = overallBounds.hull(bounds);
            }
        }

        // Recursively construct tree
        _setData->nodes.resize(2 * numElements - 1);
        init(
            _setData->nodes.data(),
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
    SpatialSet<TElement>::SpatialSet(const SpatialSet<TElement>& otherSet) :
        _setData(otherSet._setData) {
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(SpatialSet<TElement>&& otherSet) :
        _setData(std::move(otherSet._setData)) {
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(
        const std::vector<TElement>& elements,
        BoundsFunction<TElement> boundsFunction
    ) : _setData(new spatialset::SetData<TElement>()) {

        _setData->elements = elements;
        init(boundsFunction);
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(
        std::vector<TElement>&& elements,
        BoundsFunction<TElement> boundsFunction
    ) : _setData(new spatialset::SetData<TElement>()) {

        _setData->elements = std::move(elements);
        init(boundsFunction);
    }
    
    template <class TElement> template <class TIterator>
    inline
    SpatialSet<TElement>::SpatialSet(
        TIterator begin,
        TIterator end,
        BoundsFunction<TElement> boundsFunction
    ) : _setData(new spatialset::SetData<TElement>()) {

        _setData->elements = std::vector<TElement>(begin, end);
        init(boundsFunction);
    }

    template <class TElement>
    inline
    const spatialset::SetNode<TElement>*
    SpatialSet<TElement>::rootNode() const {
        if (empty()) {
            return nullptr;
        } else {
            return _setData->nodes.data();
        }
    }

    template <class TElement>
    inline
    typename std::vector<TElement>::const_iterator
    SpatialSet<TElement>::begin() const {
        if (empty()) {
            return typename std::vector<TElement>::const_iterator();
        } else {
            return _setData->elements.begin();
        }
    }

    template <class TElement>
    inline
    typename std::vector<TElement>::const_iterator
    SpatialSet<TElement>::end() const {
        if (empty()) {
            return typename std::vector<TElement>::const_iterator();
        } else {
            return _setData->elements.end();
        }
    }

    template <class TElement>
    inline
    const TElement&
    SpatialSet<TElement>::front() const {
        assert(!empty());
        return _setData->elements.front();
    }

    template <class TElement>
    inline
    const TElement&
    SpatialSet<TElement>::back() const {
        assert(!empty());
        return _setData->elements.back();
    }

    template <class TElement>
    inline
    const TElement&
    SpatialSet<TElement>::operator[](std::int64_t index) const {
        assert(!empty());
        return _setData->elements[index];
    }

    template <class TElement>
    inline
    void
    SpatialSet<TElement>::swap(SpatialSet<TElement>& otherSet) {
        _setData.swap(otherSet._setData);
    }
    
    template <class TElement>
    inline
    void
    SpatialSet<TElement>::operator=(const SpatialSet<TElement>& otherSet) {
        _setData = otherSet._setData;
    }
    
    template <class TElement>
    inline
    void
    SpatialSet<TElement>::operator=(SpatialSet<TElement>&& otherSet) {
        _setData = std::move(otherSet._setData);
    }
    
    template <class TElement>
    inline
    std::int64_t
    SpatialSet<TElement>::size() const {
        if (empty()) {
            return 0;
        } else {
            return _setData->elements.size();
        }
    }

    template <class TElement>
    inline
    bool
    SpatialSet<TElement>::empty() const {
        return !_setData || _setData->elements.empty();
    }

    template <class TElement>
    inline
    typename BoundsType<TElement>::Type
    SpatialSet<TElement>::bounds() const {
        if (empty()) {
            return typename BoundsType<TElement>::Type();
        } else {
            return _setData->nodes.front().bounds;
        }
    }

    template <class TElement>
    inline
    void
    SpatialSet<TElement>::clear() {
        if (!empty()) {
            _setData->elements.clear();
            _setData->nodes.clear();
        }
    }

    template <class TElement>
    inline
    spatialset::FilteredSet<TElement, spatialset::OverlapPredicate<TElement>>
    SpatialSet<TElement>::overlapping(
        const typename BoundsType<TElement>::Type& predicateBounds
    ) const {
        return spatialset::FilteredSet<TElement, spatialset::OverlapPredicate<TElement>>(
            *this,
            spatialset::OverlapPredicate<TElement>(predicateBounds)
        );
    }

    template <class TElement>
    inline
    spatialset::FilteredSet<TElement, spatialset::ContainPredicate<TElement>>
    SpatialSet<TElement>::containing(
        const typename BoundsType<TElement>::Type& predicateBounds
    ) const {
        return spatialset::FilteredSet<TElement, spatialset::ContainPredicate<TElement>>(
            *this,
            spatialset::ContainPredicate<TElement>(predicateBounds)
        );
    }

    template <class TElement> template <class TBoundsPredicate>
    inline
    spatialset::FilteredSet<TElement, TBoundsPredicate>
    SpatialSet<TElement>::filtered(TBoundsPredicate boundsPredicate) const {
        return spatialset::FilteredSet<TElement, TBoundsPredicate>(*this, boundsPredicate);
    }
    
    template <class TElement>
    std::ostream&
    operator<<(std::ostream& stream, const SpatialSet<TElement>& set) {
        stream << "{";
        if (!set.empty()) {
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
