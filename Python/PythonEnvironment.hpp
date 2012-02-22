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

#ifndef OPENSOLID__PYTHON__PYTHONENVIRONMENT_HPP
#define OPENSOLID__PYTHON__PYTHONENVIRONMENT_HPP

#include <OpenSolid/Python/config.hpp>

#include <string>
#include <exception>
#include <vector>

#include <boost/python/converter/registry.hpp>

#include <OpenSolid/Core/Common/Error.hpp>
#include <OpenSolid/Core/Common/TypeName.hpp>
#include <OpenSolid/Python/PythonModule.hpp>
#include <OpenSolid/Python/repr.hpp>

namespace OpenSolid
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

namespace OpenSolid
{
    class ConversionFromPythonError : public Error
    {
    private:
        boost::python::object _python_object;
        std::string _expected_type;
    public:
        OPENSOLID_PYTHON_EXPORT ConversionFromPythonError(
            const boost::python::object& python_object,
            const std::string& expected_type
        );

        OPENSOLID_PYTHON_EXPORT const char* what() const override;
        OPENSOLID_PYTHON_EXPORT boost::python::object pythonObject() const;
        OPENSOLID_PYTHON_EXPORT std::string expectedType() const;
    };

    class ConversionToPythonError : public Error
    {
    private:
        std::string _type;
    public:
        OPENSOLID_PYTHON_EXPORT ConversionToPythonError(const std::string& type);
        
        OPENSOLID_PYTHON_EXPORT const char* what() const override;
        OPENSOLID_PYTHON_EXPORT std::string type() const;
    };

    class UnexpectedPythonError : public Error
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonException : public Error
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonArithmeticError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonFloatingPointError : public PythonArithmeticError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonOverflowError : public PythonArithmeticError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonZeroDivisionError : public PythonArithmeticError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonAssertionError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonAttributeError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonBufferError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonEnvironmentError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonIOError : public PythonEnvironmentError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonOSError : public PythonEnvironmentError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonEOFError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonImportError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonLookupError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonIndexError : public PythonLookupError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonKeyError : public PythonLookupError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonMemoryError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonNameError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonUnboundLocalError : public PythonNameError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonReferenceError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonRuntimeError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonNotImplementedError : public PythonRuntimeError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonSyntaxError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonIndentationError : public PythonSyntaxError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonSystemError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonTypeError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonValueError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonUnicodeError : public PythonValueError
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonWarning : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class Type>
    PythonEnvironment& PythonEnvironment::set(const std::string& name, const Type& argument) {
        try {
            _environment_dict[name] = argument;
        } catch (const boost::python::error_already_set& error) {
            PyErr_Clear();
            throw ConversionToPythonError(TypeName<Type>()());
        }
        return *this;
    }
    
    template <class Type>
    Type PythonEnvironment::get(const std::string& expression) {
        boost::python::object python_object = eval(expression);
        boost::python::extract<Type> extracted(python_object);
        if (!extracted.check()) {
            throw ConversionFromPythonError(python_object, TypeName<Type>()());
        }
        return extracted;
    }
}

#endif
