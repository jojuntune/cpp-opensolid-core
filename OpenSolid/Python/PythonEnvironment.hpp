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

#include <OpenSolid/config.hpp>

#include <string>
#include <exception>

#include <boost/python/converter/registry.hpp>

#include <OpenSolid/Python/PythonModule.hpp>
#include <OpenSolid/Python/repr.hpp>
#include <OpenSolid/Common/Error.hpp>

namespace OpenSolid
{
    class PythonEnvironment
    {
    private:
        boost::python::object _environment;
        boost::python::object _environment_dict;

        OPENSOLID_PYTHON_EXPORT boost::python::object eval(const std::string& code);
    public:
        OPENSOLID_PYTHON_EXPORT PythonEnvironment();

        OPENSOLID_PYTHON_EXPORT boost::python::object& environment();

        OPENSOLID_PYTHON_EXPORT PythonEnvironment& run(const std::string& argument);
        OPENSOLID_PYTHON_EXPORT PythonEnvironment& runFile(const std::string& filename);

        template <class Type>
        PythonEnvironment& set(const std::string& name, const Type& argument);

        template <class Type>
        Type get(const std::string& code);
    };
}

////////// Errors //////////

namespace OpenSolid
{
    class ConversionFromPythonError : public std::exception
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

    class ConversionToPythonError : public std::exception
    {
    private:
        std::string _type;
    public:
        OPENSOLID_PYTHON_EXPORT ConversionToPythonError(const std::string& type);
        
        OPENSOLID_PYTHON_EXPORT const char* what() const override;
        OPENSOLID_PYTHON_EXPORT std::string type() const;
    };

    class UnknownPythonError
    {
    };

    class PythonException : virtual public std::exception
    {
    private:
        std::string _traceback;
    public:
        OPENSOLID_PYTHON_EXPORT PythonException(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT std::string traceback() const;
    };

    class PythonArithmeticError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonArithmeticError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonFloatingPointError : public PythonArithmeticError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonFloatingPointError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonOverflowError : public PythonArithmeticError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonOverflowError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonZeroDivisionError : public PythonArithmeticError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonZeroDivisionError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonAssertionError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonAssertionError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonAttributeError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonAttributeError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonBufferError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonBufferError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonEnvironmentError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonEnvironmentError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonIOError : public PythonEnvironmentError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonIOError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonOSError : public PythonEnvironmentError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonOSError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonEOFError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonEOFError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonImportError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonImportError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonLookupError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonLookupError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonIndexError : public PythonLookupError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonIndexError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonKeyError : public PythonLookupError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonKeyError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonMemoryError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonMemoryError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonNameError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonNameError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonUnboundLocalError : public PythonNameError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonUnboundLocalError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonReferenceError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonReferenceError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonRuntimeError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonRuntimeError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonNotImplementedError : public PythonRuntimeError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonNotImplementedError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonSyntaxError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonSyntaxError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonIndentationError : public PythonSyntaxError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonIndentationError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonSystemError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonSystemError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonTypeError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonTypeError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonValueError : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonValueError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonUnicodeError : public PythonValueError
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonUnicodeError(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    class PythonWarning : public PythonException
    {
    public:
        OPENSOLID_PYTHON_EXPORT PythonWarning(const std::string& traceback);

        OPENSOLID_PYTHON_EXPORT const char* what() const;
    };

    template <class ErrorType>
    class ErrorFromPython : public ErrorType, public PythonException
    {
    public:
        ErrorFromPython(const ErrorType& error, const std::string& traceback);

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
            throw ConversionToPythonError(__repr__<Type>());
        }
        return *this;
    }
    
    template <class Type>
    Type PythonEnvironment::get(const std::string& expression) {
        boost::python::object python_object = eval(expression);
        boost::python::extract<Type> extracted(python_object);
        if (!extracted.check()) {throw ConversionFromPythonError(python_object, __repr__<Type>());}
        return extracted;
    }

    template <class ErrorType>
    ErrorWithTraceback<ErrorType>::ErrorWithTraceback(
        const ErrorType& error,
        const std::string& traceback
    ) : ErrorType(error), _traceback(traceback) {}

    template <class ErrorType>
    std::string ErrorWithTraceback<ErrorType>::traceback() const {return _traceback;}
}

#endif
