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

#include <OpenSolid/Core/SpatialCollection/TranslatedCollection.definitions.hpp>

#include <OpenSolid/Core/SpatialCollection.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TCollection>
        inline
        TranslatedCollectionIterator<TCollection>
        TranslatedCollection<TCollection>::beginImpl() const {
            return TranslatedCollectionIterator<TCollection>(_baseCollection.begin(), &vector());
        }

        template <class TCollection>
        inline
        TranslatedCollectionIterator<TCollection>
        TranslatedCollection<TCollection>::endImpl() const {
            return TranslatedCollectionIterator<TCollection>(_baseCollection.end(), &vector());
        }

        template <class TCollection>
        inline
        bool
        TranslatedCollection<TCollection>::isEmptyImpl() const {
            return _baseCollection.isEmpty();
        }

        template <class TCollection>
        inline
        std::int64_t
        TranslatedCollection<TCollection>::sizeImpl() const {
            return _baseCollection.size();
        }

        template <class TCollection>
        inline
        typename BoundsType<typename ItemType<TCollection>::Type>::Type
        TranslatedCollection<TCollection>::boundsImpl() const {
            return detail::translated(_baseCollection.bounds(), vector());
        }

        template <class TCollection> template <class TVector>
        inline
        TranslatedCollection<TCollection>::TranslatedCollection(
            const TCollection& baseCollection,
            const EigenBase<TVector>& vector
        ) : _baseCollection(baseCollection), 
            _vector(vector.derived()) {
        }

        template <class TCollection>
        inline
        const TCollection&
        TranslatedCollection<TCollection>::baseCollection() const {
            return _baseCollection;
        }

        template <class TCollection>
        inline
        const Matrix<double, NumDimensions<TCollection>::Value, 1>&
        TranslatedCollection<TCollection>::vector() const {
            return _vector;
        }

        template <class TCollection>
        inline
        void
        TranslatedCollectionIterator<TCollection>::increment() {
            ++_baseIterator;
        }

        template <class TCollection>
        inline
        bool
        TranslatedCollectionIterator<TCollection>::equal(
            const TranslatedCollectionIterator<TCollection>& other
        ) const {
            assert(*_vector == *other._vector);
            return _baseIterator == other._baseIterator;
        }

        template <class TCollection>
        inline
        const typename ItemType<TCollection>::Type&
        TranslatedCollectionIterator<TCollection>::dereference() const {
            return detail::translated(*_baseIterator, *_vector);
        }

        template <class TCollection>
        inline
        TranslatedCollectionIterator<TCollection>::TranslatedCollectionIterator() {
            _vector.setZero();
        }

        template <class TCollection>
        inline
        TranslatedCollectionIterator<TCollection>::TranslatedCollectionIterator(
            typename IteratorType<TCollection>::Type baseIterator,
            const Matrix<double, NumDimensions<TCollection>::Value, 1>* vector
        ) : _baseIterator(baseIterator),
            _vector(vector) {
        }
    }
}
