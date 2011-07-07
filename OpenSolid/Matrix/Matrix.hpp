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

#include <OpenSolid/Scalar/Double.hpp>
#include <OpenSolid/Scalar/Interval.hpp>

namespace Eigen
{   
    namespace internal
    {
        template <class ScalarType, bool is_integer_>
        struct significant_decimals_default_impl;
        
        template <class ScalarType>
        struct is_arithmetic;

        template <class Type>
        struct traits;
        
        template <class ScalarType>
        struct scalar_fuzzy_impl;
        
        template <>
        struct significant_decimals_default_impl<OpenSolid::Double, false>
        {
            static inline int run();
        };
        
        template <>
        struct is_arithmetic<OpenSolid::Double>
        {
            static const bool value = true;
        };

        template <>
        struct significant_decimals_default_impl<OpenSolid::Interval, false>
        {
            static inline int run();
        };
        
        template <>
        struct is_arithmetic<OpenSolid::Interval>
        {
            static const bool value = true;
        };
        
        template <>
        struct scalar_fuzzy_impl<OpenSolid::Double>
        {
            template <class ScalarType>
            static inline bool isMuchSmallerThan(
                OpenSolid::Double first_argument,
                const ScalarType& second_argument,
                OpenSolid::Double precision
            );
            
            static inline bool isApprox(
                OpenSolid::Double first_argument,
                OpenSolid::Double second_argument,
                OpenSolid::Double precision
            );
        };
        
        template <>
        struct scalar_fuzzy_impl<OpenSolid::Interval>
        {
            template <class ScalarType>
            static inline bool isMuchSmallerThan(
                const OpenSolid::Interval& first_argument,
                const ScalarType& second_argument,
                const OpenSolid::Interval& precision
            );
            
            static inline bool isApprox(
                const OpenSolid::Interval& first_argument,
                const OpenSolid::Interval& second_argument,
                const OpenSolid::Interval& precision
            );
        };
    }
    
    template <class Type>
    struct NumTraits;
    
    template <>
    struct NumTraits<OpenSolid::Double>
    {
        typedef OpenSolid::Double Real;
        typedef OpenSolid::Double NonInteger;
        typedef OpenSolid::Double Nested;
        
        static const int IsComplex = 0;
        static const int IsInteger = 0;
        static const int ReadCost = 1;
        static const int AddCost = 1;
        static const int MulCost = 1;
        static const int IsSigned = 1;
        static const int RequireInitialization = 0;
        
        static OpenSolid::Double epsilon();
        static OpenSolid::Double dummy_precision();
        static OpenSolid::Double lowest();
        static OpenSolid::Double highest();
    };
    
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
    
    struct LowerOperation
    {
        typedef OpenSolid::Double result_type;
        
        template <class ScalarType>
        OpenSolid::Double operator()(ScalarType argument) const;
    };
    
    struct UpperOperation
    {
        typedef OpenSolid::Double result_type;
        
        template <class ScalarType>
        OpenSolid::Double operator()(ScalarType argument) const;
    };
    
    struct MedianOperation
    {
        typedef OpenSolid::Double result_type;
        
        template <class ScalarType>
        OpenSolid::Double operator()(ScalarType argument) const;
    };
    
    struct WidthOperation
    {
        typedef OpenSolid::Double result_type;
        
        template <class ScalarType>
        OpenSolid::Double operator()(ScalarType argument) const;
    };
    
    struct HullOperation
    {
        typedef OpenSolid::Interval result_type;
        
        template <class ScalarType>
        OpenSolid::Interval operator()(ScalarType first_argument, ScalarType second_argument) const;
    };
    
    struct IntersectionOperation
    {
        typedef OpenSolid::Interval result_type;
        
        template <class ScalarType>
        OpenSolid::Interval operator()(ScalarType first_argument, ScalarType second_argument) const;
    };
    
    struct ZeroOperation
    {
        typedef bool result_type;
        
        OpenSolid::Double _precision;
        
        ZeroOperation(OpenSolid::Double precision);
        
        template <class ScalarType>
        bool operator()(ScalarType argument) const;
    };
    
    struct EqualOperation
    {
        typedef bool result_type;
        
        OpenSolid::Double _precision;
        
        EqualOperation(OpenSolid::Double precision);
        
        template <class ScalarType>
        bool operator()(ScalarType first_argument, ScalarType second_argument) const;
    };
    
    struct NotEqualOperation
    {
        typedef bool result_type;
        
        OpenSolid::Double _precision;
        
        NotEqualOperation(OpenSolid::Double precision);
        
        template <class ScalarType>
        bool operator()(ScalarType first_argument, ScalarType second_argument) const;
    };
    
    struct OverlapOperation
    {
        typedef bool result_type;
        
        OpenSolid::Double _precision;
        
        OverlapOperation(OpenSolid::Double precision);
        
        template <class ScalarType>
        bool operator()(ScalarType first_argument, ScalarType second_argument) const;
    };
    
    struct StrictOverlapOperation
    {
        typedef bool result_type;
        
        OpenSolid::Double _precision;
        
        StrictOverlapOperation(OpenSolid::Double precision);
        
        template <class ScalarType>
        bool operator()(ScalarType first_argument, ScalarType second_argument) const;
    };
    
    struct ContainOperation
    {
        typedef bool result_type;
        
        OpenSolid::Double _precision;
        
        ContainOperation(OpenSolid::Double precision);
        
        template <class ScalarType>
        bool operator()(ScalarType first_argument, ScalarType second_argument) const;
    };
    
    struct StrictContainOperation
    {
        typedef bool result_type;
        
        OpenSolid::Double _precision;
        
        StrictContainOperation(OpenSolid::Double precision);
        
        template <class ScalarType>
        bool operator()(ScalarType first_argument, ScalarType second_argument) const;
    };
    
    struct HashVisitor
    {
        std::size_t result;
        
        template <class ScalarType>
        inline void init(ScalarType argument, int, int);
        
        template <class ScalarType>
        inline void operator()(ScalarType argument, int, int);
    };
}

#define EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS
#define EIGEN_FAST_MATH 0
#define EIGEN_DONT_ALIGN
#define EIGEN_DONT_VECTORIZE

#define EIGEN_DENSEBASE_PLUGIN <OpenSolid/Matrix/DenseBasePlugin.hpp>

#ifdef FAKE_INCLUDE_TO_CREATE_CMAKE_DEPENDENCY
#include "DenseBasePlugin.hpp"
#endif

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

namespace OpenSolid
{
    using namespace Eigen;
}

namespace Eigen
{
    typedef Matrix<OpenSolid::Double, 2, 1> Vector2D;
    typedef Matrix<OpenSolid::Double, 1, 2> RowVector2D;
    typedef Matrix<OpenSolid::Double, 2, 2> Matrix2D;
    typedef Matrix<OpenSolid::Double, 3, 1> Vector3D;
    typedef Matrix<OpenSolid::Double, 1, 3> RowVector3D;
    typedef Matrix<OpenSolid::Double, 3, 3> Matrix3D;
    typedef Matrix<OpenSolid::Double, 4, 1> Vector4D;
    typedef Matrix<OpenSolid::Double, 1, 4> RowVector4D;
    typedef Matrix<OpenSolid::Double, 4, 4> Matrix4D;
    typedef Matrix<OpenSolid::Double, Dynamic, 1> VectorXD;
    typedef Matrix<OpenSolid::Double, 1, Dynamic> RowVectorXD;
    typedef Matrix<OpenSolid::Double, Dynamic, Dynamic> MatrixXD;
    typedef Matrix<OpenSolid::Double, 2, Dynamic> Matrix2XD;
    typedef Matrix<OpenSolid::Double, Dynamic, 2> MatrixX2D;
    typedef Matrix<OpenSolid::Double, 3, Dynamic> Matrix3XD;
    typedef Matrix<OpenSolid::Double, Dynamic, 3> MatrixX3D;
    typedef Matrix<OpenSolid::Double, 4, Dynamic> Matrix4XD;
    typedef Matrix<OpenSolid::Double, Dynamic, 4> MatrixX4D;
    
    typedef Matrix<OpenSolid::Interval, 2, 1> Vector2I;
    typedef Matrix<OpenSolid::Interval, 1, 2> RowVector2I;
    typedef Matrix<OpenSolid::Interval, 2, 2> Matrix2I;
    typedef Matrix<OpenSolid::Interval, 3, 1> Vector3I;
    typedef Matrix<OpenSolid::Interval, 1, 3> RowVector3I;
    typedef Matrix<OpenSolid::Interval, 3, 3> Matrix3I;
    typedef Matrix<OpenSolid::Interval, 4, 1> Vector4I;
    typedef Matrix<OpenSolid::Interval, 1, 4> RowVector4I;
    typedef Matrix<OpenSolid::Interval, 4, 4> Matrix4I;
    typedef Matrix<OpenSolid::Interval, Dynamic, 1> VectorXI;
    typedef Matrix<OpenSolid::Interval, 1, Dynamic> RowVectorXI;
    typedef Matrix<OpenSolid::Interval, Dynamic, Dynamic> MatrixXI;
    typedef Matrix<OpenSolid::Interval, 2, Dynamic> Matrix2XI;
    typedef Matrix<OpenSolid::Interval, Dynamic, 2> MatrixX2I;
    typedef Matrix<OpenSolid::Interval, 3, Dynamic> Matrix3XI;
    typedef Matrix<OpenSolid::Interval, Dynamic, 3> MatrixX3I;
    typedef Matrix<OpenSolid::Interval, 4, Dynamic> Matrix4XI;
    typedef Matrix<OpenSolid::Interval, Dynamic, 4> MatrixX4I;
    
    typedef Matrix<bool, 2, 1> Vector2b;
    typedef Matrix<bool, 1, 2> RowVector2b;
    typedef Matrix<bool, 2, 2> Matrix2b;
    typedef Matrix<bool, 3, 1> Vector3b;
    typedef Matrix<bool, 1, 3> RowVector3b;
    typedef Matrix<bool, 3, 3> Matrix3b;
    typedef Matrix<bool, 4, 1> Vector4b;
    typedef Matrix<bool, 1, 4> RowVector4b;
    typedef Matrix<bool, 4, 4> Matrix4b;
    typedef Matrix<bool, Dynamic, 1> VectorXb;
    typedef Matrix<bool, 1, Dynamic> RowVectorXb;
    typedef Matrix<bool, Dynamic, Dynamic> MatrixXb;
    typedef Matrix<bool, 2, Dynamic> Matrix2Xb;
    typedef Matrix<bool, Dynamic, 2> MatrixX2b;
    typedef Matrix<bool, 3, Dynamic> Matrix3Xb;
    typedef Matrix<bool, Dynamic, 3> MatrixX3b;
    typedef Matrix<bool, 4, Dynamic> Matrix4Xb;
    typedef Matrix<bool, Dynamic, 4> MatrixX4b;
    
    typedef Map<MatrixXD, Unaligned, Stride<Dynamic, Dynamic>> MapXD;
    typedef Map<MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> MapXI;
    typedef Map<MatrixXb, Unaligned, Stride<Dynamic, Dynamic>> MapXb;
    
    typedef Map<const MatrixXD, Unaligned, Stride<Dynamic, Dynamic>> MapXcD;
    typedef Map<const MatrixXI, Unaligned, Stride<Dynamic, Dynamic>> MapXcI;
    typedef Map<const MatrixXb, Unaligned, Stride<Dynamic, Dynamic>> MapXcb;
}

////////// Implementation //////////

#include <boost/functional/hash.hpp>

#include <OpenSolid/Matrix/MatrixIterator.hpp>

namespace Eigen
{
    namespace internal
    {
        inline int significant_decimals_default_impl<OpenSolid::Double, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
        
        inline int significant_decimals_default_impl<OpenSolid::Interval, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
        
        template <class ScalarType>
        inline bool scalar_fuzzy_impl<OpenSolid::Double>::isMuchSmallerThan(
            OpenSolid::Double first_argument,
            const ScalarType& second_argument,
            OpenSolid::Double precision
        ) {return abs(first_argument) < abs(second_argument) * precision;}
        
        inline bool scalar_fuzzy_impl<OpenSolid::Double>::isApprox(
            OpenSolid::Double first_argument,
            OpenSolid::Double second_argument,
            OpenSolid::Double precision
        ) {return first_argument.isEqualTo(second_argument, precision);}
        
        template <class ScalarType>
        inline bool scalar_fuzzy_impl<OpenSolid::Interval>::isMuchSmallerThan(
            const OpenSolid::Interval& first_argument,
            const ScalarType& second_argument,
            const OpenSolid::Interval& precision
        ) {return abs(first_argument).upper() < abs(second_argument) * precision.lower();}
        
        inline bool scalar_fuzzy_impl<OpenSolid::Interval>::isApprox(
            const OpenSolid::Interval& first_argument,
            const OpenSolid::Interval& second_argument,
            const OpenSolid::Interval& precision
        ) {return first_argument.isEqualTo(second_argument, precision.lower());}
    }

    inline OpenSolid::Double NumTraits<OpenSolid::Double>::epsilon() {
        return std::numeric_limits<double>::epsilon();
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::dummy_precision() {
        return OPENSOLID_PRECISION;
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::lowest() {
        return std::numeric_limits<double>::min();
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::highest() {
        return std::numeric_limits<double>::max();
    }

    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::epsilon() {
        return std::numeric_limits<double>::epsilon();
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::dummy_precision() {
        return OPENSOLID_PRECISION;
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::lowest() {
        return std::numeric_limits<double>::min();
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::highest() {
        return std::numeric_limits<double>::max();
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
    inline CwiseUnaryOp<WidthOperation, const DerivedType>
    DenseBase<DerivedType>::cwiseWidth() const {return derived().unaryExpr(WidthOperation());}

    template <class DerivedType> template <class OtherDerivedType>
    inline bool DenseBase<DerivedType>::isEqualTo(
        const DenseBase<OtherDerivedType>& other,
        OpenSolid::Double precision = OPENSOLID_PRECISION
    ) const {return derived().binaryExpr(other.derived(), EqualOperation(precision)).all();}

    template <class DerivedType> template <class OtherDerivedType>
    inline bool DenseBase<DerivedType>::isNotEqualTo(
        const DenseBase<OtherDerivedType>& other,
        OpenSolid::Double precision = OPENSOLID_PRECISION
    ) const {return derived().binaryExpr(other.derived(), NotEqualOperation(precision)).any();}

    template <class DerivedType> template<class OtherDerivedType>
    inline bool DenseBase<DerivedType>::overlaps(
        const DenseBase<OtherDerivedType>& other,
        OpenSolid::Double precision = OPENSOLID_PRECISION
    ) const {return derived().binaryExpr(other.derived(), OverlapOperation(precision)).all();}

    template <class DerivedType> template<class OtherDerivedType>
    inline bool DenseBase<DerivedType>::strictlyOverlaps(
        const DenseBase<OtherDerivedType>& other,
        OpenSolid::Double precision = OPENSOLID_PRECISION
    ) const {return derived().binaryExpr(other.derived(), StrictOverlapOperation(precision)).all();}

    template <class DerivedType> template<class OtherDerivedType>
    inline bool DenseBase<DerivedType>::contains(
        const DenseBase<OtherDerivedType>& other,
        OpenSolid::Double precision = OPENSOLID_PRECISION
    ) const {return derived().binaryExpr(other.derived(), ContainOperation(precision)).all();}

    template <class DerivedType> template<class OtherDerivedType>
    inline bool DenseBase<DerivedType>::strictlyContains(
        const DenseBase<OtherDerivedType>& other,
        OpenSolid::Double precision = OPENSOLID_PRECISION
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
    inline typename internal::conditional<
        internal::is_same<
            typename internal::traits<DerivedType>::Scalar,
            OpenSolid::Interval
        >::value,
        const DerivedType&,
        const CwiseUnaryOp<
            internal::scalar_cast_op<
                typename internal::traits<DerivedType>::Scalar,
                OpenSolid::Interval
            >,
            const DerivedType
        >
    >::type DenseBase<DerivedType>::bounds() const {
        return derived().template cast<OpenSolid::Interval>();
    }

    template <class DerivedType>
    inline std::size_t DenseBase<DerivedType>::hashValue() const {
        HashVisitor visitor;
        derived().visit(visitor);
        return visitor.result;
    }

    template <class DerivedType>
    inline const typename DenseBase<DerivedType>::RandomAccessLinSpacedReturnType
    DenseBase<DerivedType>::LinSpaced(
        typename DenseBase<DerivedType>::Index size,
        const OpenSolid::Interval& range
    ) {return LinSpaced(size, range.lower(), range.upper());}

    template <class DerivedType>
    inline const typename DenseBase<DerivedType>::RandomAccessLinSpacedReturnType
    DenseBase<DerivedType>::LinSpaced(const OpenSolid::Interval& range) {
        return LinSpaced(range.lower(), range.upper());
    }
        
    template <class ScalarType>
    inline OpenSolid::Double LowerOperation::operator()(ScalarType argument) const {
        return argument.lower();
    }
    
    template <class ScalarType>
    inline OpenSolid::Double UpperOperation::operator()(ScalarType argument) const {
        return argument.upper();
    }
    
    template <class ScalarType>
    inline OpenSolid::Double MedianOperation::operator()(ScalarType argument) const {
        return argument.median();
    }
    
    template <class ScalarType>
    inline OpenSolid::Double WidthOperation::operator()(ScalarType argument) const {
        return argument.width();
    }
    
    template <class ScalarType>
    inline OpenSolid::Interval HullOperation::operator()(
        ScalarType first_argument,
        ScalarType second_argument
    ) const {return first_argument.hull(second_argument);}
    
    template <class ScalarType>
    inline OpenSolid::Interval IntersectionOperation::operator()(
        ScalarType first_argument,
        ScalarType second_argument
    ) const {return first_argument.intersection(second_argument);}
    
    inline ZeroOperation::ZeroOperation(OpenSolid::Double precision) :
        _precision(precision) {}
    
    template <class ScalarType>
    inline bool ZeroOperation::operator()(ScalarType argument) const {
        return argument.isZero(_precision);
    }
    
    inline EqualOperation::EqualOperation(OpenSolid::Double precision) :
        _precision(precision) {}
    
    template <class ScalarType>
    inline bool EqualOperation::operator()(
        ScalarType first_argument,
        ScalarType second_argument
    ) const {return first_argument.isEqualTo(second_argument, _precision);}
    
    inline NotEqualOperation::NotEqualOperation(OpenSolid::Double precision) :
        _precision(precision) {}
    
    template <class ScalarType>
    inline bool NotEqualOperation::operator()(
        ScalarType first_argument,
        ScalarType second_argument
    ) const {return first_argument.isNotEqualTo(second_argument, _precision);}
    
    inline OverlapOperation::OverlapOperation(OpenSolid::Double precision) :
        _precision(precision) {}
    
    template <class ScalarType>
    inline bool OverlapOperation::operator()(
        ScalarType first_argument,
        ScalarType second_argument
    ) const {return first_argument.overlaps(second_argument, _precision);}
    
    inline StrictOverlapOperation::StrictOverlapOperation(OpenSolid::Double precision) :
        _precision(precision) {}
    
    template <class ScalarType>
    inline bool StrictOverlapOperation::operator()(
        ScalarType first_argument,
        ScalarType second_argument
    ) const {return first_argument.strictlyOverlaps(second_argument, _precision);}
    
    inline ContainOperation::ContainOperation(OpenSolid::Double precision) :
        _precision(precision) {}
    
    template <class ScalarType>
    inline bool ContainOperation::operator()(
        ScalarType first_argument,
        ScalarType second_argument
    ) const {return first_argument.contains(second_argument, _precision);}
    
    inline StrictContainOperation::StrictContainOperation(OpenSolid::Double precision) :
        _precision(precision) {}
    
    template <class ScalarType>
    inline bool StrictContainOperation::operator()(
        ScalarType first_argument,
        ScalarType second_argument
    ) const {return first_argument.strictlyContains(second_argument, _precision);}
    
    template <class ScalarType>
    inline void HashVisitor::init(ScalarType argument, int, int) {
        result = 0;
        boost::hash_combine(result, argument.hashValue());
    }
    
    template <class ScalarType>
    inline void HashVisitor::operator()(ScalarType argument, int, int) {
        boost::hash_combine(result, argument.hashValue());
    }
}

#endif
