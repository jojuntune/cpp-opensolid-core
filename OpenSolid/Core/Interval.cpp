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
        inline BoostInterval operator()(Interval argument) {
            return BoostInterval(argument.lower(), argument.upper());
        }
    };

    template <>
    struct Conversion<BoostInterval, Interval>
    {
        inline Interval operator()(BoostInterval argument) {
            return Interval(argument.lower(), argument.upper());
        }
    };
    
    Interval& Interval::operator*=(Interval argument) {
        BoostInterval self = this->as<BoostInterval>();
        BoostInterval other = argument.as<BoostInterval>();
        *this = Interval::from(self * other);
        return *this;
    }
    
    Interval& Interval::operator/=(Interval argument) {
        BoostInterval self = this->as<BoostInterval>();
        BoostInterval other = argument.as<BoostInterval>();
        *this = Interval::from(self / other);
        return *this;
    }
    
    Interval operator*(Interval first_argument, Interval second_argument) {
        return Interval::from(
            first_argument.as<BoostInterval>() * second_argument.as<BoostInterval>()
        );
    }

    Interval operator/(double first_argument, Interval second_argument) {
        return Interval::from(first_argument / second_argument.as<BoostInterval>());
    }

    Interval operator/(Interval first_argument, Interval second_argument) {
        return Interval::from(
            first_argument.as<BoostInterval>() / second_argument.as<BoostInterval>()
        );
    }

    Interval sin(Interval argument) {
        return Interval::from(boost::numeric::sin(argument.as<BoostInterval>()));
    }

    Interval cos(Interval argument) {
        return Interval::from(boost::numeric::cos(argument.as<BoostInterval>()));
    }

    Interval tan(Interval argument) {
        return Interval::from(boost::numeric::tan(argument.as<BoostInterval>()));
    }

    Interval asin(Interval argument) {
        return Interval::from(boost::numeric::asin(argument.as<BoostInterval>()));
    }

    Interval acos(Interval argument) {
        return Interval::from(boost::numeric::acos(argument.as<BoostInterval>()));
    }

    Interval atan(Interval argument) {
        return Interval::from(boost::numeric::atan(argument.as<BoostInterval>()));
    }

    Interval atan2(Interval y, Interval x) {
        if (x.lower() > 0.0) {
            return atan(y / x);
        } else if (y.lower() > 0.0) {
            return atan(-x / y) + M_PI / 2;
        } else if (y.upper() < 0.0) {
            return atan(-x / y) - M_PI / 2;
        } else {
            return Interval(-M_PI, M_PI);
        }
    }

    Interval exp(Interval argument) {
        return Interval::from(boost::numeric::exp(argument.as<BoostInterval>()));
    }

    Interval log(Interval argument) {
        return Interval::from(boost::numeric::log(argument.as<BoostInterval>()));
    }

    Interval pow(Interval argument, int exponent) {
        return Interval::from(boost::numeric::pow(argument.as<BoostInterval>(), exponent));
    }
    
    Interval pow(Interval base, double exponent) {return exp(log(base) * exponent);}
    
    Interval pow(Interval base, Interval exponent) {return exp(log(base) * exponent);}
    
    std::ostream& operator<<(std::ostream& stream, Interval argument) {
        if (argument.isEmpty()) {
            stream << "[]";
        } else if (argument.isSingleton()) {
            stream << "[" << argument.lower() << "]";
        } else {
            stream << "[" << argument.lower() << "," << argument.upper() << "]";
        }
        return stream;
    }
}
