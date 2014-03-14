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

#include <OpenSolid/Core/Matrix/MatrixBase.definitions.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Matrix/Unroll.hpp>

#include <cstdlib>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        MatrixBase<TScalar, iNumRows, iNumColumns>::MatrixBase() :
            _components() {
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        MatrixBase<TScalar, iNumRows, iNumColumns>::MatrixBase(const TScalar* sourcePtr) {
            TScalar* dataPtr = data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    *dataPtr = *sourcePtr;
                    ++sourcePtr;
                    ++dataPtr;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::component(std::int64_t index) const {
            assert(index >= 0 && index < Size);

            return *(data() + index);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar&
        MatrixBase<TScalar, iNumRows, iNumColumns>::component(std::int64_t index) {
            assert(index >= 0 && index < Size);

            return *(data() + index);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::component(
            std::int64_t rowIndex,
            std::int64_t columnIndex
        ) const {
            assert(rowIndex >= 0 && rowIndex < iNumRows);
            assert(columnIndex >= 0 && columnIndex < iNumColumns);

            return component(columnIndex * iNumRows + rowIndex);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar&
        MatrixBase<TScalar, iNumRows, iNumColumns>::component(
            std::int64_t rowIndex,
            std::int64_t columnIndex
        ) {
            assert(rowIndex >= 0 && rowIndex < iNumRows);
            assert(columnIndex >= 0 && columnIndex < iNumColumns);

            return component(columnIndex * iNumRows + rowIndex);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator()(std::int64_t index) const {
            return component(index);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar&
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator()(std::int64_t index) {
            return component(index);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator()(
            std::int64_t rowIndex,
            std::int64_t columnIndex
        ) const {
            return component(rowIndex, columnIndex);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar&
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator()(
            std::int64_t rowIndex,
            std::int64_t columnIndex
        ) {
            return component(rowIndex, columnIndex);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, 1, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::row(std::int64_t rowIndex) const {
            assert(rowIndex >= 0 && rowIndex < iNumRows);

            Matrix<TScalar, 1, iNumColumns> result;
            const TScalar* dataPtr = data() + rowIndex;
            TScalar* resultDataPtr = result.data();
            Unroll<iNumColumns>(
                [&] (std::int64_t index) {
                    *resultDataPtr = *dataPtr;
                    dataPtr += iNumRows;
                    ++resultDataPtr;
                }
            );
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, 1>
        MatrixBase<TScalar, iNumRows, iNumColumns>::column(std::int64_t columnIndex) const {
            assert(columnIndex >= 0 && columnIndex < iNumColumns);
            
            Matrix<TScalar, iNumRows, 1> result;
            const TScalar* dataPtr = data() + columnIndex * iNumRows;
            TScalar* resultDataPtr = result.data();
            Unroll<iNumRows>(
                [&] (std::int64_t index) {
                    *resultDataPtr = *dataPtr;
                    ++dataPtr;
                    ++resultDataPtr;
                }
            );
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar*
        MatrixBase<TScalar, iNumRows, iNumColumns>::data() const {
            return _components;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar*
        MatrixBase<TScalar, iNumRows, iNumColumns>::data() {
            return _components;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumColumns, iNumRows>
        MatrixBase<TScalar, iNumRows, iNumColumns>::transpose() const {
            Matrix<TScalar, iNumColumns, iNumRows> result;
            const TScalar* dataPtr = data();
            TScalar* resultDataPtr = result.data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    std::int64_t row = index % iNumRows;
                    std::int64_t column = index / iNumRows;
                    resultDataPtr[column + row * iNumColumns] = dataPtr[index];
                }
            );
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TUnaryFunction>
        inline
        const typename MappedMatrixType<
            TUnaryFunction,
            TScalar,
            iNumRows,
            iNumColumns
        >::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::map(TUnaryFunction unaryFunction) const {
            typename MappedMatrixType<
                TUnaryFunction,
                TScalar,
                iNumRows,
                iNumColumns
            >::Type result;
            const TScalar* dataPtr = data();
            typename MappedScalarType<
                TUnaryFunction,
                TScalar
            >::Type* resultDataPtr = result.data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    *resultDataPtr = unaryFunction(*dataPtr);
                    ++dataPtr;
                    ++resultDataPtr;
                }
            );
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        template <class TBinaryFunction, class TOtherScalar>
        inline
        const typename PairwiseMappedMatrixType<
            TBinaryFunction,
            TScalar,
            TOtherScalar,
            iNumRows,
            iNumColumns
        >::Type
        MatrixBase<TScalar, iNumRows, iNumColumns>::binaryMap(
            const Matrix<TOtherScalar, iNumRows, iNumColumns>& other,
            TBinaryFunction binaryFunction
        ) const {
            typename PairwiseMappedMatrixType<
                TBinaryFunction,
                TScalar,
                TOtherScalar,
                iNumRows,
                iNumColumns
            >::Type result;
            const TScalar* dataPtr = data();
            const TOtherScalar* otherDataPtr = other.data();
            typename PairwiseMappedScalarType<
                TBinaryFunction,
                TScalar, TOtherScalar
            >::Type* resultDataPtr = result.data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    *resultDataPtr = binaryFunction(*dataPtr, *otherDataPtr);
                    ++dataPtr;
                    ++otherDataPtr;
                    ++resultDataPtr;
                }
            );
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        template <class TValue, class TFunction>
        inline
        const TValue
        MatrixBase<TScalar, iNumRows, iNumColumns>::fold(
            TValue initialValue,
            TFunction function
        ) const {
            const TScalar* dataPtr = data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    initialValue = function(initialValue, *dataPtr);
                    ++dataPtr;
                }
            );
            return initialValue;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        template <class TValue, class TOtherScalar, class TFunction>
        inline
        const TValue
        MatrixBase<TScalar, iNumRows, iNumColumns>::binaryFold(
            const Matrix<TOtherScalar, iNumRows, iNumColumns>& other,
            TValue initialValue,
            TFunction function
        ) const {
            const TScalar* dataPtr = data();
            const TOtherScalar* otherDataPtr = other.data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    initialValue = function(initialValue, *dataPtr, *otherDataPtr);
                    ++dataPtr;
                    ++otherDataPtr;
                }
            );
            return initialValue;
        }


        template <class TScalar, int iNumRows, int iNumColumns> template <class TFunction>
        TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::reduce(TFunction function) const {
            const TScalar* dataPtr = data();
            TScalar result = *data();
            Unroll<Size - 1>(
                [&] (std::int64_t index) {
                    ++dataPtr;
                    result = function(result, *dataPtr);
                }
            );
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TUnaryPredicate>
        inline
        bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::any(TUnaryPredicate unaryPredicate) const {
            const TScalar* dataPtr = data();
            const TScalar* endPtr = data() + Size;
            for (; dataPtr != endPtr; ++dataPtr) {
                if (unaryPredicate(*dataPtr)) {
                    return true;
                }
            }
            return false;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        template <class TBinaryPredicate, class TOtherScalar>
        inline
        bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::binaryAny(
            const Matrix<TOtherScalar, iNumRows, iNumColumns>& other,
            TBinaryPredicate binaryPredicate
        ) const {
            const TScalar* dataPtr = data();
            const TScalar* endPtr = data() + Size;
            const TOtherScalar* otherDataPtr = other.data();
            for (; dataPtr != endPtr; ++dataPtr, ++otherDataPtr) {
                if (binaryPredicate(*dataPtr, *otherDataPtr)) {
                    return true;
                }
            }
            return false;
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TUnaryPredicate>
        inline
        bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::all(TUnaryPredicate unaryPredicate) const {
            const TScalar* dataPtr = data();
            const TScalar* endPtr = data() + Size;
            for (; dataPtr != endPtr; ++dataPtr) {
                if (!unaryPredicate(*dataPtr)) {
                    return false;
                }
            }
            return true;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        template <class TBinaryPredicate, class TOtherScalar>
        inline
        bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::binaryAll(
            const Matrix<TOtherScalar, iNumRows, iNumColumns>& other,
            TBinaryPredicate binaryPredicate
        ) const {
            const TScalar* dataPtr = data();
            const TScalar* endPtr = data() + Size;
            const TOtherScalar* otherDataPtr = other.data();
            for (; dataPtr != endPtr; ++dataPtr, ++otherDataPtr) {
                if (!binaryPredicate(*dataPtr, *otherDataPtr)) {
                    return false;
                }
            }
            return true;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::isZero(double precision) const {
            return all(
                [precision] (TScalar component) -> bool {
                    return component == opensolid::Zero(precision);
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::isIdentity(double precision) const {
            const TScalar* dataPtr = data();
            for (std::int64_t columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
                for (std::int64_t rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                    if (*dataPtr - int(rowIndex == columnIndex) != opensolid::Zero()) {
                        return false;
                    }
                    ++dataPtr;
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

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<double, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::cwiseLowerBound() const {
            return map(
                [] (TScalar component) -> double {
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

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<double, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::cwiseUpperBound() const {
            return map(
                [] (TScalar component) -> double {
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

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<double, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::cwiseWidth() const {
            return map(
                [] (TScalar component) -> double {
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

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<double, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::cwiseMedian() const {
            return map(
                [] (TScalar component) -> double {
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

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::cwiseSquared() const {
            return map(
                [] (TScalar component) -> TScalar {
                    return componentSquared(component);
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherScalar>
        inline
        const Matrix<decltype(TScalar() * TOtherScalar()), iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::cwiseProduct(
            const Matrix<TOtherScalar, iNumRows, iNumColumns>& other
        ) const {
            return binaryMap(
                other,
                [] (TScalar component, TOtherScalar otherComponent) {
                    return component * otherComponent;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherScalar>
        inline
        const Matrix<decltype(TScalar() / TOtherScalar()), iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::cwiseQuotient(
            const Matrix<TOtherScalar, iNumRows, iNumColumns>& other
        ) const {
            return binaryMap(
                other,
                [] (TScalar component, TOtherScalar otherComponent) {
                    return component / otherComponent;
                }
            );
        }

        inline
        Interval
        componentHull(double firstComponent, double secondComponent) {
            return Interval::Hull(firstComponent, secondComponent);
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

        template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherScalar>
        inline
        const Matrix<Interval, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::cwiseHull(
            const Matrix<TOtherScalar, iNumRows, iNumColumns>& other
        ) const {
            return binaryMap(
                other,
                [] (TScalar component, TOtherScalar otherComponent) -> Interval {
                    return componentHull(component, otherComponent);
                }
            );
        }

        inline
        Interval
        componentIntersection(double firstComponent, double secondComponent) {
            return firstComponent - secondComponent == Zero() ?
                Interval(firstComponent) :
                Interval::Empty();
        }

        inline
        Interval
        componentIntersection(double firstComponent, Interval secondComponent) {
            return secondComponent.contains(firstComponent) ?
                Interval(firstComponent) :
                Interval::Empty();
        }

        inline
        Interval
        componentIntersection(Interval firstComponent, double secondComponent) {
            return firstComponent.contains(secondComponent) ?
                Interval(secondComponent) :
                Interval::Empty();
        }

        inline
        Interval
        componentIntersection(Interval firstComponent, Interval secondComponent) {
            return firstComponent.intersection(secondComponent);
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherScalar>
        inline
        const Matrix<Interval, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::cwiseIntersection(
            const Matrix<TOtherScalar, iNumRows, iNumColumns>& other
        ) const {
            return binaryMap(
                other,
                [] (TScalar component, TOtherScalar otherComponent) -> Interval {
                    return componentIntersection(component, otherComponent);
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::sum() const {
            return reduce(
                [] (TScalar result, TScalar component) {
                    return result + component;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar
        MatrixBase<TScalar, iNumRows, iNumColumns>::product() const {
            return reduce(
                [] (TScalar result, TScalar component) {
                    return result * component;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator==(
            const Matrix<TScalar, iNumRows, iNumColumns>& other
        ) const {
            return binaryAll(
                other,
                [] (TScalar component, TScalar otherComponent) -> bool {
                    return component == otherComponent;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        bool
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator!=(
            const Matrix<TScalar, iNumRows, iNumColumns>& other
        ) const {
            return binaryAny(
                other,
                [] (TScalar component, TScalar otherComponent) -> bool {
                    return component != otherComponent;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherScalar>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator*=(TOtherScalar scale) {
            TScalar* dataPtr = data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    *dataPtr *= scale;
                    ++dataPtr;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherScalar>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator/=(TOtherScalar divisor) {
            TScalar* dataPtr = data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    *dataPtr /= divisor;
                    ++dataPtr;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherScalar>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator+=(
            const Matrix<TOtherScalar, iNumRows, iNumColumns>& other
        ) const {
            TScalar* dataPtr = data();
            const TOtherScalar* otherDataPtr = other.data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    *dataPtr += *otherDataPtr;
                    ++dataPtr;
                    ++otherDataPtr;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherScalar>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::operator-=(
            const Matrix<TOtherScalar, iNumRows, iNumColumns>& other
        ) const {
            TScalar* dataPtr = data();
            const TOtherScalar* otherDataPtr = other.data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    *dataPtr -= *otherDataPtr;
                    ++dataPtr;
                    ++otherDataPtr;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::setConstant(TScalar value) {
            TScalar* dataPtr = data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    *dataPtr = value;
                    ++dataPtr;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::setDefault() {
            setConstant(TScalar());
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::setZero() {
            setConstant(TScalar(0));
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::setOnes() {
            setConstant(TScalar(1));
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::setIdentity() {
            setZero();
            TScalar* dataPtr = data();
            Unroll<(iNumRows <= iNumColumns) ? iNumRows : iNumColumns>(
                [&] (std::int64_t index) {
                    *dataPtr = TScalar(1);
                    dataPtr += (iNumRows + 1);
                }
            );
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
            return Interval::Random();
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::setRandom() {
            TScalar* dataPtr = data();
            Unroll<Size>(
                [&] (std::int64_t index) {
                    *dataPtr = randomComponent<TScalar>();
                    ++dataPtr;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        void
        copyColumn(const TScalar* sourcePtr, TScalar* destinationPtr) {
            Unroll<iNumRows>(
                [&] (std::int64_t index) {
                    *destinationPtr = *sourcePtr;
                    ++sourcePtr;
                    ++destinationPtr;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::setColumns(
            const Matrix<TScalar, iNumRows, 1>& firstColumn,
            const Matrix<TScalar, iNumRows, 1>& secondColumn
        ) {
            static_assert(iNumColumns == 2, "Incorrect number of columns");

            TScalar* dataPtr = data();
            copyColumn<TScalar, iNumRows, iNumColumns>(firstColumn.data(), dataPtr);
            dataPtr += iNumRows;
            copyColumn<TScalar, iNumRows, iNumColumns>(secondColumn.data(), dataPtr);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::setColumns(
            const Matrix<TScalar, iNumRows, 1>& firstColumn,
            const Matrix<TScalar, iNumRows, 1>& secondColumn,
            const Matrix<TScalar, iNumRows, 1>& thirdColumn
        ) {
            static_assert(iNumColumns == 3, "Incorrect number of columns");

            TScalar* dataPtr = data();
            copyColumn<TScalar, iNumRows, iNumColumns>(firstColumn.data(), dataPtr);
            dataPtr += iNumRows;
            copyColumn<TScalar, iNumRows, iNumColumns>(secondColumn.data(), dataPtr);
            dataPtr += iNumRows;
            copyColumn<TScalar, iNumRows, iNumColumns>(thirdColumn.data(), dataPtr);

        }

        template <class TScalar, int iNumRows, int iNumColumns>
        void
        copyRow(const TScalar* sourcePtr, TScalar* destinationPtr) {
            Unroll<iNumColumns>(
                [&] (std::int64_t index) {
                    *destinationPtr = *sourcePtr;
                    ++sourcePtr;
                    destinationPtr += iNumRows;
                }
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::setRows(
            const Matrix<TScalar, 1, iNumColumns>& firstRow,
            const Matrix<TScalar, 1, iNumColumns>& secondRow
        ) {
            static_assert(iNumRows == 2, "Incorrect number of rows");

            TScalar* dataPtr = data();
            copyRow(firstRow.data(), dataPtr);
            ++dataPtr;
            copyRow(secondRow.data(), dataPtr);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        void
        MatrixBase<TScalar, iNumRows, iNumColumns>::setRows(
            const Matrix<TScalar, 1, iNumColumns>& firstRow,
            const Matrix<TScalar, 1, iNumColumns>& secondRow,
            const Matrix<TScalar, 1, iNumColumns>& thirdRow
        ) {
            static_assert(iNumRows == 3, "Incorrect number of rows");

            TScalar* dataPtr = data();
            copyRow(firstRow.data(), dataPtr);
            ++dataPtr;
            copyRow(secondRow.data(), dataPtr);
            ++dataPtr;
            copyRow(thirdRow.data(), dataPtr);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::Constant(TScalar value) {
            Matrix<TScalar, iNumRows, iNumColumns> result;
            result.setConstant(value);
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::Zero() {
            Matrix<TScalar, iNumRows, iNumColumns> result;
            result.setZero();
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::Ones() {
            Matrix<TScalar, iNumRows, iNumColumns> result;
            result.setOnes();
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::Identity() {
            Matrix<TScalar, iNumRows, iNumColumns> result;
            result.setIdentity();
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::Random() {
            Matrix<TScalar, iNumRows, iNumColumns> result;
            result.setRandom();
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::FromColumns(
            const Matrix<TScalar, iNumRows, 1>& firstColumn,
            const Matrix<TScalar, iNumRows, 1>& secondColumn
        ) {
            static_assert(iNumColumns == 2, "Incorrect number of columns");

            Matrix<TScalar, iNumRows, iNumColumns> result;
            result.setColumns(firstColumn, secondColumn);
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::FromColumns(
            const Matrix<TScalar, iNumRows, 1>& firstColumn,
            const Matrix<TScalar, iNumRows, 1>& secondColumn,
            const Matrix<TScalar, iNumRows, 1>& thirdColumn
        ) {
            static_assert(iNumColumns == 3, "Incorrect number of columns");

            Matrix<TScalar, iNumRows, iNumColumns> result;
            result.setColumns(firstColumn, secondColumn, thirdColumn);
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::FromRows(
            const Matrix<TScalar, 1, iNumColumns>& firstRow,
            const Matrix<TScalar, 1, iNumColumns>& secondRow
        ) {
            static_assert(iNumRows == 2, "Incorrect number of rows");

            Matrix<TScalar, iNumRows, iNumColumns> result;
            result.setRows(firstRow, secondRow);
            return result;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const Matrix<TScalar, iNumRows, iNumColumns>
        MatrixBase<TScalar, iNumRows, iNumColumns>::FromRows(
            const Matrix<TScalar, 1, iNumColumns>& firstRow,
            const Matrix<TScalar, 1, iNumColumns>& secondRow,
            const Matrix<TScalar, 1, iNumColumns>& thirdRow
        ) {
            static_assert(iNumRows == 3, "Incorrect number of rows");

            Matrix<TScalar, iNumRows, iNumColumns> result;
            result.setRows(firstRow, secondRow, thirdRow);
            return result;
        }
    }
}
