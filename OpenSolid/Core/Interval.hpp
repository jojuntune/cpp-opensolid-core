/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#include <cmath>
#include <cstdlib>
#include <limits>
#include <algorithm>

// Temporary hack to allow use of _isnan() until Visual Studio supports std::isnan()
#ifdef _MSC_VER
#include <float.h>
#endif

namespace opensolid
{
    inline
    Interval::Interval() :
        _lowerBound(std::numeric_limits<double>::quiet_NaN()),
        _upperBound(std::numeric_limits<double>::quiet_NaN()) {
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

        assert(!(lowerBound > upperBound));
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
    Interval
    Interval::bounds() const {
        return *this;
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
        if (isEmpty()) {
            return Interval::EMPTY();
        } else {
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
    }
    
    inline
    bool
    Interval::isEmpty() const {
        // Temporary hack until Visual Studio supports std::isnan()
        #ifdef _MSC_VER
        return _isnan(lowerBound()) && _isnan(upperBound());
        #else
        return std::isnan(lowerBound()) && std::isnan(upperBound());
        #endif
    }
    
    inline
    bool
    Interval::isSingleton() const {
        return lowerBound() == upperBound();
    }
    
    inline
    std::pair<Interval, Interval>
    Interval::bisected() const {
        double median = this->median();
        return std::pair<Interval, Interval>(
            Interval(lowerBound(), median),
            Interval(median, upperBound())
        );
    }

    inline
    Interval
    Interval::hull(double value) const {
        if (isEmpty()) {
            return value;
        } else {
            return Interval(
                min(lowerBound(), value),
                max(upperBound(), value)
            );
        }
    }
    
    inline
    Interval
    Interval::hull(Interval other) const {
        if (isEmpty()) {
            return other;
        } else if (other.isEmpty()) {
            return *this;
        } else {
            return Interval(
                min(lowerBound(), other.lowerBound()),
                max(upperBound(), other.upperBound())
            );
        }
    }

    inline
    Interval
    Interval::intersection(Interval other) const {
        if (isEmpty() || other.isEmpty()) {
            return Interval::EMPTY();
        } else {
            double lowerBound = max(this->lowerBound(), other.lowerBound());
            double upperBound = min(this->upperBound(), other.upperBound());
            return lowerBound <= upperBound ? Interval(lowerBound, upperBound) : Interval::EMPTY();
        }
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
        return (
            interval.lowerBound() >= lowerBound() - tolerance &&
            interval.upperBound() <= upperBound() + tolerance
        );
    }

    inline
    bool
    Interval::strictlyContains(Interval interval, double tolerance) const {
        return ( 
            interval.lowerBound() > lowerBound() + tolerance &&
            interval.upperBound() < upperBound() - tolerance
        );
    }

    inline
    bool
    Interval::overlaps(Interval interval, double tolerance) const {
        return (
            interval.lowerBound() <= upperBound() + tolerance &&
            interval.upperBound() >= lowerBound() - tolerance
        );
    }

    inline
    bool
    Interval::strictlyOverlaps(Interval interval, double tolerance) const {
        return (
            interval.lowerBound() < upperBound() - tolerance &&
            interval.upperBound() > lowerBound() + tolerance
        );
    }

    inline
    bool
    Interval::equals(const Interval& other, double precision) {
        return (
            lowerBound() - other.lowerBound() == Zero(precision) &&
            upperBound() - other.upperBound() == Zero(precision)
        );
    }

    inline
    Interval&
    Interval::operator+=(double value) {
        *this = *this + value;
        return *this;
    }

    inline
    Interval&
    Interval::operator+=(Interval other) {
        *this = *this + other;
        return *this;
    }

    inline
    Interval&
    Interval::operator-=(double value) {
        *this = *this - value;
        return *this;
    }

    inline
    Interval&
    Interval::operator-=(Interval other) {
        *this = *this - other;
        return *this;
    }

    inline
    Interval&
    Interval::operator*=(double value) {
        *this = *this * value;
        return *this;
    }

    inline
    Interval&
    Interval::operator*=(Interval other) {
        *this = *this * other;
        return *this;
    }

    inline
    Interval&
    Interval::operator/=(double value) {
        *this = *this / value;
        return *this;
    }

    inline
    Interval&
    Interval::operator/=(Interval other) {
        *this = *this / other;
        return *this;
    }

    inline
    Interval
    Interval::EMPTY() {
        return Interval(
            std::numeric_limits<double>::quiet_NaN(),
            std::numeric_limits<double>::quiet_NaN()
        );
    }
    
    inline
    Interval
    Interval::WHOLE() {
        return Interval(
            -std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::infinity()
        );
    }

    inline
    Interval
    Interval::UNIT() {
        return Interval(0.0, 1.0);
    }
    
    inline
    Interval
    Interval::hull(double firstValue, double secondValue) {
        if (firstValue <= secondValue) {
            return Interval(firstValue, secondValue);
        } else {
            return Interval(secondValue, firstValue);
        }
    }

    inline
    Interval
    Interval::random() {
        return hull(double(std::rand()) / RAND_MAX, double(std::rand()) / RAND_MAX);
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
        return (
            firstInterval.lowerBound() == secondInterval.lowerBound() &&
            firstInterval.upperBound() == secondInterval.upperBound()
        );
    }

    inline
    bool
    operator!=(double value, Interval interval) {
        return value != interval.lowerBound() || value != interval.upperBound();
    }

    inline
    bool
    operator!=(Interval interval, double value) {
        return interval.lowerBound() != value || interval.upperBound() != value;
    }

    inline
    bool
    operator!=(Interval firstInterval, Interval secondInterval) {
        return (
            firstInterval.lowerBound() != secondInterval.lowerBound() ||
            firstInterval.upperBound() != secondInterval.upperBound()
        );
    }

    inline
    bool
    operator==(Interval interval, Zero zero) {
        return (
            interval.lowerBound() >= -zero.precision() &&
            interval.upperBound() <= zero.precision()
        );
    }

    inline
    bool
    operator!=(Interval interval, Zero zero) {
        return (
            !(interval.lowerBound() <= zero.precision()) ||
            !(interval.upperBound() >= -zero.precision())
        );
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
        if (value >= 0.0) {
            return Interval(value * interval.lowerBound(), value * interval.upperBound());
        } else {
            return Interval(value * interval.upperBound(), value * interval.lowerBound());
        }
    }

    inline
    Interval
    operator*(Interval interval, double value) {
        if (value >= 0.0) {
            return Interval(interval.lowerBound() * value, interval.upperBound() * value);
        } else {
            return Interval(interval.upperBound() * value, interval.lowerBound() * value);
        }
    }

    inline
    Interval
    operator*(Interval firstInterval, Interval secondInterval) {
        double ll = firstInterval.lowerBound() * secondInterval.lowerBound();
        double lu = firstInterval.lowerBound() * secondInterval.upperBound();
        double ul = firstInterval.upperBound() * secondInterval.lowerBound();
        double uu = firstInterval.upperBound() * secondInterval.upperBound();
        auto lPair = std::minmax(ll, lu);
        auto uPair = std::minmax(ul, uu);
        return Interval(std::min(lPair.first, uPair.first), std::max(lPair.second, uPair.second));
    }

    inline
    Interval
    operator/(double value, Interval interval) {
        if (interval.lowerBound() >= 0.0 || interval.upperBound() <= 0.0) {
            if (value > 0.0) {
                return Interval(value / interval.upperBound(), value / interval.lowerBound());
            } else if (value < 0.0) {
                return Interval(value / interval.lowerBound(), value / interval.upperBound());
            } else {
                return 0.0;
            }
        } else if (interval.isEmpty()) {
            return Interval::EMPTY();
        } else if (value == 0.0) {
            return 0.0;
        } else {
            return Interval::WHOLE();
        }
    }

    inline
    Interval
    operator/(Interval interval, double value) {
        if (value > 0.0) {
            double reciprocal = 1.0 / value;
            return Interval(interval.lowerBound() * reciprocal, interval.upperBound() * reciprocal);
        } else if (value < 0.0) {
            double reciprocal = 1.0 / value;
            return Interval(interval.upperBound() * reciprocal, interval.lowerBound() * reciprocal);
        } else if (interval.isEmpty()) {
            return Interval::EMPTY();
        } else {
            return Interval::WHOLE();
        }
    }

    inline
    Interval
    operator/(Interval firstInterval, Interval secondInterval) {
        if (secondInterval.lowerBound() >= 0.0 || secondInterval.upperBound() <= 0.0) {
            Interval reciprocal(
                1.0 / secondInterval.upperBound(),
                1.0 / secondInterval.lowerBound()
            );
            return firstInterval * reciprocal;
        } else if (firstInterval.isEmpty() || secondInterval.isEmpty()) {
            return Interval::EMPTY();
        } else if (firstInterval == 0.0) {
            return 0.0;
        } else {
            return Interval::WHOLE();
        }
    }

    inline
    Interval
    abs(Interval interval) {
        if (interval.isEmpty()) {
            return Interval::EMPTY();
        } else if (interval.lowerBound() >= 0.0) {
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
        if (interval.isEmpty() || interval.upperBound() < 0.0) {
            return Interval::EMPTY();
        } else {
            return Interval(
                sqrt(max(0.0, interval.lowerBound())),
                sqrt(interval.upperBound())
            );
        }
    }
}
