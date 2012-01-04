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

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>

#include <boost/numeric/interval.hpp>

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Common/Convertible.hpp>
#include <OpenSolid/Common/Repr.hpp>

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

    class Interval : public Convertible<Interval>
    {
    private:
        BoostInterval _value;
    public:
        Interval();
        Interval(double argument);
        Interval(double lower, double upper);
        Interval(const BoostInterval& argument);
        
        const BoostInterval& value() const;
        
        double lower() const;
        double upper() const;
        double median() const;
        double width() const;

        double clamp(double argument) const;
        Interval clamp(const Interval& argument) const;
        double interpolated(double argument) const;
        Interval interpolated(const Interval& argument) const;
        double random() const;
        
        Interval squared() const;
        
        bool isEmpty() const;
        bool isSingleton() const;
        
        std::pair<Interval, Interval> bisected() const;
        
        Interval hull(const Interval& argument) const;
        Interval intersection(const Interval& argument) const;
        
        bool contains(double argument, double tolerance = 1e-12) const;
        bool strictlyContains(double argument, double tolerance = 1e-12) const;

        bool contains(const Interval& argument, double tolerance = 1e-12) const;
        bool strictlyContains(const Interval& argument, double tolerance = 1e-12) const;

        bool overlaps(const Interval& argument, double tolerance = 1e-12) const;
        bool strictlyOverlaps(const Interval& argument, double tolerance = 1e-12) const;
        
        Interval& operator+=(double argument);
        Interval& operator+=(const Interval& argument);
        Interval& operator-=(double argument);
        Interval& operator-=(const Interval& argument);
        Interval& operator*=(double argument);
        Interval& operator*=(const Interval& argument);
        Interval& operator/=(double argument);
        Interval& operator/=(const Interval& argument);
        
        static Interval Hull(double first_argument, double second_argument);
        static Interval Empty();
        static Interval Whole();
    };

    template <>
    struct Bounds<Interval>
    {
        typedef Interval Type;

        const Interval& operator()(const Interval& argument) const;
    };

    template <>
    struct Repr<Interval>
    {
        OPENSOLID_CORE_EXPORT std::string operator()(const Interval& argument) const;
    };

    bool operator==(double first_argument, const Interval& second_argument);
    bool operator==(const Interval& first_argument, double second_argument);
    bool operator==(const Interval& first_argument, const Interval& second_argument);

    bool operator!=(double first_argument, const Interval& second_argument);
    bool operator!=(const Interval& first_argument, double second_argument);
    bool operator!=(const Interval& first_argument, const Interval& second_argument);

    bool operator<(double first_argument, const Interval& second_argument);
    bool operator<(const Interval& first_argument, double second_argument);
    bool operator<(const Interval& first_argument, const Interval& second_argument);

    bool operator>(double first_argument, const Interval& second_argument);
    bool operator>(const Interval& first_argument, double second_argument);
    bool operator>(const Interval& first_argument, const Interval& second_argument);

    bool operator<=(double first_argument, const Interval& second_argument);
    bool operator<=(const Interval& first_argument, double second_argument);
    bool operator<=(const Interval& first_argument, const Interval& second_argument);

    bool operator>=(double first_argument, const Interval& second_argument);
    bool operator>=(const Interval& first_argument, double second_argument);
    bool operator>=(const Interval& first_argument, const Interval& second_argument);
        
    Interval operator-(const Interval& argument);

    Interval operator+(double first_argument, const Interval& second_argument);
    Interval operator+(const Interval& first_argument, double second_argument);
    Interval operator+(const Interval& first_argument, const Interval& second_argument);

    Interval operator-(double first_argument, const Interval& second_argument);
    Interval operator-(const Interval& first_argument, double second_argument);
    Interval operator-(const Interval& first_argument, const Interval& second_argument);

    Interval operator*(double first_argument, const Interval& second_argument);
    Interval operator*(const Interval& first_argument, double second_argument);
    Interval operator*(const Interval& first_argument, const Interval& second_argument);

    Interval operator/(double first_argument, const Interval& second_argument);
    Interval operator/(const Interval& first_argument, double second_argument);
    Interval operator/(const Interval& first_argument, const Interval& second_argument);

    Interval abs(const Interval& argument);
    Interval sqrt(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval sin(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval cos(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval tan(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval asin(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval acos(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval atan(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval atan2(const Interval& y, const Interval& x);
    OPENSOLID_CORE_EXPORT Interval exp(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval log(const Interval& argument);
    OPENSOLID_CORE_EXPORT Interval pow(const Interval& base, int exponent);
    OPENSOLID_CORE_EXPORT Interval pow(const Interval& base, double exponent);
    OPENSOLID_CORE_EXPORT Interval pow(const Interval& base, const Interval& exponent);

    const Interval& conj(const Interval& argument);
    const Interval& real(const Interval& argument);
    Interval imag(const Interval& argument);
    Interval abs2(const Interval& argument);

    OPENSOLID_CORE_EXPORT std::ostream& operator<<(std::ostream& stream, const Interval& argument);
}

////////// Implementation //////////

#include <OpenSolid/Scalar/double.hpp>

namespace OpenSolid
{
    inline Interval Bounds<int>::operator()(int argument) const {return Interval(argument);}

    inline Interval Bounds<double>::operator()(double argument) const {return Interval(argument);}

    inline Interval::Interval() : _value(BoostInterval::empty()) {}
    
    inline Interval::Interval(double argument) : _value(argument) {}

    inline Interval::Interval(double lower, double upper) : _value(lower, upper) {}

    inline Interval::Interval(const BoostInterval& argument) : _value(argument) {}
        
    inline const BoostInterval& Interval::value() const {return _value;}
    
    inline double Interval::lower() const {return value().lower();}

    inline double Interval::upper() const {return value().upper();}
    
    inline double Interval::median() const {return boost::numeric::median(value());}
    
    inline double Interval::width() const {return boost::numeric::width(value());}

    inline double Interval::clamp(double argument) const {
        return argument <= lower() ? lower() : (argument <= upper() ? argument : upper());
    }

    inline Interval Interval::clamp(const Interval& argument) const {
        return Interval(clamp(argument.lower()), clamp(argument.upper()));
    }

    inline double Interval::interpolated(double argument) const {
        return lower() + argument * width();
    }

    inline Interval Interval::interpolated(const Interval& argument) const {
        return lower() + argument * width();
    }

    inline double Interval::random() const {return lower() + rand() * width() / RAND_MAX;}

    inline Interval Interval::squared() const {return boost::numeric::square(value());}
    
    inline bool Interval::isEmpty() const {return boost::numeric::empty(value());}
    
    inline bool Interval::isSingleton() const {return boost::numeric::singleton(value());}
    
    inline std::pair<Interval, Interval> Interval::bisected() const {
        double mid = median();
        return std::make_pair(Interval(lower(), mid), Interval(mid, upper()));
    }
    
    inline Interval Interval::hull(const Interval& argument) const {
        return boost::numeric::hull(value(), argument.value());
    }

    inline Interval Interval::intersection(const Interval& argument) const {
        return boost::numeric::intersect(value(), argument.value());
    }
        
    inline bool Interval::contains(double argument, double tolerance) const {
        return argument >= lower() - tolerance && argument <= upper() + tolerance;
    }

    inline bool Interval::strictlyContains(double argument, double tolerance) const {
        return argument > lower() + tolerance && argument < upper() - tolerance;
    }

    inline bool Interval::contains(const Interval& argument, double tolerance) const {
        return argument.lower() >= lower() - tolerance && argument.upper() <= upper() + tolerance;
    }

    inline bool Interval::strictlyContains(const Interval& argument, double tolerance) const {
        return argument.lower() > lower() + tolerance && argument.upper() < upper() - tolerance;
    }

    inline bool Interval::overlaps(const Interval& argument, double tolerance) const {
        return argument.lower() <= upper() + tolerance && argument.upper() >= lower() - tolerance;
    }

    inline bool Interval::strictlyOverlaps(const Interval& argument, double tolerance) const {
        return argument.lower() < upper() - tolerance && argument.upper() > lower() + tolerance;
    }

    inline Interval& Interval::operator+=(double argument) {
        _value += argument;
        return *this;
    }

    inline Interval& Interval::operator+=(const Interval& argument) {
        _value += argument.value();
        return *this;
    }

    inline Interval& Interval::operator-=(double argument) {
        _value -= argument;
        return *this;
    }

    inline Interval& Interval::operator-=(const Interval& argument) {
        _value -= argument.value();
        return *this;
    }

    inline Interval& Interval::operator*=(double argument) {
        _value -= argument;
        return *this;
    }

    inline Interval& Interval::operator*=(const Interval& argument) {
        _value -= argument.value();
        return *this;
    }

    inline Interval& Interval::operator/=(double argument) {
        _value /= argument;
        return *this;
    }

    inline Interval& Interval::operator/=(const Interval& argument) {
        _value /= argument.value();
        return *this;
    }
    
    inline Interval Interval::Hull(double first_argument, double second_argument) {
        return Interval(min(first_argument, second_argument), max(first_argument, second_argument));
    }

    inline Interval Interval::Empty() {return BoostInterval::empty();}
    
    inline Interval Interval::Whole() {return BoostInterval::whole();}
    
    inline const Interval& Bounds<Interval>::operator()(const Interval& argument) const {
        return argument;
    }

    inline bool operator==(double first_argument, const Interval& second_argument) {
        return first_argument == second_argument.lower() &&
            first_argument == second_argument.upper();
    }

    inline bool operator==(const Interval& first_argument, double second_argument) {
        return first_argument.lower() == second_argument &&
            first_argument.upper() == second_argument;
    }

    inline bool operator==(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() == second_argument.lower() &&
            first_argument.upper() == second_argument.upper();
    }

    inline bool operator!=(double first_argument, const Interval& second_argument) {
        return !(first_argument == second_argument);
    }

    inline bool operator!=(const Interval& first_argument, double second_argument) {
        return !(first_argument == second_argument);
    }

    inline bool operator!=(const Interval& first_argument, const Interval& second_argument) {
        return !(first_argument == second_argument);
    }

    inline bool operator<(double first_argument, const Interval& second_argument) {
        return first_argument < second_argument.lower() ||
            (first_argument == second_argument.lower() &&
            first_argument < second_argument.upper());
    }

    inline bool operator<(const Interval& first_argument, double second_argument) {
        return first_argument.lower() < second_argument;
    }

    inline bool operator<(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.lower() < second_argument.lower() ||
            (first_argument.lower() == second_argument.lower() &&
            first_argument.upper() < second_argument.upper());
    }

    inline bool operator>(double first_argument, const Interval& second_argument) {
        return second_argument < first_argument;
    }

    inline bool operator>(const Interval& first_argument, double second_argument) {
        return second_argument < first_argument;
    }

    inline bool operator>(const Interval& first_argument, const Interval& second_argument) {
        return second_argument < first_argument;
    }

    inline bool operator<=(double first_argument, const Interval& second_argument) {
        return !(second_argument < first_argument);
    }

    inline bool operator<=(const Interval& first_argument, double second_argument) {
        return !(second_argument < first_argument);
    }

    inline bool operator<=(const Interval& first_argument, const Interval& second_argument) {
        return !(second_argument < first_argument);
    }

    inline bool operator>=(double first_argument, const Interval& second_argument) {
        return !(first_argument < second_argument);
    }

    inline bool operator>=(const Interval& first_argument, double second_argument) {
        return !(first_argument < second_argument);
    }

    inline bool operator>=(const Interval& first_argument, const Interval& second_argument) {
        return !(first_argument < second_argument);
    }

    inline Interval operator-(const Interval& argument) {return -argument.value();}

    inline Interval operator+(double first_argument, const Interval& second_argument) {
        return first_argument + second_argument.value();
    }

    inline Interval operator+(const Interval& first_argument, double second_argument) {
        return first_argument.value() + second_argument;
    }

    inline Interval operator+(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.value() + second_argument.value();
    }

    inline Interval operator-(double first_argument, const Interval& second_argument) {
        return first_argument - second_argument.value();
    }

    inline Interval operator-(const Interval& first_argument, double second_argument) {
        return first_argument.value() - second_argument;
    }

    inline Interval operator-(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.value() - second_argument.value();
    }

    inline Interval operator*(double first_argument, const Interval& second_argument) {
        return first_argument * second_argument.value();
    }

    inline Interval operator*(const Interval& first_argument, double second_argument) {
        return first_argument.value() * second_argument;
    }

    inline Interval operator*(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.value() * second_argument.value();
    }

    inline Interval operator/(double first_argument, const Interval& second_argument) {
        return first_argument / second_argument.value();
    }

    inline Interval operator/(const Interval& first_argument, double second_argument) {
        return first_argument.value() / second_argument;
    }

    inline Interval operator/(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.value() / second_argument.value();
    }

    inline Interval abs(const Interval& argument) {
        return boost::numeric::abs(argument.value());
    }

    inline Interval sqrt(const Interval& argument) {
        return boost::numeric::sqrt(argument.value());
    }
    
    inline const Interval& conj(const Interval& argument) {return argument;}
    
    inline const Interval& real(const Interval& argument) {return argument;}
    
    inline Interval imag(const Interval& argument) {return 0.0;}
    
    inline Interval abs2(const Interval& argument) {return argument.squared();}
}

#include <OpenSolid/Scalar/Comparison.hpp>

#endif
