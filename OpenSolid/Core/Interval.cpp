/*************************************************************************************
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
 *************************************************************************************/

#include <OpenSolid/Core/Interval.hpp>

#include <boost/numeric/interval.hpp>

#include <cmath>
#include <sstream>

namespace opensolid
{
    using namespace boost::numeric::interval_lib;

    typedef boost::numeric::interval<
        double,
        policies<
            save_state_nothing<rounded_transc_exact<double, rounded_arith_exact<double>>>,
            checking_base<double>
        >
    > BoostInterval;

    template <>
    struct Conversion<Interval, BoostInterval>
    {
        inline BoostInterval operator()(Interval interval) {
            return BoostInterval(interval.lowerBound(), interval.upperBound());
        }
    };

    template <>
    struct Conversion<BoostInterval, Interval>
    {
        inline Interval operator()(BoostInterval boostInterval) {
            return Interval(boostInterval.lower(), boostInterval.upper());
        }
    };
    
    Interval& Interval::operator*=(Interval interval) {
        BoostInterval self = this->as<BoostInterval>();
        BoostInterval other = interval.as<BoostInterval>();
        *this = Interval::from(self * other);
        return *this;
    }
    
    Interval& Interval::operator/=(Interval interval) {
        BoostInterval self = this->as<BoostInterval>();
        BoostInterval other = interval.as<BoostInterval>();
        *this = Interval::from(self / other);
        return *this;
    }
    
    Interval operator*(Interval firstInterval, Interval secondInterval) {
        return Interval::from(
            firstInterval.as<BoostInterval>() * secondInterval.as<BoostInterval>()
        );
    }

    Interval operator/(double value, Interval interval) {
        return Interval::from(value / interval.as<BoostInterval>());
    }

    Interval operator/(Interval firstInterval, Interval secondInterval) {
        return Interval::from(
            firstInterval.as<BoostInterval>() / secondInterval.as<BoostInterval>()
        );
    }

    Interval sin(Interval interval) {
        return Interval::from(boost::numeric::sin(interval.as<BoostInterval>()));
    }

    Interval cos(Interval interval) {
        return Interval::from(boost::numeric::cos(interval.as<BoostInterval>()));
    }

    Interval tan(Interval interval) {
        return Interval::from(boost::numeric::tan(interval.as<BoostInterval>()));
    }

    Interval asin(Interval interval) {
        return Interval::from(boost::numeric::asin(interval.as<BoostInterval>()));
    }

    Interval acos(Interval interval) {
        return Interval::from(boost::numeric::acos(interval.as<BoostInterval>()));
    }

    Interval atan(Interval interval) {
        return Interval::from(boost::numeric::atan(interval.as<BoostInterval>()));
    }

    Interval atan2(Interval yInterval, Interval xInterval) {
        if (xInterval.lowerBound() > 0.0) {
            return atan(yInterval / xInterval);
        } else if (yInterval.lowerBound() > 0.0) {
            return atan(-xInterval / yInterval) + M_PI / 2;
        } else if (yInterval.upperBound() < 0.0) {
            return atan(-xInterval / yInterval) - M_PI / 2;
        } else {
            return Interval(-M_PI, M_PI);
        }
    }

    Interval exp(Interval interval) {
        return Interval::from(boost::numeric::exp(interval.as<BoostInterval>()));
    }

    Interval log(Interval interval) {
        return Interval::from(boost::numeric::log(interval.as<BoostInterval>()));
    }

    Interval pow(Interval baseInterval, int exponentValue) {
        return Interval::from(
            boost::numeric::pow(baseInterval.as<BoostInterval>(), exponentValue)
        );
    }
    
    Interval pow(Interval baseInterval, double exponentValue) {
        return exp(log(baseInterval) * exponentValue);
    }
    
    Interval pow(Interval baseInterval, Interval exponentInterval) {
        return exp(log(baseInterval) * exponentInterval);
    }
    
    std::ostream& operator<<(std::ostream& stream, Interval interval) {
        if (interval.isEmpty()) {
            stream << "[]";
        } else if (interval.isSingleton()) {
            stream << "[" << interval.lowerBound() << "]";
        } else {
            stream << "[" << interval.lowerBound() << "," << interval.upperBound() << "]";
        }
        return stream;
    }
}
