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

#include <OpenSolid/Core/config.hpp>

#include <cmath>
#include <string>

#include <OpenSolid/Core/Common/Bounds.hpp>
#include <OpenSolid/Core/Common/Hash.hpp>

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
    struct Bounds<double>
    {
        typedef Interval Type;

        Interval operator()(double argument) const;
    };

    template <>
    struct Hash<double>
    {
        std::size_t operator()(double argument) const;
    };
}

////////// Implementation //////////

#include <functional>

namespace OpenSolid
{
    inline std::size_t Hash<double>::operator()(double argument) const {
        return std::hash<double>()(argument);
    }
}

#endif
