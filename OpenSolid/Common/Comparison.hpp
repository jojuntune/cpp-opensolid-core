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

#ifndef OPENSOLID__COMPARISON_HPP
#define OPENSOLID__COMPARISON_HPP

namespace OpenSolid
{
    namespace Comparison
    {
        double tolerance();
        
        // template <class Type>
        // bool zero(const Type& argument);
        // 
        // template <class FirstType, class SecondType>
        // bool equal(const FirstType& first_argument, const SecondType& second_argument);
        // 
        // template <class FirstType, class SecondType>
        // bool lesser(const FirstType& first_argument, const SecondType& second_argument);
        // 
        // template <class FirstType, class SecondType>
        // bool greater(const FirstType& first_argument, const SecondType& second_argument);
        
        inline bool zero(int argument);
        
        inline bool equal(int first_argument, int second_argument);
        
        inline bool lesser(int first_argument, int second_argument);
        
        inline bool greater(int first_argument, int second_argument);
        
        inline bool zero(double argument);
        
        inline bool equal(double first_argument, double second_argument);
        
        inline bool lesser(double first_argument, double second_argument);
        
        inline bool greater(double first_argument, double second_argument);
    }
}

////////// Implementation //////////

#include "Traits.hpp"

namespace OpenSolid
{
    namespace Comparison
    {
        inline double tolerance() {return 1e-12;}

        inline bool zero(int argument) {return argument == 0;}
        
        inline bool equal(int first_argument, int second_argument) {
            return first_argument == second_argument;
        }
        
        inline bool lesser(int first_argument, int second_argument) {
            return first_argument < second_argument;
        }
        
        inline bool greater(int first_argument, int second_argument){
            return first_argument > second_argument;
        }

        inline bool zero(double argument) {return abs(argument) < tolerance();}
        
        inline bool equal(double first_argument, double second_argument) {
            return abs(first_argument - second_argument) < tolerance();
        }
        
        inline bool lesser(double first_argument, double second_argument) {
            return second_argument - first_argument > tolerance();
        }
        
        inline bool greater(double first_argument, double second_argument){
            return first_argument - second_argument > tolerance();
        }
    }
}

#endif
