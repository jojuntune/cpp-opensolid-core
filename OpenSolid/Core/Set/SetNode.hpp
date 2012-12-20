/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Core/Interval.hpp>

#include <new>
#include <vector>

namespace opensolid
{
    template <class Type>
    class SetNode
    {
    private:
        void operator=(const SetNode<Type>& other);
        
        const Type* _object;
        typename Bounds<Type>::Type _bounds;
        int _split_direction;
        double _split_value;
        SetNode<Type>* _left;
        SetNode<Type>* _right;
        std::size_t _size;
        
        void getLeaves(std::vector<SetNode<Type>*>& leaves);
    public:
        explicit SetNode(const SetNode<Type>& other);
        
        SetNode(const Type& object, const typename Bounds<Type>::Type& bounds);
        
        SetNode(
            const typename Bounds<Type>::Type& overall_bounds,
            int split_direction,
            double split_value,
            SetNode<Type>* left,
            SetNode<Type>* right
        );
        
        SetNode(
            const typename Bounds<Type>::Type& overall_bounds,
            SetNode<Type>** begin,
            SetNode<Type>** end
        );
        
        ~SetNode();
        
        const Type* object() const;
        const typename Bounds<Type>::Type& bounds() const;
        int splitDirection() const;
        double splitValue() const;
        const SetNode<Type>* left() const;
        const SetNode<Type>* right() const;
        std::size_t size() const;
        
        SetNode<Type>* insert(
            const Type& argument,
            const typename Bounds<Type>::Type& argument_bounds
        );

        SetNode<Type>* erase(
            const Type& argument,
            const typename Bounds<Type>::Type& argument_bounds
        );
    };
}

////////// Implementation //////////

namespace opensolid
{
    namespace
    {
        template <class BoundsType>
        inline void split(const BoundsType& bounds, int& split_direction, double& split_value) {
            typename BoundsType::Index index;
            bounds.cwiseWidth().maxCoeff(&index);
            split_direction = int(index);
            split_value = bounds(index).median();
        }
        
        inline void split(const Interval& bounds, int& split_direction, double& split_value) {
            split_direction = 0;
            split_value = bounds.median();
        }

        template <class BoundsType>
        inline bool compatible(const BoundsType& bounds, int split_direction, double split_value) {
            double lower = bounds(split_direction).lower();
            double upper = bounds(split_direction).upper();
            double split_ratio = (split_value - lower) / (upper - split_value);
            double width_ratio = bounds.cwiseWidth().maxCoeff() / (upper - lower);
            return split_ratio > 0.5 && split_ratio < 2 && width_ratio < 1.5;
        }
    
        inline bool compatible(const Interval& bounds, int split_direction, double split_value) {
            assert(split_direction == 0);
            double split_ratio = (split_value - bounds.lower()) / (bounds.upper() - split_value);
            return split_ratio > 0.5 && split_ratio < 2;
        }

        template <class BoundsType>
        inline double median(const BoundsType& bounds, int split_direction) {
            return bounds(split_direction).median();
        }

        inline double median(const Interval& bounds, int split_direction) {
            assert(split_direction == 0);
            return bounds.median();
        }

        template <class BoundsType>
        inline bool lesserMedian(
            const BoundsType& first_bounds,
            const BoundsType& second_bounds,
            int split_direction
        ) {
            Interval difference = first_bounds(split_direction) - second_bounds(split_direction);
            return difference.upper() < -difference.lower();
        }

        inline bool lesserMedian(
            const Interval& first_bounds,
            const Interval& second_bounds,
            int split_direction
        ) {
            assert(split_direction == 0);
            Interval difference = first_bounds - second_bounds;
            return difference.upper() < -difference.lower();
        }

        template <class BoundsType>
        inline bool greaterMedian(
            const BoundsType& first_bounds,
            const BoundsType& second_bounds,
            int split_direction
        ) {
            Interval difference = first_bounds(split_direction) - second_bounds(split_direction);
            return difference.upper() > -difference.lower();
        }

        inline bool greaterMedian(
            const Interval& first_bounds,
            const Interval& second_bounds,
            int split_direction
        ) {
            assert(split_direction == 0);
            Interval difference = first_bounds - second_bounds;
            return difference.upper() > -difference.lower();
        }
    }
    
    template <class Type>
    void SetNode<Type>::getLeaves(std::vector<SetNode<Type>*>& leaves) {
        if (_object) {
            assert(!_left && !_right);
            leaves.push_back(this);
        } else {
            assert(_left && _right);
            _left->getLeaves(leaves);
            _right->getLeaves(leaves);
            _left = nullptr;
            _right = nullptr;
            delete this;
        }
    }
    
    template <class Type>
    inline SetNode<Type>::SetNode(const SetNode<Type>& other) :
        _bounds(other._bounds),
        _split_direction(other._split_direction),
        _split_value(other._split_value),
        _size(other._size) {
        if (other._object) {
            assert(!other._left && !other._right);
            _object = new Type(*other._object);
            _left = nullptr;
            _right = nullptr;
        } else {
            assert(other._left && other._right);
            _object = nullptr;
            _left = new SetNode<Type>(*other._left);
            _right = new SetNode<Type>(*other._right);
        }
    }
    
    template <class Type>
    inline SetNode<Type>::SetNode(const Type& object, const typename Bounds<Type>::Type& bounds) :
        _object(new Type(object)),
        _bounds(bounds),
        _left(nullptr),
        _right(nullptr),
        _size(1) {}
    
    template <class Type>
    inline SetNode<Type>::SetNode(
        const typename Bounds<Type>::Type& overall_bounds,
        int split_direction,
        double split_value,
        SetNode<Type>* left,
        SetNode<Type>* right
    ) : _object(nullptr),
        _bounds(overall_bounds),
        _split_direction(split_direction),
        _split_value(split_value),
        _left(left),
        _right(right),
        _size(left->_size + right->_size) {}
    
    template <class Type>
    SetNode<Type>::SetNode(
        const typename Bounds<Type>::Type& overall_bounds,
        SetNode<Type>** begin,
        SetNode<Type>** end
    ) {
        _object = nullptr;
        _bounds = overall_bounds;
        _size = end - begin;
        split(_bounds, _split_direction, _split_value);
        if (_size == 2) {
            _left = *begin;
            _right = *(begin + 1);
            double right_median = median(_right->_bounds, _split_direction);
            double left_median = median(_left->_bounds, _split_direction);
            if (right_median < left_median) {std::swap(_left, _right);}
        } else {
            std::size_t left_size = 0;
            std::size_t right_size = 0;
            typename Bounds<Type>::Type left_bounds;
            typename Bounds<Type>::Type right_bounds;
            SetNode<Type>** lower = begin;
            SetNode<Type>** upper = end - 1;
            for (SetNode<Type>** i = lower; i <= upper; ++i) {
                if (lesserMedian((*i)->_bounds, _bounds, _split_direction)) {
                    if (left_size == 0) {
                        left_bounds = (*i)->_bounds;
                    } else {
                        left_bounds = left_bounds.hull((*i)->_bounds);
                    }
                    ++left_size;
                    if (i != lower) {std::swap(*i, *lower);}
                    ++lower;
                }
            }
            for (SetNode<Type>** i = upper; i >= lower; --i) {
                if (greaterMedian((*i)->_bounds, _bounds, _split_direction)) {
                    if (right_size == 0) {
                        right_bounds = (*i)->_bounds;
                    } else {
                        right_bounds = right_bounds.hull((*i)->_bounds);
                    }
                    ++right_size;
                    if (i != upper) {std::swap(*i, *upper);}
                    --upper;
                }
            }
            while (left_size < _size / 2 && lower <= upper) {
                if (left_size == 0) {
                    left_bounds = (*lower)->_bounds;
                } else {
                    left_bounds = left_bounds.hull((*lower)->_bounds);
                }
                ++left_size;
                ++lower;
            }
            while (right_size < _size - _size / 2 && lower <= upper) {
                if (right_size == 0) {
                    right_bounds = (*upper)->_bounds;
                } else {
                    right_bounds = right_bounds.hull((*upper)->_bounds);
                }
                ++right_size;
                --upper;
            }
            if (left_size == 1) {
                _left = *begin;
            } else {
                _left = new SetNode<Type>(left_bounds, begin, lower);
            }
            if (right_size == 1) {
                _right = *lower;
            } else {
                _right = new SetNode<Type>(right_bounds, lower, end);
            }
        }
    }
    
    template <class Type>
    inline SetNode<Type>::~SetNode() {
        if (_object) {
            assert(!_left && !_right);
            delete _object;
        } else if (_left && _right) {
            delete _left;
            delete _right;
        }
    }
    
    template <class Type>
    inline const Type* SetNode<Type>::object() const {return _object;}
    
    template <class Type>
    inline const typename Bounds<Type>::Type& SetNode<Type>::bounds() const {return _bounds;}
    
    template <class Type>
    inline int SetNode<Type>::splitDirection() const {return _split_direction;}
    
    template <class Type>
    inline double SetNode<Type>::splitValue() const {return _split_value;}
        
    template <class Type>
    inline const SetNode<Type>* SetNode<Type>::left() const {return _left;}
    
    template <class Type>
    inline const SetNode<Type>* SetNode<Type>::right() const {return _right;}
    
    template <class Type>
    inline std::size_t SetNode<Type>::size() const {return _size;}
    
    template <class Type>
    SetNode<Type>* SetNode<Type>::insert(
        const Type& argument,
        const typename Bounds<Type>::Type& argument_bounds
    ) {
        typename Bounds<Type>::Type overall_bounds = _bounds.hull(argument_bounds);
        if (_object) {
            assert(!_left && !_right);
            SetNode<Type>* nodes[2] = {this, new SetNode<Type>(argument, argument_bounds)};
            return new SetNode<Type>(overall_bounds, nodes, nodes + 2);
        } else if (compatible(overall_bounds, _split_direction, _split_value)) {
            assert(_left && _right);
            double mid = median(argument_bounds, _split_direction);
            if (mid < _split_value) {
                _left = _left->insert(argument, argument_bounds);
            } else if (mid > _split_value) {
                _right = _right->insert(argument, argument_bounds);
            } else if (_left->_size < _right->_size) {
                _left = _left->insert(argument, argument_bounds);
            } else {
                _right = _right->insert(argument, argument_bounds);
            }
            _bounds = overall_bounds;
            ++_size;
            return this;
        } else {
            assert(_left && _right);
            std::vector<SetNode<Type>*> nodes;
            nodes.reserve(_size + 1);
            _left->getLeaves(nodes);
            _right->getLeaves(nodes);
            nodes.push_back(new SetNode<Type>(argument, argument_bounds));
            return new(this) SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1);
        }
    }

    template <class Type>
    SetNode<Type>* SetNode<Type>::erase(
        const Type& argument,
        const typename Bounds<Type>::Type& argument_bounds
    ) {
        if (!_bounds.overlaps(argument_bounds)) {
            return this;
        } else if (_object) {
            assert(!_left && !_right);
            if (*_object == argument) {
                delete this;
                return nullptr;
            } else {
                return this;
            }
        } else {
            assert(_left && _right);
            double mid = median(argument_bounds, _split_direction);
            if (mid - _split_value <= Zero()) {
                _left = _left->erase(argument, argument_bounds);
            }
            if (mid - _split_value >= Zero()) {
                _right = _right->erase(argument, argument_bounds);
            }
            if (!_left) {
                SetNode<Type>* result = _right;
                _right = nullptr;
                delete this;
                return result;
            } else if (!_right) {
                SetNode<Type>* result = _left;
                _left = nullptr;
                delete this;
                return result;
            } else {
                typename Bounds<Type>::Type overall_bounds = _left->_bounds.hull(_right->_bounds);
                if (compatible(overall_bounds, _split_direction, _split_value)) {
                    _bounds = overall_bounds;
                    _size = _left->size() + _right->size();
                    return this;
                } else {
                    std::vector<SetNode<Type>*> nodes;
                    nodes.reserve(_left->_size + _right->_size);
                    _left->getLeaves(nodes);
                    _right->getLeaves(nodes);
                    return new(this) SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1);
                }
            }
        }
    }
}
