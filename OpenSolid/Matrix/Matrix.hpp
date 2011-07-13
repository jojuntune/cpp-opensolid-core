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

#include <OpenSolid/Scalar/Interval.hpp>

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
    
    struct WidthOperation
    {
        typedef double result_type;
        
        double operator()(const OpenSolid::Interval& argument) const;
    };
    
    struct HullOperation
    {
        typedef OpenSolid::Interval result_type;
        
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
    
    struct OverlapOperation
    {
        typedef bool result_type;

        bool operator()(
            const OpenSolid::Interval& first_argument,
            const OpenSolid::Interval& second_argument
        ) const;
    };
    
    struct ContainOperation
    {
        typedef bool result_type;
        
        bool operator()(
            const OpenSolid::Interval& first_argument,
            const OpenSolid::Interval& second_argument
        ) const;
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

namespace Eigen
{   
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
    struct Traits<Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>>
    {
        static typename internal::conditional<
            internal::is_same<ScalarType, Interval>::value,
            const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>&,
            const CwiseUnaryOp<
                internal::scalar_cast_op<Scalar, Interval>,
                const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>
            >
        >::type bounds(
            const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
        ) const;

        static std::size_t hash(
            const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
        ) const;

        static bool equal(
            const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& first_argument,
            const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& second_argument
        );
    };
}

////////// Implementation //////////

#include <boost/functional/hash.hpp>

#include <OpenSolid/Matrix/MatrixIterator.hpp>

namespace Eigen
{
    namespace internal
    {
        inline int significant_decimals_default_impl<OpenSolid::Interval, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
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
        
    template <class ScalarType>
    inline double LowerOperation::operator()(ScalarType argument) const {return argument.lower();}
    
    template <class ScalarType>
    inline double UpperOperation::operator()(ScalarType argument) const {return argument.upper();}
    
    template <class ScalarType>
    inline double MedianOperation::operator()(ScalarType argument) const {return argument.median();}
    
    template <class ScalarType>
    inline double WidthOperation::operator()(ScalarType argument) const {return argument.width();}
    
    template <class ScalarType>
    inline OpenSolid::Interval HullOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.hull(second_argument);}
    
    inline OpenSolid::Interval IntersectionOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.intersection(second_argument);}
    
    inline bool OverlapOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.overlaps(second_argument);}
    
    inline bool ContainOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.contains(second_argument);}

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

    template <class DerivedType> template<class OtherDerivedType>
    inline bool DenseBase<DerivedType>::overlaps(
        const DenseBase<OtherDerivedType>& other
    ) const {return derived().binaryExpr(other.derived(), OverlapOperation()).all();}

    template <class DerivedType> template<class OtherDerivedType>
    inline bool DenseBase<DerivedType>::contains(
        const DenseBase<OtherDerivedType>& other
    ) const {return derived().binaryExpr(other.derived(), ContainOperation()).all();}

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
}

namespace OpenSolid
{
    namespace
    {
        struct HashVisitor
        {
            std::size_t result;
        
            template <class ScalarType>
            inline void init(const ScalarType& argument, int, int) {
                result = 0;
                boost::hash_combine(result, Traits<ScalarType>::hash(argument));
            }
        
            template <class ScalarType>
            inline void operator()(const ScalarType& argument, int, int) {
                boost::hash_combine(result, Traits<ScalarType>::hash(argument));
            }
        };

        struct EqualVisitor
        {
            typedef bool result_type;

            template <class ScalarType>
            inline bool operator()(
                const ScalarType& first_argument,
                const ScalarType& second_argument
            ) {return Traits<ScalarType>::equal(first_argument, second_argument);}
        };
    }

    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    inline typename Eigen::internal::conditional<
        Eigen::internal::is_same<ScalarType, Interval>::value,
        const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>&,
        const CwiseUnaryOp<
            Eigen::internal::scalar_cast_op<Scalar, Interval>,
            const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>
        >
    >::type Traits<Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>>::bounds(
        const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
    ) const {return derived().template cast<Interval>();}

    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    inline std::size_t
    Traits<Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>>::hash(
        const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
    ) const {
        HashVisitor visitor;
        derived().visit(visitor);
        return visitor.result;
    }

    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    inline bool Traits<Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>>::equal(
        const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& first_argument,
        const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& second_argument
    ) {return first_argument.binaryExpr(second_argument, EqualVisitor()).all();}
}

#endif
