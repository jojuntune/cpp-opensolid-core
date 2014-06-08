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

#include <OpenSolid/Python/PythonEnvironment.hpp>

#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Python/PythonExtension.hpp>

using namespace boost::python;

namespace opensolid
{
    PythonStackFrame::PythonStackFrame() :
        _lineNumber(0) {
    }

    PythonStackFrame::PythonStackFrame(
        const std::string& filename,
        int lineNumber,
        const std::string& functionName,
        const std::string& text
    ) : _filename(filename),
        _lineNumber(lineNumber),
        _functionName(functionName),
        _text(text) {
    }

    std::string
    PythonStackFrame::filename() const {
        return _filename;
    }

    int
    PythonStackFrame::lineNumber() const {
        return _lineNumber;
    }

    std::string
    PythonStackFrame::functionName() const {
        return _functionName;
    }

    std::string
    PythonStackFrame::text() const {
        return _text;
    }

    std::ostream&
    operator<<(std::ostream& stream, const PythonStackFrame& stackFrame) {
        stream << "File " << stackFrame.filename() << ", ";
        stream << "line " << stackFrame.lineNumber() << ", ";
        stream << "in " << stackFrame.functionName();
        std::string text = stackFrame.text();
        if (!text.empty()) {
            stream << ": " << text;
        };
        return stream;
    }

    object
    pythonErrorClass();

    template <class ErrorType>
    void
    checkForPythonError(PyObject* raisedType, PyObject* errorType) {
        if (PyErr_GivenExceptionMatches(raisedType, errorType)) {
            throw ErrorType();
        }
    }

    template <class ErrorType>
    void
    checkForOpenSolidError(object errorObject) {
        extract<ErrorType> extracted(errorObject);
        if (extracted.check()) {
            throw extracted();
        }
    }

    void
    PythonEnvironment::throwError() {
        PyObject* typePointer = nullptr;
        PyObject* valuePointer = nullptr;
        PyObject* tracebackPointer = nullptr;
        PyErr_Fetch(&typePointer, &valuePointer, &tracebackPointer);
        if (typePointer) {
            _error_type = object(handle<>(typePointer));
        }
        if (valuePointer) {
            _error_value = object(handle<>(valuePointer));
        }
        if (tracebackPointer) {
            _traceback = object(handle<>(tracebackPointer));
        }
        if (PyErr_GivenExceptionMatches(typePointer, pythonErrorBaseClass().ptr())) {
            object errorObject = _error_value.attr("args")[0];
            checkForOpenSolidError<Axis2dConstructionError>(errorObject);
            checkForOpenSolidError<Axis2dCopyConstructionError>(errorObject);
            checkForOpenSolidError<Axis3dConstructionError>(errorObject);
            checkForOpenSolidError<Axis3dCopyConstructionError>(errorObject);
            checkForOpenSolidError<ConstantMatrixXIConstructionError>(errorObject);
            checkForOpenSolidError<ConstantMatrixXdConstructionError>(errorObject);
            checkForOpenSolidError<IdentityMatrixXIConstructionError>(errorObject);
            checkForOpenSolidError<IdentityMatrixXdConstructionError>(errorObject);
            checkForOpenSolidError<Matrix2ICopyConstructionError>(errorObject);
            checkForOpenSolidError<Matrix2dCopyConstructionError>(errorObject);
            checkForOpenSolidError<Matrix3ICopyConstructionError>(errorObject);
            checkForOpenSolidError<Matrix3dCopyConstructionError>(errorObject);
            checkForOpenSolidError<MatrixXIAssignmentError>(errorObject);
            checkForOpenSolidError<MatrixXIContainsMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXIContainsMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXICrossProductMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXICrossProductMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXIDeterminantError>(errorObject);
            checkForOpenSolidError<MatrixXIDifferenceMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXIDifferenceMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXIDotProductMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXIDotProductMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXIEqualityMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXIEqualityMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXIHullMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXIHullMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXIIndexError>(errorObject);
            checkForOpenSolidError<MatrixXIInequalityMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXIInequalityMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXIIntersectionMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXINormError>(errorObject);
            checkForOpenSolidError<MatrixXINormalizedError>(errorObject);
            checkForOpenSolidError<MatrixXIOverlapsMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXIProductMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXIProductMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXIQuotientDoubleError>(errorObject);
            checkForOpenSolidError<MatrixXIQuotientIntervalError>(errorObject);
            checkForOpenSolidError<MatrixXIReplicateError>(errorObject);
            checkForOpenSolidError<MatrixXISquaredNormError>(errorObject);
            checkForOpenSolidError<MatrixXISumMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXISumMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXIVectorAssignmentError>(errorObject);
            checkForOpenSolidError<MatrixXIVectorComponentError>(errorObject);
            checkForOpenSolidError<MatrixXIVectorIndexError>(errorObject);
            checkForOpenSolidError<MatrixXdAssignmentError>(errorObject);
            checkForOpenSolidError<MatrixXdCrossProductMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXdCrossProductMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXdDeterminantError>(errorObject);
            checkForOpenSolidError<MatrixXdDifferenceMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXdDifferenceMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXdDotProductMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXdDotProductMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXdEqualityMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXdEqualityMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXdHullMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXdHullMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXdIndexError>(errorObject);
            checkForOpenSolidError<MatrixXdInequalityMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXdInequalityMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXdInverseError>(errorObject);
            checkForOpenSolidError<MatrixXdNormError>(errorObject);
            checkForOpenSolidError<MatrixXdNormalizedError>(errorObject);
            checkForOpenSolidError<MatrixXdProductMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXdProductMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXdQuotientDoubleError>(errorObject);
            checkForOpenSolidError<MatrixXdQuotientIntervalError>(errorObject);
            checkForOpenSolidError<MatrixXdReplicateError>(errorObject);
            checkForOpenSolidError<MatrixXdSquaredNormError>(errorObject);
            checkForOpenSolidError<MatrixXdSumMatrixXIError>(errorObject);
            checkForOpenSolidError<MatrixXdSumMatrixXdError>(errorObject);
            checkForOpenSolidError<MatrixXdVectorAssignmentError>(errorObject);
            checkForOpenSolidError<MatrixXdVectorComponentError>(errorObject);
            checkForOpenSolidError<MatrixXdVectorIndexError>(errorObject);
            checkForOpenSolidError<NotImplementedError>(errorObject);
            checkForOpenSolidError<OnesMatrixXIConstructionError>(errorObject);
            checkForOpenSolidError<OnesMatrixXdConstructionError>(errorObject);
            checkForOpenSolidError<RandomMatrixXIConstructionError>(errorObject);
            checkForOpenSolidError<RandomMatrixXdConstructionError>(errorObject);
            checkForOpenSolidError<RowVector2ICopyConstructionError>(errorObject);
            checkForOpenSolidError<RowVector2dCopyConstructionError>(errorObject);
            checkForOpenSolidError<RowVector3ICopyConstructionError>(errorObject);
            checkForOpenSolidError<RowVector3dCopyConstructionError>(errorObject);
            checkForOpenSolidError<RowVectorXICopyConstructionError>(errorObject);
            checkForOpenSolidError<RowVectorXdCopyConstructionError>(errorObject);
            checkForOpenSolidError<UnitRowVector2IConstructionError>(errorObject);
            checkForOpenSolidError<UnitRowVector2dConstructionError>(errorObject);
            checkForOpenSolidError<UnitRowVector3IConstructionError>(errorObject);
            checkForOpenSolidError<UnitRowVector3dConstructionError>(errorObject);
            checkForOpenSolidError<UnitRowVectorXIConstructionError>(errorObject);
            checkForOpenSolidError<UnitRowVectorXdConstructionError>(errorObject);
            checkForOpenSolidError<UnitVector2IConstructionError>(errorObject);
            checkForOpenSolidError<UnitVector2dConstructionError>(errorObject);
            checkForOpenSolidError<UnitVector3IConstructionError>(errorObject);
            checkForOpenSolidError<UnitVector3dConstructionError>(errorObject);
            checkForOpenSolidError<UnitVectorXIConstructionError>(errorObject);
            checkForOpenSolidError<UnitVectorXdConstructionError>(errorObject);
            checkForOpenSolidError<Vector2ICopyConstructionError>(errorObject);
            checkForOpenSolidError<Vector2dCopyConstructionError>(errorObject);
            checkForOpenSolidError<Vector3ICopyConstructionError>(errorObject);
            checkForOpenSolidError<Vector3dCopyConstructionError>(errorObject);
            checkForOpenSolidError<VectorXICopyConstructionError>(errorObject);
            checkForOpenSolidError<VectorXdCopyConstructionError>(errorObject);
            checkForOpenSolidError<ZeroMatrixXIConstructionError>(errorObject);
            checkForOpenSolidError<ZeroMatrixXdConstructionError>(errorObject);
        } else {
            checkForPythonError<PythonWarning>(typePointer, PyExc_Warning);
            checkForPythonError<PythonUnicodeError>(typePointer, PyExc_UnicodeError);
            checkForPythonError<PythonValueError>(typePointer, PyExc_ValueError);
            checkForPythonError<PythonTypeError>(typePointer, PyExc_TypeError);
            checkForPythonError<PythonSystemError>(typePointer, PyExc_SystemError);
            checkForPythonError<PythonIndentationError>(typePointer, PyExc_IndentationError);
            checkForPythonError<PythonSyntaxError>(typePointer, PyExc_SyntaxError);
            checkForPythonError<PythonNotImplementedError>(typePointer, PyExc_NotImplementedError);
            checkForPythonError<PythonRuntimeError>(typePointer, PyExc_RuntimeError);
            checkForPythonError<PythonReferenceError>(typePointer, PyExc_ReferenceError);
            checkForPythonError<PythonUnboundLocalError>(typePointer, PyExc_UnboundLocalError);
            checkForPythonError<PythonNameError>(typePointer, PyExc_NameError);
            checkForPythonError<PythonMemoryError>(typePointer, PyExc_MemoryError);
            checkForPythonError<PythonKeyError>(typePointer, PyExc_KeyError);
            checkForPythonError<PythonIndexError>(typePointer, PyExc_IndexError);
            checkForPythonError<PythonLookupError>(typePointer, PyExc_LookupError);
            checkForPythonError<PythonImportError>(typePointer, PyExc_ImportError);
            checkForPythonError<PythonEOFError>(typePointer, PyExc_EOFError);
            checkForPythonError<PythonOSError>(typePointer, PyExc_OSError);
            checkForPythonError<PythonIOError>(typePointer, PyExc_IOError);
            checkForPythonError<PythonEnvironmentError>(typePointer, PyExc_EnvironmentError);
            checkForPythonError<PythonBufferError>(typePointer, PyExc_BufferError);
            checkForPythonError<PythonAttributeError>(typePointer, PyExc_AttributeError);
            checkForPythonError<PythonAssertionError>(typePointer, PyExc_AssertionError);
            checkForPythonError<PythonZeroDivisionError>(typePointer, PyExc_ZeroDivisionError);
            checkForPythonError<PythonOverflowError>(typePointer, PyExc_OverflowError);
            checkForPythonError<PythonFloatingPointError>(typePointer, PyExc_FloatingPointError);
            checkForPythonError<PythonArithmeticError>(typePointer, PyExc_ArithmeticError);
            checkForPythonError<PythonException>(typePointer, PyExc_Exception);
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
        const boost::python::object& python_object
    ) : _python_object(python_object) {}

    ConversionFromPythonError::~ConversionFromPythonError() throw() {}

    const char* ConversionFromPythonError::what() const throw() {
        return "ConversionFromPythonError";
    }

    boost::python::object ConversionFromPythonError::pythonObject() const {return _python_object;}

    ConversionToPythonError::ConversionToPythonError() {}

    ConversionToPythonError::~ConversionToPythonError() throw() {}
        
    const char* ConversionToPythonError::what() const throw() {
        return "ConversionToPythonError";
    }

    const char* UnexpectedPythonError::what() const throw() {
        return "UnexpectedPythonError";
    }
    
    const char* PythonException::what() const throw() {
        return "PythonException";
    }

    const char* PythonArithmeticError::what() const throw() {
        return "PythonArithmeticError";
    }

    const char* PythonFloatingPointError::what() const throw() {
        return "PythonFloatingPointError";
    }

    const char* PythonOverflowError::what() const throw() {
        return "PythonOverflowError";
    }

    const char* PythonZeroDivisionError::what() const throw() {
        return "PythonZeroDivisionError";
    }

    const char* PythonAssertionError::what() const throw() {
        return "PythonAssertionError";
    }

    const char* PythonAttributeError::what() const throw() {
        return "PythonAttributeError";
    }

    const char* PythonBufferError::what() const throw() {
        return "PythonBufferError";
    }

    const char* PythonEnvironmentError::what() const throw() {
        return "PythonEnvironmentError";
    }

    const char* PythonIOError::what() const throw() {
        return "PythonIOError";
    }

    const char* PythonOSError::what() const throw() {
        return "PythonOSError";
    }

    const char* PythonEOFError::what() const throw() {
        return "PythonEOFError";
    }

    const char* PythonImportError::what() const throw() {
        return "PythonImportError";
    }

    const char* PythonLookupError::what() const throw() {
        return "PythonLookupError";
    }

    const char* PythonIndexError::what() const throw() {
        return "PythonIndexError";
    }

    const char* PythonKeyError::what() const throw() {
        return "PythonKeyError";
    }

    const char* PythonMemoryError::what() const throw() {
        return "PythonMemoryError";
    }

    const char* PythonNameError::what() const throw() {
        return "PythonNameError";
    }

    const char* PythonUnboundLocalError::what() const throw() {
        return "PythonUnboundLocalError";
    }

    const char* PythonReferenceError::what() const throw() {
        return "PythonReferenceError";
    }

    const char* PythonRuntimeError::what() const throw() {
        return "PythonRuntimeError";
    }

    const char* PythonNotImplementedError::what() const throw() {
        return "PythonNotImplementedError";
    }

    const char* PythonSyntaxError::what() const throw() {
        return "PythonSyntaxError";
    }

    const char* PythonIndentationError::what() const throw() {
        return "PythonIndentationError";
    }

    const char* PythonSystemError::what() const throw() {
        return "PythonSystemError";
    }

    const char* PythonTypeError::what() const throw() {
        return "PythonTypeError";
    }

    const char* PythonValueError::what() const throw() {
        return "PythonValueError";
    }

    const char* PythonUnicodeError::what() const throw() {
        return "PythonUnicodeError";
    }

    const char* PythonWarning::what() const throw() {
        return "PythonWarning";
    }
}
