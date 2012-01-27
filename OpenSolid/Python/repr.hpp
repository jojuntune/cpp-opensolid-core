/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef OPENSOLID__REPR_HPP
#define OPENSOLID__REPR_HPP

#include <OpenSolid/config.hpp>

#include <string>

#include <boost/python.hpp>

#include <OpenSolid/Scalar/Interval.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>

namespace OpenSolid
{
    template <class Type>
    std::string __repr__();

    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(bool argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(int argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(double argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(const std::string& argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(const Interval& argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(const MatrixXd& argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(const MatrixXI& argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(const boost::python::object& argument);
}

////////// Implementation //////////

namespace OpenSolid
{    
    template <>
    inline std::string __repr__<bool>() {return "bool";}

    template <>
    inline std::string __repr__<int>() {return "int";}

    template <>
    inline std::string __repr__<double>() {return "double";}

    template <>
    inline std::string __repr__<std::string>() {return "string";}

    template <>
    inline std::string __repr__<Interval>() {return "Interval";}

    template <>
    inline std::string __repr__<MatrixXd>() {return "MatrixXd";}

    template <>
    inline std::string __repr__<MatrixXI>() {return "MatrixXI";}

    template <>
    inline std::string __repr__<boost::python::object>() {return "object";}

    template <>
    inline std::string __repr__<boost::python::list>() {return "list";}

    template <>
    inline std::string __repr__<boost::python::tuple>() {return "tuple";}

    template <>
    inline std::string __repr__<boost::python::str>() {return "str";}

    template <>
    inline std::string __repr__<boost::python::dict>() {return "dict";}
}

#endif
