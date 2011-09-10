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
#include <utility>
#include <list>
#include <vector>
#include <type_traits>
#include <iterator>

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

    template <class BoundedType>
    struct Bounds<std::pair<BoundedType, BoundedType>>
    {
        typedef typename Bounds<BoundedType>::Type Type;

        typename Bounds<BoundedType>::Type operator()(
            const std::pair<BoundedType, BoundedType>& argument
        ) const;
    };

    template <class BoundedType, class AllocatorType>
    struct Bounds<std::list<BoundedType, AllocatorType>>
    {
        typedef typename Bounds<BoundedType>::Type Type;

        typename Bounds<BoundedType>::Type operator()(
            const std::list<BoundedType, AllocatorType>& argument
        ) const;
    };

    template <class BoundedType, class AllocatorType>
    struct Bounds<std::vector<BoundedType, AllocatorType>>
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
        decltype(argument.bounds()) {return argument.bounds();}

    template <class BoundedType>
    inline typename Bounds<BoundedType>::Type
    Bounds<std::pair<BoundedType, BoundedType>>::operator()(
        const std::pair<BoundedType, BoundedType>& argument
    ) const {
        Bounds<BoundedType> bounds_function;
        typename Bounds<BoundedType>::Type result = bounds_function(argument.first);
        result = result.hull(bounds_function(argument.second));
        return result;
    }

    namespace
    {
        template <class IteratorType>
        inline typename Bounds<typename IteratorType::value_type>::Type rangeBounds(
            IteratorType begin,
            IteratorType end
        ) {
            typedef typename std::iterator_traits<IteratorType>::value_type ValueType;
            typedef typename Bounds<ValueType>::Type BoundsType;
            if (begin == end) {
                return BoundsType();
            } else {
                Bounds<ValueType> bounds_function;
                BoundsType result = bounds_function(*begin);
                while (++begin != end) {
                    result = result.hull(bounds_function(*begin));
                }
                return result;
            }
        }
    }
    
    template <class BoundedType, class AllocatorType>
    inline typename Bounds<BoundedType>::Type
    Bounds<std::list<BoundedType, AllocatorType>>::operator()(
        const std::list<BoundedType, AllocatorType>& argument
    ) const {return rangeBounds(argument.begin(), argument.end());}
    
    template <class BoundedType, class AllocatorType>
    inline typename Bounds<BoundedType>::Type
    Bounds<std::vector<BoundedType, AllocatorType>>::operator()(
        const std::vector<BoundedType, AllocatorType>& argument
    ) const {return rangeBounds(argument.begin(), argument.end());}
}

#endif
