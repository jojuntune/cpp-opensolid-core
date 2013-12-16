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

#include <OpenSolid/Core/SpatialCollection/MappedCollection.definitions.hpp>

#include <OpenSolid/Core/SpatialCollection.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection, class TMappingFunction>
        inline
        MappedCollection<TBaseCollection, TMappingFunction>::MappedCollection(
            const MappedCollection<TBaseCollection, TMappingFunction>& other
        ) : _baseCollection(other._baseCollection),
            _mappingFunction(other._mappingFunction) {
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        MappedCollection<TBaseCollection, TMappingFunction>::MappedCollection(
            MappedCollection<TBaseCollection, TMappingFunction>&& other
        ) : _baseCollection(std::move(other._baseCollection)),
            _mappingFunction(other._mappingFunction) {
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        MappedCollection<TBaseCollection, TMappingFunction>::MappedCollection(
            const TBaseCollection& baseCollection,
            TMappingFunction mappingFunction
        ) : _baseCollection(baseCollection),
            _mappingFunction(mappingFunction) {
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        MappedCollection<TBaseCollection, TMappingFunction>::MappedCollection(
            TBaseCollection&& baseCollection,
            TMappingFunction mappingFunction
        ) : _baseCollection(std::move(baseCollection)),
            _mappingFunction(mappingFunction) {
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        MappedCollectionIterator<TBaseCollection, TMappingFunction>
        MappedCollection<TBaseCollection, TMappingFunction>::begin() const {
            return MappedCollectionIterator<TBaseCollection, TMappingFunction>(
                _baseCollection.begin(),
                &_mappingFunction
            );
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        MappedCollectionIterator<TBaseCollection, TMappingFunction>
        MappedCollection<TBaseCollection, TMappingFunction>::end() const {
            return MappedCollectionIterator<TBaseCollection, TMappingFunction>(
                _baseCollection.end(),
                &_mappingFunction
            );
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        bool
        MappedCollection<TBaseCollection, TMappingFunction>::isEmpty() const {
            return _baseCollection.isEmpty();
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        std::int64_t
        MappedCollection<TBaseCollection, TMappingFunction>::size() const {
            return _baseCollection.size();
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        typename BoundsType<MappedCollection<TBaseCollection, TMappingFunction>>::Type
        MappedCollection<TBaseCollection, TMappingFunction>::bounds() const {
            return boundsDefaultImpl();
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        void
        MappedCollectionIterator<TBaseCollection, TMappingFunction>::increment() {
            ++_baseIterator;
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        bool
        MappedCollectionIterator<TBaseCollection, TMappingFunction>::equal(
            const MappedCollectionIterator<TBaseCollection, TMappingFunction>& other
        ) const {
            assert(_mappingFunctionPtr == other._mappingFunctionPtr);
            return _baseIterator == other._baseIterator;
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        typename ItemType<MappedCollection<TBaseCollection, TMappingFunction>>::Type
        MappedCollectionIterator<TBaseCollection, TMappingFunction>::dereference() const {
            return (*_mappingFunctionPtr)(*_baseIterator);
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        MappedCollectionIterator<TBaseCollection, TMappingFunction>::MappedCollectionIterator() :
            _baseIterator(),
            _mappingFunctionPtr(nullptr) {
        }

        template <class TBaseCollection, class TMappingFunction>
        inline
        MappedCollectionIterator<TBaseCollection, TMappingFunction>::MappedCollectionIterator(
            typename IteratorType<TBaseCollection>::Type baseIterator,
            const TMappingFunction* mappingFunctionPtr
        ) : _baseIterator(baseIterator),
            _mappingFunctionPtr(mappingFunctionPtr) {
        }
    }
}
