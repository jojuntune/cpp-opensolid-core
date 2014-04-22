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

#include <OpenSolid/Core/Matrix/MatrixInterface.declarations.hpp>

#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/MatrixView.declarations.hpp>

#include <type_traits>

namespace opensolid
{
    namespace detail
    {
        template <class TDerived>
        class MatrixInterface
        {
        private:
            typedef typename MatrixTraits<TDerived>::ScalarType ScalarType;
            typedef typename MatrixTraits<TDerived>::PlainScalarType PlainScalarType;
            static const int NumRows = MatrixTraits<TDerived>::NumRows;
            static const int NumColumns = MatrixTraits<TDerived>::NumColumns;
            static const int ColumnStride = MatrixTraits<TDerived>::ColumnStride;

            TDerived&
            derived();

            const TDerived&
            derived() const;

            template <class TOtherDerived> friend class MatrixInterface;
        public:
            const typename MatrixTraits<TDerived>::ScalarType*
            data() const;

            typename MatrixTraits<TDerived>::ScalarType*
            data();

            int
            numRows() const;

            int
            numColumns() const;

            int
            size() const;

            int
            columnStride() const;

            typename MatrixTraits<TDerived>::PlainScalarType
            coeff(int index) const;

            typename MatrixTraits<TDerived>::ScalarType&
            coeff(int index);

            typename MatrixTraits<TDerived>::PlainScalarType
            coeff(int rowIndex, int columnIndex) const;

            typename MatrixTraits<TDerived>::ScalarType&
            coeff(int rowIndex, int columnIndex);

            typename MatrixTraits<TDerived>::PlainScalarType
            operator()(int index) const;

            typename MatrixTraits<TDerived>::ScalarType&
            operator()(int index);

            typename MatrixTraits<TDerived>::PlainScalarType
            operator()(int rowIndex, int columnIndex) const;

            typename MatrixTraits<TDerived>::ScalarType&
            operator()(int rowIndex, int columnIndex);

            typename MatrixTraits<TDerived>::PlainScalarType
            value() const;

            typename MatrixTraits<TDerived>::ScalarType&
            value();

            template <class TOtherDerived>
            void
            operator=(const MatrixInterface<TOtherDerived>& other);

            const MatrixView<
                const typename MatrixTraits<TDerived>::PlainScalarType,
                1,
                MatrixTraits<TDerived>::NumColumns,
                MatrixTraits<TDerived>::ColumnStride
            >
            row(int rowIndex) const;

            MatrixView<
                typename MatrixTraits<TDerived>::ScalarType,
                1,
                MatrixTraits<TDerived>::NumColumns,
                MatrixTraits<TDerived>::ColumnStride
            >
            row(int rowIndex);

            const MatrixView<
                const typename MatrixTraits<TDerived>::PlainScalarType,
                MatrixTraits<TDerived>::NumRows,
                1,
                MatrixTraits<TDerived>::ColumnStride
            >
            column(int columnIndex) const;

            MatrixView<
                typename MatrixTraits<TDerived>::ScalarType,
                MatrixTraits<TDerived>::NumRows,
                1,
                MatrixTraits<TDerived>::ColumnStride
            >
            column(int columnIndex);

            template <int iBlockRows, int iBlockCols>
            const MatrixView<
                const typename MatrixTraits<TDerived>::PlainScalarType,
                iBlockRows,
                iBlockCols,
                MatrixTraits<TDerived>::ColumnStride
            >
            block(int startRow, int startCol) const;

            template <int iBlockRows, int iBlockCols>
            MatrixView<
                typename MatrixTraits<TDerived>::ScalarType,
                iBlockRows,
                iBlockCols,
                MatrixTraits<TDerived>::ColumnStride
            >
            block(int startRow, int startCol);

            const MatrixView<
                const typename MatrixTraits<TDerived>::PlainScalarType,
                -1,
                -1,
                MatrixTraits<TDerived>::ColumnStride
            >
            block(int startRow, int startCol, int blockRows, int blockCols) const;

            MatrixView<
                typename MatrixTraits<TDerived>::ScalarType,
                -1,
                -1,
                MatrixTraits<TDerived>::ColumnStride
            >
            block(int startRow, int startCol, int blockRows, int blockCols);

            const Matrix<
                typename MatrixTraits<TDerived>::PlainScalarType,
                MatrixTraits<TDerived>::NumColumns,
                MatrixTraits<TDerived>::NumRows
            >
            transpose() const;

            typename MatrixTraits<TDerived>::PlainScalarType
            determinant() const;

            const Matrix<
                typename MatrixTraits<TDerived>::PlainScalarType,
                MatrixTraits<TDerived>::NumColumns,
                MatrixTraits<TDerived>::NumRows
            >
            inverse() const;

            template <class TUnaryFunction>
            const typename MappedMatrixType<TUnaryFunction, TDerived>::Type
            map(TUnaryFunction unaryFunction) const;

            template <class TUnaryFunction, class TResultDerived>
            void
            map(TUnaryFunction unaryFunction, MatrixInterface<TResultDerived>& result) const;

            template <class TBinaryFunction, class TOtherDerived>
            const typename PairwiseMappedMatrixType<TBinaryFunction, TDerived, TOtherDerived>::Type
            binaryMap(
                const MatrixInterface<TOtherDerived>& other,
                TBinaryFunction binaryFunction
            ) const;

            template <class TBinaryFunction, class TOtherDerived, class TResultDerived>
            void
            binaryMap(
                const MatrixInterface<TOtherDerived>& other,
                TBinaryFunction binaryFunction,
                MatrixInterface<TResultDerived>& result
            ) const;

            template <class TValue, class TFunction>
            const TValue
            fold(TValue initialValue, TFunction function) const;

            template <class TOtherDerived, class TValue, class TFunction>
            const TValue
            binaryFold(
                const MatrixInterface<TOtherDerived>& other,
                TValue initialValue,
                TFunction function
            ) const;

            template <class TFunction>
            typename MatrixTraits<TDerived>::PlainScalarType
            reduce(TFunction function) const;

            template <class TUnaryPredicate>
            bool
            any(TUnaryPredicate unaryPredicate) const;

            template <class TBinaryPredicate, class TOtherDerived>
            bool
            binaryAny(
                const MatrixInterface<TOtherDerived>& other,
                TBinaryPredicate binaryPredicate
            ) const;

            template <class TUnaryPredicate>
            bool
            all(TUnaryPredicate unaryPredicate) const;

            template <class TBinaryPredicate, class TOtherDerived>
            bool
            binaryAll(
                const MatrixInterface<TOtherDerived>& other,
                TBinaryPredicate binaryPredicate
            ) const;

            bool
            isConstant(double value, double precision = 1e-12) const;

            bool
            isZero(double precision = 1e-12) const;

            bool
            isOnes(double precision = 1e-12) const;

            bool
            isIdentity(double precision = 1e-12) const;

            const Matrix<
                double,
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumColumns
            >
            cwiseLowerBound() const;

            const Matrix<
                double,
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumColumns
            >
            cwiseUpperBound() const;

            const Matrix<
                double,
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumColumns
            >
            cwiseWidth() const;

            const Matrix<
                double,
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumColumns
            >
            cwiseMedian() const;

            const Matrix<
                typename MatrixTraits<TDerived>::PlainScalarType,
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumColumns
            >
            cwiseSquared() const;

            template <class TOtherDerived>
            const Matrix<
                typename CommonScalar<TDerived, TOtherDerived>::Type,
                CommonRows<TDerived, TOtherDerived>::Value,
                CommonCols<TDerived, TOtherDerived>::Value
            >
            cwiseProduct(const MatrixInterface<TOtherDerived>& other) const;

            template <class TOtherDerived>
            const Matrix<
                typename CommonScalar<TDerived, TOtherDerived>::Type,
                CommonRows<TDerived, TOtherDerived>::Value,
                CommonCols<TDerived, TOtherDerived>::Value
            >
            cwiseQuotient(const MatrixInterface<TOtherDerived>& other) const;

            template <class TOtherDerived>
            const Matrix<
                Interval,
                CommonRows<TDerived, TOtherDerived>::Value,
                CommonCols<TDerived, TOtherDerived>::Value
            >
            cwiseHull(const MatrixInterface<TOtherDerived>& other) const;

            template <class TOtherDerived>
            const Matrix<
                Interval,
                CommonRows<TDerived, TOtherDerived>::Value,
                CommonCols<TDerived, TOtherDerived>::Value
            >
            cwiseIntersection(const MatrixInterface<TOtherDerived>& other) const;

            typename MatrixTraits<TDerived>::PlainScalarType
            sum() const;

            typename MatrixTraits<TDerived>::PlainScalarType
            prod() const;

            template <class TOtherDerived>
            bool
            operator==(const MatrixInterface<TOtherDerived>& other) const;

            template <class TOtherDerived>
            bool
            operator!=(const MatrixInterface<TOtherDerived>& other) const;

            template <class TOtherScalar>
            void
            operator*=(TOtherScalar scale);

            template <class TOtherScalar>
            void
            operator/=(TOtherScalar divisor);

            template <class TOtherDerived>
            void
            operator+=(const MatrixInterface<TOtherDerived>& other);

            template <class TOtherDerived>
            void
            operator-=(const MatrixInterface<TOtherDerived>& other);

            void
            setConstant(typename MatrixTraits<TDerived>::ScalarType value);

            void
            setZero();

            void
            setOnes();

            void
            setIdentity();

            void
            setRandom();
        };

        template <class TUnaryFunction, class TScalar>
        struct MappedScalarType
        {
            typedef typename std::decay<
                typename std::result_of<TUnaryFunction(TScalar)>::type
            >::type Type;
        };

        template <class TBinaryFunction, class TFirstScalar, class TSecondScalar>
        struct PairwiseMappedScalarType
        {
            typedef typename std::decay<
                typename std::result_of<TBinaryFunction(TFirstScalar, TSecondScalar)>::type
            >::type Type;
        };

        template <class TUnaryFunction, class TMatrix>
        struct MappedMatrixType
        {
            typedef Matrix<
                typename MappedScalarType<
                    TUnaryFunction,
                    typename MatrixTraits<TMatrix>::ScalarType
                >::Type,
                MatrixTraits<TMatrix>::NumRows,
                MatrixTraits<TMatrix>::NumColumns
            > Type;
        };

        template < class TBinaryFunction, class TFirstMatrix, class TSecondMatrix>
        struct PairwiseMappedMatrixType
        {
            typedef Matrix<
                typename PairwiseMappedScalarType<
                    TBinaryFunction,
                    typename MatrixTraits<TFirstMatrix>::ScalarType,
                    typename MatrixTraits<TSecondMatrix>::ScalarType
                >::Type,
                CommonRows<TFirstMatrix, TSecondMatrix>::Value,
                CommonCols<TFirstMatrix, TSecondMatrix>::Value
            > Type;
        };


        template <int iFirstSize, int iSecondSize>
        struct CheckCompatibleSizes
        {
            static_assert(
                iFirstSize == iSecondSize || iFirstSize == -1 || iSecondSize == -1,
                "Incompatible static matrix sizes"
            );

            CheckCompatibleSizes();

            CheckCompatibleSizes(int firstSize, int secondSize);
        };

        template <int iFirstRows, int iSecondRows>
        struct CheckCompatibleRows :
            public CheckCompatibleSizes<iFirstRows, iSecondRows>
        {
            CheckCompatibleRows();

            CheckCompatibleRows(int firstRows, int secondRows);
        };

        template <int iFirstCols, int iSecondCols>
        struct CheckCompatibleCols :
            public CheckCompatibleSizes<iFirstCols, iSecondCols>
        {
            CheckCompatibleCols();

            CheckCompatibleCols(int firstCols, int secondCols);
        };

        template <class TFirstMatrix, class TSecondMatrix>
        struct CheckCompatibleMatrices :
            public CheckCompatibleRows<
                MatrixTraits<TFirstMatrix>::NumRows,
                MatrixTraits<TSecondMatrix>::NumRows
            >,
            public CheckCompatibleCols<
                MatrixTraits<TFirstMatrix>::NumColumns,
                MatrixTraits<TSecondMatrix>::NumColumns
            >
        {
            CheckCompatibleMatrices();

            CheckCompatibleMatrices(
                const TFirstMatrix& firstMatrix,
                const TSecondMatrix& secondMatrix
            );
        };

        template <int iFirstSize, int iSecondSize>
        struct CommonSize :
            public CheckCompatibleSizes<iFirstSize, iSecondSize>
        {
            static const int Value = (iFirstSize != -1) ? iFirstSize : iSecondSize;
        };

        template <class TFirstMatrix, class TSecondMatrix>
        struct CommonRows
        {
            static const int Value = CommonSize<
                MatrixTraits<TFirstMatrix>::NumRows,
                MatrixTraits<TSecondMatrix>::NumRows
            >::Value;
        };

        template <class TFirstMatrix, class TSecondMatrix>
        struct CommonCols
        {
            static const int Value = CommonSize<
                MatrixTraits<TFirstMatrix>::NumColumns,
                MatrixTraits<TSecondMatrix>::NumColumns
            >::Value;
        };

        template <>
        struct CommonScalar<double, double>
        {
            typedef double Type;
        };

        template <>
        struct CommonScalar<const double, double>
        {
            typedef double Type;
        };

        template <>
        struct CommonScalar<double, const double>
        {
            typedef double Type;
        };

        template <>
        struct CommonScalar<const double, const double>
        {
            typedef double Type;
        };

        template <>
        struct CommonScalar<double, Interval>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<const double, Interval>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<double, const Interval>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<const double, const Interval>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<Interval, double>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<const Interval, double>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<Interval, const double>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<const Interval, const double>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<Interval, Interval>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<const Interval, Interval>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<Interval, const Interval>
        {
            typedef Interval Type;
        };

        template <>
        struct CommonScalar<const Interval, const Interval>
        {
            typedef Interval Type;
        };

        template <class TSecondMatrix>
        struct CommonScalar<double, TSecondMatrix>
        {
            typedef typename MatrixTraits<TSecondMatrix>::ScalarType Type;
        };

        template <class TSecondMatrix>
        struct CommonScalar<const double, TSecondMatrix>
        {
            typedef typename MatrixTraits<TSecondMatrix>::ScalarType Type;
        };

        template <class TFirstMatrix>
        struct CommonScalar<TFirstMatrix, double>
        {
            typedef typename MatrixTraits<TFirstMatrix>::ScalarType Type;
        };

        template <class TFirstMatrix>
        struct CommonScalar<TFirstMatrix, const double>
        {
            typedef typename MatrixTraits<TFirstMatrix>::ScalarType Type;
        };

        template <class TSecondMatrix>
        struct CommonScalar<Interval, TSecondMatrix>
        {
            typedef Interval Type;
        };

        template <class TSecondMatrix>
        struct CommonScalar<const Interval, TSecondMatrix>
        {
            typedef Interval Type;
        };

        template <class TFirstMatrix>
        struct CommonScalar<TFirstMatrix, Interval>
        {
            typedef Interval Type;
        };

        template <class TFirstMatrix>
        struct CommonScalar<TFirstMatrix, const Interval>
        {
            typedef Interval Type;
        };

        template <class TFirstMatrix, class TSecondMatrix>
        struct CommonScalar
        {
            typedef typename CommonScalar<
                typename MatrixTraits<TFirstMatrix>::ScalarType,
                typename MatrixTraits<TSecondMatrix>::ScalarType
            >::Type Type;
        };

        template <class TDerived>
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator-(const MatrixInterface<TDerived>& matrix);

        template <class TDerived>
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator*(double scale, const MatrixInterface<TDerived>& matrix);

        template <class TDerived>
        const Matrix<
            Interval,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator*(Interval scale, const MatrixInterface<TDerived>& matrix);

        template <class TDerived>
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator*(const MatrixInterface<TDerived>& matrix, double scale);

        template <class TDerived>
        const Matrix<
            Interval,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator*(const MatrixInterface<TDerived>& matrix, Interval scale);

        template <class TDerived>
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator/(const MatrixInterface<TDerived>& matrix, double divisor);

        template <class TDerived>
        const Matrix<
            Interval,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator/(const MatrixInterface<TDerived>& matrix, Interval divisor);

        template <class TFirstDerived, class TSecondDerived>
        const Matrix<
            typename CommonScalar<TFirstDerived, TSecondDerived>::Type,
            CommonRows<TFirstDerived, TSecondDerived>::Value,
            CommonCols<TFirstDerived, TSecondDerived>::Value
        >
        operator+(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        );

        template <class TFirstDerived, class TSecondDerived>
        const Matrix<
            typename CommonScalar<TFirstDerived, TSecondDerived>::Type,
            CommonRows<TFirstDerived, TSecondDerived>::Value,
            CommonCols<TFirstDerived, TSecondDerived>::Value
        >
        operator-(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        );

        template <class TFirstDerived, class TSecondDerived>
        const Matrix<
            typename CommonScalar<TFirstDerived, TSecondDerived>::Type,
            MatrixTraits<TFirstDerived>::NumRows,
            MatrixTraits<TSecondDerived>::NumColumns
        >
        operator*(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        );
    }
}
