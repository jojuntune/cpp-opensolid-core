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

#include <OpenSolid/Common/Error.hpp>
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
            "    def __init__(self, expected, caller):\n"
            "        self._expected = expected\n"
            "        self._caller = caller\n"
            "        self._data = {}\n"
            "\n"
            "    def expected(self): return self._expected\n"
            "\n"
            "    def caller(self): return self._caller\n"
            "\n"
            "    def set(self, name, argument):\n"
            "        self._data[name] = argument\n"
            "        return self\n"
            "\n"
            "    def has(self, name): return self._data.has_key(name)\n"
            "\n"
            "    def get(self, name): return self._data[name]\n"
            "\n"
            "    def __repr__(self):\n"
            "        result = 'Error(\\'%s\\', \\'%s\\')' % (self.expected(), self.caller())\n"
            "        for (key, value) in self._data.iteritems():\n"
            "            result += '.set(\\'%s\\', \\'%s\\')' % (key, value)\n"
            "        return result\n"
            "\n"
            "    def __str__(self): return self.__repr__()\n"
            "\n",
            dictionary(),
            dictionary()
        );
        _errorClass() = eval("Error", dictionary(), dictionary());
        register_exception_translator<Error>(
            [] (const Error& error) {
                std::stringstream constructor;
                constructor << "Error(";
                constructor << "'" << error.expected() << "'";
                constructor << ", ";
                constructor << "'" << error.caller() << "'";
                constructor << ")";
                boost::python::object error_object = eval(
                    constructor.str().c_str(),
                    dictionary(),
                    dictionary()
                );
                boost::python::object error_data = error_object.attr("_data");
                for (auto i = error.data().begin(); i != error.data().end(); ++i) {
                    error_data[str(i->first.c_str())] = str(i->second.c_str());
                }
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
