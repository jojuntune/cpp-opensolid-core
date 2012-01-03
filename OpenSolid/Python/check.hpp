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

#ifndef OPENSOLID__PYTHON__CHECK_HPP
#define OPENSOLID__PYTHON__CHECK_HPP

#include <OpenSolid/config.hpp>

#include <string>

#include <OpenSolid/Common/Error.hpp>
#include <OpenSolid/Scalar/Interval.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Datum/Datum.hpp>
#include <OpenSolid/Simplex/Simplex.hpp>
#include <OpenSolid/Set/Set.hpp>
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>
#include <OpenSolid/Domain/Domain.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

namespace OpenSolid
{
    /// Check that a Python object is convertible to a desired type.
    template <>
    struct Check<1>
    {
        /// Perform the actual check.
        template <class ExpectedType>
        static void CompatibleType(const boost::python::object& python_object);
    };

    typedef Check<1> CheckConvertible;
    
    /// Check that a scalar value is non-zero.
    template <>
    struct Check<2>
    {
        /// Perform the actual check.
        OPENSOLID_PYTHON_MODULE_EXPORT static void NonZero(double value);
    };
    
    /// Check that two generic sizes are equal.
    template <>
    struct Check<3>
    {
        /// Perform the actual check.
        OPENSOLID_PYTHON_MODULE_EXPORT static void EqualSizes(int first_size, int second_size);
    };
    
    /// Check that two dimensions (e.g., of two  vectors to be added) are equal.
    template <>
    struct Check<4>
    {
        /// Perform the actual check.
        OPENSOLID_PYTHON_MODULE_EXPORT static void EqualDimensions(
            int first_dimensions,
            int second_dimensions
        );
    };
    
    /// Check that a matrix is actually a single scalar value.
    template <>
    struct Check<5>
    {
        /// Perform the actual check.
        template <class MatrixType>
        static void ScalarValue(const MatrixType& matrix);
    };
    
    /// Check that a matrix is actually a vector, i.e., has one column.
    template <>
    struct Check<6>
    {
        /// Perform the actual check.
        template <class MatrixType>
        static void VectorValue(const MatrixType& matrix);
    };
    
    /// Check that a matrix is actually a row vector.
    template<>
    struct Check<7>
    {
        /// Perform the actual check.
        template <class MatrixType>
        static void RowVectorValue(const MatrixType& matrix);
    };
    
    /// Check that a matrix is actually a vector or row vector.
    template <>
    struct Check<8>
    {
        /// Perform the actual check.
        template <class MatrixType>
        static void VectorOrRowVectorValue(const MatrixType& matrix);
    };
    
    /// Check that two matrices are the same size.
    template <>
    struct Check<9>
    {
        /// Perform the actual check.
        template <class FirstMatrixType, class SecondMatrixType>
        static void SameSizeMatrices(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
    };
    
    /// Check that a matrix is square.
    template <>
    struct Check<10>
    {
        /// Perform the actual check.
        template <class MatrixType>
        static void SquareMatrix(const MatrixType& matrix);
    };

    /// Check that a matrix has a specific size.
    template <>
    struct Check<11>
    {
        /// Perform the actual check.
        template <class MatrixType>
        static void SpecificMatrixSize(
            const MatrixType& matrix,
            int expected_rows,
            int expected_cols
        );
    };
    
    /// Check two dimensions to ensure they form a valid product.
    /**
     * The product of two objects is valid if at least one of them is a scalar,
     * i.e., has dimension 1.
     */
    template <>
    struct Check<12>
    {
        /// Perform the actual check.
        OPENSOLID_PYTHON_MODULE_EXPORT static void ValidProductDimensions(
            int first_dimensions,
            int second_dimensions
        );
    };
    
    /// Check that two matrices can be multiplied together.
    template <>
    struct Check<13>
    {
        /// Perform the actual check.
        template <class FirstMatrixType, class SecondMatrixType>
        static void ValidMatrixProduct(
            const FirstMatrixType& first_matrix,
            const SecondMatrixType& second_matrix
        );
    };
    
    /// Check that a matrix component index is in range.
    template <>
    struct Check<14>
    {
        /// Perform the actual check.
        OPENSOLID_PYTHON_MODULE_EXPORT static void ComponentIndexInRange(
            int component_index,
            int size
        );
    };
    
    /// Check that a matrix component block is in range.
    template <>
    struct Check<15>
    {
        /// Perform the actual check.
        OPENSOLID_PYTHON_MODULE_EXPORT static void ComponentBlockInRange(
            int block_start,
            int block_size,
            int size
        );
    };
    
    /// Check that no step size is given when indexing into a matrix.
    template <>
    struct Check<16>
    {
        /// Perform the actual check.
        OPENSOLID_PYTHON_MODULE_EXPORT static void NoMatrixIndexStep(
            const boost::python::slice& indices
        );
    };
    
    /// Check that a function is actually a constant value.
    template <>
    struct Check<17>
    {
        /// Perform the actual check.
        OPENSOLID_PYTHON_MODULE_EXPORT static void ConstantFunction(const Function& function);
    };
    
    /// Check that a function is a scalar function (produces scalar values).
    template <>
    struct Check<18>
    {
        /// Perform the actual check.
        OPENSOLID_PYTHON_MODULE_EXPORT void ScalarFunction(const Function& function);
    };
    
    /// Check that an index is a valid parameter index for a function.
    template <>
    struct Check<19>
    {
        /// Perform the actual check.
        OPENSOLID_PYTHON_MODULE_EXPORT static void ParameterIndexInRange(
            int index,
            const Function& function
        );
    };
    
    /// Check that two functions have 'consistent' numbers of parameters.
    /**
     * In order for two functions to be combined (added together, multiplied,
     * etc.), they must have consistent numbers of parameters - either both
     * functions must have the same number of parameters, or one of them must
     * be constant (have zero parameters).
     */
    template <>
    struct Check<20>
    {
        OPENSOLID_PYTHON_MODULE_EXPORT static void ConsistentFunctionParameters(
            const Function& first_function,
            const Function& second_function
        );
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    namespace
    {
        template <class Type>
        std::string typeName() {return typeid(Type).name();}

        template <>
        inline std::string typeName<boost::python::object>() {return "object";}

        template <>
        inline std::string typeName<boost::python::list>() {return "list";}

        template <>
        inline std::string typeName<boost::python::tuple>() {return "tuple";}

        template <>
        inline std::string typeName<boost::python::str>() {return "str";}

        template <>
        inline std::string typeName<boost::python::dict>() {return "dict";}
        
        template <>
        inline std::string typeName<bool>() {return "bool";}
        
        template <>
        inline std::string typeName<int>() {return "int";}
        
        template <>
        inline std::string typeName<double>() {return "double";}
        
        template <>
        inline std::string typeName<std::string>() {return "std::string";}
        
        template <>
        inline std::string typeName<Interval>() {return "Interval";}
        
        template <>
        inline std::string typeName<Vector2d>() {return "Vector2d";}
        
        template <>
        inline std::string typeName<Vector3d>() {return "Vector3d";}
        
        template <>
        inline std::string typeName<VectorXd>() {return "VectorXd";}
        
        template <>
        inline std::string typeName<RowVector2d>() {return "RowVector2d";}
        
        template <>
        inline std::string typeName<RowVector3d>() {return "RowVector3d";}
        
        template <>
        inline std::string typeName<RowVectorXd>() {return "RowVectorXd";}
        
        template <>
        inline std::string typeName<Vector2I>() {return "Vector2I";}
        
        template <>
        inline std::string typeName<Vector3I>() {return "Vector3I";}
        
        template <>
        inline std::string typeName<VectorXI>() {return "VectorXI";}
        
        template <>
        inline std::string typeName<RowVector2I>() {return "RowVector2I";}
        
        template <>
        inline std::string typeName<RowVector3I>() {return "RowVector3I";}
        
        template <>
        inline std::string typeName<RowVectorXI>() {return "RowVectorXI";}
        
        template <>
        inline std::string typeName<Matrix2d>() {return "Matrix2d";}
        
        template <>
        inline std::string typeName<Matrix3d>() {return "Matrix3d";}
        
        template <>
        inline std::string typeName<MatrixXd>() {return "MatrixXd";}
        
        template <>
        inline std::string typeName<Matrix2I>() {return "Matrix2I";}
        
        template <>
        inline std::string typeName<Matrix3I>() {return "Matrix3I";}
        
        template <>
        inline std::string typeName<MatrixXI>() {return "MatrixXI";}

        template <>
        inline std::string typeName<DatumXd>() {return "DatumXd";}
        
        template <>
        inline std::string typeName<Function>() {return "Function";}
        
        template <>
        inline std::string typeName<Domain>() {return "Domain";}
        
        template <>
        inline std::string typeName<Geometry>() {return "Geometry";}

        template <>
        inline std::string typeName<SimplexXd>() {return "SimplexXd";}
    }
    
    template <class ExpectedType>
    void Check<1>::CompatibleType(const boost::python::object& python_object) {
        boost::python::extract<ExpectedType> extracted(python_object);
        if (!extracted.check()) {
            Error error((Check()));
            error.set("expected_type", typeName<ExpectedType>());
            error.set("type", python_object.ptr()->ob_type->tp_name);
            throw error;
        }
    }
    
    template <class MatrixType>
    void Check<5>::ScalarValue(const MatrixType& matrix) {
        if (matrix.rows() != 1 || matrix.cols() != 1) {
            Error error((Check()));
            error.set("rows", matrix.rows());
            error.set("cols", matrix.cols());
            throw error;
        }
    }
    
    template <class MatrixType>
    void Check<6>::VectorValue(const MatrixType& matrix) {
        if (matrix.cols() != 1) {
            Error error((Check()));
            error.set("cols", matrix.cols());
            throw error;
        }
    }
    
    template <class MatrixType>
    void Check<7>::RowVectorValue(const MatrixType& matrix) {
        if (matrix.rows() != 1) {
            Error error((Check()));
            error.set("rows", matrix.rows());
            throw error;
        }
    }
    
    template <class MatrixType>
    void Check<8>::VectorOrRowVectorValue(const MatrixType& matrix) {
        if (matrix.rows() != 1 && matrix.cols() != 1) {
            Error error((Check()));
            error.set("rows", matrix.rows());
            error.set("cols", matrix.cols());
            throw error;
        }
    }
    
    template <class FirstMatrixType, class SecondMatrixType>
    void Check<9>::SameSizeMatrices(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix
    ) {
        if (
            first_matrix.rows() != second_matrix.rows() ||
            first_matrix.cols() != second_matrix.cols()
        ) {
            Error error((Check()));
            error.set("first_rows", first_matrix.rows());
            error.set("first_cols", first_matrix.cols());
            error.set("second_rows", second_matrix.rows());
            error.set("second_cols", second_matrix.cols());
            throw error;
        }
    }
    
    template <class MatrixType>
    void Check<10>::SquareMatrix(const MatrixType& matrix) {
        if (matrix.rows() != matrix.cols()) {
            Error error((Check()));
            error.set("rows", matrix.rows());
            error.set("cols", matrix.cols());
            throw error;
        }
    }
    
    template <class MatrixType>
    void Check<11>::SpecificMatrixSize(
        const MatrixType& matrix,
        int expected_rows,
        int expected_cols
    ) {
        if (matrix.rows() != expected_rows || matrix.cols() != expected_cols) {
            Error error((Check()));
            error.set("rows", matrix.rows());
            error.set("cols", matrix.cols());
            error.set("expected_rows", expected_rows);
            error.set("expected_cols", expected_cols);
            throw error;
        }
    }
}

#endif
