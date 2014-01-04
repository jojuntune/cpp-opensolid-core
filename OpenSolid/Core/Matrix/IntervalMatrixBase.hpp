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

#include <OpenSolid/Core/Matrix/InteravlMatrixBase.definitions.hpp>

#include <OpenSolid/Core/IntervalMatrix.definitions.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>

namespace opensolid
{
    template <int iNumRows, int iNumColumns>
    inline
    IntervalMatrixBase<iNumRows, iNumColumns>::IntervalMatrixBase() {
    }

    template <int iNumRows, int iNumColumns>
    inline
    IntervalMatrixBase<iNumRows, iNumColumns>::IntervalMatrixBase(
        const Matrix<iNumRows, iNumColumns>& matrix
    ) {
        for (int index = 0; index < iNumRows * iNumColumns; ++index) {
            component(index) = matrix.component(index);
        }
    }

    template <int iNumRows, int iNumColumns>
    inline
    const Interval
    MatrixBase<iNumRows, iNumColumns>::component(std::int64_t index) const {
        return _components[index];
    }

    template <int iNumRows, int iNumColumns>
    inline
    Interval&
    MatrixBase<iNumRows, iNumColumns>::component(std::int64_t index) {
        return _components[index];
    }

    template <int iNumRows, int iNumColumns>
    inline
    const Interval
    MatrixBase<iNumRows, iNumColumns>::component(
        std::int64_t rowIndex,
        std::int64_t columnIndex
    ) const {
        return component(columnIndex * iNumRows + rowIndex);
    }

    template <int iNumRows, int iNumColumns>
    inline
    Interval&
    MatrixBase<iNumRows, iNumColumns>::component(
        std::int64_t rowIndex,
        std::int64_t columnIndex
    ) {
        return component(columnIndex * iNumRows + rowIndex);
    }

    template <int iNumRows, int iNumColumns>
    inline
    const Interval
    MatrixBase<iNumRows, iNumColumns>::operator()(std::int64_t index) const {
        return component(index);
    }

    template <int iNumRows, int iNumColumns>
    inline
    Interval&
    MatrixBase<iNumRows, iNumColumns>::operator()(std::int64_t index) {
        return component(index);
    }

    template <int iNumRows, int iNumColumns>
    inline
    const Interval
    MatrixBase<iNumRows, iNumColumns>::operator()(
        std::int64_t rowIndex,
        std::int64_t columnIndex
    ) const {
        return component(rowIndex, columnIndex);
    }

    template <int iNumRows, int iNumColumns>
    inline
    Interval&
    MatrixBase<iNumRows, iNumColumns>::operator()(
        std::int64_t rowIndex,
        std::int64_t columnIndex
    ) {
        return component(rowIndex, columnIndex);
    }

    template <int iNumRows, int iNumColumns>
    inline
    const Interval*
    IntervalMatrixBase<iNumRows, iNumColumns>::data() const {
        return _components;
    }

    template <int iNumRows, int iNumColumns>
    inline
    Interval*
    IntervalMatrixBase<iNumRows, iNumColumns>::data() {
        return _components;
    }

    template <int iNumRows, int iNumColumns>
    inline
    const IntervalMatrix<iNumColumns, iNumRows>
    IntervalMatrixBase<iNumRows, iNumColumns>::transpose() const {
        IntervalMatrix<iNumColumns, iNumRows> result;
        for (std::int64_t columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
            for (std::int64_t rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                result.component(columnIndex, rowIndex) = component(rowIndex, columnIndex);
            }
        }
        return result;
    }

    template <int iNumRows, int iNumColumns>
    inline
    void
    IntervalMatrixBase<iNumRows, iNumColumns>::operator*=(double scale) {
        for (std::int64_t index = 0; index < iNumRows * iNumColumns; ++index) {
            component(index) *= scale;
        }
    }

    template <int iNumRows, int iNumColumns>
    inline
    void
    IntervalMatrixBase<iNumRows, iNumColumns>::operator*=(Interval scale) {
        for (std::int64_t index = 0; index < iNumRows * iNumColumns; ++index) {
            component(index) *= scale;
        }
    }

    template <int iNumRows, int iNumColumns>
    inline
    void
    IntervalMatrixBase<iNumRows, iNumColumns>::operator+=(
        const Matrix<iNumRows, iNumColumns>& matrix
    ) {
        for (std::int64_t index = 0; index < iNumRows * iNumColumns; ++index) {
            component(index) += matrix.component(index);
        }
    }

    template <int iNumRows, int iNumColumns>
    inline
    void
    IntervalMatrixBase<iNumRows, iNumColumns>::operator+=(
        const IntervalMatrix<iNumRows, iNumColumns>& other
    ) {
        for (std::int64_t index = 0; index < iNumRows * iNumColumns; ++index) {
            component(index) += other.component(index);
        }
    }

    template <int iNumRows, int iNumColumns>
    inline
    void
    IntervalMatrixBase<iNumRows, iNumColumns>::operator-=(
        const Matrix<iNumRows, iNumColumns>& matrix
    ) {
        for (std::int64_t index = 0; index < iNumRows * iNumColumns; ++index) {
            component(index) -= matrix.component(index);
        }
    }

    template <int iNumRows, int iNumColumns>
    inline
    void
    IntervalMatrixBase<iNumRows, iNumColumns>::operator-=(
        const IntervalMatrix<iNumRows, iNumColumns>& other
    ) {
        for (std::int64_t index = 0; index < iNumRows * iNumColumns; ++index) {
            component(index) -= other.component(index);
        }
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    IntervalMatrixBase<iNumRows, iNumColumns>::OuterProduct(
        const IntervalMatrix<iNumRows, 1>& columnMatrix,
        const IntervalMatrix<1, iNumColumns>& rowMatrix
    ) {
        IntervalMatrix<iNumRows, iNumColumns> result;
        for (std::int64_t columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
            for (std::int64_t rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                result(rowIndex, columnIndex) =
                    columnMatrix(rowIndex, 1) * rowMatrix(1, columnIndex);
            }
        }
        return result;
    }
}
