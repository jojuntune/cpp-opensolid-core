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

#include <opensolid/detail/MatrixHandle.hpp>

namespace opensolid
{
    using namespace boost::python;

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    const MatrixHandleType&
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::derived() const {
        return static_cast<const MatrixHandleType&>(*this);
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType&
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::derived() {
        return static_cast<MatrixHandleType&>(*this);
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    const MatrixType&
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::readAccess() const {
        return derived().readAccess();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixType&
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::writeAccess() {
        return derived().writeAccess();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    int MatrixHandle<MatrixHandleType, ScalarType>::rows() const {
        return readAccess().rows();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    int MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::cols() const {
        return readAccess().cols();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    int MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::size() const {
        return readAccess().size();
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::value() const {
        if (readAccess().size() != 1) {throw MatrixValueError<MatrixType>(readAccess());}
        return readAccess().value();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::x() const {
        if (!(readAccess().cols() == 1 || readAccess().rows() == 1)) {
            throw VectorComponentError<MatrixType>(readAccess(), 0);
        }
        return readAccess().x();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::y() const {
        if (readAccess().size() < 2 || !(readAccess().cols() == 1 || readAccess().rows() == 1)) {
            throw VectorComponentError<MatrixType>(readAccess(), 1);
        }
        return readAccess().y();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::z() const {
        if (readAccess().size() < 3 || (readAccess().cols() != 1 && readAccess().rows() != 1)) {
            throw VectorComponentError<MatrixType>(readAccess(), 2);
        }
        return readAccess().z();
    }

    struct IndexError
    {
    };
        
    int positiveIndex(int index, int size) {
        if (index < -size || index >= size) {throw IndexError();}
        return index >= 0 ? index : size + index;
    }
    
    void getComponentBlock(slice indices, int size, int& block_start, int& block_size) {
        if (!indices.step().is_none()) {throw IndexError();}
        if (indices.start() == object()) {
            block_start = 0;
        } else {
            boost::python::extract<int> extracted_start(indices.start());
            if (!extracted_start.check()) {throw IndexError();}
            block_start = extracted_start;
        }
        if (indices.stop() == object()) {
            block_size = block_start < 0 ? -block_start : size - block_start;
        } else {
            extract<int> extracted_stop(indices.stop());
            if (!extracted_stop.check()) {throw IndexError();}
            block_size = extracted_stop;
        }
        if (block_size <= 0) {throw IndexError();}
        if (block_start < 0) {
            if (block_start < -size || block_size > -block_start) {throw IndexError();}
        } else {
            if (block_start + block_size > size) {throw IndexError();}
        }
        if (block_start < 0) {block_start += size;}
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemI(int index) const {
        try {
            if (readAccess().cols() == 1) {
                return readAccess()(positiveIndex(index, matrix.rows()), 0);
            } else if (readAccess().rows() == 1) {
                return readAccess()(0, positiveIndex(index, matrix.cols()));
            } else {
                throw IndexError();
            }
        } catch (const IndexError&) {
            throw VectorIndexError<MatrixType>(readAccess(), object(index));
        }
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemS(slice indices) const {
        try {
            int block_start = 0;
            int block_size = 0;
            if (readAccess().cols() == 1) {
                getComponentBlock(indices, readAccess().rows(), block_start, block_size);
                return MatrixHandleType(
                    new MatrixType(readAccess().block(block_start, 0, block_size, 1))
                );
            } else if (readAccess().rows() == 1) {
                getComponentBlock(indices, readAccess().cols(), block_start, block_size);
                return MatrixHandleType(
                    new MatrixType(readAccess().block(0, block_start, 1, block_size))
                );
            } else {
                throw IndexError();
            }
        } catch (const IndexError&) {
            throw VectorIndexError<MatrixType>(readAccess(), indices);
        }
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemII(int row, int col) const {
        try {
            row = positiveIndex(row, readAccess().rows());
            col = positiveIndex(col, readAccess().cols());
            return readAccess()(row, col);
        } catch (const IndexError&) {
            throw MatrixIndexError<MatrixType>(readAccess(), object(row), object(col));
        }
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemIS(int row, slice cols) const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemSI(slice rows, int col) const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemSS(slice rows, slice cols) const {
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    void MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::setItemI(
        int index,
        const ScalarType& argument
    ) {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    void MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::setItemS(
        slice indices,
        const MatrixHandleType& argument
    ) {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    void MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::setItemII(
        int row,
        int col,
        const ScalarType& argument
    ) {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    void MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::setItemIS(
        int row,
        slice cols,
        const MatrixHandleType& argument
    ) {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    void MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::setItemSI(
        slice rows,
        int col,
        const MatrixHandleType& argument
    ) {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    void MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::setItemSS(
        slice rows,
        slice cols,
        const MatrixHandleType& argument
    ) {
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleIterator<MatrixHandleType>
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::begin() const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleIterator<MatrixHandleType>
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::end() const {
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::squaredNorm() const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::norm() const {
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::determinant() const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::trace() const {
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::transpose() const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::replicate(
        int row_factor,
        int col_factor
    ) const {
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    bool MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::isZero() const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    bool MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::isZeroP(double precision) const {
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::transformed(
        const MatrixXdHandle& matrix,
        const MatrixXdHandle& vector
    ) const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::scaled(
        double scale,
        const MatrixXdHandle& point
    ) const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::translatedV(
        const MatrixXdHandle& vector
    ) const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::translatedD(
        double distance,
        const DatumXd& axis
    ) const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::rotatedP(
        double angle,
        const MatrixXdHandle& point
    ) {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::rotatedA(
        double angle,
        const DatumXd& axis
    ) {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::mirrored(
        const DatumXd& plane
    ) {
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::Constant(
        int rows,
        int cols,
        const ScalarType& value
    ) {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::Zero(
        int rows,
        int cols
    ) const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::Ones(
        int rows,
        int cols
    ) const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::Random(
        int rows,
        int cols
    ) const {
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::Identity(
        int rows,
        int cols
    ) const {
    }

    template <class MatrixHandleType, class ScalarType>
    class MatrixHandleIterator
    {
    private:
        MatrixHandleType _matrix_handle;
        int _index;
    public:
        typedef ScalarType value_type;

        MatrixHandleIterator();
        MatrixHandleIterator(const MatrixHandleType& matrix_handle, int index);

        MatrixHandleIterator& operator++() const;
        ScalarType operator*() const;
        bool operator==(const MatrixHandleIterator& other) const;
        bool operator<(const MatrixHandleIterator& other) const;
    };
}
