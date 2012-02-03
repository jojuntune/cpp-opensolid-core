/*****************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                     *
 *   ian.e.mackenzie@gmail.com                                               *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <sstream>

#include <boost/python/converter/pytype_function.hpp>

#include <OpenSolid/Datum/Axis.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
{
    object reference(PyObject* pointer) {
        return pointer ? object(handle<>(borrowed(pointer))) : object();
    }
    
    object reference(PyTypeObject* pointer) {return reference((PyObject*) pointer);}

    object __init__() {
        static object result = raw_function(
            [] (const tuple& arguments, const dict& keyword_arguments) -> object {
                object self = arguments[0];
                object native_error = arguments[1];
                self.attr("args") = make_tuple(native_error);
                return object();
            },
            2
        );
        return result;
    }

    object __str__() {
        static object result = raw_function(
            [] (const tuple& arguments, const dict&) -> object {
                object self = arguments[0];
                return str(self.attr("args")[0]);
            },
            1
        );
        return result;
    }

    object __repr__(str class_name) {
         return raw_function(
            [class_name] (const tuple&, const dict&) -> object {
                return class_name + str("()");
            },
            1
        );
    }

    object accessor(object native_accessor) {
        object result = raw_function(
            [native_accessor] (const tuple& arguments, const dict&) -> object {
                object self = arguments[0];
                return native_accessor(object(self.attr("args")[0]));
            },
            1
        );
        result.attr("__doc__") = native_accessor.attr("__doc__");
        return result;
    }

    object pythonErrorClass(object native_error_class, str class_name) {
        dict class_dict;
        class_dict["__module__"] = scope();
        class_dict["__doc__"] = native_error_class.attr("__doc__");
        class_dict["__init__"] = __init__();
        class_dict["__str__"] = __str__();
        class_dict["__repr__"] = __repr__(class_name);
        dict native_error_class_dict(native_error_class.attr("__dict__"));
        list names = native_error_class_dict.keys();
        for (int i = 0; i < len(names); ++i) {
            str name(names[i]);
            if (!name.startswith("__")) {
                class_dict[name] = accessor(native_error_class.attr(name));
            }
        }
        return reference(&PyType_Type)(
            class_name,
            make_tuple(reference(PyExc_Exception)),
            class_dict
        );
    }

    template <class ErrorType>
    void registerException(class_<ErrorType>& native_error_class) {
        str class_name(native_error_class.attr("__name__").slice(1, _));
        object python_error_class = pythonErrorClass(native_error_class, class_name);
        scope().attr(class_name) = python_error_class;
        PyObject* class_pointer = python_error_class.ptr();
        auto translator = [class_pointer, python_error_class] (const ErrorType& error) {
            object error_object = python_error_class(error);
            PyErr_SetObject(class_pointer, error_object.ptr());
        };
        register_exception_translator<ErrorType>(translator);
    }

    void bindError() {
        // Axis construction errors
        registerException(
            class_<Axis2dConstructionError>("_Axis2dConstructionError", no_init)
                .def("__str__", &Axis2dConstructionError::what)
                .def("origin", &Axis2dConstructionError::origin)
                .def("direction", &Axis2dConstructionError::direction)
        );
        registerException(
            class_<Axis2dCopyConstructionError>("_Axis2dCopyConstructionError", no_init)
                .def("__str__", &Axis2dCopyConstructionError::what)
                .def("argument", &Axis2dCopyConstructionError::argument)
        );
        registerException(
            class_<Axis3dConstructionError>("_Axis3dConstructionError", no_init)
                .def("__str__", &Axis3dConstructionError::what)
                .def("origin", &Axis3dConstructionError::origin)
                .def("direction", &Axis3dConstructionError::direction)
        );
        registerException(
            class_<Axis3dCopyConstructionError>("_Axis3dCopyConstructionError", no_init)
                .def("__str__", &Axis3dCopyConstructionError::what)
                .def("argument", &Axis3dCopyConstructionError::argument)
        );

        // VectorComponentError
        registerException(
            class_<VectorComponentError<MatrixXd>>("_VectorComponentError_MatrixXd", no_init)
                .def("__str__", &VectorComponentError<MatrixXd>::what)
                .def("matrix", &VectorComponentError<MatrixXd>::matrix)
                .def("index", &VectorComponentError<MatrixXd>::index)
        );
        registerException(
            class_<VectorComponentError<MatrixXI>>("_VectorComponentError_MatrixXI", no_init)
                .def("__str__", &VectorComponentError<MatrixXI>::what)
                .def("matrix", &VectorComponentError<MatrixXI>::matrix)
                .def("index", &VectorComponentError<MatrixXI>::index)
        );

        // VectorIndexError
        registerException(
            class_<VectorIndexError<MatrixXd>>("_VectorIndexError_MatrixXd", no_init)
                .def("__str__", &VectorIndexError<MatrixXd>::what)
                .def("matrix", &VectorIndexError<MatrixXd>::matrix)
                .def("index", &VectorIndexError<MatrixXd>::index)
        );
        registerException(
            class_<VectorIndexError<MatrixXI>>("_VectorIndexError_MatrixXI", no_init)
                .def("__str__", &VectorIndexError<MatrixXI>::what)
                .def("matrix", &VectorIndexError<MatrixXI>::matrix)
                .def("index", &VectorIndexError<MatrixXI>::index)
        );

        // MatrixIndexError
        registerException(
            class_<MatrixIndexError<MatrixXd>>("_MatrixIndexError_MatrixXd", no_init)
                .def("__str__", &MatrixIndexError<MatrixXd>::what)
                .def("matrix", &MatrixIndexError<MatrixXd>::matrix)
                .def("rowIndex", &MatrixIndexError<MatrixXd>::rowIndex)
                .def("colIndex", &MatrixIndexError<MatrixXd>::colIndex)
        );
        registerException(
            class_<MatrixIndexError<MatrixXI>>("_MatrixIndexError_MatrixXI", no_init)
                .def("__str__", &MatrixIndexError<MatrixXI>::what)
                .def("matrix", &MatrixIndexError<MatrixXI>::matrix)
                .def("rowIndex", &MatrixIndexError<MatrixXI>::rowIndex)
                .def("colIndex", &MatrixIndexError<MatrixXI>::colIndex)
        );

        // VectorAssignmentError
        registerException(
            class_<VectorAssignmentError<MatrixXd>>("_VectorAssignmentError_MatrixXd", no_init)
                .def("__str__", &VectorAssignmentError<MatrixXd>::what)
                .def("firstMatrix", &VectorAssignmentError<MatrixXd>::firstMatrix)
                .def("index", &VectorAssignmentError<MatrixXd>::index)
                .def("secondMatrix", &VectorAssignmentError<MatrixXd>::secondMatrix)
        );
        registerException(
            class_<VectorAssignmentError<MatrixXI>>("_VectorAssignmentError_MatrixXI", no_init)
                .def("__str__", &VectorAssignmentError<MatrixXI>::what)
                .def("firstMatrix", &VectorAssignmentError<MatrixXI>::firstMatrix)
                .def("index", &VectorAssignmentError<MatrixXI>::index)
                .def("secondMatrix", &VectorAssignmentError<MatrixXI>::secondMatrix)
        );

        // MatrixAssignmentError
        registerException(
            class_<MatrixAssignmentError<MatrixXd>>("_MatrixAssignmentError_MatrixXd", no_init)
                .def("__str__", &MatrixAssignmentError<MatrixXd>::what)
                .def("firstMatrix", &MatrixAssignmentError<MatrixXd>::firstMatrix)
                .def("rowIndex", &MatrixAssignmentError<MatrixXd>::rowIndex)
                .def("colIndex", &MatrixAssignmentError<MatrixXd>::colIndex)
                .def("secondMatrix", &MatrixAssignmentError<MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixAssignmentError<MatrixXI>>("_MatrixAssignmentError_MatrixXI", no_init)
                .def("__str__", &MatrixAssignmentError<MatrixXI>::what)
                .def("firstMatrix", &MatrixAssignmentError<MatrixXI>::firstMatrix)
                .def("rowIndex", &MatrixAssignmentError<MatrixXI>::rowIndex)
                .def("colIndex", &MatrixAssignmentError<MatrixXI>::colIndex)
                .def("secondMatrix", &MatrixAssignmentError<MatrixXI>::secondMatrix)
        );

        // VectorSquaredNormError
        registerException(
            class_<VectorSquaredNormError<MatrixXd>>("_VectorSquaredNormError_MatrixXd", no_init)
                .def("__str__", &VectorSquaredNormError<MatrixXd>::what)
                .def("matrix", &VectorSquaredNormError<MatrixXd>::matrix)
        );
        registerException(
            class_<VectorSquaredNormError<MatrixXI>>("_VectorSquaredNormError_MatrixXI", no_init)
                .def("__str__", &VectorSquaredNormError<MatrixXI>::what)
                .def("matrix", &VectorSquaredNormError<MatrixXI>::matrix)
        );

        // VectorNormError
        registerException(
            class_<VectorNormError<MatrixXd>>("_VectorNormError_MatrixXd", no_init)
                .def("__str__", &VectorNormError<MatrixXd>::what)
                .def("matrix", &VectorNormError<MatrixXd>::matrix)
        );
        registerException(
            class_<VectorNormError<MatrixXI>>("_VectorNormError_MatrixXI", no_init)
                .def("__str__", &VectorNormError<MatrixXI>::what)
                .def("matrix", &VectorNormError<MatrixXI>::matrix)
        );

        // VectorNormalizedError
        registerException(
            class_<VectorNormalizedError<MatrixXd>>("_VectorNormalizedError_MatrixXd", no_init)
                .def("__str__", &VectorNormalizedError<MatrixXd>::what)
                .def("matrix", &VectorNormalizedError<MatrixXd>::matrix)
        );
        registerException(
            class_<VectorNormalizedError<MatrixXI>>("_VectorNormalizedError_MatrixXI", no_init)
                .def("__str__", &VectorNormalizedError<MatrixXI>::what)
                .def("matrix", &VectorNormalizedError<MatrixXI>::matrix)
        );

        // MatrixDeterminantError
        registerException(
            class_<MatrixDeterminantError<MatrixXd>>("_MatrixDeterminantError_MatrixXd", no_init)
                .def("__str__", &MatrixDeterminantError<MatrixXd>::what)
                .def("matrix", &MatrixDeterminantError<MatrixXd>::matrix)
        );
        registerException(
            class_<MatrixDeterminantError<MatrixXI>>("_MatrixDeterminantError_MatrixXI", no_init)
                .def("__str__", &MatrixDeterminantError<MatrixXI>::what)
                .def("matrix", &MatrixDeterminantError<MatrixXI>::matrix)
        );

        // MatrixInverseError
        registerException(
            class_<MatrixInverseError>("_MatrixInverseError", no_init)
                .def("__str__", &MatrixInverseError::what)
                .def("matrix", &MatrixInverseError::matrix)
        );

        // MatrixReplicateError
        registerException(
            class_<MatrixReplicateError<MatrixXd>>("_MatrixReplicateError_MatrixXd", no_init)
                .def("__str__", &MatrixReplicateError<MatrixXd>::what)
                .def("matrix", &MatrixReplicateError<MatrixXd>::matrix)
                .def("rowFactor", &MatrixReplicateError<MatrixXd>::rowFactor)
                .def("colFactor", &MatrixReplicateError<MatrixXd>::colFactor)
        );
        registerException(
            class_<MatrixReplicateError<MatrixXI>>("_MatrixReplicateError_MatrixXI", no_init)
                .def("__str__", &MatrixReplicateError<MatrixXI>::what)
                .def("matrix", &MatrixReplicateError<MatrixXI>::matrix)
                .def("rowFactor", &MatrixReplicateError<MatrixXI>::rowFactor)
                .def("colFactor", &MatrixReplicateError<MatrixXI>::colFactor)
        );

        // MatrixDotProductError
        registerException(
            class_<MatrixDotProductError<MatrixXd, MatrixXd>>("_MatrixDotProductError_MatrixXd_MatrixXd", no_init)
                .def("__str__", &MatrixDotProductError<MatrixXd, MatrixXd>::what)
                .def("firstMatrix", &MatrixDotProductError<MatrixXd, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixDotProductError<MatrixXd, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixDotProductError<MatrixXd, MatrixXI>>("_MatrixDotProductError_MatrixXd_MatrixXI", no_init)
                .def("__str__", &MatrixDotProductError<MatrixXd, MatrixXI>::what)
                .def("firstMatrix", &MatrixDotProductError<MatrixXd, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixDotProductError<MatrixXd, MatrixXI>::secondMatrix)
        );
        registerException(
            class_<MatrixDotProductError<MatrixXI, MatrixXd>>("_MatrixDotProductError_MatrixXI_MatrixXd", no_init)
                .def("__str__", &MatrixDotProductError<MatrixXI, MatrixXd>::what)
                .def("firstMatrix", &MatrixDotProductError<MatrixXI, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixDotProductError<MatrixXI, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixDotProductError<MatrixXI, MatrixXI>>("_MatrixDotProductError_MatrixXI_MatrixXI", no_init)
                .def("__str__", &MatrixDotProductError<MatrixXI, MatrixXI>::what)
                .def("firstMatrix", &MatrixDotProductError<MatrixXI, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixDotProductError<MatrixXI, MatrixXI>::secondMatrix)
        );

        // MatrixCrossProductError
        registerException(
            class_<MatrixCrossProductError<MatrixXd, MatrixXd>>("_MatrixCrossProductError_MatrixXd_MatrixXd", no_init)
                .def("__str__", &MatrixCrossProductError<MatrixXd, MatrixXd>::what)
                .def("firstMatrix", &MatrixCrossProductError<MatrixXd, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixCrossProductError<MatrixXd, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixCrossProductError<MatrixXd, MatrixXI>>("_MatrixCrossProductError_MatrixXd_MatrixXI", no_init)
                .def("__str__", &MatrixCrossProductError<MatrixXd, MatrixXI>::what)
                .def("firstMatrix", &MatrixCrossProductError<MatrixXd, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixCrossProductError<MatrixXd, MatrixXI>::secondMatrix)
        );
        registerException(
            class_<MatrixCrossProductError<MatrixXI, MatrixXd>>("_MatrixCrossProductError_MatrixXI_MatrixXd", no_init)
                .def("__str__", &MatrixCrossProductError<MatrixXI, MatrixXd>::what)
                .def("firstMatrix", &MatrixCrossProductError<MatrixXI, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixCrossProductError<MatrixXI, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixCrossProductError<MatrixXI, MatrixXI>>("_MatrixCrossProductError_MatrixXI_MatrixXI", no_init)
                .def("__str__", &MatrixCrossProductError<MatrixXI, MatrixXI>::what)
                .def("firstMatrix", &MatrixCrossProductError<MatrixXI, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixCrossProductError<MatrixXI, MatrixXI>::secondMatrix)
        );

        // MatrixOverlapsError
        registerException(
            class_<MatrixOverlapsError>("_MatrixOverlapsError", no_init)
                .def("__str__", &MatrixOverlapsError::what)
                .def("firstMatrix", &MatrixOverlapsError::firstMatrix)
                .def("secondMatrix", &MatrixOverlapsError::secondMatrix)
        );

        // MatrixContainsError
        registerException(
            class_<MatrixContainsError<MatrixXd>>("_MatrixContainsError_MatrixXd", no_init)
                .def("__str__", &MatrixContainsError<MatrixXd>::what)
                .def("firstMatrix", &MatrixContainsError<MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixContainsError<MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixContainsError<MatrixXI>>("_MatrixContainsError_MatrixXI", no_init)
                .def("__str__", &MatrixContainsError<MatrixXI>::what)
                .def("firstMatrix", &MatrixContainsError<MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixContainsError<MatrixXI>::secondMatrix)
        );

        // MatrixHullError
        registerException(
            class_<MatrixHullError<MatrixXd, MatrixXd>>("_MatrixHullError_MatrixXd_MatrixXd", no_init)
                .def("__str__", &MatrixHullError<MatrixXd, MatrixXd>::what)
                .def("firstMatrix", &MatrixHullError<MatrixXd, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixHullError<MatrixXd, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixHullError<MatrixXd, MatrixXI>>("_MatrixHullError_MatrixXd_MatrixXI", no_init)
                .def("__str__", &MatrixHullError<MatrixXd, MatrixXI>::what)
                .def("firstMatrix", &MatrixHullError<MatrixXd, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixHullError<MatrixXd, MatrixXI>::secondMatrix)
        );
        registerException(
            class_<MatrixHullError<MatrixXI, MatrixXd>>("_MatrixHullError_MatrixXI_MatrixXd", no_init)
                .def("__str__", &MatrixHullError<MatrixXI, MatrixXd>::what)
                .def("firstMatrix", &MatrixHullError<MatrixXI, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixHullError<MatrixXI, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixHullError<MatrixXI, MatrixXI>>("_MatrixHullError_MatrixXI_MatrixXI", no_init)
                .def("__str__", &MatrixHullError<MatrixXI, MatrixXI>::what)
                .def("firstMatrix", &MatrixHullError<MatrixXI, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixHullError<MatrixXI, MatrixXI>::secondMatrix)
        );

        // MatrixIntersectionError
        registerException(
            class_<MatrixIntersectionError>("_MatrixIntersectionError", no_init)
                .def("__str__", &MatrixIntersectionError::what)
                .def("firstMatrix", &MatrixIntersectionError::firstMatrix)
                .def("secondMatrix", &MatrixIntersectionError::secondMatrix)
        );

        // ConstantMatrixConstructionError
        registerException(
            class_<ConstantMatrixConstructionError<MatrixXd>>("_ConstantMatrixConstructionError_MatrixXd", no_init)
                .def("__str__", &ConstantMatrixConstructionError<MatrixXd>::what)
                .def("rows", &ConstantMatrixConstructionError<MatrixXd>::rows)
                .def("cols", &ConstantMatrixConstructionError<MatrixXd>::cols)
                .def("value", &ConstantMatrixConstructionError<MatrixXd>::value)
        );
        registerException(
            class_<ConstantMatrixConstructionError<MatrixXI>>("_ConstantMatrixConstructionError_MatrixXI", no_init)
                .def("__str__", &ConstantMatrixConstructionError<MatrixXI>::what)
                .def("rows", &ConstantMatrixConstructionError<MatrixXI>::rows)
                .def("cols", &ConstantMatrixConstructionError<MatrixXI>::cols)
                .def("value", &ConstantMatrixConstructionError<MatrixXI>::value)
        );

        // ZeroMatrixConstructionError
        registerException(
            class_<ZeroMatrixConstructionError<MatrixXd>>("_ZeroMatrixConstructionError_MatrixXd", no_init)
                .def("__str__", &ZeroMatrixConstructionError<MatrixXd>::what)
                .def("rows", &ZeroMatrixConstructionError<MatrixXd>::rows)
                .def("cols", &ZeroMatrixConstructionError<MatrixXd>::cols)
        );
        registerException(
            class_<ZeroMatrixConstructionError<MatrixXI>>("_ZeroMatrixConstructionError_MatrixXI", no_init)
                .def("__str__", &ZeroMatrixConstructionError<MatrixXI>::what)
                .def("rows", &ZeroMatrixConstructionError<MatrixXI>::rows)
                .def("cols", &ZeroMatrixConstructionError<MatrixXI>::cols)
        );

        // OnesMatrixConstructionError
        registerException(
            class_<OnesMatrixConstructionError<MatrixXd>>("_OnesMatrixConstructionError_MatrixXd", no_init)
                .def("__str__", &OnesMatrixConstructionError<MatrixXd>::what)
                .def("rows", &OnesMatrixConstructionError<MatrixXd>::rows)
                .def("cols", &OnesMatrixConstructionError<MatrixXd>::cols)
        );
        registerException(
            class_<OnesMatrixConstructionError<MatrixXI>>("_OnesMatrixConstructionError_MatrixXI", no_init)
                .def("__str__", &OnesMatrixConstructionError<MatrixXI>::what)
                .def("rows", &OnesMatrixConstructionError<MatrixXI>::rows)
                .def("cols", &OnesMatrixConstructionError<MatrixXI>::cols)
        );

        // RandomMatrixConstructionError
        registerException(
            class_<RandomMatrixConstructionError<MatrixXd>>("_RandomMatrixConstructionError_MatrixXd", no_init)
                .def("__str__", &RandomMatrixConstructionError<MatrixXd>::what)
                .def("rows", &RandomMatrixConstructionError<MatrixXd>::rows)
                .def("cols", &RandomMatrixConstructionError<MatrixXd>::cols)
        );
        registerException(
            class_<RandomMatrixConstructionError<MatrixXI>>("_RandomMatrixConstructionError_MatrixXI", no_init)
                .def("__str__", &RandomMatrixConstructionError<MatrixXI>::what)
                .def("rows", &RandomMatrixConstructionError<MatrixXI>::rows)
                .def("cols", &RandomMatrixConstructionError<MatrixXI>::cols)
        );

        // IdentityMatrixConstructionError
        registerException(
            class_<IdentityMatrixConstructionError<MatrixXd>>("_IdentityMatrixConstructionError_MatrixXd", no_init)
                .def("__str__", &IdentityMatrixConstructionError<MatrixXd>::what)
                .def("rows", &IdentityMatrixConstructionError<MatrixXd>::rows)
                .def("cols", &IdentityMatrixConstructionError<MatrixXd>::cols)
        );
        registerException(
            class_<IdentityMatrixConstructionError<MatrixXI>>("_IdentityMatrixConstructionError_MatrixXI", no_init)
                .def("__str__", &IdentityMatrixConstructionError<MatrixXI>::what)
                .def("rows", &IdentityMatrixConstructionError<MatrixXI>::rows)
                .def("cols", &IdentityMatrixConstructionError<MatrixXI>::cols)
        );

        // MatrixSumError
        registerException(
            class_<MatrixSumError<MatrixXd, MatrixXd>>("_MatrixSumError_MatrixXd_MatrixXd", no_init)
                .def("__str__", &MatrixSumError<MatrixXd, MatrixXd>::what)
                .def("firstMatrix", &MatrixSumError<MatrixXd, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixSumError<MatrixXd, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixSumError<MatrixXd, MatrixXI>>("_MatrixSumError_MatrixXd_MatrixXI", no_init)
                .def("__str__", &MatrixSumError<MatrixXd, MatrixXI>::what)
                .def("firstMatrix", &MatrixSumError<MatrixXd, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixSumError<MatrixXd, MatrixXI>::secondMatrix)
        );
        registerException(
            class_<MatrixSumError<MatrixXI, MatrixXd>>("_MatrixSumError_MatrixXI_MatrixXd", no_init)
                .def("__str__", &MatrixSumError<MatrixXI, MatrixXd>::what)
                .def("firstMatrix", &MatrixSumError<MatrixXI, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixSumError<MatrixXI, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixSumError<MatrixXI, MatrixXI>>("_MatrixSumError_MatrixXI_MatrixXI", no_init)
                .def("__str__", &MatrixSumError<MatrixXI, MatrixXI>::what)
                .def("firstMatrix", &MatrixSumError<MatrixXI, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixSumError<MatrixXI, MatrixXI>::secondMatrix)
        );

        // MatrixDifferenceError
        registerException(
            class_<MatrixDifferenceError<MatrixXd, MatrixXd>>("_MatrixDifferenceError_MatrixXd_MatrixXd", no_init)
                .def("__str__", &MatrixDifferenceError<MatrixXd, MatrixXd>::what)
                .def("firstMatrix", &MatrixDifferenceError<MatrixXd, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixDifferenceError<MatrixXd, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixDifferenceError<MatrixXd, MatrixXI>>("_MatrixDifferenceError_MatrixXd_MatrixXI", no_init)
                .def("__str__", &MatrixDifferenceError<MatrixXd, MatrixXI>::what)
                .def("firstMatrix", &MatrixDifferenceError<MatrixXd, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixDifferenceError<MatrixXd, MatrixXI>::secondMatrix)
        );
        registerException(
            class_<MatrixDifferenceError<MatrixXI, MatrixXd>>("_MatrixDifferenceError_MatrixXI_MatrixXd", no_init)
                .def("__str__", &MatrixDifferenceError<MatrixXI, MatrixXd>::what)
                .def("firstMatrix", &MatrixDifferenceError<MatrixXI, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixDifferenceError<MatrixXI, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixDifferenceError<MatrixXI, MatrixXI>>("_MatrixDifferenceError_MatrixXI_MatrixXI", no_init)
                .def("__str__", &MatrixDifferenceError<MatrixXI, MatrixXI>::what)
                .def("firstMatrix", &MatrixDifferenceError<MatrixXI, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixDifferenceError<MatrixXI, MatrixXI>::secondMatrix)
        );

        // MatrixQuotientError
        registerException(
            class_<MatrixQuotientError<MatrixXd, double>>("_MatrixQuotientError_MatrixXd_double", no_init)
                .def("__str__", &MatrixQuotientError<MatrixXd, double>::what)
                .def("matrix", &MatrixQuotientError<MatrixXd, double>::matrix)
                .def("divisor", &MatrixQuotientError<MatrixXd, double>::divisor)
        );
        registerException(
            class_<MatrixQuotientError<MatrixXd, Interval>>("_MatrixQuotientError_MatrixXd_Interval", no_init)
                .def("__str__", &MatrixQuotientError<MatrixXd, Interval>::what)
                .def("matrix", &MatrixQuotientError<MatrixXd, Interval>::matrix)
                .def("divisor", &MatrixQuotientError<MatrixXd, Interval>::divisor)
        );
        registerException(
            class_<MatrixQuotientError<MatrixXI, double>>("_MatrixQuotientError_MatrixXI_double", no_init)
                .def("__str__", &MatrixQuotientError<MatrixXI, double>::what)
                .def("matrix", &MatrixQuotientError<MatrixXI, double>::matrix)
                .def("divisor", &MatrixQuotientError<MatrixXI, double>::divisor)
        );
        registerException(
            class_<MatrixQuotientError<MatrixXI, Interval>>("_MatrixQuotientError_MatrixXI_Interval", no_init)
                .def("__str__", &MatrixQuotientError<MatrixXI, Interval>::what)
                .def("matrix", &MatrixQuotientError<MatrixXI, Interval>::matrix)
                .def("divisor", &MatrixQuotientError<MatrixXI, Interval>::divisor)
        );

        // MatrixProductError
        registerException(
            class_<MatrixProductError<MatrixXd, MatrixXd>>("_MatrixProductError_MatrixXd_MatrixXd", no_init)
                .def("__str__", &MatrixProductError<MatrixXd, MatrixXd>::what)
                .def("firstMatrix", &MatrixProductError<MatrixXd, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixProductError<MatrixXd, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixProductError<MatrixXd, MatrixXI>>("_MatrixProductError_MatrixXd_MatrixXI", no_init)
                .def("__str__", &MatrixProductError<MatrixXd, MatrixXI>::what)
                .def("firstMatrix", &MatrixProductError<MatrixXd, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixProductError<MatrixXd, MatrixXI>::secondMatrix)
        );
        registerException(
            class_<MatrixProductError<MatrixXI, MatrixXd>>("_MatrixProductError_MatrixXI_MatrixXd", no_init)
                .def("__str__", &MatrixProductError<MatrixXI, MatrixXd>::what)
                .def("firstMatrix", &MatrixProductError<MatrixXI, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixProductError<MatrixXI, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixProductError<MatrixXI, MatrixXI>>("_MatrixProductError_MatrixXI_MatrixXI", no_init)
                .def("__str__", &MatrixProductError<MatrixXI, MatrixXI>::what)
                .def("firstMatrix", &MatrixProductError<MatrixXI, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixProductError<MatrixXI, MatrixXI>::secondMatrix)
        );

        // MatrixEqualityError
        registerException(
            class_<MatrixEqualityError<MatrixXd, MatrixXd>>("_MatrixEqualityError_MatrixXd_MatrixXd", no_init)
                .def("__str__", &MatrixEqualityError<MatrixXd, MatrixXd>::what)
                .def("firstMatrix", &MatrixEqualityError<MatrixXd, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixEqualityError<MatrixXd, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixEqualityError<MatrixXd, MatrixXI>>("_MatrixEqualityError_MatrixXd_MatrixXI", no_init)
                .def("__str__", &MatrixEqualityError<MatrixXd, MatrixXI>::what)
                .def("firstMatrix", &MatrixEqualityError<MatrixXd, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixEqualityError<MatrixXd, MatrixXI>::secondMatrix)
        );
        registerException(
            class_<MatrixEqualityError<MatrixXI, MatrixXd>>("_MatrixEqualityError_MatrixXI_MatrixXd", no_init)
                .def("__str__", &MatrixEqualityError<MatrixXI, MatrixXd>::what)
                .def("firstMatrix", &MatrixEqualityError<MatrixXI, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixEqualityError<MatrixXI, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixEqualityError<MatrixXI, MatrixXI>>("_MatrixEqualityError_MatrixXI_MatrixXI", no_init)
                .def("__str__", &MatrixEqualityError<MatrixXI, MatrixXI>::what)
                .def("firstMatrix", &MatrixEqualityError<MatrixXI, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixEqualityError<MatrixXI, MatrixXI>::secondMatrix)
        );

        // MatrixInequalityError
        registerException(
            class_<MatrixInequalityError<MatrixXd, MatrixXd>>("_MatrixInequalityError_MatrixXd_MatrixXd", no_init)
                .def("__str__", &MatrixInequalityError<MatrixXd, MatrixXd>::what)
                .def("firstMatrix", &MatrixInequalityError<MatrixXd, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixInequalityError<MatrixXd, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixInequalityError<MatrixXd, MatrixXI>>("_MatrixInequalityError_MatrixXd_MatrixXI", no_init)
                .def("__str__", &MatrixInequalityError<MatrixXd, MatrixXI>::what)
                .def("firstMatrix", &MatrixInequalityError<MatrixXd, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixInequalityError<MatrixXd, MatrixXI>::secondMatrix)
        );
        registerException(
            class_<MatrixInequalityError<MatrixXI, MatrixXd>>("_MatrixInequalityError_MatrixXI_MatrixXd", no_init)
                .def("__str__", &MatrixInequalityError<MatrixXI, MatrixXd>::what)
                .def("firstMatrix", &MatrixInequalityError<MatrixXI, MatrixXd>::firstMatrix)
                .def("secondMatrix", &MatrixInequalityError<MatrixXI, MatrixXd>::secondMatrix)
        );
        registerException(
            class_<MatrixInequalityError<MatrixXI, MatrixXI>>("_MatrixInequalityError_MatrixXI_MatrixXI", no_init)
                .def("__str__", &MatrixInequalityError<MatrixXI, MatrixXI>::what)
                .def("firstMatrix", &MatrixInequalityError<MatrixXI, MatrixXI>::firstMatrix)
                .def("secondMatrix", &MatrixInequalityError<MatrixXI, MatrixXI>::secondMatrix)
        );
    }
}
