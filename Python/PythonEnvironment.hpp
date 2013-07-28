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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include "detail/PythonModule.hpp"
#include "detail/repr.hpp"
#include <OpenSolid/Core/Error.hpp>

#include <boost/python/converter/registry.hpp>

#include <string>
#include <exception>
#include <vector>

namespace opensolid
{
    class PythonStackFrame
    {
    private:
        std::string _filename;
        int _line_number;
        std::string _function_name;
        std::string _text;
    public:
        OPENSOLID_PYTHON_EXPORT PythonStackFrame();

        OPENSOLID_PYTHON_EXPORT PythonStackFrame(
            const std::string& filename,
            int line_number,
            const std::string& function_name,
            const std::string& text
        );

        OPENSOLID_PYTHON_EXPORT std::string filename() const;
        OPENSOLID_PYTHON_EXPORT int lineNumber() const;
        OPENSOLID_PYTHON_EXPORT std::string functionName() const;
        OPENSOLID_PYTHON_EXPORT std::string text() const;
    };

    OPENSOLID_PYTHON_EXPORT std::ostream& operator<<(
        std::ostream& stream,
        const PythonStackFrame& stack_frame
    );

    class PythonEnvironment
    {
    private:
        boost::python::object _environment;
        boost::python::object _environment_dict;
        boost::python::object _print_exception;
        boost::python::object _string_io;
        boost::python::object _extract_tb;
        boost::python::object _error_type;
        boost::python::object _error_value;
        boost::python::object _traceback;
        
        OPENSOLID_PYTHON_EXPORT void throwError();
        OPENSOLID_PYTHON_EXPORT boost::python::object eval(const std::string& code);
    public:
        OPENSOLID_PYTHON_EXPORT PythonEnvironment();

        OPENSOLID_PYTHON_EXPORT boost::python::object environment();

        OPENSOLID_PYTHON_EXPORT PythonEnvironment& run(const std::string& argument);
        OPENSOLID_PYTHON_EXPORT PythonEnvironment& runFile(const std::string& filename);

        template <class Type>
        PythonEnvironment& set(const std::string& name, const Type& argument);

        template <class Type>
        Type get(const std::string& code);

        OPENSOLID_PYTHON_EXPORT std::string formattedTraceback() const;
        OPENSOLID_PYTHON_EXPORT std::vector<PythonStackFrame> stackTrace() const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class ConversionFromPythonError : public Error
    {
    private:
        boost::python::object _python_object;
    public:
        OPENSOLID_PYTHON_EXPORT ConversionFromPythonError(
            const boost::python::object& python_object
        );
        
        OPENSOLID_PYTHON_EXPORT ~ConversionFromPythonError() throw ();

        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
        OPENSOLID_PYTHON_EXPORT boost::python::object pythonObject() const;
    };

    class ConversionToPythonError : public Error
    {
    public:
        OPENSOLID_PYTHON_EXPORT ConversionToPythonError();
        
        OPENSOLID_PYTHON_EXPORT ~ConversionToPythonError() throw ();
        
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class UnexpectedPythonError : public Error
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonException : public Error
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonArithmeticError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonFloatingPointError : public PythonArithmeticError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonOverflowError : public PythonArithmeticError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonZeroDivisionError : public PythonArithmeticError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonAssertionError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonAttributeError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonBufferError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonEnvironmentError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonIOError : public PythonEnvironmentError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonOSError : public PythonEnvironmentError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonEOFError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonImportError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonLookupError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonIndexError : public PythonLookupError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonKeyError : public PythonLookupError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonMemoryError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonNameError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonUnboundLocalError : public PythonNameError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonReferenceError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonRuntimeError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonNotImplementedError : public PythonRuntimeError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonSyntaxError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonIndentationError : public PythonSyntaxError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonSystemError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonTypeError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonValueError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonUnicodeError : public PythonValueError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };

    class PythonWarning : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const throw() override;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    PythonEnvironment& PythonEnvironment::set(const std::string& name, const Type& argument) {
        try {
            _environment_dict[name] = argument;
        } catch (const boost::python::error_already_set& error) {
            PyErr_Clear();
            throw ConversionToPythonError();
        }
        return *this;
    }
    
    template <class Type>
    Type PythonEnvironment::get(const std::string& expression) {
        boost::python::object python_object = eval(expression);
        boost::python::extract<Type> extracted(python_object);
        if (!extracted.check()) {
            throw ConversionFromPythonError(python_object);
        }
        return extracted;
    }
}
