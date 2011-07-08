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
    Interval sin(const Interval& argument) {return boost::numeric::sin(argument.value());}

    Interval cos(const Interval& argument) {return boost::numeric::cos(argument.value());}

    Interval tan(const Interval& argument) {return boost::numeric::tan(argument.value());}

    Interval asin(const Interval& argument) {return boost::numeric::asin(argument.value());}

    Interval acos(const Interval& argument) {return boost::numeric::acos(argument.value());}

    Interval atan(const Interval& argument) {return boost::numeric::atan(argument.value());}

    Interval atan2(int y, const Interval& x) {
        if (x.lower() > 0.0) {
            return atan(double(y) / x);
        } else if (double(y) > 0.0) {
            return atan(-x / double(y)) + M_PI / 2;
        } else if (double(y) < 0.0) {
            return atan(-x / double(y)) - M_PI / 2;
        } else {
            return Interval(-M_PI, M_PI);
        }
    }

    Interval atan2(double y, const Interval& x) {
        if (x.lower() > 0.0) {
            return atan(y / x);
        } else if (y > 0.0) {
            return atan(-x / y) + M_PI / 2;
        } else if (y < 0.0) {
            return atan(-x / y) - M_PI / 2;
        } else {
            return Interval(-M_PI, M_PI);
        }
    }

    Interval atan2(Double y, const Interval& x) {
        if (x.lower() > 0.0) {
            return atan(y / x);
        } else if (y > 0.0) {
            return atan(-x / y) + M_PI / 2;
        } else if (y < 0.0) {
            return atan(-x / y) - M_PI / 2;
        } else {
            return Interval(-M_PI, M_PI);
        }
    }

    Interval atan2(const Interval& y, int x) {
        if (double(x) > 0.0) {
            return atan(y / double(x));
        } else if (y.lower() > 0.0) {
            return atan(-double(x) / y) + M_PI / 2;
        } else if (y.upper() < 0.0) {
            return atan(-double(x) / y) - M_PI / 2;
        } else {
            return Interval(-M_PI, M_PI);
        }
    }

    Interval atan2(const Interval& y, double x) {
        if (x > 0.0) {
            return atan(y / x);
        } else if (y.lower() > 0.0) {
            return atan(-x / y) + M_PI / 2;
        } else if (y.upper() < 0.0) {
            return atan(-x / y) - M_PI / 2;
        } else {
            return Interval(-M_PI, M_PI);
        }
    }

    Interval atan2(const Interval& y, Double x) {
        if (x > 0.0) {
            return atan(y / x);
        } else if (y.lower() > 0.0) {
            return atan(-x / y) + M_PI / 2;
        } else if (y.upper() < 0.0) {
            return atan(-x / y) - M_PI / 2;
        } else {
            return Interval(-M_PI, M_PI);
        }
    }

    Interval atan2(const Interval& y, const Interval& x) {
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

    Interval exp(const Interval& argument) {return boost::numeric::exp(argument.value());}

    Interval log(const Interval& argument) {return boost::numeric::log(argument.value());}
    
    Interval pow(int base, const Interval& exponent) {return exp(log(double(base)) * exponent);}
    
    Interval pow(double base, const Interval& exponent) {return exp(log(base) * exponent);}
    
    Interval pow(Double base, const Interval& exponent) {return exp(log(base) * exponent);}
    
    Interval pow(const Interval& base, int exponent) {return exp(log(base) * double(exponent));}
    
    Interval pow(const Interval& base, double exponent) {return exp(log(base) * exponent);}
    
    Interval pow(const Interval& base, Double exponent) {return exp(log(base) * exponent);}
    
    Interval pow(const Interval& base, const Interval& exponent) {return exp(log(base) * exponent);}
    
    std::ostream& operator<<(std::ostream& stream, const Interval& argument) {
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
