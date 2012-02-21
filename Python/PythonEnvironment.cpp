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

#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <OpenSolid/Core/Common/Error.hpp>
#include <OpenSolid/Core/Datum/Axis.hpp>
#include <OpenSolid/Core/Object/Object.hpp>
#include <OpenSolid/Python/PythonEnvironment.hpp>

using namespace boost::python;

namespace OpenSolid
{
    PythonStackFrame::PythonStackFrame() : _line_number(0) {}

    PythonStackFrame::PythonStackFrame(
        const std::string& filename,
        int line_number,
        const std::string& function_name,
        const std::string& text
    ) : _filename(filename),
        _line_number(line_number),
        _function_name(function_name),
        _text(text) {}

    std::string PythonStackFrame::filename() const {return _filename;}

    int PythonStackFrame::lineNumber() const {return _line_number;}

    std::string PythonStackFrame::functionName() const {return _function_name;}

    std::string PythonStackFrame::text() const {return _text;}

    std::ostream& operator<<(std::ostream& stream, const PythonStackFrame& stack_frame) {
        stream << "File " << stack_frame.filename() << ", ";
        stream << "line " << stack_frame.lineNumber() << ", ";
        stream << "in " << stack_frame.functionName();
        std::string text = stack_frame.text();
        if (!text.empty()) {stream << ": " << text;};
        return stream;
    }

    object pythonErrorBaseClass();

    template <class ErrorType>
    void checkForPythonError(PyObject* raised_type, PyObject* error_type) {
        if (PyErr_GivenExceptionMatches(raised_type, error_type)) {throw ErrorType();}
    }

    template <class ErrorType>
    void checkForOpenSolidError(object error_object) {
        extract<ErrorType> extracted(error_object);
        if (extracted.check()) {throw extracted();}
    }

    void PythonEnvironment::throwError() {
        PyObject* type_pointer = nullptr;
        PyObject* value_pointer = nullptr;
        PyObject* traceback_pointer = nullptr;
        PyErr_Fetch(&type_pointer, &value_pointer, &traceback_pointer);
        if (type_pointer) {_error_type = object(handle<>(type_pointer));}
        if (value_pointer) {_error_value = object(handle<>(value_pointer));}
        if (traceback_pointer) {_traceback = object(handle<>(traceback_pointer));}
        if (PyErr_GivenExceptionMatches(type_pointer, pythonErrorBaseClass().ptr())) {
            object error_object = _error_value.attr("args")[0];
            checkForOpenSolidError<Axis2dConstructionError>(error_object);
            checkForOpenSolidError<Axis2dCopyConstructionError>(error_object);
            checkForOpenSolidError<Axis3dConstructionError>(error_object);
            checkForOpenSolidError<Axis3dCopyConstructionError>(error_object);
            checkForOpenSolidError<ConstantMatrixXIConstructionError>(error_object);
            checkForOpenSolidError<ConstantMatrixXdConstructionError>(error_object);
            checkForOpenSolidError<IdentityMatrixXIConstructionError>(error_object);
            checkForOpenSolidError<IdentityMatrixXdConstructionError>(error_object);
            checkForOpenSolidError<Matrix2ICopyConstructionError>(error_object);
            checkForOpenSolidError<Matrix2dCopyConstructionError>(error_object);
            checkForOpenSolidError<Matrix3ICopyConstructionError>(error_object);
            checkForOpenSolidError<Matrix3dCopyConstructionError>(error_object);
            checkForOpenSolidError<MatrixXIAssignmentError>(error_object);
            checkForOpenSolidError<MatrixXIContainsMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXIContainsMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXICrossProductMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXICrossProductMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXIDeterminantError>(error_object);
            checkForOpenSolidError<MatrixXIDifferenceMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXIDifferenceMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXIDotProductMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXIDotProductMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXIEqualityMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXIEqualityMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXIHullMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXIHullMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXIIndexError>(error_object);
            checkForOpenSolidError<MatrixXIInequalityMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXIInequalityMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXIIntersectionMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXINormError>(error_object);
            checkForOpenSolidError<MatrixXINormalizedError>(error_object);
            checkForOpenSolidError<MatrixXIOverlapsMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXIProductMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXIProductMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXIQuotientDoubleError>(error_object);
            checkForOpenSolidError<MatrixXIQuotientIntervalError>(error_object);
            checkForOpenSolidError<MatrixXIReplicateError>(error_object);
            checkForOpenSolidError<MatrixXISquaredNormError>(error_object);
            checkForOpenSolidError<MatrixXISumMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXISumMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXIVectorAssignmentError>(error_object);
            checkForOpenSolidError<MatrixXIVectorComponentError>(error_object);
            checkForOpenSolidError<MatrixXIVectorIndexError>(error_object);
            checkForOpenSolidError<MatrixXdAssignmentError>(error_object);
            checkForOpenSolidError<MatrixXdCrossProductMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXdCrossProductMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXdDeterminantError>(error_object);
            checkForOpenSolidError<MatrixXdDifferenceMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXdDifferenceMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXdDotProductMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXdDotProductMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXdEqualityMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXdEqualityMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXdHullMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXdHullMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXdIndexError>(error_object);
            checkForOpenSolidError<MatrixXdInequalityMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXdInequalityMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXdInverseError>(error_object);
            checkForOpenSolidError<MatrixXdNormError>(error_object);
            checkForOpenSolidError<MatrixXdNormalizedError>(error_object);
            checkForOpenSolidError<MatrixXdProductMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXdProductMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXdQuotientDoubleError>(error_object);
            checkForOpenSolidError<MatrixXdQuotientIntervalError>(error_object);
            checkForOpenSolidError<MatrixXdReplicateError>(error_object);
            checkForOpenSolidError<MatrixXdSquaredNormError>(error_object);
            checkForOpenSolidError<MatrixXdSumMatrixXIError>(error_object);
            checkForOpenSolidError<MatrixXdSumMatrixXdError>(error_object);
            checkForOpenSolidError<MatrixXdVectorAssignmentError>(error_object);
            checkForOpenSolidError<MatrixXdVectorComponentError>(error_object);
            checkForOpenSolidError<MatrixXdVectorIndexError>(error_object);
            checkForOpenSolidError<ObjectPropertyError>(error_object);
            checkForOpenSolidError<ObjectConversionError>(error_object);
            checkForOpenSolidError<OnesMatrixXIConstructionError>(error_object);
            checkForOpenSolidError<OnesMatrixXdConstructionError>(error_object);
            checkForOpenSolidError<RandomMatrixXIConstructionError>(error_object);
            checkForOpenSolidError<RandomMatrixXdConstructionError>(error_object);
            checkForOpenSolidError<RowVector2ICopyConstructionError>(error_object);
            checkForOpenSolidError<RowVector2dCopyConstructionError>(error_object);
            checkForOpenSolidError<RowVector3ICopyConstructionError>(error_object);
            checkForOpenSolidError<RowVector3dCopyConstructionError>(error_object);
            checkForOpenSolidError<RowVectorXICopyConstructionError>(error_object);
            checkForOpenSolidError<RowVectorXdCopyConstructionError>(error_object);
            checkForOpenSolidError<UnitRowVector2IConstructionError>(error_object);
            checkForOpenSolidError<UnitRowVector2dConstructionError>(error_object);
            checkForOpenSolidError<UnitRowVector3IConstructionError>(error_object);
            checkForOpenSolidError<UnitRowVector3dConstructionError>(error_object);
            checkForOpenSolidError<UnitRowVectorXIConstructionError>(error_object);
            checkForOpenSolidError<UnitRowVectorXdConstructionError>(error_object);
            checkForOpenSolidError<UnitVector2IConstructionError>(error_object);
            checkForOpenSolidError<UnitVector2dConstructionError>(error_object);
            checkForOpenSolidError<UnitVector3IConstructionError>(error_object);
            checkForOpenSolidError<UnitVector3dConstructionError>(error_object);
            checkForOpenSolidError<UnitVectorXIConstructionError>(error_object);
            checkForOpenSolidError<UnitVectorXdConstructionError>(error_object);
            checkForOpenSolidError<Vector2ICopyConstructionError>(error_object);
            checkForOpenSolidError<Vector2dCopyConstructionError>(error_object);
            checkForOpenSolidError<Vector3ICopyConstructionError>(error_object);
            checkForOpenSolidError<Vector3dCopyConstructionError>(error_object);
            checkForOpenSolidError<VectorXICopyConstructionError>(error_object);
            checkForOpenSolidError<VectorXdCopyConstructionError>(error_object);
            checkForOpenSolidError<ZeroMatrixXIConstructionError>(error_object);
            checkForOpenSolidError<ZeroMatrixXdConstructionError>(error_object);
        } else {
            checkForPythonError<PythonWarning>(type_pointer, PyExc_Warning);
            checkForPythonError<PythonUnicodeError>(type_pointer, PyExc_UnicodeError);
            checkForPythonError<PythonValueError>(type_pointer, PyExc_ValueError);
            checkForPythonError<PythonTypeError>(type_pointer, PyExc_TypeError);
            checkForPythonError<PythonSystemError>(type_pointer, PyExc_SystemError);
            checkForPythonError<PythonIndentationError>(type_pointer, PyExc_IndentationError);
            checkForPythonError<PythonSyntaxError>(type_pointer, PyExc_SyntaxError);
            checkForPythonError<PythonNotImplementedError>(type_pointer, PyExc_NotImplementedError);
            checkForPythonError<PythonRuntimeError>(type_pointer, PyExc_RuntimeError);
            checkForPythonError<PythonReferenceError>(type_pointer, PyExc_ReferenceError);
            checkForPythonError<PythonUnboundLocalError>(type_pointer, PyExc_UnboundLocalError);
            checkForPythonError<PythonNameError>(type_pointer, PyExc_NameError);
            checkForPythonError<PythonMemoryError>(type_pointer, PyExc_MemoryError);
            checkForPythonError<PythonKeyError>(type_pointer, PyExc_KeyError);
            checkForPythonError<PythonIndexError>(type_pointer, PyExc_IndexError);
            checkForPythonError<PythonLookupError>(type_pointer, PyExc_LookupError);
            checkForPythonError<PythonImportError>(type_pointer, PyExc_ImportError);
            checkForPythonError<PythonEOFError>(type_pointer, PyExc_EOFError);
            checkForPythonError<PythonOSError>(type_pointer, PyExc_OSError);
            checkForPythonError<PythonIOError>(type_pointer, PyExc_IOError);
            checkForPythonError<PythonEnvironmentError>(type_pointer, PyExc_EnvironmentError);
            checkForPythonError<PythonBufferError>(type_pointer, PyExc_BufferError);
            checkForPythonError<PythonAttributeError>(type_pointer, PyExc_AttributeError);
            checkForPythonError<PythonAssertionError>(type_pointer, PyExc_AssertionError);
            checkForPythonError<PythonZeroDivisionError>(type_pointer, PyExc_ZeroDivisionError);
            checkForPythonError<PythonOverflowError>(type_pointer, PyExc_OverflowError);
            checkForPythonError<PythonFloatingPointError>(type_pointer, PyExc_FloatingPointError);
            checkForPythonError<PythonArithmeticError>(type_pointer, PyExc_ArithmeticError);
            checkForPythonError<PythonException>(type_pointer, PyExc_Exception);
        }
        throw UnexpectedPythonError();
    }

    object PythonEnvironment::eval(const std::string& code) {
        std::vector<std::string> lines;
        boost::algorithm::split(
            lines,
            code,
            boost::algorithm::is_any_of("\r\n"),
            boost::algorithm::token_compress_on
        );
        if (lines.back().empty()) {lines.pop_back();}
        std::string last_line = lines.back();
        lines.pop_back();
        if (!lines.empty()) {run(boost::algorithm::join(lines, "\n"));}
        try {
            return boost::python::eval(str(last_line), _environment_dict, _environment_dict);
        } catch (const error_already_set&) {
            throwError();
            return object(); // Should never be reached
        }
    }
    
    extern "C" OPENSOLID_PYTHON_EXPORT void initopensolid();

    PythonEnvironment::PythonEnvironment() {
        if (!Py_IsInitialized()) {Py_Initialize();}
        static bool initialized = false;
        static object global;
        static object hidden;
        static object print_exception;
        static object string_io;
        static object extract_tb;
        if (!initialized) {
            initopensolid();
            global = import("__main__").attr("__dict__");
            hidden = dict(global);
            exec("import opensolid", global, global);
            exec("from opensolid import *", global, global);
            exec("class Environment: pass", hidden, hidden);
            object traceback_module = import("traceback");
            print_exception = traceback_module.attr("print_exception");
            string_io = import("StringIO").attr("StringIO");
            extract_tb = traceback_module.attr("extract_tb");
            initialized = true;
        }
        _environment_dict = dict(global);
        _environment = boost::python::eval("Environment()", hidden, hidden);
        _environment.attr("__dict__") = _environment_dict;
        _print_exception = print_exception;
        _string_io = string_io;
        _extract_tb = extract_tb;
    }

    object PythonEnvironment::environment() {return _environment;}
    
    PythonEnvironment& PythonEnvironment::run(const std::string& argument) {
        try {
            exec(str(argument), _environment_dict, _environment_dict);
        } catch (const error_already_set&) {
            throwError();
        }
        return *this;
    }
    
    PythonEnvironment& PythonEnvironment::runFile(const std::string& filename) {
        try {
            exec_file(str(filename), _environment_dict, _environment_dict);
        } catch (const error_already_set&) {
            throwError();
        }
        return *this;
    }

    std::string PythonEnvironment::formattedTraceback() const {
        std::string result;
        if (_traceback) {
            object string_io = _string_io();
            _print_exception(_error_type, _error_value, _traceback, object(), string_io);
            result = extract<std::string>(string_io.attr("getvalue")());
        }
        return result;
    }

    std::vector<PythonStackFrame> PythonEnvironment::stackTrace() const {
        std::vector<PythonStackFrame> result;
        if (_traceback) {
            object stack_trace = _extract_tb(_traceback);
            int num_frames = len(stack_trace);
            result.resize(num_frames);
            for (int i = 0; i < num_frames; ++i) {
                object frame = stack_trace[i];
                std::string filename = extract<std::string>(frame[0]);
                int line_number = extract<int>(frame[1]);
                std::string function_name = extract<std::string>(frame[2]);
                std::string text;
                if (frame[3]) {text = extract<std::string>(frame[3]);}
                result[i] = PythonStackFrame(filename, line_number, function_name, text);
            }
        }
        return result;
    }

    ConversionFromPythonError::ConversionFromPythonError(
        const boost::python::object& python_object,
        const std::string& expected_type
    ) : _python_object(python_object), _expected_type(expected_type) {}

    const char* ConversionFromPythonError::what() const {
        return "ConversionFromPythonError";
    }

    boost::python::object ConversionFromPythonError::pythonObject() const {return _python_object;}

    std::string ConversionFromPythonError::expectedType() const {return _expected_type;}

    ConversionToPythonError::ConversionToPythonError(const std::string& type) : _type(type) {}
        
    const char* ConversionToPythonError::what() const {
        return "ConversionToPythonError";
    }
    
    std::string ConversionToPythonError::type() const {return _type;}

    const char* UnexpectedPythonError::what() const {
        return "UnexpectedPythonError";
    }
    
    const char* PythonException::what() const {
        return "PythonException";
    }

    const char* PythonArithmeticError::what() const {
        return "PythonArithmeticError";
    }

    const char* PythonFloatingPointError::what() const {
        return "PythonFloatingPointError";
    }

    const char* PythonOverflowError::what() const {
        return "PythonOverflowError";
    }

    const char* PythonZeroDivisionError::what() const {
        return "PythonZeroDivisionError";
    }

    const char* PythonAssertionError::what() const {
        return "PythonAssertionError";
    }

    const char* PythonAttributeError::what() const {
        return "PythonAttributeError";
    }

    const char* PythonBufferError::what() const {
        return "PythonBufferError";
    }

    const char* PythonEnvironmentError::what() const {
        return "PythonEnvironmentError";
    }

    const char* PythonIOError::what() const {
        return "PythonIOError";
    }

    const char* PythonOSError::what() const {
        return "PythonOSError";
    }

    const char* PythonEOFError::what() const {
        return "PythonEOFError";
    }

    const char* PythonImportError::what() const {
        return "PythonImportError";
    }

    const char* PythonLookupError::what() const {
        return "PythonLookupError";
    }

    const char* PythonIndexError::what() const {
        return "PythonIndexError";
    }

    const char* PythonKeyError::what() const {
        return "PythonKeyError";
    }

    const char* PythonMemoryError::what() const {
        return "PythonMemoryError";
    }

    const char* PythonNameError::what() const {
        return "PythonNameError";
    }

    const char* PythonUnboundLocalError::what() const {
        return "PythonUnboundLocalError";
    }

    const char* PythonReferenceError::what() const {
        return "PythonReferenceError";
    }

    const char* PythonRuntimeError::what() const {
        return "PythonRuntimeError";
    }

    const char* PythonNotImplementedError::what() const {
        return "PythonNotImplementedError";
    }

    const char* PythonSyntaxError::what() const {
        return "PythonSyntaxError";
    }

    const char* PythonIndentationError::what() const {
        return "PythonIndentationError";
    }

    const char* PythonSystemError::what() const {
        return "PythonSystemError";
    }

    const char* PythonTypeError::what() const {
        return "PythonTypeError";
    }

    const char* PythonValueError::what() const {
        return "PythonValueError";
    }

    const char* PythonUnicodeError::what() const {
        return "PythonUnicodeError";
    }

    const char* PythonWarning::what() const {
        return "PythonWarning";
    }
}
