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

#include <opensolid/common/ReferenceCountedBase.hpp>
#include <opensolid/common/Bounds.hpp>
#include "List.hpp"

namespace opensolid
{
    template <class Type>
    class LeafNodes;
    
    template <class Type>
    class SetNode : public ReferenceCountedBase<SetNode<Type> >
    {
    private:
        SetNode();
        SetNode(const SetNode<Type>& other);
        void operator=(const SetNode<Type>& other);
        
        typename Bounds<Type>::Type _bounds;
        int _split_direction;
        double _split_value;
        const Type* _object;
        typename SetNode<Type>::Pointer _left;
        typename SetNode<Type>::Pointer _right;
        int _size;
    public:
        SetNode(const typename Bounds<Type>::Type& bounds, const Type& object);
        
        SetNode(
            const typename Bounds<Type>::Type& overall_bounds,
            int split_direction,
            double split_value,
            const SetNode<Type>* left,
            const SetNode<Type>* right
        );
        
        SetNode(
            const typename Bounds<Type>::Type& overall_bounds,
            const SetNode<Type>** begin,
            const SetNode<Type>** end
        );
        
        ~SetNode();
        
        const typename Bounds<Type>::Type& bounds() const;
        int splitDirection() const;
        double splitValue() const;
        const Type* object() const;
        const SetNode<Type>* left() const;
        const SetNode<Type>* right() const;
        int size() const;
        
        const SetNode<Type>* insert(
            const typename Bounds<Type>::Type& new_bounds,
            const Type& new_object
        ) const;
        
        const SetNode<Type>* remove(
            const typename Bounds<Type>::Type& bounds,
            const Type& object
        ) const;
        
        LeafNodes<Type> leaves() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
    };
    
    template <class Type>
    class LeafNodes : public FixedSizeCollection<LeafNodes<Type> >
    {
    private:
        const SetNode<Type>* _root;
        
        template <class VisitorType>
        static void visit(const SetNode<Type>* node, const VisitorType& visitor);
    public:
        typedef const SetNode<Type>* Item;
        
        LeafNodes(const SetNode<Type>* root);
        
        int size() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
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
    inline SetNode<Type>::SetNode(const typename Bounds<Type>::Type& bounds, const Type& object) :
        _bounds(bounds), _object(new Type(object)), _size(1) {}
    
    template <class Type>
    inline SetNode<Type>::SetNode(
        const typename Bounds<Type>::Type& overall_bounds,
        int split_direction,
        double split_value,
        const SetNode<Type>* left,
        const SetNode<Type>* right
    ) : _bounds(overall_bounds), _split_direction(split_direction), _split_value(split_value),
        _object(0), _left(left), _right(right), _size(left->size() + right->size()) {}
    
    template <class Type>
    SetNode<Type>::SetNode(
        const typename Bounds<Type>::Type& overall_bounds,
        const SetNode<Type>** begin,
        const SetNode<Type>** end
    ) : _bounds(overall_bounds), _object(0), _size(end - begin) {
        split(bounds(), _split_direction, _split_value);
        if (size() == 2) {
            _left = *begin;
            _right = *(begin + 1);
            double right_median = right()->bounds()(splitDirection()).median();
            double left_median = left()->bounds()(splitDirection()).median();
            if (right_median < left_median) {_left.swap(_right);}
        } else {
            int left_size = 0;
            int right_size = 0;
            typename Bounds<Type>::Type left_bounds;
            typename Bounds<Type>::Type right_bounds;
            const SetNode<Type>** lower = begin;
            const SetNode<Type>** upper = end - 1;
            for (const SetNode<Type>** i = lower; i <= upper; ++i) {
                Interval difference = (*i)->bounds()(splitDirection()) - bounds()(splitDirection());
                if (difference.upper() < -difference.lower()) {
                    if (left_size > 0) {
                        left_bounds = left_bounds.hull((*i)->bounds());
                    } else {
                        left_bounds = (*i)->bounds();
                    }
                    ++left_size;
                    if (i != lower) {std::swap(*i, *lower);}
                    ++lower;
                }
            }
            for (const SetNode<Type>** i = upper; i >= lower; --i) {
                Interval difference = (*i)->bounds()(splitDirection()) - bounds()(splitDirection());
                if (difference.upper() > -difference.lower()) {
                    if (right_size > 0) {
                        right_bounds = right_bounds.hull((*i)->bounds());
                    } else {
                        right_bounds = (*i)->bounds();
                    }
                    ++right_size;
                    if (i != upper) {std::swap(*i, *upper);}
                    --upper;
                }
            }
            while (left_size < _size / 2 && lower <= upper) {
                if (left_size > 0) {
                    left_bounds = left_bounds.hull((*lower)->bounds());
                } else {
                    left_bounds = (*lower)->bounds();
                }
                ++left_size;
                ++lower;
            }
            while (right_size < _size - _size / 2 && lower <= upper) {
                if (right_size > 0) {
                    right_bounds = right_bounds.hull((*upper)->bounds());
                } else {
                    right_bounds = (*upper)->bounds();
                }
                ++right_size;
                --upper;
            }
            _left = left_size == 1 ? *begin : new SetNode<Type>(left_bounds, begin, lower);
            _right = right_size == 1 ? *lower : new SetNode<Type>(right_bounds, lower, end);
        }
    }
    
    template <class Type>
    inline SetNode<Type>::~SetNode() {if (object()) {delete object();}}
    
    template <class Type>
    inline const typename Bounds<Type>::Type& SetNode<Type>::bounds() const {return _bounds;}
    
    template <class Type>
    inline int SetNode<Type>::splitDirection() const {return _split_direction;}
    
    template <class Type>
    inline double SetNode<Type>::splitValue() const {return _split_value;}
    
    template <class Type>
    inline const Type* SetNode<Type>::object() const {return _object;}
        
    template <class Type>
    inline const SetNode<Type>* SetNode<Type>::left() const {return _left.get();}
    
    template <class Type>
    inline const SetNode<Type>* SetNode<Type>::right() const {return _right.get();}
    
    template <class Type>
    inline int SetNode<Type>::size() const {return _size;}
    
    template <class Type>
    const SetNode<Type>* SetNode<Type>::insert(
        const typename Bounds<Type>::Type& new_bounds,
        const Type& new_object
    ) const {
        typename Bounds<Type>::Type overall_bounds = bounds().hull(new_bounds);
        if (object()) {
            const SetNode<Type>* nodes[2] = {this, new SetNode<Type>(new_bounds, new_object)};
            return new SetNode<Type>(overall_bounds, nodes, nodes + 2);
        } else if (compatible(overall_bounds, splitDirection(), splitValue())) {
            double median = new_bounds(splitDirection()).median();
            const SetNode<Type>* new_left = left();
            const SetNode<Type>* new_right = right();
            if (median < splitValue()) {
                new_left = left()->insert(new_bounds, new_object);
            } else if (median > _split_value) {
                new_right = right()->insert(new_bounds, new_object);
            } else if (left()->size() < right()->size()) {
                new_left = left()->insert(new_bounds, new_object);
            } else {
                new_right = right()->insert(new_bounds, new_object);
            }
            return new SetNode<Type>(
                overall_bounds,
                splitDirection(),
                splitValue(),
                new_left,
                new_right
            );
        } else {
            List<const SetNode<Type>*> nodes;
            nodes.reserve(size() + 1);
            nodes = leaves();
            nodes.append(new SetNode<Type>(new_bounds, new_object));
            return new SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1);
        }
    }

    template <class Type>
    const SetNode<Type>* SetNode<Type>::remove(
        const typename Bounds<Type>::Type& removed_bounds,
        const Type& removed_object
    ) const {
        if (!bounds().overlap(removed_bounds)) {return this;}
        if (object()) {return *object() == removed_object ? 0 : this;}
        const SetNode<Type>* new_left = left();
        const SetNode<Type>* new_right = right();
        double median = removed_bounds(splitDirection()).median();
        if (median <= splitValue()) {new_left = left()->remove(removed_bounds, removed_object);}
        if (median >= splitValue()) {new_right = right()->remove(removed_bounds, removed_object);}
        if (!new_left) {return new_right;}
        if (!new_right) {return new_left;}
        typename Bounds<Type>::Type overall_bounds = new_left->bounds().hull(new_right->bounds());
        if (compatible(overall_bounds, splitDirection(), splitValue())) {
            return new SetNode<Type>(
                overall_bounds,
                splitDirection(),
                splitValue(),
                new_left,
                new_right
            );
        } else {
            List<const SetNode<Type>*> nodes;
            nodes.reserve(new_left->size() + new_right->size());
            nodes.extend(new_left->leaves());
            nodes.extend(new_right->leaves());
            const SetNode<Type>* result = new SetNode<Type>(
                overall_bounds,
                &nodes.front(),
                &nodes.back() + 1
            );
            if (new_left->intrusive_ptr_count == 0) {delete new_left;}
            if (new_right->intrusive_ptr_count == 0) {delete new_right;}
            return result;
        }
    }

    template <class Type>
    inline LeafNodes<Type> SetNode<Type>::leaves() const {return LeafNodes<Type>(this);}
        
    template <class Type> template <class VisitorType>
    void SetNode<Type>::visit(const VisitorType& visitor) const {
        if (object()) {
            const_cast<VisitorType&>(visitor)(*object());
        } else {
            left()->visit(visitor);
            right()->visit(visitor);
        }
    }
        
    template <class Type> template <class VisitorType>
    void LeafNodes<Type>::visit(const SetNode<Type>* node, const VisitorType& visitor) {
        if (node->object()) {
            const_cast<VisitorType&>(visitor)(node);
        } else {
            visit(node->left(), visitor);
            visit(node->right(), visitor);
        }
    }
    
    template <class Type>
    inline LeafNodes<Type>::LeafNodes(const SetNode<Type>* root) : _root(root) {}
    
    template <class Type>
    inline int LeafNodes<Type>::size() const {return _root->size();}
    
    template <class Type> template <class VisitorType>
    inline void LeafNodes<Type>::visit(const VisitorType& visitor) const {visit(_root, visitor);}
}

#endif
