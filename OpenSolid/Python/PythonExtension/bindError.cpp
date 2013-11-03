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
*************************************************************************************/

// Disable size_t-to-int warning triggered within Boost.Python source code
#pragma warning(disable: 4267)

#include <OpenSolid/Python/PythonExtension.hpp>

#include <boost/python/converter/pytype_function.hpp>

#include <sstream>

using namespace boost::python;

namespace opensolid
{
    object
    reference(PyObject* pointer) {
        return pointer ? object(handle<>(borrowed(pointer))) : object();
    }

    object
    reference(PyTypeObject* pointer) {
        return reference((PyObject*) pointer);
    }

    // Create a pure-Python Error class inheriting directly from the Python Exception class instead
    // of any Boost.Python class (required to work properly in some situations)
    object
    pythonErrorClass() {
        static object result;
        if (result.is_none()) {
            dict classDict;

            // Set the module of this class to be the opensolid module
            classDict["__module__"] = scope();

            // Allow initialization of an Error object from an OpenSolid Error object (wrapped as
            // _Error below)
            classDict["__init__"] = raw_function(
                [] (const tuple& arguments, const dict&) -> object {
                    object self = arguments[0];
                    object nativeError = arguments[1];

                    // Store _Error object in 'args' tuple (standard Exception behaviour)
                    self.attr("args") = make_tuple(nativeError);
                    return object();
                },
                2
            );

            // Delegate stringification to contained error object
            classDict["__str__"] = raw_function(
                [] (const tuple& arguments, const dict&) -> object {
                    object self = arguments[0];
                    return str(self.attr("args")[0]);
                },
                1
            );

            // Expose error code of contained error object
            classDict["code"] = raw_function(
                [] (const tuple& arguments, const dict&) -> object {
                    object self = arguments[0];

                    // Native error object is the first member of the 'args' tuple
                    object nativeError = self.attr("args")[0];

                    // Call the 'code' member function of the contained error object
                    return nativeError.attr("code")();
                },
                1
            );

            // Use the builtin 'type' object to construct a new type named Error, inheriting from
            // Exception, with the class dictionary constructed above
            result = reference(&PyType_Type)(
                "Error",
                make_tuple(reference(PyExc_Exception)),
                classDict
            );
        }
        return result;
    }

    void
    bindError() {
        // Add native Python Error class to opensolid module
        object errorClass = pythonErrorClass();
        scope().attr("Error") = errorClass;

        // Add wrapped OpenSolid Error class to opensolid module as _Error
        class_<Error>("_Error", no_init)
            .def("code", &Error::code)
            .def("__str__", &Error::what);

        // Translate OpenSolid Error objects into Python by storing them inside native Python
        // Error objects 
        register_exception_translator<Error>(
            [&] (const Error& error) {
                object errorObject = errorClass(error);
                PyErr_SetObject(errorClass.ptr(), errorObject.ptr());
            }
        );
    }
}
