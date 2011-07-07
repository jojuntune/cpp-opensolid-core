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
#include <functional>
#include <numeric>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/functional/hash.hpp>
#include <boost/smart_ptr/detail/atomic_count.hpp>

#include <OpenSolid/Set/SetNode.hpp>

namespace OpenSolid
{
    template <class Type, class BoundsType>
    struct DefaultBoundsFunction
    {
        typedef BoundsType Bounds;
        
        BoundsType operator()(const Type& argument) const;
    };

    template <class Type, class BoundsType, class BoundsFunctionType>
    class SetIterator;

    template <
        class Type,
        class BoundsType = typename Type::Bounds,
        class BoundsFunctionType = DefaultBoundsFunction<Type, BoundsType>
    >
    class Set
    {
    public:
        typedef BoundsType Bounds;
        typedef SetNode<Type, BoundsType> Node;
        typedef SetIterator<Type, BoundsType, BoundsFunctionType> Iterator;
    private:
        Node* _root;
        boost::detail::atomic_count* _shared_count;
        BoundsFunctionType _bounds_function;
    public:
        Set(const BoundsFunctionType& bounds_function = BoundsFunctionType());
        
        Set(const Set<Type, BoundsType, BoundsFunctionType>& other);
        
        template <class IteratorType>
        Set(
            IteratorType begin,
            IteratorType end,
            const BoundsFunctionType& bounds_function = BoundsFunctionType()
        );
        
        ~Set();
        
        const Node* root() const;
        
        void operator=(const Set<Type, BoundsType, BoundsFunctionType>& other);
        
        int size() const;
        bool empty() const;
        const BoundsType& bounds() const;
        std::size_t hashValue() const;
        
        const Type& front() const;
        const Type& back() const;
        
        SetIterator<Type, BoundsType, BoundsFunctionType> begin() const;
        SetIterator<Type, BoundsType, BoundsFunctionType> end() const;
        
        void insert(const Type& object);
        int erase(const Type& object);
        
        template <class IteratorType>
        void insert(IteratorType begin, IteratorType end);
        
        template <class IteratorType>
        int erase(IteratorType begin, IteratorType end);
        
        void clear();
        
        template <class FunctionType>
        Set<Type, BoundsType, BoundsFunctionType> filtered(const FunctionType& function) const;
        
        Set<Type, BoundsType, BoundsFunctionType> overlapping(const BoundsType& bounds) const;
        
        bool operator==(const Set<Type, BoundsType, BoundsFunctionType>& other) const;
    };
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    class SetIterator :
        public boost::iterator_facade<
            SetIterator<Type, BoundsType, BoundsFunctionType>,
            const Type,
            std::forward_iterator_tag
        >
    {
    private:
        typedef typename Set<Type, BoundsType, BoundsFunctionType>::Node Node;
        
        const Node* _node;
        
        friend class boost::iterator_core_access;
        
        void increment();
        bool equal(const SetIterator<Type, BoundsType, BoundsFunctionType>& other) const;
        const Type& dereference() const;
    public:
        SetIterator();
        SetIterator(const Node* node);
    };
    
    template <class Type, class BoundsType>
    std::ostream& operator<<(std::ostream& stream, const SetNode<Type, BoundsType>& node);
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    std::ostream& operator<<(
        std::ostream& stream,
        const Set<Type, BoundsType, BoundsFunctionType>& set
    );
}
    
////////// Implementation //////////
    
namespace OpenSolid
{   
    template <class Type, class BoundsType>
    inline BoundsType DefaultBoundsFunction<Type, BoundsType>::operator()(
        const Type& argument
    ) const {return argument.bounds();}
        
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline Set<Type, BoundsType, BoundsFunctionType>::Set(
        const BoundsFunctionType& bounds_function
    ) : _root(nullptr), _shared_count(nullptr), _bounds_function(bounds_function) {}
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline Set<Type, BoundsType, BoundsFunctionType>::Set(
        const Set<Type, BoundsType, BoundsFunctionType>& other
    ) : _bounds_function(other._bounds_function) {
        if (other._root) {
            _root = other._root;
            _shared_count = other._shared_count;
            ++*_shared_count;
        } else {
            _root = nullptr;
            _shared_count = nullptr;
        }
    }
        
    template <class Type, class BoundsType, class BoundsFunctionType> template <class IteratorType>
    inline Set<Type, BoundsType, BoundsFunctionType>::Set(
        IteratorType begin,
        IteratorType end,
        const BoundsFunctionType& bounds_function
    ) : _bounds_function(bounds_function) {
        std::vector<Node*> nodes;
        std::transform(
            begin,
            end,
            std::back_inserter(nodes), 
            [bounds_function] (const Type& item) {return new Node(item, bounds_function(item));}
        );
        if (nodes.empty()) {
            _root = nullptr;
            _shared_count = nullptr;
        } else if (nodes.size() == 1) {
            _root = nodes[0];
            _shared_count = new boost::detail::atomic_count(1);
        } else {
            BoundsType overall_bounds = nodes.front()->bounds();
            std::for_each(
                nodes.begin() + 1,
                nodes.end(),
                [&overall_bounds] (Node* node) {
                    overall_bounds = overall_bounds.hull(node->bounds());
                }
            );
            _root = new Node(overall_bounds, &nodes.front(), &nodes.back() + 1);
            _shared_count = new boost::detail::atomic_count(1);
        }
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline Set<Type, BoundsType, BoundsFunctionType>::~Set() {
        if (_root && !--*_shared_count) {
            delete _root;
            delete _shared_count;
        }
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline int Set<Type, BoundsType, BoundsFunctionType>::size() const {
        return empty() ? 0 : root()->size();
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline bool Set<Type, BoundsType, BoundsFunctionType>::empty() const {return !root();}
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline const typename Set<Type, BoundsType, BoundsFunctionType>::Node*
    Set<Type, BoundsType, BoundsFunctionType>::root() const {return _root;}
        
    template <class Type, class BoundsType, class BoundsFunctionType>
    void Set<Type, BoundsType, BoundsFunctionType>::operator=(
        const Set<Type, BoundsType, BoundsFunctionType>& other
    ) {
        _bounds_function = other._bounds_function;
        if (other._root) {
            _root = other._root;
            _shared_count = other._shared_count;
            ++*_shared_count;
        } else {
            _root = nullptr;
            _shared_count = nullptr;
        }
    }
        
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline SetIterator<Type, BoundsType, BoundsFunctionType>
    Set<Type, BoundsType, BoundsFunctionType>::begin() const {
        if (empty()) {
            return nullptr;
        } else {
            const Node* node = root();
            while (node->left()) {node = node->left();}
            return node;
        }
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline SetIterator<Type, BoundsType, BoundsFunctionType>
    Set<Type, BoundsType, BoundsFunctionType>::end() const {return nullptr;}
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline const BoundsType& Set<Type, BoundsType, BoundsFunctionType>::bounds() const {
        assert(!empty());
        return root()->bounds();
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline std::size_t Set<Type, BoundsType, BoundsFunctionType>::hashValue() const {
        return boost::hash_value(root());
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline const Type& Set<Type, BoundsType, BoundsFunctionType>::front() const {
        assert(!empty());
        const Node* node = root();
        while (node->left()) {node = node->left();}
        return *node->object();
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline const Type& Set<Type, BoundsType, BoundsFunctionType>::back() const {
        assert(!empty());
        const Node* node = root();
        while (node->right()) {node = node->right();}
        return *node->object();
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline void Set<Type, BoundsType, BoundsFunctionType>::insert(const Type& object) {
        BoundsType bounds = _bounds_function(object);
        if (empty()) {
            _root = new Node(object, bounds);
            _shared_count = new boost::detail::atomic_count(1);
        } else {
            if (*_shared_count > 1) {
                --*_shared_count;
                _root = new Node(*_root);
                _shared_count = new boost::detail::atomic_count(1);
            }
            _root = _root->insert(object, bounds);
        }
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline int Set<Type, BoundsType, BoundsFunctionType>::erase(const Type& object) {
        if (empty()) {
            return 0;
        } else {
            if (*_shared_count > 1) {
                --*_shared_count;
                _root = new Node(*_root);
                _shared_count = new boost::detail::atomic_count(1);
            }
            BoundsType bounds = _bounds_function(object);
            int previous_size = size();
            _root = _root->erase(object, bounds);
            return previous_size - size();
        }
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType> template <class IteratorType>
    inline void Set<Type, BoundsType, BoundsFunctionType>::insert(
        IteratorType begin,
        IteratorType end
    ) {std::for_each(begin, end, [this] (const Type& object) {this->insert(object);});}
    
    template <class Type, class BoundsType, class BoundsFunctionType> template <class IteratorType>
    inline int Set<Type, BoundsType, BoundsFunctionType>::erase(
        IteratorType begin,
        IteratorType end
    ) {
        return std::accumulate(
            begin,
            end,
            0,
            [this] (int result, const Type& object) {return result + this->erase(object);}
        );
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline void Set<Type, BoundsType, BoundsFunctionType>::clear() {
        if (_root) {
            if (!--*_shared_count) {
                delete _root;
                delete _shared_count;
            }
            _root = nullptr;
            _shared_count = nullptr;
        }
    }
    
    namespace
    {
        template <class Type, class BoundsType, class FunctionType>
        inline void getFiltered(
            const SetNode<Type, BoundsType>* node,
            const FunctionType& function,
            std::vector<SetNode<Type, BoundsType>*>& nodes
        ) {
            if (function(node->bounds())) {
                if (node->object()) {
                    nodes.push_back(new SetNode<Type, BoundsType>(*node));
                } else {
                    getFiltered(node->left(), function, nodes);
                    getFiltered(node->right(), function, nodes);
                }
            }
        }
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType> template <class FunctionType>
    inline Set<Type, BoundsType, BoundsFunctionType>
    Set<Type, BoundsType, BoundsFunctionType>::filtered(const FunctionType& function) const {
        if (empty()) {
            return Set<Type, BoundsType, BoundsFunctionType>();
        } else {
            std::vector<Node*> nodes;
            getFiltered(root(), function, nodes);
            if (nodes.empty()) {
                return Set<Type, BoundsType, BoundsFunctionType>();
            } else if (nodes.size() == 1) {
                Set<Type, BoundsType, BoundsFunctionType> result;
                result._root = nodes[0];
                result._shared_count = new boost::detail::atomic_count(1);
                result._bounds_function = _bounds_function;
                return result;
            } else {
                Bounds overall_bounds = nodes.front()->bounds();
                std::for_each(
                    nodes.begin() + 1,
                    nodes.end(),
                    [&overall_bounds] (Node* node) {
                        overall_bounds = overall_bounds.hull(node->bounds());
                    }
                );
                Set<Type, BoundsType, BoundsFunctionType> result;
                result._root = new Node(overall_bounds, &nodes.front(), &nodes.back() + 1);
                result._shared_count = new boost::detail::atomic_count(1);
                result._bounds_function = _bounds_function;
                return result;
            }
        }
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline Set<Type, BoundsType, BoundsFunctionType>
    Set<Type, BoundsType, BoundsFunctionType>::overlapping(const BoundsType& bounds) const {
        return filtered(
            [&bounds] (const BoundsType& subset_bounds) {return bounds.overlaps(subset_bounds);}
        );
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline bool Set<Type, BoundsType, BoundsFunctionType>::operator==(
        const Set<Type, BoundsType, BoundsFunctionType>& other
    ) const {return root() == other.root();}
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline void SetIterator<Type, BoundsType, BoundsFunctionType>::increment() {
        while (_node->parent() && _node->parent()->right() == _node) {_node = _node->parent();}
        if (!_node->parent()) {
            _node = nullptr;
            return;
        } else {
            _node = _node->parent()->right();
            while (_node->left()) {_node = _node->left();}
        }
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline bool SetIterator<Type, BoundsType, BoundsFunctionType>::equal(
        const SetIterator<Type, BoundsType, BoundsFunctionType>& other
    ) const {return _node == other._node;}
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline const Type& SetIterator<Type, BoundsType, BoundsFunctionType>::dereference() const {
        return *_node->object();
    }
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline SetIterator<Type, BoundsType, BoundsFunctionType>::SetIterator() : _node(nullptr) {}
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    inline SetIterator<Type, BoundsType, BoundsFunctionType>::SetIterator(
        const typename SetIterator<Type, BoundsType, BoundsFunctionType>::Node* node
    ) :  _node(node) {}

    template <class Type, class BoundsType>
    std::ostream& operator<<(std::ostream& stream, const SetNode<Type, BoundsType>& node) {
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
    
    template <class Type, class BoundsType, class BoundsFunctionType>
    std::ostream& operator<<(
        std::ostream& stream,
        const Set<Type, BoundsType, BoundsFunctionType>& set
    ) {
        if (set.empty()) {
            stream << "{}";
        } else {
            stream << *set.root();
        }
        return stream;
    }
}

#endif
