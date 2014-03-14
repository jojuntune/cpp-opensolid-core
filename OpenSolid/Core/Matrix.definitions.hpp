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

#include <OpenSolid/Core/Matrix.declarations.hpp>

#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Matrix/MatrixBase.definitions.hpp>

#include <ostream>

namespace opensolid
{
    template <class TScalar>
    class Matrix<TScalar, 1, 1> :
        public detail::MatrixBase<TScalar, 1, 1>
    {
    public:
        Matrix();

        explicit
        Matrix(TScalar value);

        explicit
        Matrix(const TScalar* sourcePtr);

        const TScalar
        value() const;

        TScalar&
        value();

        const TScalar
        determinant() const;

        const Matrix<TScalar, 1, 1>
        inverse() const;
    };

    typedef Matrix<double, 1, 1> Matrix1x1;
    typedef Matrix<Interval, 1, 1> IntervalMatrix1x1;

    template <class TScalar>
    class Matrix<TScalar, 2, 2> :
        public detail::MatrixBase<TScalar, 2, 2>
    {
    public:
        Matrix();

        Matrix(TScalar a00, TScalar a10, TScalar a01, TScalar a11);

        explicit
        Matrix(const TScalar* sourcePtr);

        TScalar
        determinant() const;

        const Matrix<TScalar, 2, 2>
        inverse() const;
    };

    typedef Matrix<double, 2, 2> Matrix2x2;
    typedef Matrix<Interval, 2, 2> IntervalMatrix2x2;

    template <class TScalar>
    class Matrix<TScalar, 3, 3> :
        public detail::MatrixBase<TScalar, 3, 3>
    {
    public:
        Matrix();

        Matrix(
            TScalar a00,
            TScalar a10,
            TScalar a20,
            TScalar a01,
            TScalar a11,
            TScalar a21,
            TScalar a02,
            TScalar a12,
            TScalar a22
        );

        explicit
        Matrix(const TScalar* sourcePtr);

        OPENSOLID_CORE_EXPORT
        TScalar
        determinant() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<TScalar, 3, 3>
        inverse() const;
    };

    typedef Matrix<double, 3, 3> Matrix3x3;
    typedef Matrix<Interval, 3, 3> IntervalMatrix3x3;

    template <class TScalar>
    class Matrix<TScalar, 1, 2> :
        public detail::MatrixBase<TScalar, 1, 2>
    {
    public:
        Matrix();

        Matrix(TScalar x, TScalar y);

        explicit
        Matrix(const TScalar* sourcePtr);
    };

    typedef Matrix<double, 1, 2> Matrix1x2;
    typedef Matrix<Interval, 1, 2> IntervalMatrix1x2;

    template <class TScalar>
    class Matrix<TScalar, 2, 1> :
        public detail::MatrixBase<TScalar, 2, 1>
    {
    public:
        Matrix();

        Matrix(TScalar x, TScalar y);

        explicit
        Matrix(const TScalar* sourcePtr);
    };

    typedef Matrix<double, 2, 1> Matrix2x1;
    typedef Matrix<Interval, 2, 1> IntervalMatrix2x1;

    template <class TScalar>
    class Matrix<TScalar, 1, 3> :
        public detail::MatrixBase<TScalar, 1, 3>
    {
    public:
        Matrix();

        Matrix(TScalar x, TScalar y, TScalar z);

        explicit
        Matrix(const TScalar* sourcePtr);
    };

    typedef Matrix<double, 1, 3> Matrix1x3;
    typedef Matrix<Interval, 1, 3> IntervalMatrix1x3;

    template <class TScalar>
    class Matrix<TScalar, 3, 1> :
        public detail::MatrixBase<TScalar, 3, 1>
    {
    public:
        Matrix();

        Matrix(TScalar x, TScalar y, TScalar z);

        explicit
        Matrix(const TScalar* sourcePtr);
    };

    typedef Matrix<double, 3, 1> Matrix3x1;
    typedef Matrix<Interval, 3, 1> IntervalMatrix3x1;

    template <class TScalar>
    class Matrix<TScalar, 2, 3> :
        public detail::MatrixBase<TScalar, 2, 3>
    {
    public:
        Matrix();

        Matrix(
            TScalar a00,
            TScalar a10,
            TScalar a01,
            TScalar a11,
            TScalar a02,
            TScalar a12
        );

        explicit
        Matrix(const TScalar* sourcePtr);
    };

    typedef Matrix<double, 2, 3> Matrix2x3;
    typedef Matrix<Interval, 2, 3> IntervalMatrix2x3;

    template <class TScalar>
    class Matrix<TScalar, 3, 2> :
        public detail::MatrixBase<TScalar, 3, 2>
    {
    public:
        Matrix();

        Matrix(
            TScalar a00,
            TScalar a10,
            TScalar a20,
            TScalar a01,
            TScalar a11,
            TScalar a21
        );

        explicit
        Matrix(const TScalar* sourcePtr);
    };

    typedef Matrix<double, 3, 2> Matrix3x2;
    typedef Matrix<Interval, 3, 2> IntervalMatrix3x2;

    template <class TScalar, int iNumRows, int iNumColumns>
    const Matrix<TScalar, iNumRows, iNumColumns>
    operator-(const Matrix<TScalar, iNumRows, iNumColumns>& matrix);

    template <class TFirstScalar, class TSecondScalar, int iNumRows, int iNumColumns>
    const Matrix<decltype(TFirstScalar() * TSecondScalar()), iNumRows, iNumColumns>
    operator*(TFirstScalar scale, const Matrix<TSecondScalar, iNumRows, iNumColumns>& matrix);

    template <class TFirstScalar, class TSecondScalar, int iNumRows, int iNumColumns>
    const Matrix<decltype(TFirstScalar() * TSecondScalar()), iNumRows, iNumColumns>
    operator*(const Matrix<TFirstScalar, iNumRows, iNumColumns>& matrix, TSecondScalar scale);

    template <class TFirstScalar, class TSecondScalar, int iNumRows, int iNumColumns>
    const Matrix<decltype(TFirstScalar() / TSecondScalar()), iNumRows, iNumColumns>
    operator/(const Matrix<TFirstScalar, iNumRows, iNumColumns>& matrix, TSecondScalar divisor);

    template <class TFirstScalar, class TSecondScalar, int iNumRows, int iNumColumns>
    const Matrix<decltype(TFirstScalar() + TSecondScalar()), iNumRows, iNumColumns>
    operator+(
        const Matrix<TFirstScalar, iNumRows, iNumColumns>& firstMatrix,
        const Matrix<TSecondScalar, iNumRows, iNumColumns>& secondMatrix
    );

    template <class TFirstScalar, class TSecondScalar, int iNumRows, int iNumColumns>
    const Matrix<decltype(TFirstScalar() - TSecondScalar()), iNumRows, iNumColumns>
    operator-(
        const Matrix<TFirstScalar, iNumRows, iNumColumns>& firstMatrix,
        const Matrix<TSecondScalar, iNumRows, iNumColumns>& secondMatrix
    );

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
    );

    template <int iNumRows, int iNumColumns>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<double, iNumRows, iNumColumns>& matrix);

    template <int iNumRows, int iNumColumns>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<Interval, iNumRows, iNumColumns>& matrix);
}
