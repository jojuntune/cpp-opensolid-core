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

#include <boost/python.hpp>

#include <opensolid/common/Error.hpp>

using namespace boost::python;

namespace opensolid
{
    OPENSOLID_PYTHON_EXPORT PyObject* error_class;
    
    struct ErrorTranslator
    {
        void operator()(const Error& error) const {
            PyErr_SetObject(error_class, object(error).ptr());
        }
    };
    
    void bindError() {
        error_class = class_<Error>("Error", init<const std::string&, const std::string&>())
            .def("expected", &Error::expected)
            .def("caller", &Error::caller)
            .def("get", &Error::get<std::string>)
            .def("set", &Error::set<std::string>, return_value_policy<copy_non_const_reference>())
            .def("has", &Error::has)
            .def(self_ns::str(self))
            .ptr();
        register_exception_translator<Error>(ErrorTranslator());
    }
}
