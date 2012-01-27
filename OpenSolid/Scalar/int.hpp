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

#ifndef OPENSOLID__INT_HPP
#define OPENSOLID__INT_HPP

#include <OpenSolid/config.hpp>

#include <string>

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Common/Hash.hpp>

namespace OpenSolid
{
    class Interval;
    
    template <>
    struct Bounds<int>
    {
        typedef Interval Type;

        Interval operator()(int argument) const;
    };

    template <>
    struct Hash<int>
    {
        std::size_t operator()(int argument) const;
    };
}

////////// Implementation //////////

#include <functional>

namespace OpenSolid
{
    inline std::size_t Hash<int>::operator()(int argument) const {
        return std::hash<int>()(argument);
    }
}

#endif
