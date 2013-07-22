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
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::scaledAbout(
        const opensolid::Point<NumDimensions>& originPoint,
        double scale
    ) const {
        return scaling(derived(), scale);
    }

    template <class TDerived> template <class TVector>
    inline const TDerived&
    MatrixBase<TDerived>::translated(const EigenBase<TVector>& vector) const {
        return derived();
    }

    template <class TDerived>
    inline const TDerived&
    MatrixBase<TDerived>::translatedAlong(
        const opensolid::Axis<NumDimensions>& axis,
        double distance
    ) const {
        return derived();
    }

    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotatedAbout(const opensolid::Point<2>& originPoint, double angle) const {
        return opensolid::Rotation2d(originPoint, angle)(derived());
    }

    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotatedAbout(const opensolid::Axis<3>& axis, double angle) const {
        return opensolid::Rotation3d(axis, angle)(derived());
    }

    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::mirroredAbout(const opensolid::Axis<2>& axis) const {
        return opensolid::Mirror2d(axis)(derived());
    }

    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::mirroredAbout(const opensolid::Plane3d& plane) const {
        return opensolid::Mirror3d(plane)(derived());
    }

    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projectedOnto(const opensolid::Axis<2>& axis) const {
        return opensolid::Projection2d(axis)(derived());
    }

    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projectedOnto(const opensolid::Axis<3>& axis) const {
        return opensolid::Projection3d(axis)(derived());
    }

    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projectedOnto(const opensolid::Plane3d& plane) const {
        return opensolid::Projection3d(plane)(derived());
    }

    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::transformed(
        const opensolid::LinearTransformation<NumDimensions>& transformation
    ) const {
        return transformation(derived());
    }

    template <class TDerived>
    template <int iNumDestinationDimensions, int iNumAxes>
    inline Matrix<typename internal::traits<TDerived>::Scalar, iNumDestinationDimensions, internal::traits<TDerived>::ColsAtCompileTime>
    MatrixBase<TDerived>::transplanted(
        const opensolid::CoordinateSystem<NumDimensions, iNumAxes>& sourceCoordinateSystem,
        const opensolid::CoordinateSystem<iNumDestinationDimensions, iNumAxes>& destinationCoordinateSystem
    ) const {
        return localizedTo(sourceCoordinateSystem).globalizedFrom(destinationCoordinateSystem);
    }

    template <class TDerived> template <int iNumDestinationDimensions>
    inline Matrix< typename internal::traits<TDerived>::Scalar, iNumDestinationDimensions, internal::traits<TDerived>::ColsAtCompileTime>
    MatrixBase<TDerived>::transplanted(
        const opensolid::Transplant<NumDimensions, iNumDestinationDimensions>& transplant
    ) const {
        return transplant(derived());
    }

    template <class TDerived> template <int iNumAxes>
    inline Matrix<typename internal::traits<TDerived>::Scalar, iNumAxes, internal::traits<TDerived>::ColsAtCompileTime>
    MatrixBase<TDerived>::localizedTo(
        const opensolid::CoordinateSystem<NumDimensions, iNumAxes>& coordinateSystem
    ) const {
        return transformation(derived(), coordinateSystem.inverseMatrix());
    }

    template <class TDerived> template <int iNumDimensions>
    inline Matrix<typename internal::traits<TDerived>::Scalar, iNumDimensions, internal::traits<TDerived>::ColsAtCompileTime>
    MatrixBase<TDerived>::globalizedFrom(
        const opensolid::CoordinateSystem<iNumDimensions, NumDimensions>& coordinateSystem
    ) const {
        return transformation(derived(), coordinateSystem.basisMatrix());
    }

    template <class TDerived>
    inline const CwiseUnaryOp<internal::scalar_multiple_op<typename internal::traits<TDerived>::Scalar>, const TDerived>
    MatrixBase<TDerived>::scaling(const TDerived& argument, double scale) {
        return argument * Scalar(scale);
    }

    template <class TDerived> template <class TVector>
    inline const TDerived&
    MatrixBase<TDerived>::translation(const TDerived& argument, const EigenBase<TVector>& vector) {
        return argument;
    }

    template <class TDerived> template <class TMatrix>
    Matrix<
        typename internal::traits<TDerived>::Scalar,
        TMatrix::RowsAtCompileTime,
        internal::traits<TDerived>::ColsAtCompileTime
    >
    MatrixBase<TDerived>::transformation(const TDerived& argument, const EigenBase<TMatrix>& matrix) {
        return matrix.derived().template cast<Scalar>() * argument;
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

    namespace internal
    {
        inline int
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

    inline opensolid::Interval
    NumTraits<opensolid::Interval>::epsilon() {
        return std::numeric_limits<double>::epsilon();
    }
    
    inline opensolid::Interval
    NumTraits<opensolid::Interval>::dummy_precision() {
        return 1e-12;
    }
    
    inline opensolid::Interval
    NumTraits<opensolid::Interval>::lowest() {
        return std::numeric_limits<double>::min();
    }
    
    inline opensolid::Interval
    NumTraits<opensolid::Interval>::highest() {
        return std::numeric_limits<double>::max();
    }
}

namespace opensolid
{
    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    inline Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    ScalingFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>::operator()(
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
        double scale
    ) const {
        return scale * argument;
    }

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    template <class TVector>
    inline const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>&
    TranslationFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>::operator()(
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
        const EigenBase<TVector>& vector
    ) const {
        return argument;
    }

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols, int iNumTransformedDimensions>
    template <class TMatrix>
    inline Matrix<TScalar, iNumTransformedDimensions, iCols, iOptions, iNumTransformedDimensions, iMaxCols>
    TransformationFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>, iNumTransformedDimensions>::operator()(
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
        const EigenBase<TMatrix>& matrix
    ) const {
        return matrix.derived() * argument;
    }

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
