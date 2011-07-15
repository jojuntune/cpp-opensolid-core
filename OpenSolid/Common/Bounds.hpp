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
#include <type_traits>

namespace OpenSolid
{
    template <class BoundedType>
    class Bounds
    {
        typedef typename std::remove_const<
            typename std::remove_reference<
                decltype(((const Type*) nullptr)->bounds())
            >::type
        >::type Type;

        auto operator()(const BoundedType& argument) const -> decltype(argument.bounds());
    };

    template <class BoundedType, class AllocatorType>
    class Bounds<std::vector<BoundedType, AllocatorType>>
    {
        typedef typename Bounds<BoundedType>::Type Type;

        typename Bounds<BoundedType>::Type operator()(
            const std::vector<BoundedType, AllocatorType>& argument
        ) const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class BoundedType>
    inline auto Bounds<BoundedType>::operator()(const BoundedType& argument) const ->
        decltype(argument.bounds()) {
        return argument.bounds();
    }
    
    template <class BoundedType, class AllocatorType>
    typename Bounds<BoundedType>::Type Bounds<std::vector<BoundedType, AllocatorType>>::operator()(
        const std::vector<BoundedType, AllocatorType>& argument
    ) const {
        typedef typename Bounds<BoundedType>::Type BoundsType;
        Bounds<Type> bounds_function;
        if (argument.empty()) {
            return BoundsType();
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
