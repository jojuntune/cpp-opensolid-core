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

#ifndef OPENSOLID__SCRIPTING__CHECK_HPP
#define OPENSOLID__SCRIPTING__CHECK_HPP

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
    template <class ExpectedType>
    void checkCompatiblePythonType(boost::python::object argument, const std::string& caller);
    
    OPENSOLID_PYTHON_EXPORT void checkNonZeroValue(double value, const std::string& caller);
    
    OPENSOLID_PYTHON_EXPORT void checkSameSize(
        int first_size,
        int second_size,
        const std::string& caller
    );
    
    OPENSOLID_PYTHON_EXPORT void checkSameDimensions(
        int first_dimensions,
        int second_dimensions,
        const std::string& caller
    );
    
    template <class MatrixType>
    void checkScalarValue(const MatrixType& argument, const std::string& caller);
    
    template <class MatrixType>
    void checkVectorValue(const MatrixType& argument, const std::string& caller);
    
    template <class MatrixType>
    void checkRowVectorValue(const MatrixType& matrix, const std::string& caller);
    
    template <class MatrixType>
    void checkVectorOrRowVectorValue(const MatrixType& matrix, const std::string& caller);
    
    template <class FirstMatrixType, class SecondMatrixType>
    void checkSameSizeMatrices(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix,
        const std::string& caller
    );
    
    template <class MatrixType>
    void checkSquareMatrix(const MatrixType& matrix, const std::string& caller);
    
    template <class MatrixType>
    void checkSpecificMatrixSize(
        const MatrixType& matrix,
        int expected_rows,
        int expected_cols,
        const std::string& caller
    );
    
    OPENSOLID_PYTHON_EXPORT void checkValidProductDimensions(
        int first_dimensions,
        int second_dimensions,
        const std::string& caller
    );
    
    template <class FirstMatrixType, class SecondMatrixType>
    void checkValidMatrixProduct(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix,
        const std::string& caller
    );
    
    OPENSOLID_PYTHON_EXPORT void checkComponentIndexInRange(
        int component_index,
        int size,
        const std::string& caller
    );
    
    OPENSOLID_PYTHON_EXPORT void checkComponentBlockInRange(
        int block_start,
        int block_size,
        int size,
        const std::string& caller
    );
    
    OPENSOLID_PYTHON_EXPORT void checkNoMatrixIndexStep(
        boost::python::slice indices,
        const std::string& caller
    );
    
    OPENSOLID_PYTHON_EXPORT void checkConstantFunction(
        const Function& function,
        const std::string& caller
    );
    
    OPENSOLID_PYTHON_EXPORT void checkScalarFunction(
        const Function& function,
        const std::string& caller
    );
    
    OPENSOLID_PYTHON_EXPORT void checkParameterIndexInRange(
        int index,
        const Function& function,
        const std::string& caller
    );
    
    OPENSOLID_PYTHON_EXPORT void checkConsistentFunctionParameters(
        const Function& first_function,
        const Function& second_function,
        const std::string& caller
    );
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
    void checkCompatiblePythonType(boost::python::object argument, const std::string& caller) {
        boost::python::extract<ExpectedType> extracted(argument);
        if (!extracted.check()) {
            Error error("CompatiblePythonType", caller);
            error.set("expected_type", typeName<ExpectedType>());
            error.set("type", argument.ptr()->ob_type->tp_name);
            throw error;
        }
    }
    
    template <class MatrixType>
    void checkScalarValue(const MatrixType& matrix, const std::string& caller) {
        if (matrix.rows() != 1 || matrix.cols() != 1) {
            Error error("ScalarValue", caller);
            error.set("rows", matrix.rows());
            error.set("cols", matrix.cols());
            throw error;
        }
    }
    
    template <class MatrixType>
    void checkVectorValue(const MatrixType& matrix, const std::string& caller) {
        if (matrix.cols() != 1) {
            Error error("VectorValue", caller);
            error.set("cols", matrix.cols());
            throw error;
        }
    }
    
    template <class MatrixType>
    void checkRowVectorValue(const MatrixType& matrix, const std::string& caller) {
        if (matrix.rows() != 1) {
            Error error("RowVectorValue", caller);
            error.set("rows", matrix.rows());
            throw error;
        }
    }
    
    template <class MatrixType>
    void checkVectorOrRowVectorValue(const MatrixType& matrix, const std::string& caller) {
        if (matrix.rows() != 1 && matrix.cols() != 1) {
            Error error("VectorOrRowVectorValue", caller);
            error.set("rows", matrix.rows());
            error.set("cols", matrix.cols());
            throw error;
        }
    }
    
    template <class FirstMatrixType, class SecondMatrixType>
    void checkSameSizeMatrices(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix,
        const std::string& caller
    ) {
        if (
            first_matrix.rows() != second_matrix.rows() ||
            first_matrix.cols() != second_matrix.cols()
        ) {
            Error error("SameSizeMatrices", caller);
            error.set("first_rows", first_matrix.rows());
            error.set("first_cols", first_matrix.cols());
            error.set("second_rows", second_matrix.rows());
            error.set("second_cols", second_matrix.cols());
            throw error;
        }
    }
    
    template <class MatrixType>
    void checkSquareMatrix(const MatrixType& matrix, const std::string& caller) {
        if (matrix.rows() != matrix.cols()) {
            Error error("SquareMatrix", caller);
            error.set("rows", matrix.rows());
            error.set("cols", matrix.cols());
            throw error;
        }
    }
    
    template <class MatrixType>
    void checkSpecificMatrixSize(
        const MatrixType& matrix,
        int expected_rows,
        int expected_cols,
        const std::string& caller
    ) {
        if (matrix.rows() != expected_rows || matrix.cols() != expected_cols) {
            Error error("SpecificMatrixSize", caller);
            error.set("rows", matrix.rows());
            error.set("cols", matrix.cols());
            error.set("expected_rows", expected_rows);
            error.set("expected_cols", expected_cols);
            throw error;
        }
    }
}

#endif
