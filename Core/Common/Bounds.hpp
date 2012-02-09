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

#ifndef OPENSOLID__BOUNDS_HPP
#define OPENSOLID__BOUNDS_HPP

#include <type_traits>

namespace OpenSolid
{
    template <class BoundedType>
    struct Bounds
    {
        typedef typename std::remove_const<
            typename std::remove_reference<
                decltype(((const BoundedType*) nullptr)->bounds())
            >::type
        >::type Type;

        auto operator()(const BoundedType& argument) const -> decltype(argument.bounds());
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class BoundedType>
    inline auto Bounds<BoundedType>::operator()(const BoundedType& argument) const ->
        decltype(argument.bounds()) {return argument.bounds();}
}

#endif
