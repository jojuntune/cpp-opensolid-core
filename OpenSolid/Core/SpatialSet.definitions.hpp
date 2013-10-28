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

#include <OpenSolid/Core/SpatialSet.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/Iterable.definitions.hpp>
#include <OpenSolid/Core/SpatialSet/ContainPredicate.declarations.hpp>
#include <OpenSolid/Core/SpatialSet/FilteredSpatialSet.declarations.hpp>
#include <OpenSolid/Core/SpatialSet/OverlapPredicate.declarations.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSetData.declarations.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSetNode.declarations.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSubset.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <boost/intrusive_ptr.hpp>

#include <vector>

namespace opensolid
{
    template <class TElement>
    class SpatialSet :
        public Iterable<SpatialSet<TElement>>,
        public Transformable<SpatialSet<TElement>>
    {
    private:
        boost::intrusive_ptr<detail::SpatialSetData<TElement>> _data;

        template <class TDerived>
        friend class Iterable;

        typename std::vector<TElement>::const_iterator
        beginImpl() const;

        typename std::vector<TElement>::const_iterator
        endImpl() const;

        bool
        isEmptyImpl() const;
        
        std::int64_t
        sizeImpl() const;

        struct BoundsData
        {
            typename BoundsType<TElement>::Type bounds;
            const TElement* element;
        };

        void
        init(
            detail::SpatialSetNode<TElement>* node,
            detail::SpatialSetNode<TElement>* next,
            BoundsData** begin,
            BoundsData** end,
            typename BoundsType<TElement>::Type& overallBounds,
            std::int64_t sortIndex
        );

        void
        init(const BoundsFunction<TElement>& boundsFunction);
    public:
        SpatialSet();

        SpatialSet(const SpatialSet<TElement>& other);

        SpatialSet(SpatialSet<TElement>&& other);

        SpatialSet(
            const std::vector<TElement>& elements,
            BoundsFunction<TElement> boundsFunction = BoundsFunction<TElement>()
        );

        SpatialSet(
            std::vector<TElement>&& elements,
            BoundsFunction<TElement> boundsFunction = BoundsFunction<TElement>()
        );
        
        template <class TIterator>
        SpatialSet(
            TIterator begin,
            TIterator end,
            BoundsFunction<TElement> boundsFunction = BoundsFunction<TElement>()
        );

        const detail::SpatialSetNode<TElement>*
        rootNode() const;

        typename std::vector<TElement>::const_iterator
        begin() const;

        typename std::vector<TElement>::const_iterator
        end() const;

        const TElement&
        first() const;

        const TElement&
        last() const;

        const TElement&
        operator[](std::int64_t index) const;

        void
        swap(SpatialSet<TElement>& other);
        
        void
        operator=(const SpatialSet<TElement>& other);
        
        void
        operator=(SpatialSet<TElement>&& other);

        typename BoundsType<TElement>::Type
        bounds() const;

        void
        clear();

        detail::FilteredSpatialSet<TElement, detail::OverlapPredicate<TElement>>
        overlapping(const typename BoundsType<TElement>::Type& predicateBounds) const;

        detail::FilteredSpatialSet<TElement, detail::ContainPredicate<TElement>>
        containing(const typename BoundsType<TElement>::Type& predicateBounds) const;

        template <class TBoundsPredicate>
        detail::FilteredSpatialSet<TElement, TBoundsPredicate>
        filtered(TBoundsPredicate boundsPredicate) const;

        template <class TElementComparator>
        detail::SpatialSubset<TElement>
        uniqueElements(TElementComparator elementComparator) const;

        template <class TElementComparator>
        std::vector<std::int64_t>
        uniqueMapping(TElementComparator elementComparator) const;
    };
    
    template <class TElement>
    std::ostream&
    operator<<(std::ostream& stream, const SpatialSet<TElement>& set);
}
    
////////// Specializations //////////

namespace opensolid
{
    template <class TElement>
    struct ElementType<SpatialSet<TElement>>
    {
        typedef TElement Type;
    };

    template <class TElement>
    struct IteratorType<SpatialSet<TElement>>
    {
        typedef typename std::vector<TElement>::const_iterator Type;
    };

    template <class TElement>
    struct NumDimensions<SpatialSet<TElement>>
    {
        static const int Value = NumDimensions<TElement>::Value;
    };

    template <class TElement, int iNumResultDimensions>
    struct ChangeDimensions<SpatialSet<TElement>, iNumResultDimensions>
    {
        typedef SpatialSet<typename ChangeDimensions<TElement, iNumResultDimensions>::Type> Type;
    };

    template <class TElement>
    struct ScalingFunction<SpatialSet<TElement>>
    {
        SpatialSet<TElement>
        operator()(const SpatialSet<TElement>& set, double scale) const;
    };

    template <class TElement>
    struct TranslationFunction<SpatialSet<TElement>>
    {
        template <class TVector>
        SpatialSet<TElement>
        operator()(const SpatialSet<TElement>& set, const EigenBase<TVector>& vector) const;
    };

    template <class TElement, int iNumResultDimensions>
    struct TransformationFunction<SpatialSet<TElement>, iNumResultDimensions>
    {
        template <class TMatrix>
        SpatialSet<typename ChangeDimensions<TElement, iNumResultDimensions>::Type>
        operator()(const SpatialSet<TElement>& set, const EigenBase<TMatrix>& matrix) const;
    };

    template <class TElement, int iNumResultDimensions>
    struct MorphingFunction<SpatialSet<TElement>, iNumResultDimensions>
    {
        SpatialSet<typename ChangeDimensions<TElement, iNumResultDimensions>::Type>
        operator()(
            const SpatialSet<TElement>& set,
            const Function<iNumResultDimensions, NumDimensions<TElement>::Value>& function
        ) const;
    };

    template <class TElement>
    struct BoundsType<SpatialSet<TElement>>
    {
        typedef typename BoundsType<TElement>::Type Type;
    };
}
