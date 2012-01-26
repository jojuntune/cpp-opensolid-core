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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Error/Error.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
{
    void bindFunction();
    void bindDatum();
    void bindSimplex();
    void bindMatrixConstructors();
    void bindMatrix();
    void bindComparison();
    void bindInterval();
    void bindDouble();
    void bindError();

    object& _object() {
        static object result;
        return result;
    }

    object& _dictionary() {
        static object result;
        return result;
    }

    object& _errorClass() {
        static object result;
        return result;
    }

    void PythonModule::initialize() {
        _object() = scope();
        _dictionary() = _object().attr("__dict__");
        boost::python::object exceptions = import("exceptions");
        dictionary()["Exception"] = exceptions.attr("Exception");
        exec(
            "class Error(Exception):\n"
            "    def __init__(self):\n"
            "        self._error = None\n"
            "        self._message = None"
            "\n"
            "    def __str__(self): return self._message\n"
            "\n",
            dictionary(),
            dictionary()
        );
        _errorClass() = eval("Error", dictionary(), dictionary());
        boost::python::class_<Error>("_Error", no_init);
        register_exception_translator<Error>(
            [] (const Error& error) {
                boost::python::object error_object = eval("Error()", dictionary(), dictionary());
                error_object.attr("_error") = error;
                error_object.attr("_message") = error.what();
                PyErr_SetObject(errorClass().ptr(), error_object.ptr());
            }
        );
        bindFunction();
        bindDatum();
        bindSimplex();
        bindMatrix();
        bindMatrixConstructors();
        bindComparison();
        bindInterval();
        bindDouble();
    }

    object PythonModule::object() {return _object();}

    object PythonModule::dictionary() {return _dictionary();}
    
    object PythonModule::errorClass() {return _errorClass();}

    BOOST_PYTHON_MODULE(opensolid) {PythonModule::initialize();}
}
