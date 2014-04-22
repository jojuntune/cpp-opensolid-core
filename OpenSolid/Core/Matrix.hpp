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
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(int size) :
        detail::MatrixBase<TScalar, iNumRows, iNumColumns>(size) {
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(int numRows, int numColumns) :
        detail::MatrixBase<TScalar, iNumRows, iNumColumns>(numRows, numColumns) {
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
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(const TScalar* sourcePtr, int size) :
        detail::MatrixBase<TScalar, iNumRows, iNumColumns>(size) {

        for (int index = 0; index < this->size(); ++index) {
            this->data()[index] = sourcePtr[index];
        }
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    Matrix<TScalar, iNumRows, iNumColumns>::Matrix(
        const TScalar* sourcePtr,
        int numRows, int
        numColumns
    ) : detail::MatrixBase<TScalar, iNumRows, iNumColumns>(numRows, numColumns) {

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
    Matrix<TScalar, iNumRows, iNumColumns>::Constant(TScalar value) {
        Matrix<TScalar, iNumRows, iNumColumns> result;
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Constant(int size, TScalar value) {
        Matrix<TScalar, iNumRows, iNumColumns> result(size);
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Constant(int numRows, int numColumns, TScalar value) {
        Matrix<TScalar, iNumRows, iNumColumns> result(numRows, numColumns);
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Zero() {
        Matrix<TScalar, iNumRows, iNumColumns> result;
        result.setZero();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Zero(int size) {
        Matrix<TScalar, iNumRows, iNumColumns> result(size);
        result.setZero();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Zero(int numRows, int numColumns) {
        Matrix<TScalar, iNumRows, iNumColumns> result(numRows, numColumns);
        result.setZero();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Ones() {
        Matrix<TScalar, iNumRows, iNumColumns> result;
        result.setOnes();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Ones(int size) {
        Matrix<TScalar, iNumRows, iNumColumns> result(size);
        result.setOnes();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Ones(int numRows, int numColumns) {
        Matrix<TScalar, iNumRows, iNumColumns> result(numRows, numColumns);
        result.setOnes();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Identity() {
        Matrix<TScalar, iNumRows, iNumColumns> result;
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Identity(int size) {
        Matrix<TScalar, iNumRows, iNumColumns> result(size);
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Identity(int numRows, int numColumns) {
        Matrix<TScalar, iNumRows, iNumColumns> result(numRows, numColumns);
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Random() {
        Matrix<TScalar, iNumRows, iNumColumns> result;
        result.setRandom();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Random(int size) {
        Matrix<TScalar, iNumRows, iNumColumns> result(size);
        result.setRandom();
        return result;
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    inline
    const Matrix<TScalar, iNumRows, iNumColumns>
    Matrix<TScalar, iNumRows, iNumColumns>::Random(int numRows, int numColumns) {
        Matrix<TScalar, iNumRows, iNumColumns> result(numRows, numColumns);
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

        inline
        void
        printMatrixRowColPrefix(int numRows, int numColumns, std::ostream& stream) {
            if (numRows == 1 && numColumns != 1) {
                stream << "Row";
            } else if (numColumns == 1 && numRows != 1) {
                stream << "Col";
            }
        }

        inline
        void
        printMatrixSize(int size, std::ostream& stream) {
            if (size == -1) {
                stream << "X";
            } else {
                stream << size;
            }
        }
    }

    template <class TScalar, int iNumRows, int iNumColumns>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<TScalar, iNumRows, iNumColumns>& matrix) {
        int numRows = matrix.numRows();
        int numColumns = matrix.numColumns();
        int size = matrix.size();
        
        detail::printMatrixTypePrefix<TScalar>(stream);
        detail::printMatrixRowColPrefix(numRows, numColumns, stream);
        stream << "Matrix";
        detail::printMatrixSize(numRows, stream);
        stream << "x";
        detail::printMatrixSize(numColumns, stream);
        stream << "([";
        if (numRows == 1 || numColumns == 1) {
            for (int index = 0; index < size; ++index) {
                stream << matrix(index);
                if (index < size - 1) {
                    stream << ", ";
                }
            }
        } else {
            for (int colIndex = 0; colIndex < numColumns; ++colIndex) {
                stream << "[";
                for (int rowIndex = 0; rowIndex < numRows; ++rowIndex) {
                    stream << matrix(rowIndex, colIndex);
                    if (rowIndex < numRows - 1) {
                        stream << ", ";
                    }
                }
                stream << "]";
                if (colIndex < numColumns - 1) {
                    stream << ", ";
                }
            }
        }
        stream << "])";
        
        return stream;
    }
}
