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

#include "ScalarBase.hpp"

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
        BoostInterval _interval;
    public:
        Interval();
        Interval(Double value);
        Interval(Double lower, Double upper);
        Interval(const Interval& other);
        Interval(const BoostInterval& interval);
        
        BoostInterval& interval();
        const BoostInterval& interval() const;
        
        Double lower() const;
        Double upper() const;
        Double median() const;
        Double width() const;
        
        bool empty() const;
        bool singleton() const;
        
        std::pair<Interval, Interval> bisected() const;
        
        Interval squared() const;
        
        bool overlap(Double value) const;
        bool overlap(Double value, Double precision) const;
        bool overlap(Interval other) const;
        bool overlap(Interval other, Double precision) const;
        bool contain(Double value) const;
        bool contain(Double value, Double precision) const;
        bool contain(Interval other) const;
        bool contain(Interval other, Double precision) const;
        
        Interval hull(Double value) const;
        Interval hull(Interval other) const;
        Interval intersection(Double value) const;
        Interval intersection(Interval other) const;
        
        Interval& operator+=(Double argument);
        Interval& operator+=(Interval other);
        Interval& operator-=(Double argument);
        Interval& operator-=(Interval other);
        Interval& operator*=(Double argument);
        Interval& operator*=(Interval other);
        Interval& operator/=(Double argument);
        Interval& operator/=(Interval other);
        
        static Interval Empty();
        static Interval Whole();
        static Interval Hull(Double first_argument, Double second_argument);
    };

    bool operator==(Interval first_argument, Interval second_argument);
    bool operator!=(Interval first_argument, Interval second_argument);
    bool operator<(Interval first_argument, Interval second_argument);
    bool operator>(Interval first_argument, Interval second_argument);
    
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
        
        template <class ScalarType, bool is_integer_>
        struct significant_decimals_default_impl;
        
        template <>
        struct significant_decimals_default_impl<OpenSolid::Interval, false>
        {
            static inline int run();
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

#include <OpenSolid/Common/Eigen.hp>
#include "Traits.hpp"

namespace OpenSolid
{
    inline Interval Traits<int>::bounds(int argument) {return Interval(argument);}
    
    inline Interval Traits<float>::bounds(float argument) {return Interval(argument);}
    
    inline Interval Traits<double>::bounds(double argument) {return Interval(argument);}
    
    inline Interval Traits<Double>::bounds(Double argument) {return Interval(argument);}
    
    inline Interval Traits<Interval>::bounds(Interval argument) {return argument;}
    
    inline std::size_t Traits<Interval>::hash(Interval argument) {
        std::size_t result = 0;
        boost::hash_combine(result, argument.lower());
        boost::hash_combine(result, argument.upper());
        return result;
    }
    
    inline Interval::Interval(const BoostInterval& interval) : _interval(interval) {}
        
    inline Interval::Interval() : _interval() {}

    inline Interval::Interval(Double value) : _interval(value) {}

    inline Interval::Interval(Double lower, Double upper) : _interval(lower, upper) {}

    inline Interval::Interval(const Interval& other) : _interval(other._interval) {}
        
    inline BoostInterval& Interval::interval() {return _interval;}
    
    inline const BoostInterval& Interval::interval() const {return _interval;}
    
    inline Double Interval::lower() const {return interval().lower();}

    inline Double Interval::upper() const {return interval().upper();}
    
    inline Double Interval::median() const {return boost::numeric::median(interval());}
    
    inline Double Interval::width() const {return boost::numeric::width(interval());}
    
    inline bool Interval::empty() const {return boost::numeric::empty(interval());}
    
    inline bool Interval::singleton() const {return boost::numeric::singleton(interval());}
    
    inline std::pair<Interval, Interval> Interval::bisected() const {
        Double mid = median();
        return std::make_pair(Interval(lower(), mid), Interval(mid, upper()));
    }
    
    inline Interval Interval::squared() const {return square(interval());}
    
    inline bool Interval::overlap(Double value, Double tolerance) const {
        return lower() - tolerance <= value && value <= upper() + tolerance;
    }
    
    inline bool Interval::overlap(Interval other, Double tolerance) const {
        return lower() - tolerance <= other.upper() && other.lower() <= upper() + tolerance;
    }
    
    inline bool Interval::contain(Double value, Double tolerance) const {
        return lower() - tolerance <= value && value <= upper() + tolerance;
    }
    
    inline bool Interval::contain(Interval other, Double tolerance) const {
        return lower() - tolerance <= other.lower() && other.upper() <= upper() + tolerance;
    }
        
    inline Interval Interval::hull(Double value) const {
        return boost::numeric::hull(interval(), value);
    }
    
    inline Interval Interval::hull(Interval other) const {
        return boost::numeric::hull(interval(), other.interval());
    }
    
    inline Interval Interval::intersection(Interval other) const {
        return boost::numeric::intersect(interval(), other.interval());
    }

    inline Interval& Interval::operator+=(Double argument) {
        interval() += argument;
        return *this;
    }

    inline Interval& Interval::operator+=(Interval other) {
        interval() += other.interval();
        return *this;
    }

    inline Interval& Interval::operator-=(Double argument) {
        interval() -= argument;
        return *this;
    }

    inline Interval& Interval::operator-=(Interval other) {
        interval() -= other.interval();
        return *this;
    }

    inline Interval& Interval::operator*=(Double argument) {
        interval() *= argument;
        return *this;
    }

    inline Interval& Interval::operator*=(Interval other) {
        interval() *= other.interval();
        return *this;
    }

    inline Interval& Interval::operator/=(Double argument) {
        interval() /= argument;
        return *this;
    }

    inline Interval& Interval::operator/=(Interval other) {
        interval() /= other.interval();
        return *this;
    }
    
    inline Interval Interval::Empty() {return BoostInterval::empty();}
    
    inline Interval Interval::Whole() {return BoostInterval::whole();}
    
    inline Interval Interval::Hull(Double first_argument, Double second_argument) {
        return BoostInterval::hull(first_argument, second_argument);
    }

    inline bool operator==(Interval first_argument, Interval second_argument) {
        return first_argument.lower() == second_argument.lower() &&
            first_argument.upper() == second_argument.upper();
    }

    inline bool operator!=(Interval first_argument, Interval second_argument) {
        return first_argument.lower() != second_argument.lower() ||
            first_argument.upper() != second_argument.upper();
    }
    
    inline bool operator<(Interval first_argument, Interval second_argument) {
        if (first_argument.lower() == second_argument.lower()) {
            return first_argument.upper() < second_argument.upper();
        } else {
            return first_argument.lower() < second_argument.lower();
        }
    }
    
    inline bool operator>(Interval first_argument, Interval second_argument) {
        if (first_argument.lower() == second_argument.lower()) {
            return first_argument.upper() > second_argument.upper();
        } else {
            return first_argument.lower() > second_argument.lower();
        }
    }
        
    inline Interval operator-(Interval argument) {return -argument.interval();}

    inline Interval operator+(Double first_argument, Interval second_argument) {
        return first_argument + second_argument.interval();
    }

    inline Interval operator+(Interval first_argument, Double second_argument) {
        return first_argument.interval() + second_argument;
    }

    inline Interval operator+(Interval first_argument, Interval second_argument) {
        return first_argument.interval() + second_argument.interval();
    }

    inline Interval operator-(Double first_argument, Interval second_argument) {
        return first_argument - second_argument.interval();
    }

    inline Interval operator-(Interval first_argument, Double second_argument) {
        return first_argument.interval() - second_argument;
    }

    inline Interval operator-(Interval first_argument, Interval second_argument) {
        return first_argument.interval() - second_argument.interval();
    }

    inline Interval operator*(Double first_argument, Interval second_argument) {
        return first_argument * second_argument.interval();
    }

    inline Interval operator*(Interval first_argument, Double second_argument) {
        return first_argument.interval() * second_argument;
    }

    inline Interval operator*(Interval first_argument, Interval second_argument) {
        return first_argument.interval() * second_argument.interval();
    }

    inline Interval operator/(Double first_argument, Interval second_argument) {
        return first_argument / second_argument.interval();
    }

    inline Interval operator/(Interval first_argument, Double second_argument) {
        return first_argument.interval() / second_argument;
    }

    inline Interval operator/(Interval first_argument, Interval second_argument) {
        return first_argument.interval() / second_argument.interval();
    }

    inline Interval abs(Interval argument) {return abs(argument.interval());}

    inline Interval sqrt(Interval argument) {return sqrt(argument.interval());}
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
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::epsilon() {
        return OpenSolid::Interval(NumTraits<double>::epsilon());
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::dummy_precision() {
        return OpenSolid::Interval(NumTraits<double>::dummy_precision());
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::lowest() {
        return OpenSolid::Interval(NumTraits<double>::lowest());
    }
    
    inline OpenSolid::Interval NumTraits<OpenSolid::Interval>::highest() {
        return OpenSolid::Interval(NumTraits<double>::highest());
    }
}

#endif
