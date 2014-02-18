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

#include <OpenSolid/Core/IntervalMatrix.declarations.hpp>

#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Matrix/MatrixBase.definitions.hpp>

namespace opensolid
{
    template <int iNumRows, int iNumColumns>
    class IntervalMatrix :
        public detail::MatrixBase<Interval, iNumRows, iNumColumns>
    {
    public:
        IntervalMatrix();

        explicit
        IntervalMatrix(const Matrix<iNumRows, iNumColumns>& matrix);
    };

    template <>
    class IntervalMatrix<1, 1> :
        public detail::MatrixBase<Interval, 1, 1>
    {
    public:
        IntervalMatrix();

        explicit
        IntervalMatrix(Interval value);

        explicit
        IntervalMatrix(const Matrix<1, 1>& matrix);

        const Interval
        value() const;

        Interval&
        value();

        const Interval
        determinant() const;

        const IntervalMatrix<1, 1>
        inverse() const;
    };

    typedef IntervalMatrix<1, 1> IntervalMatrix1d;

    template <>
    class IntervalMatrix<2, 2> :
        public detail::MatrixBase<Interval, 2, 2>
    {
    public:
        IntervalMatrix();

        IntervalMatrix(Interval a00, Interval a10, Interval a01, Interval a11);

        explicit
        IntervalMatrix(const Matrix<2, 2>& matrix);

        const Interval
        determinant() const;

        const IntervalMatrix<2, 2>
        inverse() const;
    };

    typedef IntervalMatrix<2, 2> IntervalMatrix2d;

    template <>
    class IntervalMatrix<3, 3> :
        public detail::MatrixBase<Interval, 3, 3>
    {
    public:
        IntervalMatrix();

        IntervalMatrix(
            Interval a00,
            Interval a10,
            Interval a20,
            Interval a01,
            Interval a11,
            Interval a21,
            Interval a02,
            Interval a12,
            Interval a22
        );

        explicit
        IntervalMatrix(const Matrix<3, 3>& matrix);

        OPENSOLID_CORE_EXPORT
        const Interval
        determinant() const;

        OPENSOLID_CORE_EXPORT
        const IntervalMatrix<3, 3>
        inverse() const;
    };

    typedef IntervalMatrix<3, 3> IntervalMatrix3d;

    template <>
    class IntervalMatrix<2, 1> :
        public detail::MatrixBase<Interval, 2, 1>
    {
    public:
        IntervalMatrix();

        IntervalMatrix(Interval x, Interval y);

        explicit
        IntervalMatrix(const Matrix<2, 1>& columnMatrix);
    };

    typedef IntervalMatrix<2, 1> IntervalColumnMatrix2d;

    template <>
    class IntervalMatrix<3, 1> :
        public detail::MatrixBase<Interval, 3, 1>
    {
    public:
        IntervalMatrix();

        IntervalMatrix(Interval x, Interval y, Interval z);

        explicit
        IntervalMatrix(const Matrix<3, 1>& columnMatrix);
    };

    template <>
    class IntervalMatrix<1, 2> :
        public detail::MatrixBase<Interval, 1, 2>
    {
    public:
        IntervalMatrix();

        IntervalMatrix(Interval x, Interval y);

        explicit
        IntervalMatrix(const Matrix<1, 2>& columnMatrix);
    };

    typedef IntervalMatrix<1, 2> IntervalRowMatrix2d;

    template <>
    class IntervalMatrix<1, 3> :
        public detail::MatrixBase<Interval, 1, 3>
    {
    public:
        IntervalMatrix();

        IntervalMatrix(Interval x, Interval y, Interval z);

        explicit
        IntervalMatrix(const Matrix<1, 3>& columnMatrix);
    };

    typedef Matrix<1, 3> IntervalRowMatrix3d;

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(Interval scale, const Matrix<iNumRows, iNumColumns>& matrix);

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(double scale, const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix);

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(Interval scale, const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix);

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(const Matrix<iNumRows, iNumColumns>& matrix, Interval scale);

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, double scale);

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator*(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, Interval scale);

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator/(const Matrix<iNumRows, iNumColumns>& matrix, Interval divisor);

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator/(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, double divisor);

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, iNumColumns>
    operator/(const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix, Interval divisor);

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator+(
        const Matrix<iNumRows, iNumColumns>& matrix,
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix
    );

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator+(
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix,
        const Matrix<iNumRows, iNumColumns>& matrix
    );

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator+(
        const IntervalMatrix<iNumRows, iNumColumns>& firstIntervalMatrix,
        const IntervalMatrix<iNumRows, iNumColumns>& secondIntervalMatrix
    );

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator-(
        const Matrix<iNumRows, iNumColumns>& matrix,
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix
    );

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator-(
        const IntervalMatrix<iNumRows, iNumColumns>& intervalMatrix,
        const Matrix<iNumRows, iNumColumns>& matrix
    );

    template <int iNumRows, int iNumColumns>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator-(
        const IntervalMatrix<iNumRows, iNumColumns>& firstIntervalMatrix,
        const IntervalMatrix<iNumRows, iNumColumns>& secondIntervalMatrix
    );

    template <int iNumRows, int iNumColumns, int iInnerSize>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator*(
        const Matrix<iNumRows, iInnerSize>& matrix,
        const IntervalMatrix<iInnerSize, iNumColumns>& intervalMatrix
    );

    template <int iNumRows, int iNumColumns, int iInnerSize>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator*(
        const IntervalMatrix<iNumRows, iInnerSize>& intervalMatrix,
        const Matrix<iInnerSize, iNumColumns>& matrix
    );

    template <int iNumRows, int iNumColumns, int iInnerSize>
    const IntervalMatrix<iNumRows, int iNumColumns>
    operator*(
        const IntervalMatrix<iNumRows, iInnerSize>& firstIntervalMatrix,
        const IntervalMatrix<iInnerSize, iNumColumns>& secondIntervalMatrix
    );
}
