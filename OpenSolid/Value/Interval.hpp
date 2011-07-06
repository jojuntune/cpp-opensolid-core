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

#include <OpenSolid/Common/config.hpp>
#include <OpenSolid/Value/declarations.hpp>

namespace OpenSolid
{
    typedef boost::numeric::interval_lib::policies<
        boost::numeric::interval_lib::save_state_nothing<
            boost::numeric::interval_lib::rounded_transc_exact<double,
                boost::numeric::interval_lib::rounded_arith_exact<double>
            >
        >,
        boost::numeric::interval_lib::checking_base<double>
    > IntervalPolicies;
    
    typedef boost::numeric::interval<double, IntervalPolicies> BoostInterval;
    
    class Interval
    {
    private:
        BoostInterval _implementation;
    public:
        typedef Double OtherScalar;
        typedef Interval Bounds;
        
        Interval();
        Interval(int argument);
        Interval(float argument);
        Interval(double argument);
        Interval(Double argument);
        Interval(Double lower, Double upper);
        Interval(const BoostInterval& argument);
        
        const BoostInterval& implementation() const;
        
        Double lower() const;
        Double upper() const;
        Double median() const;
        Double width() const;
        
        Interval squaredNorm() const;
        
        bool empty() const;
        bool singleton() const;
        
        Interval bounds() const;
        std::size_t hashValue() const;
        
        std::pair<Interval, Interval> bisected() const;
        
        Interval hull(const Interval& argument) const;
        Interval intersection(const Interval& argument) const;
        
        bool isZero(Double precision = OPENSOLID_PRECISION) const;
        
        bool isEqualTo(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isLessThan(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isGreaterThan(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isLessThanOrEqualTo(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isGreaterThanOrEqualTo(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool contains(
            Double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool strictlyContains(
            Double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool overlaps(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool strictlyOverlaps(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const ;
        
        bool isSubsetOf(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isStrictSubsetOf(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isSupersetOf(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isStrictSupersetOf(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        Interval& operator+=(const Interval& argument);
        Interval& operator-=(const Interval& argument);
        Interval& operator*=(const Interval& argument);
        Interval& operator/=(const Interval& argument);
        
        static Interval Empty();
        static Interval Whole();
    };
    
    bool operator==(const Interval& first_argument, const Interval& second_argument);
    bool operator!=(const Interval& first_argument, const Interval& second_argument);
    bool operator<(const Interval& first_argument, const Interval& second_argument);
    bool operator>(const Interval& first_argument, const Interval& second_argument);
    bool operator<=(const Interval& first_argument, const Interval& second_argument);
    bool operator>=(const Interval& first_argument, const Interval& second_argument);
    
    Interval operator-(const Interval& argument);
    Interval operator+(const Interval& first_argument, const Interval& second_argument);
    Interval operator-(const Interval& first_argument, const Interval& second_argument);
    Interval operator*(Double first_argument, const Interval& second_argument);
    Interval operator*(const Interval& first_argument, Double second_argument);
    Interval operator*(const Interval& first_argument, const Interval& second_argument);
    Interval operator/(Double first_argument, const Interval& second_argument);
    Interval operator/(const Interval& first_argument, Double second_argument);
    Interval operator/(const Interval& first_argument, const Interval& second_argument);
    
    Interval abs(const Interval& argument);
    Interval sqrt(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval sin(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval cos(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval tan(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval asin(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval acos(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval atan(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval atan2(const Interval& x, const Interval& y);
    OPENSOLID_CORE_EXPORT Interval exp(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval log(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval pow(const Interval& base, const Interval& exponent);
    const Interval& conj(const Interval& argument);
    const Interval& conj(const Interval& argument);
    Interval imag(const Interval& argument);
    Interval abs2(const Interval& argument);

    OPENSOLID_CORE_EXPORT std::ostream& operator<<(std::ostream& stream, const Interval& argument);
}

////////// Implementation //////////

#include <OpenSolid/Scalar/Double.hpp>

namespace OpenSolid
{   
    inline Interval::Interval() : _implementation() {}

    inline Interval::Interval(int argument) : _implementation(argument) {}

    inline Interval::Interval(float argument) : _implementation(argument) {}

    inline Interval::Interval(double argument) : _implementation(argument) {}

    inline Interval::Interval(Double argument) : _implementation(argument.implementation()) {}

    inline Interval::Interval(Double lower, Double upper) :
        _implementation(lower.implementation(), upper.implementation()) {}

    inline Interval::Interval(const BoostInterval& argument) : _implementation(argument) {}
        
    inline const BoostInterval& Interval::implementation() const {return _implementation;}
    
    inline Double Interval::lower() const {return implementation().lower();}

    inline Double Interval::upper() const {return implementation().upper();}
    
    inline Double Interval::median() const {return boost::numeric::median(implementation());}
    
    inline Double Interval::width() const {return boost::numeric::width(implementation());}

    inline Interval Interval::squaredNorm() const {return boost::numeric::square(implementation());}
    
    inline bool Interval::empty() const {return boost::numeric::empty(implementation());}
    
    inline bool Interval::singleton() const {return boost::numeric::singleton(implementation());}
    
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
    
    inline Interval Interval::hull(const Interval& argument) const {
        return boost::numeric::hull(implementation(), argument.implementation());
    }

    inline Interval Interval::intersection(const Interval& argument) const {
        return boost::numeric::intersect(implementation(), argument.implementation());
    }
    
    inline bool Interval::isZero(Double precision) const {
        return lower().isZero(precision) && upper().isZero(precision);
    }

    inline bool Interval::isEqualTo(const Interval& argument, Double precision) const {
        return lower().isEqualTo(argument.upper(), precision) &&
            upper().isEqualTo(argument.lower(), precision);
    }

    inline bool Interval::isLessThan(const Interval& argument, Double precision) const {
        return upper().isLessThan(argument.lower(), precision);
    }

    inline bool Interval::isGreaterThan(const Interval& argument, Double precision) const {
        return lower().isGreaterThan(argument.upper(), precision);
    }

    inline bool Interval::isLessThanOrEqualTo(const Interval& argument, Double precision) const {
        return upper().isLessThanOrEqualTo(argument.lower(), precision);
    }

    inline bool Interval::isGreaterThanOrEqualTo(const Interval& argument, Double precision) const {
        return lower().isGreaterThanOrEqualTo(argument.upper(), precision);
    }

    inline bool Interval::contains(Double argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument, precision) &&
            upper().isGreaterThanOrEqualTo(argument, precision);
    }

    inline bool Interval::strictlyContains(Double argument, Double precision) const {
        return lower().isLessThan(argument, precision) &&
            upper().isGreaterThan(argument, precision);
    }
    
    inline bool Interval::overlaps(const Interval& argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument.upper(), precision) &&
            upper().isGreaterThanOrEqualTo(argument.lower(), precision);
    }
    
    inline bool Interval::strictlyOverlaps(const Interval& argument, Double precision) const {
        return lower().isLessThan(argument.upper(), precision) &&
            upper().isGreaterThan(argument.lower(), precision);
    }
    
    inline bool Interval::isSubsetOf(const Interval& argument, Double precision) const {
        return lower().isGreaterThanOrEqualTo(argument.lower(), precision) &&
            upper().isLessThanOrEqualTo(argument.upper(), precision);
    }
    
    inline bool Interval::isStrictSubsetOf(const Interval& argument, Double precision) const {
        return lower().isGreaterThan(argument.lower(), precision) &&
            upper().isLessThan(argument.upper(), precision);
    }
    
    inline bool Interval::isSupersetOf(const Interval& argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument.lower(), precision) &&
            upper().isGreaterThanOrEqualTo(argument.upper(), precision);
    }
    
    inline bool Interval::isStrictSupersetOf(const Interval& argument, Double precision) const {
        return lower().isLessThan(argument.lower(), precision) &&
            upper().isGreaterThan(argument.upper(), precision);
    }
    
    inline Interval Interval::Empty() {return BoostInterval::empty();}
    
    inline Interval Interval::Whole() {return BoostInterval::whole();}

    inline bool operator==(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() &&
            first_argument.upper() == second_argument.upper();
    }

    inline bool operator!=(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() != second_argument.lower() ||
            first_argument.upper() != second_argument.upper();
    }

    inline bool operator<(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() ?
            first_argument.upper() < second_argument.upper() :
            first_argument.lower() < second_argument.lower();
    }

    inline bool operator>(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() ?
            first_argument.upper() > second_argument.upper() :
            first_argument.lower() > second_argument.lower();
    }

    inline bool operator<=(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() ?
            first_argument.upper() <= second_argument.upper() :
            first_argument.lower() <= second_argument.lower();
    }

    inline bool operator>=(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() ?
            first_argument.upper() >= second_argument.upper() :
            first_argument.lower() >= second_argument.lower();
    }

    inline Interval operator-(const Interval& argument) {return -argument.implementation();}

    inline Interval operator+(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.implementation() + second_argument.implementation();
    }

    inline Interval operator-(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.implementation() - second_argument.implementation();
    }

    inline Interval operator*(Double first_argument, const Interval& second_argument) {
        return first_argument.implementation() * second_argument.implementation();
    }

    inline Interval operator*(const Interval& first_argument, Double second_argument) {
        return first_argument.implementation() * second_argument.implementation();
    }

    inline Interval operator*(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.implementation() * second_argument.implementation();
    }

    inline Interval operator/(Double first_argument, const Interval& second_argument) {
        return first_argument.implementation() / second_argument.implementation();
    }

    inline Interval operator/(const Interval& first_argument, Double second_argument) {
        return first_argument.implementation() / second_argument.implementation();
    }

    inline Interval operator/(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.implementation() / second_argument.implementation();
    }

    inline Interval abs(const Interval& argument) {
        return boost::numeric::abs(argument.implementation());
    }

    inline Interval sqrt(const Interval& argument) {
        return boost::numeric::sqrt(argument.implementation());
    }
    
    inline const Interval& conj(const Interval& argument) {return argument;}
    
    inline const Interval& conj(const Interval& argument) {return argument;}
    
    inline Interval imag(const Interval& argument) {return 0.0;}
    
    inline Interval abs2(const Interval& argument) {return argument.squaredNorm();}
}

#endif
