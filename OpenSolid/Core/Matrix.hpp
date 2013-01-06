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

#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Core/Datum/declarations.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix/declarations.hpp>
#include <OpenSolid/Core/Matrix/MatrixIterator.hpp>
#include <OpenSolid/Utils/Conversion.hpp>

namespace Eigen
{   
    namespace internal
    {
        template <>
        struct significant_decimals_default_impl<opensolid::Interval, false>
        {
            static inline int run();
        };
        
        template <>
        struct is_arithmetic<opensolid::Interval>
        {
            static const bool value = true;
        };
    }
    
    template <>
    struct NumTraits<opensolid::Interval>
    {
        typedef opensolid::Interval Real;
        typedef opensolid::Interval NonInteger;
        typedef opensolid::Interval Nested;
        
        static const int IsComplex = 0;
        static const int IsInteger = 0;
        static const int ReadCost = 2;
        static const int AddCost = 2;
        static const int MulCost = 10;
        static const int IsSigned = 1;
        static const int RequireInitialization = 0;
        
        static opensolid::Interval epsilon();
        static opensolid::Interval dummy_precision();
        static opensolid::Interval lowest();
        static opensolid::Interval highest();  
    };

    struct EmptyOperation
    {
        typedef bool result_type;

        bool operator()(opensolid::Interval interval) const;
    };
    
    struct LowerOperation
    {
        typedef double result_type;
        
        double operator()(opensolid::Interval interval) const;
    };
    
    struct UpperOperation
    {
        typedef double result_type;
        
        double operator()(opensolid::Interval interval) const;
    };
    
    struct MedianOperation
    {
        typedef double result_type;
        
        double operator()(opensolid::Interval interval) const;
    };

    struct RandomOperation
    {
        typedef double result_type;

        double operator()(opensolid::Interval interval) const;
    };
    
    struct WidthOperation
    {
        typedef double result_type;
        
        double operator()(opensolid::Interval interval) const;
    };
    
    struct HullOperation
    {
        typedef opensolid::Interval result_type;

        opensolid::Interval operator()(double firstValue, double secondValue) const;
        
        opensolid::Interval operator()(
            opensolid::Interval firstInterval,
            opensolid::Interval secondInterval
        ) const;
    };
    
    struct IntersectionOperation
    {
        typedef opensolid::Interval result_type;
        
        opensolid::Interval operator()(
            opensolid::Interval firstInterval,
            opensolid::Interval secondInterval
        ) const;
    };
    
    class OverlapOperation
    {
    private:
        double _precision;
    public:
        typedef bool result_type;

        OverlapOperation(double precision);

        bool operator()(
            opensolid::Interval firstInterval,
            opensolid::Interval secondInterval
        ) const;
    };
    
    class StrictOverlapOperation
    {
    private:
        double _precision;
    public:
        typedef bool result_type;

        StrictOverlapOperation(double precision);

        bool operator()(
            opensolid::Interval firstInterval,
            opensolid::Interval secondInterval
        ) const;
    };
    
    class ContainOperation
    {
    private:
        double _precision;
    public:
        typedef bool result_type;

        ContainOperation(double precision);
        
        bool operator()(
            opensolid::Interval firstInterval,
            opensolid::Interval secondInterval
        ) const;
    };
    
    class StrictContainOperation
    {
    private:
        double _precision;
    public:
        typedef bool result_type;

        StrictContainOperation(double precision);
        
        bool operator()(
            opensolid::Interval firstInterval,
            opensolid::Interval secondInterval
        ) const;
    };
}

#define EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS
#define EIGEN_FAST_MATH 0
#define EIGEN_DONT_ALIGN
#define EIGEN_DONT_VECTORIZE

#define EIGEN_DENSEBASE_PLUGIN "DenseBasePlugin.hpp"
#define EIGEN_MATRIXBASE_PLUGIN "MatrixBasePlugin.hpp"
#define EIGEN_MATRIX_PLUGIN "MatrixPlugin.hpp"

#ifdef FAKE_INCLUDE_TO_CREATE_CMAKE_DEPENDENCY
#include "../../external/eigen/DenseBasePlugin.hpp"
#include "../../external/eigen/MatrixBasePlugin.hpp"
#include "../../external/eigen/MatrixPlugin.hpp"
#endif

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

namespace Eigen
{   
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
    
    typedef Map<MatrixXd, Unaligned, Stride<Dynamic, Dynamic>> MapXd;
    typedef Map<MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> MapXI;
    typedef Map<MatrixXb, Unaligned, Stride<Dynamic, Dynamic>> MapXb;
    
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

    template <class TMatrixType>
    void assertVector(const TMatrixType& matrix);

    template <int iNumDimensions, class TMatrix, class TVector>
    void assertValidTransform(int dimensions, const TMatrix& matrix, const TVector& vector);
}

////////// Implementation //////////

#include <OpenSolid/Utils/Conversion.hpp>

namespace Eigen
{
    namespace internal
    {
        inline int significant_decimals_default_impl<opensolid::Interval, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }

        template <>
        struct random_impl<opensolid::Interval>
        {
            static opensolid::Interval run(
                const opensolid::Interval& lowerInterval,
                const opensolid::Interval& upperInterval
            ) {
                opensolid::Interval interval(lowerInterval.lowerValue(), upperInterval.upperValue());
                double firstRatio = double(std::rand()) / RAND_MAX;
                double secondRatio = double(std::rand()) / RAND_MAX;
                return interval.interpolated(opensolid::Interval::Hull(firstRatio, secondRatio));
            }

            static opensolid::Interval run() {
                double lower = -1 + 2 * double(std::rand()) / RAND_MAX;
                double upper = -1 + 2 * double(std::rand()) / RAND_MAX;
                return opensolid::Interval::Hull(lower, upper);
            }
        };
    }

    inline opensolid::Interval NumTraits<opensolid::Interval>::epsilon() {
        return NumTraits<double>::epsilon();
    }
    
    inline opensolid::Interval NumTraits<opensolid::Interval>::dummy_precision() {
        return NumTraits<double>::dummy_precision();
    }
    
    inline opensolid::Interval NumTraits<opensolid::Interval>::lowest() {
        return NumTraits<double>::lowest();
    }
    
    inline opensolid::Interval NumTraits<opensolid::Interval>::highest() {
        return NumTraits<double>::highest();
    }

    inline bool EmptyOperation::operator()(opensolid::Interval interval) const {
        return interval.isEmpty();
    }
        
    inline double LowerOperation::operator()(opensolid::Interval interval) const {
        return interval.lowerValue();
    }
    
    inline double UpperOperation::operator()(opensolid::Interval interval) const {
        return interval.upperValue();
    }
    
    inline double MedianOperation::operator()(opensolid::Interval interval) const {
        return interval.median();
    }

    inline double RandomOperation::operator()(opensolid::Interval interval) const {
        return interval.randomValue();
    }
    
    inline double WidthOperation::operator()(opensolid::Interval interval) const {
        return interval.width();
    }
    
    inline opensolid::Interval HullOperation::operator()(
        double firstValue,
        double secondValue
    ) const {
        return opensolid::Interval::Hull(firstValue, secondValue);
    }
    
    inline opensolid::Interval HullOperation::operator()(
        opensolid::Interval firstInterval,
        opensolid::Interval secondInterval
    ) const {
        return firstInterval.hull(secondInterval);
    }
    
    inline opensolid::Interval IntersectionOperation::operator()(
        opensolid::Interval firstInterval,
        opensolid::Interval secondInterval
    ) const {
        return firstInterval.intersection(secondInterval);
    }

    inline OverlapOperation::OverlapOperation(double precision) :
        _precision(precision) {
    }
    
    inline bool OverlapOperation::operator()(
        opensolid::Interval firstInterval,
        opensolid::Interval secondInterval
    ) const {
        return firstInterval.overlaps(secondInterval, _precision);
    }

    inline StrictOverlapOperation::StrictOverlapOperation(double precision) :
        _precision(precision) {
    }
    
    inline bool StrictOverlapOperation::operator()(
        opensolid::Interval firstInterval,
        opensolid::Interval secondInterval
    ) const {
        return firstInterval.strictlyOverlaps(secondInterval, _precision);
    }

    inline ContainOperation::ContainOperation(double precision) :
        _precision(precision) {
    }
    
    inline bool ContainOperation::operator()(
        opensolid::Interval firstInterval,
        opensolid::Interval secondInterval
    ) const {
        return firstInterval.contains(secondInterval, _precision);
    }

    inline StrictContainOperation::StrictContainOperation(double precision)
        : _precision(precision) {
    }
    
    inline bool StrictContainOperation::operator()(
        opensolid::Interval firstInterval,
        opensolid::Interval secondInterval
    ) const {
        return firstInterval.strictlyContains(secondInterval, _precision);
    }

    template <class TDerived> template <int iInputDimensions, int iOutputDimensions>
    typename MatrixBase<TDerived>::Transformed<iOutputDimensions>::Type
    MatrixBase<TDerived>::transformed(
        const Transformation<iInputDimensions, iOutputDimensions>& transformation
    ) const {
        return (transformation.matrix() * derived()).colwise() + transformation.vector();
    }

    template <class TDerived> template <class TPoint>
    inline typename MatrixBase<TDerived>::PlainObject MatrixBase<TDerived>::scaled(
        double scale,
        const EigenBase<TPoint>& point
    ) const {
        return ((derived().colwise() - point.derived()) * scale).colwise() + point.derived();
    }

    template <class TDerived> template <class TVector>
    inline typename MatrixBase<TDerived>::PlainObject MatrixBase<TDerived>::translated(
        const EigenBase<TVector>& vector
    ) const {
        return derived().colwise() + vector.derived();
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline typename MatrixBase<TDerived>::PlainObject MatrixBase<TDerived>::translated(
        double distance,
        const opensolid::Datum<iNumDimensions, iNumAxes>& axis
    ) const {
        return derived().colwise() + distance * axis.directionVector();
    }

    template <class TDerived>
    inline typename MatrixBase<TDerived>::PlainObject MatrixBase<TDerived>::rotated(
        double angle,
        const Vector2d& point
    ) const {
        Matrix2d rotationMatrix(Rotation2Dd(angle));
        return ((derived().colwise() - point.derived()) * rotationMatrix).colwise() +
            point.derived();
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline typename MatrixBase<TDerived>::PlainObject MatrixBase<TDerived>::rotated(
        double angle,
        const opensolid::Datum<iNumDimensions, iNumAxes>& axis
    ) const {
        Matrix3d rotationMatrix(AngleAxisd(angle, axis.directionVector()));
        return ((derived().colwise() - axis.originPoint()) * rotationMatrix).colwise() +
            axis.originPoint();
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline typename MatrixBase<TDerived>::PlainObject MatrixBase<TDerived>::mirrored(
        const opensolid::Datum<iNumDimensions, iNumAxes>& datum
    ) const {
        return derived() - 2 * datum.normalVector() *
            (datum.normalVector().transpose() * (derived().colwise() - datum.originPoint()));
    }

    template<class TDerived> template <class TOther>
    OtherType MatrixBase<TDerived>::as() const {
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

    template <class DerivedType>
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
        return LinSpaced(size, Scalar(interval.lower()), Scalar(interval.upper()));
    }

    template <class TDerived>
    inline const typename DenseBase<TDerived>::RandomAccessLinSpacedReturnType
    DenseBase<TDerived>::LinSpaced(opensolid::Interval interval) {
        return LinSpaced(Scalar(interval.lower()), Scalar(interval.upper()));
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
