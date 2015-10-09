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

#include <OpenSolid/Core/Interval.hpp>

#include <cmath>

namespace opensolid
{
    Interval
    sin(Interval interval) {
        return cos(interval - M_PI / 2.0);
    }

    Interval
    cos(Interval interval) { 
        Interval absolute = abs(interval);
        double width = absolute.width();
        bool hasMin = std::fmod(absolute.upperBound() + M_PI, 2 * M_PI) <= width;
        bool hasMax = std::fmod(absolute.upperBound(), 2 * M_PI) <= width;
        if (hasMin && hasMax) {
            return Interval(-1.0, 1.0);
        } else {
            double cosLower = std::cos(absolute.lowerBound());
            double cosUpper = std::cos(absolute.upperBound());
            auto sorted = std::minmax(cosLower, cosUpper);
            return Interval(hasMin ? -1.0 : sorted.first, hasMax ? 1.0 : sorted.second);
        }
    }

    Interval
    tan(Interval interval) {
        Interval absolute = abs(interval);
        bool hasSingularity = std::fmod(absolute.upperBound() + M_PI / 2, M_PI) <= absolute.width();
        if (hasSingularity) {
            return Interval::WHOLE();
        } else {
            return Interval(std::tan(interval.lowerBound()), std::tan(interval.upperBound()));
        }
    }

    Interval
    asin(Interval interval) {
        if (interval.isEmpty() || interval.lowerBound() > 1.0 || interval.upperBound() < -1.0) {
            return Interval::EMPTY();
        } else {
            return Interval(
                asin(max(interval.lowerBound(), -1.0)),
                asin(min(interval.upperBound(), 1.0))
            );
        }
    }

    Interval
    acos(Interval interval) {
        if (interval.isEmpty() || interval.lowerBound() > 1.0 || interval.upperBound() < -1.0) {
            return Interval::EMPTY();
        } else {
            return Interval(
                acos(min(interval.upperBound(), 1.0)),
                acos(max(interval.lowerBound(), -1.0))
            );
        }
    }

    Interval
    atan(Interval interval) {
        return Interval(atan(interval.lowerBound()), atan(interval.upperBound()));
    }

    Interval
    atan2(Interval yInterval, Interval xInterval) {
        if (yInterval.isEmpty() || xInterval.isEmpty()) {
            return Interval::EMPTY();
        } else if (xInterval.lowerBound() > 0.0) {
            return atan(yInterval / xInterval);
        } else if (yInterval.lowerBound() > 0.0) {
            return atan(-xInterval / yInterval) + M_PI / 2;
        } else if (yInterval.upperBound() < 0.0) {
            return atan(-xInterval / yInterval) - M_PI / 2;
        } else {
            return Interval(-M_PI, M_PI);
        }
    }

    Interval
    exp(Interval interval) {
        if (interval.isEmpty()) {
            return Interval::EMPTY();
        } else {
            return Interval(exp(interval.lowerBound()), exp(interval.upperBound()));
        }
    }

    Interval
    log(Interval interval) {
        if (interval.isEmpty() || interval.upperBound() < 0.0) {
            return Interval::EMPTY();
        } else if (interval.lowerBound() > 0.0) {
            return Interval(log(interval.lowerBound()), log(interval.upperBound()));
        } else if (interval.upperBound() > 0.0) {
            return Interval(-std::numeric_limits<double>::infinity(), log(interval.upperBound()));
        } else {
            return -std::numeric_limits<double>::infinity();
        }
    }
    
    Interval
    pow(Interval baseInterval, double exponentValue) {
        return exp(log(baseInterval) * exponentValue);
    }
    
    Interval
    pow(Interval baseInterval, Interval exponentInterval) {
        return exp(log(baseInterval) * exponentInterval);
    }
    
    std::ostream&
    operator<<(std::ostream& stream, Interval interval) {
        stream << "Interval";
        if (interval.isEmpty()) {
            stream << "()";
        } else if (interval.isSingleton()) {
            stream << "(" << interval.lowerBound() << ")";
        } else {
            stream << "(" << interval.lowerBound() << "," << interval.upperBound() << ")";
        }
        return stream;
    }
}
