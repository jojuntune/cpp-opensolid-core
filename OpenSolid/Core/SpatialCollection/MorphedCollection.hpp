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

#include <OpenSolid/Core/SpatialCollection/MorphedCollection.definitions.hpp>

#include <OpenSolid/Core/SpatialCollection.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection>
        inline
        MorphedCollectionIterator<TBaseCollection>
        MorphedCollection<TBaseCollection>::beginImpl() const {
            return MorphedCollectionIterator<TBaseCollection>(
                baseCollection().begin(),
                &function()
            );
        }

        template <class TBaseCollection>
        inline
        MorphedCollectionIterator<TBaseCollection>
        MorphedCollection<TBaseCollection>::endImpl() const {
            return MorphedCollectionIterator<TBaseCollection>(
                baseCollection().end(),
                &function()
            );
        }

        template <class TBaseCollection>
        inline
        bool
        MorphedCollection<TBaseCollection>::isEmptyImpl() const {
            return baseCollection().isEmpty();
        }

        template <class TBaseCollection>
        inline
        std::int64_t
        MorphedCollection<TBaseCollection>::sizeImpl() const {
            return baseCollection().size();
        }

        template <class TBaseCollection>
        inline
        typename BoundsType<typename ItemType<TBaseCollection>::Type>::Type
        MorphedCollection<TBaseCollection>::boundsImpl() const {
            return detail::morphed(baseCollection().bounds(), function());
        }

        template <class TBaseCollection>
        inline
        MorphedCollection<TBaseCollection>::MorphedCollection(
            const TBaseCollection& baseCollection,
            const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>& function
        ) : _baseCollection(baseCollection), 
            _function(function) {
        }

        template <class TBaseCollection>
        const TBaseCollection&
        MorphedCollection<TBaseCollection>::baseCollection() const {
            return _baseCollection;
        }

        template <class TBaseCollection>
        const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>&
        MorphedCollection<TBaseCollection>::function() const {
            return _function;
        }

        template <class TBaseCollection>
        inline
        void
        MorphedCollectionIterator<TBaseCollection>::increment() {
            ++_baseIterator;
        }

        template <class TBaseCollection>
        inline
        bool
        MorphedCollectionIterator<TBaseCollection>::equal(
            const MorphedCollectionIterator<TBaseCollection>& other
        ) const {
            return _baseIterator == other._baseIterator;
        }

        template <class TBaseCollection>
        inline
        const typename MorphedType<typename ItemType<TBaseCollection>::Type>::Type&
        MorphedCollectionIterator<TBaseCollection>::dereference() const {
            return detail::morphed(*_baseIterator, *_function);
        }

        template <class TBaseCollection>
        inline
        MorphedCollectionIterator<TBaseCollection>::MorphedCollectionIterator() :
            _function(nullptr) {
        }

        template <class TBaseCollection>
        inline
        MorphedCollectionIterator<TBaseCollection>::MorphedCollectionIterator(
            typename IteratorType<TBaseCollection>::Type baseIterator,
            const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>* function
        ) : _baseIterator(baseIterator),
            _function(function) {
        }
    }
}
