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

#include <algorithm>
#include <cmath>

// Create OPENSOLID_OVERRIDE and OPENSOLID_NULLPTR to act as placeholders for
// override and nullptr keywords respectively until all current compilers
// support them
#ifdef __GNUC__
    #if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7) || __GNUC__ >= 5
        #define OPENSOLID_OVERRIDE override
        #define OPENSOLID_NULLPTR nullptr
    #elif __GNUC__ == 4 && __GNUC_MINOR__ == 6
        #define OPENSOLID_OVERRIDE
        #define OPENSOLID_NULLPTR nullptr
    #elif __GNUC__ == 4 && __GNUC_MINOR__ == 5
        #define OPENSOLID_OVERRIDE
        #define OPENSOLID_NULLPTR 0
    #else
        #error GCC 4.5 or higher required for C++11 support
    #endif
#else
    #define OPENSOLID_OVERRIDE override
    #define OPENSOLID_NULLPTR nullptr
#endif

// Create DLL import/export declaration macros for core module
#ifdef _WIN32
    #ifdef opensolid_core_EXPORTS
        #define OPENSOLID_CORE_EXPORT __declspec(dllexport)
    #else
        #define OPENSOLID_CORE_EXPORT __declspec(dllimport)
    #endif
#else
    #define OPENSOLID_CORE_EXPORT
#endif

// Create DLL import/export declaration macros for I/O module
#ifdef _WIN32
    #ifdef opensolid_io_EXPORTS
        #define OPENSOLID_IO_EXPORT __declspec(dllexport)
    #else
        #define OPENSOLID_IO_EXPORT __declspec(dllimport)
    #endif
#else
    #define OPENSOLID_IO_EXPORT
#endif

// Create DLL import/export declaration macros for python extension module
#ifdef _WIN32
    #ifdef opensolid_python_module_EXPORTS
        #define OPENSOLID_PYTHON_MODULE_EXPORT __declspec(dllexport)
    #else
        #define OPENSOLID_PYTHON_MODULE_EXPORT __declspec(dllimport)
    #endif
#else
    #define OPENSOLID_PYTHON_EXPORT
#endif

// Create DLL import/export declaration macros for python library
#ifdef _WIN32
    #ifdef opensolid_python_EXPORTS
        #define OPENSOLID_PYTHON_EXPORT __declspec(dllexport)
    #else
        #define OPENSOLID_PYTHON_EXPORT __declspec(dllimport)
    #endif
#else
    #define OPENSOLID_PYTHON_EXPORT
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
