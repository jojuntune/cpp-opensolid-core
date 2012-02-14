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

#ifndef OPENSOLID__MATRIX_HPP
#define OPENSOLID__MATRIX_HPP

#include <OpenSolid/Core/Common/Bounds.hpp>
#include <OpenSolid/Core/Common/Convertible.hpp>
#include <OpenSolid/Core/Common/Serialization.hpp>
#include <OpenSolid/Core/Scalar/double.hpp>
#include <OpenSolid/Core/Scalar/Interval.hpp>

namespace Eigen
{   
    namespace internal
    {
        template <class ScalarType, bool is_integer_>
        struct significant_decimals_default_impl;

        template <>
        struct significant_decimals_default_impl<OpenSolid::Interval, false>
        {
            static inline int run();
        };
        
        template <class ScalarType>
        struct is_arithmetic;
        
        template <>
        struct is_arithmetic<OpenSolid::Interval>
        {
            static const bool value = true;
        };
    }
    
    template <class Type>
    struct NumTraits;
    
    template <>
    struct NumTraits<OpenSolid::Interval>
    {
        typedef OpenSolid::Interval Real;
        typedef OpenSolid::Interval NonInteger;
        typedef OpenSolid::Interval Nested;
        
        static const int IsComplex = 0;
        static const int IsInteger = 0;
        static const int ReadCost = 2;
        static const int AddCost = 2;
        static const int MulCost = 10;
        static const int IsSigned = 1;
        static const int RequireInitialization = 0;
        
        static OpenSolid::Interval epsilon();
        static OpenSolid::Interval dummy_precision();
        static OpenSolid::Interval lowest();
        static OpenSolid::Interval highest();  
    };

    struct EmptyOperation
    {
        typedef bool result_type;

        bool operator()(const OpenSolid::Interval& argument) const;
    };
    
    struct LowerOperation
    {
        typedef double result_type;
        
        double operator()(const OpenSolid::Interval& argument) const;
    };
    
    struct UpperOperation
    {
        typedef double result_type;
        
        double operator()(const OpenSolid::Interval& argument) const;
    };
    
    struct MedianOperation
    {
        typedef double result_type;
        
        double operator()(const OpenSolid::Interval& argument) const;
    };

    struct RandomOperation
    {
        typedef double result_type;

        double operator()(const OpenSolid::Interval& argument) const;
    };
    
    struct WidthOperation
    {
        typedef double result_type;
        
        double operator()(const OpenSolid::Interval& argument) const;
    };
    
    struct HullOperation
    {
        typedef OpenSolid::Interval result_type;

        OpenSolid::Interval operator()(double first_argument, double second_argument) const;
        
        OpenSolid::Interval operator()(
            const OpenSolid::Interval& first_argument,
            const OpenSolid::Interval& second_argument
        ) const;
    };
    
    struct IntersectionOperation
    {
        typedef OpenSolid::Interval result_type;
        
        OpenSolid::Interval operator()(
            const OpenSolid::Interval& first_argument,
            const OpenSolid::Interval& second_argument
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
            const OpenSolid::Interval& first_argument,
            const OpenSolid::Interval& second_argument
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
            const OpenSolid::Interval& first_argument,
            const OpenSolid::Interval& second_argument
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
            const OpenSolid::Interval& first_argument,
            const OpenSolid::Interval& second_argument
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
            const OpenSolid::Interval& first_argument,
            const OpenSolid::Interval& second_argument
        ) const;
    };
}

namespace OpenSolid
{
    template <class ArgumentType>
    class TransformableMatrix;

    template <int dimensions_, int size_>
    class Datum;
};

#define EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS
#define EIGEN_FAST_MATH 0
#define EIGEN_DONT_ALIGN
#define EIGEN_DONT_VECTORIZE

#define EIGEN_DENSEBASE_PLUGIN <OpenSolid/Core/Matrix/DenseBasePlugin.hpp>
#define EIGEN_MATRIXBASE_PLUGIN <OpenSolid/Core/Matrix/MatrixBasePlugin.hpp>

#ifdef FAKE_INCLUDE_TO_CREATE_CMAKE_DEPENDENCY
#include <OpenSolid/Core/Matrix/DenseBasePlugin.hpp>
#include <OpenSolid/Core/Matrix/MatrixBasePlugin.hpp>
#endif

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

namespace Eigen
{   
    typedef Matrix<OpenSolid::Interval, 2, 1> Vector2I;
    typedef Matrix<OpenSolid::Interval, 1, 2> RowVector2I;
    typedef Matrix<OpenSolid::Interval, 2, 2> Matrix2I;
    typedef Matrix<OpenSolid::Interval, 3, 1> Vector3I;
    typedef Matrix<OpenSolid::Interval, 1, 3> RowVector3I;
    typedef Matrix<OpenSolid::Interval, 3, 3> Matrix3I;
    typedef Matrix<OpenSolid::Interval, Dynamic, 1> VectorXI;
    typedef Matrix<OpenSolid::Interval, 1, Dynamic> RowVectorXI;
    typedef Matrix<OpenSolid::Interval, Dynamic, Dynamic> MatrixXI;
    typedef Matrix<OpenSolid::Interval, 2, Dynamic> Matrix2XI;
    typedef Matrix<OpenSolid::Interval, Dynamic, 2> MatrixX2I;
    typedef Matrix<OpenSolid::Interval, 3, Dynamic> Matrix3XI;
    typedef Matrix<OpenSolid::Interval, Dynamic, 3> MatrixX3I;
    
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

namespace OpenSolid
{
    using namespace Eigen;
    
    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    struct Bounds<Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>>
    {
        typedef Matrix<Interval, rows_, cols_, options_, max_rows_, max_cols_> Type;

        typedef typename internal::conditional<
            internal::is_same<ScalarType, Interval>::value,
            const Matrix<Interval, rows_, cols_, options_, max_rows_, max_cols_>&,
            const CwiseUnaryOp<
                internal::scalar_cast_op<ScalarType, Interval>,
                const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>
            >
        >::type CastType;

        CastType operator()(
            const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
        ) const;
    };

    template <>
    struct Conversion<Interval, VectorXI>
    {
        VectorXI operator()(const Interval& interval) const;
    };

    template <>
    struct Serialization<MatrixXd>
    {
        OPENSOLID_CORE_EXPORT std::string serialized(const MatrixXd& argument) const;
        OPENSOLID_CORE_EXPORT MatrixXd deserialized(const std::string& argument) const;
    };

    template <>
    struct Serialization<MatrixXI>
    {
        OPENSOLID_CORE_EXPORT std::string serialized(const MatrixXI& argument) const;
        OPENSOLID_CORE_EXPORT MatrixXI deserialized(const std::string& argument) const;
    };

    template <int destination_size_, int source_size_>
    void assertCompatible();

    template <int destination_size_>
    void assertCompatible(int source_size);

    template <class VectorType>
    void assertVector(const VectorType& vector);

    template <int dimensions_, class MatrixType, class VectorType>
    void assertValidTransform(int dimensions, const MatrixType& matrix, const VectorType& vector);
}

////////// Implementation //////////

namespace Eigen
{
    namespace internal
    {
        inline int significant_decimals_default_impl<OpenSolid::Interval, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }

        template <>
        struct random_impl<OpenSolid::Interval>
        {
            static OpenSolid::Interval run(
                const OpenSolid::Interval& lower,
                const OpenSolid::Interval& upper
            ) {
                OpenSolid::Interval range(lower.lower(), upper.upper());
                double first_ratio = double(std::rand()) / RAND_MAX;
                double second_ratio = double(std::rand()) / RAND_MAX;
                if (first_ratio > second_ratio) {std::swap(first_ratio, second_ratio);}
                return range.interpolated(OpenSolid::Interval(first_ratio, second_ratio));
            }

            static OpenSolid::Interval run() {
                double lower = -1 + 2 * double(std::rand()) / RAND_MAX;
                double upper = -1 + 2 * double(std::rand()) / RAND_MAX;
                if (lower > upper) {std::swap(lower, upper);}
                return OpenSolid::Interval(lower, upper);
            }
        };
    }

    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::epsilon() {
        return NumTraits<double>::epsilon();
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::dummy_precision() {
        return NumTraits<double>::dummy_precision();
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::lowest() {
        return NumTraits<double>::lowest();
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::highest() {
        return NumTraits<double>::highest();
    }

    inline bool EmptyOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.isEmpty();
    }
        
    inline double LowerOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.lower();
    }
    
    inline double UpperOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.upper();
    }
    
    inline double MedianOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.median();
    }

    inline double RandomOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.random();
    }
    
    inline double WidthOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.width();
    }
    
    inline OpenSolid::Interval HullOperation::operator()(
        double first_argument,
        double second_argument
    ) const {return OpenSolid::Interval::Hull(first_argument, second_argument);}
    
    inline OpenSolid::Interval HullOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.hull(second_argument);}
    
    inline OpenSolid::Interval IntersectionOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.intersection(second_argument);}

    inline OverlapOperation::OverlapOperation(double precision) : _precision(precision) {}
    
    inline bool OverlapOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.overlaps(second_argument, _precision);}

    inline StrictOverlapOperation::StrictOverlapOperation(double precision)
        : _precision(precision) {}
    
    inline bool StrictOverlapOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.strictlyOverlaps(second_argument, _precision);}

    inline ContainOperation::ContainOperation(double precision) : _precision(precision) {}
    
    inline bool ContainOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.contains(second_argument, _precision);}

    inline StrictContainOperation::StrictContainOperation(double precision)
        : _precision(precision) {}
    
    inline bool StrictContainOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.strictlyContains(second_argument, _precision);}

    template <class DerivedType> template <class MatrixType, class VectorType>
    inline Matrix<
        typename internal::traits<DerivedType>::Scalar,
        MatrixType::RowsAtCompileTime,
        internal::traits<DerivedType>::ColsAtCompileTime
    > MatrixBase<DerivedType>::transformed(
        const MatrixType& matrix,
        const VectorType& vector
    ) const {
        return OpenSolid::TransformableMatrix<DerivedType>(derived()).transformed(matrix, vector);
    }

    template <class DerivedType> template <class PointType>
    inline typename MatrixBase<DerivedType>::PlainObject MatrixBase<DerivedType>::scaled(
        double scale,
        const EigenBase<PointType>& point
    ) const {return OpenSolid::TransformableMatrix<DerivedType>(derived()).scaled(scale, point);}

    template <class DerivedType> template <class VectorType>
    inline typename MatrixBase<DerivedType>::PlainObject MatrixBase<DerivedType>::translated(
        const EigenBase<VectorType>& vector
    ) const {return OpenSolid::TransformableMatrix<DerivedType>(derived()).translated(vector);}

    template <class DerivedType> template <int dimensions_, int axes_>
    inline typename MatrixBase<DerivedType>::PlainObject MatrixBase<DerivedType>::translated(
        double distance,
        const OpenSolid::Datum<dimensions_, axes_>& axis
    ) const {
        return OpenSolid::TransformableMatrix<DerivedType>(derived()).translated(distance, axis);
    }

    template <class DerivedType>
    inline typename MatrixBase<DerivedType>::PlainObject MatrixBase<DerivedType>::rotated(
        double angle,
        const Vector2d& point
    ) const {return OpenSolid::TransformableMatrix<DerivedType>(derived()).rotated(angle, point);}

    template <class DerivedType> template <int dimensions_, int axes_>
    inline typename MatrixBase<DerivedType>::PlainObject MatrixBase<DerivedType>::rotated(
        double angle,
        const OpenSolid::Datum<dimensions_, axes_>& axis
    ) const {return OpenSolid::TransformableMatrix<DerivedType>(derived()).rotated(angle, axis);}

    template <class DerivedType> template <int dimensions_, int axes_>
    inline typename MatrixBase<DerivedType>::PlainObject MatrixBase<DerivedType>::mirrored(
        const OpenSolid::Datum<dimensions_, axes_>& datum
    ) const {return OpenSolid::TransformableMatrix<DerivedType>(derived()).mirrored(datum);}

    template <class DerivedType>
    inline bool DenseBase<DerivedType>::isEmpty() const {
        return derived().unaryExpr(EmptyOperation()).any();
    }
    
    template <class DerivedType>
    inline CwiseUnaryOp<LowerOperation, const DerivedType>
    DenseBase<DerivedType>::cwiseLower() const {return derived().unaryExpr(LowerOperation());}

    template <class DerivedType>
    inline CwiseUnaryOp<UpperOperation, const DerivedType>
    DenseBase<DerivedType>::cwiseUpper() const {return derived().unaryExpr(UpperOperation());}

    template <class DerivedType>
    inline CwiseUnaryOp<MedianOperation, const DerivedType>
    DenseBase<DerivedType>::cwiseMedian() const {return derived().unaryExpr(MedianOperation());}

    template <class DerivedType>
    inline CwiseUnaryOp<RandomOperation, const DerivedType>
    DenseBase<DerivedType>::cwiseRandom() const {return derived().unaryExpr(RandomOperation());}

    template <class DerivedType>
    inline CwiseUnaryOp<WidthOperation, const DerivedType>
    DenseBase<DerivedType>::cwiseWidth() const {return derived().unaryExpr(WidthOperation());}

    template <class DerivedType> template<class OtherDerivedType>
    inline bool DenseBase<DerivedType>::overlaps(
        const DenseBase<OtherDerivedType>& other,
        double precision
    ) const {return derived().binaryExpr(other.derived(), OverlapOperation(precision)).all();}

    template <class DerivedType> template<class OtherDerivedType>
    inline bool DenseBase<DerivedType>::strictlyOverlaps(
        const DenseBase<OtherDerivedType>& other,
        double precision
    ) const {return derived().binaryExpr(other.derived(), StrictOverlapOperation(precision)).all();}

    template <class DerivedType> template<class OtherDerivedType>
    inline bool DenseBase<DerivedType>::contains(
        const DenseBase<OtherDerivedType>& other,
        double precision
    ) const {return derived().binaryExpr(other.derived(), ContainOperation(precision)).all();}

    template <class DerivedType> template<class OtherDerivedType>
    inline bool DenseBase<DerivedType>::strictlyContains(
        const DenseBase<OtherDerivedType>& other,
        double precision
    ) const {return derived().binaryExpr(other.derived(), StrictContainOperation(precision)).all();}

    template <class DerivedType> template <class OtherDerivedType>
    inline CwiseBinaryOp<HullOperation, const DerivedType, const OtherDerivedType>
    DenseBase<DerivedType>::hull(const DenseBase<OtherDerivedType>& other) const {
        return derived().binaryExpr(other.derived(), HullOperation());
    }

    template <class DerivedType> template <class OtherDerivedType>
    inline CwiseBinaryOp<IntersectionOperation, const DerivedType, const OtherDerivedType>
    DenseBase<DerivedType>::intersection(const DenseBase<OtherDerivedType>& other) const {
        return derived().binaryExpr(other.derived(), IntersectionOperation());
    }

    template <class DerivedType>
    inline const typename DenseBase<DerivedType>::RandomAccessLinSpacedReturnType
    DenseBase<DerivedType>::LinSpaced(
        typename DenseBase<DerivedType>::Index size,
        const OpenSolid::Interval& range
    ) {return LinSpaced(size, Scalar(range.lower()), Scalar(range.upper()));}

    template <class DerivedType>
    inline const typename DenseBase<DerivedType>::RandomAccessLinSpacedReturnType
    DenseBase<DerivedType>::LinSpaced(const OpenSolid::Interval& range) {
        return LinSpaced(Scalar(range.lower()), Scalar(range.upper()));
    }

    template <class DerivedType> template <class FirstDerivedType, class SecondDerivedType>
    inline CwiseBinaryOp<HullOperation, const FirstDerivedType, const SecondDerivedType>
    DenseBase<DerivedType>::Hull(
        const DenseBase<FirstDerivedType>& first_argument,
        const DenseBase<SecondDerivedType>& second_argument
    ) {return first_argument.hull(second_argument);}

    template <class DerivedType>
    const typename DenseBase<DerivedType>::ConstantReturnType DenseBase<DerivedType>::Empty() {
        return Constant(OpenSolid::Interval::Empty());
    }
    
    template <class DerivedType>
    const typename DenseBase<DerivedType>::ConstantReturnType DenseBase<DerivedType>::Empty(
        typename DenseBase<DerivedType>::Index size
    ) {return Constant(size, OpenSolid::Interval::Empty());}
    
    template <class DerivedType>
    const typename DenseBase<DerivedType>::ConstantReturnType DenseBase<DerivedType>::Empty(
        typename DenseBase<DerivedType>::Index rows,
        typename DenseBase<DerivedType>::Index cols
    ) {return Constant(rows, cols, OpenSolid::Interval::Empty());}

    template <class DerivedType>
    const typename DenseBase<DerivedType>::ConstantReturnType DenseBase<DerivedType>::Whole() {
        return Constant(OpenSolid::Interval::Whole());
    }
    
    template <class DerivedType>
    const typename DenseBase<DerivedType>::ConstantReturnType DenseBase<DerivedType>::Whole(
        typename DenseBase<DerivedType>::Index size
    ) {return Constant(size, OpenSolid::Interval::Whole());}
    
    template <class DerivedType>
    const typename DenseBase<DerivedType>::ConstantReturnType DenseBase<DerivedType>::Whole(
        typename DenseBase<DerivedType>::Index rows,
        typename DenseBase<DerivedType>::Index cols
    ) {return Constant(rows, cols, OpenSolid::Interval::Whole());}
}

namespace OpenSolid
{
    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    inline typename Bounds<
        Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>
    >::CastType
    Bounds<Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>>::operator()(
        const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
    ) const {return argument.template cast<Interval>();}

    inline VectorXI Conversion<Interval, VectorXI>::operator()(const Interval& interval) const {
        return VectorXI::Constant(1, interval);
    }

    template <int destination_size_, int source_size_>
    inline void assertCompatible() {
        static_assert(
            destination_size_ == source_size_ ||
            destination_size_ == Dynamic ||
            source_size_ == Dynamic,
            "Different sizes at compile time"
        );
    }

    template <int destination_size_>
    inline void assertCompatible(int source_size) {
        assert(source_size == destination_size_ && "Different sizes");
    }

    template <>
    inline void assertCompatible<Dynamic>(int) {}

    template <class VectorType>
    inline void assertVector(const VectorType& vector) {
        assertCompatible<VectorType::ColsAtCompileTime, 1>();
        assert(vector.cols() == 1);
    }

    template <int dimensions_, class MatrixType, class VectorType>
    inline void assertValidTransform(
        int dimensions,
        const MatrixType& matrix,
        const VectorType& vector
    ) {
        assertCompatible<MatrixType::ColsAtCompileTime, dimensions_>();
        assert(matrix.cols() == dimensions);
        assertVector(vector);
        assertCompatible<MatrixType::RowsAtCompileTime, VectorType::SizeAtCompileTime>();
        assert(matrix.rows() == vector.size());
    }
}

#include <OpenSolid/Core/Matrix/MatrixIterator.hpp>
#include <OpenSolid/Core/Common/Transformable.hpp>

#endif
