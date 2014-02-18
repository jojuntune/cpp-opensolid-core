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
#include <OpenSolid/Core/IntervalMatrix.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TUnaryFunction, class TScalar>
        struct MappedScalarType
        {
            typedef typename std::decay<
                typename std::result_of<
                    TUnaryFunction(TScalar)
                >::type
            >::type Type;
        };

        template <class TBinaryFunction, class TScalar, class TOtherScalar>
        struct PairwiseMappedScalarType
        {
            typedef typename std::decay<
                typename std::result_of<
                    TBinaryFunction(TScalar, TOtherScalar)
                >::type
            >::type Type;
        };

        template <class TUnaryFunction, class TScalar, int iNumRows, int iNumColumns>
        struct MappedMatrixType
        {
            typedef typename MatrixType<
                typename MappedScalarType<TFunction, TScalar>::Type,
                iNumRows,
                iNumColumns
            >::Type Type;
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
            typedef typename MatrixType<
                typename PairwiseMappedScalarType<TBinaryFunction, TScalar, TOtherScalar>::Type,
                iNumRows,
                iNumColumns
            >::Type Type;
        };

        template <class TScalar, int iNumRows, int iNumColumns>
        class MatrixBase
        {
        private:
            TScalar _components[iNumRows * iNumColumns];

            template <class TScalar, int iNumRows, int iNumColumns> friend class MatrixBase;
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

            const typename MatrixType<TScalar, 1, iNumColumns>::Type
            row(std::int64_t rowIndex) const;

            const typename MatrixType<TScalar, iNumRows, 1>::Type
            column(std::int64_t columnIndex) const;

            const TScalar*
            data() const;

            TScalar*
            data();

            void
            fill(TScalar value);

            const typename MatrixType<TScalar, iNumColumns, iNumRows>::Type
            transpose() const;

            template <class TUnaryPredicate>
            const bool
            any(TUnaryPredicate unaryPredicate) const;

            template <class TUnaryPredicate>
            const bool
            all(TUnaryPredicate unaryPredicate) const;

            template <class TBinaryPredicate, class TOtherScalar>
            const bool
            binaryAny(
                const MatrixBase<TOtherScalar, iNumRows, iNumColumns>& other,
                TBinaryPredicate binaryPredicate
            ) const;

            template <class TBinaryPredicate, class TOtherScalar>
            const bool
            binaryAll(
                const MatrixBase<TOtherScalar, iNumRows, iNumColumns>& other,
                TBinaryPredicate binaryPredicate
            ) const;

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
                const MatrixBase<TOtherScalar, iNumRows, iNumColumns>& other,
                TBinaryFunction binaryFunction
            ) const;

            static const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
            Constant(TScalar value);

            static const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
            Zero();

            static const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
            Ones();

            static const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
            Identity();

            static const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
            Random();

            static const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
            FromColumns(
                const typename MatrixType<TScalar, iNumRows, 1>& firstColumn,
                const typename MatrixType<TScalar, iNumRows, 1>& secondColumn
            );

            static const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
            FromColumns(
                const typename MatrixType<TScalar, iNumRows, 1>& firstColumn,
                const typename MatrixType<TScalar, iNumRows, 1>& secondColumn,
                const typename MatrixType<TScalar, iNumRows, 1>& thirdColumn
            );

            static const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
            FromRows(
                const typename MatrixType<TScalar, 1, iNumColumns>& firstRow,
                const typename MatrixType<TScalar, 1, iNumColumns>& secondRow
            );

            static const typename MatrixType<TScalar, iNumRows, iNumColumns>::Type
            FromRows(
                const typename MatrixType<TScalar, 1, iNumColumns>& firstRow,
                const typename MatrixType<TScalar, 1, iNumColumns>& secondRow,
                const typename MatrixType<TScalar, 1, iNumColumns>& thirdRow
            );
        };
    }
}
