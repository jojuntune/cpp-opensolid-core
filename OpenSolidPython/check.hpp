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

#ifndef OPENSOLID__SCRIPTING__CHECK_HPP
#define OPENSOLID__SCRIPTING__CHECK_HPP

#include <OpenSolid/config.hpp>

#include <string>

#include <boost/python.hpp>

#include <OpenSolid/Value/Matrix.hpp>

using namespace boost::python;

namespace opensolid
{
    class Function;
    class Domain;
    class Geometry;
    
    template<class Type>
    std::string typeName();
    
    template<>
    inline std::string typeName<bool>() {return "bool";}
    
    template<>
    inline std::string typeName<int>() {return "int";}
    
    template<>
    inline std::string typeName<double>() {return "double";}
    
    template<>
    inline std::string typeName<std::string>() {return "string";}
    
    template<>
    inline std::string typeName<Interval>() {return "Interval";}
    
    template<>
    inline std::string typeName<MatrixXd>() {return "MatrixXd";}
    
    template<>
    inline std::string typeName<MatrixXI>() {return "MatrixXI";}
    
    template<>
    inline std::string typeName<Function>() {return "Function";}
    
    template<>
    inline std::string typeName<Domain>() {return "Domain";}
    
    template<>
    inline std::string typeName<Geometry>() {return "Geometry";}
    
    inline std::string typeName(object argument) {return argument.ptr()->ob_type->tp_name;}
    
    OPENSOLID_PYTHON_EXPORT void checkCompatiblePythonType(
        bool compatible,
        const std::string& expected_type,
        const std::string& type,
        const std::string& caller
    );
}

#endif
