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
        double _lower;
        double _upper;
    public:
        Interval();
        Interval(double value);
        Interval(double lowerValue, double upperValue);
        
        double lower() const;
        double upper() const;
        double median() const;
        double random() const;
        double width() const;

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

////////// Implementation //////////

namespace opensolid
{
    inline Interval::Interval() :
        _lower(infinity()),
        _upper(-infinity()) {
    }
    
    inline Interval::Interval(double value) :
        _lower(value),
        _upper(value) {
    }

    inline Interval::Interval(double lowerValue, double upperValue) :
        _lower(lowerValue),
        _upper(upperValue) {
    }
    
    inline double Interval::lower() const {
        return _lower;
    }

    inline double Interval::upper() const {
        return _upper;
    }
    
    inline double Interval::median() const {
        return lower() + 0.5 * (upper() - lower());
    }

    inline double Interval::random() const {
        return lower() + rand() * width() / RAND_MAX;
    }
    
    inline double Interval::width() const {
        return upper() - lower();
    }

    inline double Interval::clamp(double value) const {
        return value <= lower() ? lower() : (value <= upper() ? value : upper());
    }

    inline Interval Interval::clamp(Interval interval) const {
        return Interval(clamp(interval.lower()), clamp(interval.upper()));
    }

    inline double Interval::interpolated(double value) const {
        return lower() + value * width();
    }

    inline Interval Interval::interpolated(Interval interval) const {
        return lower() + interval * width();
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
    
    inline bool Interval::isEmpty() const {
        return lower() > upper();
    }
    
    inline bool Interval::isSingleton() const {
        return lower() == upper();
    }
    
    inline std::pair<Interval, Interval> Interval::bisected() const {
        double mid = median();
        return std::pair<Interval, Interval>(Interval(lower(), mid), Interval(mid, upper()));
    }
    
    inline Interval Interval::hull(Interval interval) const {
        return Interval(min(lower(), interval.lower()), max(upper(), interval.upper()));
    }

    inline Interval Interval::intersection(Interval interval) const {
        return Interval(max(lower(), interval.lower()), min(upper(), interval.upper()));
    }
        
    inline bool Interval::contains(double value, double tolerance) const {
        return value >= lower() - tolerance && value <= upper() + tolerance;
    }

    inline bool Interval::strictlyContains(double value, double tolerance) const {
        return value > lower() + tolerance && value < upper() - tolerance;
    }

    inline bool Interval::contains(Interval interval, double tolerance) const {
        return interval.lower() >= lower() - tolerance && interval.upper() <= upper() + tolerance;
    }

    inline bool Interval::strictlyContains(Interval interval, double tolerance) const {
        return interval.lower() > lower() + tolerance && interval.upper() < upper() - tolerance;
    }

    inline bool Interval::overlaps(Interval interval, double tolerance) const {
        return interval.lower() <= upper() + tolerance && interval.upper() >= lower() - tolerance;
    }

    inline bool Interval::strictlyOverlaps(Interval interval, double tolerance) const {
        return interval.lower() < upper() - tolerance && interval.upper() > lower() + tolerance;
    }

    inline Interval& Interval::operator+=(double value) {
        _lower += value;
        _upper += value;
        return *this;
    }

    inline Interval& Interval::operator+=(Interval interval) {
        _lower += interval.lower();
        _upper += interval.upper();
        return *this;
    }

    inline Interval& Interval::operator-=(double value) {
        _lower -= value;
        _upper -= value;
        return *this;
    }

    inline Interval& Interval::operator-=(Interval interval) {
        _lower -= interval.upper();
        _upper -= interval.lower();
        return *this;
    }

    inline Interval& Interval::operator*=(double value) {
        if (value >= 0.0) {
            _lower *= value;
            _upper *= value;
        } else {
            _lower = _upper * value;
            _upper = _lower * value;
        }
        return *this;
    }

    inline Interval& Interval::operator/=(double value) {
        if (value >= 0.0) {
            _lower /= value;
            _upper /= value;
        } else {
            _lower = _upper / value;
            _upper = _lower / value;
        }
        return *this;
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
        return value == interval.lower() && value == interval.upper();
    }

    inline bool operator==(Interval interval, double value) {
        return interval.lower() == value && interval.upper() == value;
    }

    inline bool operator==(Interval firstInterval, Interval secondInterval) {
        return firstInterval.isSingleton() && secondInterval.isSingleton() &&
            firstInterval.lower() == secondInterval.lower();
    }

    inline bool operator!=(double value, Interval interval) {
        return value < interval.lower() || value > interval.upper();
    }

    inline bool operator!=(Interval interval, double value) {
        return interval.lower() > value || interval.upper() < value;
    }

    inline bool operator!=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lower() > secondInterval.upper() ||
            firstInterval.upper() < secondInterval.lower();
    }

    inline bool operator<(double value, Interval interval) {
        return value < interval.lower();
    }

    inline bool operator<(Interval interval, double value) {
        return interval.upper() < value;
    }

    inline bool operator<(Interval firstInterval, Interval secondInterval) {
        return firstInterval.upper() < secondInterval.lower();
    }

    inline bool operator>(double value, Interval interval) {
        return value > interval.upper();
    }

    inline bool operator>(Interval interval, double value) {
        return interval.lower() > value;
    }

    inline bool operator>(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lower() > secondInterval.upper();
    }

    inline bool operator<=(double value, Interval interval) {
        return value <= interval.lower();
    }

    inline bool operator<=(Interval interval, double value) {
        return interval.upper() <= value;
    }

    inline bool operator<=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.upper() <= secondInterval.lower();
    }

    inline bool operator>=(double value, Interval interval) {
        return value >= interval.upper();
    }

    inline bool operator>=(Interval interval, double value) {
        return interval.lower() >= value;
    }

    inline bool operator>=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lower() >= secondInterval.upper();
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

    inline Interval operator-(Interval interval) {
        return Interval(-interval.upper(), -interval.lower());
    }

    inline Interval operator+(double value, Interval interval) {
        return Interval(value + interval.lower(), value + interval.upper());
    }

    inline Interval operator+(Interval interval, double value) {
        return Interval(interval.lower() + value, interval.upper() + value);
    }

    inline Interval operator+(Interval firstInterval, Interval secondInterval) {
        return Interval(
            firstInterval.lower() + secondInterval.lower(),
            firstInterval.upper() + secondInterval.upper()
        );
    }

    inline Interval operator-(double value, Interval interval) {
        return Interval(value - interval.upper(), value - interval.lower());
    }

    inline Interval operator-(Interval interval, double value) {
        return Interval(interval.lower() - value, interval.upper() - value);
    }

    inline Interval operator-(Interval firstInterval, Interval secondInterval) {
        return Interval(
            firstInterval.lower() - secondInterval.upper(),
            firstInterval.upper() - secondInterval.lower()
        );
    }

    inline Interval operator*(double value, Interval interval) {
        return value >= 0.0 ?
            Interval(value * interval.lower(), value * interval.upper()) :
            Interval(value * interval.upper(), value * interval.lower());
    }

    inline Interval operator*(Interval interval, double value) {
        return value >= 0.0 ?
            Interval(interval.lower() * value, interval.upper() * value) :
            Interval(interval.upper() * value, interval.lower() * value);
    }

    inline Interval operator/(Interval interval, double value) {
        return value >= 0.0 ?
            Interval(interval.lower() / value, interval.upper() / value) :
            Interval(interval.upper() / value, interval.lower() / value);
    }

    inline Interval abs(Interval interval) {
        if (interval.lower() >= 0.0) {
            return interval;
        } else if (interval.upper() <= 0.0) {
            return -interval;
        } else if (-interval.lower() < interval.upper()) {
            return Interval(0.0, interval.upper());
        } else {
            return Interval(0.0, -interval.lower());
        }
    }

    inline Interval sqrt(Interval interval) {
        return Interval(sqrt(max(0.0, interval.lower())), sqrt(max(0.0, interval.upper())));
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
