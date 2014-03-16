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
            typedef typename MatrixTraits<TDerived>::Scalar Scalar;
            static const int NumRows = MatrixTraits<TDerived>::NumRows;
            static const int NumCols = MatrixTraits<TDerived>::NumCols;
            static const int ColStride = MatrixTraits<TDerived>::ColStride;

            TDerived&
            derived();

            const TDerived&
            derived() const;
        public:
            const typename MatrixTraits<TDerived>::Scalar
            coeff(int index) const;

            typename MatrixTraits<TDerived>::Scalar&
            coeffRef(int index);

            const typename MatrixTraits<TDerived>::Scalar
            coeff(int rowIndex, int colIndex) const;

            typename MatrixTraits<TDerived>::Scalar&
            coeffRef(int rowIndex, int colIndex);

            typename MatrixTraits<TDerived>::Scalar
            operator()(int index) const;

            typename MatrixTraits<TDerived>::Scalar&
            operator()(int index);

            const typename MatrixTraits<TDerived>::Scalar
            operator()(int rowIndex, int colIndex) const;

            typename MatrixTraits<TDerived>::Scalar&
            operator()(int rowIndex, int colIndex);

            const MatrixView<
                typename MatrixTraits<TDerived>::Scalar,
                1,
                MatrixTraits<TDerived>::NumCols,
                MatrixTraits<TDerived>::ColStride
            >
            row(int rowIndex) const;

            MatrixView<
                typename MatrixTraits<TDerived>::Scalar,
                1,
                MatrixTraits<TDerived>::NumCols,
                MatrixTraits<TDerived>::ColStride
            >
            row(int rowIndex);

            const MatrixView<
                typename MatrixTraits<TDerived>::Scalar,
                MatrixTraits<TDerived>::NumRows,
                1,
                MatrixTraits<TDerived>::ColStride
            >
            col(int colIndex) const;

            MatrixView<
                typename MatrixTraits<TDerived>::Scalar,
                MatrixTraits<TDerived>::NumRows,
                1,
                MatrixTraits<TDerived>::ColStride
            >
            col(int colIndex);

            const Matrix<
                typename MatrixTraits<TDerived>::Scalar,
                MatrixTraits<TDerived>::NumCols,
                MatrixTraits<TDerived>::NumRows
            >
            transpose() const;

            template <class TUnaryFunction>
            const typename MappedMatrixType<TUnaryFunction, TDerived>::Type
            map(TUnaryFunction unaryFunction) const;

            template <class TBinaryFunction, class TOtherDerived>
            const typename PairwiseMappedMatrixType<TBinaryFunction, TDerived, TOtherDerived>::Type
            binaryMap(
                const MatrixInterface<TOtherDerived>& other,
                TBinaryFunction binaryFunction
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
            TScalar
            redux(TFunction function) const;

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
                MatrixTraits<TDerived>::NumCols
            >
            cwiseLowerBound() const;

            const Matrix<
                double,
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumCols
            >
            cwiseUpperBound() const;

            const Matrix<
                double,
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumCols
            >
            cwiseWidth() const;

            const Matrix<
                double,
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumCols
            >
            cwiseMedian() const;

            const Matrix<
                TScalar,
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumCols
            >
            cwiseSquared() const;

            template <class TOtherDerived>
            const Matrix<
                decltype(MatrixTraits<TDerived>::Scalar() * MatrixTraits<TOtherDerived>::Scalar()),
                CommonRows<TDerived, TOtherDerived>::Value,
                CommonCols<TDerived, TOtherDerived>::Value
            >
            cwiseProduct(const MatrixInterface<TOtherDerived>& other) const;

            template <class TOtherDerived>
            const Matrix<
                decltype(MatrixTraits<TDerived>::Scalar() / MatrixTraits<TOtherDerived>::Scalar()),
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

            typename MatrixTraits<TDerived>::Scalar
            sum() const;

            typename MatrixTraits<TDerived>::Scalar
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
            operator+=(const MatrixInterface<TOtherDerived>& other) const;

            template <class TOtherDerived>
            void
            operator-=(const MatrixInterface<TOtherDerived>& other) const;

            void
            setConstant(typename MatrixTraits<TDerived>::Scalar value);

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
                    typename MatrixTraits<TMatrix>::Scalar
                >::Type,
                MatrixTraits<TMatrix>::NumRows,
                MatrixTraits<TMatrix>::NumCols
            > Type;
        };

        template < class TBinaryFunction, class TFirstMatrix, class TSecondMatrix>
        struct PairwiseMappedMatrixType
        {
            typedef Matrix<
                typename PairwiseMappedScalarType<
                    TBinaryFunction,
                    typename MatrixTraits<TFirstMatrix>::Scalar,
                    typename MatrixTraits<TSecondMatrix>::Scalar
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
        };

        template <int iFirstSize, int iSecondSize>
        struct CommonSize<iFirstSize, iSecondSize>
        {
            CheckCompatibleSizes<iFirstSize, iSecondSize> sizeCheck;

            static const int Value = (iFirstSize == -1) ? iSecondSize : iFirstSize;
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
                MatrixTraits<TFirstMatrix>::NumCols,
                MatrixTraits<TSecondMatrix>::NumCols
            >::Value;
        };
    }
}
