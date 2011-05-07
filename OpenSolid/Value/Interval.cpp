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

#include <cmath>

#include <boost/numeric/interval.hpp>

#include "Interval.hpp"

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
            
    Interval sin(const Interval& argument) {
        BoostInterval temp = boost::numeric::sin(BoostInterval(argument.lower(), argument.upper()));
        return Interval(temp.lower(), temp.upper());
    }

    Interval cos(const Interval& argument) {
        BoostInterval temp = boost::numeric::cos(BoostInterval(argument.lower(), argument.upper()));
        return Interval(temp.lower(), temp.upper());
    }

    Interval tan(const Interval& argument) {
        BoostInterval temp = boost::numeric::tan(BoostInterval(argument.lower(), argument.upper()));
        return Interval(temp.lower(), temp.upper());
    }

    Interval asin(const Interval& argument) {
        BoostInterval temp = boost::numeric::asin(BoostInterval(argument.lower(), argument.upper()));
        return Interval(temp.lower(), temp.upper());
    }

    Interval acos(const Interval& argument) {
        BoostInterval temp = boost::numeric::acos(BoostInterval(argument.lower(), argument.upper()));
        return Interval(temp.lower(), temp.upper());
    }

    Interval atan(const Interval& argument) {
        return Interval(atan(argument.lower()), atan(argument.upper()));
    }

    Interval atan2(const Interval& y, const Interval& x) {
        if (x > 0.0) {
            return atan(y / x);
        } else if (y > 0.0) {
            return atan(-x / y) + M_PI / 2;
        } else if (y < 0.0) {
            return atan(-x / y) - M_PI / 2;
        } else {
            return Interval(-M_PI, M_PI);
        }
    }

    Interval exp(const Interval& argument) {
        return Interval(exp(argument.lower()), exp(argument.upper()));
    }

    Interval log(const Interval& argument) {
        return Interval(log(argument.lower()), log(argument.upper()));
    }
    
    Interval pow(const Interval& base, const Interval& exponent) {
        return exp(log(base) * exponent);
    }
    
    std::ostream& operator<<(std::ostream& stream, const Interval& value) {
        if (
            value.lower() == std::numeric_limits<double>::infinity() &&
            value.upper() == -std::numeric_limits<double>::infinity()
        ) {
            stream << "[]";
        } else if (value.lower() == value.upper()) {
            stream << "[" << value.lower() << "]";
        } else {
            stream << "[" << value.lower() << "," << value.upper() << "]";
        }
        return stream;
    }
}
