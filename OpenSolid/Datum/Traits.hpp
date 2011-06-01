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

#ifndef OPENSOLID__DATUM__TRAITS_HPP
#define OPENSOLID__DATUM__TRAITS_HPP

#include <OpenSolid/Common/Traits.hpp>

namespace OpenSolid
{
    template <int dimensions_, int axes_>
    class Datum;
    
    template <int dimensions_>
    class Axis;
    
    template <int dimensions_>
    class Plane;
    
    template <int dimensions_>
    class Frame;
    
    template <int dimensions_, int axes_>
    class CoordinateSystem;
    
    template <int dimensions_, int axes_>
    struct Traits<Datum<dimensions_, axes_>>
    {
        static std::size_t hash(const Datum<dimensions_, axes_>& argument);
    };
    
    template <int dimensions_>
    struct Traits<Axis<dimensions_>> : public Traits<Datum<dimensions_, 1>>
    {  
    };
    
    template <int dimensions_>
    struct Traits<Plane<dimensions_>> :
        public Traits<Datum<dimensions_, dimensions_ == Dynamic ? Dynamic : dimensions_ - 1>>
    {  
    };
    
    template <int dimensions_>
    struct Traits<Frame<dimensions_>> : public Traits<Datum<dimensions_, dimensions_>>
    {  
    };
    
    template <int dimensions_, int axes_>
    struct Traits<CoordinateSystem<dimensions_, axes_>> : public Traits<Datum<dimensions_, axes_>>
    {  
    };
}

#endif
