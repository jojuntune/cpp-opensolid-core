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

#include "detail/SetNode.hpp"

#include <OpenSolid/Core/Bounds.hpp>

#include <ostream>
#include <algorithm>
#include <functional>
#include <numeric>

namespace opensolid
{
    template <class Type>
    class SetInserter;

    template <class Type>
    class Set
    {
    private:
        SetNode<Type>* _root;
        Bounds<Type> _bounds_function;
    public:
        Set(Bounds<Type> bounds_function = Bounds<Type>());
        
        Set(const Set<Type>& other);
        
        template <class IteratorType>
        Set(IteratorType begin, IteratorType end, Bounds<Type> bounds_function = Bounds<Type>());
        
        ~Set();
        
        const SetNode<Type>* root() const;
        
        void operator=(const Set<Type>& other);
        
        std::size_t size() const;
        bool isEmpty() const;
        typename Bounds<Type>::Type bounds() const;
        
        void insert(const Type& object);
        std::size_t erase(const Type& object);
        
        template <class IteratorType>
        void insert(IteratorType begin, IteratorType end);
        
        template <class IteratorType>
        std::size_t erase(IteratorType begin, IteratorType end);
        
        void clear();

        SetInserter<Type> inserter();

        template <class VisitorType>
        void forEach(const VisitorType& visitor) const;

        template <class VisitorType>
        void forEachOverlapping(
            const typename Bounds<Type>::Type& overlapping_bounds,
            const VisitorType& visitor
        ) const;

        template <class VisitorType, class BoundsPredicateType>
        void forEachFiltered(
            const BoundsPredicateType& bounds_predicate,
            const VisitorType& visitor
        ) const;

        template <class VisitorType, class PredicateType>
        void forEachIf(const PredicateType& predicate, const VisitorType& visitor) const;

        template <class VisitorType, class PredicateType>
        void forEachOverlappingIf(
            const typename Bounds<Type>::Type& overlapping_bounds,
            const PredicateType& predicate,
            const VisitorType& visitor
        ) const;

        template <class VisitorType, class BoundsPredicateType, class PredicateType>
        void forEachFilteredIf(
            const BoundsPredicateType& bounds_predicate,
            const PredicateType& predicate,
            const VisitorType& visitor
        ) const;

        template <class OutputIteratorType>
        void copy(OutputIteratorType output_iterator) const;

        template<class OutputIteratorType>
        void copyOverlapping(
            const typename Bounds<Type>::Type& overlapping_bounds,
            OutputIteratorType output_iterator
        ) const;

        template <class BoundsPredicateType, class OutputIteratorType>
        void copyFiltered(
            const BoundsPredicateType& bounds_predicate,
            OutputIteratorType output_iterator
        ) const;

        template <class PredicateType, class OutputIteratorType>
        void copyIf(const PredicateType& predicate, OutputIteratorType output_iterator) const;

        template <class PredicateType, class OutputIteratorType>
        void copyOverlappingIf(
            const typename Bounds<Type>::Type& overlapping_bounds,
            const PredicateType& predicate,
            OutputIteratorType output_iterator
        ) const;

        template <class BoundsPredicateType, class PredicateType, class OutputIteratorType>
        void copyFilteredIf(
            const BoundsPredicateType& bounds_predicate,
            const PredicateType& predicate,
            OutputIteratorType output_iterator
        ) const;

        template <class FunctionType, class OutputIteratorType>
        void transform(const FunctionType& function, OutputIteratorType output_iterator) const;

        template <class FunctionType, class OutputIteratorType>
        void transformOverlapping(
            const FunctionType& function,
            const typename Bounds<Type>::Type& overlapping_bounds,
            OutputIteratorType output_iterator
        ) const;

        template <class FunctionType, class BoundsPredicateType, class OutputIteratorType>
        void transformFiltered(
            const FunctionType& function,
            const BoundsPredicateType& bounds_predicate,
            OutputIteratorType output_iterator
        ) const;

        template <class FunctionType, class PredicateType, class OutputIteratorType>
        void transformIf(
            const FunctionType& function,
            const PredicateType& predicate,
            OutputIteratorType output_iterator
        ) const;

        template <class FunctionType, class PredicateType, class OutputIteratorType>
        void transformOverlappingIf(
            const FunctionType& function,
            const typename Bounds<Type>::Type& overlapping_bounds,
            const PredicateType& predicate,
            OutputIteratorType output_iterator
        ) const;

        template <
            class FunctionType,
            class BoundsPredicateType,
            class PredicateType,
            class OutputIteratorType
        >
        void transformFilteredIf(
            const FunctionType& function,
            const BoundsPredicateType& bounds_predicate,
            const PredicateType& predicate,
            OutputIteratorType output_iterator
        ) const;
    };

    template <class Type>
    class SetInserter
    {
    private:
        Set<Type>* _set;
    public:
        SetInserter(Set<Type>* set);

        SetInserter<Type>& operator*();
        void operator=(const Type& item);
        SetInserter<Type>& operator++();
        SetInserter<Type>& operator++(int);
    };
    
    template <class Type>
    std::ostream& operator<<(std::ostream& stream, const SetNode<Type>& node);
    
    template <class Type>
    std::ostream& operator<<(std::ostream& stream, const Set<Type>& set);
}
    
////////// Specializations //////////

namespace opensolid
{
    template <class ItemType>
    struct Bounds<Set<ItemType>>
    {
        typedef typename Bounds<ItemType>::Type Type;

        const typename Bounds<ItemType>::Type& operator()(const Set<ItemType>& set) const;
    };
}
    
////////// Implementation //////////
    
namespace opensolid
{   
    template <class Type>
    inline Set<Type>::Set(Bounds<Type> bounds_function) :
        _root(OPENSOLID_NULLPTR), _bounds_function(bounds_function) {}
    
    template <class Type>
    inline Set<Type>::Set(const Set<Type>& other) :
        _root(other.isEmpty() ? OPENSOLID_NULLPTR : new SetNode<Type>(*other.root())),
        _bounds_function(other._bounds_function) {}
        
    template <class Type> template <class IteratorType>
    inline Set<Type>::Set(IteratorType begin, IteratorType end, Bounds<Type> bounds_function) :
        _bounds_function(bounds_function) {
        std::vector<SetNode<Type>*> nodes;
        std::transform(
            begin,
            end,
            std::back_inserter(nodes), 
            [&bounds_function] (const Type& item) {
                return new SetNode<Type>(item, bounds_function(item));
            }
        );
        if (nodes.empty()) {
            _root = OPENSOLID_NULLPTR;
        } else if (nodes.size() == 1) {
            _root = nodes[0];
        } else {
            typename Bounds<Type>::Type overall_bounds = nodes.front()->bounds();
            std::for_each(
                nodes.begin() + 1,
                nodes.end(),
                [&overall_bounds] (SetNode<Type>* node) {
                    overall_bounds = overall_bounds.hull(node->bounds());
                }
            );
            _root = new SetNode<Type>(overall_bounds, &nodes.front(), &nodes.back() + 1);
        }
    }
    
    template <class Type>
    inline Set<Type>::~Set() {clear();}
    
    template <class Type>
    inline std::size_t Set<Type>::size() const {return isEmpty() ? 0 : root()->size();}
    
    template <class Type>
    inline bool Set<Type>::isEmpty() const {return !root();}
    
    template <class Type>
    inline const SetNode<Type>* Set<Type>::root() const {return _root;}
        
    template <class Type>
    void Set<Type>::operator=(const Set<Type>& other) {
        if (this == &other) {return;}
        clear();
        if (!other.isEmpty()) {
            _root = new SetNode<Type>(*other.root());
        }
    }
    
    template <class Type>
    inline typename Bounds<Type>::Type
    Set<Type>::bounds() const {
        if (isEmpty()) {
            return Bounds<Type>::Type();
        } else {
            return root()->bounds();
        }
    }
    
    template <class Type>
    inline void Set<Type>::insert(const Type& object) {
        typename Bounds<Type>::Type bounds = _bounds_function(object);
        if (isEmpty()) {
            _root = new SetNode<Type>(object, bounds);
        } else {
            _root = _root->insert(object, bounds);
        }
    }
    
    template <class Type>
    inline std::size_t Set<Type>::erase(const Type& object) {
        if (isEmpty()) {
            return 0;
        } else {
            std::size_t previous_size = size();
            _root = _root->erase(object, _bounds_function(object));
            return previous_size - size();
        }
    }
    
    template <class Type> template <class IteratorType>
    inline void Set<Type>::insert(IteratorType begin, IteratorType end) {
        std::for_each(begin, end, [this] (const Type& object) {this->insert(object);});
    }
    
    template <class Type> template <class IteratorType>
    inline std::size_t Set<Type>::erase(IteratorType begin, IteratorType end) {
        return std::accumulate(
            begin,
            end,
            std::size_t(0),
            [this] (std::size_t result, const Type& object) {return result + this->erase(object);}
        );
    }
    
    template <class Type>
    inline void Set<Type>::clear() {
        if (_root) {
            delete _root;
            _root = OPENSOLID_NULLPTR;
        }
    }

    template <class Type>
    inline SetInserter<Type> Set<Type>::inserter() {return SetInserter<Type>(this);}

    namespace
    {
        template <class Type, class VisitorType, class BoundsPredicateType>
        void visitNode(
            const SetNode<Type>* node,
            const VisitorType& visitor,
            const BoundsPredicateType& bounds_predicate
        ) {
            if (bounds_predicate(node->bounds())) {
                if (node->object()) {
                    const_cast<VisitorType&>(visitor)(*node->object());
                } else {
                    visitNode(node->left(), visitor, bounds_predicate);
                    visitNode(node->right(), visitor, bounds_predicate);
                }
            }
        }
    }

    template <class Type> template <class VisitorType>
    void Set<Type>::forEach(const VisitorType& visitor) const {
        if (root()) {
            visitNode(root(), visitor, [] (const typename Bounds<Type>::Type&) {return true;});
        }
    }

    template <class Type> template <class VisitorType>
    void Set<Type>::forEachOverlapping(
        const typename Bounds<Type>::Type& overlapping_bounds,
        const VisitorType& visitor
    ) const {
        if (root()) {
            visitNode(
                root(),
                visitor,
                [&overlapping_bounds] (const typename Bounds<Type>::Type& bounds) {
                    return bounds.overlaps(overlapping_bounds);
                }
            );
        }
    }

    template <class Type> template <class VisitorType, class BoundsPredicateType>
    inline void Set<Type>::forEachFiltered(
        const BoundsPredicateType& bounds_predicate,
        const VisitorType& visitor
    ) const {if (root()) {visitNode(root(), visitor, bounds_predicate);}}

    template <class Type>
    template <class VisitorType, class PredicateType>
    void Set<Type>::forEachIf(const PredicateType& predicate, const VisitorType& visitor) const {
        if (root()) {
            visitNode(
                root(),
                [&visitor, &predicate] (const Type& item) {
                    if (predicate(item)) {const_cast<VisitorType&>(visitor)(item);}
                },
                [] (const typename Bounds<Type>::Type&) {return true;}
            );
        }
    }

    template <class Type> template <class VisitorType, class PredicateType>
    void Set<Type>::forEachOverlappingIf(
        const typename Bounds<Type>::Type& overlapping_bounds,
        const PredicateType& predicate,
        const VisitorType& visitor
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&visitor, &predicate] (const Type& item) {
                    if (predicate(item)) {const_cast<VisitorType&>(visitor)(item);}
                },
                [&overlapping_bounds] (const typename Bounds<Type>::Type& bounds) {
                    return bounds.overlaps(overlapping_bounds);
                }
            );
        }
    }

    template <class Type>
    template <class VisitorType, class BoundsPredicateType, class PredicateType>
    void Set<Type>::forEachFilteredIf(
        const BoundsPredicateType& bounds_predicate,
        const PredicateType& predicate,
        const VisitorType& visitor
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&visitor, &predicate] (const Type& item) {
                    if (predicate(item)) {const_cast<VisitorType&>(visitor)(item);}
                },
                bounds_predicate
            );
        }
    }

    template <class Type> template<class OutputIteratorType>
    void Set<Type>::copy(OutputIteratorType output_iterator) const {
        if (root()) {
            visitNode(
                root(),
                [&output_iterator] (const Type& item) {
                    *output_iterator = item;
                    ++output_iterator;
                },
                [] (const typename Bounds<Type>::Type&) {return true;}
            );
        }
    }

    template <class Type> template<class OutputIteratorType>
    void Set<Type>::copyOverlapping(
        const typename Bounds<Type>::Type& overlapping_bounds,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&output_iterator] (const Type& item) {
                    *output_iterator = item;
                    ++output_iterator;
                },
                [&overlapping_bounds] (const typename Bounds<Type>::Type& bounds) {
                    return bounds.overlaps(overlapping_bounds);
                }
            );
        }
    }

    template <class Type> template <class BoundsPredicateType, class OutputIteratorType>
    void Set<Type>::copyFiltered(
        const BoundsPredicateType& bounds_predicate,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&output_iterator] (const Type& item) {
                    *output_iterator = item;
                    ++output_iterator;
                },
                bounds_predicate
            );
        }
    }

    template <class Type> template <class PredicateType, class OutputIteratorType>
    void Set<Type>::copyIf(
        const PredicateType& predicate,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&predicate, &output_iterator] (const Type& item) {
                    if (predicate(item)) {
                        *output_iterator = item;
                        ++output_iterator;
                    }
                },
                [] (const typename Bounds<Type>::Type&) {return true;}
            );
        }
    }

    template <class Type> template <class PredicateType, class OutputIteratorType>
    void Set<Type>::copyOverlappingIf(
        const typename Bounds<Type>::Type& overlapping_bounds,
        const PredicateType& predicate,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&predicate, &output_iterator] (const Type& item) {
                    if (predicate(item)) {
                        *output_iterator = item;
                        ++output_iterator;
                    }
                },
                [&overlapping_bounds] (const typename Bounds<Type>::Type& bounds) {
                    return bounds.overlaps(overlapping_bounds);
                }
            );
        }
    }

    template <class Type>
    template <class BoundsPredicateType, class PredicateType, class OutputIteratorType>
    void Set<Type>::copyFilteredIf(
        const BoundsPredicateType& bounds_predicate,
        const PredicateType& predicate,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&predicate, &output_iterator] (const Type& item) {
                    if (predicate(item)) {
                        *output_iterator = item;
                        ++output_iterator;
                    }
                },
                bounds_predicate
            );
        }
    }

    template <class Type>
    template <class FunctionType, class OutputIteratorType>
    void Set<Type>::transform(
        const FunctionType& function,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&function, &output_iterator] (const Type& item) {
                    *output_iterator = function(item);
                    ++output_iterator;
                },
                [] (const typename Bounds<Type>::Type&) {return true;}
            );
        }
    }

    template <class Type> template <class FunctionType, class OutputIteratorType>
    void Set<Type>::transformOverlapping(
        const FunctionType& function,
        const typename Bounds<Type>::Type& overlapping_bounds,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&function, &output_iterator] (const Type& item) {
                    *output_iterator = function(item);
                    ++output_iterator;
                },
                [&overlapping_bounds] (const typename Bounds<Type>::Type& bounds) {
                    return bounds.overlaps(overlapping_bounds);
                }
            );
        }
    }

    template <class Type>
    template <class FunctionType, class BoundsPredicateType, class OutputIteratorType>
    void Set<Type>::transformFiltered(
        const FunctionType& function,
        const BoundsPredicateType& bounds_predicate,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&function, &output_iterator] (const Type& item) {
                    *output_iterator = function(item);
                    ++output_iterator;
                },
                bounds_predicate
            );
        }
    }

    template <class Type>
    template <class FunctionType, class PredicateType, class OutputIteratorType>
    void Set<Type>::transformIf(
        const FunctionType& function,
        const PredicateType& predicate,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&function, &predicate, &output_iterator] (const Type& item) {
                    if (predicate(item)) {
                        *output_iterator = function(item);
                        ++output_iterator;
                    }
                },
                [] (const typename Bounds<Type>::Type&) {return true;}
            );
        }
    }

    template <class Type>
    template <class FunctionType, class PredicateType, class OutputIteratorType>
    void Set<Type>::transformOverlappingIf(
        const FunctionType& function,
        const typename Bounds<Type>::Type& overlapping_bounds,
        const PredicateType& predicate,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&function, &predicate, &output_iterator] (const Type& item) {
                    if (predicate(item)) {
                        *output_iterator = function(item);
                        ++output_iterator;
                    }
                },
                [&overlapping_bounds] (const typename Bounds<Type>::Type& bounds) {
                    return bounds.overlaps(overlapping_bounds);
                }
            );
        }
    }

    template <class Type>
    template <
        class FunctionType,
        class BoundsPredicateType,
        class PredicateType,
        class OutputIteratorType
    >
    void Set<Type>::transformFilteredIf(
        const FunctionType& function,
        const BoundsPredicateType& bounds_predicate,
        const PredicateType& predicate,
        OutputIteratorType output_iterator
    ) const {
        if (root()) {
            visitNode(
                root(),
                [&function, &predicate, &output_iterator] (const Type& item) {
                    if (predicate(item)) {
                        *output_iterator = function(item);
                        ++output_iterator;
                    }
                },
                bounds_predicate
            );
        }
    }

    template <class Type>
    inline SetInserter<Type>::SetInserter(Set<Type>* set) : _set(set) {}

    template <class Type>
    inline SetInserter<Type>& SetInserter<Type>::operator*() {return *this;}
    
    template <class Type>
    inline void SetInserter<Type>::operator=(const Type& item) {_set->insert(item);}
    
    template <class Type>
    inline SetInserter<Type>& SetInserter<Type>::operator++() {return *this;}
    
    template <class Type>
    inline SetInserter<Type>& SetInserter<Type>::operator++(int) {return *this;}

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
        if (set.isEmpty()) {
            stream << "{}";
        } else {
            stream << *set.root();
        }
        return stream;
    }

    template <class ItemType>
    inline const typename Bounds<ItemType>::Type& Bounds<Set<ItemType>>::operator()(
        const Set<ItemType>& set
    ) const {return set.bounds();}
}
