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

#ifndef OPENSOLID__SCRIPTING__SCRIPT_HPP
#define OPENSOLID__SCRIPTING__SCRIPT_HPP

#include <OpenSolid/config.hpp>

#include <string>

#include <boost/python.hpp>
#include <boost/python/raw_function.hpp>

#include <OpenSolid/Python/check.hpp>

namespace OpenSolid
{
    class Script
    {
    private:
        boost::python::object _environment;
        
        OPENSOLID_SCRIPT_EXPORT void _throw();
        OPENSOLID_SCRIPT_EXPORT boost::python::object _get(const std::string& argument);
    public:
        OPENSOLID_SCRIPT_EXPORT Script();

        template <class Type>
        Script& set(const std::string& name, const Type& argument);

        OPENSOLID_SCRIPT_EXPORT Script& run(const std::string& argument);

        template <class Type>
        Type get(const std::string& code);
        
        template <class FunctionType>
        Script& def(const char* name, FunctionType function);
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class Type>
    Script& Script::set(const std::string& name, const Type& argument) {
        _environment[name] = argument;
        return *this;
    }
    
    template <class Type>
    Type cast(boost::python::object argument) {
        checkCompatiblePythonType<Type>(argument, __func__);
        return extract<Type>(argument);
    }
    
    template <class Type>
    inline Type Script::get(const std::string& code) {
        boost::python::object result = _get(code);
        return cast<Type>(_get(code));
    }
    
    template <class FunctionType>
    Script& Script::def(const char* name, FunctionType function) {
        _environment[name] = boost::python::raw_function(function);
        return *this;
    }
}

#endif
