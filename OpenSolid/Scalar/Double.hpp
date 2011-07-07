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

#include <OpenSolid/Common/config.hpp>

namespace OpenSolid
{
    class Interval;
    
    class Double
    {
    private:
        double _implementation;
    public:
        typedef Interval Bounds;
        
        Double();
        Double(double argument);
        
        double implementation() const;
        
        Interval bounds() const;
        std::size_t hashValue() const;
        
        Interval hull(Double argument) const;
        
        bool isZero(Double precision = OPENSOLID_PRECISION) const;
        bool isEqualTo(Double argument, Double precision = OPENSOLID_PRECISION) const;
        bool isLessThan(Double argument, Double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThan(Double argument, Double precision = OPENSOLID_PRECISION) const;
        bool isLessThanOrEqualTo(Double argument, Double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThanOrEqualTo(Double argument, Double precision = OPENSOLID_PRECISION) const;
        
        Double& operator+=(Double argument);
        Double& operator-=(Double argument);
        Double& operator*=(Double argument);
        Double& operator/=(Double argument);
    };
    
    bool operator==(double first_argument, Double second_argument);
    bool operator==(Double first_argument, double second_argument);
    bool operator==(Double first_argument, Double second_argument);
    bool operator!=(double first_argument, Double second_argument);
    bool operator!=(Double first_argument, double second_argument);
    bool operator!=(Double first_argument, Double second_argument);
    bool operator<(double first_argument, Double second_argument);
    bool operator<(Double first_argument, double second_argument);
    bool operator<(Double first_argument, Double second_argument);
    bool operator>(double first_argument, Double second_argument);
    bool operator>(Double first_argument, double second_argument);
    bool operator>(Double first_argument, Double second_argument);
    bool operator<=(double first_argument, Double second_argument);
    bool operator<=(Double first_argument, double second_argument);
    bool operator<=(Double first_argument, Double second_argument);
    bool operator>=(double first_argument, Double second_argument);
    bool operator>=(Double first_argument, double second_argument);
    bool operator>=(Double first_argument, Double second_argument);
    
    Double operator-(Double argument);
    Double operator+(double first_argument, Double second_argument);
    Double operator+(Double first_argument, double second_argument);
    Double operator+(Double first_argument, Double second_argument);
    Double operator-(double first_argument, Double second_argument);
    Double operator-(Double first_argument, double second_argument);
    Double operator-(Double first_argument, Double second_argument);
    Double operator*(double first_argument, Double second_argument);
    Double operator*(Double first_argument, double second_argument);
    Double operator*(Double first_argument, Double second_argument);
    Double operator/(double first_argument, Double second_argument);
    Double operator/(Double first_argument, double second_argument);
    Double operator/(Double first_argument, Double second_argument);
    
    using std::min;
    using std::max;
    using std::abs;
    using std::sqrt;
    using std::sin;
    using std::cos;
    using std::tan;
    using std::asin;
    using std::acos;
    using std::atan;
    using std::atan2;
    using std::exp;
    using std::log;
    using std::pow;
    
    Double min(double first_argument, Double second_argument);
    Double min(Double first_argument, double second_argument);
    Double min(Double first_argument, Double second_argument);
    Double max(double first_argument, Double second_argument);
    Double max(Double first_argument, double second_argument);
    Double max(Double first_argument, Double second_argument);
    
    Double abs(Double argument);
    Double sqrt(Double argument);
    Double sin(Double argument);
    Double cos(Double argument);
    Double tan(Double argument);
    Double asin(Double argument);
    Double acos(Double argument);
    Double atan(Double argument);
    Double atan2(double y, Double exponent);
    Double atan2(Double y, double exponent);
    Double atan2(Double y, Double exponent);
    Double exp(Double argument);
    Double log(Double argument);
    Double pow(double base, Double exponent);
    Double pow(Double base, double exponent);
    Double pow(Double base, Double exponent);
    Double conj(Double argument);
    Double real(Double argument);
    Double imag(Double argument);
    Double abs2(Double argument);

    std::ostream& operator<<(std::ostream& stream, Double argument);
}

////////// Implementation //////////

namespace OpenSolid
{
    inline Double::Double() {}
    
    inline Double::Double(double argument) : _implementation(argument) {}

    inline double Double::implementation() const {return _implementation;}
    
    inline std::size_t Double::hashValue() const {return boost::hash_value(implementation());}
        
    inline bool Double::isZero(Double precision) const {
        return std::abs(implementation()) < precision;
    }
    
    inline bool Double::isEqualTo(Double argument, Double precision) const {
        return std::abs(implementation() - argument.implementation()) < precision.implementation();
    }
    
    inline bool Double::isLessThan(Double argument, Double precision) const {
        return implementation() < argument.implementation() - precision.implementation();
    }
    
    inline bool Double::isGreaterThan(Double argument, Double precision) const {
        return implementation() > argument.implementation() + precision.implementation();
    }

    inline bool Double::isLessThanOrEqualTo(Double argument, Double precision) const {
        return implementation() < argument.implementation() + precision.implementation();
    }

    inline bool Double::isGreaterThanOrEqualTo(Double argument, Double precision) const {
        return implementation() > argument.implementation() - precision.implementation();
    }
    
    inline Double& Double::operator+=(Double argument) {
        _implementation += argument._implementation;
        return *this;
    }
    
    inline Double& Double::operator-=(Double argument) {
        _implementation -= argument._implementation;
        return *this;
    }
    
    inline Double& Double::operator*=(Double argument) {
        _implementation *= argument._implementation;
        return *this;
    }
    
    inline Double& Double::operator/=(Double argument) {
        _implementation /= argument._implementation;
        return *this;
    }
    
    inline bool operator==(double first_argument, Double second_argument) {
        return first_argument == second_argument.implementation();
    }
    
    inline bool operator==(Double first_argument, double second_argument) {
        return first_argument.implementation() == second_argument;
    }
    
    inline bool operator==(Double first_argument, Double second_argument) {
        return first_argument.implementation() == second_argument.implementation();
    }
    
    inline bool operator!=(double first_argument, Double second_argument) {
        return first_argument != second_argument.implementation();
    }
    
    inline bool operator!=(Double first_argument, double second_argument) {
        return first_argument.implementation() != second_argument;
    }
    
    inline bool operator!=(Double first_argument, Double second_argument) {
        return first_argument.implementation() != second_argument.implementation();
    }
    
    inline bool operator<(double first_argument, Double second_argument) {
        return first_argument < second_argument.implementation();
    }
    
    inline bool operator<(Double first_argument, double second_argument) {
        return first_argument.implementation() < second_argument;
    }
    
    inline bool operator<(Double first_argument, Double second_argument) {
        return first_argument.implementation() < second_argument.implementation();
    }
    
    inline bool operator>(double first_argument, Double second_argument) {
        return first_argument > second_argument.implementation();
    }
    
    inline bool operator>(Double first_argument, double second_argument) {
        return first_argument.implementation() > second_argument;
    }
    
    inline bool operator>(Double first_argument, Double second_argument) {
        return first_argument.implementation() > second_argument.implementation();
    }
    
    inline bool operator<=(double first_argument, Double second_argument) {
        return first_argument <= second_argument.implementation();
    }
    
    inline bool operator<=(Double first_argument, double second_argument) {
        return first_argument.implementation() <= second_argument;
    }
    
    inline bool operator<=(Double first_argument, Double second_argument) {
        return first_argument.implementation() <= second_argument.implementation();
    }
    
    inline bool operator>=(double first_argument, Double second_argument) {
        return first_argument >= second_argument.implementation();
    }
    
    inline bool operator>=(Double first_argument, double second_argument) {
        return first_argument.implementation() >= second_argument;
    }
    
    inline bool operator>=(Double first_argument, Double second_argument) {
        return first_argument.implementation() >= second_argument.implementation();
    }
    
    inline Double operator-(Double argument) {return -argument.implementation();}
    
    inline Double operator+(double first_argument, Double second_argument) {
        return first_argument + second_argument.implementation();
    }
    
    inline Double operator+(Double first_argument, double second_argument) {
        return first_argument.implementation() + second_argument;
    }
    
    inline Double operator+(Double first_argument, Double second_argument) {
        return first_argument.implementation() + second_argument.implementation();
    }
    
    inline Double operator-(double first_argument, Double second_argument) {
        return first_argument - second_argument.implementation();
    }
    
    inline Double operator-(Double first_argument, double second_argument) {
        return first_argument.implementation() - second_argument;
    }
    
    inline Double operator-(Double first_argument, Double second_argument) {
        return first_argument.implementation() - second_argument.implementation();
    }
    
    inline Double operator*(double first_argument, Double second_argument) {
        return first_argument * second_argument.implementation();
    }
    
    inline Double operator*(Double first_argument, double second_argument) {
        return first_argument.implementation() * second_argument;
    }
    
    inline Double operator*(Double first_argument, Double second_argument) {
        return first_argument.implementation() * second_argument.implementation();
    }
    
    inline Double operator/(double first_argument, Double second_argument) {
        return first_argument / second_argument.implementation();
    }
    
    inline Double operator/(Double first_argument, double second_argument) {
        return first_argument.implementation() / second_argument;
    }
    
    inline Double operator/(Double first_argument, Double second_argument) {
        return first_argument.implementation() / second_argument.implementation();
    }
    
    inline Double min(double first_argument, Double second_argument) {
        return std::min(first_argument, second_argument.implementation());
    }
    
    inline Double min(Double first_argument, double second_argument) {
        return std::min(first_argument.implementation(), second_argument);
    }
    
    inline Double min(Double first_argument, Double second_argument) {
        return std::min(first_argument.implementation(), second_argument.implementation());
    }
    
    inline Double max(double first_argument, Double second_argument) {
        return std::max(first_argument, second_argument.implementation());
    }
    
    inline Double max(Double first_argument, double second_argument) {
        return std::max(first_argument.implementation(), second_argument);
    }
    
    inline Double max(Double first_argument, Double second_argument) {
        return std::max(first_argument.implementation(), second_argument.implementation());
    }
    
    inline Double abs(Double argument) {return std::abs(argument.implementation());}
    
    inline Double sqrt(Double argument) {return std::sqrt(argument.implementation());}
    
    inline Double sin(Double argument) {return std::sin(argument.implementation());}
    
    inline Double cos(Double argument) {return std::cos(argument.implementation());}
    
    inline Double tan(Double argument) {return std::tan(argument.implementation());}
    
    inline Double asin(Double argument) {return std::asin(argument.implementation());}
    
    inline Double acos(Double argument) {return std::acos(argument.implementation());}
    
    inline Double atan(Double argument) {return std::atan(argument.implementation());}
    
    inline Double atan2(double y, Double x) {
        return std::atan2(y, x.implementation());
    }
    
    inline Double atan2(Double y, double x) {
        return std::atan2(y.implementation(), x);
    }
    
    inline Double atan2(Double y, Double x) {
        return std::atan2(y.implementation(), x.implementation());
    }
    
    inline Double exp(Double argument) {return std::exp(argument.implementation());}
    
    inline Double log(Double argument) {return std::log(argument.implementation());}
    
    inline Double pow(double base, Double exponent) {
        return std::pow(base, exponent.implementation());
    }
    
    inline Double pow(Double base, double exponent) {
        return std::pow(base.implementation(), exponent);
    }
    
    inline Double pow(Double base, Double exponent) {
        return std::pow(base.implementation(), exponent.implementation());
    }
    
    inline Double conj(Double argument) {return argument;}
    
    inline Double real(Double argument) {return argument;}
    
    inline Double imag(Double argument) {return 0.0;}
    
    inline Double abs2(Double argument) {return argument * argument;}

    inline std::ostream& operator<<(std::ostream& stream, Double argument) {
        stream << argument.implementation();
        return stream;
    }
}
#include <OpenSolid/Scalar/Interval.hpp>

#endif
