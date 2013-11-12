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
        template <class TBaseCollection>
        inline
        TranslatedCollection<TBaseCollection>::TranslatedCollection(
            const TranslatedCollection<TBaseCollection>& other
        ) : _baseCollection(other._baseCollection),
            _vector(other._vector) {
        }

        template <class TBaseCollection>
        inline
        TranslatedCollection<TBaseCollection>::TranslatedCollection(
            TranslatedCollection<TBaseCollection>&& other
        ) : _baseCollection(std::move(other._baseCollection)),
            _vector(other._vector) {
        }

        template <class TBaseCollection> template <class TVector>
        inline
        TranslatedCollection<TBaseCollection>::TranslatedCollection(
            const TBaseCollection& baseCollection,
            const EigenBase<TVector>& vector
        ) : _baseCollection(baseCollection), 
            _vector(vector.derived()) {
        }

        template <class TBaseCollection> template <class TVector>
        inline
        TranslatedCollection<TBaseCollection>::TranslatedCollection(
            TBaseCollection&& baseCollection,
            const EigenBase<TVector>& vector
        ) : _baseCollection(std::move(baseCollection)), 
            _vector(vector.derived()) {
        }

        template <class TBaseCollection>
        inline
        const TBaseCollection&
        TranslatedCollection<TBaseCollection>::baseCollection() const {
            return _baseCollection;
        }

        template <class TBaseCollection>
        inline
        const Matrix<double, NumDimensions<TBaseCollection>::Value, 1>&
        TranslatedCollection<TBaseCollection>::vector() const {
            return _vector;
        }

        template <class TBaseCollection>
        inline
        TranslatedCollectionIterator<TBaseCollection>
        TranslatedCollection<TBaseCollection>::begin() const {
            return TranslatedCollectionIterator<TBaseCollection>(
                baseCollection().begin(),
                &vector()
            );
        }

        template <class TBaseCollection>
        inline
        TranslatedCollectionIterator<TBaseCollection>
        TranslatedCollection<TBaseCollection>::end() const {
            return TranslatedCollectionIterator<TBaseCollection>(
                baseCollection().end(),
                &vector()
            );
        }

        template <class TBaseCollection>
        inline
        bool
        TranslatedCollection<TBaseCollection>::isEmpty() const {
            return baseCollection().isEmpty();
        }

        template <class TBaseCollection>
        inline
        std::int64_t
        TranslatedCollection<TBaseCollection>::size() const {
            return baseCollection().size();
        }

        template <class TBaseCollection>
        inline
        typename TranslatedType<typename BoundsType<TBaseCollection>::Type>::Type
        TranslatedCollection<TBaseCollection>::bounds() const {
            return detail::translated(baseCollection().bounds(), vector());
        }

        template <class TBaseCollection>
        inline
        void
        TranslatedCollectionIterator<TBaseCollection>::increment() {
            ++_baseIterator;
        }

        template <class TBaseCollection>
        inline
        bool
        TranslatedCollectionIterator<TBaseCollection>::equal(
            const TranslatedCollectionIterator<TBaseCollection>& other
        ) const {
            assert(*_vector == *other._vector);
            return _baseIterator == other._baseIterator;
        }

        template <class TBaseCollection>
        inline
        typename TranslatedType<typename ItemType<TBaseCollection>::Type>::Type
        TranslatedCollectionIterator<TBaseCollection>::dereference() const {
            return detail::translated(*_baseIterator, *_vector);
        }

        template <class TBaseCollection>
        inline
        TranslatedCollectionIterator<TBaseCollection>::TranslatedCollectionIterator() :
            _vector(nullptr) {
        }

        template <class TBaseCollection>
        inline
        TranslatedCollectionIterator<TBaseCollection>::TranslatedCollectionIterator(
            typename IteratorType<TBaseCollection>::Type baseIterator,
            const Matrix<double, NumDimensions<TBaseCollection>::Value, 1>* vector
        ) : _baseIterator(baseIterator),
            _vector(vector) {
        }
    }

    template <class TBaseCollection> template <class TVector>
    inline
    detail::TranslatedCollection<TBaseCollection>
    TranslationFunction<detail::TranslatedCollection<TBaseCollection>>::operator()(
        const detail::TranslatedCollection<TBaseCollection>& translatedCollection,
        const EigenBase<TVector>& vector
    ) const {
        return detail::TranslatedCollection<TBaseCollection>(
            translatedCollection.baseCollection(),
            translatedCollection.vector() + vector.derived()
        );
    }
}
