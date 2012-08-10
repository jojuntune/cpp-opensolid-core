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

#include <opensolid/core/scalar/Interval.hpp>
#include <opensolid/python/PythonModule.hpp>
#include <opensolid/python/repr.hpp>

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
            return make_tuple(argument.lower(), argument.upper());
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
        
        def("abs", (Interval (*)(const Interval&)) &abs);
        def("sqrt", (Interval (*)(const Interval&)) &sqrt);
        def("sin", (Interval (*)(const Interval&)) &sin);
        def("cos", (Interval (*)(const Interval&)) &cos);
        def("tan", (Interval (*)(const Interval&)) &tan);
        def("asin", (Interval (*)(const Interval&)) &asin);
        def("acos", (Interval (*)(const Interval&)) &acos);
        def("atan", (Interval (*)(const Interval&)) &atan);
        def("atan2", (Interval (*)(const Interval&, const Interval&)) &atan2);
        def("exp", (Interval (*)(const Interval&))  &exp);
        def("log", (Interval (*)(const Interval&)) &log);
        def("pow", (Interval (*)(const Interval&, int)) &pow);
        def("pow", (Interval (*)(const Interval&, double)) &pow);
        def("pow", (Interval (*)(const Interval&, const Interval&)) &pow);
    }
}
