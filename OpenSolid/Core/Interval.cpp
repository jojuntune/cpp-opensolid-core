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
*************************************************************************************/

#include <OpenSolid/Core/Interval.hpp>

#include <boost/numeric/interval.hpp>

#include <cmath>

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
    struct ConversionFunction<Interval, BoostInterval>
    {
        inline
        BoostInterval
        operator()(Interval interval) {
            return BoostInterval(interval.lowerBound(), interval.upperBound());
        }
    };

    template <>
    struct ConversionFunction<BoostInterval, Interval>
    {
        inline
        Interval
        operator()(BoostInterval boostInterval) {
            return Interval(boostInterval.lower(), boostInterval.upper());
        }
    };
    
    Interval&
    Interval::operator*=(Interval interval) {
        BoostInterval self = this->to<BoostInterval>();
        BoostInterval other = interval.to<BoostInterval>();
        *this = Interval::From(self * other);
        return *this;
    }
    
    Interval&
    Interval::operator/=(Interval interval) {
        BoostInterval self = this->to<BoostInterval>();
        BoostInterval other = interval.to<BoostInterval>();
        *this = Interval::From(self / other);
        return *this;
    }
    
    Interval
    operator*(Interval firstInterval, Interval secondInterval) {
        return Interval::From(
            firstInterval.to<BoostInterval>() * secondInterval.to<BoostInterval>()
        );
    }

    Interval
    operator/(double value, Interval interval) {
        return Interval::From(value / interval.to<BoostInterval>());
    }

    Interval
    operator/(Interval firstInterval, Interval secondInterval) {
        return Interval::From(
            firstInterval.to<BoostInterval>() / secondInterval.to<BoostInterval>()
        );
    }

    Interval
    sin(Interval interval) {
        return Interval::From(boost::numeric::sin(interval.to<BoostInterval>()));
    }

    Interval
    cos(Interval interval) {
        return Interval::From(boost::numeric::cos(interval.to<BoostInterval>()));
    }

    Interval
    tan(Interval interval) {
        return Interval::From(boost::numeric::tan(interval.to<BoostInterval>()));
    }

    Interval
    asin(Interval interval) {
        return Interval::From(boost::numeric::asin(interval.to<BoostInterval>()));
    }

    Interval
    acos(Interval interval) {
        return Interval::From(boost::numeric::acos(interval.to<BoostInterval>()));
    }

    Interval
    atan(Interval interval) {
        return Interval::From(boost::numeric::atan(interval.to<BoostInterval>()));
    }

    Interval
    atan2(Interval yInterval, Interval xInterval) {
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

    Interval
    exp(Interval interval) {
        return Interval::From(boost::numeric::exp(interval.to<BoostInterval>()));
    }

    Interval
    log(Interval interval) {
        return Interval::From(boost::numeric::log(interval.to<BoostInterval>()));
    }

    Interval
    pow(Interval baseInterval, int exponentValue) {
        return Interval::From(
            boost::numeric::pow(baseInterval.to<BoostInterval>(), exponentValue)
        );
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
