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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Python/PythonExtension.hpp>
#include <OpenSolid/Python/repr.hpp>

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
        int _lineNumber;
        std::string _functionName;
        std::string _text;
    public:
        OPENSOLID_PYTHON_EXPORT
        PythonStackFrame();

        OPENSOLID_PYTHON_EXPORT
        PythonStackFrame(
            const std::string& filename,
            int lineNumber,
            const std::string& functionName,
            const std::string& text
        );

        OPENSOLID_PYTHON_EXPORT
        std::string
        filename() const;
        
        OPENSOLID_PYTHON_EXPORT
        int
        lineNumber() const;

        OPENSOLID_PYTHON_EXPORT
        std::string
        functionName() const;

        OPENSOLID_PYTHON_EXPORT
        std::string
        text() const;
    };

    OPENSOLID_PYTHON_EXPORT
    std::ostream&
    operator<<(std::ostream& stream, const PythonStackFrame& stackFrame);

    class PythonEnvironment
    {
    private:
        boost::python::object _environment;
        boost::python::object _environmentDict;
        boost::python::object _printException;
        boost::python::object _stringIo;
        boost::python::object _extractTb;
        boost::python::object _errorType;
        boost::python::object _errorValue;
        boost::python::object _traceback;
        
        OPENSOLID_PYTHON_EXPORT
        void throwError();
        
        OPENSOLID_PYTHON_EXPORT
        boost::python::object
        eval(const std::string& expression);
    public:
        OPENSOLID_PYTHON_EXPORT
        PythonEnvironment();

        OPENSOLID_PYTHON_EXPORT
        boost::python::object
        environment();

        OPENSOLID_PYTHON_EXPORT
        PythonEnvironment&
        run(const std::string& argument);

        OPENSOLID_PYTHON_EXPORT
        PythonEnvironment&
        runFile(const std::string& filename);

        template <class Type>
        PythonEnvironment&
        set(const std::string& name, const Type& argument);

        template <class Type>
        Type
        get(const std::string& expression);

        OPENSOLID_PYTHON_EXPORT
        std::string
        formattedTraceback() const;

        OPENSOLID_PYTHON_EXPORT
        std::vector<PythonStackFrame>
        stackTrace() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    PythonEnvironment&
    PythonEnvironment::set(const std::string& name, const Type& argument) {
        try {
            _environmentDict[name] = argument;
        } catch (const boost::python::error_already_set& error) {
            PyErr_Clear();
            throw Error(new PlaceholderError());
        }
        return *this;
    }
    
    template <class Type>
    Type
    PythonEnvironment::get(const std::string& expression) {
        boost::python::object pythonObject = eval(expression);
        boost::python::extract<Type> extracted(pythonObject);
        if (!extracted.check()) {
            throw Error(new PlaceholderError());
        }
        return extracted;
    }
}
