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

#include <OpenSolid/Core/Set.declarations.hpp>

#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/BoundsFunction.definitions.hpp>
#include <OpenSolid/Core/BoundsFunction.declarations.hpp>

#include <cstdint>
#include <ostream>
#include <type_traits>

namespace opensolid
{
    template <class TElement>
    class Set :
        public Transformable<Set<TElement>>
    {
    private:
        SetNode<TElement>* _root;
        BoundsFunction<TElement> _boundsFunction;
    public:
        Set(BoundsFunction<TElement> boundsFunction = BoundsFunction<TElement>());
        
        Set(const Set<TElement>& otherSet);

        Set(Set<TElement>&& otherSet);
        
        template <class TIterator>
        Set(
            TIterator begin,
            TIterator end,
            BoundsFunction<TElement> boundsFunction = BoundsFunction<TElement>()
        );
        
        ~Set();
        
        const SetNode<TElement>*
        root() const;

        void
        swap(Set<TElement>& otherSet);
        
        void
        operator=(const Set<TElement>& otherSet);
        
        void
        operator=(Set<TElement>&& otherSet);
        
        std::int64_t
        size() const;

        bool
        isEmpty() const;

        typename BoundsType<TElement>::Type
        bounds() const;

        TElement
        atIndex(std::int64_t index) const;
        
        std::int64_t
        indexOf(const TElement& element) const;
        
        void
        insert(const TElement& element);

        std::int64_t
        erase(const TElement& element);
        
        template <class TIterator>
        void
        insert(TIterator begin, TIterator end);
        
        template <class TIterator>
        std::int64_t
        erase(TIterator begin, TIterator end);
        
        void
        clear();

        SetInserter<TElement>
        inserter();

        Set<TElement>
        overlapping(const typename BoundsType<TElement>::Type& bounds) const;

        template <class TBoundsPredicate>
        Set<TElement>
        filtered(const TBoundsPredicate& boundsPredicate) const;

        template <class TFunction>
        Set<typename std::decay<typename std::result_of<TFunction(TElement)>::type>::type>
        mapped(const TFunction& function) const;

        template <class TVisitor>
        void
        forEach(
            const TVisitor& visitor
        ) const;

        template <class TVisitor>
        void
        forEachOverlapping(
            const typename BoundsType<TElement>::Type& predicateBounds,
            const TVisitor& visitor
        ) const;

        template <class TBoundsPredicate, class TVisitor>
        void
        forEachFiltered(
            const TBoundsPredicate& boundsPredicate,
            const TVisitor& visitor
        ) const;

        template <class TElementPredicate, class TVisitor>
        void
        forEachIf(
            const TElementPredicate& elementPredicate,
            const TVisitor& visitor
        ) const;

        template <class TElementPredicate, class TVisitor>
        void
        forEachOverlappingIf(
            const typename BoundsType<TElement>::Type& predicateBounds,
            const TElementPredicate& elementPredicate,
            const TVisitor& visitor
        ) const;

        template <class TBoundsPredicate, class TElementPredicate, class TVisitor>
        void
        forEachFilteredIf(
            const TBoundsPredicate& boundsPredicate,
            const TElementPredicate& elementPredicate,
            const TVisitor& visitor
        ) const;

        template <class TOutputIterator>
        void
        copy(
            TOutputIterator outputIterator
        ) const;

        template<class TOutputIterator>
        void
        copyOverlapping(
            const typename BoundsType<TElement>::Type& predicateBounds,
            TOutputIterator outputIterator
        ) const;

        template <class TBoundsPredicate, class TOutputIterator>
        void
        copyFiltered(
            const TBoundsPredicate& boundsPredicate,
            TOutputIterator outputIterator
        ) const;

        template <class TElementPredicate, class TOutputIterator>
        void
        copyIf(
            const TElementPredicate& elementPredicate,
            TOutputIterator outputIterator
        ) const;

        template <class TElementPredicate, class TOutputIterator>
        void
        copyOverlappingIf(
            const typename BoundsType<TElement>::Type& predicateBounds,
            const TElementPredicate& elementPredicate,
            TOutputIterator outputIterator
        ) const;

        template <class TBoundsPredicate, class TElementPredicate, class TOutputIterator>
        void
        copyFilteredIf(
            const TBoundsPredicate& boundsPredicate,
            const TElementPredicate& elementPredicate,
            TOutputIterator outputIterator
        ) const;

        template <class TFunction, class TOutputIterator>
        void
        map(
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;

        template <class TFunction, class TOutputIterator>
        void
        mapOverlapping(
            const typename BoundsType<TElement>::Type& predicateBounds,
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;

        template <class TBoundsPredicate, class TFunction, class TOutputIterator>
        void
        mapFiltered(
            const TBoundsPredicate& boundsPredicate,
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;

        template <class TElementPredicate, class TFunction, class TOutputIterator>
        void
        mapIf(
            const TElementPredicate& predicate,
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;

        template <class TElementPredicate, class TFunction, class TOutputIterator>
        void
        mapOverlappingIf(
            const typename BoundsType<TElement>::Type& predicateBounds,
            const TElementPredicate& elementPredicate,
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;

        template <class TBoundsPredicate, class TElementPredicate, class TFunction, class TOutputIterator>
        void
        mapFilteredIf(
            const TBoundsPredicate& boundsPredicate,
            const TElementPredicate& elementPredicate,
            const TFunction& function,
            TOutputIterator outputIterator
        ) const;
    };
    
    template <class TElement>
    std::ostream&
    operator<<(std::ostream& stream, const Set<TElement>& set);
}
    
////////// Specializations //////////

namespace opensolid
{
    template <class TElement>
    struct NumDimensions<Set<TElement>>
    {
        static const int Value = NumDimensions<TElement>::Value;
    };

    template <class TElement, int iNumResultDimensions>
    struct ChangeDimensions<Set<TElement>, iNumResultDimensions>
    {
        typedef Set<typename ChangeDimensions<TElement, iNumResultDimensions>::Type> Type;
    };

    template <class TElement>
    struct ScalingFunction<Set<TElement>>
    {
        Set<TElement>
        operator()(const Set<TElement>& set, double scale) const;
    };

    template <class TElement>
    struct TranslationFunction<Set<TElement>>
    {
        template <class TVector>
        Set<TElement>
        operator()(const Set<TElement>& set, const EigenBase<TVector>& vector) const;
    };

    template <class TElement, int iNumTransformedDimensions>
    struct TransformationFunction<Set<TElement>, iNumTransformedDimensions>
    {
        template <class TMatrix>
        Set<typename ChangeDimensions<TElement, iNumTransformedDimensions>::Type>
        operator()(const Set<TElement>& set, const EigenBase<TMatrix>& matrix) const;
    };

    template <class TElement, int iNumDestinationDimensions>
    struct MorphingFunction<Set<TElement>, iNumDestinationDimensions>
    {
        Set<typename ChangeDimensions<TElement, iNumDestinationDimensions>::Type>
        operator()(
            const Set<TElement>& set,
            const Function<iNumDestinationDimensions, iNumDimensions>& function
        ) const;
    };

    template <class TElement>
    struct BoundsType<Set<TElement>>
    {
        typedef typename BoundsType<TElement>::Type Type;
    };
}
