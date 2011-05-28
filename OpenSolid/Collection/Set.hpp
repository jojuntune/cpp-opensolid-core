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

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Common/ReferenceCountedBase.hpp>
#include <OpenSolid/Common/Shared.hpp>
#include <OpenSolid/Value/Tolerance.hpp>
#include "SetNode.hpp"

namespace OpenSolid
{
    template <class Type>
    class SetIterator;
    
    template <class Type>
    class Set
    {
    private:
        SetNode<Type>* _root;
        boost::detail::atomic_count* _shared_count;
    public:
        typedef SetIterator<Type> Iterator;
        
        Set();
        
        Set(const Set<Type>& other);
        
        template <class IteratorType>
        Set(IteratorType begin, IteratorType end);
        
        ~Set();
        
        const SetNode<Type>* root() const;
        
        void operator=(const Set<Type>& other);
        
        std::size_t size() const;
        bool empty() const;
        const typename Bounds<Type>::Type& bounds() const;
        
        const Type& front() const;
        const Type& back() const;
        
        SetIterator<Type> begin() const;
        SetIterator<Type> end() const;
        
        void insert(const Type& object);
        std::size_t erase(const Type& object);
        void clear();
        
        template <class FunctionType>
        Set<Type> filtered(const FunctionType& function) const;
        
        Set<Type> overlapping(const typename Bounds<Type>::Type& bounds) const;
        
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
    class SetIterator :
        public boost::iterator_facade<
            SetIterator<Type>,
            const Type,
            boost::forward_traversal_tag
        >
    {
    private:
        const SetNode<Type>* _node;
        
        friend class boost::iterator_core_access;
        
        void increment();
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
        double _tolerance;
    public:
        OverlapFunction(const typename Bounds<Type>::Type& bounds);
    
        bool operator()(const typename Bounds<Type>::Type& subset_bounds) const;
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
        struct NodeCreator : public std::unary_function<Type, SetNode<Type>*>
        {
            inline SetNode<Type>* operator()(const Type& item) const {
                return new SetNode<Type>(Bounds<Type>::bounds(item), item);
            }
        };
    }
    
    template <class Type>
    inline Set<Type>::Set() : _root(0), _shared_count(0) {}
    
    template <class Type>
    inline Set<Type>::Set(const Set<Type>& other) {
        if (other._root) {
            _root = other._root;
            _shared_count = other._shared_count;
            ++*_shared_count;
        } else {
            _root = 0;
            _shared_count = 0;
        }
    }
        
    template <class Type> template <class IteratorType>
    inline Set<Type>::Set(IteratorType begin, IteratorType end) {
        std::vector<SetNode<Type>*> nodes;
        std::transform(begin, end, std::back_inserter(nodes), NodeCreator<Type>());
        if (nodes.empty()) {
            _root = 0;
            _shared_count = 0;
        } else if (nodes.size() == 1) {
            _root = nodes[0];
            _shared_count = new boost::detail::atomic_count(1);
        } else {
            typename Bounds<Type>::Type overall_bounds = nodes[0]->bounds();
            for (std::size_t i = 1; i < nodes.size(); ++i) {
                overall_bounds = overall_bounds.hull(nodes[i]->bounds());
            }
            _root = new SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1);
            _shared_count = new boost::detail::atomic_count(1);
        }
    }
    
    template <class Type>
    inline Set<Type>::~Set() {
        if (_root && !--*_shared_count) {
            delete _root;
            delete _shared_count;
        }
    }
    
    template <class Type>
    inline std::size_t Set<Type>::size() const {return empty() ? 0 : root()->size();}
    
    template <class Type>
    inline bool Set<Type>::empty() const {return !root();}
    
    template <class Type>
    inline const SetNode<Type>* Set<Type>::root() const {return _root;}
        
    template <class Type>
    void Set<Type>::operator=(const Set<Type>& other) {
        if (other._root) {
            _root = other._root;
            _shared_count = other._shared_count;
            ++*_shared_count;
        } else {
            _root = 0;
            _shared_count = 0;
        }
    }
        
    template <class Type>
    inline SetIterator<Type> Set<Type>::begin() const {
        if (empty()) {
            return 0;
        } else {
            const SetNode<Type>* node = root();
            while (node->left()) {node = node->left();}
            return node;
        }
    }
    
    template <class Type>
    inline SetIterator<Type> Set<Type>::end() const {return 0;}
    
    template <class Type>
    inline const typename Bounds<Type>::Type& Set<Type>::bounds() const {
        assert(!empty());
        return root()->bounds();
    }
    
    template <class Type>
    inline const Type& Set<Type>::front() const {
        assert(!empty());
        const SetNode<Type>* node = root();
        while (node->left()) {node = node->left();}
        return *node->object();
    }
    
    template <class Type>
    inline const Type& Set<Type>::back() const {
        assert(!empty());
        const SetNode<Type>* node = root();
        while (node->right()) {node = node->right();}
        return *node->object();
    }
    
    template <class Type>
    inline void Set<Type>::insert(const Type& object) {
        typename Bounds<Type>::Type bounds = Bounds<Type>::bounds(object);
        if (empty()) {
            _root = new SetNode<Type>(bounds, object);
            _shared_count = new boost::detail::atomic_count(1);
        } else {
            if (*_shared_count > 1) {
                --*_shared_count;
                _root = new SetNode<Type>(*_root);
                _shared_count = new boost::detail::atomic_count(1);
            }
            _root = _root->insert(bounds, object);
        }
    }
    
    template <class Type>
    inline std::size_t Set<Type>::erase(const Type& object) {
        if (empty()) {
            return 0;
        } else {
            if (*_shared_count > 1) {
                --*_shared_count;
                _root = new SetNode<Type>(*_root);
                _shared_count = new boost::detail::atomic_count(1);
            }
            typename Bounds<Type>::Type bounds = Bounds<Type>::bounds(object);
            std::size_t previous_size = size();
            _root = _root->erase(bounds, object);
            return size() - previous_size;
        }
    }
    
    template <class Type>
    inline void Set<Type>::clear() {
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
        template <class Type, class FunctionType>
        inline void getFiltered(
            const SetNode<Type>* node,
            const FunctionType& function,
            std::vector<SetNode<Type>*>& nodes
        ) {
            if (function(node->bounds())) {
                if (node->object()) {
                    nodes.push_back(new SetNode<Type>(*node));
                } else {
                    getFiltered(node->left(), function, nodes);
                    getFiltered(node->right(), function, nodes);
                }
            }
        }
    }
    
    template <class Type> template <class FunctionType>
    inline Set<Type> Set<Type>::filtered(const FunctionType& function) const {
        if (empty()) {
            return Set<Type>();
        } else {
            std::vector<SetNode<Type>*> nodes;
            getFiltered(root(), function, nodes);
            if (nodes.empty()) {
                return Set<Type>();
            } else if (nodes.size() == 1) {
                Set<Type> result;
                result._root = nodes[0];
                result._shared_count = new boost::detail::atomic_count(1);
                return result;
            } else {
                typename Bounds<Type>::Type overall_bounds = nodes[0]->bounds();
                for (std::size_t i = 1; i < nodes.size(); ++i) {
                    overall_bounds = overall_bounds.hull(nodes[i]->bounds());
                }
                Set<Type> result;
                result._root = new SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1);
                result._shared_count = new boost::detail::atomic_count(1);
                return result;
            }
        }
    }
    
    template <class Type>
    inline Set<Type> Set<Type>::overlapping(const typename Bounds<Type>::Type& bounds) const {
        return filtered(OverlapFunction<Type>(bounds));
    }
    
    template <class Type>
    inline bool Set<Type>::operator==(const Set<Type>& other) const {
        return root() == other.root();
    }
    
    template <class Type>
    inline std::size_t hash_value(const Set<Type>& set) {
        return boost::hash_value(set.root());
    }
    
    template <class Type>
    inline typename Bounds<Type>::Type bounds(const Set<Type>& set) {return set.bounds();}
    
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
        _bounds(bounds), _tolerance(Tolerance::roundoff()) {}

    template <class Type>
    inline bool OverlapFunction<Type>::operator()(
        const typename Bounds<Type>::Type& subset_bounds
    ) const {return subset_bounds.overlap(_bounds, _tolerance);}

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
            stream << *set.root();
        }
        return stream;
    }
}

#endif
