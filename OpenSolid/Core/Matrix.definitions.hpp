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
#include <OpenSolid/Core/Matrix/MatrixDimensions.definitions.hpp>
#include <OpenSolid/Core/Matrix/MatrixInterface.definitions.hpp>
#include <OpenSolid/Core/Matrix/MatrixStorage.definitions.hpp>

#include <ostream>

namespace opensolid
{
    template <class TScalar, int iRows, int iCols>
    class Matrix :
        public detail::MatrixInterface<Matrix<TScalar, iRows, iCols>>,
        private detail::MatrixDimensions<iRows, iCols>,
        private detail::MatrixStorage<TScalar, iRows, iCols>
    {
    public:
        Matrix();

        Matrix(int size);

        Matrix(int rows, int cols);

        Matrix(const TScalar* sourcePtr);

        Matrix(const TScalar* sourcePtr, int size);

        Matrix(const TScalar* sourcePtr, int rows, int cols);

        template <class TOtherDerived>
        Matrix(const detail::MatrixInterface<TOtherDerived>& other);

        template <class TOtherDerived>
        void
        operator=(const detail::MatrixInterface<TOtherDerived>& other);

        const TScalar*
        data() const;

        TScalar*
        data();

        int
        rows() const;

        int
        cols() const;

        int
        size() const;

        int
        colStride() const;

        static const Matrix<TScalar, iRows, iCols>
        Constant(TScalar value);

        static const Matrix<TScalar, iRows, iCols>
        Constant(int size, TScalar value);

        static const Matrix<TScalar, iRows, iCols>
        Constant(int rows, int cols, TScalar value);

        static const Matrix<TScalar, iRows, iCols>
        Zero();

        static const Matrix<TScalar, iRows, iCols>
        Zero(int size);

        static const Matrix<TScalar, iRows, iCols>
        Zero(int rows, int cols);

        static const Matrix<TScalar, iRows, iCols>
        Ones();

        static const Matrix<TScalar, iRows, iCols>
        Ones(int size);

        static const Matrix<TScalar, iRows, iCols>
        Ones(int rows, int cols);

        static const Matrix<TScalar, iRows, iCols>
        Identity();

        static const Matrix<TScalar, iRows, iCols>
        Identity(int size);

        static const Matrix<TScalar, iRows, iCols>
        Identity(int rows, int cols);

        static const Matrix<TScalar, iRows, iCols>
        Random();

        static const Matrix<TScalar, iRows, iCols>
        Random(int size);

        static const Matrix<TScalar, iRows, iCols>
        Random(int rows, int cols);
    };

    typedef Matrix<double, 1, 1> Matrix1x1;
    typedef Matrix<double, 2, 1> ColMatrix2x1;
    typedef Matrix<double, 3, 1> ColMatrix3x1;
    typedef Matrix<double, -1, 1> ColMatrixXx1;

    typedef Matrix<double, 1, 2> RowMatrix1x2;
    typedef Matrix<double, 2, 2> Matrix2x2;
    typedef Matrix<double, 3, 2> Matrix3x2;
    typedef Matrix<double, -1, 2> MatrixXx2;

    typedef Matrix<double, 1, 3> RowMatrix1x3;
    typedef Matrix<double, 2, 3> Matrix2x3;
    typedef Matrix<double, 3, 3> Matrix3x3;
    typedef Matrix<double, -1, 3> MatrixXx3;

    typedef Matrix<double, 1, -1> RowMatrix1xX;
    typedef Matrix<double, 2, -1> Matrix2xX;
    typedef Matrix<double, 3, -1> Matrix3xX;
    typedef Matrix<double, -1, -1> MatrixXxX;

    typedef Matrix<Interval, 1, 1> IntervalMatrix1x1;
    typedef Matrix<Interval, 2, 1> IntervalColMatrix2x1;
    typedef Matrix<Interval, 3, 1> IntervalColMatrix3x1;
    typedef Matrix<Interval, -1, 1> IntervalColMatrixXx1;

    typedef Matrix<Interval, 1, 2> IntervalRowMatrix1x2;
    typedef Matrix<Interval, 2, 2> IntervalMatrix2x2;
    typedef Matrix<Interval, 3, 2> IntervalMatrix3x2;
    typedef Matrix<Interval, -1, 2> IntervalMatrixXx2;

    typedef Matrix<Interval, 1, 3> IntervalRowMatrix1x3;
    typedef Matrix<Interval, 2, 3> IntervalMatrix2x3;
    typedef Matrix<Interval, 3, 3> IntervalMatrix3x3;
    typedef Matrix<Interval, -1, 3> IntervalMatrixXx3;

    typedef Matrix<Interval, 1, -1> IntervalRowMatrix1xX;
    typedef Matrix<Interval, 2, -1> IntervalMatrix2xX;
    typedef Matrix<Interval, 3, -1> IntervalMatrix3xX;
    typedef Matrix<Interval, -1, -1> IntervalMatrixXxX;

    template <class TScalar, int iRows, int iCols>
    struct MatrixTraits<Matrix<TScalar, iRows, iCols>>
    {
        typedef TScalar ScalarType;
        static const int Rows = iRows;
        static const int Cols = iCols;
        static const int ColStride = iRows;
    };

    template <class TScalar, int iRows, int iCols>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<TScalar, iRows, iCols>& matrix);
}
