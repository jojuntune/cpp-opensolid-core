/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

// Public headers
#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Interval.hpp>

// Declarations headers
#include <OpenSolid/Core/Datum/declarations.hpp>
#include <OpenSolid/Core/Matrix/declarations.hpp>
#include <OpenSolid/Core/Transformation/declarations.hpp>

#define EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS
#define EIGEN_FAST_MATH 0
#define EIGEN_DONT_ALIGN
#define EIGEN_DONT_VECTORIZE

#define EIGEN_DENSEBASE_PLUGIN "DenseBasePlugin.hpp"
#define EIGEN_MATRIXBASE_PLUGIN "MatrixBasePlugin.hpp"
#define EIGEN_MATRIX_PLUGIN "MatrixPlugin.hpp"

#ifdef FAKE_INCLUDE_TO_CREATE_CMAKE_DEPENDENCY
#include "../../External/Eigen/DenseBasePlugin.hpp"
#include "../../External/Eigen/MatrixBasePlugin.hpp"
#include "../../External/Eigen/MatrixPlugin.hpp"
#endif

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

namespace Eigen
{
    typedef Matrix<int, 1, 1> Matrix1i;
    typedef Matrix<double, 1, 1> Matrix1d;
    typedef Matrix<opensolid::Interval, 1, 1> Matrix1I;
    typedef Matrix<bool, 1, 1> Matrix1b;

    typedef Matrix<opensolid::Interval, 2, 1> Vector2I;
    typedef Matrix<opensolid::Interval, 1, 2> RowVector2I;
    typedef Matrix<opensolid::Interval, 2, 2> Matrix2I;
    typedef Matrix<opensolid::Interval, 3, 1> Vector3I;
    typedef Matrix<opensolid::Interval, 1, 3> RowVector3I;
    typedef Matrix<opensolid::Interval, 3, 3> Matrix3I;
    typedef Matrix<opensolid::Interval, Dynamic, 1> VectorXI;
    typedef Matrix<opensolid::Interval, 1, Dynamic> RowVectorXI;
    typedef Matrix<opensolid::Interval, Dynamic, Dynamic> MatrixXI;
    typedef Matrix<opensolid::Interval, 2, Dynamic> Matrix2XI;
    typedef Matrix<opensolid::Interval, Dynamic, 2> MatrixX2I;
    typedef Matrix<opensolid::Interval, 3, Dynamic> Matrix3XI;
    typedef Matrix<opensolid::Interval, Dynamic, 3> MatrixX3I;
    
    typedef Matrix<bool, 2, 1> Vector2b;
    typedef Matrix<bool, 1, 2> RowVector2b;
    typedef Matrix<bool, 2, 2> Matrix2b;
    typedef Matrix<bool, 3, 1> Vector3b;
    typedef Matrix<bool, 1, 3> RowVector3b;
    typedef Matrix<bool, 3, 3> Matrix3b;
    typedef Matrix<bool, Dynamic, 1> VectorXb;
    typedef Matrix<bool, 1, Dynamic> RowVectorXb;
    typedef Matrix<bool, Dynamic, Dynamic> MatrixXb;
    typedef Matrix<bool, 2, Dynamic> Matrix2Xb;
    typedef Matrix<bool, Dynamic, 2> MatrixX2b;
    typedef Matrix<bool, 3, Dynamic> Matrix3Xb;
    typedef Matrix<bool, Dynamic, 3> MatrixX3b;
    
    typedef Map<MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> MapXi;
    typedef Map<MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> MapXd;
    typedef Map<MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> MapXI;
    typedef Map<MatrixXb, Unaligned, Stride<Dynamic, Dynamic>> MapXb;
    
    typedef Map<const MatrixXb, Unaligned, Stride<Dynamic, Dynamic>> MapXci;
    typedef Map<const MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> MapXcd;
    typedef Map<const MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> MapXcI;
    typedef Map<const MatrixXb, Unaligned, Stride<Dynamic, Dynamic>> MapXcb;
}

namespace opensolid
{
    using namespace Eigen;
    
    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct Bounds<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        typedef Matrix<Interval, iRows, iCols, iOptions, iMaxRows, iMaxCols> Type;

        typedef typename internal::conditional<
            internal::is_same<TScalar, Interval>::value,
            const Matrix<Interval, iRows, iCols, iOptions, iMaxRows, iMaxCols>&,
            const CwiseUnaryOp<
                internal::scalar_cast_op<TScalar, Interval>,
                const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
            >
        >::type CastType;

        CastType operator()(
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument
        ) const;
    };

    template <>
    struct Conversion<Interval, VectorXI>
    {
        VectorXI operator()(Interval interval) const;
    };

    template <int iDestinationSize, int iSourceSize>
    void assertCompatible();

    template <int iDestinationSize>
    void assertCompatible(int sourceSize);

    template <class TMatrix>
    void assertVector(const TMatrix& matrix);

    template <int iNumDimensions, class TMatrix, class TVector>
    void assertValidTransform(int dimensions, const TMatrix& matrix, const TVector& vector);
}

////////// Implementation //////////

// Public headers
#include <OpenSolid/Core/Mirror.hpp>
#include <OpenSolid/Core/Projection.hpp>
#include <OpenSolid/Core/Rotation.hpp>
#include <OpenSolid/Core/Convertible.hpp>

// Internal headers
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

namespace Eigen
{
    template<class TDerived> template <class TPoint>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::scaled(double scale, const EigenBase<TPoint>& originPoint) const {
        return (scale * (derived().colwise() - originPoint.derived())).colwise() +
            originPoint.derived();
    }

    template<class TDerived> template <int iNumDimensions, int iNumAxes>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::translated(
        double coordinateValue,
        const opensolid::Datum<iNumDimensions, iNumAxes>& axis
    ) const {
        return derived().colwise() + (coordinateValue * axis.basisVector()).template cast<Scalar>();
    }

    template<class TDerived>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotated(double angle) const {
        return rotated(opensolid::Rotation<2>(angle, Vector2d::Zero()), opensolid::Linear);
    }

    template<class TDerived>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotated(
        double angle,
        const Matrix<double, 2, 1>& originPoint
    ) const {
        return rotated(opensolid::Rotation<2>(angle, originPoint));
    }

    template<class TDerived>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotated(const opensolid::Rotation<2>& rotation) const {
        return (rotation.transformationMatrix().template cast<Scalar>() * (derived().colwise() - rotation.originPoint().template cast<Scalar>())).colwise() +
            rotation.originPoint().template cast<Scalar>();
    }

    template<class TDerived>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotated(
        const opensolid::Rotation<2>& rotation,
        opensolid::LinearTag
    ) const {
        return rotation.transformationMatrix().template cast<Scalar>() * derived();
    }

    template<class TDerived> template <int iNumDimensions, int iNumAxes>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotated(
        double angle,
        const opensolid::Datum<iNumDimensions, iNumAxes>& axis
    ) const {
        return rotated(opensolid::Rotation<3>(angle, axis));
    }

    template<class TDerived>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotated(const opensolid::Rotation<3>& rotation) const {
        return (rotation.transformationMatrix().template cast<Scalar>() * (derived().colwise() - rotation.originPoint().template cast<Scalar>())).colwise() +
            rotation.originPoint().template cast<Scalar>();
    }

    template<class TDerived>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::rotated(
        const opensolid::Rotation<3>& rotation,
        opensolid::LinearTag
    ) const {
        return rotation.transformationMatrix().template cast<Scalar>() * derived();
    }

    template<class TDerived> template <int iNumDimensions, int iNumAxes>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::mirrored(const opensolid::Datum<iNumDimensions, iNumAxes>& datum) const {
        return mirrored(opensolid::Mirror<iNumDimensions>(datum));
    }

    template<class TDerived> template <int iNumDimensions>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::mirrored(const opensolid::Mirror<iNumDimensions>& mirror) const {
        return (mirror.transformationMatrix().template cast<Scalar>() * (derived().colwise() - mirror.originPoint().template cast<Scalar>())).colwise() +
            mirror.originPoint().template cast<Scalar>();
    }

    template<class TDerived> template <int iNumDimensions, class TPoint>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::mirrored(
        const opensolid::Mirror<iNumDimensions>& mirror,
        opensolid::LinearTag
    ) const {
        return mirror.transformationMatrix().template cast<Scalar>() * derived();
    }

    template<class TDerived> template <int iNumDimensions, int iNumAxes>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projected(const opensolid::Datum<iNumDimensions, iNumAxes>& datum) const {
        return projected(opensolid::Projection<iNumDimensions>(datum));
    }

    template<class TDerived> template <int iNumDimensions>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projected(const opensolid::Projection<iNumDimensions>& projection) const {
        return (projection.transformationMatrix().template cast<Scalar>() * (derived().colwise() - projection.originPoint().template cast<Scalar>())).colwise() +
            projection.originPoint().template cast<Scalar>();
    }

    template<class TDerived> template <int iNumDimensions, class TPoint>
    typename MatrixBase<TDerived>::PlainObject
    MatrixBase<TDerived>::projected(
        const opensolid::Projection<iNumDimensions>& projection,
        opensolid::LinearTag
    ) const {
        return projection.transformationMatrix().template cast<Scalar>() * derived();
    }

    template<class TDerived>
    template <
        int iNumSourceDatumDimensions,
        int iNumSourceDatumAxes,
        int iNumDestinationDatumDimensions,
        int iNumDestinationDatumAxes
    >
    Matrix<
        typename internal::traits<TDerived>::Scalar,
        iNumDestinationDatumDimensions,
        internal::traits<TDerived>::ColsAtCompileTime
    >
    MatrixBase<TDerived>::transformed(
        const opensolid::Datum<iNumSourceDatumDimensions, iNumSourceDatumAxes>& sourceDatum,
        const opensolid::Datum<iNumDestinationDatumDimensions, iNumDestinationDatumAxes>& destinationDatum
    ) const {
        return destinationDatum * (derived() / sourceDatum);
    }

    template<class TDerived> template <int iNumSourceDimensions, int iNumDestinationDimensions>
    Matrix<
        typename internal::traits<TDerived>::Scalar,
        iNumDestinationDimensions,
        internal::traits<TDerived>::ColsAtCompileTime
    >
    MatrixBase<TDerived>::transformed(
        const opensolid::Transformation<iNumSourceDimensions, iNumDestinationDimensions>& transformation
    ) const {
        return transformation.transformationMatrix().template cast<Scalar>() *
            (derived().colwise() - transformation.sourceOriginPoint().template cast<Scalar>()).colwise() +
            transformation.destinationOriginPoint().template cast<Scalar>();
    }

    template<class TDerived> template <int iNumSourceDimensions, int iNumDestinationDimensions>
    Matrix<
        typename internal::traits<TDerived>::Scalar,
        iNumDestinationDimensions,
        internal::traits<TDerived>::ColsAtCompileTime
    >
    MatrixBase<TDerived>::transformed(
        const opensolid::Transformation<iNumSourceDimensions, iNumDestinationDimensions>& transformation,
        opensolid::LinearTag
    ) const {
        return transformation.transformationMatrix().template cast<Scalar>() * derived();
    }

    template<class TDerived> template <class TOther>
    TOther MatrixBase<TDerived>::as() const {
        return opensolid::Conversion<PlainObject, TOther>()(derived());
    }

    template<class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    template <class TOther>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
    Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>::from(const TOther& other) {
        return opensolid::Conversion<TOther, Matrix>()(other);
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
    inline typename Bounds<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>::CastType
    Bounds<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>::operator()(
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& matrix
    ) const {
        return matrix.template cast<Interval>();
    }

    inline VectorXI Conversion<Interval, VectorXI>::operator()(Interval interval) const {
        return VectorXI::Constant(1, interval);
    }

    template <int iDestinationSize, int iSourceSize>
    inline void assertCompatible() {
        static_assert(
            iDestinationSize == iSourceSize ||
            iDestinationSize == Dynamic ||
            iSourceSize == Dynamic,
            "Different sizes at compile time"
        );
    }

    template <int iDestinationSize>
    inline void assertCompatible(int sourceSize) {
        assert(sourceSize == iDestinationSize && "Different sizes");
    }

    template <>
    inline void assertCompatible<Dynamic>(int) {
    }

    template <class TVector>
    inline void assertVector(const TVector& vector) {
        assertCompatible<TVector::ColsAtCompileTime, 1>();
        assert(vector.cols() == 1);
    }

    template <int iNumDimensions, class TMatrix, class TVector>
    inline void assertValidTransform(
        int dimensions,
        const TMatrix& matrix,
        const TVector& vector
    ) {
        assertCompatible<TMatrix::ColsAtCompileTime, iNumDimensions>();
        assert(matrix.cols() == dimensions);
        assertVector(vector);
        assertCompatible<TMatrix::RowsAtCompileTime, TVector::SizeAtCompileTime>();
        assert(matrix.rows() == vector.size());
    }
}
