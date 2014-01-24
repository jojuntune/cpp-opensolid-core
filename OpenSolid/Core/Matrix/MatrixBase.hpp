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

#include <OpenSolid/Core/Matrix/MatrixBase.definitions.hpp>

#include <OpenSolid/Core/Matrix.definitions.hpp>

#include <algorithm>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        MatrixBase<TScalar, iNumRows, iNumColumns>::MatrixBase() {
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        MatrixBase<TScalar, iNumRows, iNumColumns>::MatrixBase(const TScalar* sourcePtr) {
            TScalar* destinationPtr = _components;
            for (std::int64_t index = 0; index < Size; ++index, ++sourcePtr, ++destinationPtr) {
                *destinationPtr = *sourcePtr;
            }
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::component(std::int64_t index) const {
            return _components[index];
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar&
        MatrixBase<TScalar, iNumRows, iNumColumns>::component(std::int64_t index) {
            return _components[index];
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::component(
            std::int64_t rowIndex,
            std::int64_t columnIndex
        ) const {
            return component(columnIndex * iNumRows + rowIndex);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar&
        MatrixBase<TScalar, iNumRows, iNumColumns>::component(
            std::int64_t rowIndex,
            std::int64_t columnIndex
        ) {
            return component(columnIndex * iNumRows + rowIndex);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator()(std::int64_t index) const {
            return component(index);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar&
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator()(std::int64_t index) {
            return component(index);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator()(
            std::int64_t rowIndex,
            std::int64_t columnIndex
        ) const {
            return component(rowIndex, columnIndex);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar&
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator()(
            std::int64_t rowIndex,
            std::int64_t columnIndex
        ) {
            return component(rowIndex, columnIndex);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const typename MatrixType<TScalar, 1, iNumColumns>::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::row(std::int64_t rowIndex) const {
            typename MatrixType<TScalar, 1, iNumColumns>::Type result;
            for (std::int64_t columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
                result.component(columnIndex) = component(rowIndex, columnIndex);
            }
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const typename MatrixType<TScalar, iNumRows, 1>::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::column(std::int64_t columnIndex) const {
            typename MatrixType<TScalar, iNumRows, 1>::Type result;
            for (std::int64_t rowIndex = 0; rowIndex < iNumColumns; ++rowIndex) {
                result.component(rowIndex) = component(rowIndex, columnIndex);
            }
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar*
        MatrixBase<TScalar, iNumRows, iNumColumns>::data() const {
            return _components;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar*
        MatrixBase<TScalar, iNumRows, iNumColumns>::data() {
            return _components;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::fill(TScalar value) {
            std::fill_n(_components, Size, value);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const typename MatrixType<TScalar, iNumColumns, iNumRows>::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::transpose() const {
            typename MatrixType<TScalar, iNumColumns, iNumRows>::Type result;
            for (std::int64_t columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
                for (std::int64_t rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                    result.component(columnIndex, rowIndex) = component(rowIndex, columnIndex);
                }
            }
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TUnaryPredicate>
        inline
        const bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::any(TUnaryPredicate unaryPredicate) const {
            const TScalar* scalarPtr = data();
            for (std::int64_t index = 0; index < Size; ++index, ++scalarPtr) {
                if (unaryPredicate(*scalarPtr)) {
                    return true;
                }
            }
            return false;
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TUnaryPredicate>
        inline
        const bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::all(TUnaryPredicate unaryPredicate) const {
            const TScalar* scalarPtr = data();
            for (std::int64_t index = 0; index < Size; ++index, ++scalarPtr) {
                if (!unaryPredicate(*scalarPtr)) {
                    return false;
                }
            }
            return true;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        template <class TBinaryPredicate, class TOtherScalar>
        inline
        const bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::binaryAny(
            const MatrixBase<TOtherScalar, iNumRows, iNumColumns>& other,
            TBinaryPredicate binaryPredicate
        ) const {
            const TScalar* scalarPtr = data();
            const TOtherScalar* otherScalarPtr = other.data();
            for (std::int64_t index = 0; index < Size; ++index, ++scalarPtr,++otherScalarPtr) {
                if (binaryPredicate(*scalarPtr, *otherScalarPtr)) {
                    return true;
                }
            }
            return false;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        template <class TBinaryPredicate, class TOtherScalar>
        inline
        const bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::binaryAll(
            const MatrixBase<TOtherScalar, iNumRows, iNumColumns>& other,
            TBinaryPredicate binaryPredicate
        ) const {
            const TScalar* scalarPtr = data();
            const TOtherScalar* otherScalarPtr = other.data();
            for (std::int64_t index = 0; index < Size; ++index, ++scalarPtr, ++otherScalarPtr) {
                if (!binaryPredicate(*scalarPtr, *otherScalarPtr)) {
                    return false;
                }
            }
            return true;
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TUnaryFunction>
        inline
        const typename MappedMatrixType<
            TUnaryFunction,
            TScalar,
            iNumRows,
            iNumColumns
        >::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::map(TUnaryFunction unaryFunction) const {
            typename MappedMatrixType<
                TUnaryFunction,
                TScalar,
                iNumRows,
                iNumColumns
            >::Type result;

            const TScalar* sourcePtr = data();
            typename MappedScalarType<TUnaryFunction, TScalar>::Type*
                destinationPtr = result.data();
            for (std::int64_t index = 0; index < Size; ++index, ++sourcePtr, ++destinationPtr) {
                *destinationPtr = unaryFunction(*sourcePtr);
            }

            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        template <class TBinaryFunction, class TOtherScalar>
        inline
        const typename PairwiseMappedMatrixType<
            TBinaryFunction,
            TScalar,
            TOtherScalar,
            iNumRows,
            iNumColumns
        >::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::binaryMap(
            const MatrixBase<TOtherScalar, iNumRows, iNumColumns>& other,
            TBinaryFunction binaryFunction
        ) const {
            typename PairwiseMappedMatrixType<
                TBinaryFunction,
                TScalar,
                TOtherScalar,
                iNumRows,
                iNumColumns
            >::Type result;

            const TScalar* sourcePtr = data();
            const TOtherScalar* otherSourcePtr = other.data();
            typename PairwiseMappedScalarType<TBinaryFunction, TScalar, TOtherScalar>::Type*
                destinationPtr = result.data();
            for (
                std::int64_t index = 0;
                index < Size;
                ++index, ++sourcePtr, ++otherSourcePtr, ++destinationPtr
            ) {
                *destinationPtr = binaryFunction(*sourcePtr, *otherSourcePtr);
            }

            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::Constant(TScalar value) {
            typename MatrixType<TScalar, iNumRows, iNumColumns>::Type result;
            result.fill(value);
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::Zero() {
            return Constant(TScalar(0));
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::Zero() {
            return Constant(TScalar(1));
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::Identity() {
            typename MatrixType<TScalar, iNumRows, iNumColumns>::Type result;
            result.fill(TScalar(0));
            std::int64_t count = min(iNumRows, iNumColumns);
            for (std::int64_t index = 0; index < count; ++index) {
                result(index, index) = TScalar(1);
            }
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::OuterProduct
            const typename MatrixType<TScalar, iNumRows, 1>& columnMatrix,
            const typename MatrixType<TScalar, 1, iNumColumns>& rowMatrix
        ) {
            typename MatrixType<TScalar, iNumRows, iNumColumns>::Type result;
            for (std::int64_t columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
                for (std::int64_t rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                    result(rowIndex, columnIndex) = columnMatrix(rowIndex, 1) *
                        rowMatrix(1, columnIndex);
                }
            }
            return result;
        }
    }
}
