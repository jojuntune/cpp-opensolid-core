/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
*************************************************************************************/

#include "MatrixHandle.hpp"
#include <OpenSolid/Python/PythonEnvironment.hpp>

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
    int MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::rows() const {
        return derived().readAccess().rows();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    int MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::cols() const {
        return derived().readAccess().cols();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    int MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::size() const {
        return derived().readAccess().size();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::value() const {
        if (derived().readAccess().size() != 1) {
            throw MatrixValueError<MatrixType>(derived().readAccess());
        }
        return derived().readAccess().value();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::x() const {
        if (derived().readAccess().cols() != 1 && derived().readAccess().rows() != 1) {
            throw VectorComponentError<MatrixType>(derived().readAccess(), 0);
        }
        return derived().readAccess()(0);
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::y() const {
        if (
            derived().readAccess().size() < 2 ||
            (derived().readAccess().cols() != 1 && derived().readAccess().rows() != 1)
        ) {throw VectorComponentError<MatrixType>(derived().readAccess(), 1);}
        return derived().readAccess()(1);
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::z() const {
        if (
            derived().readAccess().size() < 3 ||
            (derived().readAccess().cols() != 1 && derived().readAccess().rows() != 1)
        ) {throw VectorComponentError<MatrixType>(derived().readAccess(), 2);}
        return derived().readAccess()(2);
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
            if (derived().readAccess().cols() == 1) {
                return derived().readAccess()(positiveIndex(index, derived().readAccess().rows()), 0);
            } else if (derived().readAccess().rows() == 1) {
                return derived().readAccess()(0, positiveIndex(index, derived().readAccess().cols()));
            } else {
                throw IndexError();
            }
        } catch (const IndexError&) {
            throw VectorIndexError<MatrixType>(derived().readAccess(), object(index));
        }
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemS(slice indices) const {
        try {
            int block_start = 0;
            int block_size = 0;
            if (derived().readAccess().cols() == 1) {
                getComponentBlock(indices, derived().readAccess().rows(), block_start, block_size);
                return MatrixHandleType(
                    new MatrixType(derived().readAccess().block(block_start, 0, block_size, 1))
                );
            } else if (derived().readAccess().rows() == 1) {
                getComponentBlock(indices, derived().readAccess().cols(), block_start, block_size);
                return MatrixHandleType(
                    new MatrixType(derived().readAccess().block(0, block_start, 1, block_size))
                );
            } else {
                throw IndexError();
            }
        } catch (const IndexError&) {
            throw VectorIndexError<MatrixType>(derived().readAccess(), indices);
        }
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemII(int row, int col) const {
        try {
            row = positiveIndex(row, derived().readAccess().rows());
            col = positiveIndex(col, derived().readAccess().cols());
            return derived().readAccess()(row, col);
        } catch (const IndexError&) {
            throw MatrixIndexError<MatrixType>(derived().readAccess(), object(row), object(col));
        }
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemIS(int row, slice cols) const {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemSI(slice rows, int col) const {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::getItemSS(slice rows, slice cols) const {
        // TODO
        return MatrixHandleType();
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
    MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::begin() const {
        // TODO
        return MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>
    MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::end() const {
        // TODO
        return MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>();
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::squaredNorm() const {
        // TODO
        return ScalarType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::norm() const {
        // TODO
        return ScalarType();
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::determinant() const {
        // TODO
        return ScalarType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::trace() const {
        // TODO
        return ScalarType();
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::transpose() const {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::replicate(
        int row_factor,
        int col_factor
    ) const {
        // TODO
        return MatrixHandleType();
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    bool MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::isZero() const {
        // TODO
        return false;
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    bool MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::isZeroP(double precision) const {
        // TODO
        return false;
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::transformed(
        const MatrixXdHandle& matrix,
        const MatrixXdHandle& vector
    ) const {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::scaled(
        double scale,
        const MatrixXdHandle& point
    ) const {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::translatedV(
        const MatrixXdHandle& vector
    ) const {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::translatedD(
        double distance,
        const DatumXd& axis
    ) const {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::rotatedP(
        double angle,
        const MatrixXdHandle& point
    ) {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::rotatedA(
        double angle,
        const DatumXd& axis
    ) {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::mirrored(
        const DatumXd& plane
    ) {
        // TODO
        return MatrixHandleType();
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::Constant(
        int rows,
        int cols,
        const ScalarType& value
    ) {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::Zero(
        int rows,
        int cols
    ) {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::Ones(
        int rows,
        int cols
    ) {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::Random(
        int rows,
        int cols
    ) {
        // TODO
        return MatrixHandleType();
    }
    
    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleType MatrixHandle<MatrixHandleType, MatrixType, ScalarType>::Identity(
        int rows,
        int cols
    ) {
        // TODO
        return MatrixHandleType();
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>::MatrixHandleIterator() {
        // TODO
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>::MatrixHandleIterator(
        const MatrixHandleType& matrix_handle,
        int index
    ) {
        // TODO
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>&
    MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>::operator++() const {
        // TODO
        return *this;
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    ScalarType MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>::operator*() const {
        // TODO
        return ScalarType();
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    bool MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>::operator==(
        const MatrixHandleIterator& other
    ) const {
        // TODO
        return false;
    }

    template <class MatrixHandleType, class MatrixType, class ScalarType>
    bool MatrixHandleIterator<MatrixHandleType, MatrixType, ScalarType>::operator<(
        const MatrixHandleIterator& other
    ) const {
        // TODO
        return false;
    }
}
