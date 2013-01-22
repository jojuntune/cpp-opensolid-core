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

#include "Set/SetNode.hpp"

#include <OpenSolid/Core/Bounds.hpp>

#include <ostream>
#include <algorithm>
#include <functional>
#include <numeric>

namespace opensolid
{
    template <class TElement>
    class SetInserter;

    template <class TElement>
    class Set
    {
    private:
        SetNode<TElement>* _root;
        Bounds<TElement> _boundsFunction;
    public:
        Set(Bounds<TElement> boundsFunction = Bounds<TElement>());
        
        Set(const Set<TElement>& otherSet);
        
        template <class TIterator>
        Set(TIterator begin, TIterator end, Bounds<TElement> boundsFunction = Bounds<TElement>());
        
        ~Set();
        
        const SetNode<TElement>* root() const;
        
        void operator=(const Set<TElement>& otherSet);
        
        std::size_t size() const;
        bool isEmpty() const;
        const typename Bounds<TElement>::Type& bounds() const;
        
        void insert(const TElement& element);
        std::size_t erase(const TElement& element);
        
        template <class TIterator>
        void insert(TIterator begin, TIterator end);
        
        template <class TIterator>
        std::size_t erase(TIterator begin, TIterator end);
        
        void clear();

        SetInserter<TElement> inserter();

        template <class TVisitor>
        void forEach(
            const TVisitor& visitor
        ) const;

        template <class TVisitor>
        void forEachOverlapping(
            const typename Bounds<TElement>::Type& predicateBounds,
            const TVisitor& visitor
        ) const;

        template <class TBoundsPredicate, class TVisitor>
        void forEachFiltered(
            const TBoundsPredicate& boundsPredicate,
            const TVisitor& visitor
        ) const;

        template <class TElementPredicate, class TVisitor>
        void forEachIf(
            const TElementPredicate& elementPredicate,
            const TVisitor& visitor
        ) const;

        template <class TElementPredicate, class TVisitor>
        void forEachOverlappingIf(
            const typename Bounds<TElement>::Type& predicateBounds,
            const TElementPredicate& elementPredicate,
            const TVisitor& visitor
        ) const;

        template <class TBoundsPredicate, class TElementPredicate, class TVisitor>
        void forEachFilteredIf(
            const TBoundsPredicate& boundsPredicate,
            const TElementPredicate& elementPredicate,
            const TVisitor& visitor
        ) const;

        template <class TOutputIterator>
        void copy(
            TOutputIterator outputIterator
        ) const;

        template<class TOutputIterator>
        void copyOverlapping(
            const typename Bounds<TElement>::Type& predicateBounds,
            TOutputIterator outputIterator
        ) const;

        template <class TBoundsPredicate, class TOutputIterator>
        void copyFiltered(
            const TBoundsPredicate& boundsPredicate,
            TOutputIterator outputIterator
        ) const;

        template <class TElementPredicate, class TOutputIterator>
        void copyIf(
            const TElementPredicate& elementPredicate,
            TOutputIterator outputIterator
        ) const;

        template <class TElementPredicate, class TOutputIterator>
        void copyOverlappingIf(
            const typename Bounds<TElement>::Type& predicateBounds,
            const TElementPredicate& elementPredicate,
            TOutputIterator outputIterator
        ) const;

        template <class TBoundsPredicate, class TElementPredicate, class TOutputIterator>
        void copyFilteredIf(
            const TBoundsPredicate& boundsPredicate,
            const TElementPredicate& elementPredicate,
            TOutputIterator outputIterator
        ) const;

        template <class TFunction, class TOutputIterator>
        void transform(
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;

        template <class TFunction, class TOutputIterator>
        void transformOverlapping(
            const typename Bounds<TElement>::Type& predicateBounds,
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;

        template <class TBoundsPredicate, class TFunction, class TOutputIterator>
        void transformFiltered(
            const TBoundsPredicate& boundsPredicate,
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;

        template <class TElementPredicate, class TFunction, class TOutputIterator>
        void transformIf(
            const TElementPredicate& predicate,
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;

        template <class TElementPredicate, class TFunction, class TOutputIterator>
        void transformOverlappingIf(
            const typename Bounds<TElement>::Type& predicateBounds,
            const TElementPredicate& elementPredicate,
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;

        template <class TBoundsPredicate, class TElementPredicate, class TFunction, class TOutputIterator>
        void transformFilteredIf(
            const TBoundsPredicate& boundsPredicate,
            const TElementPredicate& elementPredicate,
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;
    };

    template <class TElement>
    class SetInserter
    {
    private:
        Set<TElement>* _set;
    public:
        SetInserter(Set<TElement>* set);

        SetInserter<TElement>& operator*();
        void operator=(const TElement& element);
        SetInserter<TElement>& operator++();
        SetInserter<TElement>& operator++(int);
    };
    
    template <class TElement>
    std::ostream& operator<<(std::ostream& stream, const SetNode<TElement>& node);
    
    template <class TElement>
    std::ostream& operator<<(std::ostream& stream, const Set<TElement>& set);
}
    
////////// Specializations //////////

namespace opensolid
{
    template <class TElement>
    struct Bounds<Set<TElement>>
    {
        typedef typename Bounds<TElement>::Type Type;

        const typename Bounds<TElement>::Type& operator()(const Set<TElement>& set) const;
    };
}
    
////////// Implementation //////////
    
namespace opensolid
{   
    template <class TElement>
    inline Set<TElement>::Set(Bounds<TElement> boundsFunction) :
        _root(OPENSOLID_NULLPTR), _boundsFunction(boundsFunction) {
    }
    
    template <class TElement>
    inline Set<TElement>::Set(const Set<TElement>& otherSet) :
        _root(otherSet.isEmpty() ? OPENSOLID_NULLPTR : new SetNode<TElement>(*otherSet.root())),
        _boundsFunction(otherSet._boundsFunction) {
    }
        
    template <class TElement> template <class TIterator>
    inline Set<TElement>::Set(TIterator begin, TIterator end, Bounds<TElement> boundsFunction) :
        _boundsFunction(boundsFunction) {
        std::vector<SetNode<TElement>*> nodes;
        std::transform(
            begin,
            end,
            std::back_inserter(nodes), 
            [boundsFunction] (const TElement& element) {
                return new SetNode<TElement>(element, boundsFunction(element));
            }
        );
        if (nodes.empty()) {
            _root = OPENSOLID_NULLPTR;
        } else if (nodes.size() == 1) {
            _root = nodes[0];
        } else {
            typename Bounds<TElement>::Type overallBounds = nodes.front()->bounds();
            std::for_each(
                nodes.begin() + 1,
                nodes.end(),
                [&overallBounds] (SetNode<TElement>* node) {
                    overallBounds = overallBounds.hull(node->bounds());
                }
            );
            _root = new SetNode<TElement>(overallBounds, &nodes.front(), &nodes.back() + 1);
        }
    }
    
    template <class TElement>
    inline Set<TElement>::~Set() {
        clear();
    }
    
    template <class TElement>
    inline std::size_t Set<TElement>::size() const {
        return isEmpty() ? 0 : root()->size();
    }
    
    template <class TElement>
    inline bool Set<TElement>::isEmpty() const {
        return !root();
    }
    
    template <class TElement>
    inline const SetNode<TElement>* Set<TElement>::root() const {
        return _root;
    }
        
    template <class TElement>
    void Set<TElement>::operator=(const Set<TElement>& otherSet) {
        if (this == &otherSet) {
            return;
        }
        clear();
        if (!otherSet.isEmpty()) {
            _root = new SetNode<TElement>(*otherSet.root());
        }
    }
    
    template <class TElement>
    inline const typename Bounds<TElement>::Type&
    Set<TElement>::bounds() const {
        assert(!isEmpty());
        return root()->bounds();
    }
    
    template <class TElement>
    inline void Set<TElement>::insert(const TElement& element) {
        typename Bounds<TElement>::Type bounds = _boundsFunction(element);
        if (isEmpty()) {
            _root = new SetNode<TElement>(element, bounds);
        } else {
            _root = _root->insert(element, bounds);
        }
    }
    
    template <class TElement>
    inline std::size_t Set<TElement>::erase(const TElement& element) {
        if (isEmpty()) {
            return 0;
        } else {
            std::size_t previousSize = size();
            _root = _root->erase(element, _boundsFunction(element));
            return previousSize - size();
        }
    }
    
    template <class TElement> template <class TIterator>
    inline void Set<TElement>::insert(TIterator begin, TIterator end) {
        std::for_each(
            begin,
            end,
            [this] (const TElement& element) {
                this->insert(element);
            }
        );
    }
    
    template <class TElement> template <class TIterator>
    inline std::size_t Set<TElement>::erase(TIterator begin, TIterator end) {
        return std::accumulate(
            begin,
            end,
            std::size_t(0),
            [this] (std::size_t result, const TElement& element) {
                return result + this->erase(element);
            }
        );
    }
    
    template <class TElement>
    inline void Set<TElement>::clear() {
        if (_root) {
            delete _root;
            _root = OPENSOLID_NULLPTR;
        }
    }

    template <class TElement>
    inline SetInserter<TElement> Set<TElement>::inserter() {
        return SetInserter<TElement>(this);
    }

    namespace detail
    {
        template <class TElement, class TVisitor>
        void visitNodes(
            const SetNode<TElement>* root,
            const TVisitor& visitor
        ) {
            if (root->element()) {
                const_cast<TVisitor&>(visitor)(*root->element());
            } else {
                visitNodes(root->leftChild(), visitor);
                visitNodes(root->rightChild(), visitor);
            }
        }

        template <class TElement, class TBoundsPredicate, class TVisitor>
        void visitFilteredNodes(
            const SetNode<TElement>* root,
            const TBoundsPredicate& boundsPredicate,
            const TVisitor& visitor
        ) {
            if (boundsPredicate(root->bounds())) {
                if (root->element()) {
                    const_cast<TVisitor&>(visitor)(*root->element());
                } else {
                    visitFilteredNodes(root->leftChild(), boundsPredicate, visitor);
                    visitFilteredNodes(root->rightChild(), boundsPredicate, visitor);
                }
            }
        }
    }

    template <class TElement>
    template <class TVisitor>
    void Set<TElement>::forEach(
        const TVisitor& visitor
    ) const {
        if (root()) {
            detail::visitNodes(
                root(),
                visitor
            );
        }
    }

    template <class TElement>
    template <class TVisitor>
    void Set<TElement>::forEachOverlapping(
        const typename Bounds<TElement>::Type& predicateBounds,
        const TVisitor& visitor
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename Bounds<TElement>::Type& bounds) {
                    return bounds.overlaps(predicateBounds);
                },
                visitor
            );
        }
    }

    template <class TElement>
    template <class TBoundsPredicate, class TVisitor>
    inline void Set<TElement>::forEachFiltered(
        const TBoundsPredicate& boundsPredicate,
        const TVisitor& visitor
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                boundsPredicate,
                visitor
            );
        }
    }

    template <class TElement>
    template <class TElementPredicate, class TVisitor>
    void Set<TElement>::forEachIf(
        const TElementPredicate& elementPredicate,
        const TVisitor& visitor
    ) const {
        if (root()) {
            detail::visitNodes(
                root(),
                [&visitor, &elementPredicate] (const TElement& element) {
                    if (elementPredicate(element)) {
                        const_cast<TVisitor&>(visitor)(element);
                    }
                }
            );
        }
    }

    template <class TElement>
    template <class TElementPredicate, class TVisitor>
    void Set<TElement>::forEachOverlappingIf(
        const typename Bounds<TElement>::Type& predicateBounds,
        const TElementPredicate& elementPredicate,
        const TVisitor& visitor
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename Bounds<TElement>::Type& bounds) {
                    return bounds.overlaps(predicateBounds);
                },
                [&visitor, &elementPredicate] (const TElement& element) {
                    if (elementPredicate(element)) {
                        const_cast<TVisitor&>(visitor)(element);
                    }
                }
            );
        }
    }

    template <class TElement>
    template <class TBoundsPredicate, class TElementPredicate, class TVisitor>
    void Set<TElement>::forEachFilteredIf(
        const TBoundsPredicate& boundsPredicate,
        const TElementPredicate& elementPredicate,
        const TVisitor& visitor
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                boundsPredicate,
                [&visitor, &elementPredicate] (const TElement& element) {
                    if (elementPredicate(element)) {
                        const_cast<TVisitor&>(visitor)(element);
                    }
                }
            );
        }
    }

    template <class TElement> template<class TOutputIterator>
    void Set<TElement>::copy(
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitNodes(
                root(),
                [&outputIterator] (const TElement& element) {
                    *outputIterator = element;
                    ++outputIterator;
                }
            );
        }
    }

    template <class TElement> template<class TOutputIterator>
    void Set<TElement>::copyOverlapping(
        const typename Bounds<TElement>::Type& predicateBounds,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename Bounds<TElement>::Type& bounds) {
                    return bounds.overlaps(predicateBounds);
                },
                [&outputIterator] (const TElement& element) {
                    *outputIterator = element;
                    ++outputIterator;
                }
            );
        }
    }

    template <class TElement> template <class TBoundsPredicate, class TOutputIterator>
    void Set<TElement>::copyFiltered(
        const TBoundsPredicate& boundsPredicate,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                boundsPredicate,
                [&outputIterator] (const TElement& element) {
                    *outputIterator = element;
                    ++outputIterator;
                }
            );
        }
    }

    template <class TElement> template <class TElementPredicate, class TOutputIterator>
    void Set<TElement>::copyIf(
        const TElementPredicate& elementPredicate,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitNodes(
                root(),
                [&elementPredicate, &outputIterator] (const TElement& element) {
                    if (elementPredicate(element)) {
                        *outputIterator = element;
                        ++outputIterator;
                    }
                }
            );
        }
    }

    template <class TElement> template <class TElementPredicate, class TOutputIterator>
    void Set<TElement>::copyOverlappingIf(
        const typename Bounds<TElement>::Type& predicateBounds,
        const TElementPredicate& elementPredicate,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename Bounds<TElement>::Type& bounds) {
                    return bounds.overlaps(predicateBounds);
                },
                [&elementPredicate, &outputIterator] (const TElement& element) {
                    if (elementPredicate(element)) {
                        *outputIterator = element;
                        ++outputIterator;
                    }
                }
            );
        }
    }

    template <class TElement>
    template <class TBoundsPredicate, class TElementPredicate, class TOutputIterator>
    void Set<TElement>::copyFilteredIf(
        const TBoundsPredicate& boundsPredicate,
        const TElementPredicate& elementPredicate,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                boundsPredicate,
                [&elementPredicate, &outputIterator] (const TElement& element) {
                    if (elementPredicate(element)) {
                        *outputIterator = element;
                        ++outputIterator;
                    }
                }
            );
        }
    }

    template <class TElement>
    template <class TFunction, class TOutputIterator>
    void Set<TElement>::transform(
        const TFunction& function,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitNodes(
                root(),
                [&function, &outputIterator] (const TElement& element) {
                    *outputIterator = function(element);
                    ++outputIterator;
                }
            );
        }
    }

    template <class TElement>
    template <class TFunction, class TOutputIterator>
    void Set<TElement>::transformOverlapping(
        const typename Bounds<TElement>::Type& predicateBounds,
        const TFunction& function,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename Bounds<TElement>::Type& bounds) {
                    return bounds.overlaps(predicateBounds);
                },
                [&function, &outputIterator] (const TElement& element) {
                    *outputIterator = function(element);
                    ++outputIterator;
                }
            );
        }
    }

    template <class TElement>
    template <class TBoundsPredicate, class TFunction, class TOutputIterator>
    void Set<TElement>::transformFiltered(
        const TBoundsPredicate& boundsPredicate,
        const TFunction& function,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                boundsPredicate,
                [&function, &outputIterator] (const TElement& element) {
                    *outputIterator = function(element);
                    ++outputIterator;
                }
            );
        }
    }

    template <class TElement>
    template <class TElementPredicate, class TFunction, class TOutputIterator>
    void Set<TElement>::transformIf(
        const TElementPredicate& elementPredicate,
        const TFunction& function,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitNodes(
                root(),
                [&function, &elementPredicate, &outputIterator] (const TElement& element) {
                    if (elementPredicate(element)) {
                        *outputIterator = function(element);
                        ++outputIterator;
                    }
                }
            );
        }
    }

    template <class TElement>
    template <class TElementPredicate, class TFunction, class TOutputIterator>
    void Set<TElement>::transformOverlappingIf(
        const typename Bounds<TElement>::Type& predicateBounds,
        const TElementPredicate& elementPredicate,
        const TFunction& function,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename Bounds<TElement>::Type& bounds) {
                    return bounds.overlaps(predicateBounds);
                },
                [&function, &elementPredicate, &outputIterator] (const TElement& element) {
                    if (elementPredicate(element)) {
                        *outputIterator = function(element);
                        ++outputIterator;
                    }
                }
            );
        }
    }

    template <class TElement>
    template <class TBoundsPredicate, class TElementPredicate, class TFunction, class TOutputIterator>
    void Set<TElement>::transformFilteredIf(
        const TBoundsPredicate& boundsPredicate,
        const TElementPredicate& elementPredicate,
        const TFunction& function,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                boundsPredicate,
                [&function, &elementPredicate, &outputIterator] (const TElement& element) {
                    if (elementPredicate(element)) {
                        *outputIterator = function(element);
                        ++outputIterator;
                    }
                }
            );
        }
    }

    template <class TElement>
    inline SetInserter<TElement>::SetInserter(Set<TElement>* set) : _set(set) {
    }

    template <class TElement>
    inline SetInserter<TElement>& SetInserter<TElement>::operator*() {
        return *this;
    }
    
    template <class TElement>
    inline void SetInserter<TElement>::operator=(const TElement& element) {
        _set->insert(element);
    }
    
    template <class TElement>
    inline SetInserter<TElement>& SetInserter<TElement>::operator++() {
        return *this;
    }
    
    template <class TElement>
    inline SetInserter<TElement>& SetInserter<TElement>::operator++(int) {
        return *this;
    }

    template <class TElement>
    std::ostream& operator<<(std::ostream& stream, const SetNode<TElement>& node) {
        stream << "{";
        if (node.element()) {
            stream << *node.element();
        } else {
            stream << *node.left();
            stream << ",";
            stream << *node.right();
        }
        stream << "}";
        return stream;
    }
    
    template <class TElement>
    std::ostream& operator<<(std::ostream& stream, const Set<TElement>& set) {
        if (set.isEmpty()) {
            stream << "{}";
        } else {
            stream << *set.root();
        }
        return stream;
    }

    template <class TElement>
    inline const typename Bounds<TElement>::Type& Bounds<Set<TElement>>::operator()(
        const Set<TElement>& set
    ) const {
        return set.bounds();
    }
}
