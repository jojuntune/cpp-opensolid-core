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
    template <class TScalar, int iRows, int iCols>
    inline
    Matrix<TScalar, iRows, iCols>::Matrix() {
    }

    template <class TScalar, int iRows, int iCols>
    inline
    Matrix<TScalar, iRows, iCols>::Matrix(int size) :
        detail::MatrixBase<TScalar, iRows, iCols>(size) {
    }

    template <class TScalar, int iRows, int iCols>
    inline
    Matrix<TScalar, iRows, iCols>::Matrix(int rows, int cols) :
        detail::MatrixBase<TScalar, iRows, iCols>(rows, cols) {
    }

    template <class TScalar, int iRows, int iCols>
    inline
    Matrix<TScalar, iRows, iCols>::Matrix(const TScalar* sourcePtr) {
        for (int index = 0; index < this->size(); ++index) {
            this->data()[index] = sourcePtr[index];
        }
    }

    template <class TScalar, int iRows, int iCols>
    inline
    Matrix<TScalar, iRows, iCols>::Matrix(const TScalar* sourcePtr, int size) :
        detail::MatrixBase<TScalar, iRows, iCols>(size) {

        for (int index = 0; index < this->size(); ++index) {
            this->data()[index] = sourcePtr[index];
        }
    }

    template <class TScalar, int iRows, int iCols>
    inline
    Matrix<TScalar, iRows, iCols>::Matrix(const TScalar* sourcePtr, int rows, int cols) :
        detail::MatrixBase<TScalar, iRows, iCols>(rows, cols) {

        for (int index = 0; index < this->size(); ++index) {
            this->data()[index] = sourcePtr[index];
        }
    }

    template <class TScalar, int iRows, int iCols> template <class TOtherDerived>
    inline
    Matrix<TScalar, iRows, iCols>::Matrix(const detail::MatrixInterface<TOtherDerived>& other) :
        detail::MatrixBase<TScalar, iRows, iCols>(other.rows(), other.cols()) {

        detail::MatrixInterface<Matrix<TScalar, iRows, iCols>>::operator=(other);
    }

    template <class TScalar, int iRows, int iCols> template <class TOtherDerived>
    inline
    void
    Matrix<TScalar, iRows, iCols>::operator=(const detail::MatrixInterface<TOtherDerived>& other) {
        detail::MatrixInterface<Matrix<TScalar, iRows, iCols>>::operator=(other);
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Constant(TScalar value) {
        Matrix<TScalar, iRows, iCols> result;
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Constant(int size, TScalar value) {
        Matrix<TScalar, iRows, iCols> result(size);
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Constant(int rows, int cols, TScalar value) {
        Matrix<TScalar, iRows, iCols> result(rows, cols);
        result.setConstant(value);
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Zero() {
        Matrix<TScalar, iRows, iCols> result;
        result.setZero();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Zero(int size) {
        Matrix<TScalar, iRows, iCols> result(size);
        result.setZero();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Zero(int rows, int cols) {
        Matrix<TScalar, iRows, iCols> result(rows, cols);
        result.setZero();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Ones() {
        Matrix<TScalar, iRows, iCols> result;
        result.setOnes();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Ones(int size) {
        Matrix<TScalar, iRows, iCols> result(size);
        result.setOnes();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Ones(int rows, int cols) {
        Matrix<TScalar, iRows, iCols> result(rows, cols);
        result.setOnes();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Identity() {
        Matrix<TScalar, iRows, iCols> result;
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Identity(int size) {
        Matrix<TScalar, iRows, iCols> result(size);
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Identity(int rows, int cols) {
        Matrix<TScalar, iRows, iCols> result(rows, cols);
        result.setIdentity();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Random() {
        Matrix<TScalar, iRows, iCols> result;
        result.setRandom();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Random(int size) {
        Matrix<TScalar, iRows, iCols> result(size);
        result.setRandom();
        return result;
    }

    template <class TScalar, int iRows, int iCols>
    inline
    const Matrix<TScalar, iRows, iCols>
    Matrix<TScalar, iRows, iCols>::Random(int rows, int cols) {
        Matrix<TScalar, iRows, iCols> result(rows, cols);
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
        printMatrixRowColPrefix(int rows, int cols, std::ostream& stream) {
            if (rows == 1 && cols != 1) {
                stream << "Row";
            } else if (cols == 1 && rows != 1) {
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

    template <class TScalar, int iRows, int iCols>
    std::ostream&
    operator<<(std::ostream& stream, const Matrix<TScalar, iRows, iCols>& matrix) {
        int rows = matrix.rows();
        int cols = matrix.cols();
        int size = matrix.size();
        
        detail::printMatrixTypePrefix<TScalar>(stream);
        detail::printMatrixRowColPrefix(rows, cols, stream);
        stream << "Matrix";
        detail::printMatrixSize(rows, stream);
        stream << "x";
        detail::printMatrixSize(cols, stream);
        stream << "([";
        if (rows == 1 || cols == 1) {
            for (int index = 0; index < size; ++index) {
                stream << matrix(index);
                if (index < size - 1) {
                    stream << ", ";
                }
            }
        } else {
            for (int colIndex = 0; colIndex < cols; ++colIndex) {
                stream << "[";
                for (int rowIndex = 0; rowIndex < rows; ++rowIndex) {
                    stream << matrix(rowIndex, colIndex);
                    if (rowIndex < rows - 1) {
                        stream << ", ";
                    }
                }
                stream << "]";
                if (colIndex < cols - 1) {
                    stream << ", ";
                }
            }
        }
        stream << "])";
        
        return stream;
    }
}
