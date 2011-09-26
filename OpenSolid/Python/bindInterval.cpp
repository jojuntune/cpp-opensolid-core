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
#include <OpenSolid/Python/check.hpp>
#include <OpenSolid/Support/STL.hpp>

using namespace boost::python;

namespace OpenSolid
{
    struct ConvertListToInterval
    {
        ConvertListToInterval() {
            converter::registry::push_back(&convertible, &construct, type_id<Interval>());
        }

        static void* convertible(PyObject* argument) {
            return PyList_Check(argument) ? argument : nullptr;
        }

        static void construct(
            PyObject* argument_pointer,
            converter::rvalue_from_python_stage1_data* data
        ) {
            object argument(handle<>(borrowed(argument_pointer)));
            void* storage =
                ((converter::rvalue_from_python_storage<Interval>*) data)->storage.bytes;
            if (len(argument) == 1) {
                checkCompatiblePythonType<double>(argument[0], __func__);
                double value = extract<double>(argument[0]);
                new (storage) Interval(value);
            } else {
                checkSameSize(len(argument), 2, __func__);
                checkCompatiblePythonType<double>(argument[0], __func__);
                checkCompatiblePythonType<double>(argument[1], __func__);
                new (storage) Interval(extract<double>(argument[0]), extract<double>(argument[1]));
            }
            data->convertible = storage;
        }
    };

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

    std::string str(const Interval& argument) {
        std::stringstream stream;
        stream << argument;
        return stream.str();
    }

    std::string repr(const Interval& argument) {
        std::stringstream stream;
        stream << "Interval(" << argument.lower();
        if (argument.upper() != argument.lower()) {stream << "," << argument.upper();}
        stream << ")";
        return stream.str();
    }

    std::size_t hash(const Interval& argument) {return std::hash<Interval>()(argument);}

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
            .def("__str__", &str)
            .def("__repr__", &repr)
            .def("__hash__", &hash)
            .def_pickle(IntervalPickleSuite());
        
        implicitly_convertible<double, Interval>();
        ConvertListToInterval();
        
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
        def("pow", (Interval (*)(const Interval&, const Interval&)) &pow);
    }
}
