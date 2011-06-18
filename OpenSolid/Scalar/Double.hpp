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
#include <limits>
#include <cmath>

#include <boost/functional/hash.hpp>

#include <OpenSolid/Scalar/ScalarBase.hpp>

namespace OpenSolid
{
    class Interval;
    
    class Double : public ScalarBase<Double>
    {
    private:
        double _value;
    public:
        static Double defaultPrecision();
        
        Double();
        Double(double value);
        
        double& value();
        double value() const;
        operator double() const;
        
        Double lower() const;
        Double upper() const;
        Double median() const;
        Double width() const;
        
        Interval bounds() const;
        std::size_t hashValue() const;
        
        Double squared() const;
        
        Interval hull(Double argument) const;
        Interval hull(Interval argument) const;
        Interval intersection(Double argument) const;
        Interval intersection(Interval argument) const;
        
        bool operator==(Double argument);
        bool operator!=(Double argument);
        bool operator<(Double argument);
        bool operator>(Double argument);
        bool operator<=(Double argument);
        bool operator>=(Double argument);
        
        bool isZero(Double precision = defaultPrecision()) const;
        bool isApprox(Double argument, Double precision = defaultPrecision()) const;
        bool isApprox(Interval argument, Double precision = defaultPrecision()) const;
        bool isEqualTo(Double argument, Double precision = defaultPrecision()) const;
        bool isEqualTo(Interval argument, Double precision = defaultPrecision()) const;
        bool isLessThan(Double argument, Double precision = defaultPrecision()) const;
        bool isLessThan(Interval argument, Double precision = defaultPrecision()) const;
        bool isGreaterThan(Double argument, Double precision = defaultPrecision()) const;
        bool isGreaterThan(Interval argument, Double precision = defaultPrecision()) const;
        bool isLessThanOrEqualTo(Double argument, Double precision = defaultPrecision()) const;
        bool isLessThanOrEqualTo(Interval argument, Double precision = defaultPrecision()) const;
        bool isGreaterThanOrEqualTo(Double argument, Double precision = defaultPrecision()) const;
        bool isGreaterThanOrEqualTo(Interval argument, Double precision = defaultPrecision()) const;
        
        bool overlaps(Double argument, Double precision = defaultPrecision()) const;
        bool overlaps(Interval argument, Double precision = defaultPrecision()) const;
        bool isSubsetOf(Double argument, Double precision = defaultPrecision()) const;
        bool isSubsetOf(Interval argument, Double precision = defaultPrecision()) const;
        bool isProperSubsetOf(Double argument, Double precision = defaultPrecision()) const;
        bool isProperSubsetOf(Interval argument, Double precision = defaultPrecision()) const;
        bool isSupersetOf(Double argument, Double precision = defaultPrecision()) const;
        bool isSupersetOf(Interval argument, Double precision = defaultPrecision()) const;
        bool isProperSupersetOf(Double argument, Double precision = defaultPrecision()) const;
        bool isProperSupersetOf(Interval argument, Double precision = defaultPrecision()) const;
        
        Double& operator+=(Double argument);
        Double& operator-=(Double argument);
        Double& operator*=(Double argument);
        Double& operator/=(Double argument);
        
        friend Double operator-(Double argument);
        friend Double operator+(Double first_argument, Double second_argument);
        friend Double operator-(Double first_argument, Double second_argument);
        friend Double operator*(Double first_argument, Double second_argument);
        friend Double operator/(Double first_argument, Double second_argument);
    
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
        friend Double pow(Double base, Double exponent);
        
        friend std::ostream& operator<<(std::ostream& stream, Double argument);
    };
        
    Double operator-(Double argument);
    Double operator+(Double first_argument, Double second_argument);
    Double operator-(Double first_argument, Double second_argument);
    Double operator*(Double first_argument, Double second_argument);
    Double operator/(Double first_argument, Double second_argument);
    
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

#include "Interval.hpp"

namespace OpenSolid
{
    inline Double Double::defaultPrecision() {return 1e-12;}
    
    inline Double::Double() {}
    
    inline Double::Double(double value) : _value(value) {}

    inline double& Double::value() {return _value;}

    inline double Double::value() const {return _value;}
    
    inline Double::operator double() const {return _value;}

    inline Double Double::lower() const {return *this;}

    inline Double Double::upper() const {return *this;}

    inline Double Double::median() const {return *this;}

    inline Double Double::width() const {return 0.0;}
    
    inline Interval Double::bounds() const {return Interval(*this);}
    
    inline std::size_t Double::hashValue() const {return boost::hash_value(_value);}
    
    inline Double Double::squared() const {return _value * _value;}
    
    inline Interval Double::hull(Double argument) const {
        return *this <= argument ? Interval(*this, argument) : Interval(argument, *this);
    }
    
    inline Interval Double::hull(Interval argument) const {
        if (*this < argument.lower()) {
            return Interval(*this, argument.upper());
        } else if (argument.upper() < *this) {
            return Interval(argument.lower(), *this)
        } else {
            return argument;
        }
    }
    
    inline Interval Double::intersection(Double argument) const {
        return *this == argument ? Interval(*this) : Interval::Empty();
    }
    
    inline Interval Double::intersection(Interval argument) const {
        if (*this >= argument.lower() && *this <= argument.upper()) {
            return Interval(*this);
        } else {
            return Interval::Empty();
        }
    }
    
    inline bool Double::operator==(Double other) {return _value == other._value;}
    
    inline bool Double::operator!=(Double other) {return _value != other._value;}
    
    inline bool Double::operator<(Double other) {return _value < other._value;}
    
    inline bool Double::operator>(Double other) {return _value > other._value;}
    
    inline bool Double::operator<=(Double other) {return _value <= other._value;}
    
    inline bool Double::operator>=(Double other) {return _value >= other._value;}
        
    inline bool Double::isZero(Double precision) const {return std::abs(_value) < precision._value;}
    
    inline bool Double::isApprox(Double argument, Double precision) const {
        return std::abs(_value - argument._value) < precision._value;
    }
    
    inline bool Double::isApprox(Interval argument, Double precision) const {
        return this->isApprox(argument.lower(), precision) &&
            this->isApprox(argument.upper(), precision);
    }
    
    inline bool Double::isEqualTo(Double argument, Double precision) const {
        return this->isApprox(argument, precision);
    }
    
    inline bool Double::isEqualTo(Interval argument, Double precision) const {
        return this->isApprox(argument, precision);
    }
    
    inline bool Double::isLessThan(Double argument, Double precision) const {
        return _value < argument._value - precision._value;
    }
    
    inline bool Double::isLessThan(Interval argument, Double precision) const {
        return this->isLessThan(argument.lower(), precision);
    }
    
    inline bool Double::isGreaterThan(Double argument, Double precision) const {
        return _value > argument._value + precision._value;
    }
    
    inline bool Double::isGreaterThan(Interval argument, Double precision) const {
        return this->isGreaterThan(argument.upper(), precision);
    }

    inline bool Double::isLessThanOrEqualTo(Double argument, Double precision) const {
        return _value < argument._value + precision._value;
    }

    inline bool Double::isLessThanOrEqualTo(Interval argument, Double precision) const {
        return this->isLessThanOrEqualTo(argument.lower(), precision);
    }

    inline bool Double::isGreaterThanOrEqualTo(Double argument, Double precision) const {
        return _value > argument._value - precision._value;
    }

    inline bool Double::isGreaterThanOrEqualTo(Interval argument, Double precision) const {
        return this->isGreaterThanOrEqualTo(argument.upper(), precision);
    }

    inline bool Double::overlaps(Double argument, Double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::overlaps(Interval argument, Double precision) const {
        this->isGreaterThanOrEqualTo(argument.lower(), precision) &&
            this->isLessThanOrEqualTo(argument.upper(), precision);
    }

    inline bool Double::isSubsetOf(Double argument, Double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::isSubsetOf(Interval argument, Double precision) const {
        return this->overlaps(argument, precision);
    }

    inline bool Double::isProperSubsetOf(Double argument, Double precision) const {
        return false;
    }

    inline bool Double::isProperSubsetOf(Interval argument, Double precision) const {
        return this->isGreaterThan(argument.lower(), precision) &&
            this->isLessThan(argument.upper(), precision);
    }

    inline bool Double::isSupersetOf(Double argument, Double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::isSupersetOf(Interval argument, Double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::isProperSupersetOf(Double argument, Double precision) const {
        return false;
    }

    inline bool Double::isProperSupersetOf(Interval argument, Double precision) const {
        return false;
    }

    
    inline Double& Double::operator+=(Double argument) {
        _value += argument._value;
        return *this;
    }
    
    inline Double& Double::operator-=(Double argument) {
        _value -= argument._value;
        return *this;
    }
    
    inline Double& Double::operator*=(Double argument) {
        _value *= argument._value;
        return *this;
    }
    
    inline Double& Double::operator/=(Double argument) {
        _value /= argument._value;
        return *this;
    }
    
    inline Double operator-(Double argument) {return -argument._value;}
    
    inline Double operator+(Double first_argument, Double second_argument) {
        return first_argument._value + second_argument._value;
    }
    
    inline Double operator-(Double first_argument, Double second_argument) {
        return first_argument._value - second_argument._value;
    }
    
    inline Double operator*(Double first_argument, Double second_argument) {
        return first_argument._value * second_argument._value;
    }
    
    inline Double operator/(Double first_argument, Double second_argument) {
        return first_argument._value / second_argument._value;
    }
    
    inline Double min(Double first_argument, Double second_argument) {
        return std::min(first_argument._value, second_argument._value);
    }
    
    inline Double max(Double first_argument, Double second_argument) {
        return std::max(first_argument._value, second_argument._value);
    }
    
    inline Double abs(Double argument) {return std::abs(argument._value);}
    
    inline Double sqrt(Double argument) {return std::sqrt(argument._value);}
    
    inline Double sin(Double argument) {return std::sin(argument._value);}
    
    inline Double cos(Double argument) {return std::cos(argument._value);}
    
    inline Double tan(Double argument) {return std::tan(argument._value);}
    
    inline Double asin(Double argument) {return std::asin(argument._value);}
    
    inline Double acos(Double argument) {return std::acos(argument._value);}
    
    inline Double atan(Double argument) {return std::atan(argument._value);}
    
    inline Double atan2(Double y, Double x) {return std::atan2(y._value, x._value);}
    
    inline Double exp(Double argument) {return std::exp(argument._value);}
    
    inline Double log(Double argument) {return std::log(argument._value);}
    
    inline Double pow(Double base, Double exponent) {
        return std::pow(base._value, exponent._value);
    }

    inline std::ostream& operator<<(std::ostream& stream, Double argument) {
        stream << argument._value;
        return stream;
    }
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
        return std::numeric_limits<double>::epsilon();
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::dummy_precision() {
        return OpenSolid::Double::defaultPrecision();
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::lowest() {
        return std::numeric_limits<double>::min();
    }
    
    inline OpenSolid::Double NumTraits<OpenSolid::Double>::highest() {
        return std::numeric_limits<double>::max();
    }
}

#endif
