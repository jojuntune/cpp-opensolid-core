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

#include <OpenSolid/Core/SpatialSet/SpatialSubset.declarations.hpp>

#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialSet.definitions.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <vector>

namespace opensolid
{
    namespace detail
    {
        template <class TItem>
        class SpatialSubset :
            public SpatialCollection<SpatialSubset<TItem>>
        {
        private:
            SpatialSet<TItem> _set;
            std::vector<const TItem*> _items;
        public:
            SpatialSubset();

            SpatialSubset(const SpatialSubset<TItem>& other);

            SpatialSubset(SpatialSubset<TItem>&& other);

            SpatialSubset(const SpatialSet<TItem>& set, std::vector<const TItem*>&& items);

            SpatialSubset(SpatialSet<TItem>&& set, std::vector<const TItem*>&& items);

            SpatialSubsetIterator<TItem>
            begin() const;

            SpatialSubsetIterator<TItem>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            typename BoundsType<TItem>::Type
            bounds() const;
        };

        template <class TItem>
        class SpatialSubsetIterator :
            public boost::iterator_facade<
                SpatialSubsetIterator<TItem>,
                TItem,
                boost::forward_traversal_tag,
                const TItem&
            >
        {
        private:
            typename std::vector<const TItem*>::const_iterator _iterator;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(const SpatialSubsetIterator<TItem>& other) const;

            const TItem&
            dereference() const;
        public:
            SpatialSubsetIterator();

            SpatialSubsetIterator(typename std::vector<const TItem*>::const_iterator iterator);
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
    template <class TItem>
    struct ItemType<detail::SpatialSubset<TItem>>
    {
        typedef TItem Type;
    };

    template <class TItem>
    struct IteratorType<detail::SpatialSubset<TItem>>
    {
        typedef detail::SpatialSubsetIterator<TItem> Type;
    };

    template <class TItem>
    struct NumDimensions<detail::SpatialSubset<TItem>>
    {
        static const int Value = NumDimensions<TItem>::Value;
    };

    template <class TItem>
    struct BoundsType<detail::SpatialSubset<TItem>>
    {
        typedef typename BoundsType<TItem>::Type Type;
    };

    template <class TItem>
    struct ScaledType<detail::SpatialSubset<TItem>> :
        public ScaledType<SpatialCollection<detail::SpatialSubset<TItem>>>
    {
    };

    template <class TItem>
    struct TranslatedType<detail::SpatialSubset<TItem>> :
        public TranslatedType<SpatialCollection<detail::SpatialSubset<TItem>>>
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct TransformedType<detail::SpatialSubset<TItem>, iNumResultDimensions> :
        public TransformedType<
            SpatialCollection<detail::SpatialSubset<TItem>>,
            iNumResultDimensions
        >
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct MorphedType<detail::SpatialSubset<TItem>, iNumResultDimensions> :
        public MorphedType<
            SpatialCollection<detail::SpatialSubset<TItem>>,
            iNumResultDimensions
        >
    {
    };

    template <class TItem>
    struct ScalingFunction<detail::SpatialSubset<TItem>> :
        public ScalingFunction<SpatialCollection<detail::SpatialSubset<TItem>>>
    {
    };

    template <class TItem>
    struct TranslationFunction<detail::SpatialSubset<TItem>> :
        public TranslationFunction<SpatialCollection<detail::SpatialSubset<TItem>>>
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct TransformationFunction<detail::SpatialSubset<TItem>, iNumResultDimensions> :
        public TransformationFunction<
            SpatialCollection<detail::SpatialSubset<TItem>>,
            iNumResultDimensions
        >
    {
    };

    template <class TItem, int iNumResultDimensions>
    struct MorphingFunction<detail::SpatialSubset<TItem>, iNumResultDimensions> :
        public MorphingFunction<
            SpatialCollection<detail::SpatialSubset<TItem>>,
            iNumResultDimensions
        >
    {
    };
}
