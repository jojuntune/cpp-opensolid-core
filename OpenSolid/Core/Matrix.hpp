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

#include <OpenSolid/Core/Matrix.definitions.hpp>

#include <cstdlib>

namespace opensolid
{
    template <int iNumRows, int iNumColumns>
    inline
    Matrix<iNumRows, iNumColumns>::Matrix() :
        detail::MatrixBase<double, iNumRows, iNumColumns>() {

        fill(0.0);
    }

    template <int iNumRows, int iNumColumns>
    inline
    Matrix<iNumRows, iNumColumns>::Matrix(const double* sourcePtr) :
        detail::MatrixBase<double, iNumRows, iNumColumns>(sourcePtr) {
    }

    template <int iNumRows, int iNumColumns>
    inline
    const Matrix<iNumRows, iNumColumns>
    Matrix<iNumRows, iNumColumns>::Zero() {
        return Matrix<iNumRows, iNumColumns>();
    }

    template <int iNumRows, int iNumColumns>
    inline
    const Matrix<iNumRows, iNumColumns>
    Matrix<iNumRows, iNumColumns>::Ones() {
        Matrix<iNumRows, iNumColumns> result;
        result.fill(1.0);
        return result;
    }

    template <int iNumRows, int iNumColumns>
    inline
    const Matrix<iNumRows, iNumColumns>
    Matrix<iNumRows, iNumColumns>::Identity() {
        Matrix<iNumRows, iNumColumns> result;
        std::int64_t count = min(iNumRows, iNumColumns);
        for (std::int64_t index = 0; index < count; ++index) {
            result(index, index) = 1.0;
        }
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    Matrix<iNumRows, iNumColumns>::Random() {
        Matrix<iNumRows, iNumColumns> result;
        for (std::int64_t index = 0; index < Size; ++index) {
            result(index) = double(rand()) / RAND_MAX;
        }
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    Matrix<iNumRows, iNumColumns>::OuterProduct(
        const Matrix<iNumRows, 1>& columnMatrix,
        const Matrix<1, iNumColumns>& rowMatrix
    ) {
        Matrix<iNumRows, iNumColumns> result;
        for (std::int64_t columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
            for (std::int64_t rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                result(rowIndex, columnIndex) = columnMatrix(rowIndex, 1) *
                    rowMatrix(1, columnIndex);
            }
        }
        return result;
    }

    inline
    Matrix1d::Matrix() :
        detail::MatrixBase<double, 1, 1>() {

        component(0) = 0.0;
    }

    inline
    Matrix1d::Matrix(const double* sourcePtr) :
        detail::MatrixBase<double, 1, 1>(sourcePtr) {
    }

    inline
    Matrix1d::Matrix(double value) :
        detail::MatrixBase<double, 1, 1>() {

        component(0) = value;
    }

    inline
    const double
    Matrix1d::value() const {
        return component(0);
    }

    inline
    double&
    Matrix1d::value() {
        return component(0);
    }

    inline
    const double
    Matrix1d::determinant() const {
        return value();
    }

    inline
    const Matrix1d
    Matrix1d::inverse() const {
        if (value() == Zero()) {
            assert(false);
            return Matrix1d(0.0);
        }
        return Matrix1d(1.0 / value());
    }

    inline
    const Matrix1d
    Matrix1d::Zero() {
        return Matrix1d();
    }

    inline
    const Matrix1d
    Matrix1d::Ones() {
        Matrix1d result;
        result(0) = 1.0;
        return result;
    }

    inline
    const Matrix1d
    Matrix1d::Identity() {
        Matrix1d result;
        result(0) = 1.0;
        return result;
    }

    inline
    const Matrix1d
    Matrix1d::Random() {
        Matrix1d result;
        result(0) = double(rand()) / RAND_MAX;
        return result;
    }

    inline
    const Matrix1d
    Matrix1d::OuterProduct(const Matrix<1, 1>& columnMatrix, const Matrix<1, 1>& rowMatrix) {
        Matrix1d result;
        result(0) = columnMatrix(0) * rowMatrix(0);
        return result;
    }

    inline
    Matrix2d::Matrix() :
        detail::MatrixBase<double, 2, 2>() {

        fill(0.0);
    }

    inline
    Matrix2d::Matrix(const double* sourcePtr) :
        detail::MatrixBase<double, 2, 2>(sourcePtr) {
    }

    inline
    Matrix2d::Matrix(double a, double b, double c, double d) :
        detail::MatrixBase<double, 2, 2>() {

        component(0) = a;
        component(1) = c;
        component(2) = b;
        component(3) = d;
    }

    inline
    double
    Matrix2d::determinant() const {
        return component(0) * component(3) - component(2) * component(1);
    }

    inline
    const Matrix2d
    Matrix2d::inverse() const {
        double determinant = this->determinant();
        if (determinant == Zero()) {
            assert(false);
            return Matrix2d();
        }
        double reciprocal = 1.0 / determinant;
        return Matrix2d(
            reciprocal * component(3),
            -reciprocal * component(2),
            -reciprocal * component(1),
            reciprocal * component(0)
        );
    }

    inline
    const Matrix2d
    Matrix2d::Zero() {
        return Matrix2d();
    }

    inline
    const Matrix2d
    Matrix2d::Ones() {
        Matrix2d result;
        result.fill(1.0);
        return result;
    }

    inline
    const Matrix2d
    Matrix2d::Identity() {
        Matrix2d result;
        result(0) = 1.0;
        result(3) = 1.0;
        return result;
    }

    inline
    const Matrix2d
    Matrix2d::Random() {
        Matrix2d result;
        result(0) = double(rand()) / RAND_MAX;
        result(1) = double(rand()) / RAND_MAX;
        result(2) = double(rand()) / RAND_MAX;
        result(3) = double(rand()) / RAND_MAX;
        return result;
    }

    inline
    const Matrix2d
    Matrix2d::OuterProduct(const Matrix<2, 1>& columnMatrix, const Matrix<1, 2>& rowMatrix) {
        Matrix2d result;
        result(0, 0) = columnMatrix(0) * rowMatrix(0);
        result(1, 0) = columnMatrix(1) * rowMatrix(0);
        result(0, 1) = columnMatrix(0) * rowMatrix(1);
        result(1, 1) = columnMatrix(1) * rowMatrix(1);
        return result;
    }

    inline
    Matrix3d::Matrix() :
        detail::MatrixBase<double, 3, 3>() {

        fill(0.0);
    }

    inline
    Matrix3d::Matrix(const double* sourcePtr) :
        detail::MatrixBase<double, 3, 3>(sourcePtr) {
    }

    inline
    Matrix3d::Matrix(
        double a11,
        double a12,
        double a13,
        double a21,
        double a22,
        double a23,
        double a31,
        double a32,
        double a33
    ) : detail::MatrixBase<double, 3, 3>() {

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
    const Matrix3d
    Matrix3d::Zero() {
        return Matrix3d();
    }

    inline
    const Matrix3d
    Matrix3d::Ones() {
        Matrix3d result;
        result.fill(1.0);
        return result;
    }

    inline
    const Matrix3d
    Matrix3d::Identity() {
        Matrix3d result;
        result(0) = 1.0;
        result(4) = 1.0;
        result(8) = 1.0;
        return result;
    }

    inline
    const Matrix3d
    Matrix3d::Random() {
        Matrix3d result;
        result(0) = double(rand()) / RAND_MAX;
        result(1) = double(rand()) / RAND_MAX;
        result(2) = double(rand()) / RAND_MAX;
        result(3) = double(rand()) / RAND_MAX;
        result(4) = double(rand()) / RAND_MAX;
        result(5) = double(rand()) / RAND_MAX;
        result(6) = double(rand()) / RAND_MAX;
        result(7) = double(rand()) / RAND_MAX;
        result(8) = double(rand()) / RAND_MAX;
        return result;
    }

    inline
    const Matrix3d
    Matrix3d::OuterProduct(const Matrix<3, 1>& columnMatrix, const Matrix<1, 3>& rowMatrix) {
        Matrix3d result;
        result(0, 0) = columnMatrix(0) * rowMatrix(0);
        result(1, 0) = columnMatrix(1) * rowMatrix(0);
        result(2, 0) = columnMatrix(2) * rowMatrix(0);
        result(0, 1) = columnMatrix(0) * rowMatrix(1);
        result(1, 1) = columnMatrix(1) * rowMatrix(1);
        result(2, 1) = columnMatrix(2) * rowMatrix(1);
        result(0, 2) = columnMatrix(0) * rowMatrix(2);
        result(1, 2) = columnMatrix(1) * rowMatrix(2);
        result(2, 2) = columnMatrix(2) * rowMatrix(2);
        return result;
    }

    inline
    ColumnMatrix2d::Matrix() :
        detail::MatrixBase<double, 2, 1>() {

        component(0) = 0.0;
        component(1) = 0.0;
    }

    inline
    ColumnMatrix2d::Matrix(const double* sourcePtr) :
        detail::MatrixBase<double, 2, 1>(sourcePtr) {
    }

    inline
    ColumnMatrix2d::Matrix(double x, double y) :
        detail::MatrixBase<double, 2, 1>() {

        component(0) = x;
        component(1) = y;
    }

    inline
    const ColumnMatrix2d
    ColumnMatrix2d::Zero() {
        return ColumnMatrix2d();
    }

    inline
    const ColumnMatrix2d
    ColumnMatrix2d::Ones() {
        ColumnMatrix2d result;
        result.fill(1.0);
        return result;
    }

    inline
    const ColumnMatrix2d
    ColumnMatrix2d::Random() {
        ColumMatrix2d result;
        result(0) = double(rand()) / RAND_MAX;
        result(1) = double(rand()) / RAND_MAX;
        return result;
    }

    inline
    ColumnMatrix3d::Matrix() :
        detail::MatrixBase<double, 3, 1>() {

        component(0) = 0.0;
        component(1) = 0.0;
        component(2) = 0.0;
    }

    inline
    ColumnMatrix3d::Matrix(const double* sourcePtr) :
        detail::MatrixBase<double, 3, 1>(sourcePtr) {
    }

    inline
    ColumnMatrix3d::Matrix(double x, double y, double z) :
        detail::MatrixBase<double, 3, 1>() {

        component(0) = x;
        component(1) = y;
        component(2) = z;
    }

    inline
    const ColumnMatrix3d
    ColumnMatrix3d::Zero() {
        return ColumnMatrix3d();
    }

    inline
    const ColumnMatrix3d
    ColumnMatrix3d::Ones() {
        ColumnMatrix3d result;
        result.fill(1.0);
        return result;
    }

    inline
    const ColumnMatrix3d
    ColumnMatrix3d::Random() {
        ColumnMatrix3d result;
        result(0) = double(rand()) / RAND_MAX;
        result(1) = double(rand()) / RAND_MAX;
        result(2) = double(rand()) / RAND_MAX;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator*(double scale, const Matrix<iNumRows, iNumColumns>& matrix) {
        return matrix.map(
            [scale] (double component) {
                return component * scale;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator*(const Matrix<iNumRows, iNumColumns>& matrix, double scale) {
        return matrix.map(
            [scale] (double component) {
                return component * scale;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator/(const Matrix<iNumRows, iNumColumns>& matrix, double divisor) {
        if (divisor == Zero()) {
            assert(false);
            return Matrix<iNumRows, iNumColumns>();
        }
        return (1.0 / divisor) * matrix;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, int iNumColumns>
    operator+(
        const Matrix<iNumRows, iNumColumns>& firstMatrix,
        const Matrix<iNumRows, iNumColumns>& secondMatrix
    ) {
        return firstMatrix.binaryMap(
            secondMatrix,
            [] (double firstComponent, double secondComponent) {
                return firstComponent + secondComponent;
            }
        );
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, int iNumColumns>
    operator-(
        const Matrix<iNumRows, iNumColumns>& firstMatrix,
        const Matrix<iNumRows, iNumColumns>& secondMatrix
    ) {
        return firstMatrix.binaryMap(
            secondMatrix,
            [] (double firstComponent, double secondComponent) {
                return firstComponent - secondComponent;
            }
        );
    }

    template <int iNumRows, int iNumColumns, int iInnerSize>
    const Matrix<iNumRows, int iNumColumns>
    operator*(
        const Matrix<iNumRows, iInnerSize>& firstMatrix,
        const Matrix<iInnerSize, iNumColumns>& secondMatrix
    ) {
        Matrix<iNumRows, iNumColumns> result;
        for (int columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
            for (int rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                double& component = result(rowIndex, columnIndex);
                component = firstMatrix(rowIndex, 0) * secondMatrix(0, columnIndex);
                for (int innerIndex = 1; innerIndex < iInnerSize; ++innerIndex) {
                    component += firstMatrix(rowIndex, innerIndex) *
                        secondMatrix(innerIndex, columnIndex);
                }
            }
        }
        return result;
    }
}
