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

#include <OpenSolid/Core/SpatialCollection/ScaledCollection.definitions.hpp>

#include <OpenSolid/Core/SpatialCollection.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection>
        inline
        ScaledCollection<TBaseCollection>::ScaledCollection(
            const ScaledCollection<TBaseCollection>& other
        ) : _baseCollection(other._baseCollection),
            _scale(other._scale) {
        }

        template <class TBaseCollection>
        inline
        ScaledCollection<TBaseCollection>::ScaledCollection(
            ScaledCollection<TBaseCollection>&& other
        ) : _baseCollection(std::move(other._baseCollection)),
            _scale(other._scale) {
        }

        template <class TBaseCollection>
        inline
        ScaledCollection<TBaseCollection>::ScaledCollection(
            const TBaseCollection& baseCollection,
            double scale
        ) : _baseCollection(baseCollection), 
            _scale(scale) {
        }

        template <class TBaseCollection>
        inline
        ScaledCollection<TBaseCollection>::ScaledCollection(
            TBaseCollection&& baseCollection,
            double scale
        ) : _baseCollection(std::move(baseCollection)),
            _scale(scale) {
        }

        template <class TBaseCollection>
        inline
        const TBaseCollection&
        ScaledCollection<TBaseCollection>::baseCollection() const {
            return _baseCollection;
        }

        template <class TBaseCollection>
        inline
        double
        ScaledCollection<TBaseCollection>::scale() const {
            return _scale;
        }

        template <class TBaseCollection>
        inline
        ScaledCollectionIterator<TBaseCollection>
        ScaledCollection<TBaseCollection>::begin() const {
            return ScaledCollectionIterator<TBaseCollection>(baseCollection().begin(), scale());
        }

        template <class TBaseCollection>
        inline
        ScaledCollectionIterator<TBaseCollection>
        ScaledCollection<TBaseCollection>::end() const {
            return ScaledCollectionIterator<TBaseCollection>(baseCollection().end(), scale());
        }

        template <class TBaseCollection>
        inline
        bool
        ScaledCollection<TBaseCollection>::isEmpty() const {
            return baseCollection().isEmpty();
        }

        template <class TBaseCollection>
        inline
        std::int64_t
        ScaledCollection<TBaseCollection>::size() const {
            return baseCollection().size();
        }

        template <class TBaseCollection>
        inline
        typename ScaledType<typename BoundsType<TBaseCollection>::Type>::Type
        ScaledCollection<TBaseCollection>::bounds() const {
            return detail::scaled(baseCollection().bounds(), scale());
        }

        template <class TBaseCollection>
        inline
        void
        ScaledCollectionIterator<TBaseCollection>::increment() {
            ++_baseIterator;
        }

        template <class TBaseCollection>
        inline
        bool
        ScaledCollectionIterator<TBaseCollection>::equal(
            const ScaledCollectionIterator<TBaseCollection>& other
        ) const {
            assert(_scale == other._scale);
            return _baseIterator == other._baseIterator;
        }

        template <class TBaseCollection>
        inline
        typename ScaledType<typename ItemType<TBaseCollection>::Type>::Type
        ScaledCollectionIterator<TBaseCollection>::dereference() const {
            return detail::scaled(*_baseIterator, _scale);
        }

        template <class TBaseCollection>
        inline
        ScaledCollectionIterator<TBaseCollection>::ScaledCollectionIterator() :
            _scale(0.0) {
        }

        template <class TBaseCollection>
        inline
        ScaledCollectionIterator<TBaseCollection>::ScaledCollectionIterator(
            typename IteratorType<TBaseCollection>::Type baseIterator,
            double scale
        ) : _baseIterator(baseIterator),
            _scale(scale) {
        }
    }

    template <class TBaseCollection>
    inline
    detail::ScaledCollection<TBaseCollection>
    ScalingFunction<detail::ScaledCollection<TBaseCollection>>::operator()(
        const detail::ScaledCollection<TBaseCollection>& scaledCollection,
        double scale
    ) const {
        return detail::ScaledCollection<TBaseCollection>(
            scaledCollection.baseCollection(),
            scale * scaledCollection.scale()
        );
    }

    template <class TBaseCollection, int iNumResultDimensions> template <class TMatrix>
    inline
    detail::TransformedCollection<TBaseCollection, iNumResultDimensions>
    TransformationFunction<detail::ScaledCollection<TBaseCollection>, iNumResultDimensions>::operator()(
        const detail::ScaledCollection<TBaseCollection>& scaledCollection,
        const EigenBase<TMatrix>& matrix
    ) const {
        return detail::TransformedCollection<TBaseCollection, iNumResultDimensions>(
            scaledCollection.baseCollection(),
            scaledCollection.scale() * matrix.derived()
        );
    }
}
