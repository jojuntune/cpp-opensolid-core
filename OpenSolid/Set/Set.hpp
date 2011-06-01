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

#include <boost/iterator/iterator_facade.hpp>
#include <boost/functional/hash.hpp>
#include <boost/smart_ptr/detail/atomic_count.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <OpenSolid/Interval/Tolerance.hpp>
#include <OpenSolid/Interval/Interval.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include "SetNode.hpp"

namespace OpenSolid
{
    template <class Type>
    struct DefaultBoundsFunction
    {
        typedef typename Traits<Type>::Bounds Bounds;
        
        auto operator()(const Type& argument) const -> decltype(Traits<Type>::bounds(argument));
    };

    template <class Type, class BoundsFunction>
    class SetIterator;

    template <class Type, class BoundsFunctionType = DefaultBoundsFunction<Type>>
    class Set
    {
    public:
        typedef typename BoundsFunctionType::Bounds Bounds;
        
        typedef SetNode<Type, Bounds> Node;
        
        typedef SetIterator<Type, BoundsFunctionType> Iterator;
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
        
        SetIterator<Type, BoundsFunctionType> begin() const;
        SetIterator<Type, BoundsFunctionType> end() const;
        
        void insert(const Type& object);
        int erase(const Type& object);
        void clear();
        
        template <class FunctionType>
        Set<Type, BoundsFunctionType> filtered(const FunctionType& function) const;
        
        Set<Type, BoundsFunctionType> overlapping(const Bounds& bounds) const;
        
        bool operator==(const Set<Type, BoundsFunctionType>& other) const;
    };
    
    template <class Type, class BoundsFunctionType>
    class SetIterator :
        public boost::iterator_facade<
            SetIterator<Type, BoundsFunctionType>,
            const Type,
            std::forward_iterator_tag
        >
    {
    private:
        typedef typename Set<Type, BoundsFunctionType>::Node Node;
        
        const Node* _node;
        
        friend class boost::iterator_core_access;
        
        void increment();
        bool equal(const SetIterator<Type, BoundsFunctionType>& other) const;
        const Type& dereference() const;
    public:
        SetIterator();
        SetIterator(const Node* node);
    };
    
    template <class Type, class BoundsType>
    std::ostream& operator<<(std::ostream& stream, const SetNode<Type, BoundsType>& node);
    
    template <class Type, class BoundsFunctionType>
    std::ostream& operator<<(std::ostream& stream, const Set<Type, BoundsFunctionType>& set);
}
    
////////// Implementation //////////

#include "Traits.hpp"
    
namespace OpenSolid
{
    template <class Type, class BoundsFunctionType>
    inline const typename Traits<Set<Type, BoundsFunctionType>>::Bounds&
    Traits<Set<Type, BoundsFunctionType>>::bounds(const Set<Type, BoundsFunctionType>& argument) {
        return argument.bounds();
    }
    
    template <class Type, class BoundsFunctionType>
    inline std::size_t Traits<Set<Type, BoundsFunctionType>>::hash(
        const Set<Type, BoundsFunctionType>& argument
    ) {return boost::hash_value(argument.root());}
    
    template <class Type>
    inline auto DefaultBoundsFunction<Type>::operator()(const Type& argument) const ->
        decltype(Traits<Type>::bounds(argument)) {return Traits<Type>::bounds(argument);}
        
    template <class Type, class BoundsFunctionType>
    inline Set<Type, BoundsFunctionType>::Set(const BoundsFunctionType& bounds_function) :
        _root(0), _shared_count(0), _bounds_function(bounds_function) {}
    
    template <class Type, class BoundsFunctionType>
    inline Set<Type, BoundsFunctionType>::Set(const Set<Type, BoundsFunctionType>& other) :
        _bounds_function(other._bounds_function) {
        if (other._root) {
            _root = other._root;
            _shared_count = other._shared_count;
            ++*_shared_count;
        } else {
            _root = 0;
            _shared_count = 0;
        }
    }
        
    template <class Type, class BoundsFunctionType> template <class IteratorType>
    inline Set<Type, BoundsFunctionType>::Set(
        IteratorType begin,
        IteratorType end,
        const BoundsFunctionType& bounds_function = BoundsFunctionType()
    ) : _bounds_function(bounds_function) {
        std::vector<Node*> nodes;
        std::transform(
            begin,
            end,
            std::back_inserter(nodes), 
            [bounds_function] (const Type& item) {return new Node(item, bounds_function(item));}
        );
        if (nodes.empty()) {
            _root = 0;
            _shared_count = 0;
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
    inline int Set<Type, BoundsFunctionType>::size() const {return empty() ? 0 : root()->size();}
    
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
            _root = 0;
            _shared_count = 0;
        }
    }
        
    template <class Type, class BoundsFunctionType>
    inline SetIterator<Type, BoundsFunctionType> Set<Type, BoundsFunctionType>::begin() const {
        if (empty()) {
            return 0;
        } else {
            const Node* node = root();
            while (node->left()) {node = node->left();}
            return node;
        }
    }
    
    template <class Type, class BoundsFunctionType>
    inline SetIterator<Type, BoundsFunctionType> Set<Type, BoundsFunctionType>::end() const {
        return 0;
    }
    
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
            return size() - previous_size;
        }
    }
    
    template <class Type, class BoundsFunctionType>
    inline void Set<Type, BoundsFunctionType>::clear() {
        if (_root) {
            if (!--*_shared_count) {
                delete _root;
                delete _shared_count;
            }
            _root = 0;
            _shared_count = 0;
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
    inline Set<Type, BoundsFunctionType> Set<Type, BoundsFunctionType>::filtered(
        const FunctionType& function
    ) const {
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
        double tolerance = Tolerance::roundoff();
        return filtered(
            [&bounds, tolerance] (const Bounds& subset_bounds) {
                return bounds.overlap(subset_bounds, tolerance);
            }
        );
    }
    
    template <class Type, class BoundsFunctionType>
    inline bool Set<Type, BoundsFunctionType>::operator==(
        const Set<Type, BoundsFunctionType>& other
    ) const {return root() == other.root();}
    
    template <class Type, class BoundsFunctionType>
    inline std::size_t hash_value(const Set<Type, BoundsFunctionType>& set) {
        return boost::hash_value(set.root());
    }
    
    template <class Type, class BoundsFunctionType>
    inline void SetIterator<Type, BoundsFunctionType>::increment() {
        while (_node->parent() && _node->parent()->right() == _node) {_node = _node->parent();}
        if (!_node->parent()) {
            _node = 0;
            return;
        } else {
            _node = _node->parent()->right();
            while (_node->left()) {_node = _node->left();}
        }
    }
    
    template <class Type, class BoundsFunctionType>
    inline bool SetIterator<Type, BoundsFunctionType>::equal(
        const SetIterator<Type, BoundsFunctionType>& other
    ) const {return _node == other._node;}
    
    template <class Type, class BoundsFunctionType>
    inline const Type& SetIterator<Type, BoundsFunctionType>::dereference() const {
        return *_node->object();
    }
    
    template <class Type, class BoundsFunctionType>
    inline SetIterator<Type, BoundsFunctionType>::SetIterator() : _node(0) {}
    
    template <class Type, class BoundsFunctionType>
    inline SetIterator<Type, BoundsFunctionType>::SetIterator(
        const typename SetIterator<Type, BoundsFunctionType>::Node* node
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

#endif
