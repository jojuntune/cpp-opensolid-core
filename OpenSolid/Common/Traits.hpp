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

#ifndef OPENSOLID__TRAITS_HPP
#define OPENSOLID__TRAITS_HPP

#include <boost/functional/hash.hpp>

namespace OpenSolid
{
    template <class Type>
    struct Traits;
    
    class Interval;
    
    template <>
    struct Traits<int>
    {
        typedef Interval Bounds;
        
        static Interval bounds(int argument);
    };
    
    template <>
    struct Traits<double>
    {
        typedef Interval Bounds;
        
        static Interval bounds(double argument);
    };
    
    template <class Type>
    std::size_t hash_value(const Type& argument);
}

////////// Implementation //////////

#include <OpenSolid/Interval/Interval.hpp>

namespace OpenSolid
{    
    template <class Type>
    std::size_t hash_value(const Type& argument) {return Traits<Type>::hash(argument);}
}

#endif
