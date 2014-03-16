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

#include <OpenSolid/Core/Matrix/MatrixInterface.definitions.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/MatrixView.hpp>

#include <type_traits>

namespace opensolid
{
    namespace detail
    {
        template <class TDerived>
        inline
        TDerived&
        MatrixInterface<TDerived>::derived() {
            return static_cast<TDerived&>(*this);
        }

        template <class TDerived>
        inline
        const TDerived&
        MatrixInterface<TDerived>::derived() const {
            return static_cast<const TDerived&>(*this);
        }

        template <class TDerived>
        inline
        const typename MatrixTraits<TDerived>::Scalar
        MatrixInterface<TDerived>::coeff(int index) const {
            assert(index >= 0 && index < derived().size());
            return *(derived().data() + index);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar&
        MatrixInterface<TDerived>::coeffRef(int index) {
            assert(index >= 0 && index < derived().size());
            return *(derived().data() + index);
        }

        template <class TDerived>
        inline
        const typename MatrixTraits<TDerived>::Scalar
        MatrixInterface<TDerived>::coeff(int rowIndex, int colIndex) const {
            assert(rowIndex >= 0 && rowIndex < derived.rows());
            assert(colIndex >= 0 && colIndex < derived.cols());
            return coeff(rowIndex * derived().colStride() * colIndex);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar&
        MatrixInterface<TDerived>::coeffRef(int rowIndex, int colIndex) {
            assert(rowIndex >= 0 && rowIndex < derived.rows());
            assert(colIndex >= 0 && colIndex < derived.cols());
            return coeffRef(rowIndex * derived().colStride() * colIndex);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar
        MatrixInterface<TDerived>::operator()(int index) const {
            assert(index >= 0 && index < derived().size());
            return coeff(index);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar&
        MatrixInterface<TDerived>::operator()(int index) {
            assert(index >= 0 && index < derived().size());
            return coeffRef(index);
        }

        template <class TDerived>
        inline
        const typename MatrixTraits<TDerived>::Scalar
        MatrixInterface<TDerived>::operator()(int rowIndex, int colIndex) const {
            assert(rowIndex >= 0 && rowIndex < derived.rows());
            assert(colIndex >= 0 && colIndex < derived.cols());
            return coeff(rowIndex, colIndex);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar&
        MatrixInterface<TDerived>::operator()(int rowIndex, int colIndex) {
            assert(rowIndex >= 0 && rowIndex < derived.rows());
            assert(colIndex >= 0 && colIndex < derived.cols());
            return coeffRef(rowIndex, colIndex);
        }

        template <class TDerived>
        inline
        const MatrixView<
            typename MatrixTraits<TDerived>::Scalar,
            1,
            MatrixTraits<TDerived>::NumCols,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::row(int rowIndex) const {
            assert(rowIndex >= 0 && rowIndex < derived.rows());
            return MatrixView<
                typename MatrixTraits<TDerived>::Scalar,
                1,
                MatrixTraits<TDerived>::NumCols,
                MatrixTraits<TDerived>::ColStride
            >(
                derived().data() + rowIndex,
                1,
                derived().cols(),
                derived().colStride()
            );
        }

        template <class TDerived>
        inline
        MatrixView<
            typename MatrixTraits<TDerived>::Scalar,
            1,
            MatrixTraits<TDerived>::NumCols,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::row(int rowIndex) {
            assert(rowIndex >= 0 && rowIndex < derived.rows());
            return MatrixView<
                typename MatrixTraits<TDerived>::Scalar,
                1,
                MatrixTraits<TDerived>::NumCols,
                MatrixTraits<TDerived>::ColStride
            >(
                derived().data() + rowIndex,
                1,
                derived().cols(),
                derived().colStride()
            );
        }

        template <class TDerived>
        inline
        const MatrixView<
            typename MatrixTraits<TDerived>::Scalar,
            MatrixTraits<TDerived>::NumRows,
            1,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::col(int colIndex) const {
            assert(colIndex >= 0 && colIndex < derived.cols());
            return MatrixView<
                typename MatrixTraits<TDerived>::Scalar,
                MatrixTraits<TDerived>::NumRows,
                1,
                MatrixTraits<TDerived>::ColStride
            >(
                derived().data() + colIndex * derived().colStride(),
                derived().rows(),
                1,
                derived().colStride()
            );
        }

        template <class TDerived>
        inline
        MatrixView<
            typename MatrixTraits<TDerived>::Scalar,
            MatrixTraits<TDerived>::NumRows,
            1,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::col(int colIndex) {
            assert(colIndex >= 0 && colIndex < derived.cols());
            return MatrixView<
                typename MatrixTraits<TDerived>::Scalar,
                MatrixTraits<TDerived>::NumRows,
                1,
                MatrixTraits<TDerived>::ColStride
            >(
                derived().data() + colIndex * derived().colStride(),
                derived().rows(),
                1,
                derived().colStride()
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::Scalar,
            MatrixTraits<TDerived>::NumCols,
            MatrixTraits<TDerived>::NumRows
        >
        MatrixInterface<TDerived>::transpose() const {
            Matrix<Scalar, NumCols, NumRows> result;
            for (int colIndex = 0; colIndex < derived().cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < derived().rows(); ++rowIndex) {
                    result.coeffRef(colIndex, rowIndex) = coeff(rowIndex, colIndex);
                }
            }
            return result;
        }

        template <class TDerived> template <class TUnaryFunction>
        inline
        const typename MappedMatrixType<TUnaryFunction, TDerived>::Type
        MatrixInterface<TDerived>::map(TUnaryFunction unaryFunction) const {
            typename MappedMatrixType<TUnaryFunction, TDerived>::Type result;
            for (int index = 0; index < derived().size(); ++index) {
                result.coeffRef(index) = unaryFunction(coeff(index));
            }
            return result;
        }

        template <class TDerived> template <class TBinaryFunction, class TOtherDerived>
        inline
        const typename PairwiseMappedMatrixType<TBinaryFunction, TDerived, TOtherDerived>::Type
        MatrixInterface<TDerived>::binaryMap(
            const MatrixInterface<TOtherDerived>& other,
            TBinaryFunction binaryFunction
        ) const {
            typename PairwiseMappedMatrixType<
                TBinaryFunction,
                TDerived,
                TOtherDerived
            >::Type result;
            for (int index = 0; index < derived().size(); ++index) {
                result.coeffRef(index) = binaryFunction(coeff(index), other.coeff(index));
            }
            return result;
        }

        template <class TDerived> template <class TValue, class TFunction>
        inline
        const TValue
        MatrixInterface<TDerived>::fold(TValue initialValue, TFunction function) const {
            for (int index = 0; index < derived().size(); ++index) {
                initialValue = function(initialValue, coeff(index));
            }
            return initialValue;
        }

        template <class TDerived> template <class TOtherDerived, class TValue, class TFunction>
        inline
        const TValue
        MatrixInterface<TDerived>::binaryFold(
            const MatrixInterface<TOtherDerived>& other,
            TValue initialValue,
            TFunction function
        ) const {
            for (int index = 0; index < derived().size(); ++index) {
                initialValue = function(initialValue, coeff(index), other.coeff(index));
            }
            return initialValue;
        }

        template <class TDerived> template <class TFunction>
        inline
        TScalar
        MatrixInterface<TDerived>::redux(TFunction function) const {
            TScalar result = coeff(0);
            for (int index = 1; index < derived().size(); ++index) {
                result = function(result, coeff(index));
            }
            return result;
        }

        template <class TDerived> template <class TUnaryPredicate>
        inline
        bool
        MatrixInterface<TDerived>::any(TUnaryPredicate unaryPredicate) const {
            for (int index = 0; index < derived().size(); ++index) {
                if (unaryPredicate(coeff(index))) {
                    return true;
                }
            }
            return false;
        }

        template <class TDerived> template <class TBinaryPredicate, class TOtherDerived>
        inline
        bool
        MatrixInterface<TDerived>::binaryAny(
            const MatrixInterface<TOtherDerived>& other,
            TBinaryPredicate binaryPredicate
        ) const {
            for (int index = 0; index < derived().size(); ++index) {
                if (unaryPredicate(coeff(index), other.coeff(index))) {
                    return true;
                }
            }
            return false;
        }

        template <class TDerived> template <class TUnaryPredicate>
        inline
        bool
        MatrixInterface<TDerived>::all(TUnaryPredicate unaryPredicate) const {
            for (int index = 0; index < derived().size(); ++index) {
                if (!unaryPredicate(coeff(index))) {
                    return false;
                }
            }
            return true;
        }

        template <class TDerived> template <class TBinaryPredicate, class TOtherDerived>
        inline
        bool
        MatrixInterface<TDerived>::binaryAll(
            const MatrixInterface<TOtherDerived>& other,
            TBinaryPredicate binaryPredicate
        ) const {
            for (int index = 0; index < derived().size(); ++index) {
                if (!binaryPredicate(coeff(index), other.coeff(index))) {
                    return false;
                }
            }
            return true;
        }

        template <class TDerived>
        inline
        bool
        MatrixInterface<TDerived>::isConstant(double value, double precision = 1e-12) const {

        }

        template <class TDerived>
        inline
        bool
        MatrixInterface<TDerived>::isZero(double precision = 1e-12) const {

        }

        template <class TDerived>
        inline
        bool
        MatrixInterface<TDerived>::isOnes(double precision = 1e-12) const {

        }

        template <class TDerived>
        inline
        bool
        MatrixInterface<TDerived>::isIdentity(double precision = 1e-12) const {

        }

        template <class TDerived>
        inline
        const Matrix<
            double,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumCols
        >
        MatrixInterface<TDerived>::cwiseLowerBound() const {

        }

        template <class TDerived>
        inline
        const Matrix<
            double,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumCols
        >
        MatrixInterface<TDerived>::cwiseUpperBound() const {

        }

        template <class TDerived>
        inline
        const Matrix<
            double,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumCols
        >
        MatrixInterface<TDerived>::cwiseWidth() const {

        }

        template <class TDerived>
        inline
        const Matrix<
            double,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumCols
        >
        MatrixInterface<TDerived>::cwiseMedian() const {

        }

        template <class TDerived>
        inline
        const Matrix<
            TScalar,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumCols
        >
        MatrixInterface<TDerived>::cwiseSquared() const {

        }

        template <class TDerived> template <class TOtherDerived>
        inline
        const Matrix<
            decltype(MatrixTraits<TDerived>::Scalar() * MatrixTraits<TOtherDerived>::Scalar()),
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonCols<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseProduct(const MatrixInterface<TOtherDerived>& other) const {

        }

        template <class TDerived> template <class TOtherDerived>
        inline
        const Matrix<
            decltype(MatrixTraits<TDerived>::Scalar() / MatrixTraits<TOtherDerived>::Scalar()),
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonCols<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseQuotient(
            const MatrixInterface<TOtherDerived>& other
        ) const {

        }

        template <class TDerived> template <class TOtherDerived>
        inline
        const Matrix<
            Interval,
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonCols<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseHull(const MatrixInterface<TOtherDerived>& other) const {

        }

        template <class TDerived> template <class TOtherDerived>
        inline
        const Matrix<
            Interval,
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonCols<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseIntersection(
            const MatrixInterface<TOtherDerived>& other
        ) const {

        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar
        MatrixInterface<TDerived>::sum() const {

        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar
        MatrixInterface<TDerived>::prod() const {

        }

        template <class TDerived> template <class TOtherDerived>
        inline
        bool
        MatrixInterface<TDerived>::operator==(const MatrixInterface<TOtherDerived>& other) const {

        }

        template <class TDerived> template <class TOtherDerived>
        inline
        bool
        MatrixInterface<TDerived>::operator!=(const MatrixInterface<TOtherDerived>& other) const {

        }

        template <class TDerived> template <class TOtherScalar>
        inline
        void
        MatrixInterface<TDerived>::operator*=(TOtherScalar scale) {

        }

        template <class TDerived> template <class TOtherScalar>
        inline
        void
        MatrixInterface<TDerived>::operator/=(TOtherScalar divisor) {

        }

        template <class TDerived> template <class TOtherDerived>
        inline
        void
        MatrixInterface<TDerived>::operator+=(const MatrixInterface<TOtherDerived>& other) const {

        }

        template <class TDerived> template <class TOtherDerived>
        inline
        void
        MatrixInterface<TDerived>::operator-=(const MatrixInterface<TOtherDerived>& other) const {

        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setConstant(typename MatrixTraits<TDerived>::Scalar value) {

        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setZero() {

        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setOnes() {

        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setIdentity() {

        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setRandom() {

        }
    }
}
