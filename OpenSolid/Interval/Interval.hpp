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
#include <algorithm>
#include <limits>
#include <cmath>
#include <cassert>
#include <utility>

#include <boost/numeric/interval.hpp>
#include <boost/functional/hash.hpp>

namespace OpenSolid
{
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
    
    class Interval
    {
    private:
        BoostInterval _interval;
    public:
        Interval();
        Interval(double value);
        Interval(double lower, double upper);
        Interval(const Interval& other);
        Interval(const BoostInterval& interval);
        
        BoostInterval& interval();
        const BoostInterval& interval() const;
        
        double lower() const;
        double upper() const;
        double median() const;
        double width() const;
        bool empty() const;
        bool singleton() const;
        
        std::pair<Interval, Interval> bisected() const;
        Interval squared() const;
        
        bool overlap(double value, double tolerance = 0.0) const;
        bool overlap(const Interval& other, double tolerance = 0.0) const;
        bool contain(double value, double tolerance = 0.0) const;
        bool contain(const Interval& other, double tolerance = 0.0) const;
        
        Interval hull(double value) const;
        Interval hull(const Interval& other) const;
        Interval intersection(double value) const;
        Interval intersection(const Interval& other) const;
        
        Interval& operator+=(double argument);
        Interval& operator+=(const Interval& other);
        Interval& operator-=(double argument);
        Interval& operator-=(const Interval& other);
        Interval& operator*=(double argument);
        Interval& operator*=(const Interval& other);
        Interval& operator/=(double argument);
        Interval& operator/=(const Interval& other);
        
        static Interval Empty();
        static Interval Whole();
    };

    bool operator==(const Interval& first_argument, const Interval& second_argument);
    bool operator!=(const Interval& first_argument, const Interval& second_argument);
    bool operator<(const Interval& first_argument, const Interval& second_argument);
    bool operator>(const Interval& first_argument, const Interval& second_argument);
    
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
    OPENSOLID_EXPORT Interval sin(const Interval& argument);
    OPENSOLID_EXPORT Interval cos(const Interval& argument);
    OPENSOLID_EXPORT Interval tan(const Interval& argument);
    OPENSOLID_EXPORT Interval asin(const Interval& argument);
    OPENSOLID_EXPORT Interval acos(const Interval& argument);
    OPENSOLID_EXPORT Interval atan(const Interval& argument);
    OPENSOLID_EXPORT Interval atan2(const Interval& y, const Interval& x);
    OPENSOLID_EXPORT Interval exp(const Interval& argument);
    OPENSOLID_EXPORT Interval log(const Interval& argument);
    OPENSOLID_EXPORT Interval pow(const Interval& base, const Interval& exponent);

    OPENSOLID_EXPORT std::ostream& operator<<(std::ostream& stream, const Interval& argument);
}
   
////////// Implementation //////////

#include "Traits.hpp"

namespace OpenSolid
{
    inline Interval Traits<int>::bounds(int argument) {return Interval(argument);}
    
    inline Interval Traits<double>::bounds(double argument) {return Interval(argument);}

    inline const Interval& Traits<Interval>::bounds(const Interval& argument) {return argument;}
    
    inline std::size_t Traits<Interval>::hash(const Interval& argument) {
        std::size_t result = 0;
        boost::hash_combine(result, argument.lower());
        boost::hash_combine(result, argument.upper());
        return result;
    }
    
    inline Interval::Interval(const BoostInterval& interval) : _interval(interval) {}
        
    inline Interval::Interval() : _interval() {}

    inline Interval::Interval(double value) : _interval(value) {}

    inline Interval::Interval(double lower, double upper) : _interval(lower, upper) {}

    inline Interval::Interval(const Interval& other) : _interval(other._interval) {}
        
    inline BoostInterval& Interval::interval() {return _interval;}
    
    inline const BoostInterval& Interval::interval() const {return _interval;}
    
    inline double Interval::lower() const {return interval().lower();}

    inline double Interval::upper() const {return interval().upper();}
    
    inline double Interval::median() const {return boost::numeric::median(interval());}
    
    inline double Interval::width() const {return boost::numeric::width(interval());}
    
    inline bool Interval::empty() const {return boost::numeric::empty(interval());}
    
    inline bool Interval::singleton() const {return boost::numeric::singleton(interval());}
    
    inline std::pair<Interval, Interval> Interval::bisected() const {
        double mid = median();
        return std::make_pair(Interval(lower(), mid), Interval(mid, upper()));
    }
    
    inline Interval Interval::squared() const {return square(interval());}
    
    inline bool Interval::overlap(double value, double tolerance) const {
        return lower() - tolerance <= value && value <= upper() + tolerance;
    }
    
    inline bool Interval::overlap(const Interval& other, double tolerance) const {
        return lower() - tolerance <= other.upper() && other.lower() <= upper() + tolerance;
    }
    
    inline bool Interval::contain(double value, double tolerance) const {
        return lower() - tolerance <= value && value <= upper() + tolerance;
    }
    
    inline bool Interval::contain(const Interval& other, double tolerance) const {
        return lower() - tolerance <= other.lower() && other.upper() <= upper() + tolerance;
    }
        
    inline Interval Interval::hull(double value) const {
        return boost::numeric::hull(interval(), value);
    }
    
    inline Interval Interval::hull(const Interval& other) const {
        return boost::numeric::hull(interval(), other.interval());
    }
    
    inline Interval Interval::intersection(const Interval& other) const {
        return boost::numeric::intersect(interval(), other.interval());
    }

    inline Interval& Interval::operator+=(double argument) {
        interval() += argument;
        return *this;
    }

    inline Interval& Interval::operator+=(const Interval& other) {
        interval() += other.interval();
        return *this;
    }

    inline Interval& Interval::operator-=(double argument) {
        interval() -= argument;
        return *this;
    }

    inline Interval& Interval::operator-=(const Interval& other) {
        interval() -= other.interval();
        return *this;
    }

    inline Interval& Interval::operator*=(double argument) {
        interval() *= argument;
        return *this;
    }

    inline Interval& Interval::operator*=(const Interval& other) {
        interval() *= other.interval();
        return *this;
    }

    inline Interval& Interval::operator/=(double argument) {
        interval() /= argument;
        return *this;
    }

    inline Interval& Interval::operator/=(const Interval& other) {
        interval() /= other.interval();
        return *this;
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
        if (first_argument.lower() == second_argument.lower()) {
            return first_argument.upper() < second_argument.upper();
        } else {
            return first_argument.lower() < second_argument.lower();
        }
    }
    
    inline bool operator>(const Interval& first_argument, const Interval& second_argument) {
        if (first_argument.lower() == second_argument.lower()) {
            return first_argument.upper() > second_argument.upper();
        } else {
            return first_argument.lower() > second_argument.lower();
        }
    }
        
    inline Interval operator-(const Interval& argument) {return -argument.interval();}

    inline Interval operator+(double first_argument, const Interval& second_argument) {
        return first_argument + second_argument.interval();
    }

    inline Interval operator+(const Interval& first_argument, double second_argument) {
        return first_argument.interval() + second_argument;
    }

    inline Interval operator+(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.interval() + second_argument.interval();
    }

    inline Interval operator-(double first_argument, const Interval& second_argument) {
        return first_argument - second_argument.interval();
    }

    inline Interval operator-(const Interval& first_argument, double second_argument) {
        return first_argument.interval() - second_argument;
    }

    inline Interval operator-(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.interval() - second_argument.interval();
    }

    inline Interval operator*(double first_argument, const Interval& second_argument) {
        return first_argument * second_argument.interval();
    }

    inline Interval operator*(const Interval& first_argument, double second_argument) {
        return first_argument.interval() * second_argument;
    }

    inline Interval operator*(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.interval() * second_argument.interval();
    }

    inline Interval operator/(double first_argument, const Interval& second_argument) {
        return first_argument / second_argument.interval();
    }

    inline Interval operator/(const Interval& first_argument, double second_argument) {
        return first_argument.interval() / second_argument;
    }

    inline Interval operator/(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.interval() / second_argument.interval();
    }

    inline Interval abs(const Interval& argument) {return abs(argument.interval());}

    inline Interval sqrt(const Interval& argument) {return sqrt(argument.interval());}
}

#endif
