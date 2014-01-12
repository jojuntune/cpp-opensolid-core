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

#include <OpenSolid/Core/Matrix/MatrixBase.definitions.hpp>

namespace opensolid
{
    template <int iNumRows, int iNumColumns>
    class Matrix :
        public detail::MatrixBase<double, iNumRows, iNumColumns>
    {
    public:
        Matrix();

        explicit
        Matrix(const double* sourcePtr);

        static const Matrix<iNumRows, iNumColumns>
        Zero();

        static const Matrix<iNumRows, iNumColumns>
        Ones();

        static const Matrix<iNumRows, iNumColumns>
        Identity();

        static const Matrix<iNumRows, iNumColumns>
        Random();

        static const Matrix<iNumRows, iNumColumns>
        OuterProduct(
            const Matrix<iNumRows, 1>& columnMatrix,
            const Matrix<1, iNumColumns>& rowMatrix
        );
    };

    template <>
    class Matrix<1, 1> :
        public detail::MatrixBase<double, 1, 1>
    {
    public:
        Matrix();

        explicit
        Matrix(const double* sourcePtr);

        explicit
        Matrix(double value);

        const double
        value() const;

        double&
        value();

        const double
        determinant() const;

        const Matrix<1, 1>
        inverse() const;

        static const Matrix<1, 1>
        Zero();

        static const Matrix<1, 1>
        Ones();

        static const Matrix<1, 1>
        Identity();

        static const Matrix<1, 1>
        Random();

        static const Matrix<1, 1>
        OuterProduct(const Matrix<1, 1>& columnMatrix, const Matrix<1, 1>& rowMatrix);
    };

    typedef Matrix<1, 1> Matrix1d;

    template <>
    class Matrix<2, 2> :
        public detail::MatrixBase<double, 2, 2>
    {
    public:
        Matrix();

        explicit
        Matrix(const double* sourcePtr);

        Matrix(double a, double b, double c, double d);

        double
        determinant() const;

        const Matrix<2, 2>
        inverse() const;

        static const Matrix<2, 2>
        Zero();

        static const Matrix<2, 2>
        Ones();

        static const Matrix<2, 2>
        Identity();

        static const Matrix<2, 2>
        Random();

        static const Matrix<2, 2>
        OuterProduct(const Matrix<2, 1>& columnMatrix, const Matrix<1, 2>& rowMatrix);
    };

    typedef Matrix<2, 2> Matrix2d;

    template <>
    class Matrix<3, 3> :
        public detail::MatrixBase<double, 3, 3>
    {
    public:
        Matrix();

        explicit
        Matrix(const double* sourcePtr);

        Matrix(
            double a11,
            double a12,
            double a13,
            double a21,
            double a22,
            double a23,
            double a31,
            double a32,
            double a33
        );

        OPENSOLID_CORE_EXPORT
        const double
        determinant() const;

        OPENSOLID_CORE_EXPORT
        const Matrix<3, 3>
        inverse() const;

        static const Matrix<3, 3>
        Zero();

        static const Matrix<3, 3>
        Ones();

        static const Matrix<3, 3>
        Identity();

        static const Matrix<3, 3>
        Random();

        static const Matrix<3, 3>
        OuterProduct(const Matrix<3, 1>& columnMatrix, const Matrix<1, 3>& rowMatrix);
    };

    typedef Matrix<3, 3> Matrix3d;

    template <>
    class Matrix<2, 1> :
        public detail::MatrixBase<double, 2, 1>
    {
    public:
        Matrix();

        explicit
        Matrix(const double* sourcePtr);

        Matrix(double x, double y);

        static const Matrix<2, 1>
        Zero();

        static const Matrix<2, 1>
        Ones();

        static const Matrix<2, 1>
        Random();
    };

    typedef Matrix<2, 1> ColumnMatrix2d;

    template <>
    class Matrix<3, 1> :
        public detail::MatrixBase<double, 3, 1>
    {
    public:
        Matrix();

        explicit
        Matrix(const double* sourcePtr);

        Matrix(double x, double y, double z);

        static const Matrix<3, 1>
        Zero();

        static const Matrix<3, 1>
        Ones();

        static const Matrix<3, 1>
        Random();
    };

    typedef Matrix<3, 1> ColumnMatrix3d;

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator*(double scale, const Matrix<iNumRows, iNumColumns>& matrix);

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator*(const Matrix<iNumRows, iNumColumns>& matrix, double scale);

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator/(const Matrix<iNumRows, iNumColumns>& matrix, double divisor);

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, int iNumColumns>
    operator+(
        const Matrix<iNumRows, iNumColumns>& firstMatrix,
        const Matrix<iNumRows, iNumColumns>& secondMatrix
    );

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, int iNumColumns>
    operator-(
        const Matrix<iNumRows, iNumColumns>& firstMatrix,
        const Matrix<iNumRows, iNumColumns>& secondMatrix
    );

    template <int iNumRows, int iNumColumns, int iInnerSize>
    const Matrix<iNumRows, int iNumColumns>
    operator*(
        const Matrix<iNumRows, iInnerSize>& firstMatrix,
        const Matrix<iInnerSize, iNumColumns>& secondMatrix
    );
}

#endif
