/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <boost/python.hpp>

#include <string>
#include <typeinfo>

namespace opensolid
{
    OPENSOLID_PYTHON_EXTENSION_EXPORT
    std::string
    __repr__(bool argument);

    OPENSOLID_PYTHON_EXTENSION_EXPORT
    std::string
    __repr__(int argument);

    OPENSOLID_PYTHON_EXTENSION_EXPORT
    std::string
    __repr__(double argument);

    OPENSOLID_PYTHON_EXTENSION_EXPORT
    std::string
    __repr__(const std::string& argument);

    OPENSOLID_PYTHON_EXTENSION_EXPORT
    std::string
    __repr__(Zero argument);

    OPENSOLID_PYTHON_EXTENSION_EXPORT
    std::string
    __repr__(Interval argument);

    OPENSOLID_PYTHON_EXTENSION_EXPORT
    std::string
    __repr__(const MatrixXd& argument);

    OPENSOLID_PYTHON_EXTENSION_EXPORT
    std::string
    __repr__(const MatrixXI& argument);
}
