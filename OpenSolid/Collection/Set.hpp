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
#include <OpenSolid/Common/ReferenceCountedBase.hpp>
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
    
    namespace
    {
        template <class Type>
        class SetRoot : public ReferenceCountedBase<SetRoot<Type> >
        {
        private:
            SetRoot();
        public:
            SetNode<Type>* node;
            
            inline SetRoot(SetNode<Type>* node_) : node(node_) {}
            
            inline SetRoot(const SetRoot<Type>& other) : node(new SetNode<Type>(*other.node)) {}
            
            inline ~SetRoot() {if (node) {delete node;}}
        };
    }
    
    template <class Type>
    class Set : public FixedSizeCollection<Set<Type> >
    {
    private:
        Shared<SetRoot<Type> >  _root;
        
        void init(List<SetNode<Type>*>& nodes);
        
        template <class DerivedType>
        void init(const CollectionBase<DerivedType>& collection);
    public:
        Set();
        
        Set(const Set<Type>& other);
        
        template <class DerivedType>
        Set(const CollectionBase<DerivedType>& collection);
        
        int size() const;
        bool empty() const;
        
        const SetNode<Type>* rootNode() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
        
        const typename Bounds<Type>::Type& bounds() const;
        
        const Type& item() const;
        
        Set<Type>& add(const Type& object);
        
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
    class FilteredSet : public CollectionBase<FilteredSet<Type, FunctionType> >
    {
    private:
        const SetNode<Type>* _root;
        FunctionType _function;
        
        template <class VisitorType>
        void visit(const SetNode<Type>* node, const VisitorType& visitor) const;
    public:
        FilteredSet(const SetNode<Type>* root, const FunctionType& function);
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
    };
    
    template <class Type>    
    std::ostream& operator<<(std::ostream& stream, const SetNode<Type>& node);
    
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
            inline SetNode<Type>* operator()(const Type& item) const {
                return new SetNode<Type>(Bounds<Type>::bounds(item), item);
            }
        };
    }
    
    template <class Type>
    void Set<Type>::init(List<SetNode<Type>*>& nodes) {
        if (nodes.empty()) {
            _root = new SetRoot<Type>(0);
        } else if (nodes.size() == 1) {
            _root = new SetRoot<Type>(nodes[0]);
        } else {
            typename Bounds<Type>::Type overall_bounds = nodes[0]->bounds();
            for (int i = 1; i < nodes.size(); ++i) {
                overall_bounds = overall_bounds.hull(nodes[i]->bounds());
            }
            _root = new SetRoot<Type>(
                new SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1)
            );
        }
    }
    
    template <class Type> template <class DerivedType>
    inline void Set<Type>::init(const CollectionBase<DerivedType>& collection) {
        List<SetNode<Type>*> nodes =
            collection.template mapped<SetNode<Type>*>(NodeCreator<Type>());
        init(nodes);
    }
    
    template <class Type>
    inline Set<Type>::Set() : _root(new SetRoot<Type>(0)) {}
    
    template <class Type>
    inline Set<Type>::Set(const Set<Type>& other) : _root(other._root) {}
    
    template <class Type> template <class DerivedType>
    inline Set<Type>::Set(const CollectionBase<DerivedType>& collection) {
        init(collection.derived());
    }
    
    template <class Type>       
    inline int Set<Type>::size() const {
        return _root.constReference().node ? _root.constReference().node->size() : 0;
    }
    
    template <class Type>       
    inline bool Set<Type>::empty() const {return !_root.constReference().node;}
    
    template <class Type>
    inline const SetNode<Type>* Set<Type>::rootNode() const {
        return _root.constReference().node;
    }
    
    template <class Type> template <class VisitorType>
    inline void Set<Type>::visit(const VisitorType& visitor) const {
        if (_root.constReference().node) {_root.constReference().node->visit(visitor);}
    }
    
    template <class Type>
    inline const typename Bounds<Type>::Type& Set<Type>::bounds() const {
        assert(_root.constReference().node);
        return _root.constReference().node->bounds();
    }
    
    template <class Type>
    inline const Type& Set<Type>::item() const {
        assert(_root.constReference().node && _root.constReference().node->object());
        return *_root.constReference().node->object();
    }
    
    template <class Type>
    inline Set<Type>& Set<Type>::add(const Type& object) {
        typename Bounds<Type>::Type bounds = Bounds<Type>::bounds(object);
        if (_root.constReference().node) {
            SetRoot<Type>& root = _root.reference();
            root.node = root.node->insert(bounds, object);
        } else {
            _root = new SetRoot<Type>(new SetNode<Type>(bounds, object));
        }
        return *this;
    }
    
    template <class Type> template <class DerivedType>
    Set<Type>& Set<Type>::update(const CollectionBase<DerivedType>& collection) {
        typename Bounds<Type>::Type overall_bounds = bounds();
        List<SetNode<Type>*> nodes;
        if (_root.constReference().node) {
            SetRoot<Type>& root = _root.reference();
            root.node->getLeaves(nodes);
            root.node = 0;
        }
        nodes.extend(collection.template mapped<SetNode<Type>*>(NodeCreator<Type>()));
        for (int i = size(); i < nodes.size(); ++i) {
            overall_bounds = overall_bounds.hull(nodes[i]->bounds());
        }
        _root = new SetRoot<Type>(
            new SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1)
        );
        return *this;
    }
    
    template <class Type>
    inline Set<Type>& Set<Type>::remove(const Type& object) {
        if (_root.constReference().node) {
            typename Bounds<Type>::Type bounds = Bounds<Type>::bounds(object);
            SetRoot<Type>& root = _root.reference();
            root.node = root.node->remove(bounds, object);
        }
        return *this;
    }
    
    template <class Type>
    inline Set<Type>& Set<Type>::clear() {
        _root = new SetRoot<Type>(0);
        return *this;
    }
    
    template <class Type> template <class FunctionType>
    inline FilteredSet<Type, FunctionType> Set<Type>::filtered(
        const FunctionType& function
    ) const {return FilteredSet<Type, FunctionType>(_root.constReference().node, function);}
    
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
    void FilteredSet<Type, FunctionType>::visit(
        const SetNode<Type>* node,
        const VisitorType& visitor
    ) const {
        if (_function(node->bounds())) {
            if (node->object()) {
                const_cast<VisitorType&>(visitor)(*node->object());
            } else {
                assert(node->left() && node->right());
                visit(node->left(), visitor);
                visit(node->right(), visitor);
            }
        }
    }
        
    template <class Type, class FunctionType>
    inline FilteredSet<Type, FunctionType>::FilteredSet(
        const SetNode<Type>* root,
        const FunctionType& function
    ) : _root(root), _function(function) {}
    
    template <class Type, class FunctionType> template <class VisitorType>
    void FilteredSet<Type, FunctionType>::visit(const VisitorType& visitor) const {
        if (_root) {visit(_root, visitor);}
    }

    template <class Type>    
    std::ostream& operator<<(std::ostream& stream, const SetNode<Type>& node) {
        stream << "{";
        if (node.object()) {
            stream << *node.object();
        } else {
            stream << *node.left();
            stream << ",";
            stream << *node.right();
        }
        stream << "}";
        return stream;
    }
    
    template <class Type>
    std::ostream& operator<<(std::ostream& stream, const Set<Type>& set) {
        if (set.empty()) {
            stream << "{}";
        } else {
            stream << *set.rootNode();
        }
        return stream;
    }
}

#endif
