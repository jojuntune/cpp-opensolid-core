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
    Matrix2d::Matrix() :
        detail::MatrixBase<double, 2, 2>() {

        fill(0.0);
    }

    inline
    Matrix2d::Matrix(const double* sourcePtr) :
        detail::MatrixBase<double, 2, 2>(sourcePtr) {
    }

    inline
    Matrix2d::Matrix(double a00, double a10, double a01, double a11) :
        detail::MatrixBase<double, 2, 2>() {

        component(0) = a00;
        component(1) = a10;
        component(2) = a01;
        component(3) = a11;
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
        double a00,
        double a10,
        double a20,
        double a01,
        double a11,
        double a21,
        double a02,
        double a12,
        double a22
    ) : detail::MatrixBase<double, 3, 3>() {

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
