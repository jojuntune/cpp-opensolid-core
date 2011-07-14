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

#include <functional>
#include <vector>

namespace OpenSolid
{
    template <class Type>
    class Bounds
    {
        auto operator()(const Type& argument) const -> decltype(argument.bounds());
    };

    template <class Type, class AllocatorType>
    class Bounds<std::vector<Type, AllocatorType>>
    {
        typename std::result_of<Bounds<Type>(Type)>::type operator()(
            const std::vector<Type, AllocatorType>& argument
        ) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class Type>
    inline auto Bounds<Type>::operator()(const Type& argument) const ->
        decltype(argument.bounds()) {
        return argument.bounds();
    }
    
    template <class Type, class AllocatorType>
    typename std::result_of<Bounds<Type>(Type)>::type
    Bounds<std::vector<Type, AllocatorType>>::operator()(
        const std::vector<Type, AllocatorType>& argument
    ) const {
        typedef std::result_of<Bounds<Type>(Type)>::type BoundsType;
        Bounds<Type> bounds_function;
        if (argument.empty()) {
            return BoundsType::Empty();
        } else {
            BoundsType result = bounds_function(argument.front());
            std::for_each(
                ++argument.begin(),
                argument.end(),
                [&result] (const Type& item) {result = result.hull(bounds_function(item));}
            );
            return result;
        }
    }
}

#endif
