/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/SpatialSet.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.definitions.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/LazyCollection.definitions.hpp>
#include <OpenSolid/Core/LazyCollection/ContainPredicate.declarations.hpp>
#include <OpenSolid/Core/LazyCollection/FilteredSpatialSet.declarations.hpp>
#include <OpenSolid/Core/LazyCollection/OverlapPredicate.declarations.hpp>
#include <OpenSolid/Core/LazyCollection/SpatialSetData.declarations.hpp>
#include <OpenSolid/Core/LazyCollection/SpatialSetNode.declarations.hpp>

#include <boost/intrusive_ptr.hpp>

#include <vector>

namespace opensolid
{
    template <class TItem>
    struct IteratorType<SpatialSet<TItem>>
    {
        typedef typename std::vector<TItem>::const_iterator Type;
    };

    template <class TItem>
    class SpatialSet :
        public LazyCollection<SpatialSet<TItem>>
    {
    private:
        boost::intrusive_ptr<detail::SpatialSetData<TItem>> _dataPtr;
        std::vector<TItem> _emptyVector;

        struct BoundsData
        {
            typename BoundsType<TItem>::Type bounds;
            const TItem* itemPtr;
        };

        void
        init(
            detail::SpatialSetNode<TItem>* nodePtr,
            detail::SpatialSetNode<TItem>* nextPtr,
            BoundsData** begin,
            BoundsData** end,
            int sortIndex
        );

        void
        init();
    public:
        SpatialSet();

        SpatialSet(const SpatialSet<TItem>& other);

        SpatialSet(SpatialSet<TItem>&& other);

        explicit
        SpatialSet(const std::vector<TItem>& items);

        explicit
        SpatialSet(std::vector<TItem>&& items);

        template <class TDerived>
        explicit
        SpatialSet(const LazyCollection<TDerived>& collection);
        
        template <class TIterator>
        SpatialSet(TIterator begin, TIterator end);
        
        void
        operator=(const SpatialSet<TItem>& other);
        
        void
        operator=(SpatialSet<TItem>&& other);

        void
        swap(SpatialSet<TItem>& other);

        const detail::SpatialSetNode<TItem>*
        rootNode() const;

        typename std::vector<TItem>::const_iterator
        begin() const;

        typename std::vector<TItem>::const_iterator
        end() const;

        bool
        isEmpty() const;
        
        std::size_t
        size() const;

        typename BoundsType<TItem>::Type
        bounds() const;

        const TItem&
        operator[](std::size_t index) const;

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
        
        bool
        contains(const TItem& item, double precision = 1e-12) const;

        std::vector<TItem>
        uniqueItems(double precision = 1e-12) const;

        std::vector<TItem>
        uniqueItems(std::vector<std::size_t>& mapping, double precision = 1e-12) const;
    };
    
    template <class TItem>
    std::ostream&
    operator<<(std::ostream& stream, const SpatialSet<TItem>& set);
}
