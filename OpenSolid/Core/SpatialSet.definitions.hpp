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
    template <class TItem>
    class SpatialSet :
        public Iterable<SpatialSet<TItem>>,
        public Transformable<SpatialSet<TItem>>
    {
    private:
        boost::intrusive_ptr<detail::SpatialSetData<TItem>> _data;

        template <class TDerived>
        friend class Iterable;

        typename std::vector<TItem>::const_iterator
        beginImpl() const;

        typename std::vector<TItem>::const_iterator
        endImpl() const;

        bool
        isEmptyImpl() const;
        
        std::int64_t
        sizeImpl() const;

        struct BoundsData
        {
            typename BoundsType<TItem>::Type bounds;
            const TItem* item;
        };

        void
        init(
            detail::SpatialSetNode<TItem>* node,
            detail::SpatialSetNode<TItem>* next,
            BoundsData** begin,
            BoundsData** end,
            typename BoundsType<TItem>::Type& overallBounds,
            std::int64_t sortIndex
        );

        void
        init(const BoundsFunction<TItem>& boundsFunction);
    public:
        SpatialSet();

        SpatialSet(const SpatialSet<TItem>& other);

        SpatialSet(SpatialSet<TItem>&& other);

        SpatialSet(
            const std::vector<TItem>& items,
            BoundsFunction<TItem> boundsFunction = BoundsFunction<TItem>()
        );

        SpatialSet(
            std::vector<TItem>&& items,
            BoundsFunction<TItem> boundsFunction = BoundsFunction<TItem>()
        );
        
        template <class TIterator>
        SpatialSet(
            TIterator begin,
            TIterator end,
            BoundsFunction<TItem> boundsFunction = BoundsFunction<TItem>()
        );

        const detail::SpatialSetNode<TItem>*
        rootNode() const;

        typename std::vector<TItem>::const_iterator
        begin() const;

        typename std::vector<TItem>::const_iterator
        end() const;

        const TItem&
        first() const;

        const TItem&
        last() const;

        const TItem&
        operator[](std::int64_t index) const;

        void
        swap(SpatialSet<TItem>& other);
        
        void
        operator=(const SpatialSet<TItem>& other);
        
        void
        operator=(SpatialSet<TItem>&& other);

        typename BoundsType<TItem>::Type
        bounds() const;

        void
        clear();

        detail::FilteredSpatialSet<TItem, detail::OverlapPredicate<TItem>>
        overlapping(const typename BoundsType<TItem>::Type& predicateBounds) const;

        detail::FilteredSpatialSet<TItem, detail::ContainPredicate<TItem>>
        containing(const typename BoundsType<TItem>::Type& predicateBounds) const;

        template <class TBoundsPredicate>
        detail::FilteredSpatialSet<TItem, TBoundsPredicate>
        filtered(TBoundsPredicate boundsPredicate) const;

        template <class TItemComparator>
        detail::SpatialSubset<TItem>
        uniqueItems(TItemComparator itemComparator) const;

        template <class TItemComparator>
        std::vector<std::int64_t>
        uniqueMapping(TItemComparator itemComparator) const;
    };
    
    template <class TItem>
    std::ostream&
    operator<<(std::ostream& stream, const SpatialSet<TItem>& set);
}
    
////////// Specializations //////////

namespace opensolid
{
    template <class TItem>
    struct ItemType<SpatialSet<TItem>>
    {
        typedef TItem Type;
    };

    template <class TItem>
    struct IteratorType<SpatialSet<TItem>>
    {
        typedef typename std::vector<TItem>::const_iterator Type;
    };

    template <class TItem>
    struct NumDimensions<SpatialSet<TItem>>
    {
        static const int Value = NumDimensions<TItem>::Value;
    };

    template <class TItem, int iNumResultDimensions>
    struct ChangeDimensions<SpatialSet<TItem>, iNumResultDimensions>
    {
        typedef SpatialSet<typename ChangeDimensions<TItem, iNumResultDimensions>::Type> Type;
    };

    template <class TItem>
    struct ScalingFunction<SpatialSet<TItem>>
    {
        SpatialSet<TItem>
        operator()(const SpatialSet<TItem>& set, double scale) const;
    };

    template <class TItem>
    struct TranslationFunction<SpatialSet<TItem>>
    {
        template <class TVector>
        SpatialSet<TItem>
        operator()(const SpatialSet<TItem>& set, const EigenBase<TVector>& vector) const;
    };

    template <class TItem, int iNumResultDimensions>
    struct TransformationFunction<SpatialSet<TItem>, iNumResultDimensions>
    {
        template <class TMatrix>
        SpatialSet<typename ChangeDimensions<TItem, iNumResultDimensions>::Type>
        operator()(const SpatialSet<TItem>& set, const EigenBase<TMatrix>& matrix) const;
    };

    template <class TItem, int iNumResultDimensions>
    struct MorphingFunction<SpatialSet<TItem>, iNumResultDimensions>
    {
        SpatialSet<typename ChangeDimensions<TItem, iNumResultDimensions>::Type>
        operator()(
            const SpatialSet<TItem>& set,
            const Function<iNumResultDimensions, NumDimensions<TItem>::Value>& function
        ) const;
    };

    template <class TItem>
    struct BoundsType<SpatialSet<TItem>>
    {
        typedef typename BoundsType<TItem>::Type Type;
    };
}
