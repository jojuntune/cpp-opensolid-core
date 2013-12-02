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
************************************************************************************/

#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

// Create DLL import/export declaration macros for core module
// (unless static core has been selected)
#ifdef _WIN32
    #ifdef OPENSOLID_STATIC_LIBS
        #define OPENSOLID_CORE_EXPORT
    #else
        #ifdef OpenSolidCore_EXPORTS
            #define OPENSOLID_CORE_EXPORT __declspec(dllexport)
        #else
            #define OPENSOLID_CORE_EXPORT __declspec(dllimport)
        #endif
    #endif
#else
    #define OPENSOLID_CORE_EXPORT
#endif

// Create DLL import/export declaration macros for I/O module
#ifdef _WIN32
    #ifdef OPENSOLID_STATIC_LIBS
        #define OPENSOLID_IO_EXPORT
    #else
        #ifdef OpenSolidIO_EXPORTS
            #define OPENSOLID_IO_EXPORT __declspec(dllexport)
        #else
            #define OPENSOLID_IO_EXPORT __declspec(dllimport)
        #endif
    #endif
#else
    #define OPENSOLID_IO_EXPORT
#endif

// Create DLL import/export declaration macros for Python module
#ifdef _WIN32
    #ifdef OpenSolidPython_EXPORTS
        #define OPENSOLID_PYTHON_EXPORT __declspec(dllexport)
    #else
        #define OPENSOLID_PYTHON_EXPORT __declspec(dllimport)
    #endif
#else
    #define OPENSOLID_PYTHON_EXPORT
#endif

// Create DLL import/export declaration macros for Python extension
#ifdef _WIN32
    #ifdef python_extension_EXPORTS
        #define OPENSOLID_PYTHON_EXTENSION_EXPORT __declspec(dllexport)
    #else
        #define OPENSOLID_PYTHON_EXTENSION_EXPORT __declspec(dllimport)
    #endif
#else
    #define OPENSOLID_PYTHON_EXTENSION_EXPORT
#endif

// Explicitly use math functions from C++ standard library
namespace opensolid
{
    using std::min;
    using std::max;
    using std::abs;
    using std::sqrt;
    using std::sin;
    using std::cos;
    using std::tan;
    using std::asin;
    using std::acos;
    using std::atan;
    using std::atan2;
    using std::exp;
    using std::log;
    using std::pow;
}
