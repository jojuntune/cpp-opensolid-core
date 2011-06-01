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

#ifndef OPENSOLID__SET__TRAITS_HPP
#define OPENSOLID__SET__TRAITS_HPP

#include <OpenSolid/Common/Traits.hpp>

namespace OpenSolid
{
    template <class Type, class BoundsFunctionType>
    class Set;
    
    template <class Type, class BoundsFunctionType>
    struct Traits<Set<Type, BoundsFunctionType>>
    {
        typedef typename BoundsFunctionType::Bounds Bounds;
        
        static const Bounds& bounds(const Set<Type, BoundsFunctionType>& argument);
        static std::size_t hash(const Set<Type, BoundsFunctionType>& argument);
    };
}

#endif
