/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Set.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/Set/SetInserter.hpp>
#include <OpenSolid/Core/Set/SetNode.hpp>
#include <OpenSolid/Core/Transformable.hpp>

#include <algorithm>
#include <functional>
#include <numeric>

namespace opensolid
{   
    template <class TElement>
    inline
    Set<TElement>::Set(BoundsFunction<TElement> boundsFunction) :
        _root(nullptr), _boundsFunction(boundsFunction) {
    }
    
    template <class TElement>
    inline
    Set<TElement>::Set(const Set<TElement>& otherSet) :
        _root(otherSet.isEmpty() ? nullptr : new SetNode<TElement>(*otherSet.root())),
        _boundsFunction(otherSet._boundsFunction) {
    }

    template <class TElement>
    inline
    Set<TElement>::Set(Set<TElement>&& otherSet) :
        _root(otherSet._root),
        _boundsFunction(otherSet._boundsFunction) {

        otherSet._root = nullptr;
    }
        
    template <class TElement> template <class TIterator>
    inline
    Set<TElement>::Set(
        TIterator begin,
        TIterator end,
        BoundsFunction<TElement> boundsFunction
    ) : _boundsFunction(boundsFunction) {

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
            _root = nullptr;
        } else if (nodes.size() == 1) {
            _root = nodes[0];
        } else {
            typename BoundsType<TElement>::Type overallBounds = nodes.front()->bounds();
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
    inline
    Set<TElement>::~Set() {
        clear();
    }
    
    template <class TElement>
    inline std::int64_t
    Set<TElement>::size() const {
        return isEmpty() ? 0 : root()->size();
    }
    
    template <class TElement>
    inline bool
    Set<TElement>::isEmpty() const {
        return !root();
    }
    
    template <class TElement>
    inline const SetNode<TElement>*
    Set<TElement>::root() const {
        return _root;
    }

    template <class TElement>
    inline void
    Set<TElement>::swap(Set<TElement>& otherSet) {
        std::swap(_root, otherSet._root);
        std::swap(_boundsFunction, otherSet._boundsFunction);
    }
        
    template <class TElement>
    void
    Set<TElement>::operator=(const Set<TElement>& otherSet) {
        if (this == &otherSet) {
            return;
        }
        clear();
        if (!otherSet.isEmpty()) {
            _root = new SetNode<TElement>(*otherSet.root());
            _boundsFunction = otherSet._boundsFunction;
        }
    }

    template <class TElement>
    inline void
    Set<TElement>::operator=(Set<TElement>&& otherSet) {
        swap(otherSet);
    }
    
    template <class TElement>
    inline typename BoundsType<TElement>::Type
    Set<TElement>::bounds() const {
        if (isEmpty()) {
            return typename BoundsType<TElement>::Type();
        } else {
            return root()->bounds();
        }
    }

    template <class TElement>
    inline TElement
    Set<TElement>::atIndex(std::int64_t index) const {
        if (isEmpty()) {
            return TElement();
        } else {
            if (const SetNode<TElement>* nodeAtIndex = root()->nodeAtIndex(index)) {
                assert(nodeAtIndex->element());
                return *nodeAtIndex->element();
            } else {
                return TElement();
            }
        }
    }

    template <class TElement>
    inline std::int64_t
    Set<TElement>::indexOf(const TElement& element) const {
        if (isEmpty()) {
            return -1;
        } else {
            return root()->indexOf(element, _boundsFunction(element));
        }
    }
    
    template <class TElement>
    inline void
    Set<TElement>::insert(const TElement& element) {
        typename BoundsType<TElement>::Type bounds = _boundsFunction(element);
        if (isEmpty()) {
            _root = new SetNode<TElement>(element, bounds);
        } else {
            _root = _root->insert(element, bounds);
        }
    }
    
    template <class TElement>
    inline std::int64_t
    Set<TElement>::erase(const TElement& element) {
        if (isEmpty()) {
            return 0;
        } else {
            std::int64_t previousSize = size();
            _root = _root->erase(element, _boundsFunction(element));
            return previousSize - size();
        }
    }
    
    template <class TElement> template <class TIterator>
    inline void
    Set<TElement>::insert(TIterator begin, TIterator end) {
        std::for_each(
            begin,
            end,
            [this] (const TElement& element) {
                this->insert(element);
            }
        );
    }
    
    template <class TElement> template <class TIterator>
    inline std::int64_t
    Set<TElement>::erase(TIterator begin, TIterator end) {
        return std::accumulate(
            begin,
            end,
            std::int64_t(0),
            [this] (std::int64_t result, const TElement& element) {
                return result + this->erase(element);
            }
        );
    }
    
    template <class TElement>
    inline void
    Set<TElement>::clear() {
        if (_root) {
            delete _root;
            _root = nullptr;
        }
    }

    template <class TElement>
    inline SetInserter<TElement> Set<TElement>::inserter() {
        return SetInserter<TElement>(this);
    }

    template <class TElement>
    inline Set<TElement>
    Set<TElement>::overlapping(const typename BoundsType<TElement>::Type& bounds) const {
        std::vector<TElement> overlappingElements;
        copyOverlapping(bounds, std::back_inserter(overlappingElements));
        return Set<TElement>(overlappingElements.begin(), overlappingElements.end());
    }

    template <class TElement> template <class TBoundsPredicate>
    inline Set<TElement>
    Set<TElement>::filtered(const TBoundsPredicate& boundsPredicate) const {
        std::vector<TElement> filteredElements;
        copyFiltered(boundsPredicate, std::back_inserter(filteredElements));
        return Set<TElement>(filteredElements.begin(), filteredElements.end());
    }

    template <class TElement> template <class TFunction>
    inline Set<typename std::decay<typename std::result_of<TFunction(TElement)>::type>::type>
    Set<TElement>::mapped(const TFunction& function) const {
        typedef typename std::decay<typename std::result_of<TFunction(TElement)>::type>::type MappedElementType;
        std::vector<MappedElementType> mappedElements(size());
        map(function, mappedElements.begin());
        return Set<MappedElementType>(mappedElements.begin(), mappedElements.end());
    }

    namespace detail
    {
        template <class TElement, class TVisitor>
        void
        visitNodes(
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
        void
        visitFilteredNodes(
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
    void
    Set<TElement>::forEach(
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
    void
    Set<TElement>::forEachOverlapping(
        const typename BoundsType<TElement>::Type& predicateBounds,
        const TVisitor& visitor
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsType<TElement>::Type& bounds) {
                    return bounds.overlaps(predicateBounds);
                },
                visitor
            );
        }
    }

    template <class TElement>
    template <class TBoundsPredicate, class TVisitor>
    void
    Set<TElement>::forEachFiltered(
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
    void
    Set<TElement>::forEachIf(
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
    void
    Set<TElement>::forEachOverlappingIf(
        const typename BoundsType<TElement>::Type& predicateBounds,
        const TElementPredicate& elementPredicate,
        const TVisitor& visitor
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsType<TElement>::Type& bounds) {
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
    void
    Set<TElement>::forEachFilteredIf(
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
    void
    Set<TElement>::copy(
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
    void
    Set<TElement>::copyOverlapping(
        const typename BoundsType<TElement>::Type& predicateBounds,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsType<TElement>::Type& bounds) {
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
    void
    Set<TElement>::copyFiltered(
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
    void
    Set<TElement>::copyIf(
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
    void
    Set<TElement>::copyOverlappingIf(
        const typename BoundsType<TElement>::Type& predicateBounds,
        const TElementPredicate& elementPredicate,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsType<TElement>::Type& bounds) {
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
    void
    Set<TElement>::copyFilteredIf(
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
    void
    Set<TElement>::map(
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
    void
    Set<TElement>::mapOverlapping(
        const typename BoundsType<TElement>::Type& predicateBounds,
        const TFunction& function,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsType<TElement>::Type& bounds) {
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
    void
    Set<TElement>::mapFiltered(
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
    void
    Set<TElement>::mapIf(
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
    void
    Set<TElement>::mapOverlappingIf(
        const typename BoundsType<TElement>::Type& predicateBounds,
        const TElementPredicate& elementPredicate,
        const TFunction& function,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsType<TElement>::Type& bounds) {
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
    void
    Set<TElement>::mapFilteredIf(
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
    std::ostream&
    operator<<(std::ostream& stream, const Set<TElement>& set) {
        if (set.isEmpty()) {
            stream << "{}";
        } else {
            stream << *set.root();
        }
        return stream;
    }

    namespace detail
    {
        template <class TElement>
        class SetElementScalingWrapper
        {
        private:
            double _scale;
        public:
            typedef TElement result_type;

            inline
            SetElementScalingWrapper(double scale) :
                _scale(scale) {
            }

            inline TElement
            operator()(const TElement& element) const {
                return Transformable<TElement>::scaling(element, _scale);
            }
        };
    }

    template <class TElement>
    Set<TElement>
    ScalingFunction<Set<TElement>>::operator()(const Set<TElement>& set, double scale) const {
        return set.mapped(detail::SetElementScalingWrapper<TElement>(scale));
    }

    namespace detail
    {
        template <class TElement, class TVector>
        class SetElementTranslationWrapper
        {
        private:
            TVector _vector;
        public:
            typedef TElement result_type;

            inline
            SetElementTranslationWrapper(const EigenBase<TVector>& vector) :
                _vector(vector.derived()) {
            }

            inline TElement
            operator()(const TElement& element) const {
                return Transformable<TElement>::translation(element, _vector);
            }
        };
    }

    template <class TElement> template <class TVector>
    Set<TElement>
    TranslationFunction<Set<TElement>>::operator()(
        const Set<TElement>& set,
        const EigenBase<TVector>& vector
    ) const {
        return set.mapped(
            detail::SetElementTranslationWrapper<TElement, TVector>(vector.derived())
        );
    }

    namespace detail
    {
        template <class TElement, int iNumTransformedDimensions, class TMatrix>
        class SetElementTransformationWrapper
        {
        private:
            TMatrix _matrix;
        public:
            typedef typename ChangeDimensions<TElement, iNumTransformedDimensions>::Type
                result_type;

            inline
            SetElementTransformationWrapper(const EigenBase<TMatrix>& matrix) :
                _matrix(matrix.derived()) {
            }

            inline result_type
            operator()(const TElement& element) const {
                return Transformable<TElement>::transformation(element, _matrix);
            }
        };
    }

    template <class TElement, int iNumTransformedDimensions> template <class TMatrix>
    Set<typename ChangeDimensions<TElement, iNumTransformedDimensions>::Type>
    TransformationFunction<Set<TElement>, iNumTransformedDimensions>::operator()(
        const Set<TElement>& set,
        const EigenBase<TMatrix>& matrix
    ) const {
        return set.mapped(
            detail::SetElementTransformationWrapper<TElement, iNumTransformedDimensions, TMatrix>(
                matrix.derived()
            )
        );
    }

    namespace detail
    {
        template <class TElement, int iNumDestinationDimensions>
        class SetElementMorphingWrapper
        {
        private:
            Function _function;
        public:
            typedef typename ChangeDimensions<TElement, iNumDestinationDimensions>::Type
                result_type;

            inline
            SetElementMorphingWrapper(const Function& function) :
                _function(function) {
            }

            inline result_type
            operator()(const TElement& element) const {
                return Transformable<TElement>::morphing(element, _function);
            }
        };
    }

    template <class TElement, int iNumDestinationDimensions>
    Set<typename ChangeDimensions<TElement, iNumDestinationDimensions>::Type>
    MorphingFunction<Set<TElement>, iNumDestinationDimensions>::operator()(
        const Set<TElement>& set,
        const Function& function
    ) const {
        return set.mapped(
            detail::SetElementMorphingWrapper<TElement, iNumDestinationDimensions>(function)
        );
    }
}
