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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/util/Zero.hpp>
#include <OpenSolid/util/Conversion.hpp>
#include <OpenSolid/Core/Bounds.hpp>

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <limits>
#include <algorithm>

namespace opensolid
{
    class Interval : public Convertible<Interval>
    {
    private:
        double m_lower;
        double m_upper;
    public:
        Interval();
        Interval(double argument);
        Interval(double lower, double upper);
        
        double lower() const;
        double upper() const;
        double median() const;
        double random() const;
        double width() const;

        double clamp(double argument) const;
        Interval clamp(Interval argument) const;
        double interpolated(double argument) const;
        Interval interpolated(Interval argument) const;
        
        Interval squared() const;
        
        bool isEmpty() const;
        bool isSingleton() const;
        
        std::pair<Interval, Interval> bisected() const;
        
        Interval hull(Interval argument) const;
        Interval intersection(Interval argument) const;
        
        bool contains(double argument, double tolerance = 1e-12) const;
        bool strictlyContains(double argument, double tolerance = 1e-12) const;

        bool contains(Interval argument, double tolerance = 1e-12) const;
        bool strictlyContains(Interval argument, double tolerance = 1e-12) const;

        bool overlaps(Interval argument, double tolerance = 1e-12) const;
        bool strictlyOverlaps(Interval argument, double tolerance = 1e-12) const;
        
        Interval& operator+=(double argument);
        Interval& operator+=(Interval argument);
        Interval& operator-=(double argument);
        Interval& operator-=(Interval argument);
        Interval& operator*=(double argument);
        Interval& operator/=(double argument);
        OPENSOLID_CORE_EXPORT Interval& operator*=(Interval argument);
        OPENSOLID_CORE_EXPORT Interval& operator/=(Interval argument);
        
        static Interval Hull(double first_argument, double second_argument);
        static Interval Empty();
        static Interval Whole();
    };

    bool operator==(double first_argument, Interval second_argument);
    bool operator==(Interval first_argument, double second_argument);
    bool operator==(Interval first_argument, Interval second_argument);

    bool operator!=(double first_argument, Interval second_argument);
    bool operator!=(Interval first_argument, double second_argument);
    bool operator!=(Interval first_argument, Interval second_argument);

    bool operator<(double first_argument, Interval second_argument);
    bool operator<(Interval first_argument, double second_argument);
    bool operator<(Interval first_argument, Interval second_argument);

    bool operator>(double first_argument, Interval second_argument);
    bool operator>(Interval first_argument, double second_argument);
    bool operator>(Interval first_argument, Interval second_argument);

    bool operator<=(double first_argument, Interval second_argument);
    bool operator<=(Interval first_argument, double second_argument);
    bool operator<=(Interval first_argument, Interval second_argument);

    bool operator>=(double first_argument, Interval second_argument);
    bool operator>=(Interval first_argument, double second_argument);
    bool operator>=(Interval first_argument, Interval second_argument);
    
    bool operator==(Interval interval, Zero zero);
    bool operator!=(Interval interval, Zero zero);
    bool operator<(Interval interval, Zero zero);
    bool operator>(Interval interval, Zero zero);
    bool operator<=(Interval interval, Zero zero);
    bool operator>=(Interval interval, Zero zero);
        
    Interval operator-(Interval argument);

    Interval operator+(double first_argument, Interval second_argument);
    Interval operator+(Interval first_argument, double second_argument);
    Interval operator+(Interval first_argument, Interval second_argument);

    Interval operator-(double first_argument, Interval second_argument);
    Interval operator-(Interval first_argument, double second_argument);
    Interval operator-(Interval first_argument, Interval second_argument);

    Interval operator*(double first_argument, Interval second_argument);
    Interval operator*(Interval first_argument, double second_argument);
    OPENSOLID_CORE_EXPORT Interval operator*(Interval first_argument, Interval second_argument);

    Interval operator/(Interval first_argument, double second_argument);
    OPENSOLID_CORE_EXPORT Interval operator/(double first_argument, Interval second_argument);
    OPENSOLID_CORE_EXPORT Interval operator/(Interval first_argument, Interval second_argument);

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
    OPENSOLID_CORE_EXPORT Interval pow(Interval base, int exponent);
    OPENSOLID_CORE_EXPORT Interval pow(Interval base, double exponent);
    OPENSOLID_CORE_EXPORT Interval pow(Interval base, Interval exponent);

    Interval conj(Interval argument);
    Interval real(Interval argument);
    Interval imag(Interval argument);
    Interval abs2(Interval argument);

    OPENSOLID_CORE_EXPORT std::ostream& operator<<(std::ostream& stream, Interval argument);
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct Bounds<Interval>
    {
        typedef Interval Type;

        Interval operator()(Interval argument) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Interval::Interval() :
        m_lower( std::numeric_limits<double>::infinity() ),
        m_upper( -std::numeric_limits<double>::infinity() ) {}
    
    inline Interval::Interval(double argument) : m_lower(argument), m_upper(argument) {}

    inline Interval::Interval(double lower, double upper) : m_lower(lower), m_upper(upper) {}
    
    inline double Interval::lower() const {return m_lower;}

    inline double Interval::upper() const {return m_upper;}
    
    inline double Interval::median() const {return lower() + 0.5 * (upper() - lower());}

    inline double Interval::random() const {return lower() + rand() * width() / RAND_MAX;}
    
    inline double Interval::width() const {return upper() - lower();}

    inline double Interval::clamp(double argument) const {
        return argument <= lower() ? lower() : (argument <= upper() ? argument : upper());
    }

    inline Interval Interval::clamp(Interval argument) const {
        return Interval(clamp(argument.lower()), clamp(argument.upper()));
    }

    inline double Interval::interpolated(double argument) const {
        return lower() + argument * width();
    }

    inline Interval Interval::interpolated(Interval argument) const {
        return lower() + argument * width();
    }

    inline Interval Interval::squared() const {
        if (lower() > 0.0) {
            return Interval(lower() * lower(), upper() * upper());
        } else if (upper() < 0.0) {
            return Interval(upper() * upper(), lower() * lower());
        } else if (-lower() < upper()) {
            return Interval(0.0, upper() * upper());
        } else {
            return Interval(0.0, lower() * lower());
        }
    }
    
    inline bool Interval::isEmpty() const {return lower() > upper();}
    
    inline bool Interval::isSingleton() const {return lower() == upper();}
    
    inline std::pair<Interval, Interval> Interval::bisected() const {
        double mid = median();
        return std::pair<Interval, Interval>(Interval(lower(), mid), Interval(mid, upper()));
    }
    
    inline Interval Interval::hull(Interval argument) const {
        return Interval(min(lower(), argument.lower()), max(upper(), argument.upper()));
    }

    inline Interval Interval::intersection(Interval argument) const {
        return Interval(max(lower(), argument.lower()), min(upper(), argument.upper()));
    }
        
    inline bool Interval::contains(double argument, double tolerance) const {
        return argument >= lower() - tolerance && argument <= upper() + tolerance;
    }

    inline bool Interval::strictlyContains(double argument, double tolerance) const {
        return argument > lower() + tolerance && argument < upper() - tolerance;
    }

    inline bool Interval::contains(Interval argument, double tolerance) const {
        return argument.lower() >= lower() - tolerance && argument.upper() <= upper() + tolerance;
    }

    inline bool Interval::strictlyContains(Interval argument, double tolerance) const {
        return argument.lower() > lower() + tolerance && argument.upper() < upper() - tolerance;
    }

    inline bool Interval::overlaps(Interval argument, double tolerance) const {
        return argument.lower() <= upper() + tolerance && argument.upper() >= lower() - tolerance;
    }

    inline bool Interval::strictlyOverlaps(Interval argument, double tolerance) const {
        return argument.lower() < upper() - tolerance && argument.upper() > lower() + tolerance;
    }

    inline Interval& Interval::operator+=(double argument) {
        m_lower += argument;
        m_upper += argument;
        return *this;
    }

    inline Interval& Interval::operator+=(Interval argument) {
        m_lower += argument.lower();
        m_upper += argument.upper();
        return *this;
    }

    inline Interval& Interval::operator-=(double argument) {
        m_lower -= argument;
        m_upper -= argument;
        return *this;
    }

    inline Interval& Interval::operator-=(Interval argument) {
        m_lower -= argument.upper();
        m_upper -= argument.lower();
        return *this;
    }

    inline Interval& Interval::operator*=(double argument) {
        if (argument >= 0.0) {
            m_lower *= argument;
            m_upper *= argument;
        } else {
            m_lower = m_upper * argument;
            m_upper = m_lower * argument;
        }
        return *this;
    }

    inline Interval& Interval::operator/=(double argument) {
        if (argument >= 0.0) {
            m_lower /= argument;
            m_upper /= argument;
        } else {
            m_lower = m_upper / argument;
            m_upper = m_lower / argument;
        }
        return *this;
    }
    
    inline Interval Interval::Hull(double first_argument, double second_argument) {
        return Interval(min(first_argument, second_argument), max(first_argument, second_argument));
    }

    inline Interval Interval::Empty() {
        double infinity = std::numeric_limits<double>::infinity();
        return Interval(infinity, -infinity);
    }
    
    inline Interval Interval::Whole() {
        double infinity = std::numeric_limits<double>::infinity();
        return Interval(-infinity, infinity);
    }

    inline bool operator==(double first_argument, Interval second_argument) {
        return first_argument == second_argument.lower() &&
            first_argument == second_argument.upper();
    }

    inline bool operator==(Interval first_argument, double second_argument) {
        return first_argument.lower() == second_argument &&
            first_argument.upper() == second_argument;
    }

    inline bool operator==(Interval first_argument, Interval second_argument) {
        return first_argument.lower() == second_argument.lower() &&
            first_argument.upper() == second_argument.upper();
    }

    inline bool operator!=(double first_argument, Interval second_argument) {
        return !(first_argument == second_argument);
    }

    inline bool operator!=(Interval first_argument, double second_argument) {
        return !(first_argument == second_argument);
    }

    inline bool operator!=(Interval first_argument, Interval second_argument) {
        return !(first_argument == second_argument);
    }

    inline bool operator<(double first_argument, Interval second_argument) {
        return first_argument < second_argument.lower() ||
            (first_argument == second_argument.lower() &&
            first_argument < second_argument.upper());
    }

    inline bool operator<(Interval first_argument, double second_argument) {
        return first_argument.lower() < second_argument;
    }

    inline bool operator<(Interval first_argument, Interval second_argument) {
        return first_argument.lower() < second_argument.lower() ||
            (first_argument.lower() == second_argument.lower() &&
            first_argument.upper() < second_argument.upper());
    }

    inline bool operator>(double first_argument, Interval second_argument) {
        return second_argument < first_argument;
    }

    inline bool operator>(Interval first_argument, double second_argument) {
        return second_argument < first_argument;
    }

    inline bool operator>(Interval first_argument, Interval second_argument) {
        return second_argument < first_argument;
    }

    inline bool operator<=(double first_argument, Interval second_argument) {
        return !(second_argument < first_argument);
    }

    inline bool operator<=(Interval first_argument, double second_argument) {
        return !(second_argument < first_argument);
    }

    inline bool operator<=(Interval first_argument, Interval second_argument) {
        return !(second_argument < first_argument);
    }

    inline bool operator>=(double first_argument, Interval second_argument) {
        return !(first_argument < second_argument);
    }

    inline bool operator>=(Interval first_argument, double second_argument) {
        return !(first_argument < second_argument);
    }

    inline bool operator>=(Interval first_argument, Interval second_argument) {
        return !(first_argument < second_argument);
    }

    inline bool operator==(Interval interval, Zero zero) {
        return interval.lower() >= -zero.precision() && interval.upper() <= zero.precision();
    }

    inline bool operator!=(Interval interval, Zero zero) {
        return interval.lower() > zero.precision() || interval.upper() < -zero.precision();
    }

    inline bool operator<(Interval interval, Zero zero) {
        return interval.upper() < -zero.precision();
    }

    inline bool operator>(Interval interval, Zero zero) {
        return interval.lower() > zero.precision();
    }

    inline bool operator<=(Interval interval, Zero zero) {
        return interval.upper() <= zero.precision();
    }

    inline bool operator>=(Interval interval, Zero zero) {
        return interval.lower() >= -zero.precision();
    }

    inline Interval operator-(Interval argument) {
        return Interval(-argument.upper(), -argument.lower());
    }

    inline Interval operator+(double first_argument, Interval second_argument) {
        return Interval(
            first_argument + second_argument.lower(),
            first_argument + second_argument.upper()
        );
    }

    inline Interval operator+(Interval first_argument, double second_argument) {
        return Interval(
            first_argument.lower() + second_argument,
            first_argument.upper() + second_argument
        );
    }

    inline Interval operator+(Interval first_argument, Interval second_argument) {
        return Interval(
            first_argument.lower() + second_argument.lower(),
            first_argument.upper() + second_argument.upper()
        );
    }

    inline Interval operator-(double first_argument, Interval second_argument) {
        return Interval(
            first_argument - second_argument.upper(),
            first_argument - second_argument.lower()
        );
    }

    inline Interval operator-(Interval first_argument, double second_argument) {
        return Interval(
            first_argument.lower() - second_argument,
            first_argument.upper() - second_argument
        );
    }

    inline Interval operator-(Interval first_argument, Interval second_argument) {
        return Interval(
            first_argument.lower() - second_argument.upper(),
            first_argument.upper() - second_argument.lower()
        );
    }

    inline Interval operator*(double first_argument, Interval second_argument) {
        if (first_argument >= 0.0) {
            return Interval(
                first_argument * second_argument.lower(),
                first_argument * second_argument.upper()
            );
        } else {
            return Interval(
                first_argument * second_argument.upper(),
                first_argument * second_argument.lower()
            );
        }
    }

    inline Interval operator*(Interval first_argument, double second_argument) {
        if (second_argument >= 0.0) {
            return Interval(
                first_argument.lower() * second_argument,
                first_argument.upper() * second_argument
            );
        } else {
            return Interval(
                first_argument.upper() * second_argument,
                first_argument.lower() * second_argument
            );
        }
    }

    inline Interval operator/(Interval first_argument, double second_argument) {
        if (second_argument >= 0.0) {
            return Interval(
                first_argument.lower() / second_argument,
                first_argument.upper() / second_argument
            );
        } else {
            return Interval(
                first_argument.upper() / second_argument,
                first_argument.lower() / second_argument
            );
        }
    }

    inline Interval abs(Interval argument) {
        if (argument.lower() > 0.0) {
            return argument;
        } else if (argument.upper() < 0.0) {
            return -argument;
        } else if (-argument.lower() < argument.upper()) {
            return Interval(0.0, argument.upper());
        } else {
            return Interval(0.0, -argument.lower());
        }
    }

    inline Interval sqrt(Interval argument) {
        return Interval(sqrt(max(0.0, argument.lower())), sqrt(max(0.0, argument.upper())));
    }
    
    inline Interval conj(Interval argument) {return argument;}
    
    inline Interval real(Interval argument) {return argument;}
    
    inline Interval imag(Interval argument) {return 0.0;}
    
    inline Interval abs2(Interval argument) {return argument.squared();}
    
    inline Interval Bounds<int>::operator()(int argument) const {return Interval(argument);}

    inline Interval Bounds<double>::operator()(double argument) const {return Interval(argument);}
    
    inline Interval Bounds<Interval>::operator()(Interval argument) const {
        return argument;
    }
}
