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

#include <OpenSolid/Core/SpatialCollection/MorphedCollection.declarations.hpp>

#include <OpenSolid/Core/SpatialCollection.definitions.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection>
        class MorphedCollection :
            public SpatialCollection<MorphedCollection<TBaseCollection>>
        {
        private:
            const TBaseCollection& _baseCollection;
            Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value> _function;

            template <class TDerived>
            friend class opensolid::SpatialCollection;

            MorphedCollectionIterator<TBaseCollection>
            beginImpl() const;

            MorphedCollectionIterator<TBaseCollection>
            endImpl() const;

            bool
            isEmptyImpl() const;

            std::int64_t
            sizeImpl() const;

            typename MorphedType<typename BoundsType<TBaseCollection>::Type>::Type Type;
            boundsImpl() const;

            MorphedCollection(const MorphedCollection<TBaseCollection>& other);
        public:
            MorphedCollection(
                const TBaseCollection& baseCollection,
                const Function<
                    iNumResultDimensions,
                    NumDimensions<TBaseCollection>::Value
                >& function
            );

            const TBaseCollection&
            baseCollection() const;

            const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>&
            function() const;
        };

        template <class TBaseCollection>
        class MorphedCollectionIterator :
            public boost::iterator_facade<
                MorphedCollectionIterator<TBaseCollection>,
                const typename ItemType<TBaseCollection>::Type,
                boost::forward_traversal_tag
            >
        {
        private:
            typename IteratorType<TBaseCollection>::Type _baseIterator;
            const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>* _function;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(const MorphedCollectionIterator<TBaseCollection>& other) const;

            const typename ItemType<TBaseCollection>::Type&
            dereference() const;
        public:
            MorphedCollectionIterator();

            MorphedCollectionIterator(
                typename IteratorType<TBaseCollection>::Type baseIterator,
                double scale
            );
        };
    }
}
