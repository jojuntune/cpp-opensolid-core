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

#include <sstream>

#include <boost/python/converter/pytype_function.hpp>

#include <OpenSolid/Datum/Axis.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
{
    object reference(PyObject* pointer) {
        return pointer ? object(handle<>(borrowed(pointer))) : object();
    }
    
    object reference(PyTypeObject* pointer) {return reference((PyObject*) pointer);}

    object __init__() {
        static object result = raw_function(
            [] (const tuple& arguments, const dict& keyword_arguments) -> object {
                object self = arguments[0];
                object native_error = arguments[1];
                self.attr("args") = make_tuple(native_error);
                return object();
            },
            2
        );
        return result;
    }

    object __str__() {
        static object result = raw_function(
            [] (const tuple& arguments, const dict&) -> object {
                object self = arguments[0];
                return str(self.attr("args")[0]);
            },
            1
        );
        return result;
    }

    object __repr__(str class_name) {
         return raw_function(
            [class_name] (const tuple&, const dict&) -> object {
                return class_name + str("()");
            },
            1
        );
    }

    object accessor(object native_accessor) {
        object result = raw_function(
            [native_accessor] (const tuple& arguments, const dict&) -> object {
                object self = arguments[0];
                return native_accessor(object(self.attr("args")[0]));
            },
            1
        );
        result.attr("__doc__") = native_accessor.attr("__doc__");
        return result;
    }

    object pythonErrorClass(object native_error_class, str class_name) {
        dict class_dict;
        class_dict["__module__"] = scope();
        class_dict["__doc__"] = native_error_class.attr("__doc__");
        class_dict["__init__"] = __init__();
        class_dict["__str__"] = __str__();
        class_dict["__repr__"] = __repr__(class_name);
        dict native_error_class_dict(native_error_class.attr("__dict__"));
        list names = native_error_class_dict.keys();
        for (int i = 0; i < len(names); ++i) {
            str name(names[i]);
            if (!name.startswith("__")) {
                class_dict[name] = accessor(native_error_class.attr(name));
            }
        }
        return reference(&PyType_Type)(
            class_name,
            make_tuple(reference(PyExc_Exception)),
            class_dict
        );
    }

    template <class ErrorType>
    void registerException(class_<ErrorType>& native_error_class) {
        str class_name(native_error_class.attr("__name__").slice(1, _));
        object python_error_class = pythonErrorClass(native_error_class, class_name);
        scope().attr(class_name) = python_error_class;
        PyObject* class_pointer = python_error_class.ptr();
        auto translator = [class_pointer, python_error_class] (const ErrorType& error) {
            object error_object = python_error_class(error);
            PyErr_SetObject(class_pointer, error_object.ptr());
        };
        register_exception_translator<ErrorType>(translator);
    }

    void bindError() {
        registerException(
            class_<Axis2dConstructionError>("_Axis2dConstructionError", no_init)
                .def("__str__", &Axis2dConstructionError::what)
                .def("origin", &Axis2dConstructionError::origin)
                .def("direction", &Axis2dConstructionError::direction)
        );
        registerException(
            class_<Axis2dCopyConstructionError>("_Axis2dCopyConstructionError", no_init)
                .def("__str__", &Axis2dCopyConstructionError::what)
                .def("argument", &Axis2dCopyConstructionError::argument)
        );
        registerException(
            class_<Axis3dConstructionError>("_Axis3dConstructionError", no_init)
                .def("__str__", &Axis3dConstructionError::what)
                .def("origin", &Axis3dConstructionError::origin)
                .def("direction", &Axis3dConstructionError::direction)
        );
        registerException(
            class_<Axis3dCopyConstructionError>("_Axis3dCopyConstructionError", no_init)
                .def("__str__", &Axis3dCopyConstructionError::what)
                .def("argument", &Axis3dCopyConstructionError::argument)
        );
    }
}
