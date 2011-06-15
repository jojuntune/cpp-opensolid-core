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

#ifndef OPENSOLID__SCALAR__TRAITS_HPP
#define OPENSOLID__SCALAR__TRAITS_HPP

#include <OpenSolid/Common/Traits.hpp>

namespace OpenSolid
{
    class Double;
    class Interval;
    
    template <>
    struct Traits<int>
    {
        typedef Interval Bounds;
        
        static Interval bounds(int argument);
        static std::size_t hash(int argument);
    };
    
    template <>
    struct Traits<float>
    {
        typedef Interval Bounds;
        
        static Interval bounds(float argument);
        static std::size_t hash(float argument);
    };
    
    template <>
    struct Traits<double>
    {
        typedef Interval Bounds;
        
        static Interval bounds(double argument);
        static std::size_t hash(double argument);
    };
    
    template <>
    struct Traits<Double>
    {
        typedef Interval Bounds;
        
        static Interval bounds(Double argument);
        static std::size_t hash(Double argument);
    };
    
    template <>
    struct Traits<Interval>
    {
        typedef Interval Bounds;
        
        static Interval bounds(Interval argument);
        static std::size_t hash(Interval argument);
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    inline std::size_t Traits<int>::hash(int argument) {return boost::hash_value(argument);}
    
    inline std::size_t Traits<float>::hash(float argument) {return boost::hash_value(argument);}
    
    inline std::size_t Traits<double>::hash(double argument) {return boost::hash_value(argument);}
}

#endif
