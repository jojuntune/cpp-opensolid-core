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
        static std::size_t hash(int argument);
        static bool equal(int first_argument, int second_argument);
    };
    
    template <>
    struct Traits<double>
    {
        typedef Interval Bounds;
        
        static Interval bounds(double argument);
        static std::size_t hash(double argument);
        static bool equal(double first_argument, double second_argument);
    };
    
    template <class Type, class AllocatorType>
    struct Traits<std::vector<Type, AllocatorType>>
    {
        typedef typename Traits<Type>::Bounds Bounds;
        
        static Bounds bounds(const std::vector<Type, AllocatorType>& argument);

        static std::size_t hash(const std::vector<Type, AllocatorType>& argument);

        static bool equal(
            const std::vector<Type, AllocatorType>& first_argument,
            const std::vector<Type, AllocatorType>& second_argument
        );
    };
}

////////// Implementation //////////

namespace OpenSolid
{   
    inline std::size_t Traits<int>::hash(int argument) {return boost::hash_value(argument);}

    inline bool Traits<int>::equal(int first_argument, int second_argument) {
        return first_argument == second_argument;
    }
    
    inline std::size_t Traits<double>::hash(double argument) {return boost::hash_value(argument);}

    inline bool Traits<double>::equal(double first_argument, double second_argument) {
        return first_argument == second_argument;
    }
    
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
    std::size_t Traits<std::vector<Type, AllocatorType>>::hash(
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

    template <class Type, class AllocatorType>
    bool Traits<std::vector<Type, AllocatorType>>::equal(
        const std::vector<Type, AllocatorType>& first_argument,
        const std::vector<Type, AllocatorType>& second_argument
    ) {return first_argument == second_argument;}
}

#endif
