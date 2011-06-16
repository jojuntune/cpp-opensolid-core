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

#include <iostream>

#include "ScalarBase.hpp"

namespace OpenSolid
{
    class Interval;
    
    class Double : public ScalarBase<Double>
    {
    private:
        double _value;
    public:
        static Double defaultPrecision() const;
        
        Double();
        Double(double value);
        
        operator double() const;
        
        bool operator==(Double other);
        bool operator!=(Double other);
        bool operator<(Double other);
        bool operator>(Double other);
        bool operator<=(Double other);
        bool operator>=(Double other);
        
        bool isZero(Double precision = defaultPrecision()) const;
        bool isEqual(Double other, Double precision = defaultPrecision()) const;
        bool isEqual(Interval other, Double precision = defaultPrecision()) const;
        bool isLessThan(Double other, Double precision = defaultPrecision()) const;
        bool isLessThan(Interval other, Double precision = defaultPrecision()) const;
        bool isGreaterThan(Double other, Double precision = defaultPrecision()) const;
        bool isGreaterThan(Interval other, Double precision = defaultPrecision()) const;
        
        bool overlap(Double value, Double precision = defaultPrecision()) const;
        bool overlap(Interval other, Double precision = defaultPrecision()) const;
        bool contain(Double value, Double precision = defaultPrecision()) const;
        bool contain(Interval other, Double precision = defaultPrecision()) const;
        
        Double& operator+=(Double other);
        Double& operator-=(Double other);
        Double& operator*=(Double other);
        Double& operator/=(Double other);
        
        Double operator-() const;
        Double operator+(Double other) const;
        Double operator-(Double other) const;
        Double operator*(Double other) const;
        Double operator/(Double other) const;
        
        Double squared() const;
        
        Interval hull(Double value) const;
        Interval hull(Interval other) const;
        Interval intersection(Double value) const;
        Interval intersection(Interval other) const;
    
        friend Double min(Double first_argument, Double second_argument);
        friend Double max(Double first_argument, Double second_argument);
        friend Double abs(Double argument);
        friend Double sqrt(Double argument);
        friend Double sin(Double argument);
        friend Double cos(Double argument);
        friend Double tan(Double argument);
        friend Double asin(Double argument);
        friend Double acos(Double argument);
        friend Double atan(Double argument);
        friend Double atan2(Double first_argument, Double second_argument);
        friend Double exp(Double argument);
        friend Double log(Double argument);
        friend Double pow(Double argument);
        
        friend std::ostream& operator<<(std::ostream& stream, Double argument);
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
#include "Interval.hpp"
#include "Traits.hpp"

namespace OpenSolid
{
    inline Double Double::defaultPrecision() {return Eigen::NumTraits<double>::dummy_precision();}
    
    inline Double::Double() {}
    
    inline Double::Double(double value) : _value(value) {}
    
    inline Double::operator double() const {return _value;}
    
    inline bool Double::operator==(Double other) {return _value == other._value;}
    
    inline bool Double::operator!=(Double other) {return _value != other._value;}
    
    inline bool Double::operator<(Double other) {return _value < other._value;}
    
    inline bool Double::operator>(Double other) {return _value > other._value;}
    
    inline bool Double::operator<=(Double other) {return _value <= other._value;}
    
    inline bool Double::operator>=(Double other) {return _value >= other._value;}
        
    inline bool Double::isZero(Double precision) const {return std::abs(_value) < precision._value;}
    
    inline bool Double::isEqual(Double other, Double precision) const {
        return std::abs(_value - other._value) < precision._value;
    }
    
    inline bool Double::isEqual(Interval other, Double precision) const {
        return isEqual(other.lower(), precision) && isEqual(other.upper(), precision);
    }
    
    inline bool Double::isLessThan(Double other, Double precision) const {
        return other._value - _value > precision;
    }
    
    inline bool Double::isLessThan(Interval other, Double precision) const {
        return isLessThan(other.lower(), precision);
    }
    
    inline bool Double::isGreaterThan(Double other, Double precision) const {
        return _value - other._value > precision;
    }
    
    inline bool Double::isGreaterThan(Interval other, Double precision) const {
        return isGreaterThan(other.upper(), precision);
    }
    
    inline bool Double::overlap(Double value, Double precision) const {
        return isEqual(value, precision);
    }
    
    inline bool Double::overlap(Interval other, Double precision) const {
        return isEqual(other, precision);
    }
    
    inline bool Double::contain(Double value, Double precision) const {
        return isEqual(other, precision);
    }
    
    inline bool Double::contain(Interval other, Double precision) const {
        return isEqual(other, precision);
    }
    
    inline Double& Double::operator+=(Double other) {
        _value += other._value;
        return *this;
    }
    
    inline Double& Double::operator-=(Double other) {
        _value -= other._value;
        return *this;
    }
    
    inline Double& Double::operator*=(Double other) {
        _value *= other._value;
        return *this;
    }
    
    inline Double& Double::operator/=(Double other) {
        _value /= other._value;
        return *this;
    }
    
    inline Double Double::operator-() const {return -_value;}
    
    inline Double Double::operator+(Double other) const {return _value + other._value;}
    
    inline Double Double::operator-(Double other) const {return _value - other._value;}
    
    inline Double Double::operator*(Double other) const {return _value * other._value;}
    
    inline Double Double::operator/(Double other) const {return _value / other._value;}
    
    inline Double Double::squared() const {return _value * _value;}
    
    inline Interval Double::hull(Double other) const {
        return *this <= other ? Interval(*this, other) : Interval(other, *this);
    }
    
    inline Interval Double::hull(Interval other) const {
        if (*this < other.lower()) {
            return Interval(*this, other.upper());
        } else if (other.upper() < *this) {
            return Interval(other.lower(), *this)
        } else {
            return other;
        }
    }
    
    inline Interval Double::intersection(Double other) const {
        return *this == other ? Interval(*this) : Interval::Empty();
    }
    
    inline Interval Double::intersection(Interval other) const {
        
    }
    
    inline Double min(Double first_argument, Double second_argument);
    inline Double max(Double first_argument, Double second_argument);
    inline Double abs(Double argument);
    inline Double sqrt(Double argument);
    inline Double sin(Double argument);
    inline Double cos(Double argument);
    inline Double tan(Double argument);
    inline Double asin(Double argument);
    inline Double acos(Double argument);
    inline Double atan(Double argument);
    inline Double atan2(Double first_argument, Double second_argument);
    inline Double exp(Double argument);
    inline Double log(Double argument);
    inline Double pow(Double argument);

    inline std::ostream& operator<<(std::ostream& stream, Double argument);
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
