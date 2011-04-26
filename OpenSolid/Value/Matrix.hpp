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

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Common/Pair.hpp>
#include <OpenSolid/Collection/IteratorRange.hpp>
#include "Eigen.hpp"
#include "Interval.hpp"

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
}

namespace opensolid
{
    template <class ScalarType, int rows_, int cols_>
    struct Bounds<Matrix<ScalarType, rows_, cols_> >
    {
        typedef Matrix<Interval, rows_, cols_> Type;
        
        static Matrix<Interval, rows_, cols_> bounds(
            const Matrix<ScalarType, rows_, cols_>& matrix
        );
    };
    
    template <class ScalarType, int rows_, int cols_>
    class Bisected<Matrix<ScalarType, rows_, cols_> >
    {
    private:
        const Matrix<ScalarType, rows_, cols_>& _argument;
    public:
        Bisected(const Matrix<ScalarType, rows_, cols_>& argument);
        
        const Matrix<ScalarType, rows_, cols_>& argument() const;
    };
    
    template <class ScalarType, int rows_, int cols_>
    class Pair<Matrix<ScalarType, rows_, cols_>&>
    {
    private:
        Matrix<ScalarType, rows_, cols_>& _first_argument;
        Matrix<ScalarType, rows_, cols_>& _second_argument;
    public:
        Pair(
            Matrix<ScalarType, rows_, cols_>& first_argument,
            Matrix<ScalarType, rows_, cols_>& second_argument
        );
        
        template <class OtherMatrixType>
        void operator=(const Bisected<OtherMatrixType>& bisected);
    };
    
    template <class ScalarType, int rows_, int cols_>
    class Pair<Matrix<ScalarType, rows_, cols_> >
    {
    private:
        Matrix<ScalarType, rows_, cols_> _first;
        Matrix<ScalarType, rows_, cols_> _second;
    public:
        Pair(
            const Matrix<ScalarType, rows_, cols_>& first,
            const Matrix<ScalarType, rows_, cols_>& second
        );
        
        template <class OtherMatrixType>
        Pair(const Bisected<OtherMatrixType>& bisected);
        
        template <class OtherMatrixType>
        void operator=(const Bisected<OtherMatrixType>& bisected);
        
        const Matrix<ScalarType, rows_, cols_>& first() const;
        const Matrix<ScalarType, rows_, cols_>& second() const;
    };
}

////////// Implementation //////////

namespace Eigen
{
    template <class DerivedType, class MatrixType, class BlockType>
    inline BlockType MatrixBlockIterator<DerivedType, MatrixType, BlockType>::dereference() const {
        return DerivedType::block(_matrix, _index);
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
    ) : _matrix(matrix), _index(index) {}
    
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
    
    
    template <class DerivedType>
    inline MatrixListAdapter<DerivedType>::MatrixListAdapter(const DerivedType& matrix) :
        _matrix(matrix) {}
    
    template <class DerivedType>
    inline int MatrixListAdapter<DerivedType>::size() const {return _matrix.cols();}
    
    template <class DerivedType>
    inline bool MatrixListAdapter<DerivedType>::empty() const {return _matrix.cols() == 0;}
    
    template <class DerivedType> template <class VisitorType>
    inline void MatrixListAdapter<DerivedType>::visit(const VisitorType& visitor) const {
        opensolid::IteratorRange<Iterator>(begin(), end()).visit(visitor);
    }
    
    template <class DerivedType>
    inline typename Bounds<typename DerivedType::ConstColXpr::PlainObject>::Type
    MatrixListAdapter<DerivedType>::bounds() const {
        typename Bounds<typename DerivedType::ConstColXpr::PlainObject>::Type result =
            _matrix.col(0).template cast<Interval>();
        for (int i = 1; i < _matrix.cols(); ++i) {
            result = result.hull(_matrix.col(i));
        }
        return result;
    }
    
    template <class DerivedType>
    inline typename DerivedType::ConstColIterator MatrixListAdapter<DerivedType>::begin() const {
        return _matrix.colBegin();
    }
    
    template <class DerivedType>
    inline typename DerivedType::ConstColIterator MatrixListAdapter<DerivedType>::end() const {
        return _matrix.colEnd();
    }
    
    template <class DerivedType>
    inline typename DerivedType::ConstColXpr MatrixListAdapter<DerivedType>::front() const {
        return _matrix.col(0);
    }
    
    template <class DerivedType>
    inline typename DerivedType::ConstColXpr MatrixListAdapter<DerivedType>::back() const {
        return _matrix.col(_matrix.cols() - 1);
    }
    
    template <class DerivedType>
    inline typename DerivedType::ConstColXpr MatrixListAdapter<DerivedType>::operator[](
        int index
    ) const {return _matrix.col(index);}
    
    inline bool ContainOperation::operator()(
        const Interval& first_argument,
        const Interval& second_argument
    ) const {return first_argument.contain(second_argument);}
    
    inline bool ContainOperation::operator()(double first_argument, double second_argument) const {
        return first_argument == second_argument;
    }
    
    inline bool OverlapOperation::operator()(
        const Interval& first_argument,
        const Interval& second_argument
    ) const {return first_argument.overlap(second_argument);}
    
    inline bool OverlapOperation::operator()(double first_argument, double second_argument) const {
        return first_argument == second_argument;
    }
        
    inline bool AdjacentOperation::operator()(
        const Interval& first_argument,
        const Interval& second_argument
    ) const {return first_argument.adjacent(second_argument);}
    
    inline bool AdjacentOperation::operator()(double first_argument, double second_argument) const {
        return first_argument == second_argument;
    }
    
    inline Interval HullOperation::operator()(
        const Interval& first_argument,
        const Interval& second_argument
    ) const {return first_argument.hull(second_argument);}
    
    inline Interval HullOperation::operator()(double first_argument, double second_argument) const {
        if (second_argument >= first_argument) {
            return Interval(first_argument, second_argument);
        } else {
            return Interval(second_argument, first_argument);
        }
    }
    
    inline Interval IntersectionOperation::operator()(
        const Interval& first_argument,
        const Interval& second_argument
    ) const {return first_argument.intersection(second_argument);}
    
    inline Interval IntersectionOperation::operator()(
        double first_argument,
        double second_argument
    ) const {
        if (first_argument == second_argument) {
            return Interval(first_argument);
        } else {
            return Interval::empty();
        }
    }
    
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
    
    inline Interval CenteredOperation::operator()(const Interval& argument) const {
        return argument.centered();
    }
    
    inline Interval CenteredOperation::operator()(double argument) const {return argument;}
}

namespace opensolid
{
    template <class ScalarType, int rows_, int cols_>
    inline Matrix<Interval, rows_, cols_> Bounds<Matrix<ScalarType, rows_, cols_> >::bounds(
        const Matrix<ScalarType, rows_, cols_>& matrix
    ) {return matrix.template cast<Interval>();}
 
    template <class ScalarType, int rows_, int cols_>
    inline Bisected<Matrix<ScalarType, rows_, cols_> >::Bisected(
        const Matrix<ScalarType, rows_, cols_>& argument
    ) : _argument(argument) {}
    
    template <class ScalarType, int rows_, int cols_>
    inline const Matrix<ScalarType, rows_, cols_>&
    Bisected<Matrix<ScalarType, rows_, cols_> >::argument() const {return _argument;}
    
    template <class ScalarType, int rows_, int cols_>
    inline Pair<Matrix<ScalarType, rows_, cols_>&>::Pair(
        Matrix<ScalarType, rows_, cols_>& first_argument,
        Matrix<ScalarType, rows_, cols_>& second_argument
    ) : _first_argument(first_argument), _second_argument(second_argument) {}
    
    template <class ScalarType, int rows_, int cols_> template <class OtherMatrixType>
    inline void Pair<Matrix<ScalarType, rows_, cols_>&>::operator=(
        const Bisected<OtherMatrixType>& bisected
    ) {
        _first_argument = bisected.argument();
        _second_argument = bisected.argument();
        typename OtherMatrixType::Index row;
        typename OtherMatrixType::Index col;
        bisected.argument().cwiseWidth().maxCoeff(&row, &col);
        double median = bisected.argument()(row, col).median();
        _first_argument(row, col).upper() = median;
        _second_argument(row, col).lower() = median;
    }
    
    template <class ScalarType, int rows_, int cols_>
    inline Pair<Matrix<ScalarType, rows_, cols_> >::Pair(
        const Matrix<ScalarType, rows_, cols_>& first,
        const Matrix<ScalarType, rows_, cols_>& second
    ) : _first(first), _second(second) {}
    
    template <class ScalarType, int rows_, int cols_> template <class OtherMatrixType>
    inline Pair<Matrix<ScalarType, rows_, cols_> >::Pair(
        const Bisected<OtherMatrixType>& bisected
    ) {Pair<Matrix<ScalarType, rows_, cols_>&>(_first, _second) = bisected;}
    
    template <class ScalarType, int rows_, int cols_> template <class OtherMatrixType>
    inline void Pair<Matrix<ScalarType, rows_, cols_> >::operator=(
        const Bisected<OtherMatrixType>& bisected
    ) {Pair<Matrix<ScalarType, rows_, cols_>&>(_first, _second) = bisected;}
    
    template <class ScalarType, int rows_, int cols_>
    inline const Matrix<ScalarType, rows_, cols_>&
    Pair<Matrix<ScalarType, rows_, cols_> >::first() const {return _first;}
    
    template <class ScalarType, int rows_, int cols_>
    inline const Matrix<ScalarType, rows_, cols_>&
    Pair<Matrix<ScalarType, rows_, cols_> >::second() const {return _second;}
}

#endif
