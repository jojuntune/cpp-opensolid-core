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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/SpatialList.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialList/SpatialListData.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <boost/intrusive_ptr.hpp>

namespace opensolid
{
    template <class TItem>
    class SpatialList :
        public SpatialCollection<SpatialList<TItem>>
    {
    private:
        boost::intrusive_ptr<detail::SpatialListData<TItem>> _dataPtr;
        std::vector<TItem> _emptyVector;
    public:
        SpatialList();

        SpatialList(const SpatialList<TItem>& other);

        SpatialList(SpatialList<TItem>&& other);

        SpatialList(const std::vector<TItem>& items);

        SpatialList(std::vector<TItem>&& items);

        template <class TDerived>
        SpatialList(const SpatialCollection<TDerived>& collection);

        template <class TIterator>
        SpatialList(TIterator begin, TIterator end);
        
        void
        operator=(const SpatialList<TItem>& other);
        
        void
        operator=(SpatialList<TItem>&& other);

        typename std::vector<TItem>::const_iterator
        begin() const;

        typename std::vector<TItem>::const_iterator
        end() const;

        bool
        isEmpty() const;
        
        std::int64_t
        size() const;

        typename BoundsType<TItem>::Type
        bounds() const;

        const TItem&
        operator[](std::int64_t index) const;

        void
        swap(SpatialList<TItem>& other);

        void
        clear();
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <class TItem>
    struct ItemType<SpatialList<TItem>>
    {
        typedef TItem Type;
    };

    template <class TItem>
    struct IteratorType<SpatialList<TItem>>
    {
        typedef typename std::vector<TItem>::const_iterator Type;
    };

    template <class TItem>
    struct NumDimensions<SpatialList<TItem>>
    {
        static const int Value = NumDimensions<TItem>::Value;
    };

    template <class TItem>
    struct ScaledType<SpatialList<TItem>> :
        public ScaledType<SpatialCollection<SpatialList<TItem>>>
    {
    };

    template <class TItem>
    struct TranslatedType<SpatialList<TItem>> :
        public TranslatedType<SpatialCollection<SpatialList<TItem>>>
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct TransformedType<SpatialList<TItem>, iNumResultDimensions> :
        public TransformedType<SpatialCollection<SpatialList<TItem>>, iNumResultDimensions>
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct MorphedType<SpatialList<TItem>, iNumResultDimensions> :
        public MorphedType<SpatialCollection<SpatialList<TItem>>, iNumResultDimensions>
    {
    };

    template <class TItem>
    struct ScalingFunction<SpatialList<TItem>> :
        public ScalingFunction<SpatialCollection<SpatialList<TItem>>>
    {
    };

    template <class TItem>
    struct TranslationFunction<SpatialList<TItem>> :
        public TranslationFunction<SpatialCollection<SpatialList<TItem>>>
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct TransformationFunction<SpatialList<TItem>, iNumResultDimensions> :
        public TransformationFunction<SpatialCollection<SpatialList<TItem>>, iNumResultDimensions>
    {
    };

    template <class TItem>
    struct BoundsType<SpatialList<TItem>>
    {
        typedef typename BoundsType<TItem>::Type Type;
    };
}
