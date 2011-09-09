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

#ifndef OPENSOLID__DOUBLE_HPP
#define OPENSOLID__DOUBLE_HPP

#include <algorithm>
#include <cstdlib>
#include <cmath>

#ifndef M_PI
    #define M_PI 3.1415926535897932384626433832795
#endif

#ifndef DEGREES
    #define DEGREES 0.01745329251994329576923690768489
#endif

#include <OpenSolid/Common/Bounds.hpp>

namespace OpenSolid
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

    class Interval;
    
    template <>
    struct Bounds<int>
    {
        typedef Interval Type;

        Interval operator()(int argument) const;
    };
    
    template <>
    struct Bounds<double>
    {
        typedef Interval Type;

        Interval operator()(double argument) const;
    };
}

////////// Implementation //////////

#include <OpenSolid/Scalar/Interval.hpp>

namespace OpenSolid
{
    inline Interval Bounds<int>::operator()(int argument) const {return argument;}

    inline Interval Bounds<double>::operator()(double argument) const {return argument;}
}

#endif
