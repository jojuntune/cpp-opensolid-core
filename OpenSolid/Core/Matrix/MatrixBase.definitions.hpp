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

#include <OpenSolid/Core/Matrix/MatrixBase.declarations.hpp>

#include <OpenSolid/Core/Matrix.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TUnaryFunction, class TScalar>
        struct MappedScalarType
        {
            typedef typename std::decay<
                typename std::result_of<TUnaryFunction(TScalar)>::type
            >::type Type;
        };

        template <class TBinaryFunction, class TScalar, class TOtherScalar>
        struct PairwiseMappedScalarType
        {
            typedef typename std::decay<
                typename std::result_of<TBinaryFunction(TScalar, TOtherScalar)>::type
            >::type Type;
        };

        template <class TUnaryFunction, class TScalar, int iNumRows, int iNumColumns>
        struct MappedMatrixType
        {
            typedef Matrix<
                typename MappedScalarType<TUnaryFunction, TScalar>::Type,
                iNumRows,
                iNumColumns
            > Type;
        };

        template <
            class TBinaryFunction,
            class TScalar,
            class TOtherScalar,
            int iNumRows,
            int iNumColumns
        >
        struct PairwiseMappedMatrixType
        {
            typedef Matrix<
                typename PairwiseMappedScalarType<TBinaryFunction, TScalar, TOtherScalar>::Type,
                iNumRows,
                iNumColumns
            > Type;
        };

        template <class TScalar, int iNumRows, int iNumColumns>
        class MatrixBase
        {
        private:
            TScalar _components[iNumRows * iNumColumns];
        protected:
            static const int Size = iNumRows * iNumColumns;

            MatrixBase();

            MatrixBase(const TScalar* sourcePtr);
        public:
            static_assert(iNumRows > 0 && iNumColumns > 0, "Zero-sized matrices not allowed");

            const TScalar
            component(std::int64_t index) const;

            TScalar&
            component(std::int64_t index);

            const TScalar
            component(std::int64_t rowIndex, std::int64_t columnIndex) const;

            TScalar&
            component(std::int64_t rowIndex, std::int64_t columnIndex);

            const TScalar
            operator()(std::int64_t index) const;

            TScalar&
            operator()(std::int64_t index);

            const TScalar
            operator()(std::int64_t rowIndex, std::int64_t columnIndex) const;

            TScalar&
            operator()(std::int64_t rowIndex, std::int64_t columnIndex);

            const Matrix<TScalar, 1, iNumColumns>
            row(std::int64_t rowIndex) const;

            const Matrix<TScalar, iNumRows, 1>
            column(std::int64_t columnIndex) const;

            const TScalar*
            data() const;

            TScalar*
            data();

            const Matrix<TScalar, iNumColumns, iNumRows>
            transpose() const;

            template <class TUnaryFunction>
            const typename MappedMatrixType<
                TUnaryFunction,
                TScalar,
                iNumRows,
                iNumColumns
            >::Type
            map(TUnaryFunction unaryFunction) const;

            template <class TBinaryFunction, class TOtherScalar>
            const typename PairwiseMappedMatrixType<
                TBinaryFunction,
                TScalar,
                TOtherScalar,
                iNumRows,
                iNumColumns
            >::Type
            binaryMap(
                const Matrix<TOtherScalar, iNumRows, iNumColumns>& other,
                TBinaryFunction binaryFunction
            ) const;

            template <class TValue, class TFunction>
            const TValue
            fold(TValue initialValue, TFunction function) const;

            template <class TValue, class TOtherScalar, class TFunction>
            const TValue
            binaryFold(
                const Matrix<TOtherScalar, iNumRows, iNumColumns>& other,
                TValue initialValue,
                TFunction function
            ) const;

            template <class TFunction>
            TScalar
            reduce(TFunction function) const;

            template <class TUnaryPredicate>
            bool
            any(TUnaryPredicate unaryPredicate) const;

            template <class TBinaryPredicate, class TOtherScalar>
            bool
            binaryAny(
                const Matrix<TOtherScalar, iNumRows, iNumColumns>& other,
                TBinaryPredicate binaryPredicate
            ) const;

            template <class TUnaryPredicate>
            bool
            all(TUnaryPredicate unaryPredicate) const;

            template <class TBinaryPredicate, class TOtherScalar>
            bool
            binaryAll(
                const Matrix<TOtherScalar, iNumRows, iNumColumns>& other,
                TBinaryPredicate binaryPredicate
            ) const;

            bool
            isZero(double precision = 1e-12) const;

            bool
            isIdentity(double precision = 1e-12) const;

            const Matrix<double, iNumRows, iNumColumns>
            cwiseLowerBound() const;

            const Matrix<double, iNumRows, iNumColumns>
            cwiseUpperBound() const;

            const Matrix<double, iNumRows, iNumColumns>
            cwiseWidth() const;

            const Matrix<double, iNumRows, iNumColumns>
            cwiseMedian() const;

            const Matrix<TScalar, iNumRows, iNumColumns>
            cwiseSquared() const;

            template <class TOtherScalar>
            const Matrix<decltype(TScalar() * TOtherScalar()), iNumRows, iNumColumns>
            cwiseProduct(const Matrix<TOtherScalar, iNumRows, iNumColumns>& other) const;

            template <class TOtherScalar>
            const Matrix<decltype(TScalar() / TOtherScalar()), iNumRows, iNumColumns>
            cwiseQuotient(const Matrix<TOtherScalar, iNumRows, iNumColumns>& other) const;

            template <class TOtherScalar>
            const Matrix<Interval, iNumRows, iNumColumns>
            cwiseHull(const Matrix<TOtherScalar, iNumRows, iNumColumns>& other) const;

            template <class TOtherScalar>
            const Matrix<Interval, iNumRows, iNumColumns>
            cwiseIntersection(const Matrix<TOtherScalar, iNumRows, iNumColumns>& other) const;

            TScalar
            sum() const;

            TScalar
            product() const;

            bool
            operator==(const Matrix<TScalar, iNumRows, iNumColumns>& other) const;

            bool
            operator!=(const Matrix<TScalar, iNumRows, iNumColumns>& other) const;

            template <class TOtherScalar>
            void
            operator*=(TOtherScalar scale);

            template <class TOtherScalar>
            void
            operator/=(TOtherScalar divisor);

            template <class TOtherScalar>
            void
            operator+=(const Matrix<TOtherScalar, iNumRows, iNumColumns>& other) const;

            template <class TOtherScalar>
            void
            operator-=(const Matrix<TOtherScalar, iNumRows, iNumColumns>& other) const;

            void
            setConstant(TScalar value);

            void
            setDefault();

            void
            setZero();

            void
            setOnes();

            void
            setIdentity();

            void
            setRandom();

            void
            setColumns(
                const Matrix<TScalar, iNumRows, 1>& firstColumn,
                const Matrix<TScalar, iNumRows, 1>& secondColumn
            );

            void
            setColumns(
                const Matrix<TScalar, iNumRows, 1>& firstColumn,
                const Matrix<TScalar, iNumRows, 1>& secondColumn,
                const Matrix<TScalar, iNumRows, 1>& thirdColumn
            );

            void
            setRows(
                const Matrix<TScalar, 1, iNumColumns>& firstRow,
                const Matrix<TScalar, 1, iNumColumns>& secondRow
            );

            void
            setRows(
                const Matrix<TScalar, 1, iNumColumns>& firstRow,
                const Matrix<TScalar, 1, iNumColumns>& secondRow,
                const Matrix<TScalar, 1, iNumColumns>& thirdRow
            );

            static const Matrix<TScalar, iNumRows, iNumColumns>
            Constant(TScalar value);

            static const Matrix<TScalar, iNumRows, iNumColumns>
            Zero();

            static const Matrix<TScalar, iNumRows, iNumColumns>
            Ones();

            static const Matrix<TScalar, iNumRows, iNumColumns>
            Identity();

            static const Matrix<TScalar, iNumRows, iNumColumns>
            Random();

            static const Matrix<TScalar, iNumRows, iNumColumns>
            FromColumns(
                const Matrix<TScalar, iNumRows, 1>& firstColumn,
                const Matrix<TScalar, iNumRows, 1>& secondColumn
            );

            static const Matrix<TScalar, iNumRows, iNumColumns>
            FromColumns(
                const Matrix<TScalar, iNumRows, 1>& firstColumn,
                const Matrix<TScalar, iNumRows, 1>& secondColumn,
                const Matrix<TScalar, iNumRows, 1>& thirdColumn
            );

            static const Matrix<TScalar, iNumRows, iNumColumns>
            FromRows(
                const Matrix<TScalar, 1, iNumColumns>& firstRow,
                const Matrix<TScalar, 1, iNumColumns>& secondRow
            );

            static const Matrix<TScalar, iNumRows, iNumColumns>
            FromRows(
                const Matrix<TScalar, 1, iNumColumns>& firstRow,
                const Matrix<TScalar, 1, iNumColumns>& secondRow,
                const Matrix<TScalar, 1, iNumColumns>& thirdRow
            );
        };
    }
}
