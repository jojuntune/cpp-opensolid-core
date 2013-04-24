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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Matrix.definitions.hpp>

#include <OpenSolid/Core/Datum.hpp>
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
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Projection.hpp>
#include <OpenSolid/Core/Rotation.hpp>
#include <OpenSolid/Core/Transplant.hpp>

namespace Eigen
{
    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::scaled(double scale) const {
        return Scalar(scale) * derived();
    }

    template <class TDerived> template <int iNumDimensions>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::scaledAbout(
        double scale,
        const opensolid::Point<iNumDimensions>& originPoint
    ) const {
        return Scalar(scale) * derived();
    }

    template <class TDerived> template <class TVector>
    inline const TDerived&
    MatrixBase<TDerived>::translated(const EigenBase<TVector>& vector) const {
        return derived();
    }

    template <class TDerived>template <int iNumDimensions>
    inline const TDerived&
    MatrixBase<TDerived>::translatedAlong(
        double coordinateValue,
        const opensolid::Datum<iNumDimensions, 1>& axis
    ) const {
        return derived();
    }

    template <class TDerived>template <class TMatrix>
    Matrix<typename internal::traits<TDerived>::Scalar, TMatrix::RowsAtCompileTime, internal::traits<TDerived>::ColsAtCompileTime>
    MatrixBase<TDerived>::transformed(const EigenBase<TMatrix>& matrix) const {
        return matrix.derived().template cast<Scalar>() * derived();
    }

    template <class TDerived>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotated(double angle) const {
        return Matrix2d(Rotation2Dd(angle)).cast<Scalar>() * derived();
    }

    template <class TDerived>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotatedAbout(double angle, const opensolid::Point<2>& originPoint) const {
        return Matrix2d(Rotation2Dd(angle)).cast<Scalar>() * derived();

    }

    template <class TDerived>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotated(const opensolid::Rotation<2>& rotation) const {
        return rotation.transformationMatrix().cast<Scalar>() * derived();
    }

    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotatedAbout(double angle, const opensolid::Datum<3, 1>& axis) const {
        return rotated(opensolid::Rotation3d(angle, axis));
    }

    template <class TDerived>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotated(const opensolid::Rotation<3>& rotation) const {
        return rotation.transformationMatrix().cast<Scalar>() * derived();
    }

    template <class TDerived> template <int iNumDimensions>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::mirroredAbout(
        const opensolid::Datum<iNumDimensions, iNumDimensions - 1>& datum
    ) const {
        return mirrored(opensolid::Mirror<iNumDimensions>(datum));
    }

    template <class TDerived> template <int iNumDimensions>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::mirrored(const opensolid::Mirror<iNumDimensions>& mirror) const {
        return mirror.transformationMatrix().template cast<Scalar>() * derived();
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projectedOnto(
        const opensolid::Datum<iNumDimensions, iNumAxes>& datum
    ) const {
        return projected(opensolid::Projection<iNumDimensions>(datum));
    }

    template <class TDerived> template <int iNumDimensions>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projected(const opensolid::Projection<iNumDimensions>& projection) const {
        return projection.transformationMatrix().template cast<Scalar>() * derived();
    }

    template <class TDerived>
    template <int iNumSourceDimensions, int iNumDestinationDimensions, int iNumAxes>
    Matrix<typename internal::traits<TDerived>::Scalar, iNumDestinationDimensions, internal::traits<TDerived>::ColsAtCompileTime>
    MatrixBase<TDerived>::transplanted(
        const opensolid::Datum<iNumSourceDimensions, iNumAxes>& sourceDatum,
        const opensolid::Datum<iNumDestinationDimensions, iNumAxes>& destinationDatum
    ) const {
        return destinationDatum.basisMatrix().template cast<Scalar>() *
            sourceDatum.inverseMatrix().template cast<Scalar>() * derived();
    }

    template <class TDerived> template <int iNumSourceDimensions, int iNumDestinationDimensions>
    Matrix< typename internal::traits<TDerived>::Scalar, iNumDestinationDimensions, internal::traits<TDerived>::ColsAtCompileTime>
    MatrixBase<TDerived>::transplanted(
        const opensolid::Transplant<iNumSourceDimensions, iNumDestinationDimensions>& transplant
    ) const {
        return transplant.transformationMatrix().template cast<Scalar>() * derived();
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    Matrix<typename internal::traits<TDerived>::Scalar, iNumAxes, internal::traits<TDerived>::ColsAtCompileTime>
    MatrixBase<TDerived>::localizedTo(
        const opensolid::Datum<iNumDimensions, iNumAxes>& datum
    ) const {
        return datum.inverseMatrix().template cast<Scalar>() * derived();
    }

    template <class TDerived>template <int iNumDimensions, int iNumAxes>
    Matrix<typename internal::traits<TDerived>::Scalar, iNumDimensions, internal::traits<TDerived>::ColsAtCompileTime>
    MatrixBase<TDerived>::globalizedFrom(
        const opensolid::Datum<iNumDimensions, iNumAxes>& datum
    ) const {
        return datum.basisMatrix().template cast<Scalar>() * derived();
    }

    template<class TDerived> template <class TOther>
    TOther
    MatrixBase<TDerived>::convertTo() const {
        return opensolid::ConversionFunction<PlainObject, TOther>()(derived());
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    template <class TOther>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::ConvertFrom(const TOther& other) {
        return opensolid::ConversionFunction<TOther, Matrix>()(other);
    }

    template <class TDerived>
    inline bool DenseBase<TDerived>::isEmpty() const {
        return derived().unaryExpr(EmptyOperation()).any();
    }
    
    template <class TDerived>
    inline CwiseUnaryOp<LowerOperation, const TDerived> DenseBase<TDerived>::cwiseLower() const {
        return derived().unaryExpr(LowerOperation());
    }

    template <class TDerived>
    inline CwiseUnaryOp<UpperOperation, const TDerived> DenseBase<TDerived>::cwiseUpper() const {
        return derived().unaryExpr(UpperOperation());
    }

    template <class TDerived>
    inline CwiseUnaryOp<MedianOperation, const TDerived> DenseBase<TDerived>::cwiseMedian() const {
        return derived().unaryExpr(MedianOperation());
    }

    template <class TDerived>
    inline CwiseUnaryOp<RandomOperation, const TDerived> DenseBase<TDerived>::cwiseRandom() const {
        return derived().unaryExpr(RandomOperation());
    }

    template <class TDerived>
    inline CwiseUnaryOp<WidthOperation, const TDerived> DenseBase<TDerived>::cwiseWidth() const {
        return derived().unaryExpr(WidthOperation());
    }

    template <class TDerived> template<class TOther>
    inline bool DenseBase<TDerived>::overlaps(
        const DenseBase<TOther>& other,
        double precision
    ) const {
        return derived().binaryExpr(other.derived(), OverlapOperation(precision)).all();
    }

    template <class TDerived> template<class TOther>
    inline bool DenseBase<TDerived>::strictlyOverlaps(
        const DenseBase<TOther>& other,
        double precision
    ) const {
        return derived().binaryExpr(other.derived(), StrictOverlapOperation(precision)).all();
    }

    template <class TDerived> template<class TOther>
    inline bool DenseBase<TDerived>::contains(
        const DenseBase<TOther>& other,
        double precision
    ) const {
        return derived().binaryExpr(other.derived(), ContainOperation(precision)).all();
    }

    template <class TDerived> template<class TOther>
    inline bool DenseBase<TDerived>::strictlyContains(
        const DenseBase<TOther>& other,
        double precision
    ) const {
        return derived().binaryExpr(other.derived(), StrictContainOperation(precision)).all();
    }

    template <class TDerived> template <class TOther>
    inline CwiseBinaryOp<HullOperation, const TDerived, const TOther>
    DenseBase<TDerived>::hull(const DenseBase<TOther>& other) const {
        return derived().binaryExpr(other.derived(), HullOperation());
    }

    template <class TDerived> template <class TOther>
    inline CwiseBinaryOp<IntersectionOperation, const TDerived, const TOther>
    DenseBase<TDerived>::intersection(const DenseBase<TOther>& other) const {
        return derived().binaryExpr(other.derived(), IntersectionOperation());
    }

    template <class TDerived>
    inline const typename DenseBase<TDerived>::RandomAccessLinSpacedReturnType
    DenseBase<TDerived>::LinSpaced(
        typename DenseBase<TDerived>::Index size,
        opensolid::Interval interval
    ) {
        return LinSpaced(size, Scalar(interval.lowerBound()), Scalar(interval.upperBound()));
    }

    template <class TDerived>
    inline const typename DenseBase<TDerived>::RandomAccessLinSpacedReturnType
    DenseBase<TDerived>::LinSpaced(opensolid::Interval interval) {
        return LinSpaced(Scalar(interval.lowerBound()), Scalar(interval.upperBound()));
    }

    template <class TDerived> template <class TFirst, class TSecond>
    inline CwiseBinaryOp<HullOperation, const TFirst, const TSecond> DenseBase<TDerived>::Hull(
        const DenseBase<TFirst>& first,
        const DenseBase<TSecond>& second
    ) {
        return first.hull(second);
    }

    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType DenseBase<TDerived>::Empty() {
        return Constant(opensolid::Interval::Empty());
    }
    
    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType DenseBase<TDerived>::Empty(
        typename DenseBase<TDerived>::Index size
    ) {
        return Constant(size, opensolid::Interval::Empty());
    }
    
    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType DenseBase<TDerived>::Empty(
        typename DenseBase<TDerived>::Index rows,
        typename DenseBase<TDerived>::Index cols
    ) {
        return Constant(rows, cols, opensolid::Interval::Empty());
    }

    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType DenseBase<TDerived>::Whole() {
        return Constant(opensolid::Interval::Whole());
    }
    
    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType DenseBase<TDerived>::Whole(
        typename DenseBase<TDerived>::Index size
    ) {
        return Constant(size, opensolid::Interval::Whole());
    }
    
    template <class TDerived>
    const typename DenseBase<TDerived>::ConstantReturnType DenseBase<TDerived>::Whole(
        typename DenseBase<TDerived>::Index rows,
        typename DenseBase<TDerived>::Index cols
    ) {
        return Constant(rows, cols, opensolid::Interval::Whole());
    }
}

namespace opensolid
{
    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    inline typename BoundsFunction<
        Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    >::CastType
    BoundsFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>::operator()(
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& matrix
    ) const {
        return matrix.template cast<Interval>();
    }
}
