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

#include <algorithm>
#include <cmath>

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
