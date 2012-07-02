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

#pragma once

#include <OpenSolid/Python/config.hpp>

#include <OpenSolid/Core/Common/Error.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>

#ifdef override
    #define REDEFINE_OVERRIDE
    #undef override
#endif

#include <boost/python.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/slice.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/raw_function.hpp>
#include <boost/python/converter/pytype_function.hpp>

#ifdef REDEFINE_OVERRIDE
    #define override
    #undef REDEFINE_OVERRIDE
#endif

namespace opensolid
{
    class PythonModule
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT static void initialize();
    };

    OPENSOLID_PYTHON_MODULE_EXPORT boost::python::object pythonErrorBaseClass();
}

////////// Errors //////////

namespace opensolid
{
    template <class MatrixType>
    class UnaryMatrixError : public Error
    {
    private:
        MatrixType _matrix;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnaryMatrixError(const MatrixType& matrix);

        OPENSOLID_PYTHON_MODULE_EXPORT ~UnaryMatrixError() throw ();

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

        OPENSOLID_PYTHON_MODULE_EXPORT ~BinaryMatrixError() throw ();
        
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
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~VectorComponentError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
        OPENSOLID_PYTHON_MODULE_EXPORT int index() const;
    };

    typedef VectorComponentError<MatrixXd> MatrixXdVectorComponentError;
    typedef VectorComponentError<MatrixXI> MatrixXIVectorComponentError;

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
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~VectorIndexError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
        OPENSOLID_PYTHON_MODULE_EXPORT boost::python::object index() const;
    };

    typedef VectorIndexError<MatrixXd> MatrixXdVectorIndexError;
    typedef VectorIndexError<MatrixXI> MatrixXIVectorIndexError;

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
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixIndexError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
        OPENSOLID_PYTHON_MODULE_EXPORT boost::python::object rowIndex() const;
        OPENSOLID_PYTHON_MODULE_EXPORT boost::python::object colIndex() const;
    };

    typedef MatrixIndexError<MatrixXd> MatrixXdIndexError;
    typedef MatrixIndexError<MatrixXI> MatrixXIIndexError;

    template <class MatrixType>
    class VectorAssignmentError : public BinaryMatrixError<MatrixType, MatrixType>
    {
    private:
        boost::python::object _index;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT VectorAssignmentError(
            const MatrixType& first_matrix,
            boost::python::object index,
            const MatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~VectorAssignmentError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
        OPENSOLID_PYTHON_MODULE_EXPORT boost::python::object index() const;
    };

    typedef VectorAssignmentError<MatrixXd> MatrixXdVectorAssignmentError;
    typedef VectorAssignmentError<MatrixXI> MatrixXIVectorAssignmentError;

    template <class MatrixType>
    class MatrixAssignmentError : public BinaryMatrixError<MatrixType, MatrixType>
    {
    private:
        boost::python::object _row_index;
        boost::python::object _col_index;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixAssignmentError(
            const MatrixType& first_matrix,
            boost::python::object row_index,
            boost::python::object col_index,
            const MatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixAssignmentError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
        OPENSOLID_PYTHON_MODULE_EXPORT boost::python::object rowIndex() const;
        OPENSOLID_PYTHON_MODULE_EXPORT boost::python::object colIndex() const;
    };

    typedef MatrixAssignmentError<MatrixXd> MatrixXdAssignmentError;
    typedef MatrixAssignmentError<MatrixXI> MatrixXIAssignmentError;

    template <class MatrixType>
    class MatrixSquaredNormError : public UnaryMatrixError<MatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixSquaredNormError(const MatrixType& matrix);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixSquaredNormError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixSquaredNormError<MatrixXd> MatrixXdSquaredNormError;
    typedef MatrixSquaredNormError<MatrixXI> MatrixXISquaredNormError;

    template <class MatrixType>
    class MatrixNormError : public UnaryMatrixError<MatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixNormError(const MatrixType& matrix);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixNormError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixNormError<MatrixXd> MatrixXdNormError;
    typedef MatrixNormError<MatrixXI> MatrixXINormError;

    template <class MatrixType>
    class MatrixNormalizedError : public UnaryMatrixError<MatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixNormalizedError(const MatrixType& matrix);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixNormalizedError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixNormalizedError<MatrixXd> MatrixXdNormalizedError;
    typedef MatrixNormalizedError<MatrixXI> MatrixXINormalizedError;

    template <class MatrixType>
    class MatrixDeterminantError : public UnaryMatrixError<MatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixDeterminantError(const MatrixType& matrix);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixDeterminantError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixDeterminantError<MatrixXd> MatrixXdDeterminantError;
    typedef MatrixDeterminantError<MatrixXI> MatrixXIDeterminantError;

    class MatrixXdInverseError : public UnaryMatrixError<MatrixXd>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixXdInverseError(const MatrixXd& matrix);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixXdInverseError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    template <class MatrixType>
    class MatrixReplicateError : public UnaryMatrixError<MatrixType>
    {
    private:
        int _row_factor;
        int _col_factor;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixReplicateError(
            const MatrixType& matrix,
            int row_factor,
            int col_factor
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixReplicateError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
        OPENSOLID_PYTHON_MODULE_EXPORT int rowFactor() const;
        OPENSOLID_PYTHON_MODULE_EXPORT int colFactor() const;
    };

    typedef MatrixReplicateError<MatrixXd> MatrixXdReplicateError;
    typedef MatrixReplicateError<MatrixXI> MatrixXIReplicateError;

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixDotProductError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixDotProductError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixDotProductError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixDotProductError<MatrixXd, MatrixXd> MatrixXdDotProductMatrixXdError;
    typedef MatrixDotProductError<MatrixXd, MatrixXI> MatrixXdDotProductMatrixXIError;
    typedef MatrixDotProductError<MatrixXI, MatrixXd> MatrixXIDotProductMatrixXdError;
    typedef MatrixDotProductError<MatrixXI, MatrixXI> MatrixXIDotProductMatrixXIError;

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixCrossProductError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixCrossProductError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixCrossProductError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixCrossProductError<MatrixXd, MatrixXd> MatrixXdCrossProductMatrixXdError;
    typedef MatrixCrossProductError<MatrixXd, MatrixXI> MatrixXdCrossProductMatrixXIError;
    typedef MatrixCrossProductError<MatrixXI, MatrixXd> MatrixXICrossProductMatrixXdError;
    typedef MatrixCrossProductError<MatrixXI, MatrixXI> MatrixXICrossProductMatrixXIError;

    class MatrixXIOverlapsMatrixXIError : public BinaryMatrixError<MatrixXI, MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIOverlapsMatrixXIError(
            const MatrixXI& first_matrix,
            const MatrixXI& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixXIOverlapsMatrixXIError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    template <class SecondMatrixType>
    class MatrixXIContainsError : public BinaryMatrixError<MatrixXI, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIContainsError(
            const MatrixXI& first_matrix,
            const SecondMatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixXIContainsError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixXIContainsError<MatrixXd> MatrixXIContainsMatrixXdError;
    typedef MatrixXIContainsError<MatrixXI> MatrixXIContainsMatrixXIError;

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixHullError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixHullError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixHullError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixHullError<MatrixXd, MatrixXd> MatrixXdHullMatrixXdError;
    typedef MatrixHullError<MatrixXd, MatrixXI> MatrixXdHullMatrixXIError;
    typedef MatrixHullError<MatrixXI, MatrixXd> MatrixXIHullMatrixXdError;
    typedef MatrixHullError<MatrixXI, MatrixXI> MatrixXIHullMatrixXIError;

    class MatrixXIIntersectionMatrixXIError : public BinaryMatrixError<MatrixXI, MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixXIIntersectionMatrixXIError(
            const MatrixXI& first_matrix,
            const MatrixXI& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixXIIntersectionMatrixXIError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class MatrixFactoryError : public Error
    {
    private:
        int _rows;
        int _cols;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixFactoryError(int rows, int cols);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixFactoryError() throw ();

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
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~ConstantMatrixConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
        OPENSOLID_PYTHON_MODULE_EXPORT typename MatrixType::Scalar value() const;
    };

    typedef ConstantMatrixConstructionError<MatrixXd> ConstantMatrixXdConstructionError;
    typedef ConstantMatrixConstructionError<MatrixXI> ConstantMatrixXIConstructionError;

    template <class MatrixType>
    class ZeroMatrixConstructionError : public MatrixFactoryError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT ZeroMatrixConstructionError(int rows, int cols);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~ZeroMatrixConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef ZeroMatrixConstructionError<MatrixXd> ZeroMatrixXdConstructionError;
    typedef ZeroMatrixConstructionError<MatrixXI> ZeroMatrixXIConstructionError;

    template <class MatrixType>
    class OnesMatrixConstructionError : public MatrixFactoryError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT OnesMatrixConstructionError(int rows, int cols);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~OnesMatrixConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef OnesMatrixConstructionError<MatrixXd> OnesMatrixXdConstructionError;
    typedef OnesMatrixConstructionError<MatrixXI> OnesMatrixXIConstructionError;

    template <class MatrixType>
    class RandomMatrixConstructionError : public MatrixFactoryError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT RandomMatrixConstructionError(int rows, int cols);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~RandomMatrixConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef RandomMatrixConstructionError<MatrixXd> RandomMatrixXdConstructionError;
    typedef RandomMatrixConstructionError<MatrixXI> RandomMatrixXIConstructionError;

    template <class MatrixType>
    class IdentityMatrixConstructionError : public MatrixFactoryError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT IdentityMatrixConstructionError(int rows, int cols);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~IdentityMatrixConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef IdentityMatrixConstructionError<MatrixXd> IdentityMatrixXdConstructionError;
    typedef IdentityMatrixConstructionError<MatrixXI> IdentityMatrixXIConstructionError;

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixSumError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixSumError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixSumError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixSumError<MatrixXd, MatrixXd> MatrixXdSumMatrixXdError;
    typedef MatrixSumError<MatrixXd, MatrixXI> MatrixXdSumMatrixXIError;
    typedef MatrixSumError<MatrixXI, MatrixXd> MatrixXISumMatrixXdError;
    typedef MatrixSumError<MatrixXI, MatrixXI> MatrixXISumMatrixXIError;

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixDifferenceError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixDifferenceError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixDifferenceError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixDifferenceError<MatrixXd, MatrixXd> MatrixXdDifferenceMatrixXdError;
    typedef MatrixDifferenceError<MatrixXd, MatrixXI> MatrixXdDifferenceMatrixXIError;
    typedef MatrixDifferenceError<MatrixXI, MatrixXd> MatrixXIDifferenceMatrixXdError;
    typedef MatrixDifferenceError<MatrixXI, MatrixXI> MatrixXIDifferenceMatrixXIError;

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
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixQuotientError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
        OPENSOLID_PYTHON_MODULE_EXPORT ScalarType divisor() const;
    };

    typedef MatrixQuotientError<MatrixXd, double> MatrixXdQuotientDoubleError;
    typedef MatrixQuotientError<MatrixXd, Interval> MatrixXdQuotientIntervalError;
    typedef MatrixQuotientError<MatrixXI, double> MatrixXIQuotientDoubleError;
    typedef MatrixQuotientError<MatrixXI, Interval> MatrixXIQuotientIntervalError;

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixProductError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixProductError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixProductError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixProductError<MatrixXd, MatrixXd> MatrixXdProductMatrixXdError;
    typedef MatrixProductError<MatrixXd, MatrixXI> MatrixXdProductMatrixXIError;
    typedef MatrixProductError<MatrixXI, MatrixXd> MatrixXIProductMatrixXdError;
    typedef MatrixProductError<MatrixXI, MatrixXI> MatrixXIProductMatrixXIError;

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixEqualityError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixEqualityError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixEqualityError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixEqualityError<MatrixXd, MatrixXd> MatrixXdEqualityMatrixXdError;
    typedef MatrixEqualityError<MatrixXd, MatrixXI> MatrixXdEqualityMatrixXIError;
    typedef MatrixEqualityError<MatrixXI, MatrixXd> MatrixXIEqualityMatrixXdError;
    typedef MatrixEqualityError<MatrixXI, MatrixXI> MatrixXIEqualityMatrixXIError;

    template <class FirstMatrixType, class SecondMatrixType>
    class MatrixInequalityError : public BinaryMatrixError<FirstMatrixType, SecondMatrixType>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixInequalityError(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixInequalityError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    typedef MatrixInequalityError<MatrixXd, MatrixXd> MatrixXdInequalityMatrixXdError;
    typedef MatrixInequalityError<MatrixXd, MatrixXI> MatrixXdInequalityMatrixXIError;
    typedef MatrixInequalityError<MatrixXI, MatrixXd> MatrixXIInequalityMatrixXdError;
    typedef MatrixInequalityError<MatrixXI, MatrixXI> MatrixXIInequalityMatrixXIError;

    template <class MatrixType>
    class MatrixCopyConstructionError : public Error
    {
    private:
        MatrixType _argument;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT MatrixCopyConstructionError(const MatrixType& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~MatrixCopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT MatrixType argument() const;
    };

    class Vector2dCopyConstructionError : public MatrixCopyConstructionError<MatrixXd>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT Vector2dCopyConstructionError(const MatrixXd& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~Vector2dCopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class Vector3dCopyConstructionError : public MatrixCopyConstructionError<MatrixXd>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT Vector3dCopyConstructionError(const MatrixXd& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~Vector3dCopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class VectorXdCopyConstructionError : public MatrixCopyConstructionError<MatrixXd>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT VectorXdCopyConstructionError(const MatrixXd& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~VectorXdCopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class RowVector2dCopyConstructionError : public MatrixCopyConstructionError<MatrixXd>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT RowVector2dCopyConstructionError(const MatrixXd& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~RowVector2dCopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class RowVector3dCopyConstructionError : public MatrixCopyConstructionError<MatrixXd>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT RowVector3dCopyConstructionError(const MatrixXd& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~RowVector3dCopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class RowVectorXdCopyConstructionError : public MatrixCopyConstructionError<MatrixXd>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT RowVectorXdCopyConstructionError(const MatrixXd& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~RowVectorXdCopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class Matrix2dCopyConstructionError : public MatrixCopyConstructionError<MatrixXd>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT Matrix2dCopyConstructionError(const MatrixXd& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~Matrix2dCopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class Matrix3dCopyConstructionError : public MatrixCopyConstructionError<MatrixXd>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT Matrix3dCopyConstructionError(const MatrixXd& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~Matrix3dCopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class Vector2ICopyConstructionError : public MatrixCopyConstructionError<MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT Vector2ICopyConstructionError(const MatrixXI& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~Vector2ICopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class Vector3ICopyConstructionError : public MatrixCopyConstructionError<MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT Vector3ICopyConstructionError(const MatrixXI& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~Vector3ICopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class VectorXICopyConstructionError : public MatrixCopyConstructionError<MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT VectorXICopyConstructionError(const MatrixXI& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~VectorXICopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class RowVector2ICopyConstructionError : public MatrixCopyConstructionError<MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT RowVector2ICopyConstructionError(const MatrixXI& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~RowVector2ICopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class RowVector3ICopyConstructionError : public MatrixCopyConstructionError<MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT RowVector3ICopyConstructionError(const MatrixXI& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~RowVector3ICopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class RowVectorXICopyConstructionError : public MatrixCopyConstructionError<MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT RowVectorXICopyConstructionError(const MatrixXI& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~RowVectorXICopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class Matrix2ICopyConstructionError : public MatrixCopyConstructionError<MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT Matrix2ICopyConstructionError(const MatrixXI& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~Matrix2ICopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class Matrix3ICopyConstructionError : public MatrixCopyConstructionError<MatrixXI>
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT Matrix3ICopyConstructionError(const MatrixXI& argument);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~Matrix3ICopyConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitVectorConstructionError : public Error
    {
    private:
        int _index;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitVectorConstructionError(int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitVectorConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT int index() const;
    };

    class DynamicUnitVectorConstructionError : public UnitVectorConstructionError
    {
    private:
        int _size;
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT DynamicUnitVectorConstructionError(int size, int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~DynamicUnitVectorConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT int size() const;
    };

    class UnitVector2dConstructionError : public UnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitVector2dConstructionError(int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitVector2dConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitVector3dConstructionError : public UnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitVector3dConstructionError(int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitVector3dConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitVectorXdConstructionError : public DynamicUnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitVectorXdConstructionError(int size, int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitVectorXdConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitRowVector2dConstructionError : public UnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitRowVector2dConstructionError(int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitRowVector2dConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitRowVector3dConstructionError : public UnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitRowVector3dConstructionError(int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitRowVector3dConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitRowVectorXdConstructionError : public DynamicUnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitRowVectorXdConstructionError(int size, int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitRowVectorXdConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitVector2IConstructionError : public UnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitVector2IConstructionError(int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitVector2IConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitVector3IConstructionError : public UnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitVector3IConstructionError(int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitVector3IConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitVectorXIConstructionError : public DynamicUnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitVectorXIConstructionError(int size, int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitVectorXIConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitRowVector2IConstructionError : public UnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitRowVector2IConstructionError(int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitRowVector2IConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitRowVector3IConstructionError : public UnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitRowVector3IConstructionError(int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitRowVector3IConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };

    class UnitRowVectorXIConstructionError : public DynamicUnitVectorConstructionError
    {
    public:
        OPENSOLID_PYTHON_MODULE_EXPORT UnitRowVectorXIConstructionError(int size, int index);
        
        OPENSOLID_PYTHON_MODULE_EXPORT ~UnitRowVectorXIConstructionError() throw ();

        OPENSOLID_PYTHON_MODULE_EXPORT const char* what() const throw() override;
    };
}
