/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Matrix.definitions.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix/MatrixBase.hpp>
#include <OpenSolid/Core/MatrixView.hpp>

namespace opensolid
{
    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix() {
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(std::pair<int, int> dimensions) :
        detail::MatrixBase<TScalar, iNumRows, iNumColumns>(dimensions.first, dimensions.second) {
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(const TScalar* sourcePtr) {
        for (int index = 0; index < this->size(); ++index) {
            this->data()[index] = sourcePtr[index];
        }
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const TScalar* sourcePtr,
        std::pair<int, int> dimensions
    ) : detail::MatrixBase<TScalar, iNumRows, iNumColumns>(dimensions.first, dimensions.second) {

        for (int index = 0; index < this->size(); ++index) {
            this->data()[index] = sourcePtr[index];
        }
    }

    template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherDerived>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const detail::MatrixInterface<TOtherDerived>& other
    ) : detail::MatrixBase<TScalar, iNumRows, iNumColumns>(other.numRows(), other.numColumns()) {

        detail::MatrixInterface<Matrix<TScalar, iNumRows, iNumColumns>>::operator=(other);
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    void
    Matrix<TScalar, iNumRows, iNumColumns>::operator=(
        const Matrix<TScalar, iNumRows, iNumColumns>& other
    ) {
        detail::MatrixInterface<Matrix<TScalar, iNumRows, iNumColumns>>::operator=(other);
    }

    template <class TScalar, int iNumRows, int iNumColumns> template <class TOtherDerived>
    inline
    void
    Matrix<TScalar, iNumRows, iNumColumns>::operator=(
        const detail::MatrixInterface<TOtherDerived>& other
    ) {
        detail::MatrixInterface<Matrix<TScalar, iNumRows, iNumColumns>>::operator=(other);
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::constant(TScalar value) {
        Matrix<TScalar, iNumRows, iNumColumns> result;
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::constant(
        std::pair<int, int> dimensions, 
        TScalar value
    ) {
        Matrix<TScalar, iNumRows, iNumColumns> result(dimensions);
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::zero() {
        Matrix<TScalar, iNumRows, iNumColumns> result;
        result.setZero();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::zero(std::pair<int, int> dimensions) {
        Matrix<TScalar, iNumRows, iNumColumns> result(dimensions);
        result.setZero();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::ones() {
        Matrix<TScalar, iNumRows, iNumColumns> result;
        result.setOnes();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::ones(std::pair<int, int> dimensions) {
        Matrix<TScalar, iNumRows, iNumColumns> result(dimensions);
        result.setOnes();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::identity() {
        Matrix<TScalar, iNumRows, iNumColumns> result;
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::identity(std::pair<int, int> dimensions) {
        Matrix<TScalar, iNumRows, iNumColumns> result(dimensions);
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::random() {
        Matrix<TScalar, iNumRows, iNumColumns> result;
        result.setRandom();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::random(std::pair<int, int> dimensions) {
        Matrix<TScalar, iNumRows, iNumColumns> result(dimensions);
        result.setRandom();
        return result;
    }

    namespace detail
    {
        template <class TScalar>
        inline
        void
        printMatrixTypePrefix(std::ostream& stream) {
        }

        template <>
        inline
        void
        printMatrixTypePrefix<Interval>(std::ostream& stream) {
            stream << "Interval";
        }
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<TScalar, iNumRows, iNumColumns>& matrix) {
        char numRowsCharacter = iNumRows == -1 ? 'X' : '0' + iNumRows;
        char numColumnsCharacter = iNumColumns == -1 ? 'X' : '0' + iNumColumns;

        // Print type name
        detail::printMatrixTypePrefix<TScalar>(stream);
        if (iNumRows == iNumColumns) {
            stream << "Matrix" << numRowsCharacter << "d";
        } else if (iNumRows == 1) {
            stream << "RowMatrix" << numColumnsCharacter << "d";
        } else if (iNumColumns == 1) {
            stream << "ColumnMatrix" << numRowsCharacter << "d";
        } else {
            stream << "Matrix" << numRowsCharacter << "x" << numColumnsCharacter;
        }

        // Print component arguments
        stream << "([";
        int numRows = matrix.numRows();
        int numColumns = matrix.numColumns();
        int size = matrix.size();
        if (numRows == 1 || numColumns == 1) {
            for (int index = 0; index < size; ++index) {
                stream << matrix(index);
                if (index < size - 1) {
                    stream << ", ";
                }
            }
        } else {
            for (int columnIndex = 0; columnIndex < numColumns; ++columnIndex) {
                stream << "[";
                for (int rowIndex = 0; rowIndex < numRows; ++rowIndex) {
                    stream << matrix(rowIndex, columnIndex);
                    if (rowIndex < numRows - 1) {
                        stream << ", ";
                    }
                }
                stream << "]";
                if (columnIndex < numColumns - 1) {
                    stream << ", ";
                }
            }
        }
        stream << "])";
        
        return stream;
    }
}
