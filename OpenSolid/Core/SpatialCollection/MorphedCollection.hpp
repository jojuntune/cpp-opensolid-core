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
        template <class TBaseCollection, int iNumResultDimensions>
        inline
        MorphedCollection<TBaseCollection, iNumResultDimensions>::MorphedCollection(
            const MorphedCollection<TBaseCollection, iNumResultDimensions>& other
        ) : _baseCollection(other._baseCollection),
            _function(std::move(other._function)) {
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        MorphedCollection<TBaseCollection, iNumResultDimensions>::MorphedCollection(
            MorphedCollection<TBaseCollection, iNumResultDimensions>&& other
        ) : _baseCollection(std::move(other._baseCollection)),
            _function(std::move(other._function)) {
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        MorphedCollection<TBaseCollection, iNumResultDimensions>::MorphedCollection(
            const TBaseCollection& baseCollection,
            const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>& function
        ) : _baseCollection(baseCollection), 
            _function(function) {
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        MorphedCollection<TBaseCollection, iNumResultDimensions>::MorphedCollection(
            TBaseCollection&& baseCollection,
            const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>& function
        ) : _baseCollection(std::move(baseCollection)), 
            _function(function) {
        }

        template <class TBaseCollection, int iNumResultDimensions>
        const TBaseCollection&
        MorphedCollection<TBaseCollection, iNumResultDimensions>::baseCollection() const {
            return _baseCollection;
        }

        template <class TBaseCollection, int iNumResultDimensions>
        const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>&
        MorphedCollection<TBaseCollection, iNumResultDimensions>::function() const {
            return _function;
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>
        MorphedCollection<TBaseCollection, iNumResultDimensions>::begin() const {
            return MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>(
                baseCollection().begin(),
                &function()
            );
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>
        MorphedCollection<TBaseCollection, iNumResultDimensions>::end() const {
            return MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>(
                baseCollection().end(),
                &function()
            );
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        bool
        MorphedCollection<TBaseCollection, iNumResultDimensions>::isEmpty() const {
            return baseCollection().isEmpty();
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        std::int64_t
        MorphedCollection<TBaseCollection, iNumResultDimensions>::size() const {
            return baseCollection().size();
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        typename MorphedType<typename BoundsType<TBaseCollection>::Type, iNumResultDimensions>::Type
        MorphedCollection<TBaseCollection, iNumResultDimensions>::bounds() const {
            return detail::morphed(baseCollection().bounds(), function());
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        void
        MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>::increment() {
            ++_baseIterator;
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        bool
        MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>::equal(
            const MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>& other
        ) const {
            return _baseIterator == other._baseIterator;
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        typename MorphedType<typename ItemType<TBaseCollection>::Type, iNumResultDimensions>::Type
        MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>::dereference() const {
            return detail::morphed(*_baseIterator, *_function);
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>::MorphedCollectionIterator() :
            _function(nullptr) {
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        MorphedCollectionIterator<TBaseCollection, iNumResultDimensions>::MorphedCollectionIterator(
            typename IteratorType<TBaseCollection>::Type baseIterator,
            const Function<iNumResultDimensions, NumDimensions<TBaseCollection>::Value>* function
        ) : _baseIterator(baseIterator),
            _function(function) {
        }
    }

    template <class TBaseCollection, int iNumInnerResultDimensions, int iNumOuterResultDimensions>
    inline
    detail::MorphedCollection<TBaseCollection, iNumOuterResultDimensions>
    MorphingFunction<
        detail::MorphedCollection<TBaseCollection, iNumInnerResultDimensions>,
        iNumOuterResultDimensions
    >::operator()(
        const detail::MorphedCollection<
            TBaseCollection,
            iNumInnerResultDimensions
        >& morphedCollection,
        const Function<iNumOuterResultDimensions, iNumInnerResultDimensions>& function
    ) const {
        return detail::MorphedCollection<TBaseCollection, iNumOuterResultDimensions>(
            morphedCollection.baseCollection(),
            function.composed(morphedCollection.function())
        );
    }
}
