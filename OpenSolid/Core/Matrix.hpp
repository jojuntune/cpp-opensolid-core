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

#include <OpenSolid/Core/Matrix.definitions.hpp>

#if 1

#include <cstdlib>

namespace opensolid
{
    template <int iNumRows, int iNumColumns>
    inline
    Matrix<iNumRows, iNumColumns>::Matrix() :
        MatrixBase<iNumRows, iNumColumns>() {

        setZero();
    }

    inline
    Matrix1d::Matrix() :
        MatrixBase<1, 1>() {

        component(0) = 0.0;
    }

    inline
    Matrix1d::Matrix(double value) :
        MatrixBase<1, 1>() {

        component(0) = value;
    }

    inline
    const double
    Matrix1d::value() const {
        return component(0);
    }

    inline
    double&
    Matrix1d::value() {
        return component(0);
    }

    inline
    const double
    Matrix1d::determinant() const {
        return value();
    }

    inline
    const Matrix1d
    Matrix1d::inverse() const {
        if (value() == Zero()) {
            assert(false);
            return Matrix1d(0.0);
        }
        return Matrix1d(1.0 / value());
    }

    inline
    Matrix2d::Matrix() :
        MatrixBase<2, 2>() {

        setZero();
    }

    inline
    Matrix2d::Matrix(double a, double b, double c, double d) :
        MatrixBase<2, 2>() {

        component(0) = a;
        component(1) = c;
        component(2) = b;
        component(3) = d;
    }

    inline
    double
    Matrix2d::determinant() const {
        return component(0) * component(3) - component(2) * component(1);
    }

    inline
    const Matrix2d
    Matrix2d::inverse() const {
        double determinant = this->determinant();
        if (determinant == Zero()) {
            assert(false);
            return Matrix2d();
        }
        double reciprocal = 1.0 / determinant;
        return Matrix2d(
            reciprocal * component(3),
            -reciprocal * component(2),
            -reciprocal * component(1),
            reciprocal * component(0)
        );
    }

    inline
    Matrix3d::Matrix() :
        MatrixBase<3, 3>() {

        setZero();
    }

    inline
    Matrix3d::Matrix(
        double a11,
        double a12,
        double a13,
        double a21,
        double a22,
        double a23,
        double a31,
        double a32,
        double a33
    ) : MatrixBase<3, 3>() {

        component(0) = a11;
        component(1) = a21;
        component(2) = a31;
        component(3) = a12;
        component(4) = a22;
        component(5) = a32;
        component(6) = a13;
        component(7) = a23;
        component(8) = a33;
    }

    inline
    ColumnMatrix2d::Matrix() :
        MatrixBase<2, 1>() {

        component(0) = 0.0;
        component(1) = 0.0;
    }

    inline
    ColumnMatrix2d::Matrix(double x, double y) :
        MatrixBase<2, 1>() {

        component(0) = x;
        component(1) = y;
    }

    inline
    ColumnMatrix3d::Matrix() :
        MatrixBase<3, 1>() {

        component(0) = 0.0;
        component(1) = 0.0;
        component(2) = 0.0;
    }

    inline
    ColumnMatrix3d::Matrix(double x, double y, double z) :
        MatrixBase<3, 1>() {

        component(0) = x;
        component(1) = y;
        component(2) = z;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator*(double scale, const Matrix<iNumRows, iNumColumns>& matrix) {
        Matrix<iNumRows, iNumColumns> result(matrix);
        result *= scale;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator*(const Matrix<iNumRows, iNumColumns>& matrix, double scale) {
        Matrix<iNumRows, iNumColumns> result(matrix);
        result *= scale;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, iNumColumns>
    operator/(const Matrix<iNumRows, iNumColumns>& matrix, double divisor) {
        if (divisor == Zero()) {
            assert(false);
            return Matrix<iNumRows, iNumColumns>();
        }
        Matrix<iNumRows, iNumColumns> result(matrix);
        result *= (1.0 / divisor);
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, int iNumColumns>
    operator+(
        const Matrix<iNumRows, iNumColumns>& firstMatrix,
        const Matrix<iNumRows, iNumColumns>& secondMatrix
    ) {
        Matrix<iNumRows, int iNumColumns> result(firstMatrix);
        result += secondMatrix;
        return result;
    }

    template <int iNumRows, int iNumColumns>
    const Matrix<iNumRows, int iNumColumns>
    operator-(
        const Matrix<iNumRows, iNumColumns>& firstMatrix,
        const Matrix<iNumRows, iNumColumns>& secondMatrix
    ) {
        Matrix<iNumRows, int iNumColumns> result(firstMatrix);
        result -= secondMatrix;
        return result;
    }

    template <int iNumRows, int iNumColumns, int iInnerSize>
    const Matrix<iNumRows, int iNumColumns>
    operator*(
        const Matrix<iNumRows, iInnerSize>& firstMatrix,
        const Matrix<iInnerSize, iNumColumns>& secondMatrix
    ) {
        Matrix<iNumRows, iNumColumns> result;
        for (int columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
            for (int rowIndex = 0; rowIndex < iNumRows; ++rowIndex) {
                double& component = result(rowIndex, columnIndex);
                for (int innerIndex = 0; innerIndex < iInnerSize; ++innerIndex) {
                    component += firstMatrix(rowIndex, innerIndex) *
                        secondMatrix(innerIndex, columnIndex);
                }
            }
        }
        return result;
    }

    template <>
    inline
    const Matrix<1, 1>
    operator*(const Matrix<1, 1>& matrix, const Matrix<1, 1>& columnMatrix) {
        return Matrix1d(matrix.value() * columnMatrix.value());
    }

    template <>
    inline
    const Matrix<1, 1>
    operator*(const Matrix<1, 2>& matrix, const Matrix<2, 1>& columnMatrix) {
        return Matrix1d(matrix(0, 0) * columnMatrix(0) + matrix(0, 1) * columnMatrix(1));
    }

    template <>
    inline
    const Matrix<1, 1>
    operator*(const Matrix<1, 3>& matrix, const Matrix<3, 1>& columnMatrix) {
        return Matrix1d(
            matrix(0, 0) * columnMatrix(0) + matrix(0, 1) * columnMatrix(1) +
                matrix(0, 2) * columnMatrix(2)
        );
    }

    template <>
    inline
    const Matrix<2, 1>
    operator*(const Matrix<2, 1>& matrix, const Matrix<1, 1>& columnMatrix) {
        return ColumnMatrix2d(matrix(0, 0) * columnMatrix(0), matrix(1, 0) * columnMatrix(0));
    }

    template <>
    inline
    const Matrix<2, 1>
    operator*(const Matrix<2, 2>& matrix, const Matrix<2, 1>& columnMatrix) {
        return ColumnMatrix2d(
            matrix(0, 0) * columnMatrix(0) + matrix.component(0, 1) * columnMatrix(1),
            matrix(1, 0) * columnMatrix(0) + matrix.component(1, 1) * columnMatrix(1)
        );
    }

    template <>
    inline
    const Matrix<2, 1>
    operator*(const Matrix<2, 3>& matrix, const Matrix<3, 1>& columnMatrix) {
        return ColumnMatrix2d(
            matrix(0, 0) * columnMatrix(0) + matrix(0, 1) * columnMatrix(1) +
                matrix(0, 2) * columnMatrix(2),
            matrix(1, 0) * columnMatrix(0) + matrix(1, 1) * columnMatrix(1) +
                matrix(1, 2) * columnMatrix(2)
        );
    }

    template <>
    inline
    const Matrix<3, 1>
    operator*(const Matrix<3, 1>& matrix, const Matrix<1, 1>& columnMatrix) {
        return ColumnMatrix3d(
            matrix(0, 0) * columnMatrix(0),
            matrix(1, 0) * columnMatrix(0),
            matrix(2, 0) * columnMatrix(0)
        );
    }

    template <>
    inline
    const Matrix<3, 1>
    operator*(const Matrix<3, 2>& matrix, const Matrix<2, 1>& columnMatrix) {
        return ColumnMatrix3d(
            matrix(0, 0) * columnMatrix(0) + matrix.component(0, 1) * columnMatrix(1),
            matrix(1, 0) * columnMatrix(0) + matrix.component(1, 1) * columnMatrix(1),
            matrix(2, 0) * columnMatrix(0) + matrix.component(2, 1) * columnMatrix(1)
        );
    }

    template <>
    inline
    const Matrix<3, 1>
    operator*(const Matrix<3, 3>& matrix, const Matrix<3, 1>& columnMatrix) {
        return ColumnMatrix3d(
            matrix(0, 0) * columnMatrix(0) + matrix(0, 1) * columnMatrix(1) +
                matrix(0, 2) * columnMatrix(2),
            matrix(1, 0) * columnMatrix(0) + matrix(1, 1) * columnMatrix(1) +
                matrix(1, 2) * columnMatrix(2, 0),
            matrix(2, 0) * columnMatrix(0) + matrix(2, 1) * columnMatrix(1) +
                matrix(2, 2) * columnMatrix(2)
        );
    }
}

#else

#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix/ContainOperation.hpp>
#include <OpenSolid/Core/Matrix/EmptyOperation.hpp>
#include <OpenSolid/Core/Matrix/HullOperation.hpp>
#include <OpenSolid/Core/Matrix/IntersectionOperation.hpp>
#include <OpenSolid/Core/Matrix/LowerOperation.hpp>
#include <OpenSolid/Core/Matrix/MatrixIterator.hpp>
#include <OpenSolid/Core/Matrix/MedianOperation.hpp>
#include <OpenSolid/Core/Matrix/OverlapOperation.hpp>
#include <OpenSolid/Core/Matrix/RandomOperation.hpp>
#include <OpenSolid/Core/Matrix/StrictContainOperation.hpp>
#include <OpenSolid/Core/Matrix/StrictOverlapOperation.hpp>
#include <OpenSolid/Core/Matrix/UpperOperation.hpp>
#include <OpenSolid/Core/Matrix/WidthOperation.hpp>
#include <OpenSolid/Core/Mirror.hpp>
#include <OpenSolid/Core/Projection.hpp>
#include <OpenSolid/Core/Rotation.hpp>

namespace Eigen
{
    template <class TDerived>
    inline
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::scaledAbout(
        const opensolid::Point<NumDimensions>& originPoint,
        double scale
    ) const {
        return scaling(derived(), scale);
    }

    template <class TDerived> template <class TVector>
    inline
    const TDerived&
    MatrixBase<TDerived>::translatedBy(const EigenBase<TVector>& vector) const {
        return derived();
    }

    template <class TDerived>
    inline
    const TDerived&
    MatrixBase<TDerived>::translatedAlong(
        const opensolid::Axis<NumDimensions>& axis,
        double distance
    ) const {
        return derived();
    }

    template <class TDerived>
    inline
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotatedAbout(const opensolid::Point<2>& originPoint, double angle) const {
        return opensolid::Rotation2d(originPoint, angle)(derived());
    }

    template <class TDerived>
    inline
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotatedAbout(const opensolid::Axis<3>& axis, double angle) const {
        return opensolid::Rotation3d(axis, angle)(derived());
    }

    template <class TDerived>
    inline
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::mirroredAbout(const opensolid::Axis<2>& axis) const {
        return opensolid::Mirror2d(axis)(derived());
    }

    template <class TDerived>
    inline
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::mirroredAbout(const opensolid::Plane3d& plane) const {
        return opensolid::Mirror3d(plane)(derived());
    }

    template <class TDerived>
    inline
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projectedOnto(const opensolid::Axis<2>& axis) const {
        return opensolid::Projection2d(axis)(derived());
    }

    template <class TDerived>
    inline
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projectedOnto(const opensolid::Axis<3>& axis) const {
        return opensolid::Projection3d(axis)(derived());
    }

    template <class TDerived>
    inline
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projectedOnto(const opensolid::Plane3d& plane) const {
        return opensolid::Projection3d(plane)(derived());
    }

    template <class TDerived>
    inline
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::transformed(
        const opensolid::LinearTransformation<NumDimensions>& transformation
    ) const {
        return transformation(derived());
    }

    template <class TDerived>
    template <int iNumResultDimensions, int iNumAxes>
    inline
    Matrix<
        typename internal::traits<TDerived>::Scalar,
        iNumResultDimensions,
        internal::traits<TDerived>::ColsAtCompileTime
    >
    MatrixBase<TDerived>::transplanted(
        const opensolid::CoordinateSystem<
            NumDimensions,
            iNumAxes
        >& sourceCoordinateSystem,
        const opensolid::CoordinateSystem<
            iNumResultDimensions,
            iNumAxes
        >& destinationCoordinateSystem
    ) const {
        return destinationCoordinateSystem * (derived() / sourceCoordinateSystem);
    }

    template <class TDerived> template <int iNumResultDimensions>
    inline
    Matrix<
        typename internal::traits<TDerived>::Scalar,
        iNumResultDimensions,
        internal::traits<TDerived>::ColsAtCompileTime
    >
    MatrixBase<TDerived>::transplanted(
        const opensolid::Transplant<NumDimensions, iNumResultDimensions>& transplant
    ) const {
        return transplant(derived());
    }

    template<class TDerived> template <class TOther>
    TOther
    MatrixBase<TDerived>::to() const {
        return opensolid::ConversionFunction<PlainObject, TOther>()(derived());
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::operator%(
        const Matrix& other
    ) const {
        return this->cross(other);
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    typename Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::Scalar
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::operator|(
        const Matrix& other
    ) const {
        return this->dot(other);
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    template <class TFunction>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::apply(
        const TFunction& function
    ) const {
        return this->unaryExpr(function);
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>&
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::vectorize(const Scalar& value) {
        this->fill(value);
        return *this;
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    typename Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::Scalar
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::length() const {
        return this->norm();
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    typename Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::Scalar
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::sqrnorm() const {
        return this->squaredNorm();
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>&
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::normalize() {
        MatrixBase<Matrix>::normalize();
        return *this;
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>&
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::normalize_cond() {
        if (!this->isZero()) {
            this->normalize();
        }
        return *this;
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    typename Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::Scalar
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::l1_norm() const {
        return this->template lpNorm<1>();
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    typename Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::Scalar
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::l8_norm() const {
        return this->template lpNorm<Eigen::Infinity>();
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    typename Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::Scalar
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::max() const {
        return this->maxCoeff();   
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    typename Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::Scalar
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::max_abs() const {
        return this->cwiseAbs().maxCoeff();
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    typename Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::Scalar
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::min() const {
        return this->minCoeff();
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    typename Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::Scalar
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::min_abs() const {
        return this->cwiseAbs().minCoeff();
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    typename Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::Scalar
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::mean_abs() const {
        return this->cwiseAbs().mean();
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>&
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::minimize(const Matrix& other) {
        *this = this->cwiseMin(other);
        return *this;
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    bool
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::minimized(const Matrix& other) {
        bool result = false;
        auto minimizer = [&result] (TScalar value, TScalar otherValue) -> TScalar {
            if (otherValue < value) {
                result = true;
                return otherValue;
            } else {
                return value;
            }
        };
        *this = this->binaryExpr(other, minimizer);
        return result;
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>&
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::maximize(const Matrix& other) {
        *this = this->cwiseMax(other);
        return *this;
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    bool
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::maximized(const Matrix& other) {
        bool result = false;
        auto maximizer = [&result] (TScalar value, TScalar otherValue) -> TScalar {
            if (otherValue > value) {
                result = true;
                return otherValue;
            } else {
                return value;
            }
        };
        *this = this->binaryExpr(other, maximizer);
        return result;
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::min(const Matrix& other) const {
        return this->cwiseMin(other);
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::max(const Matrix& other) const {
        return this->cwiseMax(other);
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::vectorized(const Scalar& value) {
        return Constant(value);
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    template <class TOther>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::From(const TOther& other) {
        return opensolid::ConversionFunction<TOther, Matrix>()(other);
    }

    template <class TDerived>
    inline
    bool
    DenseBase<TDerived>::isEmpty() const {
        return derived().unaryExpr(EmptyOperation()).any();
    }
    
    template <class TDerived>
    inline
    CwiseUnaryOp<LowerOperation, const TDerived>
    DenseBase<TDerived>::cwiseLower() const {
        return derived().unaryExpr(LowerOperation());
    }

    template <class TDerived>
    inline
    CwiseUnaryOp<UpperOperation, const TDerived>
    DenseBase<TDerived>::cwiseUpper() const {
        return derived().unaryExpr(UpperOperation());
    }

    template <class TDerived>
    inline
    CwiseUnaryOp<MedianOperation, const TDerived>
    DenseBase<TDerived>::cwiseMedian() const {
        return derived().unaryExpr(MedianOperation());
    }

    template <class TDerived>
    inline
    CwiseUnaryOp<RandomOperation, const TDerived>
    DenseBase<TDerived>::cwiseRandom() const {
        return derived().unaryExpr(RandomOperation());
    }

    template <class TDerived>
    inline
    CwiseUnaryOp<WidthOperation, const TDerived>
    DenseBase<TDerived>::cwiseWidth() const {
        return derived().unaryExpr(WidthOperation());
    }

    template <class TDerived> template<class TOther>
    inline
    bool
    DenseBase<TDerived>::overlaps(const DenseBase<TOther>& other, double precision) const {
        return derived().binaryExpr(other.derived(), OverlapOperation(precision)).all();
    }

    template <class TDerived> template<class TOther>
    inline
    bool
    DenseBase<TDerived>::strictlyOverlaps(const DenseBase<TOther>& other, double precision) const {
        return derived().binaryExpr(other.derived(), StrictOverlapOperation(precision)).all();
    }

    template <class TDerived> template<class TOther>
    inline
    bool
    DenseBase<TDerived>::contains(const DenseBase<TOther>& other, double precision) const {
        return derived().binaryExpr(other.derived(), ContainOperation(precision)).all();
    }

    template <class TDerived> template<class TOther>
    inline
    bool
    DenseBase<TDerived>::strictlyContains(const DenseBase<TOther>& other, double precision) const {
        return derived().binaryExpr(other.derived(), StrictContainOperation(precision)).all();
    }

    template <class TDerived> template <class TOther>
    inline
    CwiseBinaryOp<HullOperation, const TDerived, const TOther>
    DenseBase<TDerived>::hull(const DenseBase<TOther>& other) const {
        return derived().binaryExpr(other.derived(), HullOperation());
    }

    template <class TDerived> template <class TOther>
    inline
    CwiseBinaryOp<IntersectionOperation, const TDerived, const TOther>
    DenseBase<TDerived>::intersection(const DenseBase<TOther>& other) const {
        return derived().binaryExpr(other.derived(), IntersectionOperation());
    }

    template <class TDerived>
    inline
    const typename DenseBase<TDerived>::RandomAccessLinSpacedReturnType
    DenseBase<TDerived>::LinSpaced(
        typename DenseBase<TDerived>::Index size,
        opensolid::Interval interval
    ) {
        return LinSpaced(size, Scalar(interval.lowerBound()), Scalar(interval.upperBound()));
    }

    template <class TDerived>
    inline
    const typename DenseBase<TDerived>::RandomAccessLinSpacedReturnType
    DenseBase<TDerived>::LinSpaced(opensolid::Interval interval) {
        return LinSpaced(Scalar(interval.lowerBound()), Scalar(interval.upperBound()));
    }

    template <class TDerived> template <class TFirst, class TSecond>
    inline
    CwiseBinaryOp<HullOperation, const TFirst, const TSecond>
    DenseBase<TDerived>::Hull(const DenseBase<TFirst>& first, const DenseBase<TSecond>& second) {
        return first.hull(second);
    }

    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType
    DenseBase<TDerived>::Empty() {
        return Constant(opensolid::Interval::Empty());
    }
    
    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType
    DenseBase<TDerived>::Empty(typename DenseBase<TDerived>::Index size) {
        return Constant(size, opensolid::Interval::Empty());
    }
    
    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType
    DenseBase<TDerived>::Empty(
        typename DenseBase<TDerived>::Index rows,
        typename DenseBase<TDerived>::Index cols
    ) {
        return Constant(rows, cols, opensolid::Interval::Empty());
    }

    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType
    DenseBase<TDerived>::Whole() {
        return Constant(opensolid::Interval::Whole());
    }
    
    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType
    DenseBase<TDerived>::Whole(typename DenseBase<TDerived>::Index size) {
        return Constant(size, opensolid::Interval::Whole());
    }
    
    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType
    DenseBase<TDerived>::Whole(
        typename DenseBase<TDerived>::Index rows,
        typename DenseBase<TDerived>::Index cols
    ) {
        return Constant(rows, cols, opensolid::Interval::Whole());
    }

    namespace internal
    {
        inline
        int
        significant_decimals_default_impl<opensolid::Interval, false>::run() {
            return 17;
        }

        template <>
        struct random_impl<opensolid::Interval>
        {
            static opensolid::Interval
            run(
                const opensolid::Interval& lowerInterval,
                const opensolid::Interval& upperInterval
            ) {
                opensolid::Interval interval(
                    lowerInterval.lowerBound(),
                    upperInterval.upperBound()
                );
                double firstRatio = double(std::rand()) / RAND_MAX;
                double secondRatio = double(std::rand()) / RAND_MAX;
                return interval.interpolated(opensolid::Interval::Hull(firstRatio, secondRatio));
            }

            static opensolid::Interval
            run() {
                double lower = -1 + 2 * double(std::rand()) / RAND_MAX;
                double upper = -1 + 2 * double(std::rand()) / RAND_MAX;
                return opensolid::Interval::Hull(lower, upper);
            }
        };
    }

    inline
    opensolid::Interval
    NumTraits<opensolid::Interval>::epsilon() {
        return std::numeric_limits<double>::epsilon();
    }
    
    inline
    opensolid::Interval
    NumTraits<opensolid::Interval>::dummy_precision() {
        return 1e-12;
    }
    
    inline
    opensolid::Interval
    NumTraits<opensolid::Interval>::lowest() {
        return std::numeric_limits<double>::min();
    }
    
    inline
    opensolid::Interval
    NumTraits<opensolid::Interval>::highest() {
        return std::numeric_limits<double>::max();
    }
    
    template <class TDerived, int iNumAxes>
    inline
    Matrix<typename TDerived::Scalar, iNumAxes, TDerived::ColsAtCompileTime>
    operator/(
        const EigenBase<TDerived>& matrix,
        const opensolid::CoordinateSystem<TDerived::RowsAtCompileTime, iNumAxes>& coordinateSystem
    ) {
        return coordinateSystem.inverseMatrix() * matrix.derived();
    }

    template <class TDerived, int iNumDimensions>
    inline
    Matrix<typename TDerived::Scalar, iNumDimensions, TDerived::ColsAtCompileTime>
    operator*(
        const opensolid::CoordinateSystem<
            iNumDimensions,
            TDerived::RowsAtCompileTime
        >& coordinateSystem,
        const EigenBase<TDerived>& matrix
    ) {
        return coordinateSystem.basisMatrix() * matrix.derived();
    }

    inline
    double
    dot(const Vector3d& firstVector, const Vector3d& secondVector) {
        return firstVector.dot(secondVector);
    }

    inline
    float
    dot(const Vector3f& firstVector, const Vector3f& secondVector) {
        return firstVector.dot(secondVector);
    }

    inline
    Vector3d
    cross(const Vector3d& firstVector, const Vector3d& secondVector) {
        return firstVector.cross(secondVector);
    }

    inline
    Vector3f
    cross(const Vector3f& firstVector, const Vector3f& secondVector) {
        return firstVector.cross(secondVector);
    }
}

namespace opensolid
{
    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    inline
    bool
    EqualityFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>::operator()(
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& firstMatrix,
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& secondMatrix,
        double precision
    ) const {
        return (firstMatrix - secondMatrix).isZero(precision);
    }

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    inline
    typename BoundsFunction< Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>::CastType
    BoundsFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>::operator()(
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& matrix
    ) const {
        return matrix.template cast<Interval>();
    }
    
    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    inline
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    ScalingFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>::operator()(
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
        double scale
    ) const {
        return TScalar(scale) * argument;
    }

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    template <class TVector>
    inline
    const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>&
    TranslationFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>::operator()(
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
        const EigenBase<TVector>& vector
    ) const {
        return argument;
    }

    template <
        class TScalar,
        int iRows,
        int iCols,
        int iOptions,
        int iMaxRows,
        int iMaxCols,
        int iNumResultDimensions
    >
    template <class TMatrix>
    inline
    Matrix<TScalar, iNumResultDimensions, iCols, iOptions, iNumResultDimensions, iMaxCols>
    TransformationFunction<
        Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>,
        iNumResultDimensions
    >::operator()(
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
        const EigenBase<TMatrix>& matrix
    ) const {
        return matrix.derived().template cast<TScalar>() * argument;
    }
}

#endif
