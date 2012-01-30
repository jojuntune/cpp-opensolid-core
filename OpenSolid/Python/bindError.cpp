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

#include <boost/python/converter/pytype_function.hpp>

#include <OpenSolid/Datum/Axis.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
{
    template <class ErrorType>
    void registerTranslator() {
        register_exception_translator<ErrorType>(
            [] (const ErrorType& error) {
                object error_object(error);
                object error_class(error_object.attr("__class__"));
                PyErr_SetObject(error_class.ptr(), error_object.ptr());
            }
        );
    }

    void bindError() {
        class_<Axis2dConstructionError>("Axis2dConstructionError", no_init)
            .def("__str__", &Axis2dConstructionError::what)
            .def("origin", &Axis2dConstructionError::origin)
            .def("direction", &Axis2dConstructionError::direction);
        registerTranslator<Axis2dConstructionError>();

        class_<Axis2dCopyConstructionError>("Axis2dCopyConstructionError", no_init)
            .def("__str__", &Axis2dCopyConstructionError::what)
            .def("argument", &Axis2dCopyConstructionError::argument);
        registerTranslator<Axis2dCopyConstructionError>();

        class_<Axis3dConstructionError>("Axis3dConstructionError", no_init)
            .def("__str__", &Axis3dConstructionError::what)
            .def("origin", &Axis3dConstructionError::origin)
            .def("direction", &Axis3dConstructionError::direction);
        registerTranslator<Axis3dConstructionError>();

        class_<Axis3dCopyConstructionError>("Axis3dCopyConstructionError", no_init)
            .def("__str__", &Axis3dCopyConstructionError::what)
            .def("argument", &Axis3dCopyConstructionError::argument);
        registerTranslator<Axis3dCopyConstructionError>();
    }
}
