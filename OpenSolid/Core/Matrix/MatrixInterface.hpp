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

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/EigenDecomposition.hpp>
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
        char*
        MatrixInterface<TDerived>::rawPointer(
            typename MatrixTraits<TDerived>::PlainScalar* scalarPtr
        ) {
            return reinterpret_cast<char*>(scalarPtr);
        }

        template <class TDerived>
        inline
        const char*
        MatrixInterface<TDerived>::rawPointer(
            typename MatrixTraits<TDerived>::ConstScalar* scalarPtr
        ) const {
            return reinterpret_cast<const char*>(scalarPtr);
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        void
        MatrixInterface<TDerived>::assign(const MatrixInterface<TOtherDerived>& other) {
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());

            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    this->component(rowIndex, columnIndex) = other.component(rowIndex, columnIndex);
                }
            }
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ConstScalar*
        MatrixInterface<TDerived>::data() const {
            return derived().data();
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar*
        MatrixInterface<TDerived>::data() {
            return derived().data();
        }

        template <class TDerived>
        inline
        std::pair<int, int> 
        MatrixInterface<TDerived>::dimensions() const {
            return std::pair<int, int>(numRows(), numColumns());
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
        MatrixInterface<TDerived>::numComponents() const {
            return derived().numComponents();
        }

        template <class TDerived>
        inline
        int
        MatrixInterface<TDerived>::columnStrideInBytes() const {
            return derived().columnStrideInBytes();
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::component(int index) const {
            assert(index >= 0 && index < numComponents());

            return component(index % numRows(), index / numRows());
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar&
        MatrixInterface<TDerived>::component(int index) {
            assert(index >= 0 && index < numComponents());

            return component(index % numRows(), index / numRows());
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::component(int rowIndex, int columnIndex) const {
            assert(rowIndex >= 0 && rowIndex < numRows());
            assert(columnIndex >= 0 && columnIndex < numColumns());

            return *reinterpret_cast<ConstScalar*>(
                rawPointer(data()) + rowIndex * sizeof(Scalar) + columnIndex * columnStrideInBytes()
            );
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar&
        MatrixInterface<TDerived>::component(int rowIndex, int columnIndex) {
            assert(rowIndex >= 0 && rowIndex < numRows());
            assert(columnIndex >= 0 && columnIndex < numColumns());

            return *reinterpret_cast<Scalar*>(
                rawPointer(data()) + rowIndex * sizeof(Scalar) + columnIndex * columnStrideInBytes()
            );
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::operator()(int index) const {
            return component(index);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar&
        MatrixInterface<TDerived>::operator()(int index) {
            return component(index);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::operator()(int rowIndex, int columnIndex) const {
            return component(rowIndex, columnIndex);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar&
        MatrixInterface<TDerived>::operator()(int rowIndex, int columnIndex) {
            return component(rowIndex, columnIndex);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::value() const {
            CheckCompatibleRows<NumRows, 1>(numRows(), 1);
            CheckCompatibleColumns<NumColumns, 1>(numColumns(), 1);

            return component(0);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::Scalar&
        MatrixInterface<TDerived>::value() {
            CheckCompatibleRows<NumRows, 1>(numRows(), 1);
            CheckCompatibleColumns<NumColumns, 1>(numColumns(), 1);

            return component(0);
        }

        template <class TDerived>
        inline
        const MatrixView<
            typename MatrixTraits<TDerived>::ConstScalar,
            1,
            MatrixTraits<TDerived>::NumColumns,
            MatrixTraits<TDerived>::ColumnStrideInBytes
        >
        MatrixInterface<TDerived>::row(int rowIndex) const {
            assert(rowIndex >= 0 && rowIndex < numRows());

            return MatrixView<ConstScalar, 1, NumColumns, ColumnStrideInBytes>(
                data() + rowIndex,
                1,
                numColumns(),
                columnStrideInBytes()
            );
        }

        template <class TDerived>
        inline
        MatrixView<
            typename MatrixTraits<TDerived>::Scalar,
            1,
            MatrixTraits<TDerived>::NumColumns,
            MatrixTraits<TDerived>::ColumnStrideInBytes
        >
        MatrixInterface<TDerived>::row(int rowIndex) {
            assert(rowIndex >= 0 && rowIndex < numRows());

            return MatrixView<Scalar, 1, NumColumns, ColumnStrideInBytes>(
                data() + rowIndex,
                1,
                numColumns(),
                columnStrideInBytes()
            );
        }

        template <class TDerived>
        inline
        const MatrixView<
            typename MatrixTraits<TDerived>::ConstScalar,
            MatrixTraits<TDerived>::NumRows,
            1,
            MatrixTraits<TDerived>::ColumnStrideInBytes
        >
        MatrixInterface<TDerived>::column(int columnIndex) const {
            assert(columnIndex >= 0 && columnIndex < numColumns());
            
            return MatrixView<ConstScalar, NumRows, 1, ColumnStrideInBytes>(
                reinterpret_cast<ConstScalar*>(
                    rawPointer(data()) + columnIndex * columnStrideInBytes()
                ),
                numRows(),
                1,
                columnStrideInBytes()
            );
        }

        template <class TDerived>
        inline
        MatrixView<
            typename MatrixTraits<TDerived>::Scalar,
            MatrixTraits<TDerived>::NumRows,
            1,
            MatrixTraits<TDerived>::ColumnStrideInBytes
        >
        MatrixInterface<TDerived>::column(int columnIndex) {
            assert(columnIndex >= 0 && columnIndex < numColumns());

            return MatrixView<Scalar, NumRows, 1, ColumnStrideInBytes>(
                reinterpret_cast<Scalar*>(
                    rawPointer(data()) + columnIndex * columnStrideInBytes()
                ),
                numRows(),
                1,
                columnStrideInBytes()
            );
        }

        template <class TDerived> template <int iBlockRows, int iBlockColumns>
        const MatrixView<
            typename MatrixTraits<TDerived>::ConstScalar,
            iBlockRows,
            iBlockColumns,
            MatrixTraits<TDerived>::ColumnStrideInBytes
        >
        MatrixInterface<TDerived>::block(int startRow, int startColumn) const {
            return MatrixView<ConstScalar, iBlockRows, iBlockColumns, ColumnStrideInBytes>(
                reinterpret_cast<ConstScalar*>(
                    rawPointer(data()) +
                    startRow * sizeof(Scalar) +
                    startColumn * columnStrideInBytes()
                ),
                iBlockRows,
                iBlockColumns,
                columnStrideInBytes()
            );
        }

        template <class TDerived> template <int iBlockRows, int iBlockColumns>
        MatrixView<
            typename MatrixTraits<TDerived>::Scalar,
            iBlockRows,
            iBlockColumns,
            MatrixTraits<TDerived>::ColumnStrideInBytes
        >
        MatrixInterface<TDerived>::block(int startRow, int startColumn) {
            return MatrixView<Scalar, iBlockRows, iBlockColumns, ColumnStrideInBytes>(
                reinterpret_cast<Scalar*>(
                    rawPointer(data()) +
                    startRow * sizeof(Scalar) +
                    startColumn * columnStrideInBytes()
                ),
                iBlockRows,
                iBlockColumns,
                columnStrideInBytes()
            );

        }

        template <class TDerived>
        const MatrixView<
            typename MatrixTraits<TDerived>::ConstScalar,
            -1,
            -1,
            MatrixTraits<TDerived>::ColumnStrideInBytes
        >
        MatrixInterface<TDerived>::block(
            int startRow,
            int startColumn,
            int blockRows,
            int blockColumns
        ) const {
            return MatrixView<ConstScalar, -1, -1, ColumnStrideInBytes>(
                reinterpret_cast<ConstScalar*>(
                    rawPointer(data()) +
                    startRow * sizeof(Scalar) +
                    startColumn * columnStrideInBytes()
                ),
                blockRows,
                blockColumns,
                columnStrideInBytes()
            );
        }

        template <class TDerived>
        MatrixView<
            typename MatrixTraits<TDerived>::Scalar,
            -1,
            -1,
            MatrixTraits<TDerived>::ColumnStrideInBytes
        >
        MatrixInterface<TDerived>::block(
            int startRow,
            int startColumn,
            int blockRows,
            int blockColumns
        ) {
            return MatrixView<Scalar, -1, -1, ColumnStrideInBytes>(
                reinterpret_cast<Scalar*>(
                    rawPointer(data()) +
                    startRow * sizeof(Scalar) +
                    startColumn * columnStrideInBytes()
                ),
                blockRows,
                blockColumns,
                columnStrideInBytes()
            );
        }

        template <class TDerived>
        inline
        MatrixView<
            const typename MatrixTraits<TDerived>::Scalar,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns,
            MatrixTraits<TDerived>::ColumnStrideInBytes
        >
        MatrixInterface<TDerived>::view() const {
            return MatrixView<ConstScalar, NumRows, NumColumns, ColumnStrideInBytes>(
                data(),
                numRows(),
                numColumns(),
                columnStrideInBytes()
            );
        }

        template <class TDerived>
        inline
        MatrixView<
            typename MatrixTraits<TDerived>::Scalar,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns,
            MatrixTraits<TDerived>::ColumnStrideInBytes
        >
        MatrixInterface<TDerived>::view() {
            return MatrixView<Scalar, NumRows, NumColumns, ColumnStrideInBytes>(
                data(),
                numRows(),
                numColumns(),
                columnStrideInBytes()
            );
        }

        template <class TDerived>
        inline
        Matrix<
            typename MatrixTraits<TDerived>::PlainScalar,
            MatrixTraits<TDerived>::NumColumns,
            MatrixTraits<TDerived>::NumRows
        >
        MatrixInterface<TDerived>::transpose() const {
            Matrix<PlainScalar, NumColumns, NumRows> result(
                std::pair<int, int>(numColumns(), numRows())
            );
            result.setTranspose(*this);
            return result;
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::determinant() const {
            return MatrixDeterminantFunction<
                CommonSize<
                    MatrixTraits<TDerived>::NumRows,
                    MatrixTraits<TDerived>::NumColumns
                >::Value
            >()(derived());
        }

        template <class TDerived>
        inline
        Matrix<
            typename MatrixTraits<TDerived>::PlainScalar,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        MatrixInterface<TDerived>::inverse() const {
            return MatrixInverseFunction<
                CommonSize<
                    MatrixTraits<TDerived>::NumRows,
                    MatrixTraits<TDerived>::NumColumns
                >::Value
            >()(derived());
        }

        template <class TDerived>
        inline
        EigenDecomposition<MatrixTraits<TDerived>::NumRows>
        MatrixInterface<TDerived>::eigenDecomposition() const {
            assert(numRows() == numColumns());
            return EigenDecomposition<
                CommonSize<
                    MatrixTraits<TDerived>::NumRows,
                    MatrixTraits<TDerived>::NumColumns
                >::Value
            >(derived());
        }


        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::minComponent() const {
            return minComponent(nullptr, nullptr);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::minComponent(int* indexPtr) const {
            if (indexPtr) {
                int rowIndex = 0;
                int columnIndex = 0;
                double result = minComponent(&rowIndex, &columnIndex);
                *indexPtr = columnIndex * numRows() + rowIndex;
                return result;
            } else {
                return minComponent(nullptr, nullptr);
            }
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::minComponent(int* rowIndexPtr, int* columnIndexPtr) const {
            static_assert(
                std::is_same<PlainScalar, double>::value,
                "minComponent() only defined for double-valued matrices (ambiguous for Interval)"
            );
            double result = component(0, 0);
            if (rowIndexPtr) {
                *rowIndexPtr = 0;
            }
            if (columnIndexPtr) {
                *columnIndexPtr = 0;
            }
            int rowIndex = 1;
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (; rowIndex < numRows(); ++rowIndex) {
                    double candidate = component(rowIndex, columnIndex);
                    if (candidate < result) {
                        result = candidate;
                        if (rowIndexPtr) {
                            *rowIndexPtr = rowIndex;
                        }
                        if (columnIndexPtr) {
                            *columnIndexPtr = columnIndex;
                        }
                    }
                }
                rowIndex = 0;
            }
            return result;
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::maxComponent() const {
            return maxComponent(nullptr, nullptr);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::maxComponent(int* indexPtr) const {
            if (indexPtr) {
                int rowIndex = 0;
                int columnIndex = 0;
                double result = maxComponent(&rowIndex, &columnIndex);
                *indexPtr = columnIndex * numRows() + rowIndex;
                return result;
            } else {
                return maxComponent(nullptr, nullptr);
            }
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::maxComponent(int* rowIndexPtr, int* columnIndexPtr) const {
            static_assert(
                std::is_same<PlainScalar, double>::value,
                "maxComponent() only defined for double-valued matrices (ambiguous for Interval)"
            );
            double result = component(0, 0);
            if (rowIndexPtr) {
                *rowIndexPtr = 0;
            }
            if (columnIndexPtr) {
                *columnIndexPtr = 0;
            }
            int rowIndex = 1;
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (; rowIndex < numRows(); ++rowIndex) {
                    double candidate = component(rowIndex, columnIndex);
                    if (candidate > result) {
                        result = candidate;
                        if (rowIndexPtr) {
                            *rowIndexPtr = rowIndex;
                        }
                        if (columnIndexPtr) {
                            *columnIndexPtr = columnIndex;
                        }
                    }
                }
                rowIndex = 0;
            }
            return result;
        }

        template <class TDerived> template <class TUnaryFunction>
        inline
        typename MappedMatrixType<TUnaryFunction, TDerived>::Type
        MatrixInterface<TDerived>::map(TUnaryFunction unaryFunction) const {
            typename MappedMatrixType<TUnaryFunction, TDerived>::Type result(dimensions());
            result.setMap(*this, unaryFunction);
            return result;
        }

        template <class TDerived> template <class TOtherDerived, class TBinaryFunction>
        inline
        typename PairwiseMappedMatrixType<TBinaryFunction, TDerived, TOtherDerived>::Type
        MatrixInterface<TDerived>::binaryMap(
            const MatrixInterface<TOtherDerived>& other,
            TBinaryFunction binaryFunction
        ) const {
            typename PairwiseMappedMatrixType<
                TBinaryFunction,
                TDerived,
                TOtherDerived
            >::Type result(dimensions());
            result.setBinaryMap(*this, other, binaryFunction);
            return result;
        }

        template <class TDerived> template <class TValue, class TFunction>
        inline
        TValue
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
        TValue
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
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::reduce(TFunction function) const {
            Scalar result = component(0, 0);
            int rowIndex = 1;
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (; rowIndex < numRows(); ++rowIndex) {
                    result = function(result, component(rowIndex, columnIndex));
                }
                rowIndex = 0;
            }
            return result;
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::sum() const {
            return reduce(
                [] (Scalar result, Scalar component) {
                    return result + component;
                }
            );
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalar
        MatrixInterface<TDerived>::product() const {
            return reduce(
                [] (Scalar result, Scalar component) {
                    return result * component;
                }
            );
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

        template <class TDerived> template <class TOtherDerived, class TBinaryPredicate>
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

        template <class TDerived> template <class TOtherDerived, class TBinaryPredicate>
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
                [value, precision] (Scalar component) -> bool {
                    return component - value == opensolid::Zero(precision);
                }
            );
        }

        template <class TDerived>
        inline
        bool
        MatrixInterface<TDerived>::isZero(double precision) const {
            return all(
                [precision] (Scalar component) -> bool {
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
        Matrix<double, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        MatrixInterface<TDerived>::cwiseLowerBound() const {
            return map(
                [] (Scalar component) -> double {
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
        Matrix<double, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        MatrixInterface<TDerived>::cwiseUpperBound() const {
            return map(
                [] (Scalar component) -> double {
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
        Matrix<double, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        MatrixInterface<TDerived>::cwiseWidth() const {
            return map(
                [] (Scalar component) -> double {
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
        Matrix<double, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        MatrixInterface<TDerived>::cwiseMedian() const {
            return map(
                [] (Scalar component) -> double {
                    return componentMedian(component);
                }
            );
        }

        template <class TDerived>
        inline
        Matrix<
            typename MatrixTraits<TDerived>::PlainScalar,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        MatrixInterface<TDerived>::cwiseAbs() const {
            return map(
                [] (Scalar component) -> Scalar {
                    return abs(component);
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
        Matrix<
            typename MatrixTraits<TDerived>::PlainScalar,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        MatrixInterface<TDerived>::cwiseSquared() const {
            return map(
                [] (Scalar component) -> Scalar {
                    return componentSquared(component);
                }
            );
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        Matrix<
            typename CommonScalar<TDerived, TOtherDerived>::Type,
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonColumns<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseProduct(const MatrixInterface<TOtherDerived>& other) const {
            return binaryMap(
                other,
                [] (
                    typename MatrixTraits<TDerived>::Scalar thisComponent,
                    typename MatrixTraits<TOtherDerived>::Scalar otherComponent
                ) {
                    return thisComponent * otherComponent;
                }
            );
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        Matrix<
            typename CommonScalar<TDerived, TOtherDerived>::Type,
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonColumns<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseQuotient(
            const MatrixInterface<TOtherDerived>& other
        ) const {
            return binaryMap(
                other,
                [] (
                    typename MatrixTraits<TDerived>::Scalar thisComponent,
                    typename MatrixTraits<TOtherDerived>::Scalar otherComponent
                ) {
                    return thisComponent / otherComponent;
                }
            );
        }

        inline
        Interval
        componentHull(double firstComponent, double secondComponent) {
            return Interval::hull(firstComponent, secondComponent);
        }

        inline
        Interval
        componentHull(double firstComponent, Interval secondComponent) {
            return secondComponent.hull(firstComponent);
        }

        inline
        Interval
        componentHull(Interval firstComponent, double secondComponent) {
            return firstComponent.hull(secondComponent);
        }

        inline
        Interval
        componentHull(Interval firstComponent, Interval secondComponent) {
            return firstComponent.hull(secondComponent);
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        Matrix<
            Interval,
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonColumns<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseHull(const MatrixInterface<TOtherDerived>& other) const {
            return binaryMap(
                other,
                [] (
                    typename MatrixTraits<TDerived>::Scalar thisComponent,
                    typename MatrixTraits<TOtherDerived>::Scalar otherComponent
                ) -> Interval {
                    return componentHull(thisComponent, otherComponent);
                }
            );
        }

        inline
        Interval
        componentIntersection(double firstComponent, double secondComponent) {
            return (
                firstComponent - secondComponent == Zero() ?
                Interval(firstComponent + 0.5 * (secondComponent - firstComponent)) :
                Interval::EMPTY()
            );
        }

        inline
        Interval
        componentIntersection(double firstComponent, Interval secondComponent) {
            return (
                secondComponent.contains(firstComponent) ?
                Interval(firstComponent) :
                Interval::EMPTY()
            );
        }

        inline
        Interval
        componentIntersection(Interval firstComponent, double secondComponent) {
            return (
                firstComponent.contains(secondComponent) ?
                Interval(secondComponent) :
                Interval::EMPTY()
            );
        }

        inline
        Interval
        componentIntersection(Interval firstComponent, Interval secondComponent) {
            return firstComponent.intersection(secondComponent);
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        Matrix<
            Interval,
            CommonRows<TDerived, TOtherDerived>::Value,
            CommonColumns<TDerived, TOtherDerived>::Value
        >
        MatrixInterface<TDerived>::cwiseIntersection(
            const MatrixInterface<TOtherDerived>& other
        ) const {
            return binaryMap(
                other,
                [] (
                    typename MatrixTraits<TDerived>::Scalar thisComponent,
                    typename MatrixTraits<TOtherDerived>::Scalar otherComponent
                ) -> Interval {
                    return componentIntersection(thisComponent, otherComponent);
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
                    typename MatrixTraits<TDerived>::Scalar thisComponent,
                    typename MatrixTraits<TOtherDerived>::Scalar otherComponent
                ) -> bool {
                    return thisComponent == otherComponent;
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
                    typename MatrixTraits<TDerived>::Scalar thisComponent,
                    typename MatrixTraits<TOtherDerived>::Scalar otherComponent
                ) -> bool {
                    return thisComponent != otherComponent;
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
                    this->component(rowIndex, columnIndex) += (
                        other.component(rowIndex, columnIndex)
                    );
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
                    this->component(rowIndex, columnIndex) -= (
                        other.component(rowIndex, columnIndex)
                    );
                }
            }
        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setConstant(typename MatrixTraits<TDerived>::Scalar value) {
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
        randomComponent();

        template <>
        inline
        double
        randomComponent<double>() {
            return double(std::rand()) / RAND_MAX;
        }

        template <>
        inline
        Interval
        randomComponent<Interval>() {
            return Interval::random();
        }

        template <class TDerived>
        inline
        void
        MatrixInterface<TDerived>::setRandom() {
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    component(rowIndex, columnIndex) = randomComponent<Scalar>();
                }
            }
        }
        
        template <class TDerived> template <class TOtherDerived>
        inline
        void
        MatrixInterface<TDerived>::setTranspose(
            const MatrixInterface<TOtherDerived>& other
        ) {
            CheckCompatibleSizes<
                MatrixTraits<TDerived>::NumRows, 
                MatrixTraits<TOtherDerived>::NumColumns
            >(numRows(), other.numColumns());
        
            CheckCompatibleSizes<
                MatrixTraits<TDerived>::NumColumns, 
                MatrixTraits<TOtherDerived>::NumRows
            >(numColumns(), other.numRows());
        
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    this->component(rowIndex, columnIndex) = (
                        other.component(columnIndex, rowIndex)
                    );
                }
            }
        }
        
        template <class TDerived> template <class TOtherDerived, class TUnaryFunction>
        inline
        void
        MatrixInterface<TDerived>::setMap(
            const MatrixInterface<TOtherDerived>& other,
            TUnaryFunction unaryFunction
        ) {
            CheckCompatibleMatrices<TDerived, TOtherDerived>(derived(), other.derived());

            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    this->component(rowIndex, columnIndex) = unaryFunction(
                        other.component(rowIndex, columnIndex)
                    );
                }
            }
        }
        
        template <class TDerived>
        template <class TFirstDerived, class TSecondDerived, class TBinaryFunction>
        inline
        void
        MatrixInterface<TDerived>::setBinaryMap(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix,
            TBinaryFunction binaryFunction
        ) {
            CheckCompatibleMatrices<TDerived, TFirstDerived>(derived(), firstMatrix.derived());
            CheckCompatibleMatrices<TDerived, TSecondDerived>(derived(), secondMatrix.derived());
            
            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    this->component(rowIndex, columnIndex) = binaryFunction(
                        firstMatrix.component(rowIndex, columnIndex),
                        secondMatrix.component(rowIndex, columnIndex)
                    );
                }
            }
        }
        
        template <class TDerived>
        template <class TFirstDerived, class TSecondDerived>
        inline
        void
        MatrixInterface<TDerived>::setProduct(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        ) {
            typedef typename MatrixTraits<TFirstDerived>::Scalar FirstScalarType;
            typedef typename MatrixTraits<TSecondDerived>::Scalar SecondScalarType;

            CheckCompatibleSizes<
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TFirstDerived>::NumRows
            >(numRows(), firstMatrix.numRows());
            
            CheckCompatibleSizes<
                MatrixTraits<TDerived>::NumColumns,
                MatrixTraits<TSecondDerived>::NumColumns
            >(numColumns(), secondMatrix.numColumns());
            
            CheckCompatibleSizes<
                MatrixTraits<TFirstDerived>::NumColumns,
                MatrixTraits<TSecondDerived>::NumRows
            >(firstMatrix.numColumns(), secondMatrix.numRows());

            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    Scalar& result = component(rowIndex, columnIndex);
                    result = firstMatrix(rowIndex, 0) * secondMatrix(0, columnIndex);
                    for (int innerIndex = 1; innerIndex < firstMatrix.numColumns(); ++innerIndex) {
                        result += (
                            firstMatrix(rowIndex, innerIndex) *
                            secondMatrix(innerIndex, columnIndex)
                        );
                    }
                }
            }
        }
        
        template <class TDerived>
        template <class TFirstDerived, class TSecondDerived>
        inline
        void
        MatrixInterface<TDerived>::setTransposeProduct(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        ) {
            typedef typename MatrixTraits<TFirstDerived>::Scalar FirstScalarType;
            typedef typename MatrixTraits<TSecondDerived>::Scalar SecondScalarType;

            CheckCompatibleSizes<
                MatrixTraits<TDerived>::NumRows,
                MatrixTraits<TFirstDerived>::NumColumns
            >(numRows(), firstMatrix.numColumns());
            
            CheckCompatibleSizes<
                MatrixTraits<TDerived>::NumColumns,
                MatrixTraits<TSecondDerived>::NumColumns
            >(numColumns(), secondMatrix.numColumns());
            
            CheckCompatibleSizes<
                MatrixTraits<TFirstDerived>::NumRows,
                MatrixTraits<TSecondDerived>::NumRows
            >(firstMatrix.numRows(), secondMatrix.numRows());

            for (int columnIndex = 0; columnIndex < numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < numRows(); ++rowIndex) {
                    Scalar& result = component(rowIndex, columnIndex);
                    result = firstMatrix(0, rowIndex) * secondMatrix(0, columnIndex);
                    for (int innerIndex = 1; innerIndex < firstMatrix.numRows(); ++innerIndex) {
                        result += (
                            firstMatrix(innerIndex, rowIndex) *
                            secondMatrix(innerIndex, columnIndex)
                        );
                    }
                }
            }
        }

        template <class TDerived> template <class TOtherDerived>
        inline
        Matrix<
            typename CommonScalar<TDerived, TOtherDerived>::Type,
            MatrixTraits<TDerived>::NumColumns,
            MatrixTraits<TOtherDerived>::NumColumns
        >
        MatrixInterface<TDerived>::transposeProduct(
            const MatrixInterface<TOtherDerived>& other
        ) const {
            Matrix<
                typename CommonScalar<TDerived, TOtherDerived>::Type,
                MatrixTraits<TDerived>::NumColumns,
                MatrixTraits<TOtherDerived>::NumColumns
            > result(std::pair<int, int>(this->numColumns(), other.numColumns()));

            result.setTransposeProduct(*this, other);
            return result;
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

        template <int iFirstColumns, int iSecondColumns>
        inline
        CheckCompatibleColumns<iFirstColumns, iSecondColumns>::CheckCompatibleColumns() {
        }

        template <int iFirstColumns, int iSecondColumns>
        inline
        CheckCompatibleColumns<iFirstColumns, iSecondColumns>::CheckCompatibleColumns(
            int firstColumns,
            int secondColumns
        ) : CheckCompatibleSizes<iFirstColumns, iSecondColumns>(firstColumns, secondColumns) {
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
            CheckCompatibleColumns<
                MatrixTraits<TFirstMatrix>::NumColumns,
                MatrixTraits<TSecondMatrix>::NumColumns
            >(firstMatrix.numColumns(), secondMatrix.numColumns()) {
        }

        template <class TDerived>
        inline
        Matrix<
            typename MatrixTraits<TDerived>::PlainScalar,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator-(const MatrixInterface<TDerived>& matrix) {
            return matrix.map(
                [] (typename MatrixTraits<TDerived>::Scalar component) {
                    return -component;
                }
            );
        }

        template <class TDerived>
        inline
        Matrix<
            typename MatrixTraits<TDerived>::PlainScalar,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator*(double scale, const MatrixInterface<TDerived>& matrix) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::Scalar component) {
                    return scale * component;
                }
            );
        }

        template <class TDerived>
        inline
        Matrix<Interval, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        operator*(Interval scale, const MatrixInterface<TDerived>& matrix) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::Scalar component) {
                    return scale * component;
                }
            );
        }

        template <class TDerived>
        inline
        Matrix<
            typename MatrixTraits<TDerived>::PlainScalar,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator*(const MatrixInterface<TDerived>& matrix, double scale) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::Scalar component) {
                    return component * scale;
                }
            );
        }

        template <class TDerived>
        inline
        Matrix<Interval, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        operator*(const MatrixInterface<TDerived>& matrix, Interval scale) {
            return matrix.map(
                [scale] (typename MatrixTraits<TDerived>::Scalar component) {
                    return component * scale;
                }
            );
        }

        template <class TDerived>
        inline
        Matrix<
            typename MatrixTraits<TDerived>::PlainScalar,
            MatrixTraits<TDerived>::NumRows,
            MatrixTraits<TDerived>::NumColumns
        >
        operator/(const MatrixInterface<TDerived>& matrix, double divisor) {
            return matrix.map(
                [divisor] (typename MatrixTraits<TDerived>::Scalar component) {
                    return component / divisor;
                }
            );
        }

        template <class TDerived>
        inline
        Matrix<Interval, MatrixTraits<TDerived>::NumRows, MatrixTraits<TDerived>::NumColumns>
        operator/(const MatrixInterface<TDerived>& matrix, Interval divisor) {
            return matrix.map(
                [divisor] (typename MatrixTraits<TDerived>::Scalar component) {
                    return component / divisor;
                }
            );
        }

        template <class TFirstDerived, class TSecondDerived>
        inline
        Matrix<
            typename CommonScalar<TFirstDerived, TSecondDerived>::Type,
            CommonRows<TFirstDerived, TSecondDerived>::Value,
            CommonColumns<TFirstDerived, TSecondDerived>::Value
        >
        operator+(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        ) {
            return firstMatrix.binaryMap(
                secondMatrix,
                [] (
                    typename MatrixTraits<TFirstDerived>::Scalar firstComponent,
                    typename MatrixTraits<TSecondDerived>::Scalar secondComponent
                ) {
                    return firstComponent + secondComponent;
                }
            );
        }

        template <class TFirstDerived, class TSecondDerived>
        inline
        Matrix<
            typename CommonScalar<TFirstDerived, TSecondDerived>::Type,
            CommonRows<TFirstDerived, TSecondDerived>::Value,
            CommonColumns<TFirstDerived, TSecondDerived>::Value
        >
        operator-(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        ) {
            return firstMatrix.binaryMap(
                secondMatrix,
                [] (
                    typename MatrixTraits<TFirstDerived>::Scalar firstComponent,
                    typename MatrixTraits<TSecondDerived>::Scalar secondComponent
                ) {
                    return firstComponent - secondComponent;
                }
            );
        }

        template <class TFirstDerived, class TSecondDerived>
        Matrix<
            typename CommonScalar<TFirstDerived, TSecondDerived>::Type,
            MatrixTraits<TFirstDerived>::NumRows,
            MatrixTraits<TSecondDerived>::NumColumns
        >
        operator*(
            const MatrixInterface<TFirstDerived>& firstMatrix,
            const MatrixInterface<TSecondDerived>& secondMatrix
        ) {
            typedef typename CommonScalar<TFirstDerived, TSecondDerived>::Type ResultScalarType;
        
            Matrix<
                ResultScalarType,
                MatrixTraits<TFirstDerived>::NumRows,
                MatrixTraits<TSecondDerived>::NumColumns
            > result(std::pair<int, int>(firstMatrix.numRows(), secondMatrix.numColumns()));

            result.setProduct(firstMatrix, secondMatrix);
            return result;
        }
    }
}
