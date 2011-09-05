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

#include <functional>

#include <boost/functional/hash.hpp>
#include <boost/geometry.hpp>
#include <boost/mpl/int.hpp>

#include <OpenSolid/Scalar/double.hpp>
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
    
    struct ContainOperation
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
    
    struct StrictContainOperation
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

    template <int first_argument_, int second_argument_>
    void assertEqual();

    void assertEqual(int first_argument, int second_argument);
}

namespace std
{
    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    struct hash<Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>> :
        public std::unary_function<
            Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>,
            size_t
        >
    {
        size_t operator()(
            const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
        ) const;
    };

    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    struct equal_to<Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>> :
        public binary_function<
            Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>,
            Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>,
            bool
        >
    {
        bool operator()(
            const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& first_argument,
            const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& second_argument
        ) const;
    };
}

namespace boost
{
    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    struct hash<Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>> :
        public std::hash<Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>>
    {
    };

    namespace geometry
    {
        namespace traits
        {
            template <>
            struct tag<Eigen::Vector2d>
            {
                typedef boost::geometry::point_tag type;
            };
            
            template <>
            struct tag<Eigen::Vector3d>
            {
                typedef boost::geometry::point_tag type;
            };

            template <>
            struct coordinate_type<Eigen::Vector2d>
            {
                typedef double type;
            };

            template <>
            struct coordinate_type<Eigen::Vector3d>
            {
                typedef double type;
            };

            template <>
            struct coordinate_system<Eigen::Vector2d>
            {
                typedef cs::cartesian type;
            };

            template <>
            struct coordinate_system<Eigen::Vector3d>
            {
                typedef cs::cartesian type;
            };

            template <>
            struct dimension<Eigen::Vector2d> : public mpl::int_<2>
            {
            };

            template <>
            struct dimension<Eigen::Vector3d> : public mpl::int_<3>
            {
            };

            template<std::size_t dimension_>
            struct access<Eigen::Vector2d, dimension_>
            {
                static double get(const Eigen::Vector2d& argument);
                static void set(Eigen::Vector2d& argument, double value);
            };

            template<std::size_t dimension_>
            struct access<Eigen::Vector3d, dimension_>
            {
                static double get(const Eigen::Vector3d& argument);
                static void set(Eigen::Vector3d& argument, double value);
            };

            template <>
            struct tag<Eigen::Vector2I>
            {
                typedef box_tag type;
            };

            template <>
            struct tag<Eigen::Vector3I>
            {
                typedef box_tag type;
            };

            template <>
            struct point_type<Eigen::Vector2I>
            {
                typedef Eigen::Vector2d type;
            };

            template <>
            struct point_type<Eigen::Vector3I>
            {
                typedef Eigen::Vector3d type;
            };

            template <std::size_t dimension_>
            struct indexed_access<Eigen::Vector2I, min_corner, dimension_>
            {
                static double get(const Eigen::Vector2I& argument);
                static void set(Eigen::Vector2I& argument, double value);
            };

            template <std::size_t dimension_>
            struct indexed_access<Eigen::Vector2I, max_corner, dimension_>
            {
                static double get(const Eigen::Vector2I& argument);
                static void set(Eigen::Vector2I& argument, double value);
            };

            template <std::size_t dimension_>
            struct indexed_access<Eigen::Vector3I, min_corner, dimension_>
            {
                static double get(const Eigen::Vector3I& argument);
                static void set(Eigen::Vector3I& argument, double value);
            };

            template <std::size_t dimension_>
            struct indexed_access<Eigen::Vector3I, max_corner, dimension_>
            {
                static double get(const Eigen::Vector3I& argument);
                static void set(Eigen::Vector3I& argument, double value);
            };
        }
    }
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
        
    inline double LowerOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.lower();
    }
    
    inline double UpperOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.upper();
    }
    
    inline double MedianOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.median();
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

    inline StrictOverlapOperation::StrictOverlapOperation(double precision) : _precision(precision) {}
    
    inline bool StrictOverlapOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.strictlyOverlaps(second_argument, _precision);}

    inline ContainOperation::ContainOperation(double precision) : _precision(precision) {}
    
    inline bool ContainOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.contains(second_argument, _precision);}

    inline StrictContainOperation::StrictContainOperation(double precision) : _precision(precision) {}
    
    inline bool StrictContainOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.strictlyContains(second_argument, _precision);}

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
    inline typename Bounds<Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>>::CastType
    Bounds<Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>>::operator()(
        const Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
    ) const {return argument.template cast<Interval>();}

    template <int first_argument_, int second_argument_>
    inline void assertEqual() {
        static const bool equal = (first_argument_ == second_argument_);
        static const bool first_dynamic = (first_argument_ == Dynamic);
        static const bool second_dynamic = (second_argument_ == Dynamic);
        static_assert(
            equal || first_dynamic || second_dynamic,
            "Matrix sizes different at compile time"
        );
    }

    inline void assertEqual(int first_argument, int second_argument) {
        assert(first_argument == second_argument && "Matrix sizes different");
    }
}

namespace
{
    struct HashVisitor
    {
        std::size_t result;
        
        template <class ScalarType>
        inline void init(const ScalarType& argument, int, int) {
            result = 0;
            boost::hash_combine(result, std::hash<ScalarType>()(argument));
        }
        
        template <class ScalarType>
        inline void operator()(const ScalarType& argument, int, int) {
            boost::hash_combine(result, std::hash<ScalarType>()(argument));
        }
    };

    struct EqualVisitor
    {
        typedef bool result_type;

        template <class ScalarType>
        inline bool operator()(
            const ScalarType& first_argument,
            const ScalarType& second_argument
        ) const {return std::equal_to<ScalarType>()(first_argument, second_argument);}
    };
}

namespace std
{
    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    inline size_t hash<
        Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>
    >::operator()(
        const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& argument
    ) const {
        HashVisitor visitor;
        argument.visit(visitor);
        return visitor.result;
    }

    template <class ScalarType, int rows_, int cols_, int options_, int max_rows_, int max_cols_>
    inline bool equal_to<
        Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>
    >::operator()(
        const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& first_argument,
        const Eigen::Matrix<ScalarType, rows_, cols_, options_, max_rows_, max_cols_>& second_argument
    ) const {return first_argument.binaryExpr(second_argument, EqualVisitor()).all();}
}

namespace boost
{
    namespace geometry
    {
        namespace traits
        {
            template<std::size_t dimension_>
            inline double access<Eigen::Vector2d, dimension_>::get(const Eigen::Vector2d& argument) {
                return argument(dimension_);
            }

            template<std::size_t dimension_>
            inline void access<Eigen::Vector2d, dimension_>::set(Eigen::Vector2d& argument, double value) {
                argument(dimension_) = value;
            }

            template<std::size_t dimension_>
            inline double access<Eigen::Vector3d, dimension_>::get(const Eigen::Vector3d& argument) {
                return argument(dimension_);
            }

            template<std::size_t dimension_>
            inline void access<Eigen::Vector3d, dimension_>::set(Eigen::Vector3d& argument, double value) {
                argument(dimension_) = value;
            }

            template <std::size_t dimension_>
            inline double indexed_access<Eigen::Vector2I, min_corner, dimension_>::get(
                const Eigen::Vector2I& argument
            ) {return argument(dimension_).lower();}

            template <std::size_t dimension_>
            inline void indexed_access<Eigen::Vector2I, min_corner, dimension_>::set(
                Eigen::Vector2I& argument,
                double value
            ) {*reinterpret_cast<double*>(&argument.coeffRef(dimension_)) = value;}

            template <std::size_t dimension_>
            inline double indexed_access<Eigen::Vector2I, max_corner, dimension_>::get(
                const Eigen::Vector2I& argument
            ) {return argument(dimension_).upper();}

            template <std::size_t dimension_>
            inline void indexed_access<Eigen::Vector2I, max_corner, dimension_>::set(
                Eigen::Vector2I& argument,
                double value
            ) {*(reinterpret_cast<double*>(&argument.coeffRef(dimension_)) + 1) = value;}

            template <std::size_t dimension_>
            inline double indexed_access<Eigen::Vector3I, min_corner, dimension_>::get(
                const Eigen::Vector3I& argument
            ) {return argument(dimension_).lower();}

            template <std::size_t dimension_>
            inline void indexed_access<Eigen::Vector3I, min_corner, dimension_>::set(
                Eigen::Vector3I& argument,
                double value
            ) {*reinterpret_cast<double*>(&argument.coeffRef(dimension_)) = value;}

            template <std::size_t dimension_>
            inline double indexed_access<Eigen::Vector3I, max_corner, dimension_>::get(
                const Eigen::Vector3I& argument
            ) {return argument(dimension_).upper();}

            template <std::size_t dimension_>
            inline void indexed_access<Eigen::Vector3I, max_corner, dimension_>::set(
                Eigen::Vector3I& argument,
                double value
            ) {*(reinterpret_cast<double*>(&argument.coeffRef(dimension_)) + 1) = value;}
        }
    }
}

#endif
