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

#ifndef OPENSOLID__DOUBLE_HPP
#define OPENSOLID__DOUBLE_HPP

#include "ScalarBase.hpp"

namespace OpenSolid
{
    class Double : public ScalarBase<Double>
    {
    private:
        double _value;
    public:
        Double(double value);
        
        Double squared() const;
        
        bool overlap(Double value) const;
        bool overlap(Double value, Double precision) const;
        bool overlap(Interval other) const;
        bool overlap(Interval other, Double precision) const;
        bool contain(Double value) const;
        bool contain(Double value, Double precision) const;
        bool contain(Interval other) const;
        bool contain(Interval other, Double precision) const;
        
        Interval hull(Double value) const;
        Interval hull(Interval other) const;
        Interval intersection(Double value) const;
        Interval intersection(Interval other) const;
        
        Double& operator+=(const Double& other);
        Double& operator-=(const Double& other);
        Double& operator/=(const Double& other);
        Double& operator*=(const Double& other);
    };
    
    Double min(Double first_argument, Double second_argument);
    Double max(Double first_argument, Double second_argument);
    Double abs(Double argument);
    Double sqrt(Double argument);
    Double sin(Double argument);
    Double cos(Double argument);
    Double tan(Double argument);
    Double asin(Double argument);
    Double acos(Double argument);
    Double atan(Double argument);
    Double atan2(Double first_argument, Double second_argument);
    Double exp(Double argument);
    Double log(Double argument);
    Double pow(Double argument);
    
    std::ostream& operator<<(std::ostream& stream, Double argument);
}

namespace Eigen
{   
    namespace internal
    {
        OpenSolid::Double conj(OpenSolid::Double argument);
        OpenSolid::Double real(OpenSolid::Double argument);
        OpenSolid::Double imag(OpenSolid::Double);
        OpenSolid::Double abs2(OpenSolid::Double argument);
        
        template <class ScalarType, bool is_integer_>
        struct significant_decimals_default_impl;
        
        template <>
        struct significant_decimals_default_impl<OpenSolid::Double, false>
        {
            static inline int run();
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
}

////////// Implementation //////////

#include <OpenSolid/Common/Eigen.hpp>
#include "Traits.hpp"

namespace OpenSolid
{
    
}

namespace Eigen
{   
    namespace internal
    {
        inline OpenSolid::Double conj(OpenSolid::Double argument) {return argument;}
        
        inline OpenSolid::Double real(OpenSolid::Double argument) {return argument;}
        
        inline OpenSolid::Double imag(OpenSolid::Double) {return 0.0;}
        
        inline OpenSolid::Double abs2(OpenSolid::Double argument) {return argument.squared();}
        
        inline int significant_decimals_default_impl<OpenSolid::Double, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::epsilon() {
        return OpenSolid::Double(NumTraits<double>::epsilon());
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::dummy_precision() {
        return OpenSolid::Double(NumTraits<double>::dummy_precision());
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::lowest() {
        return OpenSolid::Double(NumTraits<double>::lowest());
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::highest() {
        return OpenSolid::Double(NumTraits<double>::highest());
    }
}

#endif
