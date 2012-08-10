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

#include <opensolid/config.hpp>
#include <opensolid/core/config.hpp>

#ifdef WIN32
    #ifdef opensolid_python_module_EXPORTS
        #define OPENSOLID_PYTHON_MODULE_EXPORT __declspec(dllexport)
    #else
        #define OPENSOLID_PYTHON_MODULE_EXPORT __declspec(dllimport)
    #endif
    
    #ifdef opensolid_python_EXPORTS
        #define OPENSOLID_PYTHON_EXPORT __declspec(dllexport)
    #else
        #define OPENSOLID_PYTHON_EXPORT __declspec(dllimport)
    #endif
#else
    #define OPENSOLID_PYTHON_MODULE_EXPORT
    #define OPENSOLID_PYTHON_EXPORT
#endif

namespace opensolid { namespace python {} }
