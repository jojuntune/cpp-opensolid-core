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

#include <OpenSolid/config.hpp>

#include <iostream>
#include <cassert>
#include <utility>

#include <boost/numeric/interval.hpp>
#include <boost/functional/hash.hpp>

#include <OpenSolid/Scalar/ScalarBase.hpp>
#include <OpenSolid/Scalar/Double.hpp>

namespace OpenSolid
{
    typedef boost::numeric::interval<
        double,
        boost::numeric::interval_lib::policies<
            boost::numeric::interval_lib::save_state_nothing<
                boost::numeric::interval_lib::rounded_transc_exact<double,
                    boost::numeric::interval_lib::rounded_arith_exact<double>
                >
            >,
            boost::numeric::interval_lib::checking_base<double>
        >
    > BoostInterval;
    
    class Interval : public ScalarBase<Interval>
    {
    private:
        BoostInterval _value;
    public:
        Interval();
        Interval(Double argument);
        Interval(Double lower, Double upper);
        Interval(const BoostInterval& argument);
        
        BoostInterval& value();
        const BoostInterval& value() const;
        
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
        
        bool isZero(Double precision = Double::defaultPrecision()) const;
        bool isApprox(Double argument, Double precision = Double::defaultPrecision()) const;
        bool isApprox(Interval argument, Double precision = Double::defaultPrecision()) const;
        bool isEqualTo(Double argument, Double precision = Double::defaultPrecision()) const;
        bool isEqualTo(Interval argument, Double precision = Double::defaultPrecision()) const;
        bool isLessThan(Double argument, Double precision = Double::defaultPrecision()) const;
        bool isLessThan(Interval argument, Double precision = Double::defaultPrecision()) const;
        bool isGreaterThan(Double argument, Double precision = Double::defaultPrecision()) const;
        bool isGreaterThan(Interval argument, Double precision = Double::defaultPrecision()) const;
        
        bool isLessThanOrEqualTo(
            Double argument,
            Double precision = Double::defaultPrecision()
        ) const;

        bool isLessThanOrEqualTo(
            Interval argument,
            Double precision = Double::defaultPrecision()
        ) const;
        
        bool isGreaterThanOrEqualTo(
            Double argument,
            Double precision = Double::defaultPrecision()
        ) const;
        
        bool isGreaterThanOrEqualTo(
            Interval argument,
            Double precision = Double::defaultPrecision()
        ) const;
        
        bool overlaps(Double argument, Double precision = Double::defaultPrecision()) const;
        bool overlaps(Interval argument, Double precision = Double::defaultPrecision()) const;

        bool isSubsetOf(Double argument, Double precision = Double::defaultPrecision()) const;
        bool isSubsetOf(Interval argument, Double precision = Double::defaultPrecision()) const;
        
        bool isProperSubsetOf(
            Double argument,
            Double precision = Double::defaultPrecision()
        ) const;
        
        bool isProperSubsetOf(
            Interval argument,
            Double precision = Double::defaultPrecision()
        ) const;

        bool isSupersetOf(Double argument, Double precision = Double::defaultPrecision()) const;
        bool isSupersetOf(Interval argument, Double precision = Double::defaultPrecision()) const;
        
        bool isProperSupersetOf(
            Double argument,
            Double precision = Double::defaultPrecision()
        ) const;
        
        bool isProperSupersetOf(
            Interval argument,
            Double precision = Double::defaultPrecision()
        ) const;
        
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

    bool operator==(Double first_argument, Interval second_argument);
    bool operator==(Interval first_argument, Double second_argument);
    bool operator==(Interval first_argument, Interval second_argument);
    bool operator!=(Double first_argument, Interval second_argument);
    bool operator!=(Interval first_argument, Double second_argument);
    bool operator!=(Interval first_argument, Interval second_argument);
    bool operator<(Double first_argument, Interval second_argument);
    bool operator<(Interval first_argument, Double second_argument);
    bool operator<(Interval first_argument, Interval second_argument);
    bool operator>(Double first_argument, Interval second_argument);
    bool operator>(Interval first_argument, Double second_argument);
    bool operator>(Interval first_argument, Interval second_argument);
    bool operator<=(Double first_argument, Interval second_argument);
    bool operator<=(Interval first_argument, Double second_argument);
    bool operator<=(Interval first_argument, Interval second_argument);
    bool operator>=(Double first_argument, Interval second_argument);
    bool operator>=(Interval first_argument, Double second_argument);
    bool operator>=(Interval first_argument, Interval second_argument);
    
    Interval operator-(Interval argument);
    Interval operator+(Double first_argument, Interval second_argument);
    Interval operator+(Interval first_argument, Double second_argument);
    Interval operator+(Interval first_argument, Interval second_argument);
    Interval operator-(Double first_argument, Interval second_argument);
    Interval operator-(Interval first_argument, Double second_argument);
    Interval operator-(Interval first_argument, Interval second_argument);
    Interval operator*(Double first_argument, Interval second_argument);
    Interval operator*(Interval first_argument, Double second_argument);
    Interval operator*(Interval first_argument, Interval second_argument);
    Interval operator/(Double first_argument, Interval second_argument);
    Interval operator/(Interval first_argument, Double second_argument);
    Interval operator/(Interval first_argument, Interval second_argument);
    
    Interval min(Double first_argument, Interval second_argument);
    Interval min(Interval first_argument, Double second_argument);
    Interval min(Interval first_argument, Interval second_argument);
    Interval max(Double first_argument, Interval second_argument);
    Interval max(Interval first_argument, Double second_argument);
    Interval max(Interval first_argument, Interval second_argument);

    Interval abs(Interval argument);
    Interval sqrt(Interval argument);
    OPENSOLID_CORE_EXPORT Interval sin(Interval argument);
    OPENSOLID_CORE_EXPORT Interval cos(Interval argument);
    OPENSOLID_CORE_EXPORT Interval tan(Interval argument);
    OPENSOLID_CORE_EXPORT Interval asin(Interval argument);
    OPENSOLID_CORE_EXPORT Interval acos(Interval argument);
    OPENSOLID_CORE_EXPORT Interval atan(Interval argument);
    OPENSOLID_CORE_EXPORT Interval atan2(Interval y, Interval x);
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
        
        template <>
        struct significant_decimals_default_impl<OpenSolid::Interval, false>
        {
            static inline int run();
        };
    }
    
    template <>
    struct NumTraits<OpenSolid::Interval> : public NumTraits<OpenSolid::Double>
    {
        typedef OpenSolid::Interval Real;
        typedef OpenSolid::Interval NonInteger;
        typedef OpenSolid::Interval Nested;
        
        static const int ReadCost = 2;
        static const int AddCost = 2;
        static const int MulCost = 10;
    };
}

////////// Implementation //////////

#include <OpenSolid/Common/Eigen.hpp>

namespace OpenSolid
{   
    inline Interval::Interval() : _value() {}

    inline Interval::Interval(Double argument) : _value(argument.value()) {}

    inline Interval::Interval(Double lower, Double upper) :
        _value(lower.value(), upper.value()) {}

    inline Interval::Interval(const BoostInterval& argument) : _value(argument) {}
        
    inline BoostInterval& Interval::value() {return _value;}
    
    inline const BoostInterval& Interval::value() const {return _value;}
    
    inline Double Interval::lower() const {return value().lower();}

    inline Double Interval::upper() const {return value().upper();}
    
    inline Double Interval::median() const {return median(value());}
    
    inline Double Interval::width() const {return width(value());}
    
    inline bool Interval::empty() const {return empty(value());}
    
    inline bool Interval::singleton() const {return singleton(value());}
    
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
        
    inline bool Interval::isZero(Double precision = Double::defaultPrecision()) const {
        return lower().isZero(precision) && upper().isZero(precision);
    }

    inline bool Interval::isApprox(Double argument, Double precision) const {
        return lower().isEqualTo(argument, precision) && upper().isEqualTo(argument, precision);
    }

    inline bool Interval::isApprox(Interval argument, Double precision) const {
        return lower().isEqualTo(argument.upper(), precision) &&
            upper().isEqualTo(argument.lower(), precision);
    }

    inline bool Interval::isEqualTo(Double argument, Double precision) const {
        return this->isApprox(argument, precision);
    }

    inline bool Interval::isEqualTo(Interval argument, Double precision) const {
        return this->isApprox(argument, precision);
    }

    inline bool Interval::isLessThan(Double argument, Double precision) const {
        return upper().isLessThan(argument, precision);
    }

    inline bool Interval::isLessThan(Interval argument, Double precision) const {
        return upper().isLessThan(argument.lower(), precision);
    }

    inline bool Interval::isGreaterThan(Double argument, Double precision) const {
        return lower().isGreaterThan(argument, precision);
    }

    inline bool Interval::isGreaterThan(Interval argument, Double precision) const {
        return lower().isGreaterThan(argument.upper(), precision);
    }

    inline bool Interval::isLessThanOrEqualTo(Double argument, Double precision) const {
        return upper().isLessThanOrEqualTo(argument, precision);
    }

    inline bool Interval::isLessThanOrEqualTo(Interval argument, Double precision) const {
        return upper().isLessThanOrEqualTo(argument.lower(), precision);
    }

    inline bool Interval::isGreaterThanOrEqualTo(Double argument, Double precision) const {
        return lower().isGreaterThanOrEqualTo(argument, precision);
    }

    inline bool Interval::isGreaterThanOrEqualTo(Interval argument, Double precision) const {
        return lower().isGreaterThanOrEqualTo(argument.upper(), precision);
    }
    
    inline bool Interval::overlaps(Double argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument, precision) &&
            upper().isGreaterThanOrEqualTo(argument, precision);
    }
    
    inline bool Interval::overlaps(Interval argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument.upper(), precision) &&
            upper().isGreaterThanOrEqualTo(argument.lower(), precision);
    }
    
    inline bool Interval::isSubsetOf(Double argument, Double precision) const {
        return this->isEqualTo(argument, precision);
    }
    
    inline bool Interval::isSubsetOf(Interval argument, Double precision) const {
        return lower().isGreaterThanOrEqualTo(argument.lower(), precision) &&
            upper().isLessThanOrEqualTo(argument.upper(), precision);
    }
    
    inline bool Interval::isProperSubsetOf(Double argument, Double precision) const {
        return false;
    }
    
    inline bool Interval::isProperSubsetOf(Interval argument, Double precision) const {
        return lower().isGreaterThan(argument.lower(), precision) &&
            upper().isLessThan(argument.upper(), precision);
    }
    
    inline bool Interval::isSupersetOf(Double argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument, precision) &&
            upper().isGreaterThanOrEqualTo(argument, precision);
    }
    
    inline bool Interval::isSupersetOf(Interval argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument.lower(), precision) &&
            upper().isGreaterThanOrEqualTo(argument.upper(), precision);
    }
    
    inline bool Interval::isProperSupersetOf(Double argument, Double precision) const {
        return lower().isLessThan(argument, precision) &&
            upper().isGreaterThan(argument, precision);
    }
    
    inline bool Interval::isProperSupersetOf(Interval argument, Double precision) const {
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

    inline bool operator==(Double first_argument, Interval second_argument) {
        return first_argument == second_argument.lower() &&
            first_argument == second_argument.upper();
    }

    inline bool operator==(Interval first_argument, Double second_argument) {
        return first_argument.lower() == second_argument &&
            first_argument.upper() == second_argument;
    }

    inline bool operator==(Interval first_argument, Interval second_argument) {
        return first_argument.lower() == second_argument.lower() &&
            first_argument.upper() == second_argument.upper();
    }

    inline bool operator!=(Double first_argument, Interval second_argument) {
        return first_argument != second_argument.lower() ||
            first_argument != second_argument.upper();
    }

    inline bool operator!=(Interval first_argument, Double second_argument) {
        return first_argument.lower() != second_argument ||
            first_argument.upper() != second_argument;
    }

    inline bool operator!=(Interval first_argument, Interval second_argument) {
        return first_argument.lower() != second_argument.lower() ||
            first_argument.upper() != second_argument.upper();
    }

    inline bool operator<(Double first_argument, Interval second_argument) {
        if (first_argument == second_argument.lower()) {
            return first_argument < second_argument.upper();
        } else {
            return first_argument < second_argument.lower();
        }
    }

    inline bool operator<(Interval first_argument, Double second_argument) {
        return first_argument.lower() < second_argument;
    }

    inline bool operator<(Interval first_argument, Interval second_argument) {
        if (first_argument.lower() == second_argument.lower()) {
            return first_argument.upper() < second_argument.upper();
        } else {
            return first_argument.lower() < second_argument.lower();
        }
    }

    inline bool operator>(Double first_argument, Interval second_argument) {
        return first_argument > second_argument.lower();
    }

    inline bool operator>(Interval first_argument, Double second_argument) {
        if (first_argument.lower() == second_argument) {
            return first_argument.upper() > second_argument;
        } else {
            return first_argument.lower() > second_argument;
        }
    }

    inline bool operator>(Interval first_argument, Interval second_argument) {
        if (first_argument.lower() == second_argument.lower()) {
            return first_argument.upper() < second_argument.upper();
        } else {
            return first_argument.lower() < second_argument.lower();
        }
    }
        
    inline Interval operator-(Interval argument) {return -argument.value();}

    inline Interval operator+(Double first_argument, Interval second_argument) {
        return first_argument.value() + second_argument.value();
    }

    inline Interval operator+(Interval first_argument, Double second_argument) {
        return first_argument.value() + second_argument.value();
    }

    inline Interval operator+(Interval first_argument, Interval second_argument) {
        return first_argument.value() + second_argument.value();
    }

    inline Interval operator-(Double first_argument, Interval second_argument) {
        return first_argument.value() - second_argument.value();
    }

    inline Interval operator-(Interval first_argument, Double second_argument) {
        return first_argument.value() - second_argument.value();
    }

    inline Interval operator-(Interval first_argument, Interval second_argument) {
        return first_argument.value() - second_argument.value();
    }

    inline Interval operator*(Double first_argument, Interval second_argument) {
        return first_argument.value() * second_argument.value();
    }

    inline Interval operator*(Interval first_argument, Double second_argument) {
        return first_argument.value() * second_argument.value();
    }

    inline Interval operator*(Interval first_argument, Interval second_argument) {
        return first_argument.value() * second_argument.value();
    }

    inline Interval operator/(Double first_argument, Interval second_argument) {
        return first_argument.value() / second_argument.value();
    }

    inline Interval operator/(Interval first_argument, Double second_argument) {
        return first_argument.value() / second_argument.value();
    }

    inline Interval operator/(Interval first_argument, Interval second_argument) {
        return first_argument.value() / second_argument.value();
    }
    
    inline Interval min(Double first_argument, Interval second_argument) {
        return boost::numeric::min(first_argument.value(), second_argument.value());
    }

    inline Interval min(Interval first_argument, Double second_argument) {
        return boost::numeric::min(first_argument.value(), second_argument.value());
    }

    inline Interval min(Interval first_argument, Interval second_argument) {
        return boost::numeric::min(first_argument.value(), second_argument.value());
    }

    inline Interval max(Double first_argument, Interval second_argument) {
        return boost::numeric::min(first_argument.value(), second_argument.value());
    }

    inline Interval max(Interval first_argument, Double second_argument) {
        return boost::numeric::min(first_argument.value(), second_argument.value());
    }

    inline Interval max(Interval first_argument, Interval second_argument) {
        return boost::numeric::min(first_argument.value(), second_argument.value());
    }

    inline Interval abs(Interval argument) {return boost::numeric::abs(argument.value());}

    inline Interval sqrt(Interval argument) {return boost::numeric::sqrt(argument.value());}
}

namespace Eigen
{   
    namespace internal
    {
        inline OpenSolid::Interval conj(OpenSolid::Interval argument) {return argument;}
        
        inline OpenSolid::Interval real(OpenSolid::Interval argument) {return argument;}
        
        inline OpenSolid::Interval imag(OpenSolid::Interval) {return 0.0;}
        
        inline OpenSolid::Interval abs2(OpenSolid::Interval argument) {return argument.squared();}
        
        inline int significant_decimals_default_impl<OpenSolid::Interval, false>::run() {
            return significant_decimals_default_impl<double, false>::run();
        }
    }
}

#endif
