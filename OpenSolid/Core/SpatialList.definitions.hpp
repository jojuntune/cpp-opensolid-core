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

#include <OpenSolid/Core/SpatialList.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    template <class TItem>
    class SpatialList :
        public SpatialCollection<SpatialList<TItem>>
    {
    private:
        std::vector<TItem> _items;

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

        void
        clear();
    };
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

    template <class TItem>
    struct ScaledType<SpatialSet<TItem>>
    {
        typedef SpatialSet<typename ScaledType<TItem>::Type> Type;
    };

    template <class TItem>
    struct TranslatedType<SpatialSet<TItem>>
    {
        typedef SpatialSet<typename TranslatedType<TItem>::Type> Type;
    };

    template <class TItem, int iNumResultDimensions>
    struct TransformedType<SpatialSet<TItem>, iNumResultDimensions>
    {
        typedef SpatialSet<typename TransformedType<TItem, iNumResultDimensions>::Type> Type;
    };

    template <class TItem, int iNumResultDimensions>
    struct MorphedType<SpatialSet<TItem>, iNumResultDimensions>
    {
        typedef SpatialSet<typename MorphedType<TItem, iNumResultDimensions>::Type> Type;
    };

    template <class TItem>
    struct ScalingFunction<SpatialSet<TItem>>
    {
        SpatialSet<typename ScaledType<TItem>::Type>
        operator()(const SpatialSet<TItem>& set, double scale) const;
    };

    template <class TItem>
    struct TranslationFunction<SpatialSet<TItem>>
    {
        template <class TVector>
        SpatialSet<typename TranslatedType<TItem>::Type>
        operator()(const SpatialSet<TItem>& set, const EigenBase<TVector>& vector) const;
    };

    template <class TItem, int iNumResultDimensions>
    struct TransformationFunction<SpatialSet<TItem>, iNumResultDimensions>
    {
        template <class TMatrix>
        SpatialSet<typename TransformedType<TItem, iNumResultDimensions>::Type>
        operator()(const SpatialSet<TItem>& set, const EigenBase<TMatrix>& matrix) const;
    };

    template <class TItem, int iNumResultDimensions>
    struct MorphingFunction<SpatialSet<TItem>, iNumResultDimensions>
    {
        SpatialSet<typename MorphedType<TItem, iNumResultDimensions>::Type>
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
