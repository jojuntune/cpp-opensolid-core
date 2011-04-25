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

#ifndef OPENSOLID__TEMPMATRIX_HPP
#define OPENSOLID__TEMPMATRIX_HPP

#include "Matrix.hpp"

namespace opensolid
{
    template <class ScalarType>
    class TempMatrix;
}

namespace Eigen
{
    template <class ScalarType>
    struct ei_traits<opensolid::TempMatrix<ScalarType> >
    {
        typedef Dense StorageKind;
        typedef MatrixXpr XprKind;
        typedef int Index;
        typedef ScalarType Scalar;
        
        static const int RowsAtCompileTime = Dynamic;
        static const int ColsAtCompileTime = Dynamic;
        static const int MaxRowsAtCompileTime = Dynamic;
        static const int MaxColsAtCompileTime = Dynamic;
        static const int InnerStrideAtCompileTime = Dynamic;
        static const int OuterStrideAtCompileTime = Dynamic;
        static const int CoeffReadCost = 2 + NumTraits<ScalarType>::ReadCost;
        
        static const int Flags = DirectAccessBit | NestByRefBit;
    };
}

namespace opensolid
{    
    template <class ScalarType>
    class TempMatrix : public MatrixBase<TempMatrix<ScalarType> >
    {
    private:
        mutable ScalarType* _owned;
        ScalarType* _data;
        int _inner_stride;
        int _outer_stride;
        int _rows;
        int _cols;
        
        void release();
        
        void assign(const TempMatrix<ScalarType>& other);
        
        template <class Derived>
        void assign(const DenseBase<Derived>& other, ei_meta_true);
        
        template <class Derived>
        void assign(const DenseBase<Derived>& other, ei_meta_false);
        
        template <class Derived>
        void assign(const DenseBase<Derived>& vector, int replicate);
    public:
        typedef Matrix<ScalarType, Dynamic, Dynamic> PlainObject;
        typedef PlainObject Nested;
        
        TempMatrix();
        
        TempMatrix(const TempMatrix<ScalarType>& other);
        
        template <class Derived>
        TempMatrix(const DenseBase<Derived>& other);
        
        template <class Derived>
        TempMatrix(const DenseBase<Derived>& vector, int replicate);
        
        TempMatrix(int value);
        TempMatrix(float value);
        TempMatrix(double value);
        TempMatrix(const Interval& value);
        
        ~TempMatrix();
        
        void operator=(const TempMatrix<ScalarType>& other);
        
        template <class Derived>
        void operator=(const DenseBase<Derived>& other);
        
        template <class Derived>
        void setConstant(const DenseBase<Derived>& vector, int replicate);
        
        int innerStride() const;
        int outerStride() const;
        
        int rows() const;
        int cols() const;
        
        const ScalarType coeff(int row, int col) const;
        
        TempMatrix<ScalarType> block(
            int start_row,
            int start_col,
            int num_rows,
            int num_cols
        ) const;
        
        template <int num_rows, int num_cols>
        TempMatrix<ScalarType> block(int start_row, int start_col) const;
        
        TempMatrix<ScalarType> row(int index) const;
        TempMatrix<ScalarType> col(int index) const;
        
        TempMatrix<ScalarType> topRightCorner(int num_rows, int num_cols) const;
        
        template<int num_rows, int num_cols>
        TempMatrix<ScalarType> topRightCorner();
        
        TempMatrix<ScalarType> topLeftCorner(int num_rows, int num_cols) const;
        
        template<int num_rows, int num_cols>
        TempMatrix<ScalarType> topLeftCorner() const;
        
        TempMatrix<ScalarType> bottomRightCorner(int num_rows, int num_cols) const;
        
        template<int num_rows, int num_cols>
        TempMatrix<ScalarType> bottomRightCorner();
        
        TempMatrix<ScalarType> bottomLeftCorner(int num_rows, int num_cols) const;
        
        template<int num_rows, int num_cols>
        TempMatrix<ScalarType> bottomLeftCorner() const;
        
        TempMatrix<ScalarType> topRows(int num_rows) const;
        
        template <int num_rows>
        TempMatrix<ScalarType> topRows() const;
        
        TempMatrix<ScalarType> bottomRows(int num_rows) const;
        
        template <int num_rows>
        TempMatrix<ScalarType> bottomRows() const;
        
        TempMatrix<ScalarType> middleRows(int start_row, int num_rows) const;
        
        template <int num_rows>
        TempMatrix<ScalarType> middleRows(int start_row) const;
        
        TempMatrix<ScalarType> leftCols(int num_cols) const;
        
        template <int num_cols>
        TempMatrix<ScalarType> leftCols() const;
        
        TempMatrix<ScalarType> rightCols(int num_cols) const;
        
        template <int num_cols>
        TempMatrix<ScalarType> rightCols() const;
        
        TempMatrix<ScalarType> middleCols(int start_col, int num_cols) const;
        
        template <int num_cols>
        TempMatrix<ScalarType> middleCols(int start_col) const;
    };
    
    typedef TempMatrix<double> TempMatrixXd;
    typedef TempMatrix<Interval> TempMatrixXI;
}

////////// Implementation //////////

namespace opensolid
{
    template <class ScalarType>
    inline void TempMatrix<ScalarType>::release() {
        if (_owned) {
            delete[] _owned;
            _owned = 0;
        }
    }
    
    template <class ScalarType>
    inline void TempMatrix<ScalarType>::assign(const TempMatrix<ScalarType>& other) {
        _owned = other._owned;
        other._owned = 0;
        _data = other._data;
        _inner_stride = other._inner_stride;
        _outer_stride = other._outer_stride;
        _rows = other._rows;
        _cols = other._cols;
    }
    
    template <class ScalarType> template <class Derived>
    inline void TempMatrix<ScalarType>::assign(const DenseBase<Derived>& other, ei_meta_true) {
        _data = &(const_cast<DenseBase<Derived>&>(other).coeffRef(0, 0));
        if (ei_traits<Derived>::Flags & RowMajorBit) {
            _inner_stride = other.outerStride();
            _outer_stride = other.innerStride();
        } else {
            _inner_stride = other.innerStride();
            _outer_stride = other.outerStride();
        }
        _rows = other.rows();
        _cols = other.cols();
    }
    
    template <class ScalarType> template <class Derived>
    inline void TempMatrix<ScalarType>::assign(const DenseBase<Derived>& other, ei_meta_false) {
        _owned = new ScalarType[other.size()];
        _data = _owned;
        _inner_stride = 1;
        _outer_stride = other.rows();
        _rows = other.rows();
        _cols = other.cols();
        other.evalTo(*this);
    }
        
    template <class ScalarType> template <class Derived>
    inline void TempMatrix<ScalarType>::assign(
        const DenseBase<Derived>& vector,
        int replicate
    ) {
        EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived);
        _data = &(const_cast<DenseBase<Derived>&>(vector).coeffRef(0, 0));
        if (Derived::ColsAtCompileTime == 1) {
            _inner_stride = 1;
            _outer_stride = 0;
            _rows = vector.rows();
            _cols = replicate;
        } else {
            _inner_stride = 0;
            _outer_stride = 1;
            _rows = replicate;
            _cols = vector.cols();
        }
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType>::TempMatrix() {
        _owned = 0;
        _data = 0;
        _inner_stride = 0;
        _outer_stride = 0;
        _rows = 0;
        _cols = 0;
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType>::TempMatrix(const TempMatrix<ScalarType>& other) {assign(other);}
    
    template <class ScalarType> template <class Derived>
    inline TempMatrix<ScalarType>::TempMatrix(const DenseBase<Derived>& other) {
        _owned = 0;
        typename ei_meta_if<
            ei_has_direct_access<Derived>::ret,
            ei_meta_true,
            ei_meta_false
        >::ret flag;
        assign(other, flag);
    }
        
    template <class ScalarType> template <class Derived>
    inline TempMatrix<ScalarType>::TempMatrix(const DenseBase<Derived>& vector, int replicate) {
        _owned = 0;
        assign(vector, replicate);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType>::TempMatrix(int value) {
        _owned = new ScalarType[1];
        _data = _owned;
        *_data = value;
        _inner_stride = 0;
        _outer_stride = 0;
        _rows = 1;
        _cols = 1;
    }
        
    
    template <class ScalarType>
    inline TempMatrix<ScalarType>::TempMatrix(float value) {
        _owned = new ScalarType[1];
        _data = _owned;
        *_data = value;
        _inner_stride = 0;
        _outer_stride = 0;
        _rows = 1;
        _cols = 1;
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType>::TempMatrix(double value) {
        _owned = new ScalarType[1];
        _data = _owned;
        *_data = value;
        _inner_stride = 0;
        _outer_stride = 0;
        _rows = 1;
        _cols = 1;
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType>::TempMatrix(const Interval& value) {
        _owned = new ScalarType[1];
        _data = _owned;
        *_data = value;
        _inner_stride = 0;
        _outer_stride = 0;
        _rows = 1;
        _cols = 1;
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType>::~TempMatrix() {release();}
    
    template <class ScalarType>
    inline void TempMatrix<ScalarType>::operator=(const TempMatrix<ScalarType>& other) {
        release();
        assign(other);
    }
    
    template <class ScalarType> template <class Derived>
    inline void TempMatrix<ScalarType>::operator=(const DenseBase<Derived>& other) {
        typename ei_meta_if<
            ei_has_direct_access<Derived>::ret,
            ei_meta_true,
            ei_meta_false
        >::ret flag;
        release();
        assign(other, flag);
    }
        
    template <class ScalarType> template <class Derived>
    inline void TempMatrix<ScalarType>::setConstant(
        const DenseBase<Derived>& vector,
        int replicate
    ) {
        release();
        assign(vector, replicate);
    }
    
    template <class ScalarType>
    inline int TempMatrix<ScalarType>::innerStride() const {return _inner_stride;}
    
    template <class ScalarType>
    inline int TempMatrix<ScalarType>::outerStride() const {return _outer_stride;}
    
    template <class ScalarType>
    inline int TempMatrix<ScalarType>::rows() const {return _rows;}
    
    template <class ScalarType>
    inline int TempMatrix<ScalarType>::cols() const {return _cols;}
    
    template <class ScalarType>
    inline const ScalarType TempMatrix<ScalarType>::coeff(int row, int col) const {
        return *(_data + row * _inner_stride + col * _outer_stride);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::block(
        int start_row,
        int start_col,
        int num_rows,
        int num_cols
    ) const {
        TempMatrix<ScalarType> result;
        result._owned = _owned;
        result._data = _data + start_row * _inner_stride + start_col * _outer_stride;
        result._inner_stride = _inner_stride;
        result._outer_stride = _outer_stride;
        result._rows = num_rows;
        result._cols = num_cols;
        _owned = 0;
        return result;
    }
    
    template <class ScalarType> template <int num_rows, int num_cols>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::block(
        int start_row,
        int start_col
    ) const {return block(start_row, start_col, num_rows, num_cols);}
        
    template <class ScalarType>
    TempMatrix<ScalarType> TempMatrix<ScalarType>::row(int index) const {
        return block(index, 0, 1, _cols);
    }
    
    template <class ScalarType>
    TempMatrix<ScalarType> TempMatrix<ScalarType>::col(int index) const {
        return block(0, index, _rows, 1);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::topRightCorner(
        int num_rows,
        int num_cols
    ) const {return block(0, _cols - num_cols, num_rows, num_cols);}
    
    template <class ScalarType> template<int num_rows, int num_cols>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::topRightCorner() {
        return block(0, _cols - num_cols, num_rows, num_cols);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::topLeftCorner(
        int num_rows,
        int num_cols
    ) const {return block(0, 0, num_rows, num_cols);}
    
    template <class ScalarType> template<int num_rows, int num_cols>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::topLeftCorner() const {
        return block(0, 0, num_rows, num_cols);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::bottomRightCorner(
        int num_rows,
        int num_cols
    ) const {return block(_rows - num_rows, _cols - num_cols, num_rows, num_cols);}
    
    template <class ScalarType> template<int num_rows, int num_cols>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::bottomRightCorner() {
        return block(_rows - num_rows, _cols - num_cols, num_rows, num_cols);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::bottomLeftCorner(
        int num_rows,
        int num_cols
    ) const {return block(_rows - num_rows, 0, num_rows, num_cols);}
    
    template <class ScalarType> template<int num_rows, int num_cols>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::bottomLeftCorner() const {
        return block(_rows - num_rows, 0, num_rows, num_cols);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::topRows(int num_rows) const {
        return block(0, 0, num_rows, _cols);
    }
    
    template <class ScalarType> template <int num_rows>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::topRows() const {
        return block(0, 0, num_rows, _cols);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::bottomRows(int num_rows) const {
        return block(_rows - num_rows, 0, num_rows, _cols);
    }
    
    template <class ScalarType> template <int num_rows>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::bottomRows() const {
        return block(_rows - num_rows, 0, num_rows, _cols);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::middleRows(
        int start_row,
        int num_rows
    ) const {return block(start_row, 0, num_rows, _cols);}
    
    template <class ScalarType> template <int num_rows>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::middleRows(int start_row) const {
        return block(start_row, 0, num_rows, _cols);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::leftCols(int num_cols) const {
        return block(0, 0, _rows, num_cols);
    }
    
    template <class ScalarType> template <int num_cols>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::leftCols() const {
        return block(0, 0, _rows, num_cols);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::rightCols(int num_cols) const {
        return block(0, _cols - num_cols, _rows, num_cols);
    }
    
    template <class ScalarType> template <int num_cols>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::rightCols() const {
        return block(0, _cols - num_cols, _rows, num_cols);
    }
    
    template <class ScalarType>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::middleCols(
        int start_col,
        int num_cols
    ) const {return block(0, start_col, _rows, num_cols);}
    
    template <class ScalarType> template <int num_cols>
    inline TempMatrix<ScalarType> TempMatrix<ScalarType>::middleCols(int start_col) const {
        return block(0, start_col, _rows, num_cols);
    }
}

#endif
