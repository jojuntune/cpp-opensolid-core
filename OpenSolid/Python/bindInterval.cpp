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

#include <OpenSolid/Scalar/Interval.hpp>
#include <OpenSolid/Python/BoostPython.hpp>

using namespace boost::python;

namespace OpenSolid
{
    tuple bisected(const Interval& argument) {
        std::pair<Interval, Interval> bisected = argument.bisected();
        return make_tuple(bisected.first, bisected.second);
    }

    bool isZero(const Interval& argument) {return argument.isZero();}

    bool isZeroP(const Interval& argument, Double precision) {return argument.isZero(precision);}

    bool isEqualToD(
        const Interval& first_argument,
        Double second_argument
    ) {return first_argument.isEqualTo(second_argument);}

    bool isEqualToDP(
        const Interval& first_argument,
        Double second_argument,
        Double precision
    ) {return first_argument.isEqualTo(second_argument, precision);}

    bool isEqualToI(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.isEqualTo(second_argument);}

    bool isEqualToIP(
        const Interval& first_argument,
        const Interval& second_argument,
        Double precision
    ) {return first_argument.isEqualTo(second_argument, precision);}

    bool isLessThanD(
        const Interval& first_argument,
        Double second_argument
    ) {return first_argument.isLessThan(second_argument);}

    bool isLessThanDP(
        const Interval& first_argument,
        Double second_argument,
        Double precision
    ) {return first_argument.isLessThan(second_argument, precision);}

    bool isLessThanI(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.isLessThan(second_argument);}

    bool isLessThanIP(
        const Interval& first_argument,
        const Interval& second_argument,
        Double precision
    ) {return first_argument.isLessThan(second_argument, precision);}

    bool isGreaterThanD(
        const Interval& first_argument,
        Double second_argument
    ) {return first_argument.isGreaterThan(second_argument);}

    bool isGreaterThanDP(
        const Interval& first_argument,
        Double second_argument,
        Double precision
    ) {return first_argument.isGreaterThan(second_argument, precision);}

    bool isGreaterThanI(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.isGreaterThan(second_argument);}

    bool isGreaterThanIP(
        const Interval& first_argument,
        const Interval& second_argument,
        Double precision
    ) {return first_argument.isGreaterThan(second_argument, precision);}

    bool isLessThanOrEqualToD(
        const Interval& first_argument,
        Double second_argument
    ) {return first_argument.isLessThanOrEqualTo(second_argument);}

    bool isLessThanOrEqualToDP(
        const Interval& first_argument,
        Double second_argument,
        Double precision
    ) {return first_argument.isLessThanOrEqualTo(second_argument, precision);}

    bool isLessThanOrEqualToI(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.isLessThanOrEqualTo(second_argument);}

    bool isLessThanOrEqualToIP(
        const Interval& first_argument,
        const Interval& second_argument,
        Double precision
    ) {return first_argument.isLessThanOrEqualTo(second_argument, precision);}

    bool isGreaterThanOrEqualToD(
        const Interval& first_argument,
        Double second_argument
    ) {return first_argument.isGreaterThanOrEqualTo(second_argument);}

    bool isGreaterThanOrEqualToDP(
        const Interval& first_argument,
        Double second_argument,
        Double precision
    ) {return first_argument.isGreaterThanOrEqualTo(second_argument, precision);}

    bool isGreaterThanOrEqualToI(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.isGreaterThanOrEqualTo(second_argument);}

    bool isGreaterThanOrEqualToIP(
        const Interval& first_argument,
        const Interval& second_argument,
        Double precision
    ) {return first_argument.isGreaterThanOrEqualTo(second_argument, precision);}

    bool overlaps(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.overlaps(second_argument);}

    bool overlapsP(
        const Interval& first_argument,
        const Interval& second_argument,
        Double precision
    ) {return first_argument.overlaps(second_argument, precision);}

    bool strictlyOverlaps(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.strictlyOverlaps(second_argument);}

    bool strictlyOverlapsP(
        const Interval& first_argument,
        const Interval& second_argument,
        Double precision
    ) {return first_argument.strictlyOverlaps(second_argument, precision);}

    bool containsD(
        const Interval& first_argument,
        Double second_argument
    ) {return first_argument.contains(second_argument);}

    bool containsDP(
        const Interval& first_argument,
        Double second_argument,
        Double precision
    ) {return first_argument.contains(second_argument, precision);}

    bool containsI(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.contains(second_argument);}

    bool containsIP(
        const Interval& first_argument,
        const Interval& second_argument,
        Double precision
    ) {return first_argument.contains(second_argument, precision);}

    bool strictlyContainsD(
        const Interval& first_argument,
        Double second_argument
    ) {return first_argument.strictlyContains(second_argument);}

    bool strictlyContainsDP(
        const Interval& first_argument,
        Double second_argument,
        Double precision
    ) {return first_argument.strictlyContains(second_argument, precision);}

    bool strictlyContainsI(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.strictlyContains(second_argument);}

    bool strictlyContainsIP(
        const Interval& first_argument,
        const Interval& second_argument,
        Double precision
    ) {return first_argument.strictlyContains(second_argument, precision);}
    
    void bindInterval() {
        class_<Interval>("Interval")
            .def(init<double>())
            .def(init<double, double>())
            .def(init<Double>())
            .def(init<Double, Double>())
            .def(init<Interval>())
            .def("lower", &Interval::lower)
            .def("upper", &Interval::upper)
            .def("median", &Interval::median)
            .def("width", &Interval::width)
            .def("squared", &Interval::squared)
            .def("isEmpty", &Interval::isEmpty)
            .def("isSingleton", &Interval::isSingleton)
            .def("bounds", &Interval::bounds)
            .def("hashValue", &Interval::hashValue)
            .def("bisected", &bisected)
            .def("hull", &Interval::hull)
            .def("intersection", &Interval::intersection)
            .def("isZero", &isZero)
            .def("isZero", &isZeroP)
            .def("isEqualTo", &isEqualToI)
            .def("isEqualTo", &isEqualToIP)
            .def("isEqualTo", &isEqualToD)
            .def("isEqualTo", &isEqualToDP)
            .def("isLessThan", &isLessThanI)
            .def("isLessThan", &isLessThanIP)
            .def("isLessThan", &isLessThanD)
            .def("isLessThan", &isLessThanDP)
            .def("isGreaterThan", &isGreaterThanI)
            .def("isGreaterThan", &isGreaterThanIP)
            .def("isGreaterThan", &isGreaterThanD)
            .def("isGreaterThan", &isGreaterThanDP)
            .def("isLessThanOrEqualTo", &isLessThanOrEqualToI)
            .def("isLessThanOrEqualTo", &isLessThanOrEqualToIP)
            .def("isLessThanOrEqualTo", &isLessThanOrEqualToD)
            .def("isLessThanOrEqualTo", &isLessThanOrEqualToDP)
            .def("isGreaterThanOrEqualTo", &isGreaterThanOrEqualToI)
            .def("isGreaterThanOrEqualTo", &isGreaterThanOrEqualToIP)
            .def("isGreaterThanOrEqualTo", &isGreaterThanOrEqualToD)
            .def("isGreaterThanOrEqualTo", &isGreaterThanOrEqualToDP)
            .def("overlaps", &overlaps)
            .def("overlaps", &overlapsP)
            .def("strictlyOverlaps", &strictlyOverlaps)
            .def("strictlyOverlaps", &strictlyOverlapsP)
            .def("contains", &containsI)
            .def("contains", &containsIP)
            .def("contains", &containsD)
            .def("contains", &containsDP)
            .def("strictlyContains", &strictlyContainsI)
            .def("strictlyContains", &strictlyContainsIP)
            .def("strictlyContains", &strictlyContainsD)
            .def("strictlyContains", &strictlyContainsDP)
            .def("Empty", &Interval::Empty).staticmethod("Empty")
            .def("Whole", &Interval::Whole).staticmethod("Whole")
            .def(self == self)
            .def(self != self)
            .def(self < self)
            .def(self > self)
            .def(self <= self)
            .def(self >= self)
            .def(-self)
            .def(int() + self)
            .def(float() + self)
            .def(double() + self)
            .def(Double() + self)
            .def(self + self)
            .def(int() - self)
            .def(float() - self)
            .def(double() - self)
            .def(Double() - self)
            .def(self - self)
            .def(int() * self)
            .def(float() * self)
            .def(double() * self)
            .def(Double() * self)
            .def(self * self)
            .def(int() / self)
            .def(float() / self)
            .def(double() / self)
            .def(Double() / self)
            .def(self / self)
            .def(self_ns::str(self));
        def("abs", (Interval (*)(const Interval&)) &abs);
        def("sqrt", (Interval (*)(const Interval&)) &sqrt);
        def("sin", (Interval (*)(const Interval&)) &sin);
        def("cos", (Interval (*)(const Interval&)) &cos);
        def("tan", (Interval (*)(const Interval&)) &tan);
        def("asin", (Interval (*)(const Interval&)) &asin);
        def("acos", (Interval (*)(const Interval&)) &acos);
        def("atan", (Interval (*)(const Interval&)) &atan);
        def("exp", (Interval (*)(const Interval&))  &exp);
        def("log", (Interval (*)(const Interval&)) &log);
        
        implicitly_convertible<int, Interval>();
        implicitly_convertible<float, Interval>();
        implicitly_convertible<double, Interval>();
        implicitly_convertible<Double, Interval>();
    }
}
