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

#include <OpenSolid/Core/Datum/Axis.hpp>
#include <OpenSolid/Core/Object/Object.hpp>
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

    object pythonErrorBaseClass() {
        static object result;
        if (result.is_none()) {
            dict class_dict;
            class_dict["__module__"] = scope();
            result = reference(&PyType_Type)(
                "Error",
                make_tuple(reference(PyExc_Exception)),
                class_dict
            );
        }
        return result;
    }

    object pythonErrorClass(object native_error_class, str class_name) {
        dict class_dict;
        class_dict["__module__"] = "opensolid";
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
            make_tuple(pythonErrorBaseClass()),
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
        registerException(
            class_<MatrixXdVectorComponentError>("_MatrixXdVectorComponentError", no_init)
                .def("__str__", &MatrixXdVectorComponentError::what)
                .def("matrix", &MatrixXdVectorComponentError::matrix)
                .def("index", &MatrixXdVectorComponentError::index)
        );
        registerException(
            class_<MatrixXIVectorComponentError>("_MatrixXIVectorComponentError", no_init)
                .def("__str__", &MatrixXIVectorComponentError::what)
                .def("matrix", &MatrixXIVectorComponentError::matrix)
                .def("index", &MatrixXIVectorComponentError::index)
        );
        registerException(
            class_<MatrixXdVectorIndexError>("_MatrixXdVectorIndexError", no_init)
                .def("__str__", &MatrixXdVectorIndexError::what)
                .def("matrix", &MatrixXdVectorIndexError::matrix)
                .def("index", &MatrixXdVectorIndexError::index)
        );
        registerException(
            class_<MatrixXIVectorIndexError>("_MatrixXIVectorIndexError", no_init)
                .def("__str__", &MatrixXIVectorIndexError::what)
                .def("matrix", &MatrixXIVectorIndexError::matrix)
                .def("index", &MatrixXIVectorIndexError::index)
        );
        registerException(
            class_<MatrixXdIndexError>("_MatrixXdIndexError", no_init)
                .def("__str__", &MatrixXdIndexError::what)
                .def("matrix", &MatrixXdIndexError::matrix)
                .def("rowIndex", &MatrixXdIndexError::rowIndex)
                .def("colIndex", &MatrixXdIndexError::colIndex)
        );
        registerException(
            class_<MatrixXIIndexError>("_MatrixXIIndexError", no_init)
                .def("__str__", &MatrixXIIndexError::what)
                .def("matrix", &MatrixXIIndexError::matrix)
                .def("rowIndex", &MatrixXIIndexError::rowIndex)
                .def("colIndex", &MatrixXIIndexError::colIndex)
        );
        registerException(
            class_<MatrixXdVectorAssignmentError>("_MatrixXdVectorAssignmentError", no_init)
                .def("__str__", &MatrixXdVectorAssignmentError::what)
                .def("firstMatrix", &MatrixXdVectorAssignmentError::firstMatrix)
                .def("index", &MatrixXdVectorAssignmentError::index)
                .def("secondMatrix", &MatrixXdVectorAssignmentError::secondMatrix)
        );
        registerException(
            class_<MatrixXIVectorAssignmentError>("_MatrixXIVectorAssignmentError", no_init)
                .def("__str__", &MatrixXIVectorAssignmentError::what)
                .def("firstMatrix", &MatrixXIVectorAssignmentError::firstMatrix)
                .def("index", &MatrixXIVectorAssignmentError::index)
                .def("secondMatrix", &MatrixXIVectorAssignmentError::secondMatrix)
        );
        registerException(
            class_<MatrixXdAssignmentError>("_MatrixXdAssignmentError", no_init)
                .def("__str__", &MatrixXdAssignmentError::what)
                .def("firstMatrix", &MatrixXdAssignmentError::firstMatrix)
                .def("rowIndex", &MatrixXdAssignmentError::rowIndex)
                .def("colIndex", &MatrixXdAssignmentError::colIndex)
                .def("secondMatrix", &MatrixXdAssignmentError::secondMatrix)
        );
        registerException(
            class_<MatrixXIAssignmentError>("_MatrixXIAssignmentError", no_init)
                .def("__str__", &MatrixXIAssignmentError::what)
                .def("firstMatrix", &MatrixXIAssignmentError::firstMatrix)
                .def("rowIndex", &MatrixXIAssignmentError::rowIndex)
                .def("colIndex", &MatrixXIAssignmentError::colIndex)
                .def("secondMatrix", &MatrixXIAssignmentError::secondMatrix)
        );
        registerException(
            class_<MatrixXdSquaredNormError>("_MatrixXdSquaredNormError", no_init)
                .def("__str__", &MatrixXdSquaredNormError::what)
                .def("matrix", &MatrixXdSquaredNormError::matrix)
        );
        registerException(
            class_<MatrixXISquaredNormError>("_MatrixXISquaredNormError", no_init)
                .def("__str__", &MatrixXISquaredNormError::what)
                .def("matrix", &MatrixXISquaredNormError::matrix)
        );
        registerException(
            class_<MatrixXdNormError>("_MatrixXdNormError", no_init)
                .def("__str__", &MatrixXdNormError::what)
                .def("matrix", &MatrixXdNormError::matrix)
        );
        registerException(
            class_<MatrixXINormError>("_MatrixXINormError", no_init)
                .def("__str__", &MatrixXINormError::what)
                .def("matrix", &MatrixXINormError::matrix)
        );
        registerException(
            class_<MatrixXdNormalizedError>("_MatrixXdNormalizedError", no_init)
                .def("__str__", &MatrixXdNormalizedError::what)
                .def("matrix", &MatrixXdNormalizedError::matrix)
        );
        registerException(
            class_<MatrixXINormalizedError>("_MatrixXINormalizedError", no_init)
                .def("__str__", &MatrixXINormalizedError::what)
                .def("matrix", &MatrixXINormalizedError::matrix)
        );
        registerException(
            class_<MatrixXdDeterminantError>("_MatrixXdDeterminantError", no_init)
                .def("__str__", &MatrixXdDeterminantError::what)
                .def("matrix", &MatrixXdDeterminantError::matrix)
        );
        registerException(
            class_<MatrixXIDeterminantError>("_MatrixXIDeterminantError", no_init)
                .def("__str__", &MatrixXIDeterminantError::what)
                .def("matrix", &MatrixXIDeterminantError::matrix)
        );
        registerException(
            class_<MatrixXdInverseError>("_MatrixXdInverseError", no_init)
                .def("__str__", &MatrixXdInverseError::what)
                .def("matrix", &MatrixXdInverseError::matrix)
        );
        registerException(
            class_<MatrixXdReplicateError>("_MatrixXdReplicateError", no_init)
                .def("__str__", &MatrixXdReplicateError::what)
                .def("matrix", &MatrixXdReplicateError::matrix)
                .def("rowFactor", &MatrixXdReplicateError::rowFactor)
                .def("colFactor", &MatrixXdReplicateError::colFactor)
        );
        registerException(
            class_<MatrixXIReplicateError>("_MatrixXIReplicateError", no_init)
                .def("__str__", &MatrixXIReplicateError::what)
                .def("matrix", &MatrixXIReplicateError::matrix)
                .def("rowFactor", &MatrixXIReplicateError::rowFactor)
                .def("colFactor", &MatrixXIReplicateError::colFactor)
        );
        registerException(
            class_<MatrixXdDotProductMatrixXdError>("_MatrixXdDotProductMatrixXdError", no_init)
                .def("__str__", &MatrixXdDotProductMatrixXdError::what)
                .def("firstMatrix", &MatrixXdDotProductMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXdDotProductMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXdDotProductMatrixXIError>("_MatrixXdDotProductMatrixXIError", no_init)
                .def("__str__", &MatrixXdDotProductMatrixXIError::what)
                .def("firstMatrix", &MatrixXdDotProductMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXdDotProductMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXIDotProductMatrixXdError>("_MatrixXIDotProductMatrixXdError", no_init)
                .def("__str__", &MatrixXIDotProductMatrixXdError::what)
                .def("firstMatrix", &MatrixXIDotProductMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXIDotProductMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXIDotProductMatrixXIError>("_MatrixXIDotProductMatrixXIError", no_init)
                .def("__str__", &MatrixXIDotProductMatrixXIError::what)
                .def("firstMatrix", &MatrixXIDotProductMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXIDotProductMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXdCrossProductMatrixXdError>("_MatrixXdCrossProductMatrixXdError", no_init)
                .def("__str__", &MatrixXdCrossProductMatrixXdError::what)
                .def("firstMatrix", &MatrixXdCrossProductMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXdCrossProductMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXdCrossProductMatrixXIError>("_MatrixXdCrossProductMatrixXIError", no_init)
                .def("__str__", &MatrixXdCrossProductMatrixXIError::what)
                .def("firstMatrix", &MatrixXdCrossProductMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXdCrossProductMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXICrossProductMatrixXdError>("_MatrixXICrossProductMatrixXdError", no_init)
                .def("__str__", &MatrixXICrossProductMatrixXdError::what)
                .def("firstMatrix", &MatrixXICrossProductMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXICrossProductMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXICrossProductMatrixXIError>("_MatrixXICrossProductMatrixXIError", no_init)
                .def("__str__", &MatrixXICrossProductMatrixXIError::what)
                .def("firstMatrix", &MatrixXICrossProductMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXICrossProductMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXIOverlapsMatrixXIError>("_MatrixXIOverlapsMatrixXIError", no_init)
                .def("__str__", &MatrixXIOverlapsMatrixXIError::what)
                .def("firstMatrix", &MatrixXIOverlapsMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXIOverlapsMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXIContainsMatrixXdError>("_MatrixXIContainsMatrixXdError", no_init)
                .def("__str__", &MatrixXIContainsMatrixXdError::what)
                .def("firstMatrix", &MatrixXIContainsMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXIContainsMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXIContainsMatrixXIError>("_MatrixXIContainsMatrixXIError", no_init)
                .def("__str__", &MatrixXIContainsMatrixXIError::what)
                .def("firstMatrix", &MatrixXIContainsMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXIContainsMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXdHullMatrixXdError>("_MatrixXdHullMatrixXdError", no_init)
                .def("__str__", &MatrixXdHullMatrixXdError::what)
                .def("firstMatrix", &MatrixXdHullMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXdHullMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXdHullMatrixXIError>("_MatrixXdHullMatrixXIError", no_init)
                .def("__str__", &MatrixXdHullMatrixXIError::what)
                .def("firstMatrix", &MatrixXdHullMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXdHullMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXIHullMatrixXdError>("_MatrixXIHullMatrixXdError", no_init)
                .def("__str__", &MatrixXIHullMatrixXdError::what)
                .def("firstMatrix", &MatrixXIHullMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXIHullMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXIHullMatrixXIError>("_MatrixXIHullMatrixXIError", no_init)
                .def("__str__", &MatrixXIHullMatrixXIError::what)
                .def("firstMatrix", &MatrixXIHullMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXIHullMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXIIntersectionMatrixXIError>("_MatrixXIIntersectionMatrixXIError", no_init)
                .def("__str__", &MatrixXIIntersectionMatrixXIError::what)
                .def("firstMatrix", &MatrixXIIntersectionMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXIIntersectionMatrixXIError::secondMatrix)
        );
        registerException(
            class_<ConstantMatrixXdConstructionError>("_ConstantMatrixXdConstructionError", no_init)
                .def("__str__", &ConstantMatrixXdConstructionError::what)
                .def("rows", &ConstantMatrixXdConstructionError::rows)
                .def("cols", &ConstantMatrixXdConstructionError::cols)
                .def("value", &ConstantMatrixXdConstructionError::value)
        );
        registerException(
            class_<ConstantMatrixXIConstructionError>("_ConstantMatrixXIConstructionError", no_init)
                .def("__str__", &ConstantMatrixXIConstructionError::what)
                .def("rows", &ConstantMatrixXIConstructionError::rows)
                .def("cols", &ConstantMatrixXIConstructionError::cols)
                .def("value", &ConstantMatrixXIConstructionError::value)
        );
        registerException(
            class_<ZeroMatrixXdConstructionError>("_ZeroMatrixXdConstructionError", no_init)
                .def("__str__", &ZeroMatrixXdConstructionError::what)
                .def("rows", &ZeroMatrixXdConstructionError::rows)
                .def("cols", &ZeroMatrixXdConstructionError::cols)
        );
        registerException(
            class_<ZeroMatrixXIConstructionError>("_ZeroMatrixXIConstructionError", no_init)
                .def("__str__", &ZeroMatrixXIConstructionError::what)
                .def("rows", &ZeroMatrixXIConstructionError::rows)
                .def("cols", &ZeroMatrixXIConstructionError::cols)
        );
        registerException(
            class_<OnesMatrixXdConstructionError>("_OnesMatrixXdConstructionError", no_init)
                .def("__str__", &OnesMatrixXdConstructionError::what)
                .def("rows", &OnesMatrixXdConstructionError::rows)
                .def("cols", &OnesMatrixXdConstructionError::cols)
        );
        registerException(
            class_<OnesMatrixXIConstructionError>("_OnesMatrixXIConstructionError", no_init)
                .def("__str__", &OnesMatrixXIConstructionError::what)
                .def("rows", &OnesMatrixXIConstructionError::rows)
                .def("cols", &OnesMatrixXIConstructionError::cols)
        );
        registerException(
            class_<RandomMatrixXdConstructionError>("_RandomMatrixXdConstructionError", no_init)
                .def("__str__", &RandomMatrixXdConstructionError::what)
                .def("rows", &RandomMatrixXdConstructionError::rows)
                .def("cols", &RandomMatrixXdConstructionError::cols)
        );
        registerException(
            class_<RandomMatrixXIConstructionError>("_RandomMatrixXIConstructionError", no_init)
                .def("__str__", &RandomMatrixXIConstructionError::what)
                .def("rows", &RandomMatrixXIConstructionError::rows)
                .def("cols", &RandomMatrixXIConstructionError::cols)
        );
        registerException(
            class_<IdentityMatrixXdConstructionError>("_IdentityMatrixXdConstructionError", no_init)
                .def("__str__", &IdentityMatrixXdConstructionError::what)
                .def("rows", &IdentityMatrixXdConstructionError::rows)
                .def("cols", &IdentityMatrixXdConstructionError::cols)
        );
        registerException(
            class_<IdentityMatrixXIConstructionError>("_IdentityMatrixXIConstructionError", no_init)
                .def("__str__", &IdentityMatrixXIConstructionError::what)
                .def("rows", &IdentityMatrixXIConstructionError::rows)
                .def("cols", &IdentityMatrixXIConstructionError::cols)
        );
        registerException(
            class_<MatrixXdSumMatrixXdError>("_MatrixXdSumMatrixXdError", no_init)
                .def("__str__", &MatrixXdSumMatrixXdError::what)
                .def("firstMatrix", &MatrixXdSumMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXdSumMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXdSumMatrixXIError>("_MatrixXdSumMatrixXIError", no_init)
                .def("__str__", &MatrixXdSumMatrixXIError::what)
                .def("firstMatrix", &MatrixXdSumMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXdSumMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXISumMatrixXdError>("_MatrixXISumMatrixXdError", no_init)
                .def("__str__", &MatrixXISumMatrixXdError::what)
                .def("firstMatrix", &MatrixXISumMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXISumMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXISumMatrixXIError>("_MatrixXISumMatrixXIError", no_init)
                .def("__str__", &MatrixXISumMatrixXIError::what)
                .def("firstMatrix", &MatrixXISumMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXISumMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXdDifferenceMatrixXdError>("_MatrixXdDifferenceMatrixXdError", no_init)
                .def("__str__", &MatrixXdDifferenceMatrixXdError::what)
                .def("firstMatrix", &MatrixXdDifferenceMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXdDifferenceMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXdDifferenceMatrixXIError>("_MatrixXdDifferenceMatrixXIError", no_init)
                .def("__str__", &MatrixXdDifferenceMatrixXIError::what)
                .def("firstMatrix", &MatrixXdDifferenceMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXdDifferenceMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXIDifferenceMatrixXdError>("_MatrixXIDifferenceMatrixXdError", no_init)
                .def("__str__", &MatrixXIDifferenceMatrixXdError::what)
                .def("firstMatrix", &MatrixXIDifferenceMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXIDifferenceMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXIDifferenceMatrixXIError>("_MatrixXIDifferenceMatrixXIError", no_init)
                .def("__str__", &MatrixXIDifferenceMatrixXIError::what)
                .def("firstMatrix", &MatrixXIDifferenceMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXIDifferenceMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXdQuotientDoubleError>("_MatrixXdQuotientDoubleError", no_init)
                .def("__str__", &MatrixXdQuotientDoubleError::what)
                .def("matrix", &MatrixXdQuotientDoubleError::matrix)
                .def("divisor", &MatrixXdQuotientDoubleError::divisor)
        );
        registerException(
            class_<MatrixXdQuotientIntervalError>("_MatrixXdQuotientIntervalError", no_init)
                .def("__str__", &MatrixXdQuotientIntervalError::what)
                .def("matrix", &MatrixXdQuotientIntervalError::matrix)
                .def("divisor", &MatrixXdQuotientIntervalError::divisor)
        );
        registerException(
            class_<MatrixXIQuotientDoubleError>("_MatrixXIQuotientDoubleError", no_init)
                .def("__str__", &MatrixXIQuotientDoubleError::what)
                .def("matrix", &MatrixXIQuotientDoubleError::matrix)
                .def("divisor", &MatrixXIQuotientDoubleError::divisor)
        );
        registerException(
            class_<MatrixXIQuotientIntervalError>("_MatrixXIQuotientIntervalError", no_init)
                .def("__str__", &MatrixXIQuotientIntervalError::what)
                .def("matrix", &MatrixXIQuotientIntervalError::matrix)
                .def("divisor", &MatrixXIQuotientIntervalError::divisor)
        );
        registerException(
            class_<MatrixXdProductMatrixXdError>("_MatrixXdProductMatrixXdError", no_init)
                .def("__str__", &MatrixXdProductMatrixXdError::what)
                .def("firstMatrix", &MatrixXdProductMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXdProductMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXdProductMatrixXIError>("_MatrixXdProductMatrixXIError", no_init)
                .def("__str__", &MatrixXdProductMatrixXIError::what)
                .def("firstMatrix", &MatrixXdProductMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXdProductMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXIProductMatrixXdError>("_MatrixXIProductMatrixXdError", no_init)
                .def("__str__", &MatrixXIProductMatrixXdError::what)
                .def("firstMatrix", &MatrixXIProductMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXIProductMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXIProductMatrixXIError>("_MatrixXIProductMatrixXIError", no_init)
                .def("__str__", &MatrixXIProductMatrixXIError::what)
                .def("firstMatrix", &MatrixXIProductMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXIProductMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXdEqualityMatrixXdError>("_MatrixXdEqualityMatrixXdError", no_init)
                .def("__str__", &MatrixXdEqualityMatrixXdError::what)
                .def("firstMatrix", &MatrixXdEqualityMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXdEqualityMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXdEqualityMatrixXIError>("_MatrixXdEqualityMatrixXIError", no_init)
                .def("__str__", &MatrixXdEqualityMatrixXIError::what)
                .def("firstMatrix", &MatrixXdEqualityMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXdEqualityMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXIEqualityMatrixXdError>("_MatrixXIEqualityMatrixXdError", no_init)
                .def("__str__", &MatrixXIEqualityMatrixXdError::what)
                .def("firstMatrix", &MatrixXIEqualityMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXIEqualityMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXIEqualityMatrixXIError>("_MatrixXIEqualityMatrixXIError", no_init)
                .def("__str__", &MatrixXIEqualityMatrixXIError::what)
                .def("firstMatrix", &MatrixXIEqualityMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXIEqualityMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXdInequalityMatrixXdError>("_MatrixXdInequalityMatrixXdError", no_init)
                .def("__str__", &MatrixXdInequalityMatrixXdError::what)
                .def("firstMatrix", &MatrixXdInequalityMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXdInequalityMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXdInequalityMatrixXIError>("_MatrixXdInequalityMatrixXIError", no_init)
                .def("__str__", &MatrixXdInequalityMatrixXIError::what)
                .def("firstMatrix", &MatrixXdInequalityMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXdInequalityMatrixXIError::secondMatrix)
        );
        registerException(
            class_<MatrixXIInequalityMatrixXdError>("_MatrixXIInequalityMatrixXdError", no_init)
                .def("__str__", &MatrixXIInequalityMatrixXdError::what)
                .def("firstMatrix", &MatrixXIInequalityMatrixXdError::firstMatrix)
                .def("secondMatrix", &MatrixXIInequalityMatrixXdError::secondMatrix)
        );
        registerException(
            class_<MatrixXIInequalityMatrixXIError>("_MatrixXIInequalityMatrixXIError", no_init)
                .def("__str__", &MatrixXIInequalityMatrixXIError::what)
                .def("firstMatrix", &MatrixXIInequalityMatrixXIError::firstMatrix)
                .def("secondMatrix", &MatrixXIInequalityMatrixXIError::secondMatrix)
        );
        registerException(
            class_<Vector2dCopyConstructionError>("_Vector2dCopyConstructionError", no_init)
                .def("__str__", &Vector2dCopyConstructionError::what)
                .def("argument", &Vector2dCopyConstructionError::argument)
        );
        registerException(
            class_<Vector3dCopyConstructionError>("_Vector3dCopyConstructionError", no_init)
                .def("__str__", &Vector3dCopyConstructionError::what)
                .def("argument", &Vector3dCopyConstructionError::argument)
        );
        registerException(
            class_<VectorXdCopyConstructionError>("_VectorXdCopyConstructionError", no_init)
                .def("__str__", &VectorXdCopyConstructionError::what)
                .def("argument", &VectorXdCopyConstructionError::argument)
        );
        registerException(
            class_<RowVector2dCopyConstructionError>("_RowVector2dCopyConstructionError", no_init)
                .def("__str__", &RowVector2dCopyConstructionError::what)
                .def("argument", &RowVector2dCopyConstructionError::argument)
        );
        registerException(
            class_<RowVector3dCopyConstructionError>("_RowVector3dCopyConstructionError", no_init)
                .def("__str__", &RowVector3dCopyConstructionError::what)
                .def("argument", &RowVector3dCopyConstructionError::argument)
        );
        registerException(
            class_<RowVectorXdCopyConstructionError>("_RowVectorXdCopyConstructionError", no_init)
                .def("__str__", &RowVectorXdCopyConstructionError::what)
                .def("argument", &RowVectorXdCopyConstructionError::argument)
        );
        registerException(
            class_<Matrix2dCopyConstructionError>("_Matrix2dCopyConstructionError", no_init)
                .def("__str__", &Matrix2dCopyConstructionError::what)
                .def("argument", &Matrix2dCopyConstructionError::argument)
        );
        registerException(
            class_<Matrix3dCopyConstructionError>("_Matrix3dCopyConstructionError", no_init)
                .def("__str__", &Matrix3dCopyConstructionError::what)
                .def("argument", &Matrix3dCopyConstructionError::argument)
        );
        registerException(
            class_<Vector2ICopyConstructionError>("_Vector2ICopyConstructionError", no_init)
                .def("__str__", &Vector2ICopyConstructionError::what)
                .def("argument", &Vector2ICopyConstructionError::argument)
        );
        registerException(
            class_<Vector3ICopyConstructionError>("_Vector3ICopyConstructionError", no_init)
                .def("__str__", &Vector3ICopyConstructionError::what)
                .def("argument", &Vector3ICopyConstructionError::argument)
        );
        registerException(
            class_<VectorXICopyConstructionError>("_VectorXICopyConstructionError", no_init)
                .def("__str__", &VectorXICopyConstructionError::what)
                .def("argument", &VectorXICopyConstructionError::argument)
        );
        registerException(
            class_<RowVector2ICopyConstructionError>("_RowVector2ICopyConstructionError", no_init)
                .def("__str__", &RowVector2ICopyConstructionError::what)
                .def("argument", &RowVector2ICopyConstructionError::argument)
        );
        registerException(
            class_<RowVector3ICopyConstructionError>("_RowVector3ICopyConstructionError", no_init)
                .def("__str__", &RowVector3ICopyConstructionError::what)
                .def("argument", &RowVector3ICopyConstructionError::argument)
        );
        registerException(
            class_<RowVectorXICopyConstructionError>("_RowVectorXICopyConstructionError", no_init)
                .def("__str__", &RowVectorXICopyConstructionError::what)
                .def("argument", &RowVectorXICopyConstructionError::argument)
        );
        registerException(
            class_<Matrix2ICopyConstructionError>("_Matrix2ICopyConstructionError", no_init)
                .def("__str__", &Matrix2ICopyConstructionError::what)
                .def("argument", &Matrix2ICopyConstructionError::argument)
        );
        registerException(
            class_<Matrix3ICopyConstructionError>("_Matrix3ICopyConstructionError", no_init)
                .def("__str__", &Matrix3ICopyConstructionError::what)
                .def("argument", &Matrix3ICopyConstructionError::argument)
        );
        registerException(
            class_<UnitVector2dConstructionError>("_UnitVector2dConstructionError", no_init)
                .def("__str__", &UnitVector2dConstructionError::what)
                .def("index", &UnitVector2dConstructionError::index)
        );
        registerException(
            class_<UnitVector3dConstructionError>("_UnitVector3dConstructionError", no_init)
                .def("__str__", &UnitVector3dConstructionError::what)
                .def("index", &UnitVector3dConstructionError::index)
        );
        registerException(
            class_<UnitVectorXdConstructionError>("_UnitVectorXdConstructionError", no_init)
                .def("__str__", &UnitVectorXdConstructionError::what)
                .def("size", &UnitVectorXdConstructionError::size)
                .def("index", &UnitVectorXdConstructionError::index)
        );
        registerException(
            class_<UnitRowVector2dConstructionError>("_UnitRowVector2dConstructionError", no_init)
                .def("__str__", &UnitRowVector2dConstructionError::what)
                .def("index", &UnitRowVector2dConstructionError::index)
        );
        registerException(
            class_<UnitRowVector3dConstructionError>("_UnitRowVector3dConstructionError", no_init)
                .def("__str__", &UnitRowVector3dConstructionError::what)
                .def("index", &UnitRowVector3dConstructionError::index)
        );
        registerException(
            class_<UnitRowVectorXdConstructionError>("_UnitRowVectorXdConstructionError", no_init)
                .def("__str__", &UnitRowVectorXdConstructionError::what)
                .def("size", &UnitRowVectorXdConstructionError::size)
                .def("index", &UnitRowVectorXdConstructionError::index)
        );
        registerException(
            class_<UnitVector2IConstructionError>("_UnitVector2IConstructionError", no_init)
                .def("__str__", &UnitVector2IConstructionError::what)
                .def("index", &UnitVector2IConstructionError::index)
        );
        registerException(
            class_<UnitVector3IConstructionError>("_UnitVector3IConstructionError", no_init)
                .def("__str__", &UnitVector3IConstructionError::what)
                .def("index", &UnitVector3IConstructionError::index)
        );
        registerException(
            class_<UnitVectorXIConstructionError>("_UnitVectorXIConstructionError", no_init)
                .def("__str__", &UnitVectorXIConstructionError::what)
                .def("size", &UnitVectorXIConstructionError::size)
                .def("index", &UnitVectorXIConstructionError::index)
        );
        registerException(
            class_<UnitRowVector2IConstructionError>("_UnitRowVector2IConstructionError", no_init)
                .def("__str__", &UnitRowVector2IConstructionError::what)
                .def("index", &UnitRowVector2IConstructionError::index)
        );
        registerException(
            class_<UnitRowVector3IConstructionError>("_UnitRowVector3IConstructionError", no_init)
                .def("__str__", &UnitRowVector3IConstructionError::what)
                .def("index", &UnitRowVector3IConstructionError::index)
        );
        registerException(
            class_<UnitRowVectorXIConstructionError>("_UnitRowVectorXIConstructionError", no_init)
                .def("__str__", &UnitRowVectorXIConstructionError::what)
                .def("size", &UnitRowVectorXIConstructionError::size)
                .def("index", &UnitRowVectorXIConstructionError::index)
        );
        registerException(
            class_<ObjectPropertyError>("_ObjectPropertyError", no_init)
                .def("__str__", &ObjectPropertyError::what)
                .def("object", &ObjectPropertyError::object)
                .def("name", &ObjectPropertyError::name)
                .def("requestedType", &ObjectPropertyError::requestedType)
        );
        registerException(
            class_<NotImplementedError>("_NotImplementedError", no_init)
                .def("__str__", &NotImplementedError::what)
                .def("file", &NotImplementedError::file)
                .def("line", &NotImplementedError::line)
        );
    }
}
