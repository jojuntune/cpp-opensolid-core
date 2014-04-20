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

#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Matrix/MatrixDeterminantFunction.hpp>
#include <OpenSolid/Core/Matrix/MatrixInverseFunction.hpp>
#include <OpenSolid/Core/MatrixView.definitions.hpp>

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
        const typename MatrixTraits<TDerived>::ScalarType*
        MatrixInterface<TDerived>::data() const {
            return derived().data();
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType*
        MatrixInterface<TDerived>::data() {
            return derived().data();
        }

        template <class TDerived>
        inline
        int
        MatrixInterface<TDerived>::rows() const {
            return derived().rows();
        }

        template <class TDerived>
        inline
        int
        MatrixInterface<TDerived>::cols() const {
            return derived().cols();
        }

        template <class TDerived>
        inline
        int
        MatrixInterface<TDerived>::size() const {
            return derived().size();
        }

        template <class TDerived>
        inline
        int
        MatrixInterface<TDerived>::colStride() const {
            return derived().colStride();
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::coeff(int index) const {
            assert(index >= 0 && index < size());
            return coeff(index % rows(), index / rows());
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType&
        MatrixInterface<TDerived>::coeff(int index) {
            assert(index >= 0 && index < size());
            return coeff(index % rows(), index / rows());
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::coeff(int rowIndex, int colIndex) const {
            assert(rowIndex >= 0 && rowIndex < rows());
            assert(colIndex >= 0 && colIndex < cols());
            return *(data() + rowIndex + colIndex * colStride());
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType&
        MatrixInterface<TDerived>::coeff(int rowIndex, int colIndex) {
            assert(rowIndex >= 0 && rowIndex < rows());
            assert(colIndex >= 0 && colIndex < cols());
            return *(data() + rowIndex + colIndex * colStride());
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::operator()(int index) const {
            return coeff(index);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType&
        MatrixInterface<TDerived>::operator()(int index) {
            return coeff(index);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::operator()(int rowIndex, int colIndex) const {
            return coeff(rowIndex, colIndex);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType&
        MatrixInterface<TDerived>::operator()(int rowIndex, int colIndex) {
            return coeff(rowIndex, colIndex);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::value() const {
            assert(rows() == 1 && cols() == 1);
            return coeff(0);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType&
        MatrixInterface<TDerived>::value() {
            assert(rows() == 1 && cols() == 1);
            return coeff(0);
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        void
        MatrixInterface<TDerived>::operator=(const MatrixInterface<TOtherDerived>& other) {
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());

            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    this->coeff(rowIndex, colIndex) = other.coeff(rowIndex, colIndex);
                }
            }
        }

        template <class TDerived>
        inline
        const MatrixView<
            const typename MatrixTraits<TDerived>::PlainScalarType,
            1,
            MatrixTraits<TDerived>::Cols,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::row(int rowIndex) const {
            typedef const typename MatrixTraits<TDerived>::PlainScalarType ConstScalarType;

            assert(rowIndex >= 0 && rowIndex < rows());

            return MatrixView<ConstScalarType, 1, Cols, ColStride>(
                data() + rowIndex,
                1,
                cols(),
                colStride()
            );
        }

        template <class TDerived>
        inline
        MatrixView<
            typename MatrixTraits<TDerived>::ScalarType,
            1,
            MatrixTraits<TDerived>::Cols,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::row(int rowIndex) {
            assert(rowIndex >= 0 && rowIndex < rows());

            return MatrixView<typename MatrixTraits<TDerived>::ScalarType, 1, Cols, ColStride>(
                data() + rowIndex,
                1,
                cols(),
                colStride()
            );
        }

        template <class TDerived>
        inline
        const MatrixView<
            const typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::Rows,
            1,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::col(int colIndex) const {
            typedef const typename MatrixTraits<TDerived>::PlainScalarType ConstScalarType;

            assert(colIndex >= 0 && colIndex < cols());
            
            return MatrixView<ConstScalarType, Rows, 1, ColStride>(
                data() + colIndex * colStride(),
                rows(),
                1,
                colStride()
            );
        }

        template <class TDerived>
        inline
        MatrixView<
            typename MatrixTraits<TDerived>::ScalarType,
            MatrixTraits<TDerived>::Rows,
            1,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::col(int colIndex) {
            assert(colIndex >= 0 && colIndex < cols());

            return MatrixView<typename MatrixTraits<TDerived>::ScalarType, Rows, 1, ColStride>(
                data() + colIndex * colStride(),
                rows(),
                1,
                colStride()
            );
        }

        template <class TDerived> template <int iBlockRows, int iBlockCols>
        const MatrixView<
            const typename MatrixTraits<TDerived>::PlainScalarType,
            iBlockRows,
            iBlockCols,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::block(int startRow, int startCol) const {
            return MatrixView<
                const typename MatrixTraits<TDerived>::PlainScalarType,
                iBlockRows,
                iBlockCols,
                MatrixTraits<TDerived>::ColStride
            >(
                data() + startCol * colStride() + startRow,
                iBlockRows,
                iBlockCols,
                colStride()
            );
        }

        template <class TDerived> template <int iBlockRows, int iBlockCols>
        MatrixView<
            typename MatrixTraits<TDerived>::ScalarType,
            iBlockRows,
            iBlockCols,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::block(int startRow, int startCol) {
            return MatrixView<
                typename MatrixTraits<TDerived>::ScalarType,
                iBlockRows,
                iBlockCols,
                MatrixTraits<TDerived>::ColStride
            >(
                data() + startCol * colStride() + startRow,
                iBlockRows,
                iBlockCols,
                colStride()
            );

        }

        template <class TDerived>
        const MatrixView<
            const typename MatrixTraits<TDerived>::PlainScalarType,
            -1,
            -1,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::block(
            int startRow,
            int startCol,
            int blockRows,
            int blockCols
        ) const {
            return MatrixView<
                const typename MatrixTraits<TDerived>::PlainScalarType,
                -1,
                -1,
                MatrixTraits<TDerived>::ColStride
            >(
                data() + startCol * colStride() + startRow,
                blockRows,
                blockCols,
                colStride()
            );
        }

        template <class TDerived>
        MatrixView<
            typename MatrixTraits<TDerived>::ScalarType,
            -1,
            -1,
            MatrixTraits<TDerived>::ColStride
        >
        MatrixInterface<TDerived>::block(
            int startRow,
            int startCol,
            int blockRows,
            int blockCols
        ) {
            return MatrixView<
                typename MatrixTraits<TDerived>::ScalarType,
                -1,
                -1,
                MatrixTraits<TDerived>::ColStride
            >(
                data() + startCol * colStride() + startRow,
                blockRows,
                blockCols,
                colStride()
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::Cols,
            MatrixTraits<TDerived>::Rows
        >
        MatrixInterface<TDerived>::transpose() const {
            Matrix<PlainScalarType, Cols, Rows> result(cols(), rows());
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    result.coeff(colIndex, rowIndex) = this->coeff(rowIndex, colIndex);
                }
            }
            return result;
        }

        template <class TDerived>
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::determinant() const {
            return MatrixDeterminantFunction<
                MatrixTraits<TDerived>::Rows,
                MatrixTraits<TDerived>::Cols
            >()(derived());
        }

        template <class TDerived>
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::Cols,
            MatrixTraits<TDerived>::Rows
        >
        MatrixInterface<TDerived>::inverse() const {
            return MatrixInverseFunction<
                MatrixTraits<TDerived>::Rows,
                MatrixTraits<TDerived>::Cols
            >()(derived());
        }

        template <class TDerived> template <class TUnaryFunction>
        inline
        const typename MappedMatrixType<TUnaryFunction, TDerived>::Type
        MatrixInterface<TDerived>::map(TUnaryFunction unaryFunction) const {
            typename MappedMatrixType<TUnaryFunction, TDerived>::Type result(rows(), cols());
            map(unaryFunction, result);
            return result;
        }

        template <class TDerived> template <class TUnaryFunction, class TResultDerived>
        inline
        void
        MatrixInterface<TDerived>::map(
            TUnaryFunction unaryFunction,
            MatrixInterface<TResultDerived>& result
        ) const {
            CheckCompatibleMatrices<TDerived, TResultDerived>(derived(), result.derived());

            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    result.coeff(rowIndex, colIndex) = unaryFunction(
                        this->coeff(rowIndex, colIndex)
                    );
                }
            }
        }

        template <class TDerived> template <class TBinaryFunction, class TOtherDerived>
        inline
        const typename PairwiseMappedMatrixType<TBinaryFunction, TDerived, TOtherDerived>::Type
        MatrixInterface<TDerived>::binaryMap(
            const MatrixInterface<TOtherDerived>& other,
            TBinaryFunction binaryFunction
        ) const {
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());

            typename PairwiseMappedMatrixType<
                TBinaryFunction,
                TDerived,
                TOtherDerived
            >::Type result(rows(), cols());
            binaryMap(other, binaryFunction, result);
            return result;
        }

        template <class TDerived>
        template <class TBinaryFunction, class TOtherDerived, class TResultDerived>
        inline
        void
        MatrixInterface<TDerived>::binaryMap(
            const MatrixInterface<TOtherDerived>& other,
            TBinaryFunction binaryFunction,
            MatrixInterface<TResultDerived>& result
        ) const {
            CheckCompatibleMatrices<TDerived, TResultDerived>(derived(), result.derived());

            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    result.coeff(rowIndex, colIndex) = binaryFunction(
                        this->coeff(rowIndex, colIndex),
                        other.coeff(rowIndex, colIndex)
                    );
                }
            }
        }

        template <class TDerived> template <class TValue, class TFunction>
        inline
        const TValue
        MatrixInterface<TDerived>::fold(TValue initialValue, TFunction function) const {
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    initialValue = function(initialValue, coeff(rowIndex, colIndex));
                }
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
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());
            
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    initialValue = function(
                        initialValue,
                        this->coeff(rowIndex, colIndex),
                        other.coeff(rowIndex, colIndex)
                    );
                }
            }
            return initialValue;
        }

        template <class TDerived> template <class TFunction>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::reduce(TFunction function) const {
            ScalarType result = coeff(0, 0);
            int rowIndex = 1;
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (; rowIndex < rows(); ++rowIndex) {
                    result = function(result, coeff(rowIndex, colIndex));
                }
                rowIndex = 0;
            }
            return result;
        }

        template <class TDerived> template <class TUnaryPredicate>
        inline
        bool
        MatrixInterface<TDerived>::any(TUnaryPredicate unaryPredicate) const {
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    if (unaryPredicate(coeff(rowIndex, colIndex))) {
                        return true;
                    }
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
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());

            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    if (
                        binaryPredicate(
                            this->coeff(rowIndex, colIndex),
                            other.coeff(rowIndex, colIndex)
                        )
                    ) {
                        return true;
                    }
                }
            }
            return false;
        }

        template <class TDerived> template <class TUnaryPredicate>
        inline
        bool
        MatrixInterface<TDerived>::all(TUnaryPredicate unaryPredicate) const {
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    if (!unaryPredicate(coeff(rowIndex, colIndex))) {
                        return false;
                    }
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
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());

            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    if (
                        !binaryPredicate(
                            this->coeff(rowIndex, colIndex),
                            other.coeff(rowIndex, colIndex)
                        )
                    ) {
                        return false;
                    }
                }
            }
            return true;
        }

        template <class TDerived>
        inline
        bool
        MatrixInterface<TDerived>::isConstant(double value, double precision) const {
            return all(
                [value, precision] (ScalarType coeff) -> bool {
                    return coeff - value == opensolid::Zero(precision);
                }
            );
        }

        template <class TDerived>
        inline
        bool
        MatrixInterface<TDerived>::isZero(double precision) const {
            return all(
                [precision] (ScalarType coeff) -> bool {
                    return coeff == opensolid::Zero(precision);
                }
            );
        }

        template <class TDerived>
        inline
        bool
        MatrixInterface<TDerived>::isOnes(double precision) const {
            return isConstant(1.0);
        }

        template <class TDerived>
        inline
        bool
        MatrixInterface<TDerived>::isIdentity(double precision) const {
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    double expected = double(rowIndex == colIndex);
                    if (coeff(rowIndex, colIndex) - expected != opensolid::Zero(precision)) {
                        return false;
                    }
                }
            }
            return true;
        }

        inline
        double
        coeffLowerBound(double coeff) {
            return coeff;
        }

        inline
        double
        coeffLowerBound(Interval coeff) {
            return coeff.lowerBound();
        }

        template <class TDerived>
        inline
        const Matrix<double, MatrixTraits<TDerived>::Rows, MatrixTraits<TDerived>::Cols>
        MatrixInterface<TDerived>::cwiseLowerBound() const {
            return map(
                [] (ScalarType coeff) -> double {
                    return coeffLowerBound(coeff);
                }
            );
        }

        inline
        double
        coeffUpperBound(double coeff) {
            return coeff;
        }

        inline
        double
        coeffUpperBound(Interval coeff) {
            return coeff.upperBound();
        }

        template <class TDerived>
        inline
        const Matrix<double, MatrixTraits<TDerived>::Rows, MatrixTraits<TDerived>::Cols>
        MatrixInterface<TDerived>::cwiseUpperBound() const {
            return map(
                [] (ScalarType coeff) -> double {
                    return coeffUpperBound(coeff);
                }
            );
        }

        inline
        double
        coeffWidth(double coeff) {
            return 0.0;
        }

        inline
        double
        coeffWidth(Interval coeff) {
            return coeff.width();
        }

        template <class TDerived>
        inline
        const Matrix<double, MatrixTraits<TDerived>::Rows, MatrixTraits<TDerived>::Cols>
        MatrixInterface<TDerived>::cwiseWidth() const {
            return map(
                [] (ScalarType coeff) -> double {
                    return coeffWidth(coeff);
                }
            );
        }

        inline
        double
        coeffMedian(double coeff) {
            return coeff;
        }

        inline
        double
        coeffMedian(Interval coeff) {
            return coeff.median();
        }

        template <class TDerived>
        inline
        const Matrix<double, MatrixTraits<TDerived>::Rows, MatrixTraits<TDerived>::Cols>
        MatrixInterface<TDerived>::cwiseMedian() const {
            return map(
                [] (ScalarType coeff) -> double {
                    return coeffMedian(coeff);
                }
            );
        }

        inline
        double
        coeffSquared(double coeff) {
            return coeff * coeff;
        }

        inline
        Interval
        coeffSquared(Interval coeff) {
            return coeff.squared();
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::Rows,
            MatrixTraits<TDerived>::Cols
        >
        MatrixInterface<TDerived>::cwiseSquared() const {
            return map(
                [] (ScalarType coeff) -> ScalarType {
                    return coeffSquared(coeff);
                }
            );
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        const Matrix<
            typename CommonScalar<TDerived, TOtherDerived>::Type,
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonCols<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseProduct(const MatrixInterface<TOtherDerived>& other) const {
            return binaryMap(
                other,
                [] (
                    typename MatrixTraits<TDerived>::ScalarType thisCoeff,
                    typename MatrixTraits<TOtherDerived>::ScalarType otherCoeff
                ) {
                    return thisCoeff * otherCoeff;
                }
            );
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        const Matrix<
            typename CommonScalar<TDerived, TOtherDerived>::Type,
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonCols<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseQuotient(
            const MatrixInterface<TOtherDerived>& other
        ) const {
            return binaryMap(
                other,
                [] (
                    typename MatrixTraits<TDerived>::ScalarType thisCoeff,
                    typename MatrixTraits<TOtherDerived>::ScalarType otherCoeff
                ) {
                    return thisCoeff / otherCoeff;
                }
            );
        }

        inline
        Interval
        coeffHull(double firstCoeff, double secondCoeff) {
            return Interval::Hull(firstCoeff, secondCoeff);
        }

        inline
        Interval
        coeffHull(double firstCoeff, Interval secondCoeff) {
            return secondCoeff.hull(firstCoeff);
        }

        inline
        Interval
        coeffHull(Interval firstCoeff, double secondCoeff) {
            return firstCoeff.hull(secondCoeff);
        }

        inline
        Interval
        coeffHull(Interval firstCoeff, Interval secondCoeff) {
            return firstCoeff.hull(secondCoeff);
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        const Matrix<
            Interval,
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonCols<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseHull(const MatrixInterface<TOtherDerived>& other) const {
            return binaryMap(
                other,
                [] (
                    typename MatrixTraits<TDerived>::ScalarType thisCoeff,
                    typename MatrixTraits<TOtherDerived>::ScalarType otherCoeff
                ) -> Interval {
                    return coeffHull(thisCoeff, otherCoeff);
                }
            );
        }

        inline
        Interval
        coeffIntersection(double firstCoeff, double secondCoeff) {
            return firstCoeff - secondCoeff == Zero() ?
                Interval(firstCoeff + 0.5 * (secondCoeff - firstCoeff)) :
                Interval::Empty();
        }

        inline
        Interval
        coeffIntersection(double firstCoeff, Interval secondCoeff) {
            return secondCoeff.contains(firstCoeff) ?
                Interval(firstCoeff) :
                Interval::Empty();
        }

        inline
        Interval
        coeffIntersection(Interval firstCoeff, double secondCoeff) {
            return firstCoeff.contains(secondCoeff) ?
                Interval(secondCoeff) :
                Interval::Empty();
        }

        inline
        Interval
        coeffIntersection(Interval firstCoeff, Interval secondCoeff) {
            return firstCoeff.intersection(secondCoeff);
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
            return binaryMap(
                other,
                [] (
                    typename MatrixTraits<TDerived>::ScalarType thisCoeff,
                    typename MatrixTraits<TOtherDerived>::ScalarType otherCoeff
                ) -> Interval {
                    return coeffIntersection(thisCoeff, otherCoeff);
                }
            );
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::sum() const {
            return reduce(
                [] (ScalarType result, ScalarType coeff) {
                    return result + coeff;
                }
            );
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::prod() const {
            return reduce(
                [] (ScalarType result, ScalarType coeff) {
                    return result * coeff;
                }
            );
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        bool
        MatrixInterface<TDerived>::operator==(const MatrixInterface<TOtherDerived>& other) const {
            return binaryAll(
                other,
                [] (
                    typename MatrixTraits<TDerived>::ScalarType thisCoeff,
                    typename MatrixTraits<TOtherDerived>::ScalarType otherCoeff
                ) -> bool {
                    return thisCoeff == otherCoeff;
                }
            );
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        bool
        MatrixInterface<TDerived>::operator!=(const MatrixInterface<TOtherDerived>& other) const {
            return binaryAny(
                other,
                [] (
                    typename MatrixTraits<TDerived>::ScalarType thisCoeff,
                    typename MatrixTraits<TOtherDerived>::ScalarType otherCoeff
                ) -> bool {
                    return thisCoeff != otherCoeff;
                }
            );
        }

        template <class TDerived> template <class TOtherScalar>
        inline
        void
        MatrixInterface<TDerived>::operator*=(TOtherScalar scale) {
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    coeff(rowIndex, colIndex) *= scale;
                }
            }
        }

        template <class TDerived> template <class TOtherScalar>
        inline
        void
        MatrixInterface<TDerived>::operator/=(TOtherScalar divisor) {
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    coeff(rowIndex, colIndex) /= divisor;
                }
            }
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        void
        MatrixInterface<TDerived>::operator+=(const MatrixInterface<TOtherDerived>& other) {
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());
            
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    this->coeff(rowIndex, colIndex) += other.coeff(rowIndex, colIndex);
                }
            }
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        void
        MatrixInterface<TDerived>::operator-=(const MatrixInterface<TOtherDerived>& other) {
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());
            
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    this->coeff(rowIndex, colIndex) -= other.coeff(rowIndex, colIndex);
                }
            }
        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setConstant(typename MatrixTraits<TDerived>::ScalarType value) {
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    coeff(rowIndex, colIndex) = value;
                }
            }
        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setZero() {
            setConstant(0.0);
        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setOnes() {
            setConstant(1.0);
        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setIdentity() {
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    coeff(rowIndex, colIndex) = double(rowIndex == colIndex);
                }
            }
        }

        template <class TScalar>
        TScalar
        randomCoeff();

        template <>
        inline
        double
        randomCoeff<double>() {
            return double(std::rand()) / RAND_MAX;
        }

        template <>
        inline
        Interval
        randomCoeff<Interval>() {
            return Interval::Random();
        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setRandom() {
            for (int colIndex = 0; colIndex < cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < rows(); ++rowIndex) {
                    coeff(rowIndex, colIndex) = randomCoeff<ScalarType>();
                }
            }
        }

        template <int iFirstSize, int iSecondSize>
        inline
        CheckCompatibleSizes<iFirstSize, iSecondSize>::CheckCompatibleSizes() {
        }

        template <int iFirstSize, int iSecondSize>
        inline
        CheckCompatibleSizes<iFirstSize, iSecondSize>::CheckCompatibleSizes(
            int firstSize,
            int secondSize
        ) {
            assert(firstSize == iFirstSize || iFirstSize == -1);
            assert(secondSize == iSecondSize || iSecondSize == -1);
            assert(firstSize == secondSize);
        }

        template <int iFirstRows, int iSecondRows>
        inline
        CheckCompatibleRows<iFirstRows, iSecondRows>::CheckCompatibleRows() {
        }

        template <int iFirstRows, int iSecondRows>
        inline
        CheckCompatibleRows<iFirstRows, iSecondRows>::CheckCompatibleRows(
            int firstRows,
            int secondRows
        ) : CheckCompatibleSizes<iFirstRows, iSecondRows>(firstRows, secondRows) {
        }

        template <int iFirstCols, int iSecondCols>
        inline
        CheckCompatibleCols<iFirstCols, iSecondCols>::CheckCompatibleCols() {
        }

        template <int iFirstCols, int iSecondCols>
        inline
        CheckCompatibleCols<iFirstCols, iSecondCols>::CheckCompatibleCols(
            int firstCols,
            int secondCols
        ) : CheckCompatibleSizes<iFirstCols, iSecondCols>(firstCols, secondCols) {
        }

        template <class TFirstMatrix, class TSecondMatrix>
        inline
        CheckCompatibleMatrices<TFirstMatrix, TSecondMatrix>::CheckCompatibleMatrices() {
        }

        template <class TFirstMatrix, class TSecondMatrix>
        inline
        CheckCompatibleMatrices<TFirstMatrix, TSecondMatrix>::CheckCompatibleMatrices(
            const TFirstMatrix& firstMatrix,
            const TSecondMatrix& secondMatrix
        ) : CheckCompatibleRows<
                MatrixTraits<TFirstMatrix>::Rows,
                MatrixTraits<TSecondMatrix>::Rows
            >(firstMatrix.rows(), secondMatrix.rows()),
            CheckCompatibleCols<
                MatrixTraits<TFirstMatrix>::Cols,
                MatrixTraits<TSecondMatrix>::Cols
            >(firstMatrix.cols(), secondMatrix.cols()) {
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::Rows,
            MatrixTraits<TDerived>::Cols
        >
        operator-(const MatrixInterface<TDerived>& matrix) {
            return matrix.map(
                [] (typename MatrixTraits<TDerived>::ScalarType coeff) {
                    return -coeff;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::Rows,
            MatrixTraits<TDerived>::Cols
        >
        operator*(double scale, const MatrixInterface<TDerived>& matrix) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::ScalarType coeff) {
                    return scale * coeff;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            Interval,
            MatrixTraits<TDerived>::Rows,
            MatrixTraits<TDerived>::Cols
        >
        operator*(Interval scale, const MatrixInterface<TDerived>& matrix) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::ScalarType coeff) {
                    return scale * coeff;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::Rows,
            MatrixTraits<TDerived>::Cols
        >
        operator*(const MatrixInterface<TDerived>& matrix, double scale) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::ScalarType coeff) {
                    return coeff * scale;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            Interval,
            MatrixTraits<TDerived>::Rows,
            MatrixTraits<TDerived>::Cols
        >
        operator*(const MatrixInterface<TDerived>& matrix, Interval scale) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::ScalarType coeff) {
                    return coeff * scale;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::Rows,
            MatrixTraits<TDerived>::Cols
        >
        operator/(const MatrixInterface<TDerived>& matrix, double divisor) {
            return matrix.map(
                [divisor] (typename MatrixTraits<TDerived>::ScalarType coeff) {
                    return coeff / divisor;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            Interval,
            MatrixTraits<TDerived>::Rows,
            MatrixTraits<TDerived>::Cols
        >
        operator/(const MatrixInterface<TDerived>& matrix, Interval divisor) {
            return matrix.map(
                [divisor] (typename MatrixTraits<TDerived>::ScalarType coeff) {
                    return coeff / divisor;
                }
            );
        }

        template <class TFirstDerived, class TSecondDerived>
        inline
        const Matrix<
            typename CommonScalar<TFirstDerived, TSecondDerived>::Type,
            CommonRows<TFirstDerived, TSecondDerived>::Value,
            CommonCols<TFirstDerived, TSecondDerived>::Value
        >
        operator+(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        ) {
            return firstMatrix.binaryMap(
                secondMatrix,
                [] (
                    typename MatrixTraits<TFirstDerived>::ScalarType firstCoeff,
                    typename MatrixTraits<TSecondDerived>::ScalarType secondCoeff
                ) {
                    return firstCoeff + secondCoeff;
                }
            );
        }

        template <class TFirstDerived, class TSecondDerived>
        inline
        const Matrix<
            typename CommonScalar<TFirstDerived, TSecondDerived>::Type,
            CommonRows<TFirstDerived, TSecondDerived>::Value,
            CommonCols<TFirstDerived, TSecondDerived>::Value
        >
        operator-(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        ) {
            return firstMatrix.binaryMap(
                secondMatrix,
                [] (
                    typename MatrixTraits<TFirstDerived>::ScalarType firstCoeff,
                    typename MatrixTraits<TSecondDerived>::ScalarType secondCoeff
                ) {
                    return firstCoeff - secondCoeff;
                }
            );
        }

        template <class TFirstDerived, class TSecondDerived>
        const Matrix<
            typename CommonScalar<TFirstDerived, TSecondDerived>::Type,
            MatrixTraits<TFirstDerived>::Rows,
            MatrixTraits<TSecondDerived>::Cols
        >
        operator*(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        ) {
            typedef typename MatrixTraits<TFirstDerived>::ScalarType FirstScalarType;
            typedef typename MatrixTraits<TSecondDerived>::ScalarType SecondScalarType;
            typedef typename CommonScalar<TFirstDerived, TSecondDerived>::Type ResultScalarType;

            CheckCompatibleSizes<
                MatrixTraits<TFirstDerived>::Cols,
                MatrixTraits<TSecondDerived>::Rows
            >(firstMatrix.cols(), secondMatrix.rows());

            Matrix<
                ResultScalarType,
                MatrixTraits<TFirstDerived>::Rows,
                MatrixTraits<TSecondDerived>::Cols
            > result(firstMatrix.rows(), secondMatrix.cols());

            ResultScalarType* resultPtr = result.data();
            const FirstScalarType* rowStart = firstMatrix.data();
            const SecondScalarType* colStart = secondMatrix.data();
            for (int colIndex = 0; colIndex < result.cols(); ++colIndex) {
                for (int rowIndex = 0; rowIndex < result.rows(); ++rowIndex) {
                    const FirstScalarType* rowPtr = rowStart;
                    const SecondScalarType* colPtr = colStart;
                    *resultPtr = (*rowPtr) * (*colPtr);
                    for (int innerIndex = 1; innerIndex < firstMatrix.cols(); ++innerIndex) {
                        rowPtr += firstMatrix.colStride();
                        ++colPtr;
                        *resultPtr += (*rowPtr) * (*colPtr);
                    }
                    ++resultPtr;
                    ++rowStart;
                }
                rowStart = firstMatrix.data();
                colStart += secondMatrix.colStride();
            }
            return result;
        }
    }
}
