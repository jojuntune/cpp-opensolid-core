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
            typename BoundsFunction<TElement>::ResultType overallBounds = nodes.front()->bounds();
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
    void
    Set<TElement>::operator=(const Set<TElement>& otherSet) {
        if (this == &otherSet) {
            return;
        }
        clear();
        if (!otherSet.isEmpty()) {
            _root = new SetNode<TElement>(*otherSet.root());
        }
    }
    
    template <class TElement>
    inline typename BoundsFunction<TElement>::ResultType
    Set<TElement>::bounds() const {
        if (isEmpty()) {
            return typename BoundsFunction<TElement>::ResultType();
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
        typename BoundsFunction<TElement>::ResultType bounds = _boundsFunction(element);
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
        const typename BoundsFunction<TElement>::ResultType& predicateBounds,
        const TVisitor& visitor
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsFunction<TElement>::ResultType& bounds) {
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
        const typename BoundsFunction<TElement>::ResultType& predicateBounds,
        const TElementPredicate& elementPredicate,
        const TVisitor& visitor
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsFunction<TElement>::ResultType& bounds) {
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
        const typename BoundsFunction<TElement>::ResultType& predicateBounds,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsFunction<TElement>::ResultType& bounds) {
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
        const typename BoundsFunction<TElement>::ResultType& predicateBounds,
        const TElementPredicate& elementPredicate,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsFunction<TElement>::ResultType& bounds) {
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
    Set<TElement>::transform(
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
    Set<TElement>::transformOverlapping(
        const typename BoundsFunction<TElement>::ResultType& predicateBounds,
        const TFunction& function,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsFunction<TElement>::ResultType& bounds) {
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
    Set<TElement>::transformFiltered(
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
    Set<TElement>::transformIf(
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
    Set<TElement>::transformOverlappingIf(
        const typename BoundsFunction<TElement>::ResultType& predicateBounds,
        const TElementPredicate& elementPredicate,
        const TFunction& function,
        TOutputIterator outputIterator
    ) const {
        if (root()) {
            detail::visitFilteredNodes(
                root(),
                [&predicateBounds] (const typename BoundsFunction<TElement>::ResultType& bounds) {
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
    Set<TElement>::transformFilteredIf(
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

    template <class TElement>
    Set<TElement>
    ScalingFunction<Set<TElement>>::operator()(const Set<TElement>& set, double scale) const {
        ScalingFunction<TElement> scalingFunction;
        std::vector<TElement> scaledElements;
        set.transform(
            [scale, scalingFunction] (const TElement& element) -> TElement {
                return scalingFunction(element, scale);
            },
            std::back_inserter(scaledElements)
        );
        return Set<TElement>(scaledElements.begin(), scaledElements.end());
    }

    template <class TElement> template <class TVector>
    Set<TElement>
    TranslationFunction<Set<TElement>>::operator()(
        const Set<TElement>& set,
        const EigenBase<TVector>& vector
    ) const {
        TranslationFunction<TElement> translationFunction;
        std::vector<TElement> translatedElements;
        set.transform(
            [&vector, translationFunction] (const TElement& element) -> TElement {
                return translationFunction(element, vector);
            },
            std::back_inserter(translatedElements)
        );
        return Set<TElement>(translatedElements.begin(), translatedElements.end());
    }

    template <class TElement, int iNumTransformedDimensions> template <class TMatrix>
    Set<typename TransformationFunction<TElement, iNumTransformedDimensions>::ResultType>
    TransformationFunction<Set<TElement>, iNumTransformedDimensions>::operator()(
        const Set<TElement>& set,
        const EigenBase<TMatrix>& matrix
    ) const {
        typedef typename TransformationFunction<TElement, iNumTransformedDimensions>::ResultType
            TransformedElementType;

        TransformationFunction<TElement, iNumTransformedDimensions> transformationFunction;
        std::vector<TransformedElementType> transformedElements;
        set.transform(
            [transformationFunction, &matrix] (const TElement& element) -> TransformedElementType {
                return transformationFunction(element, matrix);
            },
            std::back_inserter(transformedElements)
        );
        return Set<TransformedElementType>(transformedElements.begin(), transformedElements.end());
    }

    template <class TElement, int iNumDestinationDimensions>
    Set<typename MappingFunction<TElement, iNumDestinationDimensions>::ResultType>
    MappingFunction<Set<TElement>, iNumDestinationDimensions>::operator()(
        const Set<TElement>& set,
        const Function& function
    ) const {
        typedef typename MappingFunction<TElement, iNumDestinationDimensions>::ResultType
            MappedElementType;

        MappingFunction<TElement, iNumDestinationDimensions> mappingFunction;
        std::vector<MappedElementType> mappedElements;
        set.transform(
            [mappingFunction, &function] (const TElement& element) -> MappedElementType {
                return mappingFunction(element, function);
            },
            std::back_inserter(mappedElements)
        );
        return Set<MappedElementType>(mappedElements.begin(), mappedElements.end());
    }

    template <class TElement>
    inline typename BoundsFunction<TElement>::ResultType
    BoundsFunction<Set<TElement>>::operator()(const Set<TElement>& set) const {
        return set.bounds();
    }
}
