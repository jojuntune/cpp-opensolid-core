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

#include <boost/functional/hash.hpp>

#include <OpenSolid/Common/Traits.hpp>
#include <OpenSolid/Common/Comparison.hpp>
#include "Eigen.hpp"

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
    
    template <class ScalarType, int rows_, int cols_>
    struct Traits<Matrix<ScalarType, rows_, cols_>>
    {
        typedef Matrix<Interval, rows_, cols_> Bounds;
        
        static auto bounds(const Matrix<ScalarType, rows_, cols_>& argument) ->
            decltype(argument.cast<Interval>());
            
        static std::size_t hash(const Matrix<ScalarType, rows_, cols_>& argument);
    };
    
    namespace Comparison
    {
        template <class DerivedType>
        bool zero(const EigenBase<DerivedType>& argument);
        
        template <class FirstDerivedType, class SecondDerivedType>
        bool equal(
            const EigenBase<FirstDerivedType>& first_argument,
            const EigenBase<SecondDerivedType>& second_argument
        );
    }
}

////////// Implementation //////////

namespace Eigen
{
    namespace internal
    {
        inline const Interval& conj(const Interval& argument) {return argument;}
    
        inline const Interval& real(const Interval& argument) {return argument;}
    
        inline Interval imag(const Interval&) {return Interval(0.0);}
    
        inline Interval abs2(const Interval& argument) {return argument.squared();}
    
        inline int significant_decimals_default_impl<Interval, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::epsilon() {
        return OpenSolid::Interval(NumTraits<double>::epsilon());
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::dummy_precision() {
        return OpenSolid::Interval(NumTraits<double>::dummy_precision());
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::lowest() {
        return OpenSolid::Interval(NumTraits<double>::lowest());
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::highest() {
        return OpenSolid::Interval(NumTraits<double>::highest());
    }
    
    template <class MatrixType>
    inline typename MatrixType::Scalar ConstMatrixIterator<MatrixType>::dereference() const {
        return (*_matrix)(_index);
    }
    
    template <class MatrixType>
    inline bool ConstMatrixIterator<MatrixType>::equal(
        const ConstMatrixIterator<MatrixType>& other
    ) const {return _index == other._index;}
    
    template <class MatrixType>
    inline bool ConstMatrixIterator<MatrixType>::equal(
        const MatrixIterator<MatrixType>& other
    ) const {return _index == other._index;}
    
    template <class MatrixType>
    inline int ConstMatrixIterator<MatrixType>::distance_to(
        const ConstMatrixIterator<MatrixType>& other
    ) const {return other._index - _index;}
    
    template <class MatrixType>
    inline int ConstMatrixIterator<MatrixType>::distance_to(
        const MatrixIterator<MatrixType>& other
    ) const {return other._index - _index;}
    
    template <class MatrixType>
    inline void ConstMatrixIterator<MatrixType>::increment() {++_index;}
    
    template <class MatrixType>
    inline void ConstMatrixIterator<MatrixType>::decrement() {--_index;}
    
    template <class MatrixType>
    inline void ConstMatrixIterator<MatrixType>::advance(int argument) {_index += argument;}
    
    template <class MatrixType>
    inline ConstMatrixIterator<MatrixType>::ConstMatrixIterator(
        const MatrixType& matrix,
        int index
    ) : _matrix(&matrix), _index(index) {}
    
    template <class MatrixType>
    inline ConstMatrixIterator<MatrixType>::ConstMatrixIterator(
        const ConstMatrixIterator<MatrixType>& other
    ) : _matrix(other._matrix), _index(other._index) {}
    
    template <class MatrixType>
    inline ConstMatrixIterator<MatrixType>::ConstMatrixIterator(
        const MatrixIterator<MatrixType>& other
    ) : _matrix(other._matrix), _index(other._index) {}
    
    template <class MatrixType>
    inline typename MatrixType::Scalar& MatrixIterator<MatrixType>::dereference() const {
        return (*_matrix)(_index);
    }
    
    template <class MatrixType>
    inline bool MatrixIterator<MatrixType>::equal(
        const MatrixIterator<MatrixType>& other
    ) const {return _index == other._index;}
    
    template <class MatrixType>
    inline bool MatrixIterator<MatrixType>::equal(
        const ConstMatrixIterator<MatrixType>& other
    ) const {return _index == other._index;}
    
    template <class MatrixType>
    inline int MatrixIterator<MatrixType>::distance_to(
        const MatrixIterator<MatrixType>& other
    ) const {return other._index - _index;}
    
    template <class MatrixType>
    inline int MatrixIterator<MatrixType>::distance_to(
        const ConstMatrixIterator<MatrixType>& other
    ) const {return other._index - _index;}
    
    template <class MatrixType>
    inline void MatrixIterator<MatrixType>::increment() {++_index;}
    
    template <class MatrixType>
    inline void MatrixIterator<MatrixType>::decrement() {--_index;}
    
    template <class MatrixType>
    inline void MatrixIterator<MatrixType>::advance(int argument) {_index += argument;}
    
    template <class MatrixType>
    inline MatrixIterator<MatrixType>::MatrixIterator(MatrixType& matrix, int index) :
        _matrix(&matrix), _index(index) {}
    
    template <class MatrixType>
    inline MatrixIterator<MatrixType>::MatrixIterator(const MatrixIterator<MatrixType>& other) :
        _matrix(other._matrix), _index(other._index) {}
    
    template <class DerivedType, class MatrixType, class BlockType>
    inline BlockType MatrixBlockIterator<DerivedType, MatrixType, BlockType>::dereference() const {
        return DerivedType::block(*_matrix, _index);
    }
    
    template <class DerivedType, class MatrixType, class BlockType>
    template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
    inline bool MatrixBlockIterator<DerivedType, MatrixType, BlockType>::equal(
        const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
    ) const {return _index == other._index;}
    
    template <class DerivedType, class MatrixType, class BlockType>
    template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
    inline int MatrixBlockIterator<DerivedType, MatrixType, BlockType>::distance_to(
        const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
    ) const {return other._index - _index;}
    
    template <class DerivedType, class MatrixType, class BlockType>
    inline void MatrixBlockIterator<DerivedType, MatrixType, BlockType>::increment() {++_index;}
    
    template <class DerivedType, class MatrixType, class BlockType>
    inline void MatrixBlockIterator<DerivedType, MatrixType, BlockType>::decrement() {--_index;}
    
    template <class DerivedType, class MatrixType, class BlockType>
    inline void MatrixBlockIterator<DerivedType, MatrixType, BlockType>::advance(int argument) {
        _index += argument;
    }
    
    template <class DerivedType, class MatrixType, class BlockType>
    inline MatrixBlockIterator<DerivedType, MatrixType, BlockType>::MatrixBlockIterator(
        MatrixType& matrix,
        int index
    ) : _matrix(&matrix), _index(index) {}
    
    template <class DerivedType, class MatrixType, class BlockType>
    template <class OtherDerivedType, class OtherMatrixType, class OtherBlockType>
    inline MatrixBlockIterator<DerivedType, MatrixType, BlockType>::MatrixBlockIterator(
        const MatrixBlockIterator<OtherDerivedType, OtherMatrixType, OtherBlockType>& other
    ) : _matrix(other._matrix), _index(other._index) {}
    
    template <class MatrixType>
    inline ConstMatrixRowIterator<MatrixType>::ConstMatrixRowIterator(
        const MatrixType& matrix,
        int index
    ) : MatrixBlockIterator<
            ConstMatrixRowIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstRowXpr
        >(matrix, index) {}
    
    template <class MatrixType>
    inline ConstMatrixRowIterator<MatrixType>::ConstMatrixRowIterator(
        const ConstMatrixRowIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            ConstMatrixRowIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstRowXpr
        >(other) {}
    
    template <class MatrixType>
    inline ConstMatrixRowIterator<MatrixType>::ConstMatrixRowIterator(
        const MatrixRowIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            ConstMatrixRowIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstRowXpr
        >(other) {}
    
    template <class MatrixType>
    inline typename MatrixType::ConstRowXpr ConstMatrixRowIterator<MatrixType>::block(
        const MatrixType& matrix,
        int index
    ) {return matrix.row(index);}
    
    template <class MatrixType>
    inline MatrixRowIterator<MatrixType>::MatrixRowIterator(MatrixType& matrix, int index) :
        MatrixBlockIterator<
            MatrixRowIterator<MatrixType>,
            MatrixType,
            typename MatrixType::RowXpr
        >(matrix, index) {}
    
    template <class MatrixType>
    inline MatrixRowIterator<MatrixType>::MatrixRowIterator(
        const MatrixRowIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            MatrixRowIterator<MatrixType>,
            MatrixType,
            typename MatrixType::RowXpr
        >(other) {}
    
    template <class MatrixType>
    inline typename MatrixType::RowXpr MatrixRowIterator<MatrixType>::block(
        MatrixType& matrix,
        int index
    ) {return matrix.row(index);}
    
    template <class MatrixType>
    inline ConstMatrixColIterator<MatrixType>::ConstMatrixColIterator(
        const MatrixType& matrix,
        int index
    ) : MatrixBlockIterator<
            ConstMatrixColIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstColXpr
        >(matrix, index) {}
    
    template <class MatrixType>
    inline ConstMatrixColIterator<MatrixType>::ConstMatrixColIterator(
        const ConstMatrixColIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            ConstMatrixColIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstColXpr
        >(other) {}
    
    template <class MatrixType>
    inline ConstMatrixColIterator<MatrixType>::ConstMatrixColIterator(
        const MatrixColIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            ConstMatrixColIterator<MatrixType>,
            const MatrixType,
            typename MatrixType::ConstColXpr
        >(other) {}
    
    template <class MatrixType>
    inline typename MatrixType::ConstColXpr ConstMatrixColIterator<MatrixType>::block(
        const MatrixType& matrix,
        int index
    ) {return matrix.col(index);}
    
    template <class MatrixType>
    inline MatrixColIterator<MatrixType>::MatrixColIterator(MatrixType& matrix, int index) :
        MatrixBlockIterator<
            MatrixColIterator<MatrixType>,
            MatrixType,
            typename MatrixType::ColXpr
        >(matrix, index) {}
    
    template <class MatrixType>
    inline MatrixColIterator<MatrixType>::MatrixColIterator(
        const MatrixColIterator<MatrixType>& other
    ) : MatrixBlockIterator<
            MatrixColIterator<MatrixType>,
            MatrixType,
            typename MatrixType::ColXpr
        >(other) {}
    
    template <class MatrixType>
    inline typename MatrixType::ColXpr MatrixColIterator<MatrixType>::block(
        MatrixType& matrix,
        int index
    ) {return matrix.col(index);}
    
    inline double LowerOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.lower();
    }
    
    inline double LowerOperation::operator()(double argument) const {return argument;}
    
    inline double UpperOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.upper();
    }
    
    inline double UpperOperation::operator()(double argument) const {return argument;}
    
    inline double MedianOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.median();
    }
    
    inline double MedianOperation::operator()(double argument) const {return argument;}
    
    inline double WidthOperation::operator()(const OpenSolid::Interval& argument) const {
        return argument.width();
    }
    
    inline double WidthOperation::operator()(double argument) const {return 0.0;}
    
    inline OverlapOperation::OverlapOperation(double tolerance_) : tolerance(tolerance_) {}
    
    inline bool OverlapOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.overlap(second_argument, tolerance);}
    
    inline bool OverlapOperation::operator()(double first_argument, double second_argument) const {
        return abs(first_argument - second_argument) <= tolerance;
    }
    
    inline ContainOperation::ContainOperation(double tolerance_) : tolerance(tolerance_) {}
    
    inline bool ContainOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.contain(second_argument, tolerance);}
    
    inline bool ContainOperation::operator()(double first_argument, double second_argument) const {
        return abs(first_argument - second_argument) <= tolerance;
    }
    
    inline OpenSolid::Interval HullOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.hull(second_argument);}
    
    inline OpenSolid::Interval HullOperation::operator()(
        double first_argument,
        double second_argument
    ) const {return OpenSolid::Interval::Hull(first_argument, second_argument);}
    
    inline OpenSolid::Interval IntersectionOperation::operator()(
        const OpenSolid::Interval& first_argument,
        const OpenSolid::Interval& second_argument
    ) const {return first_argument.intersection(second_argument);}
    
    inline OpenSolid::Interval IntersectionOperation::operator()(
        double first_argument,
        double second_argument
    ) const {
        return (first_argument == second_argument) ?
            OpenSolid::Interval(first_argument) :
            OpenSolid::Interval::Empty();
    }
    
    template <class ScalarType, int rows_, int cols_>
    inline std::size_t hash_value(const Matrix<ScalarType, rows_, cols_>& argument) {
        return OpenSolid::Traits<Matrix<ScalarType, rows_, cols_>>::hash(argument);
    }
}

namespace OpenSolid
{   
    template <class ScalarType, int rows_, int cols_>
    inline auto Traits<Matrix<ScalarType, rows_, cols_>>::bounds(
        const Matrix<ScalarType, rows_, cols_>& argument
    ) -> decltype(argument.cast<Interval>()) {return argument.cast<Interval>();}

    template <class ScalarType, int rows_, int cols_>
    struct HashVisitor
    {
        std::size_t result;
        
        inline void init(const ScalarType& value, int row, int col) {
            result = 0;
            boost::hash_combine(result, value);
        }
        
        inline void operator()(const ScalarType& value, int row, int col) {
            boost::hash_combine(result, value);
        }
    };
    
    template <class ScalarType, int rows_, int cols_>
    inline std::size_t Traits<Matrix<ScalarType, rows_, cols_>>::hash(
        const Matrix<ScalarType, rows_, cols_>& argument
    ) {
        HashVisitor<ScalarType, rows_, cols_> visitor;
        argument.visit(visitor);
        return visitor.result;
    }
    
    namespace Comparison
    {
        template <class ScalarType>
        struct ScalarZero
        {
            typedef bool result_type;

            inline bool operator()(ScalarType argument) const {return zero(argument);}
        };

        template <class DerivedType>
        inline bool zero(const EigenBase<DerivedType>& argument) {
            return argument.derived().unaryExpr(ScalarZero<typename DerivedType::Scalar>()).all();
        }

        template <class FirstScalarType, class SecondScalarType>
        struct ScalarEqual
        {
            typedef bool result_type;

            inline bool operator()(
                FirstScalarType first_argument,
                SecondScalarType second_argument
            ) const {return equal(first_argument, second_argument);}
        };
        
        template <class FirstDerivedType, class SecondDerivedType>
        inline bool equal(
            const EigenBase<FirstDerivedType>& first_argument,
            const EigenBase<SecondDerivedType>& second_argument
        ) {
            return first_argument.derived().binaryExpr(
                second_argument.derived(),
                ScalarEqual<
                    typename FirstDerivedType::Scalar,
                    typename SecondDerivedType::Scalar
                >()
            ).all();
        }
    }
}

#endif
