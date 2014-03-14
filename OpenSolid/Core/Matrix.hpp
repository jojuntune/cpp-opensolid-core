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

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix/MatrixBase.hpp>
#include <OpenSolid/Core/Matrix/Unroll.hpp>
#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    template <class TScalar>
    inline
    Matrix<TScalar, 1, 1>::Matrix() {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 1, 1>::Matrix(const TScalar* sourcePtr) :
        detail::MatrixBase<TScalar, 1, 1>(sourcePtr) {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 1, 1>::Matrix(TScalar value) :
        detail::MatrixBase<TScalar, 1, 1>() {

        this->component(0) = value;
    }

    template <class TScalar>
    inline
    const TScalar
    Matrix<TScalar, 1, 1>::value() const {
        return this->component(0);
    }

    template <class TScalar>
    inline
    TScalar&
    Matrix<TScalar, 1, 1>::value() {
        return this->component(0);
    }

    template <class TScalar>
    inline
    const TScalar
    Matrix<TScalar, 1, 1>::determinant() const {
        return value();
    }

    template <>
    inline
    const Matrix1x1
    Matrix1x1::inverse() const {
        if (value() == opensolid::Zero()) {
            assert(false);
            return Matrix1x1();
        }
        return Matrix1x1(1.0 / value());
    }

    template <>
    inline
    const IntervalMatrix1x1
    IntervalMatrix1x1::inverse() const {
        return IntervalMatrix1x1(1.0 / value());
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 2, 2>::Matrix() {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 2, 2>::Matrix(const TScalar* sourcePtr) :
        detail::MatrixBase<TScalar, 2, 2>(sourcePtr) {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 2, 2>::Matrix(TScalar a00, TScalar a10, TScalar a01, TScalar a11) :
        detail::MatrixBase<TScalar, 2, 2>() {

        this->component(0) = a00;
        this->component(1) = a10;
        this->component(2) = a01;
        this->component(3) = a11;
    }

    template <class TScalar>
    inline
    TScalar
    Matrix<TScalar, 2, 2>::determinant() const {
        return this->component(0) * this->component(3) - this->component(2) * this->component(1);
    }

    template <>
    inline
    const Matrix2x2
    Matrix2x2::inverse() const {
        double determinant = this->determinant();
        if (determinant == opensolid::Zero()) {
            assert(false);
            return Matrix2x2();
        }
        double reciprocal = 1.0 / determinant;
        return Matrix2x2(
            reciprocal * this->component(3),
            -reciprocal * this->component(1),
            -reciprocal * this->component(2),
            reciprocal * this->component(0)
        );
    }

    template <>
    inline
    const IntervalMatrix2x2
    IntervalMatrix2x2::inverse() const {
        Interval determinant = this->determinant();
        Interval reciprocal = 1.0 / determinant;
        return IntervalMatrix2x2(
            reciprocal * this->component(3),
            -reciprocal * this->component(1),
            -reciprocal * this->component(2),
            reciprocal * this->component(0)
        );
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 3, 3>::Matrix() {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 3, 3>::Matrix(const TScalar* sourcePtr) :
        detail::MatrixBase<TScalar, 3, 3>(sourcePtr) {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 3, 3>::Matrix(
        TScalar a00,
        TScalar a10,
        TScalar a20,
        TScalar a01,
        TScalar a11,
        TScalar a21,
        TScalar a02,
        TScalar a12,
        TScalar a22
    ) : detail::MatrixBase<TScalar, 3, 3>() {

        this->component(0) = a00;
        this->component(1) = a10;
        this->component(2) = a20;
        this->component(3) = a01;
        this->component(4) = a11;
        this->component(5) = a21;
        this->component(6) = a02;
        this->component(7) = a12;
        this->component(8) = a22;
    }



    template <class TScalar>
    inline
    Matrix<TScalar, 1, 2>::Matrix() {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 1, 2>::Matrix(const TScalar* sourcePtr) :
        detail::MatrixBase<TScalar, 1, 2>(sourcePtr) {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 1, 2>::Matrix(TScalar x, TScalar y) :
        detail::MatrixBase<TScalar, 1, 2>() {

        this->component(0) = x;
        this->component(1) = y;
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 2, 1>::Matrix() {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 2, 1>::Matrix(const TScalar* sourcePtr) :
        detail::MatrixBase<TScalar, 2, 1>(sourcePtr) {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 2, 1>::Matrix(TScalar x, TScalar y) :
        detail::MatrixBase<TScalar, 2, 1>() {

        this->component(0) = x;
        this->component(1) = y;
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 1, 3>::Matrix() {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 1, 3>::Matrix(const TScalar* sourcePtr) :
        detail::MatrixBase<TScalar, 1, 3>(sourcePtr) {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 1, 3>::Matrix(TScalar x, TScalar y, TScalar z) :
        detail::MatrixBase<TScalar, 1, 3>() {

        this->component(0) = x;
        this->component(1) = y;
        this->component(2) = z;
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 3, 1>::Matrix() {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 3, 1>::Matrix(const TScalar* sourcePtr) :
        detail::MatrixBase<TScalar, 3, 1>(sourcePtr) {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 3, 1>::Matrix(TScalar x, TScalar y, TScalar z) :
        detail::MatrixBase<TScalar, 3, 1>() {

        this->component(0) = x;
        this->component(1) = y;
        this->component(2) = z;
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 2, 3>::Matrix() {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 2, 3>::Matrix(const TScalar* sourcePtr) :
        detail::MatrixBase<TScalar, 2, 3>(sourcePtr) {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 2, 3>::Matrix(
        TScalar a00,
        TScalar a10,
        TScalar a01,
        TScalar a11,
        TScalar a02,
        TScalar a12
    ) : detail::MatrixBase<TScalar, 2, 3>() {

        this->component(0) = a00;
        this->component(1) = a10;
        this->component(2) = a01;
        this->component(3) = a11;
        this->component(4) = a02;
        this->component(5) = a12;
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 3, 2>::Matrix() {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 3, 2>::Matrix(const TScalar* sourcePtr) :
        detail::MatrixBase<TScalar, 3, 2>(sourcePtr) {
    }

    template <class TScalar>
    inline
    Matrix<TScalar, 3, 2>::Matrix(
        TScalar a00,
        TScalar a10,
        TScalar a20,
        TScalar a01,
        TScalar a11,
        TScalar a21
    ) : detail::MatrixBase<TScalar, 3, 2>() {

        this->component(0) = a00;
        this->component(1) = a10;
        this->component(2) = a20;
        this->component(3) = a01;
        this->component(4) = a11;
        this->component(5) = a21;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    operator-(const Matrix<TScalar, iNumRows, iNumColumns>& matrix) {
        return matrix.map(
            [] (TScalar component) {
                return -component;
            }
        );
    }

    template <class TFirstScalar, class TSecondScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<decltype(TFirstScalar() * TSecondScalar()), iNumRows, iNumColumns>
    operator*(TFirstScalar scale, const Matrix<TSecondScalar, iNumRows, iNumColumns>& matrix) {
        return matrix.map(
            [scale] (TSecondScalar component) {
                return scale * component;
            }
        );
    }

    template <class TFirstScalar, class TSecondScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<decltype(TFirstScalar() * TSecondScalar()), iNumRows, iNumColumns>
    operator*(const Matrix<TFirstScalar, iNumRows, iNumColumns>& matrix, TSecondScalar scale) {
        return matrix.map(
            [scale] (TFirstScalar component) {
                return component * scale;
            }
        );
    }

    template <class TFirstScalar, class TSecondScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<decltype(TFirstScalar() / TSecondScalar()), iNumRows, iNumColumns>
    operator/(const Matrix<TFirstScalar, iNumRows, iNumColumns>& matrix, TSecondScalar divisor) {
        return (1.0 / divisor) * matrix;
    }

    template <class TFirstScalar, class TSecondScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<decltype(TFirstScalar() + TSecondScalar()), iNumRows, iNumColumns>
    operator+(
        const Matrix<TFirstScalar, iNumRows, iNumColumns>& firstMatrix,
        const Matrix<TSecondScalar, iNumRows, iNumColumns>& secondMatrix
    ) {
        return firstMatrix.binaryMap(
            secondMatrix,
            [] (TFirstScalar firstComponent, TSecondScalar secondComponent) {
                return firstComponent + secondComponent;
            }
        );
    }

    template <class TFirstScalar, class TSecondScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<decltype(TFirstScalar() - TSecondScalar()), iNumRows, iNumColumns>
    operator-(
        const Matrix<TFirstScalar, iNumRows, iNumColumns>& firstMatrix,
        const Matrix<TSecondScalar, iNumRows, iNumColumns>& secondMatrix
    ) {
        return firstMatrix.binaryMap(
            secondMatrix,
            [] (TFirstScalar firstComponent, TSecondScalar secondComponent) {
                return firstComponent - secondComponent;
            }
        );
    }

    template <
        class TFirstScalar,
        class TSecondScalar,
        int iNumRows,
        int iNumColumns,
        int iInnerSize
    >
    const Matrix<decltype(TFirstScalar() * TSecondScalar()), iNumRows, iNumColumns>
    operator*(
        const Matrix<TFirstScalar, iNumRows, iInnerSize>& firstMatrix,
        const Matrix<TSecondScalar, iInnerSize, iNumColumns>& secondMatrix
    ) {
        typedef decltype(TFirstScalar() * TSecondScalar()) ResultScalarType;
        Matrix<ResultScalarType, iNumRows, iNumColumns> result;
        ResultScalarType* resultDataPtr = result.data();
        const TFirstScalar* rowStart = firstMatrix.data();
        const TSecondScalar* columnStart = secondMatrix.data();
        detail::Unroll<iNumColumns>(
            [&] (std::int64_t columnIndex) {
                detail::Unroll<iNumRows>(
                    [&] (std::int64_t rowIndex) {
                        const TFirstScalar* rowPtr = rowStart;
                        const TSecondScalar* columnPtr = columnStart;
                        *resultDataPtr = (*rowPtr) * (*columnPtr);
                        detail::Unroll<iInnerSize - 1>(
                            [&] (std::int64_t innerIndex) {
                                rowPtr += iNumRows;
                                ++columnPtr;
                                *resultDataPtr += (*rowPtr) * (*columnPtr);
                            }
                        );
                        ++resultDataPtr;
                        ++rowStart;
                    }
                );
                columnStart += iInnerSize;
                rowStart = firstMatrix.data();
            }
        );
        return result;
    }

    template <int iNumRows, int iNumColumns>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<double, iNumRows, iNumColumns>& matrix) {
        stream << "Matrix" << iNumRows << "x" << iNumColumns;
        stream << "(";
        for (std::int64_t index = 0; index < iNumRows * iNumColumns; ++index) {
            stream << matrix.component(index);
            if (index < iNumRows * iNumColumns - 1) {
                stream << ",";
            }
        }
        stream << ")";
        return stream;
    }

    template <int iNumRows, int iNumColumns>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<Interval, iNumRows, iNumColumns>& matrix) {
        stream << "IntervalMatrix" << iNumRows << "x" << iNumColumns;
        stream << "(";
        for (std::int64_t index = 0; index < iNumRows * iNumColumns; ++index) {
            stream << matrix.component(index);
            if (index < iNumRows * iNumColumns - 1) {
                stream << ",";
            }
        }
        stream << ")";
        return stream;
    }
}
