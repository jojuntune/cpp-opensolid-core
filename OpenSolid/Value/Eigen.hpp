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

#ifndef OPENSOLID__EIGEN_HPP
#define OPENSOLID__EIGEN_HPP

#define EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS
#define EIGEN_FAST_MATH 0

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

#include <OpenSolid/Value/declarations.hpp>

namespace Eigen
{   
    namespace internal
    {
        template <class ScalarType, bool is_integer_>
        struct significant_decimals_default_impl;
        
        template <class ScalarType>
        struct is_arithmetic;

        template <class Type>
        struct traits;
        
        template <>
        struct significant_decimals_default_impl<OpenSolid::Double, false>
        {
            static inline int run();
        };
        
        template <>
        struct is_arithmetic<OpenSolid::Double>
        {
            static const bool value = true;
        };

        template <>
        struct significant_decimals_default_impl<OpenSolid::Interval, false>
        {
            static inline int run();
        };
        
        template <>
        struct is_arithmetic<OpenSolid::Interval>
        {
            static const bool value = true;
        };
    }
    
    template <class Type>
    struct NumTraits;
    
    template <>
    struct NumTraits<OpenSolid::Double>
    {
        typedef OpenSolid::Double Real;
        typedef OpenSolid::Double NonInteger;
        typedef OpenSolid::Double Nested;
        
        static const int IsComplex = 0;
        static const int IsInteger = 0;
        static const int ReadCost = 1;
        static const int AddCost = 1;
        static const int MulCost = 1;
        static const int IsSigned = 1;
        static const int RequireInitialization = 0;
        
        static OpenSolid::Double epsilon();
        static OpenSolid::Double dummy_precision();
        static OpenSolid::Double lowest();
        static OpenSolid::Double highest();
    };
    
    template <>
    struct NumTraits<OpenSolid::Interval>
    {
        typedef OpenSolid::Interval Real;
        typedef OpenSolid::Interval NonInteger;
        typedef OpenSolid::Interval Nested;
        
        static const int IsComplex = 0;
        static const int IsInteger = 0;
        static const int ReadCost = 2;
        static const int AddCost = 2;
        static const int MulCost = 10;
        static const int IsSigned = 1;
        static const int RequireInitialization = 0;
        
        static OpenSolid::Interval epsilon();
        static OpenSolid::Interval dummy_precision();
        static OpenSolid::Interval lowest();
        static OpenSolid::Interval highest();  
    };
}

////////// Implementation //////////

namespace Eigen
{
    namespace internal
    {
        inline int significant_decimals_default_impl<OpenSolid::Double, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
        
        inline int significant_decimals_default_impl<OpenSolid::Interval, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
    }
}

#endif
