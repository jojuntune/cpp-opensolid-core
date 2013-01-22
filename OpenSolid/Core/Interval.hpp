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

#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Utils/Convertible.hpp>
#include <OpenSolid/Utils/Zero.hpp>

#include <OpenSolid/Core/Interval/declarations.hpp>
#include <OpenSolid/Core/Matrix/declarations.hpp>

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
        double _lowerBound;
        double _upperBound;
    public:
        Interval();
        Interval(double value);
        Interval(double lowerBound, double upperBound);
        
        double lowerBound() const;
        double upperBound() const;
        double median() const;
        double width() const;
        double randomValue() const;

        double clamp(double value) const;
        Interval clamp(Interval interval) const;
        double interpolated(double value) const;
        Interval interpolated(Interval interval) const;
        
        Interval squared() const;
        
        bool isEmpty() const;
        bool isSingleton() const;
        
        std::pair<Interval, Interval> bisected() const;
        
        Interval hull(Interval interval) const;
        Interval intersection(Interval interval) const;
        
        bool contains(double value, double tolerance = 1e-12) const;
        bool strictlyContains(double value, double tolerance = 1e-12) const;

        bool contains(Interval interval, double tolerance = 1e-12) const;
        bool strictlyContains(Interval interval, double tolerance = 1e-12) const;

        bool overlaps(Interval interval, double tolerance = 1e-12) const;
        bool strictlyOverlaps(Interval interval, double tolerance = 1e-12) const;
        
        Interval& operator+=(double value);
        Interval& operator+=(Interval interval);
        Interval& operator-=(double value);
        Interval& operator-=(Interval interval);
        Interval& operator*=(double value);
        Interval& operator/=(double value);
        OPENSOLID_CORE_EXPORT Interval& operator*=(Interval interval);
        OPENSOLID_CORE_EXPORT Interval& operator/=(Interval interval);
        
        static Interval Unit();
        static Interval Hull(double firstValue, double secondValue);
        static Interval Empty();
        static Interval Whole();
    };

    bool operator==(double value, Interval interval);
    bool operator==(Interval interval, double value);
    bool operator==(Interval firstInterval, Interval secondInterval);

    bool operator!=(double value, Interval interval);
    bool operator!=(Interval interval, double value);
    bool operator!=(Interval firstInterval, Interval secondInterval);

    bool operator<(double value, Interval interval);
    bool operator<(Interval interval, double value);
    bool operator<(Interval firstInterval, Interval secondInterval);

    bool operator>(double value, Interval interval);
    bool operator>(Interval interval, double value);
    bool operator>(Interval firstInterval, Interval secondInterval);

    bool operator<=(double value, Interval interval);
    bool operator<=(Interval interval, double value);
    bool operator<=(Interval firstInterval, Interval secondInterval);

    bool operator>=(double value, Interval interval);
    bool operator>=(Interval interval, double value);
    bool operator>=(Interval firstInterval, Interval secondInterval);
    
    bool operator==(Interval interval, Zero zero);
    bool operator!=(Interval interval, Zero zero);
    bool operator<(Interval interval, Zero zero);
    bool operator>(Interval interval, Zero zero);
    bool operator<=(Interval interval, Zero zero);
    bool operator>=(Interval interval, Zero zero);
        
    Interval operator-(Interval argument);

    Interval operator+(double value, Interval interval);
    Interval operator+(Interval interval, double value);
    Interval operator+(Interval firstInterval, Interval secondInterval);

    Interval operator-(double value, Interval interval);
    Interval operator-(Interval interval, double value);
    Interval operator-(Interval firstInterval, Interval secondInterval);

    Interval operator*(double value, Interval interval);
    Interval operator*(Interval interval, double value);
    OPENSOLID_CORE_EXPORT Interval operator*(Interval firstInterval, Interval secondInterval);

    Interval operator/(Interval interval, double value);
    OPENSOLID_CORE_EXPORT Interval operator/(double value, Interval interval);
    OPENSOLID_CORE_EXPORT Interval operator/(Interval firstInterval, Interval secondInterval);

    Interval abs(Interval interval);
    Interval sqrt(Interval interval);
    OPENSOLID_CORE_EXPORT Interval sin(Interval interval);
    OPENSOLID_CORE_EXPORT Interval cos(Interval interval);
    OPENSOLID_CORE_EXPORT Interval tan(Interval interval);
    OPENSOLID_CORE_EXPORT Interval asin(Interval interval);
    OPENSOLID_CORE_EXPORT Interval acos(Interval interval);
    OPENSOLID_CORE_EXPORT Interval atan(Interval interval);
    OPENSOLID_CORE_EXPORT Interval atan2(Interval yInterval, Interval xInterval);
    OPENSOLID_CORE_EXPORT Interval exp(Interval interval);
    OPENSOLID_CORE_EXPORT Interval log(Interval interval);
    OPENSOLID_CORE_EXPORT Interval pow(Interval baseInterval, int exponentValue);
    OPENSOLID_CORE_EXPORT Interval pow(Interval baseInterval, double exponentValue);
    OPENSOLID_CORE_EXPORT Interval pow(Interval baseInterval, Interval exponentInterval);

    Interval conj(Interval interval);
    Interval real(Interval interval);
    Interval imag(Interval interval);
    Interval abs2(Interval interval);

    OPENSOLID_CORE_EXPORT std::ostream& operator<<(std::ostream& stream, Interval interval);
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct Bounds<Interval>
    {
        typedef Interval Type;

        Interval operator()(Interval interval) const;
    };
}

namespace Eigen
{   
    namespace internal
    {
        template <>
        struct significant_decimals_default_impl<opensolid::Interval, false>
        {
            static inline int run();
        };
        
        template <>
        struct is_arithmetic<opensolid::Interval>
        {
            static const bool value = true;
        };
    }
    
    template <>
    struct NumTraits<opensolid::Interval>
    {
        typedef opensolid::Interval Real;
        typedef opensolid::Interval NonInteger;
        typedef opensolid::Interval Nested;
        
        static const int IsComplex = 0;
        static const int IsInteger = 0;
        static const int ReadCost = 2;
        static const int AddCost = 2;
        static const int MulCost = 10;
        static const int IsSigned = 1;
        static const int RequireInitialization = 0;
        
        static opensolid::Interval epsilon();
        static opensolid::Interval dummy_precision();
        static opensolid::Interval lowest();
        static opensolid::Interval highest();  
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Interval::Interval() :
        _lowerBound(infinity()),
        _upperBound(-infinity()) {
    }
    
    inline Interval::Interval(double value) :
        _lowerBound(value),
        _upperBound(value) {
    }

    inline Interval::Interval(double lowerBound, double upperBound) :
        _lowerBound(lowerBound),
        _upperBound(upperBound) {
    }
    
    inline double Interval::lowerBound() const {
        return _lowerBound;
    }

    inline double Interval::upperBound() const {
        return _upperBound;
    }
    
    inline double Interval::median() const {
        return lowerBound() + 0.5 * width();
    }

    inline double Interval::randomValue() const {
        return lowerBound() + rand() * width() / RAND_MAX;
    }
    
    inline double Interval::width() const {
        return upperBound() - lowerBound();
    }

    inline double Interval::clamp(double value) const {
        if (value <= lowerBound()) {
            return lowerBound();
        } else if (value <= upperBound()) {
            return value;
        } else {
            return upperBound();
        }
    }

    inline Interval Interval::clamp(Interval interval) const {
        return Interval(clamp(interval.lowerBound()), clamp(interval.upperBound()));
    }

    inline double Interval::interpolated(double value) const {
        return lowerBound() + value * width();
    }

    inline Interval Interval::interpolated(Interval interval) const {
        return lowerBound() + interval * width();
    }

    inline Interval Interval::squared() const {
        if (lowerBound() > 0.0) {
            return Interval(lowerBound() * lowerBound(), upperBound() * upperBound());
        } else if (upperBound() < 0.0) {
            return Interval(upperBound() * upperBound(), lowerBound() * lowerBound());
        } else if (-lowerBound() < upperBound()) {
            return Interval(0.0, upperBound() * upperBound());
        } else {
            return Interval(0.0, lowerBound() * lowerBound());
        }
    }
    
    inline bool Interval::isEmpty() const {
        return lowerBound() > upperBound();
    }
    
    inline bool Interval::isSingleton() const {
        return lowerBound() == upperBound();
    }
    
    inline std::pair<Interval, Interval> Interval::bisected() const {
        double mid = median();
        return std::pair<Interval, Interval>(
            Interval(lowerBound(), mid),
            Interval(mid, upperBound())
        );
    }
    
    inline Interval Interval::hull(Interval interval) const {
        return Interval(
            min(lowerBound(), interval.lowerBound()),
            max(upperBound(), interval.upperBound())
        );
    }

    inline Interval Interval::intersection(Interval interval) const {
        return Interval(
            max(lowerBound(), interval.lowerBound()),
            min(upperBound(), interval.upperBound())
        );
    }
        
    inline bool Interval::contains(double value, double tolerance) const {
        return value >= lowerBound() - tolerance && value <= upperBound() + tolerance;
    }

    inline bool Interval::strictlyContains(double value, double tolerance) const {
        return value > lowerBound() + tolerance && value < upperBound() - tolerance;
    }

    inline bool Interval::contains(Interval interval, double tolerance) const {
        return interval.lowerBound() >= lowerBound() - tolerance &&
            interval.upperBound() <= upperBound() + tolerance;
    }

    inline bool Interval::strictlyContains(Interval interval, double tolerance) const {
        return interval.lowerBound() > lowerBound() + tolerance &&
            interval.upperBound() < upperBound() - tolerance;
    }

    inline bool Interval::overlaps(Interval interval, double tolerance) const {
        return interval.lowerBound() <= upperBound() + tolerance &&
            interval.upperBound() >= lowerBound() - tolerance;
    }

    inline bool Interval::strictlyOverlaps(Interval interval, double tolerance) const {
        return interval.lowerBound() < upperBound() - tolerance &&
            interval.upperBound() > lowerBound() + tolerance;
    }

    inline Interval& Interval::operator+=(double value) {
        _lowerBound += value;
        _upperBound += value;
        return *this;
    }

    inline Interval& Interval::operator+=(Interval interval) {
        _lowerBound += interval.lowerBound();
        _upperBound += interval.upperBound();
        return *this;
    }

    inline Interval& Interval::operator-=(double value) {
        _lowerBound -= value;
        _upperBound -= value;
        return *this;
    }

    inline Interval& Interval::operator-=(Interval interval) {
        _lowerBound -= interval.upperBound();
        _upperBound -= interval.lowerBound();
        return *this;
    }

    inline Interval& Interval::operator*=(double value) {
        if (value >= 0.0) {
            _lowerBound *= value;
            _upperBound *= value;
        } else {
            _lowerBound = _upperBound * value;
            _upperBound = _lowerBound * value;
        }
        return *this;
    }

    inline Interval& Interval::operator/=(double value) {
        if (value >= 0.0) {
            _lowerBound /= value;
            _upperBound /= value;
        } else {
            _lowerBound = _upperBound / value;
            _upperBound = _lowerBound / value;
        }
        return *this;
    }

    inline Interval Interval::Unit() {
        return Interval(0, 1);
    }
    
    inline Interval Interval::Hull(double firstValue, double secondValue) {
        return Interval(min(firstValue, secondValue), max(firstValue, secondValue));
    }

    inline Interval Interval::Empty() {
        return Interval(infinity(), -infinity());
    }
    
    inline Interval Interval::Whole() {
        return Interval(-infinity(), infinity());
    }

    inline bool operator==(double value, Interval interval) {
        return value == interval.lowerBound() && value == interval.upperBound();
    }

    inline bool operator==(Interval interval, double value) {
        return interval.lowerBound() == value && interval.upperBound() == value;
    }

    inline bool operator==(Interval firstInterval, Interval secondInterval) {
        return firstInterval.isSingleton() && secondInterval.isSingleton() &&
            firstInterval.lowerBound() == secondInterval.lowerBound();
    }

    inline bool operator!=(double value, Interval interval) {
        return value < interval.lowerBound() || value > interval.upperBound();
    }

    inline bool operator!=(Interval interval, double value) {
        return interval.lowerBound() > value || interval.upperBound() < value;
    }

    inline bool operator!=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lowerBound() > secondInterval.upperBound() ||
            firstInterval.upperBound() < secondInterval.lowerBound();
    }

    inline bool operator<(double value, Interval interval) {
        return value < interval.lowerBound();
    }

    inline bool operator<(Interval interval, double value) {
        return interval.upperBound() < value;
    }

    inline bool operator<(Interval firstInterval, Interval secondInterval) {
        return firstInterval.upperBound() < secondInterval.lowerBound();
    }

    inline bool operator>(double value, Interval interval) {
        return value > interval.upperBound();
    }

    inline bool operator>(Interval interval, double value) {
        return interval.lowerBound() > value;
    }

    inline bool operator>(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lowerBound() > secondInterval.upperBound();
    }

    inline bool operator<=(double value, Interval interval) {
        return value <= interval.lowerBound();
    }

    inline bool operator<=(Interval interval, double value) {
        return interval.upperBound() <= value;
    }

    inline bool operator<=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.upperBound() <= secondInterval.lowerBound();
    }

    inline bool operator>=(double value, Interval interval) {
        return value >= interval.upperBound();
    }

    inline bool operator>=(Interval interval, double value) {
        return interval.lowerBound() >= value;
    }

    inline bool operator>=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lowerBound() >= secondInterval.upperBound();
    }

    inline bool operator==(Interval interval, Zero zero) {
        return interval.lowerBound() >= -zero.precision() &&
            interval.upperBound() <= zero.precision();
    }

    inline bool operator!=(Interval interval, Zero zero) {
        return interval.lowerBound() > zero.precision() ||
            interval.upperBound() < -zero.precision();
    }

    inline bool operator<(Interval interval, Zero zero) {
        return interval.upperBound() < -zero.precision();
    }

    inline bool operator>(Interval interval, Zero zero) {
        return interval.lowerBound() > zero.precision();
    }

    inline bool operator<=(Interval interval, Zero zero) {
        return interval.upperBound() <= zero.precision();
    }

    inline bool operator>=(Interval interval, Zero zero) {
        return interval.lowerBound() >= -zero.precision();
    }

    inline Interval operator-(Interval interval) {
        return Interval(-interval.upperBound(), -interval.lowerBound());
    }

    inline Interval operator+(double value, Interval interval) {
        return Interval(value + interval.lowerBound(), value + interval.upperBound());
    }

    inline Interval operator+(Interval interval, double value) {
        return Interval(interval.lowerBound() + value, interval.upperBound() + value);
    }

    inline Interval operator+(Interval firstInterval, Interval secondInterval) {
        return Interval(
            firstInterval.lowerBound() + secondInterval.lowerBound(),
            firstInterval.upperBound() + secondInterval.upperBound()
        );
    }

    inline Interval operator-(double value, Interval interval) {
        return Interval(value - interval.upperBound(), value - interval.lowerBound());
    }

    inline Interval operator-(Interval interval, double value) {
        return Interval(interval.lowerBound() - value, interval.upperBound() - value);
    }

    inline Interval operator-(Interval firstInterval, Interval secondInterval) {
        return Interval(
            firstInterval.lowerBound() - secondInterval.upperBound(),
            firstInterval.upperBound() - secondInterval.lowerBound()
        );
    }

    inline Interval operator*(double value, Interval interval) {
        return value >= 0.0 ?
            Interval(value * interval.lowerBound(), value * interval.upperBound()) :
            Interval(value * interval.upperBound(), value * interval.lowerBound());
    }

    inline Interval operator*(Interval interval, double value) {
        return value >= 0.0 ?
            Interval(interval.lowerBound() * value, interval.upperBound() * value) :
            Interval(interval.upperBound() * value, interval.lowerBound() * value);
    }

    inline Interval operator/(Interval interval, double value) {
        return value >= 0.0 ?
            Interval(interval.lowerBound() / value, interval.upperBound() / value) :
            Interval(interval.upperBound() / value, interval.lowerBound() / value);
    }

    inline Interval abs(Interval interval) {
        if (interval.lowerBound() >= 0.0) {
            return interval;
        } else if (interval.upperBound() <= 0.0) {
            return -interval;
        } else if (-interval.lowerBound() < interval.upperBound()) {
            return Interval(0.0, interval.upperBound());
        } else {
            return Interval(0.0, -interval.lowerBound());
        }
    }

    inline Interval sqrt(Interval interval) {
        if (interval < Zero()) {
            return Interval::Empty();
        } else {
            return Interval(
                sqrt(max(0.0, interval.lowerBound())),
                sqrt(max(0.0, interval.upperBound()))
            );
        }
    }
    
    inline Interval conj(Interval interval) {
        return interval;
    }
    
    inline Interval real(Interval interval) {
        return interval;
    }
    
    inline Interval imag(Interval interval) {
        return 0.0;
    }
    
    inline Interval abs2(Interval interval) {
        return interval.squared();
    }
    
    inline Interval Bounds<int>::operator()(int value) const {
        return Interval(value);
    }

    inline Interval Bounds<double>::operator()(double value) const {
        return Interval(value);
    }
    
    inline Interval Bounds<Interval>::operator()(Interval interval) const {
        return interval;
    }
}

namespace Eigen
{
    namespace internal
    {
        inline int significant_decimals_default_impl<opensolid::Interval, false>::run() {
            return 17;
        }

        template <>
        struct random_impl<opensolid::Interval>
        {
            static opensolid::Interval run(
                const opensolid::Interval& lowerInterval,
                const opensolid::Interval& upperInterval
            ) {
                opensolid::Interval interval(lowerInterval.lowerBound(), upperInterval.upperBound());
                double firstRatio = double(std::rand()) / RAND_MAX;
                double secondRatio = double(std::rand()) / RAND_MAX;
                return interval.interpolated(opensolid::Interval::Hull(firstRatio, secondRatio));
            }

            static opensolid::Interval run() {
                double lower = -1 + 2 * double(std::rand()) / RAND_MAX;
                double upper = -1 + 2 * double(std::rand()) / RAND_MAX;
                return opensolid::Interval::Hull(lower, upper);
            }
        };
    }

    inline opensolid::Interval NumTraits<opensolid::Interval>::epsilon() {
        return std::numeric_limits<double>::epsilon();
    }
    
    inline opensolid::Interval NumTraits<opensolid::Interval>::dummy_precision() {
        return 1e-12;
    }
    
    inline opensolid::Interval NumTraits<opensolid::Interval>::lowest() {
        return std::numeric_limits<double>::min();
    }
    
    inline opensolid::Interval NumTraits<opensolid::Interval>::highest() {
        return std::numeric_limits<double>::max();
    }
}
