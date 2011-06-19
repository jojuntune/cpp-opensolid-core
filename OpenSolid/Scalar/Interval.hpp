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

#ifndef OPENSOLID__INTERVAL_HPP
#define OPENSOLID__INTERVAL_HPP

#include <iostream>
#include <cassert>
#include <utility>

#include <boost/numeric/interval.hpp>
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
    class Double;
    
    typedef boost::numeric::interval_lib::policies<
        boost::numeric::interval_lib::save_state_nothing<
            boost::numeric::interval_lib::rounded_transc_exact<double,
                boost::numeric::interval_lib::rounded_arith_exact<double>
            >
        >,
        boost::numeric::interval_lib::checking_base<double>
    > IntervalPolicies;
    
    typedef boost::numeric::interval<double, IntervalPolicies> BoostInterval;
    
    class Interval : public ScalarBase<Interval>
    {
    private:
        BoostInterval _value;
    public:
        typedef ScalarBase<Interval> Base;
        typedef Interval Bounds;
        
        Interval();
        Interval(int argument);
        Interval(float argument);
        Interval(double argument);
        Interval(Double argument);
        Interval(Double lower, Double upper);
        Interval(const BoostInterval& argument);
        
        template <class DerivedType>
        Interval(const Eigen::EigenBase<DerivedType>& matrix);
        
        template <class DerivedType>
        void operator=(const Eigen::EigenBase<DerivedType>& matrix);
        
        BoostInterval value() const;
        
        Double lower() const;
        Double upper() const;
        Double median() const;
        Double width() const;
        
        bool empty() const;
        bool singleton() const;
        
        Interval bounds() const;
        std::size_t hashValue() const;
        
        std::pair<Interval, Interval> bisected() const;
        
        Interval squared() const;
        
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
        
        Interval& operator+=(Double argument);
        Interval& operator+=(Interval argument);
        
        Interval& operator-=(Double argument);
        Interval& operator-=(Interval argument);
        
        Interval& operator*=(Double argument);
        Interval& operator*=(Interval argument);
        
        Interval& operator/=(Double argument);
        Interval& operator/=(Interval argument);
        
        static Interval Empty();
        static Interval Whole();
    };
    
    using boost::numeric::abs;
    using boost::numeric::sqrt;
    using boost::numeric::sin;
    using boost::numeric::cos;
    using boost::numeric::tan;
    using boost::numeric::asin;
    using boost::numeric::acos;
    using boost::numeric::atan;
    using boost::numeric::exp;
    using boost::numeric::log;
    using boost::numeric::pow;

    Interval abs(Interval argument);
    Interval sqrt(Interval argument);
    OPENSOLID_CORE_EXPORT Interval sin(Interval argument);
    OPENSOLID_CORE_EXPORT Interval cos(Interval argument);
    OPENSOLID_CORE_EXPORT Interval tan(Interval argument);
    OPENSOLID_CORE_EXPORT Interval asin(Interval argument);
    OPENSOLID_CORE_EXPORT Interval acos(Interval argument);
    OPENSOLID_CORE_EXPORT Interval atan(Interval argument);
    OPENSOLID_CORE_EXPORT Interval exp(Interval argument);
    OPENSOLID_CORE_EXPORT Interval log(Interval argument);
    OPENSOLID_CORE_EXPORT Interval pow(Interval base, Interval exponent);

    OPENSOLID_CORE_EXPORT std::ostream& operator<<(std::ostream& stream, Interval argument);
}

namespace Eigen
{   
    namespace internal
    {
        OpenSolid::Interval conj(OpenSolid::Interval argument);
        OpenSolid::Interval real(OpenSolid::Interval argument);
        OpenSolid::Interval imag(OpenSolid::Interval);
        OpenSolid::Interval abs2(OpenSolid::Interval argument);
        
        
        template <class ScalarType, bool is_integer_>
        struct significant_decimals_default_impl;

        template <>
        struct significant_decimals_default_impl<OpenSolid::Interval, false>
        {
            static inline int run();
        };
        
        template <class ScalarType>
        struct is_arithmetic;
        
        template <>
        struct is_arithmetic<OpenSolid::Interval>
        {
            static const bool value = true;
        };
    }
    
    template <class Type>
    struct NumTraits;
    
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

#include <OpenSolid/Scalar/operators.hpp>
#include <OpenSolid/Scalar/Double.hpp>

namespace OpenSolid
{   
    inline Interval::Interval() : _value() {}
    
    inline Interval::Interval(int argument) : _value(argument) {}

    inline Interval::Interval(float argument) : _value(argument) {}

    inline Interval::Interval(double argument) : _value(argument) {}

    inline Interval::Interval(Double argument) : _value(argument.value()) {}

    inline Interval::Interval(Double lower, Double upper) :
        _value(lower.value(), upper.value()) {}

    inline Interval::Interval(const BoostInterval& argument) : _value(argument) {}
        
    template <class DerivedType>
    inline Interval::Interval(const Eigen::EigenBase<DerivedType>& matrix) :
        _value(matrix.derived().eval().coeff(0, 0).value()) {}
    
    template <class DerivedType>
    inline void Interval::operator=(const Eigen::EigenBase<DerivedType>& matrix) {
        _value = matrix.derived().eval().coeff(0, 0).value();
    }
        
    inline BoostInterval Interval::value() const {return _value;}
    
    inline Double Interval::lower() const {return value().lower();}

    inline Double Interval::upper() const {return value().upper();}
    
    inline Double Interval::median() const {return boost::numeric::median(value());}
    
    inline Double Interval::width() const {return boost::numeric::width(value());}
    
    inline bool Interval::empty() const {return boost::numeric::empty(value());}
    
    inline bool Interval::singleton() const {return boost::numeric::singleton(value());}
    
    inline Interval Interval::bounds() const {return *this;}
    
    inline std::size_t Interval::hashValue() const {
        std::size_t result = 0;
        boost::hash_combine(result, lower().hashValue());
        boost::hash_combine(result, upper().hashValue());
        return result;
    }
    
    inline std::pair<Interval, Interval> Interval::bisected() const {
        Double mid = median();
        return std::make_pair(Interval(lower(), mid), Interval(mid, upper()));
    }
    
    inline Interval Interval::squared() const {return boost::numeric::square(value());}
        
    inline Interval Interval::hull(Double argument) const {
        if (argument < lower()) {
            return Interval(argument, upper());
        } else if (argument > upper()) {
            return Interval(lower(), argument);
        } else {
            return *this;
        }
    }
    
    inline Interval Interval::hull(Interval argument) const {
        return boost::numeric::hull(value(), argument.value());
    }


    inline Interval Interval::intersection(Double argument) const {
        if (argument >= lower() && argument <= upper()) {
            return argument;
        } else {
            return *this;
        }
    }

    inline Interval Interval::intersection(Interval argument) const {
        return boost::numeric::intersect(value(), argument.value());
    }
        
    inline bool Interval::isZero(double precision) const {
        return lower().isZero(precision) && upper().isZero(precision);
    }

    inline bool Interval::isApprox(Double argument, double precision) const {
        return lower().isEqualTo(argument, precision) && upper().isEqualTo(argument, precision);
    }

    inline bool Interval::isApprox(Interval argument, double precision) const {
        return lower().isEqualTo(argument.upper(), precision) &&
            upper().isEqualTo(argument.lower(), precision);
    }

    inline bool Interval::isEqualTo(Double argument, double precision) const {
        return this->isApprox(argument, precision);
    }

    inline bool Interval::isEqualTo(Interval argument, double precision) const {
        return this->isApprox(argument, precision);
    }

    inline bool Interval::isLessThan(Double argument, double precision) const {
        return upper().isLessThan(argument, precision);
    }

    inline bool Interval::isLessThan(Interval argument, double precision) const {
        return upper().isLessThan(argument.lower(), precision);
    }

    inline bool Interval::isGreaterThan(Double argument, double precision) const {
        return lower().isGreaterThan(argument, precision);
    }

    inline bool Interval::isGreaterThan(Interval argument, double precision) const {
        return lower().isGreaterThan(argument.upper(), precision);
    }

    inline bool Interval::isLessThanOrEqualTo(Double argument, double precision) const {
        return upper().isLessThanOrEqualTo(argument, precision);
    }

    inline bool Interval::isLessThanOrEqualTo(Interval argument, double precision) const {
        return upper().isLessThanOrEqualTo(argument.lower(), precision);
    }

    inline bool Interval::isGreaterThanOrEqualTo(Double argument, double precision) const {
        return lower().isGreaterThanOrEqualTo(argument, precision);
    }

    inline bool Interval::isGreaterThanOrEqualTo(Interval argument, double precision) const {
        return lower().isGreaterThanOrEqualTo(argument.upper(), precision);
    }
    
    inline bool Interval::overlaps(Double argument, double precision) const {
        return lower().isLessThanOrEqualTo(argument, precision) &&
            upper().isGreaterThanOrEqualTo(argument, precision);
    }
    
    inline bool Interval::overlaps(Interval argument, double precision) const {
        return lower().isLessThanOrEqualTo(argument.upper(), precision) &&
            upper().isGreaterThanOrEqualTo(argument.lower(), precision);
    }
    
    inline bool Interval::isSubsetOf(Double argument, double precision) const {
        return this->isEqualTo(argument, precision);
    }
    
    inline bool Interval::isSubsetOf(Interval argument, double precision) const {
        return lower().isGreaterThanOrEqualTo(argument.lower(), precision) &&
            upper().isLessThanOrEqualTo(argument.upper(), precision);
    }
    
    inline bool Interval::isProperSubsetOf(Double argument, double precision) const {
        return false;
    }
    
    inline bool Interval::isProperSubsetOf(Interval argument, double precision) const {
        return lower().isGreaterThan(argument.lower(), precision) &&
            upper().isLessThan(argument.upper(), precision);
    }
    
    inline bool Interval::isSupersetOf(Double argument, double precision) const {
        return lower().isLessThanOrEqualTo(argument, precision) &&
            upper().isGreaterThanOrEqualTo(argument, precision);
    }
    
    inline bool Interval::isSupersetOf(Interval argument, double precision) const {
        return lower().isLessThanOrEqualTo(argument.lower(), precision) &&
            upper().isGreaterThanOrEqualTo(argument.upper(), precision);
    }
    
    inline bool Interval::isProperSupersetOf(Double argument, double precision) const {
        return lower().isLessThan(argument, precision) &&
            upper().isGreaterThan(argument, precision);
    }
    
    inline bool Interval::isProperSupersetOf(Interval argument, double precision) const {
        return lower().isLessThan(argument.lower(), precision) &&
            upper().isGreaterThan(argument.upper(), precision);
    }

    inline Interval& Interval::operator+=(Double argument) {
        value() += argument.value();
        return *this;
    }

    inline Interval& Interval::operator+=(Interval argument) {
        value() += argument.value();
        return *this;
    }

    inline Interval& Interval::operator-=(Double argument) {
        value() -= argument.value();
        return *this;
    }

    inline Interval& Interval::operator-=(Interval argument) {
        value() -= argument.value();
        return *this;
    }

    inline Interval& Interval::operator*=(Double argument) {
        value() *= argument.value();
        return *this;
    }

    inline Interval& Interval::operator*=(Interval argument) {
        value() *= argument.value();
        return *this;
    }

    inline Interval& Interval::operator/=(Double argument) {
        value() /= argument.value();
        return *this;
    }

    inline Interval& Interval::operator/=(Interval argument) {
        value() /= argument.value();
        return *this;
    }
    
    inline Interval Interval::Empty() {return BoostInterval::empty();}
    
    inline Interval Interval::Whole() {return BoostInterval::whole();}

    inline Interval abs(Interval argument) {return boost::numeric::abs(argument.value());}

    inline Interval sqrt(Interval argument) {return boost::numeric::sqrt(argument.value());}
}

#endif
