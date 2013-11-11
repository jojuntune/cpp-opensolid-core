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

#include <OpenSolid/Core/BoundsFunction.definitions.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialList.declarations.hpp>
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
        public SpatialCollection<SpatialSet<TItem>>
    {
    private:
        BoundsFunction<TItem> _boundsFunction;
        boost::intrusive_ptr<detail::SpatialSetData<TItem>> _data;

        template <class TDerived>
        friend class SpatialCollection;

        typename std::vector<TItem>::const_iterator
        beginImpl() const;

        typename std::vector<TItem>::const_iterator
        endImpl() const;

        bool
        isEmptyImpl() const;
        
        std::int64_t
        sizeImpl() const;

        typename BoundsType<TItem>::Type
        boundsImpl() const;

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
        init();
    public:
        SpatialSet();

        SpatialSet(const SpatialSet<TItem>& other);

        SpatialSet(SpatialSet<TItem>&& other);

        explicit
        SpatialSet(
            const std::vector<TItem>& items,
            BoundsFunction<TItem> boundsFunction = BoundsFunction<TItem>()
        );

        explicit
        SpatialSet(
            std::vector<TItem>&& items,
            BoundsFunction<TItem> boundsFunction = BoundsFunction<TItem>()
        );

        template <class TDerived>
        explicit
        SpatialSet(
            const SpatialCollection<TDerived>& collection,
            BoundsFunction<TItem> boundsFunction = BoundsFunction<TItem>()
        );
        
        template <class TIterator>
        SpatialSet(
            TIterator begin,
            TIterator end,
            BoundsFunction<TItem> boundsFunction = BoundsFunction<TItem>()
        );

        BoundsFunction<TItem>
        boundsFunction() const;

        const detail::SpatialSetNode<TItem>*
        rootNode() const;

        typename std::vector<TItem>::const_iterator
        begin() const;

        typename std::vector<TItem>::const_iterator
        end() const;

        const TItem&
        operator[](std::int64_t index) const;

        void
        swap(SpatialSet<TItem>& other);
        
        void
        operator=(const SpatialSet<TItem>& other);
        
        void
        operator=(SpatialSet<TItem>&& other);

        void
        clear();

        detail::FilteredSpatialSet<TItem, detail::OverlapPredicate<TItem>>
        overlapping(
            const typename BoundsType<TItem>::Type& predicateBounds,
            double precision = 1e-12
        ) const;

        detail::FilteredSpatialSet<TItem, detail::ContainPredicate<TItem>>
        containing(
            const typename BoundsType<TItem>::Type& predicateBounds,
            double precision = 1e-12
        ) const;

        template <class TBoundsPredicate>
        detail::FilteredSpatialSet<TItem, TBoundsPredicate>
        filtered(TBoundsPredicate boundsPredicate) const;

        typename std::vector<TItem>::const_iterator
        find(const TItem& item, double precision = 1e-12) const;

        detail::SpatialSubset<TItem>
        uniqueItems(double precision = 1e-12) const;

        std::vector<std::int64_t>
        uniqueMapping(double precision = 1e-12) const;
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
    struct NestedType<SpatialSet<TItem>>
    {
        typedef const SpatialSet<TItem>& Type;
    };

    template <class TItem>
    struct NumDimensions<SpatialSet<TItem>>
    {
        static const int Value = NumDimensions<TItem>::Value;
    };

    template <class TItem>
    struct ScaledType<SpatialSet<TItem>> :
        public ScaledType<SpatialCollection<SpatialSet<TItem>>>
    {
    };

    template <class TItem>
    struct TranslatedType<SpatialSet<TItem>> :
        public TranslatedType<SpatialCollection<SpatialSet<TItem>>>
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct TransformedType<SpatialSet<TItem>, iNumResultDimensions> :
        public TransformedType<SpatialCollection<SpatialSet<TItem>>, iNumResultDimensions>
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct MorphedType<SpatialSet<TItem>, iNumResultDimensions> :
        public MorphedType<SpatialCollection<SpatialSet<TItem>>, iNumResultDimensions>
    {
    };

    template <class TItem>
    struct ScalingFunction<SpatialSet<TItem>> :
        public ScalingFunction<SpatialCollection<SpatialSet<TItem>>>
    {
    };

    template <class TItem>
    struct TranslationFunction<SpatialSet<TItem>> :
        public TranslationFunction<SpatialCollection<SpatialSet<TItem>>>
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct TransformationFunction<SpatialSet<TItem>, iNumResultDimensions> :
        public TransformationFunction<SpatialCollection<SpatialSet<TItem>>, iNumResultDimensions>
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct MorphingFunction<SpatialSet<TItem>, iNumResultDimensions> :
        public MorphingFunction<SpatialCollection<SpatialSet<TItem>>, iNumResultDimensions>
    {
    };

    template <class TItem>
    struct BoundsType<SpatialSet<TItem>>
    {
        typedef typename BoundsType<TItem>::Type Type;
    };
}
