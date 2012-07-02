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

#pragma once

#include <OpenSolid/Python/config.hpp>

#include <string>
#include <typeinfo>

#ifdef override
    #define REDEFINE_OVERRIDE
    #undef override
#endif

#include <boost/python.hpp>

#ifdef REDEFINE_OVERRIDE
    #define override
    #undef REDEFINE_OVERRIDE
#endif

#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>

namespace opensolid
{
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(bool argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(int argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(double argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(const std::string& argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(const Interval& argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(const MatrixXd& argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(const MatrixXI& argument);
    OPENSOLID_PYTHON_MODULE_EXPORT std::string __repr__(const boost::python::object& argument);
}
