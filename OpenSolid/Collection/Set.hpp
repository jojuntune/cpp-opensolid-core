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

#ifndef OPENSOLID__SET_HPP
#define OPENSOLID__SET_HPP

#include <ostream>
#include <algorithm>

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Common/Shared.hpp>
#include "CollectionBase.hpp"
#include "FixedSizeCollection.hpp"
#include "SetNode.hpp"
#include "List.hpp"

namespace OpenSolid
{
    template <class Type>
    class OverlapFunction;
    
    template <class Type, class FunctionType>
    class FilteredSet;
    
    template <class Type>
    class Set : public FixedSizeCollection<Set<Type> >
    {
    private:
        Shared<SetNode<Type> >  _root;
        
        Set(const Shared<SetNode<Type> >& root);
        
        void init(const List<Shared<SetNode<Type> > >& nodes);
        
        template <class DerivedType>
        void init(const CollectionBase<DerivedType>& collection);
        
        template <class FunctionType>
        void init(const FilteredSet<Type, FunctionType>& filtered_set);
    public:
        Set();
        
        Set(const Set<Type>& other);
        
        template <class DerivedType>
        Set(const CollectionBase<DerivedType>& collection);
        
        int size() const;
        bool empty() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
        
        const typename Bounds<Type>::Type& bounds() const;
        
        const Type& item() const;
        
        Set<Type> left() const;
        Set<Type> right() const;
        
        Set<Type>& add(const Type& object);
        
        Set<Type>& update(const Set<Type>& other);
        
        template <class DerivedType>
        Set<Type>& update(const CollectionBase<DerivedType>& collection);
        
        Set<Type>& remove(const Type& object);
        
        Set<Type>& clear();
        
        template <class FunctionType>
        FilteredSet<Type, FunctionType> filtered(const FunctionType& function) const;
        
        FilteredSet<Type, OverlapFunction<Type> > overlapping(
            const typename Bounds<Type>::Type& bounds
        ) const;
        
        bool operator==(const Set<Type>& other) const;
    };
    
    template <class ItemType>
    struct Bounds<Set<ItemType> >
    {
        typedef typename Bounds<ItemType>::Type Type;
        
        static Type bounds(const Set<ItemType>& set);
    };
    
    template <class Type>
    class OverlapFunction
    {
    private:
        typename Bounds<Type>::Type _bounds;
    public:
        OverlapFunction(const typename Bounds<Type>::Type& bounds);
    
        bool operator()(const typename Bounds<Type>::Type& subset_bounds) const;
    };
    
    template <class Type, class FunctionType>
    class FilteredSetNodes : public CollectionBase<FilteredSetNodes<Type, FunctionType> >
    {
    private:
        Shared<SetNode<Type> > _root;
        FunctionType _function;
        
        template <class VisitorType>
        void visit(const Shared<SetNode<Type> >& node, const VisitorType& visitor) const;
    public:
        FilteredSetNodes(const Shared<SetNode<Type> >& root, const FunctionType& function);
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
    };
    
    template <class Type, class FunctionType>
    class FilteredSet : public CollectionBase<FilteredSet<Type, FunctionType> >
    {
    private:
        Shared<SetNode<Type> > _root;
        FunctionType _function;
        
        template <class VisitorType>
        void visit(const Shared<SetNode<Type> > node, const VisitorType& visitor) const;
    public:
        FilteredSet(const Shared<SetNode<Type> >& root, const FunctionType& function);
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
        
        FilteredSetNodes<Type, FunctionType> nodes() const;
    };
    
    template <class Type>
    std::ostream& operator<<(std::ostream& stream, const Set<Type>& set);
}
    
////////// Implementation //////////
    
namespace OpenSolid
{
    namespace
    {
        template <class Type>
        struct NodeCreator
        {
            inline Shared<SetNode<Type> > operator()(const Type& item) const {
                return new SetNode<Type>(Bounds<Type>::bounds(item), item);
            }
        };
    }
    
    template <class Type>
    inline Set<Type>::Set(const Shared<SetNode<Type> >& root) : _root(root) {}
    
    template <class Type>
    void Set<Type>::init(const List<Shared<SetNode<Type> > >& nodes) {
        if (nodes.empty()) {
            _root = 0;
        } else if (nodes.size() == 1) {
            _root = nodes.front();
        } else {
            typename Bounds<Type>::Type overall_bounds = nodes.front().constReference().bounds();
            for (int i = 1; i < nodes.size(); ++i) {
                overall_bounds = overall_bounds.hull(nodes[i].constReference().bounds());
            }
            _root = new SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1);
        }
    }
    
    template <class Type> template <class DerivedType>
    inline void Set<Type>::init(const CollectionBase<DerivedType>& collection) {
        List<Shared<SetNode<Type> > > nodes =
            collection.template mapped<Shared<SetNode<Type> > >(NodeCreator<Type>());
        init(nodes);
    }
        
    template <class Type> template <class FunctionType>
    inline void Set<Type>::init(const FilteredSet<Type, FunctionType>& filtered_set) {
        List<Shared<SetNode<Type> > > nodes = filtered_set.nodes();
        init(nodes);
    }
    
    template <class Type>
    inline Set<Type>::Set() : _root(0) {}
    
    template <class Type>
    inline Set<Type>::Set(const Set<Type>& other) : _root(other._root) {}
    
    template <class Type> template <class DerivedType>
    inline Set<Type>::Set(const CollectionBase<DerivedType>& collection) {
        init(collection.derived());
    }
    
    template <class Type>       
    inline int Set<Type>::size() const {return _root.valid() ? _root.constReference().size() : 0;}
    
    template <class Type>       
    inline bool Set<Type>::empty() const {return _root.valid();}
    
    template <class Type> template <class VisitorType>
    inline void Set<Type>::visit(const VisitorType& visitor) const {
        if (_root.valid()) {_root.constReference().visit(visitor);}
    }
    
    template <class Type>
    inline const typename Bounds<Type>::Type& Set<Type>::bounds() const {
        assert(_root.valid());
        return _root.constReference().bounds();
    }
    
    template <class Type>
    inline const Type& Set<Type>::item() const {
        assert(_root.valid() && _root.constReference().object().valid());
        return root().constReference().object().constReference();
    }
    
    template <class Type>
    inline Set<Type> Set<Type>::left() const {
        if (root()) {
            return root().constReference().left();
        } else {
            return 0;
        }
    }
    
    template <class Type>
    inline Set<Type> Set<Type>::right() const {
        if (root()) {
            return root().constReference().right();
        } else {
            return 0;
        }
    }
    
    template <class Type>
    inline Set<Type>& Set<Type>::add(const Type& object) {
        typename Bounds<Type>::Type bounds = Bounds<Type>::bounds(object);
        if (_root.valid()) {
            _root = _root.constReference().insert(bounds, object);
            _root.reference().updateParents();
        } else {
            _root = new SetNode<Type>(bounds, object);
        }
        return *this;
    }
    
    template <class Type>
    Set<Type>& Set<Type>::update(const Set<Type>& other) {
        if (_root.valid() && other._root.valid()) {
            typename Bounds<Type>::Type overall_bounds = bounds().hull(other.bounds());
            List<Shared<SetNode<Type> > > nodes = root().constReference().leaves() +
                other.root().constReference().leaves();
            _root = new SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1);
            _root.reference().updateParents();
        } else if (other.root().valid()) {
            _root = other.root();
        }
        return *this;
    }
    
    template <class Type> template <class DerivedType>
    Set<Type>& Set<Type>::update(const CollectionBase<DerivedType>& collection) {
        List<Shared<SetNode<Type> > > nodes;
        if (_root.valid()) {nodes.extend(_root.constReference().leaves());}
        nodes.extend(collection.template mapped<Shared<SetNode<Type> > >(NodeCreator<Type>()));
        typename Bounds<Type>::Type overall_bounds = bounds();
        for (int i = size(); i < nodes.size(); ++i) {
            overall_bounds = overall_bounds.hull(nodes[i]->bounds());
        }
        _root = new SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1);
        _root.reference().updatePointers();
        return *this;
    }
    
    template <class Type>
    inline Set<Type>& Set<Type>::remove(const Type& object) {
        if (_root.valid()) {
            typename Bounds<Type>::Type bounds = Bounds<Type>::bounds(object);
            _root = _root.constReference().remove(bounds, object);
            _root.reference().updatePointers();
        }
        return *this;
    }
    
    template <class Type>
    inline Set<Type>& Set<Type>::clear() {
        _root = 0;
        return *this;
    }
    
    template <class Type> template <class FunctionType>
    inline FilteredSet<Type, FunctionType> Set<Type>::filtered(
        const FunctionType& function
    ) const {return FilteredSet<Type, FunctionType>(_root, function);}
    
    template <class Type>
    inline FilteredSet<Type, OverlapFunction<Type> > Set<Type>::overlapping(
        const typename Bounds<Type>::Type& bounds
    ) const {return filtered(OverlapFunction<Type>(bounds));}
    
    template <class Type>
    inline bool Set<Type>::operator==(const Set<Type>& other) const {
        return _root.constPointer() == other._root.constPointer();
    }
    
    template <class Type>
    inline typename Bounds<Type>::Type bounds(const Set<Type>& set) {return set.bounds();}
    
    template <class Type>
    inline OverlapFunction<Type>::OverlapFunction(const typename Bounds<Type>::Type& bounds) :
        _bounds(bounds) {}

    template <class Type>
    inline bool OverlapFunction<Type>::operator()(
        const typename Bounds<Type>::Type& subset_bounds
    ) const {return _bounds.overlap(subset_bounds);}
    
    template <class Type, class FunctionType> template <class VisitorType>
    void FilteredSetNodes<Type, FunctionType>::visit(
        const Shared<SetNode<Type> >& node,
        const VisitorType& visitor
    ) const {
        if (_function(node.constReference().bounds())) {
            if (node.constReference().object().valid()) {
                const_cast<VisitorType&>(visitor)(node);
            } else {
                visit(node.constReference().left(), visitor);
                visit(node.constReference().right(), visitor);
            }
        }
    }
    
    template <class Type, class FunctionType>
    inline FilteredSetNodes<Type, FunctionType>::FilteredSetNodes(
        const Shared<SetNode<Type> >& root,
        const FunctionType& function
    ) : _root(root), _function(function) {}
    
    template <class Type, class FunctionType> template <class VisitorType>
    inline void FilteredSetNodes<Type, FunctionType>::visit(const VisitorType& visitor) const {
        if (_root.valid()) {visit(_root, visitor);}
    }
    
    template <class Type, class FunctionType> template <class VisitorType>
    void FilteredSet<Type, FunctionType>::visit(
        const Shared<SetNode<Type> >& node,
        const VisitorType& visitor
    ) const {
        if (_function(node.constReference().bounds())) {
            if (node.constReference().object().valid()) {
                const_cast<VisitorType&>(visitor)(node.constReference().object().constReference());
            } else {
                visit(node.constReference().left(), visitor);
                visit(node.constReference().right(), visitor);
            }
        }
    }
        
    template <class Type, class FunctionType>
    inline FilteredSet<Type, FunctionType>::FilteredSet(
        const Shared<SetNode<Type> >& root,
        const FunctionType& function
    ) : _root(root), _function(function) {}
    
    template <class Type, class FunctionType> template <class VisitorType>
    void FilteredSet<Type, FunctionType>::visit(const VisitorType& visitor) const {
        if (_root.valid()) {visit(_root, visitor);}
    }
    
    template <class Type, class FunctionType>
    inline FilteredSetNodes<Type, FunctionType> FilteredSet<Type, FunctionType>::nodes() const {
        return FilteredSetNodes<Type, FunctionType>(_root, _function);
    }
    
    template <class Type>
    std::ostream& operator<<(std::ostream& stream, const Set<Type>& set) {
        if (set.empty()) {
            return stream << "{}";
        } else if (set.size() == 1) {
            return stream << "{" << set.item() << "}";
        } else {
            return stream << "{" << set.left() << "," << set.right() << "}";
        }
    }
}

#endif
