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

#include <OpenSolid/Common/Bounds.hpp>
#include "Eigen.hpp"

namespace Eigen
{
    typedef Matrix<Interval, 2, 1> Vector2I;
    typedef Matrix<Interval, 1, 2> RowVector2I;
    typedef Matrix<Interval, 2, 2> Matrix2I;
    typedef Matrix<Interval, 3, 1> Vector3I;
    typedef Matrix<Interval, 1, 3> RowVector3I;
    typedef Matrix<Interval, 3, 3> Matrix3I;
    typedef Matrix<Interval, 4, 1> Vector4I;
    typedef Matrix<Interval, 1, 4> RowVector4I;
    typedef Matrix<Interval, 4, 4> Matrix4I;
    typedef Matrix<Interval, Dynamic, 1> VectorXI;
    typedef Matrix<Interval, 1, Dynamic> RowVectorXI;
    typedef Matrix<Interval, Dynamic, Dynamic> MatrixXI;
    typedef Matrix<Interval, 2, Dynamic> Matrix2XI;
    typedef Matrix<Interval, Dynamic, 2> MatrixX2I;
    typedef Matrix<Interval, 3, Dynamic> Matrix3XI;
    typedef Matrix<Interval, Dynamic, 3> MatrixX3I;
    typedef Matrix<Interval, 4, Dynamic> Matrix4XI;
    typedef Matrix<Interval, Dynamic, 4> MatrixX4I;
    
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
    
    typedef Map<MatrixXd, Unaligned, Stride<Dynamic, Dynamic> > MapXd;
    typedef Map<MatrixXI, Unaligned, Stride<Dynamic, Dynamic> > MapXI;
    typedef Map<MatrixXb, Unaligned, Stride<Dynamic, Dynamic> > MapXb;
    
    typedef Map<const MatrixXd, Unaligned, Stride<Dynamic, Dynamic> > MapXcd;
    typedef Map<const MatrixXI, Unaligned, Stride<Dynamic, Dynamic> > MapXcI;
    typedef Map<const MatrixXb, Unaligned, Stride<Dynamic, Dynamic> > MapXcb;
        
    template <class DerivedType>
    std::size_t hash_value(const EigenBase<DerivedType>& argument);
}

namespace OpenSolid
{
    using namespace Eigen;
    
    template <class ScalarType, int rows_, int cols_>
    struct Bounds<Matrix<ScalarType, rows_, cols_> >
    {
        typedef Matrix<Interval, rows_, cols_> Type;
        
        static Matrix<Interval, rows_, cols_> bounds(
            const Matrix<ScalarType, rows_, cols_>& matrix
        );
    };
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
    
    inline Interval NumTraits<Interval>::epsilon() {return Interval(NumTraits<double>::epsilon());}
    
    inline Interval NumTraits<Interval>::dummy_precision() {
        return Interval(NumTraits<double>::dummy_precision());
    }
    
    inline Interval NumTraits<Interval>::lowest() {return Interval(NumTraits<double>::lowest());}
    
    inline Interval NumTraits<Interval>::highest() {return Interval(NumTraits<double>::highest());}
    
    template <class MatrixType>
    inline typename MatrixType::Scalar ConstMatrixIterator<MatrixType>::dereference() const {
        return (*_matrix)(_index);
    }
    
    template <class MatrixType>
    inline bool ConstMatrixIterator<MatrixType>::equal(
        const ConstMatrixIterator<MatrixType>& other
    ) {return _index == other._index;}
    
    template <class MatrixType>
    inline bool ConstMatrixIterator<MatrixType>::equal(const MatrixIterator<MatrixType>& other) {
        return _index == other._index;
    }
    
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
    inline bool MatrixIterator<MatrixType>::equal(const MatrixIterator<MatrixType>& other) {
        return _index == other._index;
    }
    
    template <class MatrixType>
    inline bool MatrixIterator<MatrixType>::equal(const ConstMatrixIterator<MatrixType>& other) {
        return _index == other._index;
    }
    
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
    
    inline double LowerOperation::operator()(const Interval& argument) const {
        return argument.lower();
    }
    
    inline double LowerOperation::operator()(double argument) const {return argument;}
    
    inline double UpperOperation::operator()(const Interval& argument) const {
        return argument.upper();
    }
    
    inline double UpperOperation::operator()(double argument) const {return argument;}
    
    inline double MedianOperation::operator()(const Interval& argument) const {
        return argument.median();
    }
    
    inline double MedianOperation::operator()(double argument) const {return argument;}
    
    inline double WidthOperation::operator()(const Interval& argument) const {
        return argument.width();
    }
    
    inline double WidthOperation::operator()(double argument) const {return 0.0;}
    
    inline OverlapOperation::OverlapOperation(double tolerance_) : tolerance(tolerance_) {}
    
    inline bool OverlapOperation::operator()(
        const Interval& first_argument,
        const Interval& second_argument
    ) const {return first_argument.overlap(second_argument, tolerance);}
    
    inline bool OverlapOperation::operator()(double first_argument, double second_argument) const {
        return abs(first_argument - second_argument) <= tolerance;
    }
    
    inline ContainOperation::ContainOperation(double tolerance_) : tolerance(tolerance_) {}
    
    inline bool ContainOperation::operator()(
        const Interval& first_argument,
        const Interval& second_argument
    ) const {return first_argument.contain(second_argument, tolerance);}
    
    inline bool ContainOperation::operator()(double first_argument, double second_argument) const {
        return abs(first_argument - second_argument) <= tolerance;
    }
    
    inline Interval HullOperation::operator()(
        const Interval& first_argument,
        const Interval& second_argument
    ) const {return first_argument.hull(second_argument);}
    
    inline Interval HullOperation::operator()(double first_argument, double second_argument) const {
        return OpenSolid::BoostInterval::hull(first_argument, second_argument);
    }
    
    inline Interval IntersectionOperation::operator()(
        const Interval& first_argument,
        const Interval& second_argument
    ) const {return first_argument.intersection(second_argument);}
    
    inline Interval IntersectionOperation::operator()(
        double first_argument,
        double second_argument
    ) const {
        return (first_argument == second_argument) ? Interval(first_argument) : Interval::Empty();
    }
    
    template <class DerivedType>
    struct HashVisitor
    {
        typedef typename DerivedType::Scalar ScalarType;
        typedef typename DerivedType::Index IndexType;
    
        std::size_t result;
        
        inline void init(const ScalarType& value, IndexType row, IndexType col) {
            result = 0;
            boost::hash_combine(result, value);
        }
        
        inline void operator()(const ScalarType& value, IndexType row, IndexType col) {
            boost::hash_combine(result, value);
        }
    };
    
    template <class DerivedType>
    inline std::size_t hash_value(const EigenBase<DerivedType>& argument) {
        HashVisitor<DerivedType> visitor;
        argument.derived().visit(visitor);
        return visitor.result;
    }
}

namespace OpenSolid
{
    template <class ScalarType, int rows_, int cols_>
    inline Matrix<Interval, rows_, cols_> Bounds<Matrix<ScalarType, rows_, cols_> >::bounds(
        const Matrix<ScalarType, rows_, cols_>& matrix
    ) {return matrix.template cast<Interval>();}
}

#endif
