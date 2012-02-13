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

#include <OpenSolid/Python/config.hpp>

#include <string>
#include <typeinfo>

#include <boost/python.hpp>

#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>

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
    template <class Type>
    std::string __repr__() {return typeid(Type).name();}

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
    inline std::string __repr__<Vector2d>() {return "Vector2d";}
        
    template <>
    inline std::string __repr__<Vector3d>() {return "Vector3d";}
        
    template <>
    inline std::string __repr__<VectorXd>() {return "VectorXd";}
        
    template <>
    inline std::string __repr__<RowVector2d>() {return "RowVector2d";}
        
    template <>
    inline std::string __repr__<RowVector3d>() {return "RowVector3d";}
        
    template <>
    inline std::string __repr__<RowVectorXd>() {return "RowVectorXd";}
        
    template <>
    inline std::string __repr__<Matrix2d>() {return "Matrix2d";}
        
    template <>
    inline std::string __repr__<Matrix3d>() {return "Matrix3d";}

    template <>
    inline std::string __repr__<MatrixXd>() {return "MatrixXd";}
        
    template <>
    inline std::string __repr__<Vector2I>() {return "Vector2I";}
        
    template <>
    inline std::string __repr__<Vector3I>() {return "Vector3I";}
        
    template <>
    inline std::string __repr__<VectorXI>() {return "VectorXI";}
        
    template <>
    inline std::string __repr__<RowVector2I>() {return "RowVector2I";}
        
    template <>
    inline std::string __repr__<RowVector3I>() {return "RowVector3I";}
        
    template <>
    inline std::string __repr__<RowVectorXI>() {return "RowVectorXI";}
        
    template <>
    inline std::string __repr__<Matrix2I>() {return "Matrix2I";}
        
    template <>
    inline std::string __repr__<Matrix3I>() {return "Matrix3I";}

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
