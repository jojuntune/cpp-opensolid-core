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
        MatrixInterface<TDerived>::numRows() const {
            return derived().numRows();
        }

        template <class TDerived>
        inline
        int
        MatrixInterface<TDerived>::numColumns() const {
            return derived().numColumns();
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
        MatrixInterface<TDerived>::columnStride() const {
            return derived().columnStride();
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::component(int index) const {
            assert(index >= 0 && index < size());
            return component(index % numRows(), index / numRows());
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType&
        MatrixInterface<TDerived>::component(int index) {
            assert(index >= 0 && index < size());
            return component(index % numRows(), index / numRows());
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::component(int rowIndex, int columnIndex) const {
            assert(rowIndex >= 0 && rowIndex < numRows());
            assert(columnIndex >= 0 && columnIndex < numColumns());
            return *(data() + rowIndex + columnIndex * columnStride());
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType&
        MatrixInterface<TDerived>::component(int rowIndex, int columnIndex) {
            assert(rowIndex >= 0 && rowIndex < numRows());
            assert(columnIndex >= 0 && columnIndex < numColumns());
            return *(data() + rowIndex + columnIndex * columnStride());
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::operator()(int index) const {
            return component(index);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType&
        MatrixInterface<TDerived>::operator()(int index) {
            return component(index);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::operator()(int rowIndex, int columnIndex) const {
            return component(rowIndex, columnIndex);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType&
        MatrixInterface<TDerived>::operator()(int rowIndex, int columnIndex) {
            return component(rowIndex, columnIndex);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::value() const {
            assert(numRows() == 1 && numColumns() == 1);
            return component(0);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType&
        MatrixInterface<TDerived>::value() {
            assert(numRows() == 1 && numColumns() == 1);
            return component(0);
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        void
        MatrixInterface<TDerived>::operator=(const MatrixInterface<TOtherDerived>& other) {
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());

            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    this->component(rowIndex, columnIndex) = other.component(rowIndex, columnIndex);
                }
            }
        }

        template <class TDerived>
        inline
        const MatrixView<
            const typename MatrixTraits<TDerived>::PlainScalarType,
            1,
            MatrixTraits<TDerived>::NumColumns,
            MatrixTraits<TDerived>::ColumnStride
        >
        MatrixInterface<TDerived>::row(int rowIndex) const {
            typedef const typename MatrixTraits<TDerived>::PlainScalarType ConstScalarType;

            assert(rowIndex >= 0 && rowIndex < numRows());

            return MatrixView<ConstScalarType, 1, NumColumns, ColumnStride>(
                data() + rowIndex,
                1,
                numColumns(),
                columnStride()
            );
        }

        template <class TDerived>
        inline
        MatrixView<
            typename MatrixTraits<TDerived>::ScalarType,
            1,
            MatrixTraits<TDerived>::NumColumns,
            MatrixTraits<TDerived>::ColumnStride
        >
        MatrixInterface<TDerived>::row(int rowIndex) {
            assert(rowIndex >= 0 && rowIndex < numRows());

            return MatrixView<
                typename MatrixTraits<TDerived>::ScalarType,
                1,
                NumColumns,
                ColumnStride
            >(
                data() + rowIndex,
                1,
                numColumns(),
                columnStride()
            );
        }

        template <class TDerived>
        inline
        const MatrixView<
            const typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumRows,
            1,
            MatrixTraits<TDerived>::ColumnStride
        >
        MatrixInterface<TDerived>::column(int columnIndex) const {
            typedef const typename MatrixTraits<TDerived>::PlainScalarType ConstScalarType;

            assert(columnIndex >= 0 && columnIndex < numColumns());
            
            return MatrixView<ConstScalarType, NumRows, 1, ColumnStride>(
                data() + columnIndex * columnStride(),
                numRows(),
                1,
                columnStride()
            );
        }

        template <class TDerived>
        inline
        MatrixView<
            typename MatrixTraits<TDerived>::ScalarType,
            MatrixTraits<TDerived>::NumRows,
            1,
            MatrixTraits<TDerived>::ColumnStride
        >
        MatrixInterface<TDerived>::column(int columnIndex) {
            assert(columnIndex >= 0 && columnIndex < numColumns());

            return MatrixView<
                typename MatrixTraits<TDerived>::ScalarType,
                NumRows,
                1,
                ColumnStride
            >(
                data() + columnIndex * columnStride(),
                numRows(),
                1,
                columnStride()
            );
        }

        template <class TDerived> template <int iBlockRows, int iBlockCols>
        const MatrixView<
            const typename MatrixTraits<TDerived>::PlainScalarType,
            iBlockRows,
            iBlockCols,
            MatrixTraits<TDerived>::ColumnStride
        >
        MatrixInterface<TDerived>::block(int startRow, int startCol) const {
            return MatrixView<
                const typename MatrixTraits<TDerived>::PlainScalarType,
                iBlockRows,
                iBlockCols,
                MatrixTraits<TDerived>::ColumnStride
            >(
                data() + startCol * columnStride() + startRow,
                iBlockRows,
                iBlockCols,
                columnStride()
            );
        }

        template <class TDerived> template <int iBlockRows, int iBlockCols>
        MatrixView<
            typename MatrixTraits<TDerived>::ScalarType,
            iBlockRows,
            iBlockCols,
            MatrixTraits<TDerived>::ColumnStride
        >
        MatrixInterface<TDerived>::block(int startRow, int startCol) {
            return MatrixView<
                typename MatrixTraits<TDerived>::ScalarType,
                iBlockRows,
                iBlockCols,
                MatrixTraits<TDerived>::ColumnStride
            >(
                data() + startCol * columnStride() + startRow,
                iBlockRows,
                iBlockCols,
                columnStride()
            );

        }

        template <class TDerived>
        const MatrixView<
            const typename MatrixTraits<TDerived>::PlainScalarType,
            -1,
            -1,
            MatrixTraits<TDerived>::ColumnStride
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
                MatrixTraits<TDerived>::ColumnStride
            >(
                data() + startCol * columnStride() + startRow,
                blockRows,
                blockCols,
                columnStride()
            );
        }

        template <class TDerived>
        MatrixView<
            typename MatrixTraits<TDerived>::ScalarType,
            -1,
            -1,
            MatrixTraits<TDerived>::ColumnStride
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
                MatrixTraits<TDerived>::ColumnStride
            >(
                data() + startCol * columnStride() + startRow,
                blockRows,
                blockCols,
                columnStride()
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumColumns,
            MatrixTraits<TDerived>::NumRows
        >
        MatrixInterface<TDerived>::transpose() const {
            Matrix<PlainScalarType, NumColumns, NumRows> result(numColumns(), numRows());
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    result.component(columnIndex, rowIndex) =
                        this->component(rowIndex, columnIndex);
                }
            }
            return result;
        }

        template <class TDerived>
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::determinant() const {
            return MatrixDeterminantFunction<
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumColumns
            >()(derived());
        }

        template <class TDerived>
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumColumns,
            MatrixTraits<TDerived>::NumRows
        >
        MatrixInterface<TDerived>::inverse() const {
            return MatrixInverseFunction<
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TDerived>::NumColumns
            >()(derived());
        }

        template <class TDerived> template <class TUnaryFunction>
        inline
        const typename MappedMatrixType<TUnaryFunction, TDerived>::Type
        MatrixInterface<TDerived>::map(TUnaryFunction unaryFunction) const {
            typename MappedMatrixType<TUnaryFunction, TDerived>::Type result(
                numRows(),
                numColumns()
            );
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

            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    result.component(rowIndex, columnIndex) = unaryFunction(
                        this->component(rowIndex, columnIndex)
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
            >::Type result(numRows(), numColumns());
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

            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    result.component(rowIndex, columnIndex) = binaryFunction(
                        this->component(rowIndex, columnIndex),
                        other.component(rowIndex, columnIndex)
                    );
                }
            }
        }

        template <class TDerived> template <class TValue, class TFunction>
        inline
        const TValue
        MatrixInterface<TDerived>::fold(TValue initialValue, TFunction function) const {
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    initialValue = function(initialValue, component(rowIndex, columnIndex));
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
            
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    initialValue = function(
                        initialValue,
                        this->component(rowIndex, columnIndex),
                        other.component(rowIndex, columnIndex)
                    );
                }
            }
            return initialValue;
        }

        template <class TDerived> template <class TFunction>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::reduce(TFunction function) const {
            ScalarType result = component(0, 0);
            int rowIndex = 1;
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (; rowIndex < numRows(); ++rowIndex) {
                    result = function(result, component(rowIndex, columnIndex));
                }
                rowIndex = 0;
            }
            return result;
        }

        template <class TDerived> template <class TUnaryPredicate>
        inline
        bool
        MatrixInterface<TDerived>::any(TUnaryPredicate unaryPredicate) const {
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    if (unaryPredicate(component(rowIndex, columnIndex))) {
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

            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    if (
                        binaryPredicate(
                            this->component(rowIndex, columnIndex),
                            other.component(rowIndex, columnIndex)
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
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    if (!unaryPredicate(component(rowIndex, columnIndex))) {
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

            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    if (
                        !binaryPredicate(
                            this->component(rowIndex, columnIndex),
                            other.component(rowIndex, columnIndex)
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
                [value, precision] (ScalarType component) -> bool {
                    return component - value == opensolid::Zero(precision);
                }
            );
        }

        template <class TDerived>
        inline
        bool
        MatrixInterface<TDerived>::isZero(double precision) const {
            return all(
                [precision] (ScalarType component) -> bool {
                    return component == opensolid::Zero(precision);
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
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    double expected = double(rowIndex == columnIndex);
                    if (component(rowIndex, columnIndex) - expected != opensolid::Zero(precision)) {
                        return false;
                    }
                }
            }
            return true;
        }

        inline
        double
        componentLowerBound(double component) {
            return component;
        }

        inline
        double
        componentLowerBound(Interval component) {
            return component.lowerBound();
        }

        template <class TDerived>
        inline
        const Matrix<double, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        MatrixInterface<TDerived>::cwiseLowerBound() const {
            return map(
                [] (ScalarType component) -> double {
                    return componentLowerBound(component);
                }
            );
        }

        inline
        double
        componentUpperBound(double component) {
            return component;
        }

        inline
        double
        componentUpperBound(Interval component) {
            return component.upperBound();
        }

        template <class TDerived>
        inline
        const Matrix<double, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        MatrixInterface<TDerived>::cwiseUpperBound() const {
            return map(
                [] (ScalarType component) -> double {
                    return componentUpperBound(component);
                }
            );
        }

        inline
        double
        componentWidth(double component) {
            return 0.0;
        }

        inline
        double
        componentWidth(Interval component) {
            return component.width();
        }

        template <class TDerived>
        inline
        const Matrix<double, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        MatrixInterface<TDerived>::cwiseWidth() const {
            return map(
                [] (ScalarType component) -> double {
                    return componentWidth(component);
                }
            );
        }

        inline
        double
        componentMedian(double component) {
            return component;
        }

        inline
        double
        componentMedian(Interval component) {
            return component.median();
        }

        template <class TDerived>
        inline
        const Matrix<double, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        MatrixInterface<TDerived>::cwiseMedian() const {
            return map(
                [] (ScalarType component) -> double {
                    return componentMedian(component);
                }
            );
        }

        inline
        double
        componentSquared(double component) {
            return component * component;
        }

        inline
        Interval
        componentSquared(Interval component) {
            return component.squared();
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        MatrixInterface<TDerived>::cwiseSquared() const {
            return map(
                [] (ScalarType component) -> ScalarType {
                    return componentSquared(component);
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
        componentHull(double firstCoeff, double secondCoeff) {
            return Interval::Hull(firstCoeff, secondCoeff);
        }

        inline
        Interval
        componentHull(double firstCoeff, Interval secondCoeff) {
            return secondCoeff.hull(firstCoeff);
        }

        inline
        Interval
        componentHull(Interval firstCoeff, double secondCoeff) {
            return firstCoeff.hull(secondCoeff);
        }

        inline
        Interval
        componentHull(Interval firstCoeff, Interval secondCoeff) {
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
                    return componentHull(thisCoeff, otherCoeff);
                }
            );
        }

        inline
        Interval
        componentIntersection(double firstCoeff, double secondCoeff) {
            return firstCoeff - secondCoeff == Zero() ?
                Interval(firstCoeff + 0.5 * (secondCoeff - firstCoeff)) :
                Interval::Empty();
        }

        inline
        Interval
        componentIntersection(double firstCoeff, Interval secondCoeff) {
            return secondCoeff.contains(firstCoeff) ?
                Interval(firstCoeff) :
                Interval::Empty();
        }

        inline
        Interval
        componentIntersection(Interval firstCoeff, double secondCoeff) {
            return firstCoeff.contains(secondCoeff) ?
                Interval(secondCoeff) :
                Interval::Empty();
        }

        inline
        Interval
        componentIntersection(Interval firstCoeff, Interval secondCoeff) {
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
                    return componentIntersection(thisCoeff, otherCoeff);
                }
            );
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::sum() const {
            return reduce(
                [] (ScalarType result, ScalarType component) {
                    return result + component;
                }
            );
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixInterface<TDerived>::product() const {
            return reduce(
                [] (ScalarType result, ScalarType component) {
                    return result * component;
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
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    component(rowIndex, columnIndex) *= scale;
                }
            }
        }

        template <class TDerived> template <class TOtherScalar>
        inline
        void
        MatrixInterface<TDerived>::operator/=(TOtherScalar divisor) {
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    component(rowIndex, columnIndex) /= divisor;
                }
            }
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        void
        MatrixInterface<TDerived>::operator+=(const MatrixInterface<TOtherDerived>& other) {
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());
            
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    this->component(rowIndex, columnIndex) +=
                        other.component(rowIndex, columnIndex);
                }
            }
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        void
        MatrixInterface<TDerived>::operator-=(const MatrixInterface<TOtherDerived>& other) {
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());
            
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    this->component(rowIndex, columnIndex) -=
                        other.component(rowIndex, columnIndex);
                }
            }
        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setConstant(typename MatrixTraits<TDerived>::ScalarType value) {
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    component(rowIndex, columnIndex) = value;
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
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    component(rowIndex, columnIndex) = double(rowIndex == columnIndex);
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
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    component(rowIndex, columnIndex) = randomCoeff<ScalarType>();
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
                MatrixTraits<TFirstMatrix>::NumRows,
                MatrixTraits<TSecondMatrix>::NumRows
            >(firstMatrix.numRows(), secondMatrix.numRows()),
            CheckCompatibleCols<
                MatrixTraits<TFirstMatrix>::NumColumns,
                MatrixTraits<TSecondMatrix>::NumColumns
            >(firstMatrix.numColumns(), secondMatrix.numColumns()) {
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator-(const MatrixInterface<TDerived>& matrix) {
            return matrix.map(
                [] (typename MatrixTraits<TDerived>::ScalarType component) {
                    return -component;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator*(double scale, const MatrixInterface<TDerived>& matrix) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::ScalarType component) {
                    return scale * component;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            Interval,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator*(Interval scale, const MatrixInterface<TDerived>& matrix) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::ScalarType component) {
                    return scale * component;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator*(const MatrixInterface<TDerived>& matrix, double scale) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::ScalarType component) {
                    return component * scale;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            Interval,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator*(const MatrixInterface<TDerived>& matrix, Interval scale) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::ScalarType component) {
                    return component * scale;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            typename MatrixTraits<TDerived>::PlainScalarType,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator/(const MatrixInterface<TDerived>& matrix, double divisor) {
            return matrix.map(
                [divisor] (typename MatrixTraits<TDerived>::ScalarType component) {
                    return component / divisor;
                }
            );
        }

        template <class TDerived>
        inline
        const Matrix<
            Interval,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator/(const MatrixInterface<TDerived>& matrix, Interval divisor) {
            return matrix.map(
                [divisor] (typename MatrixTraits<TDerived>::ScalarType component) {
                    return component / divisor;
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
            MatrixTraits<TFirstDerived>::NumRows,
            MatrixTraits<TSecondDerived>::NumColumns
        >
        operator*(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        ) {
            typedef typename MatrixTraits<TFirstDerived>::ScalarType FirstScalarType;
            typedef typename MatrixTraits<TSecondDerived>::ScalarType SecondScalarType;
            typedef typename CommonScalar<TFirstDerived, TSecondDerived>::Type ResultScalarType;

            CheckCompatibleSizes<
                MatrixTraits<TFirstDerived>::NumColumns,
                MatrixTraits<TSecondDerived>::NumRows
            >(firstMatrix.numColumns(), secondMatrix.numRows());

            Matrix<
                ResultScalarType,
                MatrixTraits<TFirstDerived>::NumRows,
                MatrixTraits<TSecondDerived>::NumColumns
            > result(firstMatrix.numRows(), secondMatrix.numColumns());

            ResultScalarType* resultPtr = result.data();
            const FirstScalarType* rowStart = firstMatrix.data();
            const SecondScalarType* colStart = secondMatrix.data();
            for (int columnIndex = 0; columnIndex < result.numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < result.numRows(); ++rowIndex) {
                    const FirstScalarType* rowPtr = rowStart;
                    const SecondScalarType* colPtr = colStart;
                    *resultPtr = (*rowPtr) * (*colPtr);
                    for (int innerIndex = 1; innerIndex < firstMatrix.numColumns(); ++innerIndex) {
                        rowPtr += firstMatrix.columnStride();
                        ++colPtr;
                        *resultPtr += (*rowPtr) * (*colPtr);
                    }
                    ++resultPtr;
                    ++rowStart;
                }
                rowStart = firstMatrix.data();
                colStart += secondMatrix.columnStride();
            }
            return result;
        }
    }
}
