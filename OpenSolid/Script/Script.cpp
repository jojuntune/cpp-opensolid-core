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
#include <OpenSolid/Script/Script.hpp>

using namespace boost::python;

namespace OpenSolid
{
    OPENSOLID_PYTHON_EXPORT extern PyObject* error_class_ptr;
    
    inline object wrap(PyObject* pointer) {return object(handle<>(borrowed(pointer)));}
    
    std::string formattedTraceback(object type, object value, object traceback) {
        object traceback_module = import("traceback");
        object format_tb = traceback_module.attr("format_tb");
        object format_exception_only = traceback_module.attr("format_exception_only");
        list strings(format_tb(traceback));
        strings.extend(format_exception_only(type, value));
        return extract<std::string>(str("").join(strings));
    }
    
    Error Script::error() {
        PyObject* type;
        PyObject* value;
        PyObject* traceback;
        PyErr_Fetch(&type, &value, &traceback);
        Error result;
        if (PyErr_GivenExceptionMatches(type, error_class_ptr)) {
            result = extract<Error>(wrap(value));
        } else if (PyErr_GivenExceptionMatches(type, PyExc_SyntaxError)) {
            result = Error("ValidPythonSyntax", __func__);
        } else {
            result = Error("NoPythonExceptions", __func__);
        }
        if (traceback) {
            result.set("traceback", formattedTraceback(wrap(type), wrap(value), wrap(traceback)));
        }
        PyErr_Restore(type, value, traceback);
        PyErr_Clear();
        return result;
    }
    
    object Script::_get(const std::string& argument) {
        std::vector<std::string> lines;
        boost::algorithm::split(
            lines,
            argument,
            boost::algorithm::is_any_of("\r\n"),
            boost::algorithm::token_compress_on
        );
        if (lines.back().empty()) {lines.pop_back();}
        std::string last_line = lines.back();
        lines.pop_back();
        if (!lines.empty()) {run(boost::algorithm::join(lines, "\n"));}
        try {
            return eval(str(last_line), _environment, _environment);
        } catch (const error_already_set&) {
            throw error();
        }
    }
    
    extern "C" OPENSOLID_PYTHON_EXPORT void initopensolid();

    struct Extensions
    {
    };

    Script::Script() {
        static object main;
        if (!Py_IsInitialized()) {
            Py_Initialize();
            initopensolid();
            main = import("__main__");
            scope global(main);
            class_<Extensions>("Extensions");
        }
        _environment = dict(main.attr("__dict__"));
        exec("import opensolid", _environment, _environment);
        exec("from opensolid import *", _environment, _environment);
        exec("extensions = Extensions()", _environment, _environment);
        _extensions = _environment["extensions"];
        _extensions.attr("__dict__") = _environment;
    }
    
    Script& Script::run(const std::string& argument) {
        try {
            exec(str(argument), _environment, _environment);
        } catch (const error_already_set&) {
            throw error();
        }
        return *this;
    }
}
