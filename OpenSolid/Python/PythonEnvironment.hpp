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
    inline Type PythonEnvironment::get(const std::string& expression) {
        boost::python::object python_object = eval(expression);
        boost::python::extract<Type> extracted(python_object);
        if (!extracted.check()) {throw ConversionFromPythonError(python_object, __repr__<Type>());}
        return extracted;
    }
}

#endif
