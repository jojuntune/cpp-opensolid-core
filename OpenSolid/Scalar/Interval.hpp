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
#include <OpenSolid/Scalar/Double.hpp>

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

    struct BoostIntervalConstructionTag
    {
    };
    
    class Interval
    {
    private:
        BoostInterval _implementation;
    public:
        typedef Interval Bounds;
        
        Interval();
        Interval(double argument);
        Interval(Double argument);
        Interval(Double lower, Double upper);
        Interval(const BoostInterval& argument, BoostIntervalConstructionTag);
        
        const BoostInterval& implementation() const;
        
        Double lower() const;
        Double upper() const;
        Double median() const;
        Double width() const;
        
        Interval squared() const;
        
        bool isEmpty() const;
        bool isSingleton() const;
        
        Interval bounds() const;
        std::size_t hashValue() const;
        
        std::pair<Interval, Interval> bisected() const;
        
        Interval hull(const Interval& argument) const;
        Interval intersection(const Interval& argument) const;
        
        bool isZero(Double precision = OPENSOLID_PRECISION) const;
        
        bool isEqualTo(
            double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isEqualTo(
            Double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isEqualTo(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isLessThan(
            double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isLessThan(
            Double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isLessThan(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isGreaterThan(
            double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isGreaterThan(
            Double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isGreaterThan(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isLessThanOrEqualTo(
            double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isLessThanOrEqualTo(
            Double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isLessThanOrEqualTo(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isGreaterThanOrEqualTo(
            double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isGreaterThanOrEqualTo(
            Double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool isGreaterThanOrEqualTo(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool overlaps(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool strictlyOverlaps(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool contains(
            double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool contains(
            Double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool contains(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool strictlyContains(
            double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool strictlyContains(
            Double argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        bool strictlyContains(
            const Interval& argument,
            Double precision = OPENSOLID_PRECISION
        ) const;
        
        Interval& operator+=(double argument);
        Interval& operator+=(Double argument);
        Interval& operator+=(const Interval& argument);
        Interval& operator-=(double argument);
        Interval& operator-=(Double argument);
        Interval& operator-=(const Interval& argument);
        Interval& operator*=(double argument);
        Interval& operator*=(Double argument);
        Interval& operator*=(const Interval& argument);
        Interval& operator/=(double argument);
        Interval& operator/=(Double argument);
        Interval& operator/=(const Interval& argument);
        
        static Interval Empty();
        static Interval Whole();
    };

    bool operator==(double first_argument, const Interval& second_argument);
    bool operator==(Double first_argument, const Interval& second_argument);
    bool operator==(const Interval& first_argument, double second_argument);
    bool operator==(const Interval& first_argument, Double second_argument);
    bool operator==(const Interval& first_argument, const Interval& second_argument);

    bool operator!=(double first_argument, const Interval& second_argument);
    bool operator!=(Double first_argument, const Interval& second_argument);
    bool operator!=(const Interval& first_argument, double second_argument);
    bool operator!=(const Interval& first_argument, Double second_argument);
    bool operator!=(const Interval& first_argument, const Interval& second_argument);

    bool operator<(double first_argument, const Interval& second_argument);
    bool operator<(Double first_argument, const Interval& second_argument);
    bool operator<(const Interval& first_argument, double second_argument);
    bool operator<(const Interval& first_argument, Double second_argument);
    bool operator<(const Interval& first_argument, const Interval& second_argument);

    bool operator>(double first_argument, const Interval& second_argument);
    bool operator>(Double first_argument, const Interval& second_argument);
    bool operator>(const Interval& first_argument, double second_argument);
    bool operator>(const Interval& first_argument, Double second_argument);
    bool operator>(const Interval& first_argument, const Interval& second_argument);

    bool operator<=(double first_argument, const Interval& second_argument);
    bool operator<=(Double first_argument, const Interval& second_argument);
    bool operator<=(const Interval& first_argument, double second_argument);
    bool operator<=(const Interval& first_argument, Double second_argument);
    bool operator<=(const Interval& first_argument, const Interval& second_argument);

    bool operator>=(double first_argument, const Interval& second_argument);
    bool operator>=(Double first_argument, const Interval& second_argument);
    bool operator>=(const Interval& first_argument, double second_argument);
    bool operator>=(const Interval& first_argument, Double second_argument);
    bool operator>=(const Interval& first_argument, const Interval& second_argument);
        
    Interval operator-(const Interval& argument);

    Interval operator+(double first_argument, const Interval& second_argument);
    Interval operator+(Double first_argument, const Interval& second_argument);
    Interval operator+(const Interval& first_argument, double second_argument);
    Interval operator+(const Interval& first_argument, Double second_argument);
    Interval operator+(const Interval& first_argument, const Interval& second_argument);

    Interval operator-(double first_argument, const Interval& second_argument);
    Interval operator-(Double first_argument, const Interval& second_argument);
    Interval operator-(const Interval& first_argument, double second_argument);
    Interval operator-(const Interval& first_argument, Double second_argument);
    Interval operator-(const Interval& first_argument, const Interval& second_argument);

    Interval operator*(double first_argument, const Interval& second_argument);
    Interval operator*(Double first_argument, const Interval& second_argument);
    Interval operator*(const Interval& first_argument, double second_argument);
    Interval operator*(const Interval& first_argument, Double second_argument);
    Interval operator*(const Interval& first_argument, const Interval& second_argument);

    Interval operator/(double first_argument, const Interval& second_argument);
    Interval operator/(Double first_argument, const Interval& second_argument);
    Interval operator/(const Interval& first_argument, double second_argument);
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
    OPENSOLID_CORE_EXPORT Interval atan2(double x, const Interval& y);
    OPENSOLID_CORE_EXPORT Interval atan2(Double x, const Interval& y);
    OPENSOLID_CORE_EXPORT Interval atan2(const Interval& x, double y);
    OPENSOLID_CORE_EXPORT Interval atan2(const Interval& x, Double y);
    OPENSOLID_CORE_EXPORT Interval atan2(const Interval& x, const Interval& y);
    OPENSOLID_CORE_EXPORT Interval exp(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval log(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval pow(double base, const Interval& exponent);
    OPENSOLID_CORE_EXPORT Interval pow(Double base, const Interval& exponent);
    OPENSOLID_CORE_EXPORT Interval pow(const Interval& base, double exponent);
    OPENSOLID_CORE_EXPORT Interval pow(const Interval& base, Double exponent);
    OPENSOLID_CORE_EXPORT Interval pow(const Interval& base, const Interval& exponent);

    const Interval& conj(const Interval& argument);
    const Interval& real(const Interval& argument);
    Interval imag(const Interval& argument);
    Interval abs2(const Interval& argument);

    OPENSOLID_CORE_EXPORT std::ostream& operator<<(std::ostream& stream, const Interval& argument);
}

////////// Implementation //////////

namespace OpenSolid
{
    inline Interval Double::bounds() const {return *this;}
    
    inline Interval Double::hull(Double argument) const {
        return *this <= argument ? Interval(*this, argument) : Interval(argument, *this);
    }

    inline Interval::Interval() : _implementation() {}
    
    inline Interval::Interval(double argument) : _implementation(argument) {}

    inline Interval::Interval(Double argument) : _implementation(argument.implementation()) {}

    inline Interval::Interval(Double lower, Double upper) :
        _implementation(lower.implementation(), upper.implementation()) {}

    inline Interval::Interval(const BoostInterval& argument, BoostIntervalConstructionTag) :
        _implementation(argument) {}
        
    inline const BoostInterval& Interval::implementation() const {return _implementation;}
    
    inline Double Interval::lower() const {return implementation().lower();}

    inline Double Interval::upper() const {return implementation().upper();}
    
    inline Double Interval::median() const {return boost::numeric::median(implementation());}
    
    inline Double Interval::width() const {return boost::numeric::width(implementation());}

    inline Interval Interval::squared() const {
        return Interval(boost::numeric::square(implementation()), BoostIntervalConstructionTag());
    }
    
    inline bool Interval::isEmpty() const {return boost::numeric::empty(implementation());}
    
    inline bool Interval::isSingleton() const {return boost::numeric::singleton(implementation());}
    
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
        return Interval(
            boost::numeric::hull(implementation(), argument.implementation()),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval Interval::intersection(const Interval& argument) const {
        return Interval(
            boost::numeric::intersect(implementation(), argument.implementation()),
            BoostIntervalConstructionTag()
        );
    }
    
    inline bool Interval::isZero(Double precision) const {
        return lower().isZero(precision) && upper().isZero(precision);
    }

    inline bool Interval::isEqualTo(double argument, Double precision) const {
        return lower().isEqualTo(argument, precision) &&
            upper().isEqualTo(argument, precision);
    }

    inline bool Interval::isEqualTo(Double argument, Double precision) const {
        return lower().isEqualTo(argument, precision) &&
            upper().isEqualTo(argument, precision);
    }

    inline bool Interval::isEqualTo(const Interval& argument, Double precision) const {
        return lower().isEqualTo(argument.upper(), precision) &&
            upper().isEqualTo(argument.lower(), precision);
    }

    inline bool Interval::isLessThan(double argument, Double precision) const {
        return upper().isLessThan(argument, precision);
    }

    inline bool Interval::isLessThan(Double argument, Double precision) const {
        return upper().isLessThan(argument, precision);
    }

    inline bool Interval::isLessThan(const Interval& argument, Double precision) const {
        return upper().isLessThan(argument.lower(), precision);
    }

    inline bool Interval::isGreaterThan(double argument, Double precision) const {
        return lower().isGreaterThan(argument, precision);
    }

    inline bool Interval::isGreaterThan(Double argument, Double precision) const {
        return lower().isGreaterThan(argument, precision);
    }

    inline bool Interval::isGreaterThan(const Interval& argument, Double precision) const {
        return lower().isGreaterThan(argument.upper(), precision);
    }

    inline bool Interval::isLessThanOrEqualTo(double argument, Double precision) const {
        return upper().isLessThanOrEqualTo(argument, precision);
    }

    inline bool Interval::isLessThanOrEqualTo(Double argument, Double precision) const {
        return upper().isLessThanOrEqualTo(argument, precision);
    }

    inline bool Interval::isLessThanOrEqualTo(const Interval& argument, Double precision) const {
        return upper().isLessThanOrEqualTo(argument.lower(), precision);
    }

    inline bool Interval::isGreaterThanOrEqualTo(double argument, Double precision) const {
        return lower().isGreaterThanOrEqualTo(argument, precision);
    }

    inline bool Interval::isGreaterThanOrEqualTo(Double argument, Double precision) const {
        return lower().isGreaterThanOrEqualTo(argument, precision);
    }

    inline bool Interval::isGreaterThanOrEqualTo(const Interval& argument, Double precision) const {
        return lower().isGreaterThanOrEqualTo(argument.upper(), precision);
    }
    
    inline bool Interval::overlaps(const Interval& argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument.upper(), precision) &&
            upper().isGreaterThanOrEqualTo(argument.lower(), precision);
    }
    
    inline bool Interval::strictlyOverlaps(const Interval& argument, Double precision) const {
        return lower().isLessThan(argument.upper(), precision) &&
            upper().isGreaterThan(argument.lower(), precision);
    }
    
    inline bool Interval::contains(double argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument, precision) &&
            upper().isGreaterThanOrEqualTo(argument, precision);
    }
    
    inline bool Interval::contains(Double argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument, precision) &&
            upper().isGreaterThanOrEqualTo(argument, precision);
    }
    
    inline bool Interval::contains(const Interval& argument, Double precision) const {
        return lower().isLessThanOrEqualTo(argument.lower(), precision) &&
            upper().isGreaterThanOrEqualTo(argument.upper(), precision);
    }
    
    inline bool Interval::strictlyContains(double argument, Double precision) const {
        return lower().isLessThan(argument, precision) &&
            upper().isGreaterThan(argument, precision);
    }
    
    inline bool Interval::strictlyContains(Double argument, Double precision) const {
        return lower().isLessThan(argument, precision) &&
            upper().isGreaterThan(argument, precision);
    }
    
    inline bool Interval::strictlyContains(const Interval& argument, Double precision) const {
        return lower().isLessThan(argument.lower(), precision) &&
            upper().isGreaterThan(argument.upper(), precision);
    }

    inline Interval& Interval::operator+=(double argument) {
        _implementation += argument;
        return *this;
    }

    inline Interval& Interval::operator+=(Double argument) {
        _implementation += argument.implementation();
        return *this;
    }

    inline Interval& Interval::operator+=(const Interval& argument) {
        _implementation += argument.implementation();
        return *this;
    }

    inline Interval& Interval::operator-=(double argument) {
        _implementation -= argument;
        return *this;
    }

    inline Interval& Interval::operator-=(Double argument) {
        _implementation -= argument.implementation();
        return *this;
    }

    inline Interval& Interval::operator-=(const Interval& argument) {
        _implementation -= argument.implementation();
        return *this;
    }

    inline Interval& Interval::operator*=(double argument) {
        _implementation -= argument;
        return *this;
    }

    inline Interval& Interval::operator*=(Double argument) {
        _implementation -= argument.implementation();
        return *this;
    }

    inline Interval& Interval::operator*=(const Interval& argument) {
        _implementation -= argument.implementation();
        return *this;
    }

    inline Interval& Interval::operator/=(double argument) {
        _implementation /= argument;
        return *this;
    }

    inline Interval& Interval::operator/=(Double argument) {
        _implementation /= argument.implementation();
        return *this;
    }

    inline Interval& Interval::operator/=(const Interval& argument) {
        _implementation /= argument.implementation();
        return *this;
    }
    
    inline Interval Interval::Empty() {
        return Interval(BoostInterval::empty(), BoostIntervalConstructionTag());
    }
    
    inline Interval Interval::Whole() {
        return Interval(BoostInterval::whole(), BoostIntervalConstructionTag());
    }

    inline bool operator==(double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() &&
            first_argument == second_argument.upper();
    }

    inline bool operator==(Double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() &&
            first_argument == second_argument.upper();
    }

    inline bool operator==(const Interval& first_argument, double second_argument) {
        return first_argument.lower() == second_argument &&
            first_argument.upper() == second_argument;
    }

    inline bool operator==(const Interval& first_argument, Double second_argument) {
        return first_argument.lower() == second_argument &&
            first_argument.upper() == second_argument;
    }

    inline bool operator==(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() &&
            first_argument.upper() == second_argument.upper();
    }

    inline bool operator!=(double first_argument, const Interval& second_argument) {
        return first_argument != second_argument.lower() ||
            first_argument != second_argument.upper();
    }

    inline bool operator!=(Double first_argument, const Interval& second_argument) {
        return first_argument != second_argument.lower() ||
            first_argument != second_argument.upper();
    }

    inline bool operator!=(const Interval& first_argument, double second_argument) {
        return first_argument.lower() != second_argument ||
            first_argument.upper() != second_argument;
    }

    inline bool operator!=(const Interval& first_argument, Double second_argument) {
        return first_argument.lower() != second_argument ||
            first_argument.upper() != second_argument;
    }

    inline bool operator!=(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() != second_argument.lower() ||
            first_argument.upper() != second_argument.upper();
    }

    inline bool operator<(double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() ?
            first_argument < second_argument.upper() :
            first_argument < second_argument.lower();
    }

    inline bool operator<(Double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() ?
            first_argument < second_argument.upper() :
            first_argument < second_argument.lower();
    }

    inline bool operator<(const Interval& first_argument, double second_argument) {
        return first_argument.lower() == second_argument ?
            first_argument.upper() < second_argument :
            first_argument.lower() < second_argument;
    }

    inline bool operator<(const Interval& first_argument, Double second_argument) {
        return first_argument.lower() == second_argument ?
            first_argument.upper() < second_argument :
            first_argument.lower() < second_argument;
    }

    inline bool operator<(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() ?
            first_argument.upper() < second_argument.upper() :
            first_argument.lower() < second_argument.lower();
    }

    inline bool operator>(double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() ?
            first_argument > second_argument.upper() :
            first_argument > second_argument.lower();
    }

    inline bool operator>(Double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() ?
            first_argument > second_argument.upper() :
            first_argument > second_argument.lower();
    }

    inline bool operator>(const Interval& first_argument, double second_argument) {
        return first_argument.lower() == second_argument ?
            first_argument.upper() > second_argument :
            first_argument.lower() > second_argument;
    }

    inline bool operator>(const Interval& first_argument, Double second_argument) {
        return first_argument.lower() == second_argument ?
            first_argument.upper() > second_argument :
            first_argument.lower() > second_argument;
    }

    inline bool operator>(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() ?
            first_argument.upper() > second_argument.upper() :
            first_argument.lower() > second_argument.lower();
    }

    inline bool operator<=(double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() ?
            first_argument <= second_argument.upper() :
            first_argument <= second_argument.lower();
    }

    inline bool operator<=(Double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() ?
            first_argument <= second_argument.upper() :
            first_argument <= second_argument.lower();
    }

    inline bool operator<=(const Interval& first_argument, double second_argument) {
        return first_argument.lower() == second_argument ?
            first_argument.upper() <= second_argument :
            first_argument.lower() <= second_argument;
    }

    inline bool operator<=(const Interval& first_argument, Double second_argument) {
        return first_argument.lower() == second_argument ?
            first_argument.upper() <= second_argument :
            first_argument.lower() <= second_argument;
    }

    inline bool operator<=(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() ?
            first_argument.upper() <= second_argument.upper() :
            first_argument.lower() <= second_argument.lower();
    }

    inline bool operator>=(double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() ?
            first_argument >= second_argument.upper() :
            first_argument >= second_argument.lower();
    }

    inline bool operator>=(Double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() ?
            first_argument >= second_argument.upper() :
            first_argument >= second_argument.lower();
    }

    inline bool operator>=(const Interval& first_argument, double second_argument) {
        return first_argument.lower() == second_argument ?
            first_argument.upper() >= second_argument :
            first_argument.lower() >= second_argument;
    }

    inline bool operator>=(const Interval& first_argument, Double second_argument) {
        return first_argument.lower() == second_argument ?
            first_argument.upper() >= second_argument :
            first_argument.lower() >= second_argument;
    }

    inline bool operator>=(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() ?
            first_argument.upper() >= second_argument.upper() :
            first_argument.lower() >= second_argument.lower();
    }

    inline Interval operator-(const Interval& argument) {
        return Interval(-argument.implementation(), BoostIntervalConstructionTag());
    }

    inline Interval operator+(double first_argument, const Interval& second_argument) {
        return Interval(
            first_argument + second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator+(Double first_argument, const Interval& second_argument) {
        return Interval(
            first_argument.implementation() + second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator+(const Interval& first_argument, double second_argument) {
        return Interval(
            first_argument.implementation() + second_argument,
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator+(const Interval& first_argument, Double second_argument) {
        return Interval(
            first_argument.implementation() + second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator+(const Interval& first_argument, const Interval& second_argument) {
        return Interval(
            first_argument.implementation() + second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator-(double first_argument, const Interval& second_argument) {
        return Interval(
            first_argument - second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator-(Double first_argument, const Interval& second_argument) {
        return Interval(
            first_argument.implementation() - second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator-(const Interval& first_argument, double second_argument) {
        return Interval(
            first_argument.implementation() - second_argument,
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator-(const Interval& first_argument, Double second_argument) {
        return Interval(
            first_argument.implementation() - second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator-(const Interval& first_argument, const Interval& second_argument) {
        return Interval(
            first_argument.implementation() - second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator*(double first_argument, const Interval& second_argument) {
        return Interval(
            first_argument * second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator*(Double first_argument, const Interval& second_argument) {
        return Interval(
            first_argument.implementation() * second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator*(const Interval& first_argument, double second_argument) {
        return Interval(
            first_argument.implementation() * second_argument,
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator*(const Interval& first_argument, Double second_argument) {
        return Interval(
            first_argument.implementation() * second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator*(const Interval& first_argument, const Interval& second_argument) {
        return Interval(
            first_argument.implementation() * second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator/(double first_argument, const Interval& second_argument) {
        return Interval(
            first_argument / second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator/(Double first_argument, const Interval& second_argument) {
        return Interval(
            first_argument.implementation() / second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator/(const Interval& first_argument, double second_argument) {
        return Interval(
            first_argument.implementation() / second_argument,
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator/(const Interval& first_argument, Double second_argument) {
        return Interval(
            first_argument.implementation() / second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval operator/(const Interval& first_argument, const Interval& second_argument) {
        return Interval(
            first_argument.implementation() / second_argument.implementation(),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval abs(const Interval& argument) {
        return Interval(
            boost::numeric::abs(argument.implementation()),
            BoostIntervalConstructionTag()
        );
    }

    inline Interval sqrt(const Interval& argument) {
        return Interval(
            boost::numeric::sqrt(argument.implementation()),
            BoostIntervalConstructionTag()
        );
    }
    
    inline const Interval& conj(const Interval& argument) {return argument;}
    
    inline const Interval& real(const Interval& argument) {return argument;}
    
    inline Interval imag(const Interval& argument) {return 0.0;}
    
    inline Interval abs2(const Interval& argument) {return argument.squared();}
}

#endif
