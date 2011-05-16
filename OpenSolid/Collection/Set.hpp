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

#include <boost/iterator/iterator_facade.hpp>
#include <boost/functional/hash.hpp>

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
    class SetRoot;
    
    template <class Type>
    class SetIterator;
    
    template <class Type>
    class OverlapFunction;
    
    template <class Type, class FunctionType>
    class FilteredSet;
    
    template <class Type, class FunctionType>
    class FilteredSetIterator;
    
    template <class Type>
    class Set : public FixedSizeCollection<Set<Type> >
    {
    private:
        Shared<SetRoot<Type> >  _root;
    public:
        typedef SetIterator<Type> Iterator;
        
        Set();
        
        Set(const Set<Type>& other);
        
        template <class DerivedType>
        Set(const CollectionBase<DerivedType>& collection);
        
        int size() const;
        bool empty() const;
        
        const SetNode<Type>* rootNode() const;
        
        SetIterator<Type> begin() const;
        SetIterator<Type> end() const;
        SetIterator<Type> rbegin() const;
        SetIterator<Type> rend() const;
        
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
    
    template <class Type>
    std::size_t hash_value(const Set<Type>& set);
    
    template <class ItemType>
    struct Bounds<Set<ItemType> >
    {
        typedef typename Bounds<ItemType>::Type Type;
        
        static Type bounds(const Set<ItemType>& set);
    };
    
    template <class Type>
    class SetRoot : public ReferenceCountedBase<SetRoot<Type> >
    {
    private:
        SetRoot();
    public:
        SetNode<Type>* node;
        
        SetRoot(SetNode<Type>* node_);
        SetRoot(const SetRoot<Type>& other);
        ~SetRoot();
    };
    
    template <class Type>
    class SetIterator :
        public boost::iterator_facade<
            SetIterator<Type>,
            const Type,
            boost::bidirectional_traversal_tag
        >
    {
    private:
        const SetNode<Type>* _node;
        
        friend class boost::iterator_core_access;
        
        void increment();
        void decrement();
        bool equal(const SetIterator<Type>& other) const;
        const Type& dereference() const;
    public:
        SetIterator();
        SetIterator(const SetNode<Type>* node);
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
        
        FilteredSetIterator<Type, FunctionType> begin() const;
        FilteredSetIterator<Type, FunctionType> end() const;
        FilteredSetIterator<Type, FunctionType> rbegin() const;
        FilteredSetIterator<Type, FunctionType> rend() const;
        
        template <class VisitorType>
        void visit(const VisitorType& visitor) const;
    };
    
    template <class Type, class FunctionType>
    class FilteredSetIterator :
        public boost::iterator_facade<
            FilteredSetIterator<Type, FunctionType>,
            const Type,
            boost::bidirectional_traversal_tag
        >
    {
    private:
        const SetNode<Type>* _node;
        FunctionType _function;
        
        friend class boost::iterator_core_access;
        
        void increment();
        void decrement();
        bool equal(const FilteredSetIterator<Type, FunctionType>& other) const;
        const Type& dereference() const;
    public:
        FilteredSetIterator(const SetNode<Type>* node, const FunctionType& function);
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
    inline Set<Type>::Set() : _root(new SetRoot<Type>(0)) {}
    
    template <class Type>
    inline Set<Type>::Set(const Set<Type>& other) : _root(other._root) {}
    
    template <class Type> template <class DerivedType>
    inline Set<Type>::Set(const CollectionBase<DerivedType>& collection) {
        List<SetNode<Type>*> nodes =
            collection.template mapped<SetNode<Type>*>(NodeCreator<Type>());
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
    
    template <class Type>
    inline int Set<Type>::size() const {return empty() ? 0 : rootNode()->size();}
    
    template <class Type>
    inline bool Set<Type>::empty() const {return !rootNode();}
    
    template <class Type>
    inline const SetNode<Type>* Set<Type>::rootNode() const {return _root.constReference().node;}
        
    template <class Type>
    inline SetIterator<Type> Set<Type>::begin() const {
        if (empty()) {
            return 0;
        } else {
            const SetNode<Type>* node = rootNode();
            while (node->left()) {node = node->left();}
            return node;
        }
    }
    
    template <class Type>
    inline SetIterator<Type> Set<Type>::end() const {return 0;}
    
    template <class Type>
    inline SetIterator<Type> Set<Type>::rbegin() const {
        if (empty()) {
            return 0;
        } else {
            const SetNode<Type>* node = rootNode();
            while (node->right()) {node = node->right();}
            return node;
        }
    }
    
    template <class Type>
    inline SetIterator<Type> Set<Type>::rend() const {return 0;}
    
    template <class Type> template <class VisitorType>
    inline void Set<Type>::visit(const VisitorType& visitor) const {
        if (!empty()) {rootNode()->visit(visitor);}
    }
    
    template <class Type>
    inline const typename Bounds<Type>::Type& Set<Type>::bounds() const {
        assert(!empty());
        return rootNode()->bounds();
    }
    
    template <class Type>
    inline const Type& Set<Type>::item() const {
        assert(!empty() && rootNode()->object());
        return *rootNode()->object();
    }
    
    template <class Type>
    inline Set<Type>& Set<Type>::add(const Type& object) {
        typename Bounds<Type>::Type bounds = Bounds<Type>::bounds(object);
        if (empty()) {
            _root = new SetRoot<Type>(new SetNode<Type>(bounds, object));
        } else {
            SetRoot<Type>& root = _root.reference();
            root.node = root.node->insert(bounds, object);
        }
        return *this;
    }
    
    template <class Type> template <class DerivedType>
    Set<Type>& Set<Type>::update(const CollectionBase<DerivedType>& collection) {
        List<SetNode<Type>*> nodes =
            collection.template mapped<SetNode<Type>*>(NodeCreator<Type>());
        if (!nodes.empty()) {
            typename Bounds<Type>::Type overall_bounds = nodes[0]->bounds();
            for (int i = 1; i < nodes.size(); ++i) {
                overall_bounds = overall_bounds.hull(nodes[i]->bounds());
            }
            if (!empty()) {
                overall_bounds = overall_bounds.hull(bounds());
                nodes.reserve(nodes.size() + size());
                SetRoot<Type>& root = _root.reference();
                root.node->getLeaves(nodes);
                root.node = 0;
            }
            _root = new SetRoot<Type>(
                new SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1)
            );
        }
        return *this;
    }
    
    template <class Type>
    inline Set<Type>& Set<Type>::remove(const Type& object) {
        if (!empty()) {
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
    ) const {return FilteredSet<Type, FunctionType>(rootNode(), function);}
    
    template <class Type>
    inline FilteredSet<Type, OverlapFunction<Type> > Set<Type>::overlapping(
        const typename Bounds<Type>::Type& bounds
    ) const {return filtered(OverlapFunction<Type>(bounds));}
    
    template <class Type>
    inline bool Set<Type>::operator==(const Set<Type>& other) const {
        return rootNode() == other.rootNode();
    }
    
    template <class Type>
    inline std::size_t hash_value(const Set<Type>& set) {
        return boost::hash_value(set.rootNode());
    }
    
    template <class Type>
    inline typename Bounds<Type>::Type bounds(const Set<Type>& set) {return set.bounds();}
    
    template <class Type>
    inline SetRoot<Type>::SetRoot(SetNode<Type>* node_) : node(node_) {}
    
    template <class Type>
    inline SetRoot<Type>::SetRoot(const SetRoot<Type>& other) :
        node(new SetNode<Type>(*other.node)) {}
    
    template <class Type>
    inline SetRoot<Type>::~SetRoot() {if (node) {delete node;}}
    
    template <class Type>
    inline void SetIterator<Type>::increment() {
        while (_node->parent() && _node->parent()->right() == _node) {_node = _node->parent();}
        if (!_node->parent()) {
            _node = 0;
            return;
        } else {
            _node = _node->parent()->right();
            while (_node->left()) {_node = _node->left();}
        }
    }
    
    template <class Type>
    inline void SetIterator<Type>::decrement() {
        while (_node->parent() && _node->parent()->left() == _node) {_node = _node->parent();}
        if (!_node->parent()) {
            _node = 0;
            return;
        } else {
            _node = _node->parent()->left();
            while (_node->right()) {_node = _node->right();}
        }
    }
    
    template <class Type>
    inline bool SetIterator<Type>::equal(const SetIterator<Type>& other) const {
        return _node == other._node;
    }
    
    template <class Type>
    inline const Type& SetIterator<Type>::dereference() const {return *_node->object();}
    
    template <class Type>
    inline SetIterator<Type>::SetIterator() : _node(0) {}
    
    template <class Type>
    inline SetIterator<Type>::SetIterator(const SetNode<Type>* node) : _node(node) {}
    
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
    
    template <class Type, class FunctionType>
    inline FilteredSetIterator<Type, FunctionType> FilteredSet<Type, FunctionType>::begin() const {
        if (!_root) {
            return FilteredSetIterator<Type, FunctionType>(0, _function);
        } else {
            const SetNode<Type>* node = _root;
            while (node->left() && _function(node->bounds())) {node = node->left();}
            while (!_function(node->bounds())) {
                while (node->parent() && node->parent()->right() == node) {
                    node = node->parent();
                }
                if (!node->parent()) {
                    return FilteredSetIterator<Type, FunctionType>(0, _function);
                } else {
                    node = node->parent()->right();
                    while (node->left() && _function(node->bounds())) {node = node->left();}
                }
            }
            return FilteredSetIterator<Type, FunctionType>(node, _function);
        }
    }
    
    template <class Type, class FunctionType>
    inline FilteredSetIterator<Type, FunctionType> FilteredSet<Type, FunctionType>::end() const {
        return FilteredSetIterator<Type, FunctionType>(0, _function);
    }
    
    template <class Type, class FunctionType>
    inline FilteredSetIterator<Type, FunctionType> FilteredSet<Type, FunctionType>::rbegin() const {
        if (!_root) {
            return FilteredSetIterator<Type, FunctionType>(0, _function);
        } else {
            const SetNode<Type>* node = _root;
            while (node->right() && _function(node->bounds())) {node = node->right();}
            while (!_function(node->bounds())) {
                while (node->parent() && node->parent()->left() == node) {
                    node = node->parent();
                }
                if (!node->parent()) {
                    return FilteredSetIterator<Type, FunctionType>(0, _function);
                } else {
                    node = node->parent()->left();
                    while (node->right() && _function(node->bounds())) {node = node->right();}
                }
            }
            return FilteredSetIterator<Type, FunctionType>(node, _function);
        }
    }
    
    template <class Type, class FunctionType>
    inline FilteredSetIterator<Type, FunctionType> FilteredSet<Type, FunctionType>::rend() const {
        return FilteredSetIterator<Type, FunctionType>(0, _function);
    }
    
    template <class Type, class FunctionType> template <class VisitorType>
    inline void FilteredSet<Type, FunctionType>::visit(const VisitorType& visitor) const {
        if (_root) {visit(_root, visitor);}
    }
    
    template <class Type, class FunctionType>
    inline void FilteredSetIterator<Type, FunctionType>::increment() {
        do {
            while (_node->parent() && _node->parent()->right() == _node) {_node = _node->parent();}
            if (!_node->parent()) {
                _node = 0;
                return;
            } else {
                _node = _node->parent()->right();
                while (_node->left() && _function(_node->bounds())) {_node = _node->left();}
            }
        } while (!_function(_node->bounds()));
    }
    
    template <class Type, class FunctionType>
    inline void FilteredSetIterator<Type, FunctionType>::decrement() {
        do {
            while (_node->parent() && _node->parent()->left() == _node) {_node = _node->parent();}
            if (!_node->parent()) {
                _node = 0;
                return;
            } else {
                _node = _node->parent()->left();
                while (_node->right() && _function(_node->bounds())) {_node = _node->right();}
            }
        } while (!_function(_node->bounds()));
    }
    
    template <class Type, class FunctionType>
    inline bool FilteredSetIterator<Type, FunctionType>::equal(
        const FilteredSetIterator<Type, FunctionType>& other
    ) const {return _node == other._node;}
    
    template <class Type, class FunctionType>
    inline const Type& FilteredSetIterator<Type, FunctionType>::dereference() const {
        return *_node->object();
    }
    
    template <class Type, class FunctionType>
    inline FilteredSetIterator<Type, FunctionType>::FilteredSetIterator(
        const SetNode<Type>* node,
        const FunctionType& function
    ) : _node(node), _function(function) {}

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
