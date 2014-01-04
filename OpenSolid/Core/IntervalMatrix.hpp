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

#include <OpenSolid/Core/IntervalMatrix.definitions.hpp>

#include <cstdlib>

namespace opensolid
{
    template <int iNumRows, int iNumColumns>
    inline
    IntervalMatrix<iNumRows, iNumColumns>::IntervalMatrix() :
        IntervalMatrixBase<iNumRows, iNumColumns>() {
    }

    template <int iNumRows, int iNumColumns>
    inline
    IntervalMatrix<iNumRows, iNumColumns>::IntervalMatrix(
        const Matrix<iNumRows, iNumColumns>& matrix
    ) : IntervalMatrixBase<iNumRows, iNumColumns>(matrix) {
    }

    inline
    IntervalMatrix1d::IntervalMatrix() :
        IntervalMatrixBase<1, 1>() {
    }

    inline
    IntervalMatrix1d::Matrix(Interval value) :
        IntervalMatrixBase<1, 1>() {

        component(0) = value;
    }

    inline
    IntervalMatrix1d::IntervalMatrix(const Matrix1d& matrix) :
        IntervalMatrixBase<1, 1>(matrix) {
    }

    inline
    const Interval
    IntervalMatrix1d::value() const {
        return component(0);
    }

    inline
    Interval&
    IntervalMatrix1d::value() {
        return component(0);
    }

    inline
    const Interval
    IntervalMatrix1d::determinant() const {
        return value();
    }

    inline
    const Matrix1d
    IntervalMatrix1d::inverse() const {
        return IntervalMatrix1d(1.0 / value());
    }

    inline
    IntervalMatrix2d::IntervalMatrix() :
        IntervalMatrixBase<2, 2>() {
    }

    inline
    IntervalMatrix2d::IntervalMatrix(Interval a, Interval b, Interval c, Interval d) :
        IntervalMatrixBase<2, 2>() {

        component(0) = a;
        component(1) = c;
        component(2) = b;
        component(3) = d;
    }

    inline
    IntervalMatrix2d::IntervalMatrix(const Matrix2d& matrix) :
        IntervalMatrixBase<2, 2>(matrix) {
    }

    inline
    Interval
    Matrix2d::determinant() const {
        return component(0) * component(3) - component(2) * component(1);
    }

    inline
    const IntervalMatrix2d
    IntervalMatrix2d::inverse() const {
        Interval determinant = this->determinant();
        Interval reciprocal = 1.0 / determinant;
        return IntervalMatrix2d(
            reciprocal * component(3),
            -reciprocal * component(2),
            -reciprocal * component(1),
            reciprocal * component(0)
        );
    }

    inline
    IntervalMatrix3d::IntervalMatrix() :
        IntervalMatrixBase<3, 3>() {
    }

    inline
    IntervalMatrix3d::IntervalMatrix(
        Interval a11,
        Interval a12,
        Interval a13,
        Interval a21,
        Interval a22,
        Interval a23,
        Interval a31,
        Interval a32,
        Interval a33
    ) : IntervalMatrixBase<3, 3>() {

        component(0) = a11;
        component(1) = a21;
        component(2) = a31;
        component(3) = a12;
        component(4) = a22;
        component(5) = a32;
        component(6) = a13;
        component(7) = a23;
        component(8) = a33;
    }

    inline
    IntervalMatrix3d::IntervalMatrix(const Matrix3d& matrix) :
        IntervalMatrixBase<3, 3>(matrix) {
    }

    inline
    IntervalColumnMatrix2d::IntervalMatrix() :
        IntervalMatrixBase<2, 1>() {
    }

    inline
    IntervalColumnMatrix2d::IntervalMatrix(Interval x, Interval y) :
        IntervalMatrixBase<2, 1>() {

        component(0) = x;
        component(1) = y;
    }

    inline
    IntervalColumnMatrix2d::IntervalMatrix(const ColumnMatrix2d& columnMatrix) :
        IntervalMatrixBase<2, 1>(columnMatrix) {
    }

    inline
    IntervalColumnMatrix3d::Matrix() :
        IntervalMatrixBase<3, 1>() {
    }

    inline
    IntervalColumnMatrix3d::Matrix(Interval x, Interval y, Interval z) :
        IntervalMatrixBase<3, 1>() {

        component(0) = x;
        component(1) = y;
        component(2) = z;
    }

    inline
    IntervalColumnMatrix3d::IntervalMatrix(const ColumnMatrix2d& columnMatrix) :
        IntervalMatrixBase<3, 1>(columnMatrix) {
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(Interval scale, const Matrix<iNumRows, iNumColumns>& matrix) {
        IntervalMatrix<iNumRows, iNumColumns> result;
        for (int index = 0; index < iNumRows * iNumColumns; ++index) {
            result(index) = scale * matrix(index);
        };
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(double scale, const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix) {
        IntervalMatrix<iNumRows, iNumColumns> result(intervalMatrix);
        result *= scale;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator*(Interval scale, const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix) {
        IntervalMatrix<iNumRows, iNumColumns> result(intervalMatrix);
        result *= scale;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(const Matrix<iNumRows, iNumColumns>& matrix, Interval scale) {
        IntervalMatrix<iNumRows, iNumColumns> result;
        for (int index = 0; index < iNumRows * iNumColumns; ++index) {
            result(index) = scale * matrix(index);
        };
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, double scale) {
        IntervalMatrix<iNumRows, iNumColumns> result(intervalMatrix);
        result *= scale;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator*(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, Interval scale) {
        IntervalMatrix<iNumRows, iNumColumns> result(intervalMatrix);
        result *= scale;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator/(const Matrix<iNumRows, iNumColumns>& matrix, Interval divisor) {
        IntervalMatrix<iNumRows, iNumColumns> result;
        for (int index = 0; index < iNumRows * iNumColumns; ++index) {
            result(index) = matrix(index) / divisor;
        }
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator/(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, double divisor) {
        if (divisor == Zero()) {
            IntervalMatrix<iNumRows, iNumColumns> result;
            for (int index = 0; index < iNumRows * iNumColumns; ++index) {
                result(index) = Interval::Whole();
            }
            return result;
        } else {
            IntervalMatrix<iNumRows, iNumColumns> result(intervalMatrix);
            result *= (1.0 / divisor);
            return result;
        }
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator/(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, Interval divisor) {
        IntervalMatrix<iNumRows, iNumColumns> result(intervalMatrix);
        result *= (1.0 / divisor);
        return result;
    }



    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator+(
        const Matrix<iNumRows, iNumColumns>& matrix,
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix
    ) {
        IntervalMatrix<iNumRows, int iNumColumns> result(intervalMatrix);
        result += matrix;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator+(
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix,
        const Matrix<iNumRows, iNumColumns>& matrix
    ) {
        IntervalMatrix<iNumRows, int iNumColumns> result(intervalMatrix);
        result += matrix;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator+(
        const IntervalMatrix<iNumRows, iNumColumns>& firstIntervalMatrix,
        const IntervalMatrix<iNumRows, iNumColumns>& secondIntervalMatrix
    ) {
        Matrix<iNumRows, int iNumColumns> result(firstIntervalMatrix);
        result += secondIntervalMatrix;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator-(
        const Matrix<iNumRows, iNumColumns>& matrix,
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix
    ) {
        IntervalMatrix<iNumRows, int iNumColumns> result;
        for (int index = 0; index < iNumRows * iNumColumns; ++index) {
            result(index) = matrix(index) - intervalMatrix(index);
        }
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator-(
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix,
        const Matrix<iNumRows, iNumColumns>& matrix
    ) {
        IntervalMatrix<iNumRows, int iNumColumns> result(intervalMatrix);
        result -= matrix;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator-(
        const Matrix<iNumRows, iNumColumns>& firstIntervalMatrix,
        const Matrix<iNumRows, iNumColumns>& secondIntervalMatrix
    ) {
        IntervalMatrix<iNumRows, int iNumColumns> result(firstIntervalMatrix);
        result -= secondIntervalMatrix;
        return result;
    }

    template <int iNumRows, int iNumColumns, int iInnerSize>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator*(
        const Matrix<iNumRows, iInnerSize>& matrix,
        const IntervalMatrix<iInnerSize, iNumColumns>& intervalMatrix
    ) {
        IntervalMatrix<iNumRows, iNumColumns> result;
        for (int columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
            for (int rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                Interval& component = result(rowIndex, columnIndex);
                component = matrix(rowIndex, 0) * intervalMatrix(0, columnIndex);
                for (int innerIndex = 1; innerIndex < iInnerSize; ++innerIndex) {
                    component += matrix(rowIndex, innerIndex) *
                        intervalMatrix(innerIndex, columnIndex);
                }
            }
        }
        return result;
    }

    template <int iNumRows, int iNumColumns, int iInnerSize>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator*(
        const IntervalMatrix<iNumRows, iInnerSize>& intervalMatrix,
        const Matrix<iInnerSize, iNumColumns>& matrix
    ) {
        IntervalMatrix<iNumRows, iNumColumns> result;
        for (int columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
            for (int rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                Interval& component = result(rowIndex, columnIndex);
                component = intervalMatrix(rowIndex, 0) * matrix(0, columnIndex);
                for (int innerIndex = 1; innerIndex < iInnerSize; ++innerIndex) {
                    component += intervalMatrix(rowIndex, innerIndex) *
                        matrix(innerIndex, columnIndex);
                }
            }
        }
        return result;
    }

    template <int iNumRows, int iNumColumns, int iInnerSize>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator*(
        const Matrix<iNumRows, iInnerSize>& firstIntervalMatrix,
        const Matrix<iInnerSize, iNumColumns>& secondIntervalMatrix
    ) {
        IntervalMatrix<iNumRows, iNumColumns> result;
        for (int columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
            for (int rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                Interval& component = result(rowIndex, columnIndex);
                component = firstIntervalMatrix(rowIndex, 0) * secondIntervalMatrix(0, columnIndex);
                for (int innerIndex = 1; innerIndex < iInnerSize; ++innerIndex) {
                    component += firstIntervalMatrix(rowIndex, innerIndex) *
                        secondIntervalMatrix(innerIndex, columnIndex);
                }
            }
        }
        return result;
    }

    template <>
    inline
    const IntervalMatrix<1, 1>
    operator*(const Matrix<1, 1>& matrix, const IntervalMatrix<1, 1>& intervalColumnMatrix) {
        return IntervalMatrix1d(matrix.value() * intervalColumnMatrix.value());
    }

    template <>
    inline
    const IntervalMatrix<1, 1>
    operator*(const IntervalMatrix<1, 1>& intervalMatrix, const Matrix<1, 1>& columnMatrix) {
        return IntervalMatrix1d(intervalMatrix.value() * columnMatrix.value());
    }

    template <>
    inline
    const IntervalMatrix<1, 1>
    operator*(
        const IntervalMatrix<1, 1>& intervalMatrix,
        const Matrix<1, 1>& intervalColumnMatrix
    ) {
        return IntervalMatrix1d(intervalMatrix.value() * intervalColumnMatrix.value());
    }

    template <>
    inline
    const IntervalMatrix<1, 1>
    operator*(const Matrix<1, 2>& matrix, const IntervalMatrix<2, 1>& intervalColumnMatrix) {
        return IntervalMatrix1d(
            matrix(0, 0) * intervalColumnMatrix(0) + matrix(0, 1) * IntervalolumnMatrix(1)
        );
    }

    template <>
    inline
    const IntervalMatrix<1, 1>
    operator*(const IntervalMatrix<1, 2>& intervalMatrix, const Matrix<2, 1>& columnMatrix) {
        return IntervalMatrix1d(
            intervalMatrix(0, 0) * columnMatrix(0) + intervalMatrix(0, 1) * columnMatrix(1)
        );
    }

    template <>
    inline
    const IntervalMatrix<1, 1>
    operator*(
        const IntervalMatrix<1, 2>& intervalMatrix,
        const IntervalMatrix<2, 1>& intervalColumnMatrix
    ) {
        return IntervalMatrix1d(
            intervalMatrix(0, 0) * intervalColumnMatrix(0) +
                intervalMatrix(0, 1) * intervalColumnMatrix(1)
        );
    }

    template <>
    inline
    const IntervalMatrix<1, 1>
    operator*(const Matrix<1, 3>& matrix, const IntervalMatrix<3, 1>& intervalColumnMatrix) {
        return IntervalMatrix1d(
            matrix(0, 0) * intervalColumnMatrix(0) + matrix(0, 1) * intervalColumnMatrix(1) +
                matrix(0, 2) * intervalColumnMatrix(2)
        );
    }

    template <>
    inline
    const IntervalMatrix<1, 1>
    operator*(const IntervalMatrix<1, 3>& intervalMatrix, const Matrix<3, 1>& columnMatrix) {
        return IntervalMatrix1d(
            intervalMatrix(0, 0) * columnMatrix(0) + intervalMatrix(0, 1) * columnMatrix(1) +
                intervalMatrix(0, 2) * columnMatrix(2)
        );
    }

    template <>
    inline
    const IntervalMatrix<1, 1>
    operator*(
        const IntervalMatrix<1, 3>& intervalMatrix,
        const IntervalMatrix<3, 1>& intervalColumnMatrix
    ) {
        return IntervalMatrix1d(
            intervalMatrix(0, 0) * intervalColumnMatrix(0) +
                intervalMatrix(0, 1) * intervalColumnMatrix(1) +
                intervalMatrix(0, 2) * intervalColumnMatrix(2)
        );
    }

    template <>
    inline
    const IntervalMatrix<2, 1>
    operator*(const Matrix<2, 1>& matrix, const IntervalMatrix<1, 1>& intervalColumnMatrix) {
        return IntervalColumnMatrix2d(
            matrix(0, 0) * intervalColumnMatrix(0),
            matrix(1, 0) * intervalColumnMatrix(0)
        );
    }

    template <>
    inline
    const IntervalMatrix<2, 1>
    operator*(const IntervalMatrix<2, 1>& intervalMatrix, const Matrix<1, 1>& columnMatrix) {
        return IntervalColumnMatrix2d(
            intervalMatrix(0, 0) * columnMatrix(0),
            intervalMatrix(1, 0) * columnMatrix(0)
        );
    }

    template <>
    inline
    const IntervalMatrix<2, 1>
    operator*(
        const IntervalMatrix<2, 1>& intervalMatrix,
        const IntervalMatrix<1, 1>& intervalColumnMatrix
    ) {
        return IntervalColumnMatrix2d(
            intervalMatrix(0, 0) * intervalColumnMatrix(0),
            intervalMatrix(1, 0) * intervalColumnMatrix(0)
        );
    }

    template <>
    inline
    const IntervalMatrix<2, 1>
    operator*(const Matrix<2, 2>& matrix, const IntervalMatrix<2, 1>& intervalColumnMatrix) {
        return IntervalColumnMatrix2d(
            matrix(0, 0) * intervalColumnMatrix(0) +
                matrix.component(0, 1) * intervalColumnMatrix(1),
            matrix(1, 0) * intervalColumnMatrix(0) +
                matrix.component(1, 1) * intervalColumnMatrix(1)
        );
    }

    template <>
    inline
    const IntervalMatrix<2, 1>
    operator*(const IntervalMatrix<2, 2>& intervalMatrix, const Matrix<2, 1>& columnMatrix) {
        return IntervalColumnMatrix2d(
            intervalMatrix(0, 0) * columnMatrix(0) +
                intervalMatrix.component(0, 1) * columnMatrix(1),
            intervalMatrix(1, 0) * columnMatrix(0) +
                intervalMatrix.component(1, 1) * columnMatrix(1)
        );
    }

    template <>
    inline
    const IntervalMatrix<2, 1>
    operator*(
        const IntervalMatrix<2, 2>& intervalMatrix,
        const IntervalMatrix<2, 1>& intervalColumnMatrix
    ) {
        return IntervalColumnMatrix2d(
            intervalMatrix(0, 0) * intervalColumnMatrix(0) +
                intervalMatrix.component(0, 1) * intervalColumnMatrix(1),
            intervalMatrix(1, 0) * intervalColumnMatrix(0) +
                intervalMatrix.component(1, 1) * intervalColumnMatrix(1)
        );
    }

    template <>
    inline
    const IntervalMatrix<2, 1>
    operator*(const Matrix<2, 3>& matrix, const IntervalMatrix<3, 1>& intervalColumnMatrix) {
        return IntervalColumnMatrix2d(
            matrix(0, 0) * intervalColumnMatrix(0) + matrix(0, 1) * intervalColumnMatrix(1) +
                matrix(0, 2) * intervalColumnMatrix(2),
            matrix(1, 0) * intervalColumnMatrix(0) + matrix(1, 1) * intervalColumnMatrix(1) +
                matrix(1, 2) * intervalColumnMatrix(2)
        );
    }

    template <>
    inline
    const IntervalMatrix<2, 1>
    operator*(const IntervalMatrix<2, 3>& intervalMatrix, const Matrix<3, 1>& columnMatrix) {
        return IntervalColumnMatrix2d(
            intervalMatrix(0, 0) * columnMatrix(0) + intervalMatrix(0, 1) * columnMatrix(1) +
                intervalMatrix(0, 2) * columnMatrix(2),
            intervalMatrix(1, 0) * columnMatrix(0) + intervalMatrix(1, 1) * columnMatrix(1) +
                intervalMatrix(1, 2) * columnMatrix(2)
        );
    }

    template <>
    inline
    const IntervalMatrix<2, 1>
    operator*(
        const IntervalMatrix<2, 3>& intervalMatrix,
        const IntervalMatrix<3, 1>& intervalColumnMatrix
    ) {
        return IntervalColumnMatrix2d(
            intervalMatrix(0, 0) * intervalColumnMatrix(0) +
                intervalMatrix(0, 1) * intervalColumnMatrix(1) +
                intervalMatrix(0, 2) * intervalColumnMatrix(2),
            intervalMatrix(1, 0) * intervalColumnMatrix(0) +
                intervalMatrix(1, 1) * intervalColumnMatrix(1) +
                intervalMatrix(1, 2) * intervalColumnMatrix(2)
        );
    }

    template <>
    inline
    const IntervalMatrix<3, 1>
    operator*(const Matrix<3, 1>& matrix, const IntervalMatrix<1, 1>& intervalColumnMatrix) {
        return IntervalColumnMatrix3d(
            matrix(0, 0) * intervalColumnMatrix(0),
            matrix(1, 0) * intervalColumnMatrix(0),
            matrix(2, 0) * intervalColumnMatrix(0)
        );
    }

    template <>
    inline
    const IntervalMatrix<3, 1>
    operator*(const IntervalMatrix<3, 1>& intervalMatrix, const Matrix<1, 1>& columnMatrix) {
        return IntervalColumnMatrix3d(
            intervalMatrix(0, 0) * columnMatrix(0),
            intervalMatrix(1, 0) * columnMatrix(0),
            intervalMatrix(2, 0) * columnMatrix(0)
        );
    }

    template <>
    inline
    const IntervalMatrix<3, 1>
    operator*(
        const IntervalMatrix<3, 1>& intervalMatrix,
        const IntervalMatrix<1, 1>& intervalColumnMatrix
    ) {
        return IntervalColumnMatrix3d(
            intervalMatrix(0, 0) * intervalColumnMatrix(0),
            intervalMatrix(1, 0) * intervalColumnMatrix(0),
            intervalMatrix(2, 0) * intervalColumnMatrix(0)
        );
    }

    template <>
    inline
    const IntervalMatrix<3, 1>
    operator*(const Matrix<3, 2>& matrix, const IntervalMatrix<2, 1>& intervalColumnMatrix) {
        return IntervalColumnMatrix3d(
            matrix(0, 0) * intervalColumnMatrix(0) +
                matrix.component(0, 1) * intervalColumnMatrix(1),
            matrix(1, 0) * intervalColumnMatrix(0) +
                matrix.component(1, 1) * intervalColumnMatrix(1),
            matrix(2, 0) * intervalColumnMatrix(0) +
                matrix.component(2, 1) * intervalColumnMatrix(1)
        );
    }

    template <>
    inline
    const IntervalMatrix<3, 1>
    operator*(const IntervalMatrix<3, 2>& intervalMatrix, const Matrix<2, 1>& columnMatrix) {
        return IntervalColumnMatrix3d(
            intervalMatrix(0, 0) * columnMatrix(0) +
                intervalMatrix.component(0, 1) * columnMatrix(1),
            intervalMatrix(1, 0) * columnMatrix(0) +
                intervalMatrix.component(1, 1) * columnMatrix(1),
            intervalMatrix(2, 0) * columnMatrix(0) +
                intervalMatrix.component(2, 1) * columnMatrix(1)
        );
    }

    template <>
    inline
    const IntervalMatrix<3, 1>
    operator*(
        const IntervalMatrix<3, 2>& intervalMatrix,
        const IntervalMatrix<2, 1>& intervalColumnMatrix
    ) {
        return IntervalColumnMatrix3d(
            intervalMatrix(0, 0) * intervalColumnMatrix(0) +
                intervalMatrix.component(0, 1) * intervalColumnMatrix(1),
            intervalMatrix(1, 0) * intervalColumnMatrix(0) +
                intervalMatrix.component(1, 1) * intervalColumnMatrix(1),
            intervalMatrix(2, 0) * intervalColumnMatrix(0) +
                intervalMatrix.component(2, 1) * intervalColumnMatrix(1)
        );
    }

    template <>
    inline
    const IntervalMatrix<3, 1>
    operator*(const Matrix<3, 3>& matrix, const IntervalMatrix<3, 1>& intervalColumnMatrix) {
        return IntervalColumnMatrix3d(
            matrix(0, 0) * intervalColumnMatrix(0) + matrix(0, 1) * intervalColumnMatrix(1) +
                matrix(0, 2) * intervalColumnMatrix(2),
            matrix(1, 0) * intervalColumnMatrix(0) + matrix(1, 1) * intervalColumnMatrix(1) +
                matrix(1, 2) * intervalColumnMatrix(2, 0),
            matrix(2, 0) * intervalColumnMatrix(0) + matrix(2, 1) * intervalColumnMatrix(1) +
                matrix(2, 2) * intervalColumnMatrix(2)
        );
    }

    template <>
    inline
    const IntervalMatrix<3, 1>
    operator*(const IntervalMatrix<3, 3>& intervalMatrix, const Matrix<3, 1>& columnMatrix) {
        return IntervalColumnMatrix3d(
            intervalMatrix(0, 0) * columnMatrix(0) + intervalMatrix(0, 1) * columnMatrix(1) +
                intervalMatrix(0, 2) * columnMatrix(2),
            intervalMatrix(1, 0) * columnMatrix(0) + intervalMatrix(1, 1) * columnMatrix(1) +
                intervalMatrix(1, 2) * columnMatrix(2, 0),
            intervalMatrix(2, 0) * columnMatrix(0) + intervalMatrix(2, 1) * columnMatrix(1) +
                intervalMatrix(2, 2) * columnMatrix(2)
        );
    }

    template <>
    inline
    const IntervalMatrix<3, 1>
    operator*(
        const IntervalMatrix<3, 3>& intervalMatrix,
        const IntervalMatrix<3, 1>& intervalColumnMatrix
    ) {
        return IntervalColumnMatrix3d(
            intervalMatrix(0, 0) * intervalColumnMatrix(0) +
                intervalMatrix(0, 1) * intervalColumnMatrix(1) +
                intervalMatrix(0, 2) * intervalColumnMatrix(2),
            intervalMatrix(1, 0) * intervalColumnMatrix(0) +
                intervalMatrix(1, 1) * intervalColumnMatrix(1) +
                intervalMatrix(1, 2) * intervalColumnMatrix(2, 0),
            intervalMatrix(2, 0) * intervalColumnMatrix(0) +
                intervalMatrix(2, 1) * intervalColumnMatrix(1) +
                matrix(2, 2) * intervalColumnMatrix(2)
        );
    }
}
