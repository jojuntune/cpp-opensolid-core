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

#ifndef OPENSOLID__SETNODE_HPP
#define OPENSOLID__SETNODE_HPP

#include <new>

#include <OpenSolid/Common/Bounds.hpp>
#include "List.hpp"

namespace OpenSolid
{
    template <class Type>
    class SetNode
    {
    private:
        void operator=(const SetNode<Type>& other);
        
        typename Bounds<Type>::Type _bounds;
        int _split_direction;
        double _split_value;
        const Type* _object;
        SetNode<Type>* _left;
        SetNode<Type>* _right;
        const SetNode<Type>* _parent;
        int _size;
    public:
        SetNode();
        explicit SetNode(const SetNode<Type>& other);
        
        SetNode(const typename Bounds<Type>::Type& bounds, const Type& object);
        
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
        
        const typename Bounds<Type>::Type& bounds() const;
        int splitDirection() const;
        double splitValue() const;
        const Type* object() const;
        const SetNode<Type>* left() const;
        const SetNode<Type>* right() const;
        const SetNode<Type>* parent() const;
        int size() const;
        
        void getLeaves(List<SetNode<Type>*>& leaves);
        
        SetNode<Type>* insert(
            const typename Bounds<Type>::Type& new_bounds,
            const Type& new_object
        );
        
        SetNode<Type>* remove(
            const typename Bounds<Type>::Type& bounds,
            const Type& object
        );
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    namespace
    {
        template <class BoundsType>
        inline void split(const BoundsType& bounds, int& split_direction, double& split_value) {
            typename BoundsType::Index index;
            bounds.cwiseWidth().maxCoeff(&index);
            split_direction = index;
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
            double split_ratio = (split_value - bounds.lower()) / (bounds.upper() - split_value);
            return split_ratio > 0.5 && split_ratio < 2;
        }
    }
    
    template <class Type>
    inline SetNode<Type>::SetNode(const SetNode<Type>& other) :
        _bounds(other._bounds),
        _split_direction(other._split_direction),
        _split_value(other._split_value),
        _parent(0),
        _size(other._size) {
        if (other._object) {
            assert(!other._left && !other._right);
            _object = new Type(*other._object);
            _left = 0;
            _right = 0;
        } else {
            assert(other._left && other._right);
            _object = 0;
            _left = new SetNode<Type>(*other._left);
            _left->_parent = this;
            _right = new SetNode<Type>(*other._right);
            _right->_parent = this;
        }
    }
    
    template <class Type>
    inline SetNode<Type>::SetNode(const typename Bounds<Type>::Type& bounds, const Type& object) :
        _bounds(bounds), _object(new Type(object)), _left(0), _right(0), _parent(0), _size(1) {}
    
    template <class Type>
    inline SetNode<Type>::SetNode(
        const typename Bounds<Type>::Type& overall_bounds,
        int split_direction,
        double split_value,
        SetNode<Type>* left,
        SetNode<Type>* right
    ) : _bounds(overall_bounds), _split_direction(split_direction), _split_value(split_value),
        _object(0), _left(left), _right(right), _parent(0), _size(left->_size + right->_size) {
        _left._parent = this;
        _right._parent = this;
    }
    
    template <class Type>
    SetNode<Type>::SetNode(
        const typename Bounds<Type>::Type& overall_bounds,
        SetNode<Type>** begin,
        SetNode<Type>** end
    ) {
        _bounds = overall_bounds;
        _object = 0;
        _parent = 0;
        _size = end - begin;
        split(_bounds, _split_direction, _split_value);
        if (_size == 2) {
            _left = *begin;
            _right = *(begin + 1);
            double right_median = _right->_bounds(_split_direction).median();
            double left_median = _left->_bounds(_split_direction).median();
            if (right_median < left_median) {std::swap(_left, _right);}
        } else {
            int left_size = 0;
            int right_size = 0;
            typename Bounds<Type>::Type left_bounds;
            typename Bounds<Type>::Type right_bounds;
            SetNode<Type>** lower = begin;
            SetNode<Type>** upper = end - 1;
            for (SetNode<Type>** i = lower; i <= upper; ++i) {
                Interval difference = (*i)->_bounds(_split_direction) - _bounds(_split_direction);
                if (difference.upper() < -difference.lower()) {
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
                Interval difference = (*i)->_bounds(_split_direction) - _bounds(_split_direction);
                if (difference.upper() > -difference.lower()) {
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
        _left->_parent = this;
        _right->_parent = this;
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
    inline const typename Bounds<Type>::Type& SetNode<Type>::bounds() const {return _bounds;}
    
    template <class Type>
    inline int SetNode<Type>::splitDirection() const {return _split_direction;}
    
    template <class Type>
    inline double SetNode<Type>::splitValue() const {return _split_value;}
    
    template <class Type>
    inline const Type* SetNode<Type>::object() const {return _object;}
        
    template <class Type>
    inline const SetNode<Type>* SetNode<Type>::left() const {return _left;}
    
    template <class Type>
    inline const SetNode<Type>* SetNode<Type>::right() const {return _right;}
    
    template <class Type>
    inline const SetNode<Type>* SetNode<Type>::parent() const {return _parent;}
    
    template <class Type>
    inline int SetNode<Type>::size() const {return _size;}
    
    template <class Type>
    void SetNode<Type>::getLeaves(List<SetNode<Type>*>& leaves) {
        if (_object) {
            assert(!_left && !_right);
            _parent = 0;
            leaves.append(this);
        } else {
            assert(_left && _right);
            _left->getLeaves(leaves);
            _right->getLeaves(leaves);
            _left = 0;
            _right = 0;
            delete this;
        }
    }
    
    template <class Type>
    SetNode<Type>* SetNode<Type>::insert(
        const typename Bounds<Type>::Type& new_bounds,
        const Type& new_object
    ) {
        typename Bounds<Type>::Type overall_bounds = _bounds.hull(new_bounds);
        if (_object) {
            assert(!_left && !_right);
            SetNode<Type>* nodes[2] = {this, new SetNode<Type>(new_bounds, new_object)};
            return new SetNode<Type>(overall_bounds, nodes, nodes + 2);
        } else if (compatible(overall_bounds, _split_direction, _split_value)) {
            assert(_left && _right);
            double median = new_bounds(_split_direction).median();
            if (median < _split_value) {
                _left = _left->insert(new_bounds, new_object);
                _left->_parent = this;
            } else if (median > _split_value) {
                _right = _right->insert(new_bounds, new_object);
                _right->_parent = this;
            } else if (_left->_size < _right->_size) {
                _left = _left->insert(new_bounds, new_object);
                _left->_parent = this;
            } else {
                _right = _right->insert(new_bounds, new_object);
                _right->_parent = this;
            }
            _bounds = overall_bounds;
            return this;
        } else {
            assert(_left && _right);
            List<SetNode<Type>*> nodes;
            nodes.reserve(_size + 1);
            _left->getLeaves(nodes);
            _right->getLeaves(nodes);
            nodes.append(new SetNode<Type>(new_bounds, new_object));
            return new(this) SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1);
        }
    }

    template <class Type>
    SetNode<Type>* SetNode<Type>::remove(
        const typename Bounds<Type>::Type& removed_bounds,
        const Type& removed_object
    ) {
        if (!_bounds.overlap(removed_bounds)) {
            return this;
        } else if (_object) {
            assert(!_left && !_right);
            if (*_object == removed_object) {
                delete this;
                return 0;
            } else {
                return this;
            }
        } else {
            assert(_left && _right);
            double median = removed_bounds(_split_direction).median();
            if (median <= _split_value) {_left = _left->remove(removed_bounds, removed_object);}
            if (median >= _split_value) {_right = _right->remove(removed_bounds, removed_object);}
            if (!_left) {
                SetNode<Type>* result = _right;
                _right = 0;
                delete this;
                return result;
            } else if (!_right) {
                SetNode<Type>* result = _left;
                _left = 0;
                delete this;
                return result;
            } else {
                typename Bounds<Type>::Type overall_bounds = _left->_bounds.hull(_right->_bounds);
                if (compatible(overall_bounds, _split_direction, _split_value)) {
                    _left->_parent = this;
                    _right->_parent = this;
                    _bounds = overall_bounds;
                    return this;
                } else {
                    List<SetNode<Type>*> nodes;
                    nodes.reserve(_left->_size + _right->_size);
                    _left->getLeaves(nodes);
                    _right->getLeaves(nodes);
                    return new(this) SetNode<Type>(
                        overall_bounds,
                        &nodes.front(),
                        &nodes.back() + 1
                    );
                }
            }
        }
    }
        
    template <class Type> template <class VisitorType>
    void SetNode<Type>::visit(const VisitorType& visitor) const {
        if (_object) {
            assert(!_left && !_right);
            const_cast<VisitorType&>(visitor)(*_object);
        } else {
            assert(_left && _right);
            _left->visit(visitor);
            _right->visit(visitor);
        }
    }
}

#endif
