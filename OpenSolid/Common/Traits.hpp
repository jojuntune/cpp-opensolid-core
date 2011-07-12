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

#include <vector>
#include <algorithm>
#include <numeric>

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
        static std::size_t hashValue(int argument);
    };
    
    template <>
    struct Traits<double>
    {
        typedef Interval Bounds;
        
        static Interval bounds(double argument);
        static std::size_t hashValue(double argument);
    };
    
    template <class Type, class AllocatorType>
    struct Traits<std::vector<Type, AllocatorType>>
    {
        typedef typename Traits<Type>::Bounds Bounds;
        
        static Bounds bounds(const std::vector<Type, AllocatorType>& argument);
        static std::size_t hashValue(const std::vector<Type, AllocatorType>& argument);
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class Type>
    inline typename Type::Bounds Traits<Type>::bounds(const Type& argument) {
        return argument.bounds();
    }
    
    template <class Type>
    inline std::size_t Traits<Type>::hashValue(const Type& argument) {
        return argument.hashValue();
    }
    
    inline std::size_t Traits<int>::hashValue(int argument) {return boost::hash_value(argument);}
    
    inline std::size_t Traits<double>::hashValue(double argument) {return boost::hash_value(argument);}
    
    template <class Type, class AllocatorType>
    struct Traits<std::vector<Type, AllocatorType>>
    
    typedef typename Traits<Type>::Bounds Bounds;
    
    template <class Type, class AllocatorType>
    typename Traits<Type>::Bounds Traits<std::vector<Type, AllocatorType>>::bounds(
        const std::vector<Type, AllocatorType>& argument
    ) {
        return std::accumulate(
            argument.begin(),
            argument.end(),
            Bounds(Bounds::Empty()),
            [] (const Bounds& result, const Type& object) {
                return result.hull(Traits<Type>::bounds(object);
            }
        );
    }
    
    template <class Type, class AllocatorType>
    std::size_t Traits<std::vector<Type, AllocatorType>>::hashValue(
        const std::vector<Type, AllocatorType>& argument
    ) {
        std::size_t result = 0;
        std::for_each(
            argument.begin(),
            argument.end(),
            [&result] (const Type& object) {
                boost::hash_combine(result, Traits<Type>::hashValue(object));
            }
        );
        return result;
    }
}

#endif
