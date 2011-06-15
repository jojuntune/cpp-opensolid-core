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
    Interval sin(Interval argument) {return sin(argument.interval());}

    Interval cos(Interval argument) {return cos(argument.interval());}

    Interval tan(Interval argument) {return tan(argument.interval());}

    Interval asin(Interval argument) {return asin(argument.interval());}

    Interval acos(Interval argument) {return acos(argument.interval());}

    Interval atan(Interval argument) {return atan(argument.interval());}

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

    Interval exp(Interval argument) {return exp(argument.interval());}

    Interval log(Interval argument) {return log(argument.interval());}
    
    Interval pow(Interval base, Interval exponent) {
        return exp(log(base) * exponent);
    }
    
    std::ostream& operator<<(std::ostream& stream, Interval argument) {
        if (argument.empty()) {
            stream << "[]";
        } else if (argument.singleton()) {
            stream << "[" << argument.lower() << "]";
        } else {
            stream << "[" << argument.lower() << "," << argument.upper() << "]";
        }
        return stream;
    }
}
