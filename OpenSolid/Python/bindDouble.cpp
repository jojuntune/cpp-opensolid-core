/*****************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                     *
 *   ian.e.mackenzie@gmail.com                                               *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <OpenSolid/Scalar/Double.hpp>
#include <OpenSolid/Python/BoostPython.hpp>

using namespace boost::python;

namespace OpenSolid
{
    bool isZero(Double argument) {return argument.isZero();}
    
    bool isZeroP(Double argument, Double precision) {return argument.isZero(precision);}

    bool isEqualTo(Double first_argument, Double second_argument) {
        return first_argument.isEqualTo(second_argument);
    }

    bool isEqualToP(Double first_argument, Double second_argument, Double precision) {
        return first_argument.isEqualTo(second_argument, precision);
    }

    bool isNotEqualTo(Double first_argument, Double second_argument) {
        return first_argument.isNotEqualTo(second_argument);
    }

    bool isNotEqualToP(Double first_argument, Double second_argument, Double precision) {
        return first_argument.isNotEqualTo(second_argument, precision);
    }

    bool isLessThan(Double first_argument, Double second_argument) {
        return first_argument.isLessThan(second_argument);
    }

    bool isLessThanP(Double first_argument, Double second_argument, Double precision) {
        return first_argument.isLessThan(second_argument, precision);
    }

    bool isGreaterThan(Double first_argument, Double second_argument) {
        return first_argument.isGreaterThan(second_argument);
    }

    bool isGreaterThanP(Double first_argument, Double second_argument, Double precision) {
        return first_argument.isGreaterThan(second_argument, precision);
    }

    bool isLessThanOrEqualTo(Double first_argument, Double second_argument) {
        return first_argument.isLessThanOrEqualTo(second_argument);
    }

    bool isLessThanOrEqualToP(Double first_argument, Double second_argument, Double precision) {
        return first_argument.isLessThanOrEqualTo(second_argument, precision);
    }

    bool isGreaterThanOrEqualTo(Double first_argument, Double second_argument) {
        return first_argument.isGreaterThanOrEqualTo(second_argument);
    }

    bool isGreaterThanOrEqualToP(Double first_argument, Double second_argument, Double precision) {
        return first_argument.isGreaterThanOrEqualTo(second_argument, precision);
    }
    
    void bindDouble() {
        class_<Double>("Double")
            .def(init<Double>())
            .def(init<double>())
            .def("bounds", &Double::bounds)
            .def("hashValue", &Double::hashValue)
            .def("hull", &Double::hull)
            .def("isZero", &isZero)
            .def("isZero", &isZeroP)
            .def("isEqualTo", &isEqualTo)
            .def("isEqualTo", &isEqualToP)
            .def("isNotEqualTo", &isNotEqualTo)
            .def("isNotEqualTo", &isNotEqualToP)
            .def("isLessThan", &isLessThan)
            .def("isLessThan", &isLessThanP)
            .def("isGreaterThan", &isGreaterThan)
            .def("isGreaterThan", &isGreaterThanP)
            .def("isLessThanOrEqualTo", &isLessThanOrEqualTo)
            .def("isLessThanOrEqualTo", &isLessThanOrEqualToP)
            .def("isGreaterThanOrEqualTo", &isGreaterThanOrEqualTo)
            .def("isGreaterThanOrEqualTo", &isGreaterThanOrEqualToP)
            .def(self == self)
            .def(self == double())
            .def(double() == self)
            .def(self != self)
            .def(self != double())
            .def(double() != self)
            .def(self < self)
            .def(self < double())
            .def(double() < self)
            .def(self > self)
            .def(self > double())
            .def(double() > self)
            .def(self <= self)
            .def(self <= double())
            .def(double() <= self)
            .def(self >= self)
            .def(self >= double())
            .def(double() >= self)
            .def(-self)
            .def(self + self)
            .def(self + double())
            .def(double() + self)
            .def(self - self)
            .def(self - double())
            .def(double() - self)
            .def(self * self)
            .def(self * double())
            .def(double() * self)
            .def(self / self)
            .def(self / double())
            .def(double() / self)
            .def(self_ns::str(self));
        def("abs", (Double (*)(Double)) &abs);
        def("abs", (double (*)(double)) &abs);
        def("sqrt", (Double (*)(Double)) &sqrt);
        def("sqrt", (double (*)(double)) &sqrt);
        def("sin", (Double (*)(Double)) &sin);
        def("sin", (double (*)(double)) &sin);
        def("cos", (Double (*)(Double)) &cos);
        def("cos", (double (*)(double)) &cos);
        def("tan", (Double (*)(Double)) &tan);
        def("tan", (double (*)(double)) &tan);
        def("asin", (Double (*)(Double)) &asin);
        def("asin", (double (*)(double)) &asin);
        def("acos", (Double (*)(Double)) &acos);
        def("acos", (double (*)(double)) &acos);
        def("atan", (Double (*)(Double)) &atan);
        def("atan", (double (*)(double)) &atan);
        def("atan2", (Double (*)(Double, Double)) &atan2);
        def("atan2", (Double (*)(Double, double)) &atan2);
        def("atan2", (Double (*)(double, Double)) &atan2);
        def("atan2", (double (*)(double, double)) &atan2);
        def("exp", (Double (*)(Double))  &exp);
        def("exp", (double (*)(double)) &exp);
        def("log", (Double (*)(Double)) &log);
        def("log", (double (*)(double)) &log);
        def("pow", (Double (*)(Double, Double)) &pow);
        def("pow", (Double (*)(Double, double)) &pow);
        def("pow", (Double (*)(double, Double)) &pow);
        def("pow", (double (*)(double, double)) &pow);
        
        implicitly_convertible<double, Double>();
    }
}
