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

#include "PythonModule.hpp"
#include "repr.hpp"
#include <OpenSolid/Core/Interval.hpp>

using namespace boost::python;

namespace opensolid
{
    double clampD(const Interval& interval, double argument) {
        return interval.clamp(argument);
    }

    Interval clampI(const Interval& interval, const Interval& argument) {
        return interval.clamp(argument);
    }

    double interpolatedD(const Interval& interval, double argument) {
        return interval.interpolated(argument);
    }

    Interval interpolatedI(const Interval& interval, const Interval& argument) {
        return interval.interpolated(argument);
    }

    tuple bisected(const Interval& argument) {
        std::pair<Interval, Interval> bisected = argument.bisected();
        return make_tuple(bisected.first, bisected.second);
    }

    bool overlaps(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.overlaps(second_argument);}

    bool overlapsP(
        const Interval& first_argument,
        const Interval& second_argument,
        double precision
    ) {return first_argument.overlaps(second_argument, precision);}

    bool strictlyOverlaps(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.strictlyOverlaps(second_argument);}

    bool strictlyOverlapsP(
        const Interval& first_argument,
        const Interval& second_argument,
        double precision
    ) {return first_argument.strictlyOverlaps(second_argument, precision);}

    bool containsD(
        const Interval& first_argument,
        double second_argument
    ) {return first_argument.contains(second_argument);}

    bool containsDP(
        const Interval& first_argument,
        double second_argument,
        double precision
    ) {return first_argument.contains(second_argument, precision);}

    bool containsI(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.contains(second_argument);}

    bool containsIP(
        const Interval& first_argument,
        const Interval& second_argument,
        double precision
    ) {return first_argument.contains(second_argument, precision);}

    bool strictlyContainsD(
        const Interval& first_argument,
        double second_argument
    ) {return first_argument.strictlyContains(second_argument);}

    bool strictlyContainsDP(
        const Interval& first_argument,
        double second_argument,
        double precision
    ) {return first_argument.strictlyContains(second_argument, precision);}

    bool strictlyContainsI(
        const Interval& first_argument,
        const Interval& second_argument
    ) {return first_argument.strictlyContains(second_argument);}

    bool strictlyContainsIP(
        const Interval& first_argument,
        const Interval& second_argument,
        double precision
    ) {return first_argument.strictlyContains(second_argument, precision);}

    std::string repr(const Interval& argument) {return __repr__(argument);}

    struct IntervalPickleSuite : public pickle_suite
    {
        static tuple getinitargs(const Interval& argument) {
            return make_tuple(argument.lowerBound(), argument.upperBound());
        }
    };
    
    void bindInterval() {
        class_<Interval>("Interval")
            .def(init<Interval>())
            .def(init<double, double>())
            .def("lower", &Interval::lower)
            .def("upper", &Interval::upper)
            .def("median", &Interval::median)
            .def("width", &Interval::width)
            .def("clamp", &clampI)
            .def("clamp", &clampD)
            .def("interpolated", &interpolatedI)
            .def("interpoloated", &interpolatedD)
            .def("random", &Interval::random)
            .def("squared", &Interval::squared)
            .def("isEmpty", &Interval::isEmpty)
            .def("isSingleton", &Interval::isSingleton)
            .def("bisected", &bisected)
            .def("hull", &Interval::hull)
            .def("intersection", &Interval::intersection)
            .def("overlaps", &overlaps)
            .def("overlaps", &overlapsP)
            .def("strictlyOverlaps", &strictlyOverlaps)
            .def("strictlyOverlaps", &strictlyOverlapsP)
            .def("contains", &containsI)
            .def("contains", &containsIP)
            .def("contains", &containsD)
            .def("contains", &containsDP)
            .def("__contains__", &containsI)
            .def("__contains__", &containsD)
            .def("strictlyContains", &strictlyContainsI)
            .def("strictlyContains", &strictlyContainsIP)
            .def("strictlyContains", &strictlyContainsD)
            .def("strictlyContains", &strictlyContainsDP)
            .def("Empty", &Interval::Empty)
                .staticmethod("Empty")
            .def("Whole", &Interval::Whole)
                .staticmethod("Whole")
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
            .def("__repr__", &repr)
            .def_pickle(IntervalPickleSuite());
        
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
