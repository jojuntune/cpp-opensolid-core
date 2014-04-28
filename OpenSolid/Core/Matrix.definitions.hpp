/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
    template <class TScalar, int iNumRows, int iNumColumns>
    class Matrix :
        public detail::MatrixBase<TScalar, iNumRows, iNumColumns>
    {
    public:
        Matrix();

        Matrix(int size);

        Matrix(int numRows, int numColumns);

        Matrix(const TScalar* sourcePtr);

        Matrix(const TScalar* sourcePtr, int size);

        Matrix(const TScalar* sourcePtr, int numRows, int numColumns);

        template <class TOtherDerived>
        Matrix(const detail::MatrixInterface<TOtherDerived>& other);

        template <class TOtherDerived>
        void
        operator=(const detail::MatrixInterface<TOtherDerived>& other);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Constant(TScalar value);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Constant(int size, TScalar value);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Constant(int numRows, int numColumns, TScalar value);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Zero();

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Zero(int size);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Zero(int numRows, int numColumns);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Ones();

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Ones(int size);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Ones(int numRows, int numColumns);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Identity();

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Identity(int size);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Identity(int numRows, int numColumns);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Random();

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Random(int size);

        static const Matrix<TScalar, iNumRows, iNumColumns>
        Random(int numRows, int numColumns);
    };

    typedef Matrix<double, 1, 1> Matrix1d;
    typedef Matrix<double, 2, 1> ColumnMatrix2d;
    typedef Matrix<double, 3, 1> ColumnMatrix3d;
    typedef Matrix<double, -1, 1> ColumnMatrixXd;

    typedef Matrix<double, 1, 2> RowMatrix2d;
    typedef Matrix<double, 2, 2> Matrix2d;
    typedef Matrix<double, 3, 2> Matrix3x2;
    typedef Matrix<double, -1, 2> MatrixXx2;

    typedef Matrix<double, 1, 3> RowMatrix3d;
    typedef Matrix<double, 2, 3> Matrix2x3;
    typedef Matrix<double, 3, 3> Matrix3d;
    typedef Matrix<double, -1, 3> MatrixXx3;

    typedef Matrix<double, 1, -1> RowMatrixXd;
    typedef Matrix<double, 2, -1> Matrix2xX;
    typedef Matrix<double, 3, -1> Matrix3xX;
    typedef Matrix<double, -1, -1> MatrixXd;

    typedef Matrix<Interval, 1, 1> IntervalMatrix1d;
    typedef Matrix<Interval, 2, 1> IntervalColumnMatrix2d;
    typedef Matrix<Interval, 3, 1> IntervalColumnMatrix3d;
    typedef Matrix<Interval, -1, 1> IntervalColumnMatrixXd;

    typedef Matrix<Interval, 1, 2> IntervalRowMatrix2d;
    typedef Matrix<Interval, 2, 2> IntervalMatrix2d;
    typedef Matrix<Interval, 3, 2> IntervalMatrix3x2;
    typedef Matrix<Interval, -1, 2> IntervalMatrixXx2;

    typedef Matrix<Interval, 1, 3> IntervalRowMatrix3d;
    typedef Matrix<Interval, 2, 3> IntervalMatrix2x3;
    typedef Matrix<Interval, 3, 3> IntervalMatrix3d;
    typedef Matrix<Interval, -1, 3> IntervalMatrixXx3;

    typedef Matrix<Interval, 1, -1> IntervalRowMatrixXd;
    typedef Matrix<Interval, 2, -1> IntervalMatrix2xX;
    typedef Matrix<Interval, 3, -1> IntervalMatrix3xX;
    typedef Matrix<Interval, -1, -1> IntervalMatrixXd;

    template <class TScalar, int iNumRows, int iNumColumns>
    struct MatrixTraits<Matrix<TScalar, iNumRows, iNumColumns>>
    {
        typedef TScalar ScalarType;
        typedef TScalar PlainScalarType;
        static const int NumRows = iNumRows;
        static const int NumColumns = iNumColumns;
        static const int ColumnStride = iNumRows;
    };

    template <class TScalar, int iNumRows, int iNumColumns>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<TScalar, iNumRows, iNumColumns>& matrix);
}
