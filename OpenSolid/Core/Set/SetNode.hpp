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

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>

#include <cstdint>
#include <new>
#include <vector>

namespace opensolid
{
    template <class TElement>
    class SetNode
    {
    private:
        void
        operator=(const SetNode<TElement>& other);
        
        const TElement* _element;
        typename BoundsType<TElement>::Type _bounds;
        int _splitDirection;
        double _splitValue;
        SetNode<TElement>* _leftChild;
        SetNode<TElement>* _rightChild;
        std::int64_t _size;
        
        void
        getLeaves(std::vector<SetNode<TElement>*>& leaves);
    public:
        explicit
        SetNode(const SetNode<TElement>& otherNode);
        
        SetNode(
            const TElement& element,
            const typename BoundsType<TElement>::Type& bounds
        );
        
        SetNode(
            const typename BoundsType<TElement>::Type& overallBounds,
            int splitDirection,
            double splitValue,
            SetNode<TElement>* leftChildNode,
            SetNode<TElement>* rightChildNode
        );
        
        SetNode(
            const typename BoundsType<TElement>::Type& overallBounds,
            SetNode<TElement>** begin,
            SetNode<TElement>** end
        );
        
        ~SetNode();
        
        const TElement*
        element() const;
        
        const typename BoundsType<TElement>::Type&
        bounds() const;
        
        int
        splitDirection() const;
        
        double
        splitValue() const;
        
        const SetNode<TElement>*
        leftChild() const;
        
        const SetNode<TElement>*
        rightChild() const;
        
        std::int64_t
        size() const;

        const SetNode<TElement>*
        nodeAtIndex(std::int64_t index) const;
        
        std::int64_t
        indexOf(
            const TElement& element,
            const typename BoundsType<TElement>::Type& elementBounds
        ) const;
        
        SetNode<TElement>*
        insert(
            const TElement& element,
            const typename BoundsType<TElement>::Type& elementBounds
        );

        SetNode<TElement>*
        erase(
            const TElement& element,
            const typename BoundsType<TElement>::Type& elementBounds
        );
    };
    
    template <class TElement>
    std::ostream&
    operator<<(std::ostream& stream, const SetNode<TElement>& node);
}

////////// Implementation //////////

namespace opensolid
{
    namespace detail
    {
        template <class TBounds>
        inline void
        split(const TBounds& bounds, int& splitDirection, double& splitValue) {
            typename TBounds::Index index;
            bounds.cwiseWidth().maxCoeff(&index);
            splitDirection = int(index);
            splitValue = bounds(index).median();
        }

        template <int iNumDimensions>
        inline void
        split(const Box<iNumDimensions>& box, int& splitDirection, double& splitValue) {
            split(box.vector(), splitDirection, splitValue);
        }
        
        inline void
        split(const Interval& interval, int& splitDirection, double& splitValue) {
            splitDirection = 0;
            splitValue = interval.median();
        }

        template <class TBounds>
        inline bool
        isCompatible(const TBounds& bounds, int splitDirection, double splitValue) {
            double lowerBound = bounds(splitDirection).lowerBound();
            double upperBound = bounds(splitDirection).upperBound();
            double splitRatio = (splitValue - lowerBound) / (upperBound - splitValue);
            double widthRatio = bounds.cwiseWidth().maxCoeff() / bounds(splitDirection).width();
            return splitRatio > 0.5 && splitRatio < 2 && widthRatio < 1.5;
        }

        template <int iNumDimensions>
        inline bool
        isCompatible(const Box<iNumDimensions>& box, int splitDirection, double splitValue) {
            return isCompatible(box.vector(), splitDirection, splitValue);
        }
    
        inline bool
        isCompatible(const Interval& interval, int splitDirection, double splitValue) {
            assert(splitDirection == 0);
            double splitRatio =
                (splitValue - interval.lowerBound()) / (interval.upperBound() - splitValue);
            return splitRatio > 0.5 && splitRatio < 2;
        }

        template <class TBounds>
        inline double
        median(const TBounds& bounds, int splitDirection) {
            return bounds(splitDirection).median();
        }

        template <int iNumDimensions>
        inline double
        median(const Box<iNumDimensions>& box, int splitDirection) {
            return box(splitDirection).median();
        }

        inline double
        median(const Interval& bounds, int splitDirection) {
            assert(splitDirection == 0);
            return bounds.median();
        }

        template <class TBounds>
        inline bool
        hasLesserMedian(
            const TBounds& firstBounds,
            const TBounds& secondBounds,
            int splitDirection
        ) {
            Interval difference = firstBounds(splitDirection) - secondBounds(splitDirection);
            return difference.upperBound() < -difference.lowerBound();
        }

        template <int iNumDimensions>
        inline bool
        hasLesserMedian(
            const Box<iNumDimensions>& firstBox,
            const Box<iNumDimensions>& secondBox,
            int splitDirection
        ) {
            return hasLesserMedian(firstBox.vector(), secondBox.vector(), splitDirection);
        }

        inline bool
        hasLesserMedian(
            const Interval& firstInterval,
            const Interval& secondInterval,
            int splitDirection
        ) {
            assert(splitDirection == 0);
            Interval difference = firstInterval - secondInterval;
            return difference.upperBound() < -difference.lowerBound();
        }

        template <class TBounds>
        inline bool
        hasGreaterMedian(
            const TBounds& firstBounds,
            const TBounds& secondBounds,
            int splitDirection
        ) {
            Interval difference = firstBounds(splitDirection) - secondBounds(splitDirection);
            return difference.upperBound() > -difference.lowerBound();
        }

        template <int iNumDimensions>
        inline bool
        hasGreaterMedian(
            const Box<iNumDimensions>& firstBox,
            const Box<iNumDimensions>& secondBox,
            int splitDirection
        ) {
            return hasGreaterMedian(firstBox.vector(), secondBox.vector(), splitDirection);
        }

        inline bool
        hasGreaterMedian(
            const Interval& firstInterval,
            const Interval& secondInterval,
            int splitDirection
        ) {
            assert(splitDirection == 0);
            Interval difference = firstInterval - secondInterval;
            return difference.upperBound() > -difference.lowerBound();
        }
    }
    
    template <class TElement>
    void
    SetNode<TElement>::getLeaves(std::vector<SetNode<TElement>*>& leaves) {
        if (_element) {
            assert(!_leftChild && !_rightChild);
            leaves.push_back(this);
        } else {
            assert(_leftChild && _rightChild);
            _leftChild->getLeaves(leaves);
            _rightChild->getLeaves(leaves);
            _leftChild = nullptr;
            _rightChild = nullptr;
            delete this;
        }
    }
    
    template <class TElement>
    inline
    SetNode<TElement>::SetNode(const SetNode<TElement>& otherNode) :
        _bounds(otherNode._bounds),
        _splitDirection(otherNode._splitDirection),
        _splitValue(otherNode._splitValue),
        _size(otherNode._size) {
        if (otherNode._element) {
            assert(!otherNode._leftChild && !otherNode._rightChild);
            _element = new TElement(*otherNode._element);
            _leftChild = nullptr;
            _rightChild = nullptr;
        } else {
            assert(otherNode._leftChild && otherNode._rightChild);
            _element = nullptr;
            _leftChild = new SetNode<TElement>(*otherNode._leftChild);
            _rightChild = new SetNode<TElement>(*otherNode._rightChild);
        }
    }
    
    template <class TElement>
    inline
    SetNode<TElement>::SetNode(
        const TElement& element,
        const typename BoundsType<TElement>::Type& bounds
    ) : _element(new TElement(element)),
        _bounds(bounds),
        _leftChild(nullptr),
        _rightChild(nullptr),
        _size(1) {
    }
    
    template <class TElement>
    inline
    SetNode<TElement>::SetNode(
        const typename BoundsType<TElement>::Type& overallBounds,
        int splitDirection,
        double splitValue,
        SetNode<TElement>* leftChild,
        SetNode<TElement>* rightChild
    ) : _element(nullptr),
        _bounds(overallBounds),
        _splitDirection(splitDirection),
        _splitValue(splitValue),
        _leftChild(leftChild),
        _rightChild(rightChild),
        _size(leftChild->_size + rightChild->_size) {
    }
    
    template <class TElement>
    SetNode<TElement>::SetNode(
        const typename BoundsType<TElement>::Type& overallBounds,
        SetNode<TElement>** begin,
        SetNode<TElement>** end
    ) {
        _element = nullptr;
        _bounds = overallBounds;
        _size = end - begin;
        detail::split(_bounds, _splitDirection, _splitValue);
        if (_size == 2) {
            _leftChild = *begin;
            _rightChild = *(begin + 1);
            double rightMedian = detail::median(_rightChild->_bounds, _splitDirection);
            double leftMedian = detail::median(_leftChild->_bounds, _splitDirection);
            if (rightMedian < leftMedian) {
                std::swap(_leftChild, _rightChild);
            }
        } else {
            std::int64_t leftSize = 0;
            std::int64_t rightSize = 0;
            typename BoundsType<TElement>::Type leftBounds;
            typename BoundsType<TElement>::Type rightBounds;
            SetNode<TElement>** lower = begin;
            SetNode<TElement>** upper = end - 1;
            for (SetNode<TElement>** i = lower; i <= upper; ++i) {
                if (detail::hasLesserMedian((*i)->_bounds, _bounds, _splitDirection)) {
                    if (leftSize == 0) {
                        leftBounds = (*i)->_bounds;
                    } else {
                        leftBounds = leftBounds.hull((*i)->_bounds);
                    }
                    ++leftSize;
                    if (i != lower) {
                        std::swap(*i, *lower);
                    }
                    ++lower;
                }
            }
            for (SetNode<TElement>** i = upper; i >= lower; --i) {
                if (detail::hasGreaterMedian((*i)->_bounds, _bounds, _splitDirection)) {
                    if (rightSize == 0) {
                        rightBounds = (*i)->_bounds;
                    } else {
                        rightBounds = rightBounds.hull((*i)->_bounds);
                    }
                    ++rightSize;
                    if (i != upper) {
                        std::swap(*i, *upper);
                    }
                    --upper;
                }
            }
            while (leftSize < _size / 2 && lower <= upper) {
                if (leftSize == 0) {
                    leftBounds = (*lower)->_bounds;
                } else {
                    leftBounds = leftBounds.hull((*lower)->_bounds);
                }
                ++leftSize;
                ++lower;
            }
            while (rightSize < _size - _size / 2 && lower <= upper) {
                if (rightSize == 0) {
                    rightBounds = (*upper)->_bounds;
                } else {
                    rightBounds = rightBounds.hull((*upper)->_bounds);
                }
                ++rightSize;
                --upper;
            }
            if (leftSize == 1) {
                _leftChild = *begin;
            } else {
                _leftChild = new SetNode<TElement>(leftBounds, begin, lower);
            }
            if (rightSize == 1) {
                _rightChild = *lower;
            } else {
                _rightChild = new SetNode<TElement>(rightBounds, lower, end);
            }
        }
    }
    
    template <class TElement>
    inline
    SetNode<TElement>::~SetNode() {
        if (_element) {
            assert(!_leftChild && !_rightChild);
            delete _element;
        } else if (_leftChild && _rightChild) {
            delete _leftChild;
            delete _rightChild;
        }
    }
    
    template <class TElement>
    inline const TElement*
    SetNode<TElement>::element() const {
        return _element;
    }
    
    template <class TElement>
    inline const typename BoundsType<TElement>::Type&
    SetNode<TElement>::bounds() const {
        return _bounds;
    }
    
    template <class TElement>
    inline int
    SetNode<TElement>::splitDirection() const {
        return _splitDirection;
    }
    
    template <class TElement>
    inline double
    SetNode<TElement>::splitValue() const {
        return _splitValue;
    }
        
    template <class TElement>
    inline const SetNode<TElement>*
    SetNode<TElement>::leftChild() const {
        return _leftChild;
    }
    
    template <class TElement>
    inline const SetNode<TElement>*
    SetNode<TElement>::rightChild() const {
        return _rightChild;
    }
    
    template <class TElement>
    inline std::int64_t
    SetNode<TElement>::size() const {
        return _size;
    }

    template <class TElement>
    const SetNode<TElement>*
    SetNode<TElement>::nodeAtIndex(std::int64_t index) const {
        assert(index >= 0 && index < size());
        if (element()) {
            return this;
        } else if (index < leftChild()->size()) {
            return leftChild()->nodeAtIndex(index);
        } else {
            return rightChild()->nodeAtIndex(index - leftChild()->size());
        }
    }

    template <class TElement>
    std::int64_t
    SetNode<TElement>::indexOf(
        const TElement& element,
        const typename BoundsType<TElement>::Type& elementBounds
    ) const {
        if (bounds().overlaps(elementBounds)) {
            if (this->element()) {
                if (element == *this->element()) {
                    return 0;
                }
            } else {
                double mid = detail::median(elementBounds, splitDirection());
                if (mid - splitValue() <= Zero()) {
                    std::int64_t leftIndex = leftChild()->indexOf(element, elementBounds);
                    if (leftIndex != -1) {
                        return leftIndex;
                    }
                }
                if (mid - splitValue() >= Zero()) {
                    std::int64_t rightIndex = rightChild()->indexOf(element, elementBounds);
                    if (rightIndex != -1) {
                        return leftChild()->size() + rightIndex;
                    }
                }
            }
        }
        return -1;
    }
    
    template <class TElement>
    SetNode<TElement>*
    SetNode<TElement>::insert(
        const TElement& element,
        const typename BoundsType<TElement>::Type& elementBounds
    ) {
        typename BoundsType<TElement>::Type overallBounds = _bounds.hull(elementBounds);
        if (_element) {
            assert(!_leftChild && !_rightChild);
            SetNode<TElement>* nodes[2];
            nodes[0] = this;
            nodes[1] = new SetNode<TElement>(element, elementBounds);
            return new SetNode<TElement>(overallBounds, nodes, nodes + 2);
        } else if (detail::isCompatible(overallBounds, _splitDirection, _splitValue)) {
            assert(_leftChild && _rightChild);
            double mid = detail::median(elementBounds, _splitDirection);
            if (mid < _splitValue) {
                _leftChild = _leftChild->insert(element, elementBounds);
            } else if (mid > _splitValue) {
                _rightChild = _rightChild->insert(element, elementBounds);
            } else if (_leftChild->_size < _rightChild->_size) {
                _leftChild = _leftChild->insert(element, elementBounds);
            } else {
                _rightChild = _rightChild->insert(element, elementBounds);
            }
            _bounds = overallBounds;
            ++_size;
            return this;
        } else {
            assert(_leftChild && _rightChild);
            std::vector<SetNode<TElement>*> nodes;
            nodes.reserve(_size + 1);
            _leftChild->getLeaves(nodes);
            _rightChild->getLeaves(nodes);
            nodes.push_back(new SetNode<TElement>(element, elementBounds));
            return new(this) SetNode<TElement>(overallBounds, &nodes.front(), &nodes.back() + 1);
        }
    }

    template <class TElement>
    SetNode<TElement>*
    SetNode<TElement>::erase(
        const TElement& element,
        const typename BoundsType<TElement>::Type& elementBounds
    ) {
        if (!_bounds.overlaps(elementBounds)) {
            return this;
        } else if (_element) {
            assert(!_leftChild && !_rightChild);
            if (*_element == element) {
                delete this;
                return nullptr;
            } else {
                return this;
            }
        } else {
            assert(_leftChild && _rightChild);
            double mid = detail::median(elementBounds, _splitDirection);
            if (mid - _splitValue <= Zero()) {
                _leftChild = _leftChild->erase(element, elementBounds);
            }
            if (mid - _splitValue >= Zero()) {
                _rightChild = _rightChild->erase(element, elementBounds);
            }
            if (!_leftChild) {
                SetNode<TElement>* result = _rightChild;
                _rightChild = nullptr;
                delete this;
                return result;
            } else if (!_rightChild) {
                SetNode<TElement>* result = _leftChild;
                _leftChild = nullptr;
                delete this;
                return result;
            } else {
                typename BoundsType<TElement>::Type overallBounds =
                    _leftChild->_bounds.hull(_rightChild->_bounds);
                if (detail::isCompatible(overallBounds, _splitDirection, _splitValue)) {
                    _bounds = overallBounds;
                    _size = _leftChild->size() + _rightChild->size();
                    return this;
                } else {
                    std::vector<SetNode<TElement>*> nodes;
                    nodes.reserve(_leftChild->_size + _rightChild->_size);
                    _leftChild->getLeaves(nodes);
                    _rightChild->getLeaves(nodes);
                    return new(this) SetNode<TElement>(
                        overallBounds,
                        &nodes.front(),
                        &nodes.back() + 1
                    );
                }
            }
        }
    }

    template <class TElement>
    std::ostream&
    operator<<(std::ostream& stream, const SetNode<TElement>& node) {
        stream << "{";
        if (node.element()) {
            stream << *node.element();
        } else {
            stream << *node.leftChild();
            stream << ",";
            stream << *node.rightChild();
        }
        stream << "}";
        return stream;
    }
}
