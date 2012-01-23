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

#include <OpenSolid/Python/PythonModule.hpp>
#include <OpenSolid/Python/check.hpp>
#include <OpenSolid/Common/Error.hpp>

namespace OpenSolid
{
    class PythonEnvironment
    {
    private:
        boost::python::object _environment;
        boost::python::object _environment_dict;
        
        OPENSOLID_PYTHON_EXPORT Error error();
        OPENSOLID_PYTHON_EXPORT boost::python::object eval(const std::string& code);
        
        template <class Type>
        static Type cast(boost::python::object argument);
        
        OPENSOLID_PYTHON_EXPORT static boost::python::object main();
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

    template <>
    struct Check<25>
    {
        OPENSOLID_PYTHON_EXPORT static void PythonError();
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class Type>
    inline Type PythonEnvironment::cast(boost::python::object argument) {
        Check<1>::CompatibleType<Type>(argument);
        return boost::python::extract<Type>(argument);
    }

    template <class Type>
    inline PythonEnvironment& PythonEnvironment::set(
        const std::string& name,
        const Type& argument
    ) {
        assert(boost::python::converter::registered_pytype<Type>::get_pytype() != nullptr);
        _environment_dict[name] = argument;
        return *this;
    }
    
    template <class Type>
    inline Type PythonEnvironment::get(const std::string& expression) {
        return cast<Type>(_get(expression));
    }
}

#endif
