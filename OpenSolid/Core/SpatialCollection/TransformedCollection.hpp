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

#include <OpenSolid/Core/SpatialCollection/TransformedCollection.definitions.hpp>

#include <OpenSolid/Core/SpatialCollection.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection, int iNumResultDimensions>
        inline
        TransformedCollection<TBaseCollection, iNumResultDimensions>::TransformedCollection(
            const TransformedCollection<TBaseCollection, iNumResultDimensions>& other
        ) : _baseCollection(other._baseCollection),
            _transformationMatrix(other._transformationMatrix) {
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        TransformedCollection<TBaseCollection, iNumResultDimensions>::TransformedCollection(
            TransformedCollection<TBaseCollection, iNumResultDimensions>&& other
        ) : _baseCollection(std::move(other._baseCollection)),
            _transformationMatrix(other._transformationMatrix) {
        }

        template <class TBaseCollection, int iNumResultDimensions> template <class TMatrix>
        inline
        TransformedCollection<TBaseCollection, iNumResultDimensions>::TransformedCollection(
            const TBaseCollection& baseCollection,
            const EigenBase<TMatrix>& transformationMatrix
        ) : _baseCollection(baseCollection), 
            _transformationMatrix(transformationMatrix.derived()) {
        }

        template <class TBaseCollection, int iNumResultDimensions> template <class TMatrix>
        inline
        TransformedCollection<TBaseCollection, iNumResultDimensions>::TransformedCollection(
            TBaseCollection&& baseCollection,
            const EigenBase<TMatrix>& transformationMatrix
        ) : _baseCollection(std::move(baseCollection)), 
            _transformationMatrix(transformationMatrix.derived()) {
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        const TBaseCollection&
        TransformedCollection<TBaseCollection, iNumResultDimensions>::baseCollection() const {
            return _baseCollection;
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        const Matrix<double, iNumResultDimensions, NumDimensions<TBaseCollection>::Value>&
        TransformedCollection<TBaseCollection, iNumResultDimensions>::transformationMatrix() const {
            return _transformationMatrix;
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>
        TransformedCollection<TBaseCollection, iNumResultDimensions>::begin() const {
            return TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>(
                baseCollection().begin(),
                &transformationMatrix()
            );
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>
        TransformedCollection<TBaseCollection, iNumResultDimensions>::end() const {
            return TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>(
                baseCollection().end(),
                &transformationMatrix()
            );
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        bool
        TransformedCollection<TBaseCollection, iNumResultDimensions>::isEmpty() const {
            return baseCollection().isEmpty();
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        std::int64_t
        TransformedCollection<TBaseCollection, iNumResultDimensions>::size() const {
            return baseCollection().size();
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        typename TransformedType<
            typename BoundsType<TBaseCollection>::Type,
            iNumResultDimensions
        >::Type
        TransformedCollection<TBaseCollection, iNumResultDimensions>::bounds() const {
            return transformationFunction(baseCollection().bounds(), transformationMatrix());
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        void
        TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>::increment() {
            ++_baseIterator;
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        bool
        TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>::equal(
            const TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>& other
        ) const {
            assert(*_transformationMatrixPtr == *other._transformationMatrixPtr);
            return _baseIterator == other._baseIterator;
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        typename TransformedType<
            typename ItemType<TBaseCollection>::Type,
            iNumResultDimensions
        >::Type
        TransformedCollectionIterator<TBaseCollection, iNumResultDimensions>::dereference() const {
            return transformationFunction(*_baseIterator, *_transformationMatrixPtr);
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        TransformedCollectionIterator<
            TBaseCollection,
            iNumResultDimensions
        >::TransformedCollectionIterator() :
            _transformationMatrixPtr(nullptr) {
        }

        template <class TBaseCollection, int iNumResultDimensions>
        inline
        TransformedCollectionIterator<
            TBaseCollection,
            iNumResultDimensions
        >::TransformedCollectionIterator(
            typename IteratorType<TBaseCollection>::Type baseIterator,
            const Matrix<
                double,
                iNumResultDimensions,
                NumDimensions<TBaseCollection>::Value
            >* transformationMatrixPtr
        ) : _baseIterator(baseIterator),
            _transformationMatrixPtr(transformationMatrixPtr) {
        }
    }

    template <class TBaseCollection, int iNumResultDimensions>
    inline
    detail::TransformedCollection<TBaseCollection, iNumResultDimensions>
    ScalingFunction<
        detail::TransformedCollection<TBaseCollection, iNumResultDimensions>
    >::operator()(
        const detail::TransformedCollection<
            TBaseCollection,
            iNumResultDimensions
        >& transformedCollection,
        double scale
    ) const {
        return detail::TransformedCollection<TBaseCollection, iNumResultDimensions>(
            transformedCollection.baseCollection(),
            scale * transformedCollection.transformationMatrix()
        );
    }

    template <class TBaseCollection, int iNumInnerResultDimensions, int iNumOuterResultDimensions>
    template <class TMatrix>
    inline
    detail::TransformedCollection<TBaseCollection, iNumOuterResultDimensions>
    TransformationFunction<
        detail::TransformedCollection<TBaseCollection, iNumInnerResultDimensions>,
        iNumOuterResultDimensions
    >::operator()(
        const detail::TransformedCollection<
            TBaseCollection,
            iNumInnerResultDimensions
        >& transformedCollection,
        const EigenBase<TMatrix>& matrix
    ) const {
        return detail::TransformedCollection<TBaseCollection, iNumOuterResultDimensions>(
            transformedCollection.baseCollection(),
            matrix.derived() * transformedCollection.transformationMatrix()
        );
    }
}
