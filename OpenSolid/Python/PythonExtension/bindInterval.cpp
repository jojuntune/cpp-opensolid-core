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
************************************************************************************/

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Zero.hpp>
#include <OpenSolid/Python/PythonExtension.hpp>
#include <OpenSolid/Python/repr.hpp>

using namespace boost::python;

namespace opensolid
{
    double
    clampD(const Interval& interval, double argument) {
        return interval.clamp(argument);
    }

    Interval
    clampI(const Interval& interval, const Interval& argument) {
        return interval.clamp(argument);
    }

    double
    interpolatedD(const Interval& interval, double argument) {
        return interval.interpolated(argument);
    }

    Interval
    interpolatedI(const Interval& interval, const Interval& argument) {
        return interval.interpolated(argument);
    }

    tuple
    bisected(const Interval& argument) {
        std::pair<Interval, Interval> bisected = argument.bisected();
        return make_tuple(bisected.first, bisected.second);
    }

    bool
    overlaps(const Interval& firstArgument, const Interval& secondArgument) {
        return firstArgument.overlaps(secondArgument);
    }

    bool
    overlapsP(const Interval& firstArgument, const Interval& secondArgument, double precision) {
        return firstArgument.overlaps(secondArgument, precision);
    }

    bool
    strictlyOverlaps(const Interval& firstArgument, const Interval& secondArgument) {
        return firstArgument.strictlyOverlaps(secondArgument);
    }

    bool
    strictlyOverlapsP(
        const Interval& firstArgument,
        const Interval& secondArgument,
        double precision
    ) {
        return firstArgument.strictlyOverlaps(secondArgument, precision);
    }

    bool
    containsD(const Interval& firstArgument, double secondArgument) {
        return firstArgument.contains(secondArgument);
    }

    bool
    containsDP(const Interval& firstArgument, double secondArgument, double precision) {
        return firstArgument.contains(secondArgument, precision);
    }

    bool
    containsI(const Interval& firstArgument, const Interval& secondArgument) {
        return firstArgument.contains(secondArgument);
    }

    bool
    containsIP(const Interval& firstArgument, const Interval& secondArgument, double precision) {
        return firstArgument.contains(secondArgument, precision);
    }

    bool
    strictlyContainsD(const Interval& firstArgument, double secondArgument) {
        return firstArgument.strictlyContains(secondArgument);
    }

    bool
    strictlyContainsDP(const Interval& firstArgument, double secondArgument, double precision) {
        return firstArgument.strictlyContains(secondArgument, precision);
    }

    bool
    strictlyContainsI(const Interval& firstArgument, const Interval& secondArgument) {
        return firstArgument.strictlyContains(secondArgument);
    }

    bool
    strictlyContainsIP(
        const Interval& firstArgument,
        const Interval& secondArgument,
        double precision
    ) {
        return firstArgument.strictlyContains(secondArgument, precision);
    }

    std::string
    repr(const Interval& argument) {
        return __repr__(argument);
    }
    
    void
    bindInterval() {
        class_<Interval>("Interval")
            .def(init<Interval>())
            .def(init<double, double>())
            .add_property("lower_bound", &Interval::lowerBound)
            .add_property("upper_bound", &Interval::upperBound)
            .add_property("median", &Interval::median)
            .add_property("width", &Interval::width)
            .def("random_value", &Interval::randomValue)
            .def("clamp", &clampI)
            .def("clamp", &clampD)
            .def("interpolated", &interpolatedI)
            .def("interpoloated", &interpolatedD)
            .def("squared", &Interval::squared)
            .add_property("is_empty", &Interval::isEmpty)
            .add_property("is_singleton", &Interval::isSingleton)
            .def("bisected", &bisected)
            .def("hull", &Interval::hull)
            .def("intersection", &Interval::intersection)
            .def("contains", &containsI)
            .def("contains", &containsIP)
            .def("contains", &containsD)
            .def("contains", &containsDP)
            .def("__contains__", &containsI)
            .def("__contains__", &containsD)
            .def("strictly_contains", &strictlyContainsI)
            .def("strictly_contains", &strictlyContainsIP)
            .def("strictly_contains", &strictlyContainsD)
            .def("strictly_contains", &strictlyContainsDP)
            .def("overlaps", &overlaps)
            .def("overlaps", &overlapsP)
            .def("strictly_overlaps", &strictlyOverlaps)
            .def("strictly_overlaps", &strictlyOverlapsP)
            .def("unit", &Interval::Unit)
                .staticmethod("unit")
            .def("empty", &Interval::Empty)
                .staticmethod("empty")
            .def("whole", &Interval::Whole)
                .staticmethod("whole")
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
            .def(self == Zero())
            .def(self != Zero())
            .def(self < Zero())
            .def(self > Zero())
            .def(self <= Zero())
            .def(self >= Zero())
            .def(-self)
            .def(self += self)
            .def(self += double())
            .def(self + self)
            .def(self + double())
            .def(double() + self)
            .def(self -= self)
            .def(self -= double())
            .def(self - self)
            .def(self - double())
            .def(double() - self)
            .def(self *= self)
            .def(self *= double())
            .def(self * self)
            .def(self * double())
            .def(double() * self)
            .def(self /= self)
            .def(self /= double())
            .def(self / self)
            .def(self / double())
            .def(double() / self)
            .def("__repr__", &repr);
        
        implicitly_convertible<double, Interval>();
        
        def("abs", (Interval (*)(Interval)) &abs);
        def("sqrt", (Interval (*)(Interval)) &sqrt);
        def("sin", (Interval (*)(Interval)) &sin);
        def("cos", (Interval (*)(Interval)) &cos);
        def("tan", (Interval (*)(Interval)) &tan);
        def("asin", (Interval (*)(Interval)) &asin);
        def("acos", (Interval (*)(Interval)) &acos);
        def("atan", (Interval (*)(Interval)) &atan);
        def("atan2", (Interval (*)(Interval, Interval)) &atan2);
        def("exp", (Interval (*)(Interval))  &exp);
        def("log", (Interval (*)(Interval)) &log);
        def("pow", (Interval (*)(Interval, int)) &pow);
        def("pow", (Interval (*)(Interval, double)) &pow);
        def("pow", (Interval (*)(Interval, Interval)) &pow);
    }
}
