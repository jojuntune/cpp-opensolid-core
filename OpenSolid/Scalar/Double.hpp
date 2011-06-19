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

#include <OpenSolid/config.hpp>
#include <OpenSolid/Scalar/ScalarBase.hpp>

namespace Eigen
{
    template <class DerivedType>
    struct EigenBase;
}

namespace OpenSolid
{
    class Interval;
    
    class Double : public ScalarBase<Double>
    {
    private:
        double _value;
    public:
        typedef ScalarBase<Double> Base;
        typedef Interval Bounds;

        static Double defaultPrecision();
        
        Double();
        Double(int value);
        Double(float value);
        Double(double value);
        
        template <class DerivedType>
        Double(const Eigen::EigenBase<DerivedType>& matrix);
        
        template <class DerivedType>
        void operator=(const Eigen::EigenBase<DerivedType>& matrix);
        
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
        
        using Base::isApprox;
        using Base::isEqualTo;
        using Base::isLessThan;
        using Base::isGreaterThan;
        using Base::isLessThanOrEqualTo;
        using Base::isGreaterThanOrEqualTo;
        using Base::overlaps;
        using Base::isSubsetOf;
        using Base::isProperSubsetOf;
        using Base::isSupersetOf;
        using Base::isProperSupersetOf;
        
        bool isZero(double precision = OPENSOLID_PRECISION) const;
        
        bool isApprox(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isApprox(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isEqualTo(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isEqualTo(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isLessThan(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isLessThan(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isGreaterThan(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThan(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isLessThanOrEqualTo(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isLessThanOrEqualTo(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isGreaterThanOrEqualTo(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isGreaterThanOrEqualTo(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        bool overlaps(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool overlaps(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isSubsetOf(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isSubsetOf(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isProperSubsetOf(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isProperSubsetOf(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isSupersetOf(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isSupersetOf(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        bool isProperSupersetOf(Double argument, double precision = OPENSOLID_PRECISION) const;
        bool isProperSupersetOf(Interval argument, double precision = OPENSOLID_PRECISION) const;
        
        Double& operator+=(Double argument);
        Double& operator-=(Double argument);
        Double& operator*=(Double argument);
        Double& operator/=(Double argument);
    };
    
    using std::abs;
    using std::sqrt;
    using std::sin;
    using std::cos;
    using std::tan;
    using std::asin;
    using std::acos;
    using std::atan;
    using std::exp;
    using std::log;
    using std::pow;
    using std::atan2;
    
    Double abs(Double argument);
    Double sqrt(Double argument);
    Double sin(Double argument);
    Double cos(Double argument);
    Double tan(Double argument);
    Double asin(Double argument);
    Double acos(Double argument);
    Double atan(Double argument);
    Double exp(Double argument);
    Double log(Double argument);

    Double pow(Double base, Double exponent);
    Double pow(Double base, int exponent);
    Double pow(int base, Double exponent);
    Double pow(Double base, float exponent);
    Double pow(float base, Double exponent);
    Double pow(Double base, double exponent);
    Double pow(double base, Double exponent);

    Double atan2(Double y, Double exponent);
    Double atan2(Double y, int exponent);
    Double atan2(int y, Double exponent);
    Double atan2(Double y, float exponent);
    Double atan2(float y, Double exponent);
    Double atan2(Double y, double exponent);
    Double atan2(double y, Double exponent);

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
        
        template <class ScalarType>
        struct is_arithmetic;
        
        template <>
        struct is_arithmetic<OpenSolid::Double>
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
}

////////// Implementation //////////

#include <OpenSolid/Scalar/operators.hpp>
#include <OpenSolid/Scalar/Interval.hpp>

namespace OpenSolid
{
    inline Double::Double() {}
    
    inline Double::Double(int value) : _value(value) {}
    
    inline Double::Double(float value) : _value(value) {}
    
    inline Double::Double(double value) : _value(value) {}
        
    template <class DerivedType>
    inline Double::Double(const Eigen::EigenBase<DerivedType>& matrix) :
        _value(matrix.derived().eval().coeff(0, 0).value()) {}
    
    template <class DerivedType>
    inline void Double::operator=(const Eigen::EigenBase<DerivedType>& matrix) {
        _value = matrix.derived().eval().coeff(0, 0).value();
    }

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
            return Interval(argument.lower(), *this);
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
        
    inline bool Double::isZero(double precision) const {return std::abs(_value) < precision;}
    
    inline bool Double::isApprox(Double argument, double precision) const {
        return std::abs(_value - argument._value) < precision;
    }
    
    inline bool Double::isApprox(Interval argument, double precision) const {
        return this->isApprox(argument.lower(), precision) &&
            this->isApprox(argument.upper(), precision);
    }
    
    inline bool Double::isEqualTo(Double argument, double precision) const {
        return this->isApprox(argument, precision);
    }
    
    inline bool Double::isEqualTo(Interval argument, double precision) const {
        return this->isApprox(argument, precision);
    }
    
    inline bool Double::isLessThan(Double argument, double precision) const {
        return _value < argument._value - precision;
    }
    
    inline bool Double::isLessThan(Interval argument, double precision) const {
        return this->isLessThan(argument.lower(), precision);
    }
    
    inline bool Double::isGreaterThan(Double argument, double precision) const {
        return _value > argument._value + precision;
    }
    
    inline bool Double::isGreaterThan(Interval argument, double precision) const {
        return this->isGreaterThan(argument.upper(), precision);
    }

    inline bool Double::isLessThanOrEqualTo(Double argument, double precision) const {
        return _value < argument._value + precision;
    }

    inline bool Double::isLessThanOrEqualTo(Interval argument, double precision) const {
        return this->isLessThanOrEqualTo(argument.lower(), precision);
    }

    inline bool Double::isGreaterThanOrEqualTo(Double argument, double precision) const {
        return _value > argument._value - precision;
    }

    inline bool Double::isGreaterThanOrEqualTo(Interval argument, double precision) const {
        return this->isGreaterThanOrEqualTo(argument.upper(), precision);
    }

    inline bool Double::overlaps(Double argument, double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::overlaps(Interval argument, double precision) const {
        this->isGreaterThanOrEqualTo(argument.lower(), precision) &&
            this->isLessThanOrEqualTo(argument.upper(), precision);
    }

    inline bool Double::isSubsetOf(Double argument, double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::isSubsetOf(Interval argument, double precision) const {
        return this->overlaps(argument, precision);
    }

    inline bool Double::isProperSubsetOf(Double argument, double precision) const {
        return false;
    }

    inline bool Double::isProperSubsetOf(Interval argument, double precision) const {
        return this->isGreaterThan(argument.lower(), precision) &&
            this->isLessThan(argument.upper(), precision);
    }

    inline bool Double::isSupersetOf(Double argument, double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::isSupersetOf(Interval argument, double precision) const {
        return this->isEqualTo(argument, precision);
    }

    inline bool Double::isProperSupersetOf(Double argument, double precision) const {
        return false;
    }

    inline bool Double::isProperSupersetOf(Interval argument, double precision) const {
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
    
    inline Double abs(Double argument) {return std::abs(argument.value());}
    
    inline Double sqrt(Double argument) {return std::sqrt(argument.value());}
    
    inline Double sin(Double argument) {return std::sin(argument.value());}
    
    inline Double cos(Double argument) {return std::cos(argument.value());}
    
    inline Double tan(Double argument) {return std::tan(argument.value());}
    
    inline Double asin(Double argument) {return std::asin(argument.value());}
    
    inline Double acos(Double argument) {return std::acos(argument.value());}
    
    inline Double atan(Double argument) {return std::atan(argument.value());}
    
    inline Double exp(Double argument) {return std::exp(argument.value());}
    
    inline Double log(Double argument) {return std::log(argument.value());}
    
    inline Double pow(Double base, Double exponent) {
        return std::pow(base.value(), exponent.value());
    }
    
    inline Double atan2(Double y, Double x) {return std::atan2(y.value(), x.value());}

    inline Double atan2(Double y, int x) {return std::atan2(y.value(), double(x));}

    inline Double atan2(int y, Double x) {return std::atan2(double(y), x.value());}

    inline Double atan2(Double y, float x) {return std::atan2(y.value(), double(x));}

    inline Double atan2(float y, Double x) {return std::atan2(double(y), x.value());}

    inline Double atan2(Double y, double x) {return std::atan2(y.value(), x);}

    inline Double atan2(double y, Double x) {return std::atan2(y, x.value());}

    inline std::ostream& operator<<(std::ostream& stream, Double argument) {
        stream << argument.value();
        return stream;
    }
}

#endif
