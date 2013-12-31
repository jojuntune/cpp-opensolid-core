/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Interval.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <cassert>
#include <cstdlib>
#include <limits>
#include <algorithm>

namespace opensolid
{
    inline
    Interval::Interval() :
        _lowerBound(INFINITY),
        _upperBound(-INFINITY) {
    }
    
    inline
    Interval::Interval(double value) :
        _lowerBound(value),
        _upperBound(value) {
    }

    inline
    Interval::Interval(double lowerBound, double upperBound) :
        _lowerBound(lowerBound),
        _upperBound(upperBound) {
    }
    
    inline
    double
    Interval::lowerBound() const {
        return _lowerBound;
    }

    inline
    double
    Interval::upperBound() const {
        return _upperBound;
    }
    
    inline
    double
    Interval::median() const {
        return lowerBound() + 0.5 * width();
    }

    inline
    double
    Interval::randomValue() const {
        return lowerBound() + rand() * width() / RAND_MAX;
    }
    
    inline
    double
    Interval::width() const {
        return upperBound() - lowerBound();
    }

    inline
    double
    Interval::clamp(double value) const {
        if (value <= lowerBound()) {
            return lowerBound();
        } else if (value <= upperBound()) {
            return value;
        } else {
            return upperBound();
        }
    }

    inline
    Interval
    Interval::clamp(Interval interval) const {
        return Interval(clamp(interval.lowerBound()), clamp(interval.upperBound()));
    }

    inline
    double
    Interval::interpolated(double value) const {
        return lowerBound() + value * width();
    }

    inline
    Interval
    Interval::interpolated(Interval interval) const {
        return lowerBound() + interval * width();
    }

    inline
    Interval
    Interval::squared() const {
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
    
    inline
    bool
    Interval::isEmpty() const {
        return lowerBound() > upperBound();
    }
    
    inline
    bool
    Interval::isSingleton() const {
        return lowerBound() == upperBound();
    }
    
    inline
    std::pair<Interval, Interval>
    Interval::bisected() const {
        double mid = median();
        return std::pair<Interval, Interval>(
            Interval(lowerBound(), mid),
            Interval(mid, upperBound())
        );
    }

    inline
    Interval
    Interval::hull(double value) const {
        return Interval(
            min(lowerBound(), value),
            max(upperBound(), value)
        );
    }
    
    inline
    Interval
    Interval::hull(Interval interval) const {
        return Interval(
            min(lowerBound(), interval.lowerBound()),
            max(upperBound(), interval.upperBound())
        );
    }

    inline
    Interval
    Interval::intersection(Interval interval) const {
        return Interval(
            max(lowerBound(), interval.lowerBound()),
            min(upperBound(), interval.upperBound())
        );
    }
        
    inline
    bool
    Interval::contains(double value, double tolerance) const {
        return value >= lowerBound() - tolerance && value <= upperBound() + tolerance;
    }

    inline
    bool
    Interval::strictlyContains(double value, double tolerance) const {
        return value > lowerBound() + tolerance && value < upperBound() - tolerance;
    }

    inline
    bool
    Interval::contains(Interval interval, double tolerance) const {
        return interval.lowerBound() >= lowerBound() - tolerance &&
            interval.upperBound() <= upperBound() + tolerance;
    }

    inline
    bool
    Interval::strictlyContains(Interval interval, double tolerance) const {
        return interval.lowerBound() > lowerBound() + tolerance &&
            interval.upperBound() < upperBound() - tolerance;
    }

    inline
    bool
    Interval::overlaps(Interval interval, double tolerance) const {
        return interval.lowerBound() <= upperBound() + tolerance &&
            interval.upperBound() >= lowerBound() - tolerance;
    }

    inline
    bool
    Interval::strictlyOverlaps(Interval interval, double tolerance) const {
        return interval.lowerBound() < upperBound() - tolerance &&
            interval.upperBound() > lowerBound() + tolerance;
    }

    inline
    Interval&
    Interval::operator+=(double value) {
        _lowerBound += value;
        _upperBound += value;
        return *this;
    }

    inline
    Interval&
    Interval::operator+=(Interval interval) {
        _lowerBound += interval.lowerBound();
        _upperBound += interval.upperBound();
        return *this;
    }

    inline
    Interval&
    Interval::operator-=(double value) {
        _lowerBound -= value;
        _upperBound -= value;
        return *this;
    }

    inline
    Interval&
    Interval::operator-=(Interval interval) {
        _lowerBound -= interval.upperBound();
        _upperBound -= interval.lowerBound();
        return *this;
    }

    inline
    Interval&
    Interval::operator*=(double value) {
        if (value >= 0.0) {
            _lowerBound *= value;
            _upperBound *= value;
        } else {
            _lowerBound = _upperBound * value;
            _upperBound = _lowerBound * value;
        }
        return *this;
    }

    inline
    Interval&
    Interval::operator/=(double value) {
        if (value >= 0.0) {
            _lowerBound /= value;
            _upperBound /= value;
        } else {
            _lowerBound = _upperBound / value;
            _upperBound = _lowerBound / value;
        }
        return *this;
    }

    inline
    Interval
    Interval::Unit() {
        return Interval(0, 1);
    }
    
    inline
    Interval
    Interval::Hull(double firstValue, double secondValue) {
        return Interval(min(firstValue, secondValue), max(firstValue, secondValue));
    }

    inline
    Interval
    Interval::Empty() {
        return Interval(INFINITY, -INFINITY);
    }
    
    inline
    Interval
    Interval::Whole() {
        return Interval(-INFINITY, INFINITY);
    }

    inline
    bool
    operator==(double value, Interval interval) {
        return value == interval.lowerBound() && value == interval.upperBound();
    }

    inline
    bool
    operator==(Interval interval, double value) {
        return interval.lowerBound() == value && interval.upperBound() == value;
    }

    inline
    bool
    operator==(Interval firstInterval, Interval secondInterval) {
        return firstInterval.isSingleton() && secondInterval.isSingleton() &&
            firstInterval.lowerBound() == secondInterval.lowerBound();
    }

    inline
    bool
    operator!=(double value, Interval interval) {
        return value < interval.lowerBound() || value > interval.upperBound();
    }

    inline
    bool
    operator!=(Interval interval, double value) {
        return interval.lowerBound() > value || interval.upperBound() < value;
    }

    inline
    bool
    operator!=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lowerBound() > secondInterval.upperBound() ||
            firstInterval.upperBound() < secondInterval.lowerBound();
    }

    inline
    bool
    operator<(double value, Interval interval) {
        return value < interval.lowerBound();
    }

    inline
    bool
    operator<(Interval interval, double value) {
        return interval.upperBound() < value;
    }

    inline
    bool
    operator<(Interval firstInterval, Interval secondInterval) {
        return firstInterval.upperBound() < secondInterval.lowerBound();
    }

    inline
    bool
    operator>(double value, Interval interval) {
        return value > interval.upperBound();
    }

    inline
    bool
    operator>(Interval interval, double value) {
        return interval.lowerBound() > value;
    }

    inline
    bool
    operator>(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lowerBound() > secondInterval.upperBound();
    }

    inline
    bool
    operator<=(double value, Interval interval) {
        return value <= interval.lowerBound();
    }

    inline
    bool
    operator<=(Interval interval, double value) {
        return interval.upperBound() <= value;
    }

    inline
    bool
    operator<=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.upperBound() <= secondInterval.lowerBound();
    }

    inline
    bool
    operator>=(double value, Interval interval) {
        return value >= interval.upperBound();
    }

    inline
    bool
    operator>=(Interval interval, double value) {
        return interval.lowerBound() >= value;
    }

    inline
    bool
    operator>=(Interval firstInterval, Interval secondInterval) {
        return firstInterval.lowerBound() >= secondInterval.upperBound();
    }

    inline
    bool
    operator==(Interval interval, Zero zero) {
        return interval.lowerBound() >= -zero.precision() &&
            interval.upperBound() <= zero.precision();
    }

    inline
    bool
    operator!=(Interval interval, Zero zero) {
        return interval.lowerBound() > zero.precision() ||
            interval.upperBound() < -zero.precision();
    }

    inline
    bool
    operator<(Interval interval, Zero zero) {
        return interval.upperBound() < -zero.precision();
    }

    inline
    bool
    operator>(Interval interval, Zero zero) {
        return interval.lowerBound() > zero.precision();
    }

    inline
    bool
    operator<=(Interval interval, Zero zero) {
        return interval.upperBound() <= zero.precision();
    }

    inline
    bool
    operator>=(Interval interval, Zero zero) {
        return interval.lowerBound() >= -zero.precision();
    }

    inline
    Interval
    operator-(Interval interval) {
        return Interval(-interval.upperBound(), -interval.lowerBound());
    }

    inline
    Interval
    operator+(double value, Interval interval) {
        return Interval(value + interval.lowerBound(), value + interval.upperBound());
    }

    inline
    Interval
    operator+(Interval interval, double value) {
        return Interval(interval.lowerBound() + value, interval.upperBound() + value);
    }

    inline
    Interval
    operator+(Interval firstInterval, Interval secondInterval) {
        return Interval(
            firstInterval.lowerBound() + secondInterval.lowerBound(),
            firstInterval.upperBound() + secondInterval.upperBound()
        );
    }

    inline
    Interval
    operator-(double value, Interval interval) {
        return Interval(value - interval.upperBound(), value - interval.lowerBound());
    }

    inline
    Interval
    operator-(Interval interval, double value) {
        return Interval(interval.lowerBound() - value, interval.upperBound() - value);
    }

    inline
    Interval
    operator-(Interval firstInterval, Interval secondInterval) {
        return Interval(
            firstInterval.lowerBound() - secondInterval.upperBound(),
            firstInterval.upperBound() - secondInterval.lowerBound()
        );
    }

    inline
    Interval
    operator*(double value, Interval interval) {
        return value >= 0.0 ?
            Interval(value * interval.lowerBound(), value * interval.upperBound()) :
            Interval(value * interval.upperBound(), value * interval.lowerBound());
    }

    inline
    Interval
    operator*(Interval interval, double value) {
        return value >= 0.0 ?
            Interval(interval.lowerBound() * value, interval.upperBound() * value) :
            Interval(interval.upperBound() * value, interval.lowerBound() * value);
    }

    inline
    Interval
    operator/(Interval interval, double value) {
        return value >= 0.0 ?
            Interval(interval.lowerBound() / value, interval.upperBound() / value) :
            Interval(interval.upperBound() / value, interval.lowerBound() / value);
    }

    inline
    Interval
    abs(Interval interval) {
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

    inline
    Interval
    sqrt(Interval interval) {
        if (interval < Zero()) {
            return Interval::Empty();
        } else {
            return Interval(
                sqrt(max(0.0, interval.lowerBound())),
                sqrt(interval.upperBound())
            );
        }
    }
    
    inline
    Interval
    conj(Interval interval) {
        return interval;
    }
    
    inline
    Interval
    real(Interval interval) {
        return interval;
    }
    
    inline
    Interval
    imag(Interval interval) {
        return 0.0;
    }
    
    inline
    Interval
    abs2(Interval interval) {
        return interval.squared();
    }
    
    inline
    Interval
    BoundsFunction<Interval>::operator()(Interval interval) const {
        return interval;
    }
}
