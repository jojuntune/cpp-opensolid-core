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
        inline
        std::int64_t
        greaterOrEqualPowerOfTwo(std::int64_t num) {
            --num;
            num |= num >> 1;
            num |= num >> 2;
            num |= num >> 4;
            num |= num >> 8;
            num |= num >> 16;
            num |= num >> 32;
            return (num + 1);
        }

        inline
        std::int64_t
        leftElementCount(std::int64_t elementCount) {
            std::int64_t fullElementCount = spatialset::greaterOrEqualPowerOfTwo(elementCount);
            std::int64_t gapSize = 2 * (fullElementCount - elementCount);

            if (gapSize <= fullElementCount / 2) {
                return fullElementCount / 2;
            } else {
                return elementCount - fullElementCount / 4;
            }
        }

        inline
        std::pair<Subtree, Subtree>
        childSubtrees(const Subtree& subtree) {
            std::pair<Subtree, Subtree> results;

            std::int64_t leftElementCount = spatialset::leftElementCount(subtree.elementCount);
            std::int64_t rightElementCount = subtree.elementCount - leftElementCount;

            results.first.nodeIndex = 2 * subtree.nodeIndex + 1;
            results.first.nodeCount = 2 * leftElementCount - 1;
            results.first.startElementIndex = subtree.startElementIndex;
            results.first.elementCount = leftElementCount;

            results.second.nodeIndex = 2 * subtree.nodeIndex + 2;
            results.second.nodeCount = 2 * rightElementCount - 1;
            results.second.startElementIndex = subtree.startElementIndex + leftElementCount;
            results.second.elementCount = rightElementCount;

            return results;
        }

        template <class TBounds, class TVector>
        std::int64_t
        sortIndex(const TBounds& overallBounds, const TVector& maxElementWidths) {
            double maxOverallWidth = 0.0;
            double maxWidthRatio = 0.0;
            std::int64_t maxOverallWidthIndex = -1;
            std::int64_t maxWidthRatioIndex = -1;

            for (std::int64_t i = 0; i < overallBounds.size(); ++i) {
                double overallWidth = overallBounds(i).width();
                double maxElementWidth = maxElementWidths(i);

                if (maxElementWidth > Zero()) {
                    double widthRatio = overallWidth / maxElementWidth;
                    if (widthRatio > maxWidthRatio) {
                        maxWidthRatio = widthRatio;
                        maxWidthRatioIndex = i;
                    }
                } else {
                    if (overallWidth > maxOverallWidth) {
                        maxOverallWidth = overallWidth;
                        maxOverallWidthIndex = i;
                    }
                }
            }
            if (maxOverallWidthIndex >= 0) {
                // At least one direction was found with a zero maximum element width,
                // so ratio is not an appropriate metric
                return maxOverallWidthIndex;
            } else {
                return maxWidthRatioIndex;
            }
        }

        template <class TBounds>
        TBounds
        sortBoundsData(
            typename std::vector<BoundsData<TBounds>>::iterator begin,
            typename std::vector<BoundsData<TBounds>>::iterator end,
            std::int64_t leftElementCount
        ) {
            typedef Matrix<double, TBounds::RowsAtCompileTime, TBounds::ColsAtCompileTime> TVector;

            TBounds overallBounds = begin->bounds;
            TVector maxElementWidths = begin->bounds.cwiseWidth();
            std::for_each(
                begin + 1,
                end,
                [&overallBounds, &maxElementWidths] (
                    const BoundsData<TBounds>& boundsData
                ) -> void {
                    overallBounds = overallBounds.hull(boundsData.bounds);
                    maxElementWidths = maxElementWidths.cwiseMax(boundsData.bounds.cwiseWidth());
                }
            );
            std::int64_t sortIndex = spatialset::sortIndex(overallBounds, maxElementWidths);
            std::nth_element(
                begin,
                begin + leftElementCount,
                end,
                [sortIndex] (
                    const BoundsData<TBounds>& firstBoundsData,
                    const BoundsData<TBounds>& secondBoundsData
                ) -> bool {
                    double firstMedian = firstBoundsData.bounds(sortIndex).median();
                    double secondMedian = secondBoundsData.bounds(sortIndex).median();
                    return firstMedian < secondMedian;
                }
            );

            return overallBounds;
        }

        Subtree
        tree(std::int64_t numElements) {
            Subtree result;
            result.nodeIndex = 0;
            result.nodeCount = 2 * numElements - 1;
            result.startElementIndex = 0;
            result.elementCount = numElements;
            return result;
        }
    }

    template <class TElement>
    void
    SpatialSet<TElement>::init(
        std::vector<spatialset::BoundsData<typename BoundsType<TElement>::Type>>& boundsData,
        const spatialset::Subtree& subtree
    ) {
        assert(subtree.nodeCount > 0 && subtree.elementCount > 0);
        assert((subtree.nodeCount == 1) == (subtree.elementCount == 1));

        if (subtree.nodeCount == 1) {
            // Leaf node: get bounds from corresponding element
            _nodeBounds[subtree.nodeIndex] = boundsData[subtree.startElementIndex].bounds;
        } else {
            std::pair<spatialset::Subtree, spatialset::Subtree> childSubtrees =
                spatialset::childSubtrees(subtree);

            auto begin = boundsData.begin() + subtree.startElementIndex;
            auto end = begin + subtree.elementCount;
            _nodeBounds[subtree.nodeIndex] =
                spatialset::sortBoundsData<typename BoundsType<TElement>::Type>(
                    begin,
                    end,
                    childSubtrees.first.elementCount
                );

            init(boundsData, childSubtrees.first);
            init(boundsData, childSubtrees.second);
        }
    }

    template <class TElement>
    void
    SpatialSet<TElement>::init(const BoundsFunction<TElement>& boundsFunction) {
        std::int64_t numElements = _elements.size();

        if (numElements == 0) {
            _nodeBounds.clear();
            return;
        }

        // Initialize temporary bounds data array
        std::vector<spatialset::BoundsData<typename BoundsType<TElement>::Type>> boundsData(
            numElements
        );
        for (std::int64_t index = 0; index < numElements; ++index) {
            boundsData[index].bounds = boundsFunction(_elements[index]);
            boundsData[index].elementIndex = index;
        }

        spatialset::Subtree tree = spatialset::tree(numElements);
        _nodeBounds.resize(tree.nodeCount);
        init(boundsData, tree);

        // Use bounds data array to re-sort elements
        std::vector<TElement> elements(numElements);
        for (std::int64_t index = 0; index < numElements; ++index) {
            elements[index] = std::move(_elements[boundsData[index].elementIndex]);
        }
        _elements.swap(elements);
    }

    template <class TElement> template <class TPredicate, class TVisitor>
    void
    SpatialSet<TElement>::visit(
        const spatialset::Subtree& subtree,
        const TPredicate& predicate,
        const TVisitor& visitor
    ) const {
        if (predicate(_nodeBounds[subtree.nodeIndex])) {
            if (subtree.nodeCount == 1) {
                const_cast<TVisitor&>(visitor)(_elements[subtree.startElementIndex]);
            } else {
                std::pair<spatialset::Subtree, spatialset::Subtree> childSubtrees =
                    spatialset::childSubtrees(subtree);
                visit(childSubtrees.first, predicate, visitor);
                visit(childSubtrees.second, predicate, visitor);
            }
        }
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet() {
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(const SpatialSet<TElement>& otherSet) :
        _elements(otherSet._elements),
        _nodeBounds(otherSet._nodeBounds) {
    }

    template <class TElement>
    inline
    SpatialSet<TElement>::SpatialSet(SpatialSet<TElement>&& otherSet) :
        _elements(std::move(otherSet._elements)),
        _nodeBounds(std::move(otherSet._nodeBounds)) {
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
    ) : _elements(elements) {

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
    SpatialSet<TElement>::operator[](std::int64_t index) const {
        return _elements[index];
    }

    template <class TElement>
    inline
    void
    SpatialSet<TElement>::swap(SpatialSet<TElement>& otherSet) {
        _elements.swap(otherSet._elements);
        _nodeBounds.swap(otherSet._nodeBounds);
    }
    
    template <class TElement>
    inline
    void
    SpatialSet<TElement>::operator=(const SpatialSet<TElement>& otherSet) {
        _elements = otherSet._elements;
        _nodeBounds = otherSet._nodeBounds;
    }
    
    template <class TElement>
    inline
    void
    SpatialSet<TElement>::operator=(SpatialSet<TElement>&& otherSet) {
        _elements = std::move(otherSet._elements);
        _nodeBounds = std::move(otherSet._nodeBounds);
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
            return _nodeBounds.front();
        }
    }

    template <class TElement>
    void
    SpatialSet<TElement>::clear() {
        _elements.clear();
        _nodeBounds.clear();
    }

    template <class TElement>
    std::vector<TElement>
    SpatialSet<TElement>::overlapping(const typename BoundsType<TElement>::Type& bounds) const {
        std::vector<TElement> results;
        auto predicate = [&bounds] (const typename BoundsType<TElement>::Type& elementBounds) -> bool {
            return bounds.overlaps(elementBounds);
        };
        auto visitor = [&results] (const TElement& element) {
            results.push_back(element);
        };
        visit(spatialset::tree(size()), predicate, visitor);
        return results;
    }

    namespace spatialset
    {
        template <class TElement>
        void
        print(std::ostream& stream, const SpatialSet<TElement>& set, const Subtree& subtree) {
            stream << "{";
            if (subtree.nodeCount == 1) {
                stream << set[subtree.startElementIndex];
            } else {
                std::pair<Subtree, Subtree> childSubtrees = spatialset::childSubtrees(subtree);
                print(stream, set, childSubtrees.first);
                print(stream, set, childSubtrees.second);
            }
            stream << "}";
        }
    }
    
    template <class TElement>
    std::ostream&
    operator<<(std::ostream& stream, const SpatialSet<TElement>& set) {
        spatialset::print(stream, set, spatialset::tree(set.size()));
        return stream;
    }

    // template <class TElement>
    // struct ScalingFunction<SpatialSet<TElement>>
    // {
    //     SpatialSet<TElement>
    //     operator()(const SpatialSet<TElement>& set, double scale) const;
    // };

    // template <class TElement>
    // struct TranslationFunction<SpatialSet<TElement>>
    // {
    //     template <class TVector>
    //     SpatialSet<TElement>
    //     operator()(const SpatialSet<TElement>& set, const EigenBase<TVector>& vector) const;
    // };

    // template <class TElement, int iNumResultDimensions>
    // struct TransformationFunction<SpatialSet<TElement>, iNumResultDimensions>
    // {
    //     template <class TMatrix>
    //     SpatialSet<typename ChangeDimensions<TElement, iNumResultDimensions>::Type>
    //     operator()(const SpatialSet<TElement>& set, const EigenBase<TMatrix>& matrix) const;
    // };

    // template <class TElement, int iNumResultDimensions>
    // struct MorphingFunction<SpatialSet<TElement>, iNumResultDimensions>
    // {
    //     SpatialSet<typename ChangeDimensions<TElement, iNumResultDimensions>::Type>
    //     operator()(
    //         const SpatialSet<TElement>& set,
    //         const Function<iNumResultDimensions, NumDimensions<TElement>::Value>& function
    //     ) const;
    // };
}
