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

#include <OpenSolid/Common/Error.hpp>
#include <OpenSolid/Python/PythonEnvironment.hpp>

using namespace boost::python;

namespace OpenSolid
{
    object pythonErrorBaseClass();

    template <class ErrorType>
    void checkForPythonError(PyObject* error_type, object type, object value, object traceback) {
        if (PyErr_GivenExceptionMatches(type.ptr(), error_type)) {
            throw ErrorType(type, value, traceback);
        }
    }

    template <class ErrorType>
    void checkForOpenSolidError(object type, object value, object traceback) {
        extract<ErrorType> extracted(value);
        if (extracted.check()) {throw extracted();}
    }

    void throwError() {
        PyObject* type_pointer = nullptr;
        PyObject* value_pointer = nullptr;
        PyObject* traceback_pointer = nullptr;
        PyErr_Fetch(&type_pointer, &value_pointer, &traceback_pointer);
        object type;
        object value;
        object traceback;
        if (type_pointer) {type = object(handle<>(type_pointer));}
        if (value_pointer) {value = object(handle<>(value_pointer));}
        if (traceback_pointer) {traceback = object(handle<>(traceback_pointer));}

        std::string traceback;
        if (traceback) {
            object traceback_module = import("traceback");
            object format_tb = traceback_module.attr("format_tb");
            object format_exception_only = traceback_module.attr("format_exception_only");
            list strings(format_tb(traceback));
            strings.extend(format_exception_only(type, value));
            //traceback = extract<std::string>(str("").join(strings));
        }

        if (PyErr_GivenExceptionMatches(type_pointer, pythonErrorBaseClass().ptr())) {

        } else if (PyErr_GivenExceptionMatches(type_pointer, PyExc_Exception)) {
            checkForPythonError<PythonWarning>(PyExc_Warning, type, value, traceback);
            checkForPythonError<PythonUnicodeError>(PyExc_UnicodeError, type, value, traceback);
            checkForPythonError<PythonValueError>(PyExc_ValueError, type, value, traceback);
            checkForPythonError<PythonTypeError>(PyExc_TypeError, type, value, traceback);
            checkForPythonError<PythonSystemError>(PyExc_SystemError, type, value, traceback);
            checkForPythonError<PythonIndentationError>(PyExc_IndentationError, type, value, traceback);
            checkForPythonError<PythonSyntaxError>(PyExc_SyntaxError, type, value, traceback);
            checkForPythonError<PythonNotImplementedError>(PyExc_NotImplementedError, type, value, traceback);
            checkForPythonError<PythonRuntimeError>(PyExc_RuntimeError, type, value, traceback);
            checkForPythonError<PythonReferenceError>(PyExc_ReferenceError, type, value, traceback);
            checkForPythonError<PythonUnboundLocalError>(PyExc_UnboundLocalError, type, value, traceback);
            checkForPythonError<PythonNameError>(PyExc_NameError, type, value, traceback);
            checkForPythonError<PythonMemoryError>(PyExc_MemoryError, type, value, traceback);
            checkForPythonError<PythonKeyError>(PyExc_KeyError, type, value, traceback);
            checkForPythonError<PythonIndexError>(PyExc_IndexError, type, value, traceback);
            checkForPythonError<PythonLookupError>(PyExc_LookupError, type, value, traceback);
            checkForPythonError<PythonImportError>(PyExc_ImportError, type, value, traceback);
            checkForPythonError<PythonEOFError>(PyExc_EOFError, type, value, traceback);
            checkForPythonError<PythonOSError>(PyExc_OSError, type, value, traceback);
            checkForPythonError<PythonIOError>(PyExc_IOError, type, value, traceback);
            checkForPythonError<PythonEnvironmentError>(PyExc_EnvironmentError, type, value, traceback);
            checkForPythonError<PythonBufferError>(PyExc_BufferError, type, value, traceback);
            checkForPythonError<PythonAttributeError>(PyExc_AttributeError, type, value, traceback);
            checkForPythonError<PythonAssertionError>(PyExc_AssertionError, type, value, traceback);
            checkForPythonError<PythonZeroDivisionError>(PyExc_ZeroDivisionError, type, value, traceback);
            checkForPythonError<PythonOverflowError>(PyExc_OverflowError, type, value, traceback);
            checkForPythonError<PythonFloatingPointError>(PyExc_FloatingPointError, type, value, traceback);
            checkForPythonError<PythonArithmeticError>(PyExc_ArithmeticError, type, value, traceback);
            checkForPythonError<PythonException>(PyExc_Exception, type, value, traceback);
            // Unknown Python exception
        } else {
            // Unexpected Python error
        }
    }

    boost::python::object PythonEnvironment::eval(const std::string& code) {
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
        } catch (const boost::python::error_already_set&) {
            throwError();
        }
    }
    
    extern "C" OPENSOLID_PYTHON_EXPORT void initopensolid();

    PythonEnvironment::PythonEnvironment() {
        if (!Py_IsInitialized()) {Py_Initialize();}
        static bool PythonEnvironment_initialized = false;
        static object global;
        static object hidden;
        if (!PythonEnvironment_initialized) {
            initopensolid();
            global = import("__main__").attr("__dict__");
            hidden = dict(global);
            exec("import opensolid", global, global);
            exec("from opensolid import *", global, global);
            exec("class Environment: pass", hidden, hidden);
            PythonEnvironment_initialized = true;
        }
        _environment_dict = dict(global);
        _environment = boost::python::eval("Environment()", hidden, hidden);
        _environment.attr("__dict__") = _environment_dict;
    }

    object& PythonEnvironment::environment() {return _environment;}
    
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

    ConversionFromPythonError::ConversionFromPythonError(
        const boost::python::object& python_object,
        const std::string& expected_type
    ) : _python_object(python_object), _expected_type(expected_type) {}

    const char* ConversionFromPythonError::what() const {return "ConversionFromPythonError";}

    boost::python::object ConversionFromPythonError::pythonObject() const {return _python_object;}

    std::string ConversionFromPythonError::expectedType() const {return _expected_type;}

    ConversionToPythonError::ConversionToPythonError(const std::string& type) : _type(type) {}
        
    const char* ConversionToPythonError::what() const {return "ConversionToPythonError";}
    
    std::string ConversionToPythonError::type() const {return _type;}
}
