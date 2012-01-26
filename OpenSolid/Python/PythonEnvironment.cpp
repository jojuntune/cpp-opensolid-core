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

#include <OpenSolid/Error/Error.hpp>
#include <OpenSolid/Python/PythonEnvironment.hpp>

using namespace boost::python;

namespace OpenSolid
{   
    object PythonEnvironment::eval(const std::string& code) {
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
            return eval(str(last_line), _environment_dict, _environment_dict);
        } catch (const error_already_set&) {
            Check<25>::PythonError();
        }
    }
    
    extern "C" OPENSOLID_PYTHON_EXPORT void initopensolid();

    PythonEnvironment::PythonEnvironment() {
        if (!Py_IsInitialized()) {Py_Initialize();}
        static bool PythonEnvironment_initialized = false;
        static object global;
        static object hidden;
        if (!PythonEnvironment_initialized) {
            initopensolid();
            global = import("__main__").attr("__dict__");
            hidden = dict(global);
            exec("import opensolid", global, global);
            exec("from opensolid import *", global, global);
            exec("class Environment: pass", hidden, hidden);
            PythonEnvironment_initialized = true;
        }
        _environment_dict = dict(global);
        _environment = eval("Environment()", hidden, hidden);
        _environment.attr("__dict__") = _environment_dict;
    }

    object& PythonEnvironment::environment() {return _environment;}
    
    PythonEnvironment& PythonEnvironment::run(const std::string& argument) {
        try {
            exec(str(argument), _environment_dict, _environment_dict);
        } catch (const error_already_set&) {
            Check<25>::PythonError();
        }
        return *this;
    }
    
    PythonEnvironment& PythonEnvironment::runFile(const std::string& filename) {
        try {
            exec_file(str(filename), _environment_dict, _environment_dict);
        } catch (const error_already_set&) {
            Check<25>::PythonError();
        }
        return *this;
    }
    
    void Check<25>::PythonError() {
        PyObject* type_pointer = nullptr;
        PyObject* value_pointer = nullptr;
        PyObject* traceback_pointer = nullptr;
        PyErr_Fetch(&type_pointer, &value_pointer, &traceback_pointer);
        auto wrap = [] (PyObject* pointer) -> object {
            return pointer ? object(handle<>(borrowed(pointer))) : object();
        };
        object type = wrap(type_pointer);
        object value = wrap(value_pointer);
        object traceback = wrap(traceback_pointer);
        Error result;
        if (PyErr_GivenExceptionMatches(type_pointer, PythonModule::errorClass().ptr())) {
            result = extract<Error>(value.attr("_error"));
        } else {
            result = Error((Check()));
        }
        if (traceback) {
            object traceback_module = import("traceback");
            object format_tb = traceback_module.attr("format_tb");
            object format_exception_only = traceback_module.attr("format_exception_only");
            list strings(format_tb(traceback));
            strings.extend(format_exception_only(type, value));
            result.set("traceback", std::string(extract<std::string>(str("").join(strings))));
        }
        PyErr_Restore(type_pointer, value_pointer, traceback_pointer);
        PyErr_Clear();
        throw result;
    }
}
