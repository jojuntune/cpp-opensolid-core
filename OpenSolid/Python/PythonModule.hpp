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

#ifndef OPENSOLID__PYTHON__PYTHONMODULE_HPP
#define OPENSOLID__PYTHON__PYTHONMODULE_HPP

#include <OpenSolid/config.hpp>
#include <OpenSolid/Common/Error.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>

#include <boost/python.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/slice.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/raw_function.hpp>
#include <boost/python/converter/pytype_function.hpp>

namespace OpenSolid
{
    class PythonModule
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT static void initialize();
    };
}

////////// Errors //////////

namespace OpenSolid
{
    template <class MatrixType>
    class UnaryMatrixError : public Error
    {
    private:
        MatrixType _matrix;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnaryMatrixError(const MatrixType& matrix);

        OPENSOLID_PYTHON_MODULE_EXPORT MatrixType matrix() const;
    };

    template <class FirstMatrixType, class SecondMatrixType>
    class BinaryMatrixError : public Error
    {
    private:
        FirstMatrixType _first_matrix;
        SecondMatrixType _second_matrix;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT BinaryMatrixError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT FirstMatrixType firstMatrix() const;
        OPENSOLID_PYTHON_MODULE_EXPORT SecondMatrixType secondMatrix() const;
    };

    template <class MatrixType>
    class VectorComponentError : public UnaryMatrixError<MatrixType>
    {
    private:
        int _index;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT VectorComponentError(const MatrixType& matrix, int index);

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
        OPENSOLID_PYTHON_MODULE_EXPORT int index() const;
    };

    template <class MatrixType>
    class VectorIndexError : public UnaryMatrixError<MatrixType>
    {
    private:
        boost::python::object _index;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT VectorIndexError(
            const MatrixType& matrix,
            boost::python::object index
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
        OPENSOLID_PYTHON_MODULE_EXPORT boost::python::object index() const;
    };

    template <class MatrixType>
    class MatrixIndexError : public UnaryMatrixError<MatrixType>
    {
    private:
        boost::python::object _row_index;
        boost::python::object _col_index;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixIndexError(
            const MatrixType& matrix,
            boost::python::object row_index,
            boost::python::object col_index
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
        OPENSOLID_PYTHON_MODULE_EXPORT boost::python::object rowIndex() const;
        OPENSOLID_PYTHON_MODULE_EXPORT boost::python::object colIndex() const;
    };

    template <class MatrixType>
    class VectorSquaredNormError : public UnaryMatrixError<MatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT VectorSquaredNormError(const MatrixType& matrix);

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class MatrixType>
    class VectorNormError : public UnaryMatrixError<MatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT VectorNormError(const MatrixType& matrix);

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class MatrixType>
    class VectorNormalizedError : public UnaryMatrixError<MatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT VectorNormalizedError(const MatrixType& matrix);

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class MatrixType>
    class MatrixDeterminantError : public UnaryMatrixError<MatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixDeterminantError(const MatrixType& matrix);

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    class MatrixInverseError : public UnaryMatrixError<MatrixXd>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixInverseError(const MatrixXd& matrix);

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixDotProductError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixDotProductError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixCrossProductError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixCrossProductError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    class MatrixOverlapsError : public BinaryMatrixError<MatrixXI, MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixOverlapsError(
            const MatrixXI& first_matrix,
            const MatrixXI& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class SecondMatrixType>
    class MatrixContainsError : public BinaryMatrixError<MatrixXI, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixContainsError(
            const MatrixXI& first_matrix,
            const SecondMatrixType& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixHullError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixHullError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    class MatrixIntersectionError : public BinaryMatrixError<MatrixXI, MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixIntersectionError(
            const MatrixXI& first_matrix,
            const MatrixXI& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    class MatrixFactoryError : public Error
    {
    private:
        int _rows;
        int _cols;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixFactoryError(int rows, int cols);

        OPENSOLID_PYTHON_MODULE_EXPORT int rows() const;
        OPENSOLID_PYTHON_MODULE_EXPORT int cols() const;
    };

    template <class MatrixType>
    class ConstantMatrixConstructionError : public MatrixFactoryError
    {
    private:
        typename MatrixType::Scalar _value;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT ConstantMatrixConstructionError(
            int rows,
            int cols,
            typename MatrixType::Scalar value
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
        OPENSOLID_PYTHON_MODULE_EXPORT typename MatrixType::Scalar value() const;
    };

    template <class MatrixType>
    class ZeroMatrixConstructionError : public MatrixFactoryError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT ZeroMatrixConstructionError(int rows, int cols);

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class MatrixType>
    class OnesMatrixConstructionError : public MatrixFactoryError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT OnesMatrixConstructionError(int rows, int cols);

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class MatrixType>
    class RandomMatrixConstructionError : public MatrixFactoryError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT RandomMatrixConstructionError(int rows, int cols);

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class MatrixType>
    class IdentityMatrixConstructionError : public MatrixFactoryError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT IdentityMatrixConstructionError(int rows, int cols);

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixSumError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixSumError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixDifferenceError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixDifferenceError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class MatrixType, class ScalarType>
    class MatrixQuotientError : public UnaryMatrixError<MatrixType>
    {
    private:
        ScalarType _divisor;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixQuotientError(
            const MatrixType& matrix,
            ScalarType divisor
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
        OPENSOLID_PYTHON_MODULE_EXPORT ScalarType divisor() const;
    };

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixProductError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixProductError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixEqualityError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixEqualityError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixInequalityError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixInequalityError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const override;
    };
}

#endif
