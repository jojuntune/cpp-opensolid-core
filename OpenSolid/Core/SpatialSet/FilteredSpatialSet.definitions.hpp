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

#include <OpenSolid/Core/SpatialSet/FilteredSpatialSet.declarations.hpp>

#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialSet.declarations.hpp>
#include <OpenSolid/Core/SpatialSet/SpatialSetNode.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TItem, class TBoundsPredicate>
        class FilteredSpatialSet :
            public SpatialCollection<FilteredSpatialSet<TItem, TBoundsPredicate>>
        {
        private:
            const SpatialSet<TItem>& _set;
            TBoundsPredicate _boundsPredicate;

            template <class TDerived>
            friend class opensolid::SpatialCollection;

            friend class SpatialSet<TItem>;

            FilteredSpatialSetIterator<TItem, TBoundsPredicate>
            beginImpl() const;

            FilteredSpatialSetIterator<TItem, TBoundsPredicate>
            endImpl() const;

            bool
            isEmptyImpl() const;

            std::int64_t
            sizeImpl() const;
        public:
            FilteredSpatialSet(
                const SpatialSet<TItem>& set,
                TBoundsPredicate boundsPredicate
            );
        };

        template <class TItem, class TBoundsPredicate>
        class FilteredSpatialSetIterator :
            public boost::iterator_facade<
                FilteredSpatialSetIterator<TItem, TBoundsPredicate>,
                const TItem,
                boost::forward_traversal_tag
            >
        {
        private:
            const SpatialSetNode<TItem>* _currentNode;
            const TBoundsPredicate* _boundsPredicate;

            friend class boost::iterator_core_access;

            void
            descendFrom(const SpatialSetNode<TItem>* candidateNode);

            void
            increment();

            bool
            equal(const FilteredSpatialSetIterator<TItem, TBoundsPredicate>& other) const;

            const TItem&
            dereference() const;
        public:
            FilteredSpatialSetIterator();

            FilteredSpatialSetIterator(
                const SpatialSetNode<TItem>* rootNode,
                const TBoundsPredicate* boundsPredicate
            );
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
    template <class TItem, class TBoundsPredicate>
    struct ItemType<detail::FilteredSpatialSet<TItem, TBoundsPredicate>>
    {
        typedef TItem Type;
    };

    template <class TItem, class TBoundsPredicate>
    struct IteratorType<detail::FilteredSpatialSet<TItem, TBoundsPredicate>>
    {
        typedef detail::FilteredSpatialSetIterator<TItem, TBoundsPredicate> Type;
    };

    template <class TItem, class TPredicate>
    struct NumDimensions<detail::FilteredSpatialSet<TItem, TPredicate>>
    {
        static const int Value = NumDimensions<TItem>::Value;
    };

    template <class TItem, class TPredicate>
    struct ScaledType<detail::FilteredSpatialSet<TItem, TPredicate>> :
        public ScaledType<SpatialCollection<detail::FilteredSpatialSet<TItem, TPredicate>>>
    {
    };

    template <class TItem, class TPredicate>
    struct TranslatedType<detail::FilteredSpatialSet<TItem, TPredicate>> :
        public TranslatedType<SpatialCollection<detail::FilteredSpatialSet<TItem, TPredicate>>>
    {
    };

    template <class TItem, class TPredicate, int iNumResultDimensions>
    struct TransformedType<
        detail::FilteredSpatialSet<TItem, TPredicate>,
        iNumResultDimensions
    > : public TransformedType<
            SpatialCollection<detail::FilteredSpatialSet<TItem, TPredicate>>,
            iNumResultDimensions
        >
    {
    };

    template <class TItem, class TPredicate, int iNumResultDimensions>
    struct MorphedType<
        detail::FilteredSpatialSet<TItem, TPredicate>,
        iNumResultDimensions
    > : public MorphedType<
            SpatialCollection<detail::FilteredSpatialSet<TItem, TPredicate>>,
            iNumResultDimensions
        >
    {
    };

    template <class TItem, class TPredicate>
    struct ScalingFunction<detail::FilteredSpatialSet<TItem, TPredicate>> :
        public ScalingFunction<SpatialCollection<detail::FilteredSpatialSet<TItem, TPredicate>>>
    {
    };

    template <class TItem, class TPredicate>
    struct TranslationFunction<detail::FilteredSpatialSet<TItem, TPredicate>> :
        public TranslationFunction<SpatialCollection<detail::FilteredSpatialSet<TItem, TPredicate>>>
    {
    };

    template <class TItem, class TPredicate, int iNumResultDimensions>
    struct TransformationFunction<
        detail::FilteredSpatialSet<TItem, TPredicate>,
        iNumResultDimensions
    > : public TransformationFunction<
            SpatialCollection<detail::FilteredSpatialSet<TItem, TPredicate>>,
            iNumResultDimensions
        >
    {
    };

    template <class TItem, class TPredicate, int iNumResultDimensions>
    struct MorphingFunction<
        detail::FilteredSpatialSet<TItem, TPredicate>,
        iNumResultDimensions
    > : public MorphingFunction<
            SpatialCollection<detail::FilteredSpatialSet<TItem, TPredicate>>,
            iNumResultDimensions
        >
    {
    };
}
