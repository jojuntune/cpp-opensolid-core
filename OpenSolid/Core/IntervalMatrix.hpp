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
        detail::MatrixBase<Interval, iNumRows, iNumColumns>() {
    }

    inline
    IntervalMatrix1d::IntervalMatrix() :
        detail::MatrixBase<Interval, 1, 1>() {
    }

    inline
    IntervalMatrix1d::Matrix(Interval value) :
        detail::MatrixBase<Interval, 1, 1>() {

        component(0) = value;
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
        detail::MatrixBase<Interval, 2, 2>() {
    }

    inline
    IntervalMatrix2d::IntervalMatrix(Interval a00, Interval a10, Interval a01, Interval a11) :
        detail::MatrixBase<Interval, 2, 2>() {

        component(0) = a00;
        component(1) = a10;
        component(2) = a01;
        component(3) = a11;
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
        detail::MatrixBase<Interval, 3, 3>() {
    }

    inline
    IntervalMatrix3d::IntervalMatrix(
        Interval a00,
        Interval a10,
        Interval a20,
        Interval a01,
        Interval a11,
        Interval a21,
        Interval a02,
        Interval a12,
        Interval a22
    ) : detail::MatrixBase<Interval, 3, 3>() {

        component(0) = a00;
        component(1) = a10;
        component(2) = a20;
        component(3) = a01;
        component(4) = a11;
        component(5) = a21;
        component(6) = a02;
        component(7) = a12;
        component(8) = a22;
    }

    inline
    IntervalColumnMatrix2d::IntervalMatrix() :
        detail::MatrixBase<Interval, 2, 1>() {
    }

    inline
    IntervalColumnMatrix2d::IntervalMatrix(Interval x, Interval y) :
        detail::MatrixBase<Interval, 2, 1>() {

        component(0) = x;
        component(1) = y;
    }

    inline
    IntervalColumnMatrix3d::Matrix() :
        detail::MatrixBase<Interval, 3, 1>() {
    }

    inline
    IntervalColumnMatrix3d::Matrix(Interval x, Interval y, Interval z) :
        detail::MatrixBase<Interval, 3, 1>() {

        component(0) = x;
        component(1) = y;
        component(2) = z;
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(Interval scale, const Matrix<iNumRows, iNumColumns>& matrix) {
        return matrix.map(
            [scale] (double component) {
                return scale * component;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(double scale, const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix) {
        return intervalMatrix.map(
            [scale] (Interval component) {
                return scale * component;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator*(Interval scale, const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix) {
        return intervalMatrix.map(
            [scale] (Interval component) {
                return scale * component;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(const Matrix<iNumRows, iNumColumns>& matrix, Interval scale) {
        return matrix.map(
            [scale] (double component) {
                return scale * component;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, double scale) {
        return intervalMatrix.map(
            [scale] (Interval component) {
                return scale * component;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator*(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, Interval scale) {
        return intervalMatrix.map(
            [scale] (Interval component) {
                return scale * component;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator/(const Matrix<iNumRows, iNumColumns>& matrix, Interval divisor) {
        return matrix * (1.0 / divisor);
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator/(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, double divisor) {
        if (divisor == Zero()) {
            IntervalMatrix<iNumRows, iNumColumns> result;
            result.fill(Interval::Whole());
            return result;
        } else {
            return intervalMatrix * (1.0 / divisor);
        }
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator/(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, Interval divisor) {
        return intervalMatrix * (1.0 / divisor);
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator+(
        const Matrix<iNumRows, iNumColumns>& matrix,
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix
    ) {
        return matrix.binaryMap(
            intervalMatrix,
            [] (double firstValue, Interval secondValue) {
                return firstValue + secondValue;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator+(
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix,
        const Matrix<iNumRows, iNumColumns>& matrix
    ) {
        return intervalMatrix.binaryMap(
            matrix,
            [] (Interval firstValue, double secondValue) {
                return firstValue + secondValue;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator+(
        const IntervalMatrix<iNumRows, iNumColumns>& firstIntervalMatrix,
        const IntervalMatrix<iNumRows, iNumColumns>& secondIntervalMatrix
    ) {
        return firstIntervalMatrix.binaryMap(
            secondIntervalMatrix,
            [] (Interval firstValue, Interval secondValue) {
                return firstValue + secondValue;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator-(
        const Matrix<iNumRows, iNumColumns>& matrix,
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix
    ) {
        return matrix.binaryMap(
            intervalMatrix,
            [] (double firstValue, Interval secondValue) {
                return firstValue - secondValue;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator-(
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix,
        const Matrix<iNumRows, iNumColumns>& matrix
    ) {
        return intervalMatrix.binaryMap(
            matrix,
            [] (Interval firstValue, double secondValue) {
                return firstValue - secondValue;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator-(
        const Matrix<iNumRows, iNumColumns>& firstIntervalMatrix,
        const Matrix<iNumRows, iNumColumns>& secondIntervalMatrix
    ) {
        return firstIntervalMatrix.binaryMap(
            secondIntervalMatrix,
            [] (Interval firstValue, Interval secondValue) {
                return firstValue - secondValue;
            }
        );
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
        const IntervalMatrix<iNumRows, iInnerSize>& firstIntervalMatrix,
        const IntervalMatrix<iInnerSize, iNumColumns>& secondIntervalMatrix
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
}
