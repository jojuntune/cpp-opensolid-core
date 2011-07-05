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
    
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isZero_overloads, isZero, 0, 1)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isEqualTo_overloads, isEqualTo, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isLessThan_overloads, isLessThan, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isGreaterThan_overloads, isGreaterThan, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isLessThanOrEqualTo_overloads, isLessThanOrEqualTo, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isGreaterThanOrEqualTo_overloads, isGreaterThanOrEqualTo, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(overlaps_overloads, overlaps, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isSubsetOf_overloads, isSubsetOf, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isProperSubsetOf_overloads, isProperSubsetOf, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isSupersetOf_overloads, isSupersetOf, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isProperSupersetOf_overloads, isProperSupersetOf, 1, 2)
    
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
            .def("squaredNorm", &Interval::squaredNorm)
            .def("empty", &Interval::empty)
            .def("singleton", &Interval::singleton)
            .def("bounds", &Interval::bounds)
            .def("hashValue", &Interval::hashValue)
            .def("bisected", &bisected)
            .def("hull", &Interval::hull)
            .def("intersection", &Interval::intersection)
            .def("isZero", &Interval::isZero, isZero_overloads())
            .def("isEqualTo", &Interval::isEqualTo, isEqualTo_overloads())
            .def("isLessThan", &Interval::isLessThan, isLessThan_overloads())
            .def("isGreaterThan", &Interval::isGreaterThan, isGreaterThan_overloads())
            .def("isLessThanOrEqualTo", &Interval::isLessThanOrEqualTo, isLessThanOrEqualTo_overloads())
            .def("isGreaterThanOrEqualTo", &Interval::isGreaterThanOrEqualTo, isGreaterThanOrEqualTo_overloads())
            .def("overlaps", &Interval::overlaps, overlaps_overloads())
            .def("isSubsetOf", &Interval::isSubsetOf, isSubsetOf_overloads())
            .def("isProperSubsetOf", &Interval::isProperSubsetOf, isProperSubsetOf_overloads())
            .def("isSupersetOf", &Interval::isSupersetOf, isSupersetOf_overloads())
            .def("isProperSupersetOf", &Interval::isProperSupersetOf, isProperSupersetOf_overloads())
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
