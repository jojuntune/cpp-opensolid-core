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
#include <boost/smart_ptr/detail/atomic_count.hpp>

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Set/SetNode.hpp>

namespace OpenSolid
{
    template <class Type, class BoundsType>
    class SetIterator;

    template <class Type, class BoundsFunctionType = Bounds<Type>>
    class Set
    {
    public:
        typedef typename BoundsFunctionType::Type Bounds;
        typedef SetNode<Type, Bounds> Node;
        typedef SetIterator<Type, Bounds> Iterator;
    private:
        Node* _root;
        boost::detail::atomic_count* _shared_count;
        BoundsFunctionType _bounds_function;
    public:
        Set(const BoundsFunctionType& bounds_function = BoundsFunctionType());
        
        Set(const Set<Type, BoundsFunctionType>& other);
        
        template <class IteratorType>
        Set(
            IteratorType begin,
            IteratorType end,
            const BoundsFunctionType& bounds_function = BoundsFunctionType()
        );
        
        ~Set();
        
        const Node* root() const;
        
        void operator=(const Set<Type, BoundsFunctionType>& other);
        
        int size() const;
        bool empty() const;
        const Bounds& bounds() const;
        
        const Type& front() const;
        const Type& back() const;
        
        SetIterator<Type, Bounds> begin() const;
        SetIterator<Type, Bounds> end() const;
        
        void insert(const Type& object);
        int erase(const Type& object);
        
        template <class IteratorType>
        void insert(IteratorType begin, IteratorType end);
        
        template <class IteratorType>
        int erase(IteratorType begin, IteratorType end);
        
        void clear();
        
        template <class FunctionType>
        Set<Type, BoundsFunctionType> filtered(const FunctionType& function) const;
        
        Set<Type, BoundsFunctionType> overlapping(const Bounds& bounds) const;
    };
    
    template <class Type, class BoundsType>
    class SetIterator :
        public boost::iterator_facade<
            SetIterator<Type, BoundsType>,
            const Type,
            std::forward_iterator_tag
        >
    {
    private:
        const SetNode<Type, BoundsType>* _node;
        
        friend class boost::iterator_core_access;
        
        void increment();
        bool equal(const SetIterator<Type, BoundsType>& other) const;
        const Type& dereference() const;
    public:
        SetIterator();
        SetIterator(const SetNode<Type, BoundsType>* node);
    };
    
    template <class Type, class BoundsType>
    std::ostream& operator<<(std::ostream& stream, const SetNode<Type, BoundsType>& node);
    
    template <class Type, class BoundsFunctionType>
    std::ostream& operator<<(std::ostream& stream, const Set<Type, BoundsFunctionType>& set);
}

namespace std
{
    template <class Type, class BoundsFunctionType>
    struct hash<OpenSolid::Set<Type, BoundsFunctionType>>
    {
        size_t operator()(const OpenSolid::Set<Type, BoundsFunctionType>& argument) const;
    };

    template <class Type, class BoundsFunctionType>
    struct equal_to<OpenSolid::Set<Type, BoundsFunctionType>>
    {
        bool operator()(
            const OpenSolid::Set<Type, BoundsFunctionType>& first_argument,
            const OpenSolid::Set<Type, BoundsFunctionType>& second_argument
        );
    };
}
    
////////// Implementation //////////

#include <boost/functional/hash.hpp>
    
namespace OpenSolid
{   
    template <class Type, class BoundsFunctionType>
    inline Set<Type, BoundsFunctionType>::Set(const BoundsFunctionType& bounds_function) :
        _root(nullptr), _shared_count(nullptr), _bounds_function(bounds_function) {}
    
    template <class Type, class BoundsFunctionType>
    inline Set<Type, BoundsFunctionType>::Set(const Set<Type, BoundsFunctionType>& other) :
        _bounds_function(other._bounds_function) {
        if (other._root) {
            _root = other._root;
            _shared_count = other._shared_count;
            ++*_shared_count;
        } else {
            _root = nullptr;
            _shared_count = nullptr;
        }
    }
        
    template <class Type, class BoundsFunctionType> template <class IteratorType>
    inline Set<Type, BoundsFunctionType>::Set(
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
            Bounds overall_bounds = nodes.front()->bounds();
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
    
    template <class Type, class BoundsFunctionType>
    inline Set<Type, BoundsFunctionType>::~Set() {
        if (_root && !--*_shared_count) {
            delete _root;
            delete _shared_count;
        }
    }
    
    template <class Type, class BoundsFunctionType>
    inline int Set<Type, BoundsFunctionType>::size() const {
        return empty() ? 0 : root()->size();
    }
    
    template <class Type, class BoundsFunctionType>
    inline bool Set<Type, BoundsFunctionType>::empty() const {return !root();}
    
    template <class Type, class BoundsFunctionType>
    inline const typename Set<Type, BoundsFunctionType>::Node*
    Set<Type, BoundsFunctionType>::root() const {return _root;}
        
    template <class Type, class BoundsFunctionType>
    void Set<Type, BoundsFunctionType>::operator=(const Set<Type, BoundsFunctionType>& other) {
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
        
    template <class Type, class BoundsFunctionType>
    inline SetIterator<Type, typename Set<Type, BoundsFunctionType>::Bounds>
    Set<Type, BoundsFunctionType>::begin() const {
        if (empty()) {
            return nullptr;
        } else {
            const Node* node = root();
            while (node->left()) {node = node->left();}
            return node;
        }
    }
    
    template <class Type, class BoundsFunctionType>
    inline SetIterator<Type, typename Set<Type, BoundsFunctionType>::Bounds>
    Set<Type, BoundsFunctionType>::end() const {return nullptr;}
    
    template <class Type, class BoundsFunctionType>
    inline const typename Set<Type, BoundsFunctionType>::Bounds&
    Set<Type, BoundsFunctionType>::bounds() const {
        assert(!empty());
        return root()->bounds();
    }
    
    template <class Type, class BoundsFunctionType>
    inline const Type& Set<Type, BoundsFunctionType>::front() const {
        assert(!empty());
        const Node* node = root();
        while (node->left()) {node = node->left();}
        return *node->object();
    }
    
    template <class Type, class BoundsFunctionType>
    inline const Type& Set<Type, BoundsFunctionType>::back() const {
        assert(!empty());
        const Node* node = root();
        while (node->right()) {node = node->right();}
        return *node->object();
    }
    
    template <class Type, class BoundsFunctionType>
    inline void Set<Type, BoundsFunctionType>::insert(const Type& object) {
        Bounds bounds = _bounds_function(object);
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
    
    template <class Type, class BoundsFunctionType>
    inline int Set<Type, BoundsFunctionType>::erase(const Type& object) {
        if (empty()) {
            return 0;
        } else {
            if (*_shared_count > 1) {
                --*_shared_count;
                _root = new Node(*_root);
                _shared_count = new boost::detail::atomic_count(1);
            }
            Bounds bounds = _bounds_function(object);
            int previous_size = size();
            _root = _root->erase(object, bounds);
            return previous_size - size();
        }
    }
    
    template <class Type, class BoundsFunctionType> template <class IteratorType>
    inline void Set<Type, BoundsFunctionType>::insert(IteratorType begin, IteratorType end) {
        std::for_each(begin, end, [this] (const Type& object) {this->insert(object);});
    }
    
    template <class Type, class BoundsFunctionType> template <class IteratorType>
    inline int Set<Type, BoundsFunctionType>::erase(IteratorType begin, IteratorType end) {
        return std::accumulate(
            begin,
            end,
            0,
            [this] (int result, const Type& object) {return result + this->erase(object);}
        );
    }
    
    template <class Type, class BoundsFunctionType>
    inline void Set<Type, BoundsFunctionType>::clear() {
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
    
    template <class Type, class BoundsFunctionType> template <class FunctionType>
    inline Set<Type, BoundsFunctionType>
    Set<Type, BoundsFunctionType>::filtered(const FunctionType& function) const {
        if (empty()) {
            return Set<Type, BoundsFunctionType>();
        } else {
            std::vector<Node*> nodes;
            getFiltered(root(), function, nodes);
            if (nodes.empty()) {
                return Set<Type, BoundsFunctionType>();
            } else if (nodes.size() == 1) {
                Set<Type, BoundsFunctionType> result;
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
                Set<Type, BoundsFunctionType> result;
                result._root = new Node(overall_bounds, &nodes.front(), &nodes.back() + 1);
                result._shared_count = new boost::detail::atomic_count(1);
                result._bounds_function = _bounds_function;
                return result;
            }
        }
    }
    
    template <class Type, class BoundsFunctionType>
    inline Set<Type, BoundsFunctionType> Set<Type, BoundsFunctionType>::overlapping(
        const typename Set<Type, BoundsFunctionType>::Bounds& bounds
    ) const {
        return filtered(
            [&bounds] (const typename Set<Type, BoundsFunctionType>::Bounds& subset_bounds) {
                return bounds.overlaps(subset_bounds);
            }
        );
    }
    
    template <class Type, class BoundsType>
    inline void SetIterator<Type, BoundsType>::increment() {
        while (_node->parent() && _node->parent()->right() == _node) {_node = _node->parent();}
        if (!_node->parent()) {
            _node = nullptr;
            return;
        } else {
            _node = _node->parent()->right();
            while (_node->left()) {_node = _node->left();}
        }
    }
    
    template <class Type, class BoundsType>
    inline bool SetIterator<Type, BoundsType>::equal(
        const SetIterator<Type, BoundsType>& other
    ) const {return _node == other._node;}
    
    template <class Type, class BoundsType>
    inline const Type& SetIterator<Type, BoundsType>::dereference() const {
        return *_node->object();
    }
    
    template <class Type, class BoundsType>
    inline SetIterator<Type, BoundsType>::SetIterator() : _node(nullptr) {}
    
    template <class Type, class BoundsType>
    inline SetIterator<Type, BoundsType>::SetIterator(
        const typename SetNode<Type, BoundsType>* node
    ) : _node(node) {}

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
    
    template <class Type, class BoundsFunctionType>
    std::ostream& operator<<(std::ostream& stream, const Set<Type, BoundsFunctionType>& set) {
        if (set.empty()) {
            stream << "{}";
        } else {
            stream << *set.root();
        }
        return stream;
    }
}

namespace std
{
    template <class Type, class BoundsFunctionType>
    inline size_t hash<OpenSolid::Set<Type, BoundsFunctionType>>::operator()(
        const OpenSolid::Set<Type, BoundsFunctionType>& argument
    ) const {return boost::hash_value(argument.root());}

    template <class Type, class BoundsFunctionType>
    inline bool equal_to<OpenSolid::Set<Type, BoundsFunctionType>>::operator()(
        const OpenSolid::Set<Type, BoundsFunctionType>& first_argument,
        const OpenSolid::Set<Type, BoundsFunctionType>& second_argument
    ) {return first_argument.root() == second_argument.root();}
}

#endif
