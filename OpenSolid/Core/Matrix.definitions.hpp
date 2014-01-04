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

#if 1

#include <OpenSolid/Core/Matrix/MatrixBase.definitions.hpp>

namespace opensolid
{
    template <int iNumRows, int iNumColumns>
    class Matrix :
        public MatrixBase<iNumRows, iNumColumns>
    {
    public:
        Matrix();
    };

    template <>
    class Matrix<1, 1> :
        public MatrixBase<1, 1>
    {
    public:
        Matrix();

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
    };

    typedef Matrix<1, 1> Matrix1d;

    template <>
    class Matrix<2, 2> :
        public MatrixBase<2, 2>
    {
    public:
        Matrix();

        Matrix(double a, double b, double c, double d);

        double
        determinant() const;

        const Matrix<2, 2>
        inverse() const;
    };

    typedef Matrix<2, 2> Matrix2d;

    template <>
    class Matrix<3, 3> :
        public MatrixBase<3, 3>
    {
    public:
        Matrix();

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
    };

    typedef Matrix<3, 3> Matrix3d;

    template <>
    class Matrix<2, 1> :
        public MatrixBase<2, 1>
    {
    public:
        Matrix();

        Matrix(double x, double y);
    };

    typedef Matrix<2, 1> ColumnMatrix2d;

    template <>
    class Matrix<3, 1> :
        public MatrixBase<3, 1>
    {
    public:
        Matrix();

        Matrix(double x, double y, double z);
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

#else

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct BoundsType<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        typedef Matrix<Interval, iRows, iCols, iOptions, iMaxRows, iMaxCols> Type;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct NumDimensions<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        static const int Value = iRows;
    };

    template <
        class TScalar,
        int iRows,
        int iCols,
        int iOptions,
        int iMaxRows,
        int iMaxCols,
        int iNumResultDimensions
    >
    struct TransformedType<
        Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>,
        iNumResultDimensions
    >
    {
        typedef Matrix<
            TScalar,
            iNumResultDimensions,
            iCols,
            iOptions,
            iNumResultDimensions,
            iMaxCols
        > Type;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct EqualityFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        bool
        operator()(
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& firstMatrix,
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& secondMatrix,
            double precision
        ) const;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct BoundsFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        typedef typename internal::conditional<
            internal::is_same<TScalar, Interval>::value,
            const Matrix<Interval, iRows, iCols, iOptions, iMaxRows, iMaxCols>&,
            const CwiseUnaryOp<
                internal::scalar_cast_op<TScalar, Interval>,
                const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
            >
        >::type CastType;

        CastType
        operator()(
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument
        ) const;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct ScalingFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
        operator()(
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
            double scale
        ) const;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct TranslationFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        template <class TVector>
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>&
        operator()(
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <
        class TScalar,
        int iRows,
        int iCols,
        int iOptions,
        int iMaxRows,
        int iMaxCols,
        int iNumResultDimensions
    >
    struct TransformationFunction<
        Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>,
        iNumResultDimensions
    >
    {
        template <class TMatrix>
        Matrix<TScalar, iNumResultDimensions, iCols, iOptions, iNumResultDimensions, iMaxCols>
        operator()(
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
            const EigenBase<TMatrix>& matrix
        ) const;
    };
}

#endif
