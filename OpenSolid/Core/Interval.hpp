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

#include "Interval/declarations.hpp"

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
        double _lowerValue;
        double _upperValue;
    public:
        Interval();
        Interval(double value);
        Interval(double lowerValue, double upperValue);
        
        double lowerValue() const;
        double upperValue() const;
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
        _lowerValue(infinity()),
        _upperValue(-infinity()) {
    }
    
    inline Interval::Interval(double value) :
        _lowerValue(value),
        _upperValue(value) {
    }

    inline Interval::Interval(double lowerValue, double upperValue) :
        _lowerValue(lowerValue),
        _upperValue(upperValue) {
    }
    
    inline double Interval::lowerValue() const {
        return _lowerValue;
    }

    inline double Interval::upperValue() const {
        return _upperValue;
    }
    
    inline double Interval::median() const {
        return lowerValue() + 0.5 * width();
    }

    inline double Interval::randomValue() const {
        return lowerValue() + rand() * width() / RAND_MAX;
    }
    
    inline double Interval::width() const {
        return upperValue() - lowerValue();
    }

    inline double Interval::clamp(double value) const {
        if (value <= lowerValue()) {
            return lowerValue();
        } else if (value <= upperValue()) {
            return value;
        } else {
            return upperValue();
        }
    }

    inline Interval Interval::clamp(Interval interval) const {
        return Interval(clamp(interval.lowerValue()), clamp(interval.upperValue()));
    }

    inline double Interval::interpolated(double value) const {
        return lowerValue() + value * width();
    }

    inline Interval Interval::interpolated(Interval interval) const {
        return lowerValue() + interval * width();
    }

    inline Interval Interval::squared() const {
        if (lowerValue() > 0.0) {
            return Interval(lowerValue() * lowerValue(), upperValue() * upperValue());
        } else if (upperValue() < 0.0) {
            return Interval(upperValue() * upperValue(), lowerValue() * lowerValue());
        } else if (-lowerValue() < upperValue()) {
            return Interval(0.0, upperValue() * upperValue());
        } else {
            return Interval(0.0, lowerValue() * lowerValue());
        }
    }
    
    inline bool Interval::isEmpty() const {
        return lowerValue() > upperValue();
    }
    
    inline bool Interval::isSingleton() const {
        return lowerValue() == upperValue();
    }
    
    inline std::pair<Interval, Interval> Interval::bisected() const {
        double mid = median();
        return std::pair<Interval, Interval>(
            Interval(lowerValue(), mid),
            Interval(mid, upperValue())
        );
    }
    
    inline Interval Interval::hull(Interval interval) const {
        return Interval(
            min(lowerValue(), interval.lowerValue()),
            max(upperValue(), interval.upperValue())
        );
    }

    inline Interval Interval::intersection(Interval interval) const {
        return Interval(
            max(lowerValue(), interval.lowerValue()),
            min(upperValue(), interval.upperValue())
        );
    }
        
    inline bool Interval::contains(double value, double tolerance) const {
        return value >= lowerValue() - tolerance && value <= upperValue() + tolerance;
    }

    inline bool Interval::strictlyContains(double value, double tolerance) const {
        return value > lowerValue() + tolerance && value < upperValue() - tolerance;
    }

    inline bool Interval::contains(Interval interval, double tolerance) const {
        return interval.lowerValue() >= lowerValue() - tolerance &&
            interval.upperValue() <= upperValue() + tolerance;
    }

    inline bool Interval::strictlyContains(Interval interval, double tolerance) const {
        return interval.lowerValue() > lowerValue() + tolerance &&
            interval.upperValue() < upperValue() - tolerance;
    }

    inline bool Interval::overlaps(Interval interval, double tolerance) const {
        return interval.lowerValue() <= upperValue() + tolerance &&
            interval.upperValue() >= lowerValue() - tolerance;
    }

    inline bool Interval::strictlyOverlaps(Interval interval, double tolerance) const {
        return interval.lowerValue() < upperValue() - tolerance &&
            interval.upperValue() > lowerValue() + tolerance;
    }

    inline Interval& Interval::operator+=(double value) {
        _lowerValue += value;
        _upperValue += value;
        return *this;
    }

    inline Interval& Interval::operator+=(Interval interval) {
        _lowerValue += interval.lowerValue();
        _upperValue += interval.upperValue();
        return *this;
    }

    inline Interval& Interval::operator-=(double value) {
        _lowerValue -= value;
        _upperValue -= value;
        return *this;
    }

    inline Interval& Interval::operator-=(Interval interval) {
        _lowerValue -= interval.upperValue();
        _upperValue -= interval.lowerValue();
        return *this;
    }

    inline Interval& Interval::operator*=(double value) {
        if (value >= 0.0) {
            _lowerValue *= value;
            _upperValue *= value;
        } else {
            _lowerValue = _upperValue * value;
            _upperValue = _lowerValue * value;
        }
        return *this;
    }

    inline Interval& Interval::operator/=(double value) {
        if (value >= 0.0) {
            _lowerValue /= value;
            _upperValue /= value;
        } else {
            _lowerValue = _upperValue / value;
            _upperValue = _lowerValue / value;
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
        return value == interval.lowerValue() && value == interval.upperValue();
    }

    inline bool operator==(Interval interval, double value) {
        return interval.lowerValue() == value && interval.upperValue() == value;
    }

    inline bool operator==(Interval firstInterval, Interval secondInterval) {
        return firstInterval.isSingleton() && secondInterval.isSingleton() &&
            firstInterval.lowerValue() == secondInterval.lowerValue();
    }

    inline bool operator!=(double value, Interval interval) {
        return value < interval.lowerValue() || value > interval.upperValue();
    }

    inline bool operator!=(Interval interval, double value) {
        return interval.lowerValue() > value || interval.upperValue() < value;
    }

    inline bool operator!=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lowerValue() > secondInterval.upperValue() ||
            firstInterval.upperValue() < secondInterval.lowerValue();
    }

    inline bool operator<(double value, Interval interval) {
        return value < interval.lowerValue();
    }

    inline bool operator<(Interval interval, double value) {
        return interval.upperValue() < value;
    }

    inline bool operator<(Interval firstInterval, Interval secondInterval) {
        return firstInterval.upperValue() < secondInterval.lowerValue();
    }

    inline bool operator>(double value, Interval interval) {
        return value > interval.upperValue();
    }

    inline bool operator>(Interval interval, double value) {
        return interval.lowerValue() > value;
    }

    inline bool operator>(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lowerValue() > secondInterval.upperValue();
    }

    inline bool operator<=(double value, Interval interval) {
        return value <= interval.lowerValue();
    }

    inline bool operator<=(Interval interval, double value) {
        return interval.upperValue() <= value;
    }

    inline bool operator<=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.upperValue() <= secondInterval.lowerValue();
    }

    inline bool operator>=(double value, Interval interval) {
        return value >= interval.upperValue();
    }

    inline bool operator>=(Interval interval, double value) {
        return interval.lowerValue() >= value;
    }

    inline bool operator>=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lowerValue() >= secondInterval.upperValue();
    }

    inline bool operator==(Interval interval, Zero zero) {
        return interval.lowerValue() >= -zero.precision() &&
            interval.upperValue() <= zero.precision();
    }

    inline bool operator!=(Interval interval, Zero zero) {
        return interval.lowerValue() > zero.precision() ||
            interval.upperValue() < -zero.precision();
    }

    inline bool operator<(Interval interval, Zero zero) {
        return interval.upperValue() < -zero.precision();
    }

    inline bool operator>(Interval interval, Zero zero) {
        return interval.lowerValue() > zero.precision();
    }

    inline bool operator<=(Interval interval, Zero zero) {
        return interval.upperValue() <= zero.precision();
    }

    inline bool operator>=(Interval interval, Zero zero) {
        return interval.lowerValue() >= -zero.precision();
    }

    inline Interval operator-(Interval interval) {
        return Interval(-interval.upperValue(), -interval.lowerValue());
    }

    inline Interval operator+(double value, Interval interval) {
        return Interval(value + interval.lowerValue(), value + interval.upperValue());
    }

    inline Interval operator+(Interval interval, double value) {
        return Interval(interval.lowerValue() + value, interval.upperValue() + value);
    }

    inline Interval operator+(Interval firstInterval, Interval secondInterval) {
        return Interval(
            firstInterval.lowerValue() + secondInterval.lowerValue(),
            firstInterval.upperValue() + secondInterval.upperValue()
        );
    }

    inline Interval operator-(double value, Interval interval) {
        return Interval(value - interval.upperValue(), value - interval.lowerValue());
    }

    inline Interval operator-(Interval interval, double value) {
        return Interval(interval.lowerValue() - value, interval.upperValue() - value);
    }

    inline Interval operator-(Interval firstInterval, Interval secondInterval) {
        return Interval(
            firstInterval.lowerValue() - secondInterval.upperValue(),
            firstInterval.upperValue() - secondInterval.lowerValue()
        );
    }

    inline Interval operator*(double value, Interval interval) {
        return value >= 0.0 ?
            Interval(value * interval.lowerValue(), value * interval.upperValue()) :
            Interval(value * interval.upperValue(), value * interval.lowerValue());
    }

    inline Interval operator*(Interval interval, double value) {
        return value >= 0.0 ?
            Interval(interval.lowerValue() * value, interval.upperValue() * value) :
            Interval(interval.upperValue() * value, interval.lowerValue() * value);
    }

    inline Interval operator/(Interval interval, double value) {
        return value >= 0.0 ?
            Interval(interval.lowerValue() / value, interval.upperValue() / value) :
            Interval(interval.upperValue() / value, interval.lowerValue() / value);
    }

    inline Interval abs(Interval interval) {
        if (interval.lowerValue() >= 0.0) {
            return interval;
        } else if (interval.upperValue() <= 0.0) {
            return -interval;
        } else if (-interval.lowerValue() < interval.upperValue()) {
            return Interval(0.0, interval.upperValue());
        } else {
            return Interval(0.0, -interval.lowerValue());
        }
    }

    inline Interval sqrt(Interval interval) {
        if (interval < Zero()) {
            return Interval::Empty();
        } else {
            return Interval(
                sqrt(max(0.0, interval.lowerValue())),
                sqrt(max(0.0, interval.upperValue()))
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
