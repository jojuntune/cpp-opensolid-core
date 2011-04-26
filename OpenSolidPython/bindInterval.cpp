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

#include <boost/python.hpp>

#include <OpenSolid/Value/Interval.hpp>
#include <OpenSolid/Value/Matrix.hpp>

using namespace boost::python;

namespace OpenSolid
{
    tuple bisected(const Interval& argument) {
        Pair<Interval> bisected = argument.bisected();
        return make_tuple(bisected.first(), bisected.second());
    }
    
    bool overlapId(const Interval& first_argument, double second_argument) {
        return first_argument.overlap(second_argument);
    }
    
    bool overlapII(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.overlap(second_argument);
    }
    
    bool containId(const Interval& first_argument, double second_argument) {
        return first_argument.contain(second_argument);
    }
    
    bool containII(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.contain(second_argument);
    }
    
    bool adjacentId(const Interval& first_argument, double second_argument) {
        return first_argument.adjacent(second_argument);
    }
    
    bool adjacentII(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.adjacent(second_argument);
    }
    
    Interval hullId(const Interval& first_argument, double second_argument) {
        return first_argument.hull(second_argument);
    }
    
    Interval hullII(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.hull(second_argument);
    }
    
    Interval intersectionId(const Interval& first_argument, double second_argument) {
        return first_argument.intersection(second_argument);
    }
    
    Interval intersectionII(const Interval& first_argument, const Interval& second_argument) {
        return first_argument.intersection(second_argument);
    }
    
    void bindInterval() {
        class_<Interval>("Interval")
            .def(init<double>())
            .def(init<double, double>())
            .def(init<Interval>())
            .def("isEmpty", &Interval::isEmpty)
            .def("lower", &lowerBound)
            .def("upper", &upperBound)
            .def("median", &Interval::median)
            .def("width", &Interval::width)
            .def("centered", &Interval::centered)
            .def("bisected", &bisected)
            .def("squared", &Interval::squared)
            .def("hull", &hullId)
            .def("hull", &hullII)
            .def("overlap", &overlapId)
            .def("overlap", &overlapII)
            .def("contain", &containId)
            .def("contain", &containII)
            .def("adjacent", &adjacentId)
            .def("adjacent", &adjacentII)
            .def("hull", &hullId)
            .def("hull", &hullII)
            .def("intersection", &intersectionId)
            .def("intersection", &intersectionII)
            .def("empty", &Interval::empty).staticmethod("empty")
            .def("whole", &Interval::whole).staticmethod("whole")
            .def(self == self)
            .def(self == int())
            .def(self == float())
            .def(self == double())
            .def(int() == self)
            .def(float() == self)
            .def(double() == self)
            .def(-self)
            .def(self + double())
            .def(double() + self)
            .def(self + self)
            .def(self - double())
            .def(double() - self)
            .def(self - self)
            .def(self * double())
            .def(double() * self)
            .def(self * self)
            .def(self / double())
            .def(double() / self)
            .def(self / self)
            .def(self_ns::str(self));
        def("abs", (Interval (*)(const Interval&)) &abs);
        def("abs", (double (*)(double)) &abs);
        def("sqrt", (Interval (*)(const Interval&)) &sqrt);
        def("sqrt", (double (*)(double)) &sqrt);
        def("exp", (Interval (*)(const Interval&))  &exp);
        def("exp", (double (*)(double)) &exp);
        def("log", (Interval (*)(const Interval&)) &log);
        def("log", (double (*)(double)) &log);
        def("sin", (Interval (*)(const Interval&)) &sin);
        def("sin", (double (*)(double)) &sin);
        def("cos", (Interval (*)(const Interval&)) &cos);
        def("cos", (double (*)(double)) &cos);
        def("tan", (Interval (*)(const Interval&)) &tan);
        def("tan", (double (*)(double)) &tan);
        def("asin", (Interval (*)(const Interval&)) &asin);
        def("asin", (double (*)(double)) &asin);
        def("acos", (Interval (*)(const Interval&)) &acos);
        def("acos", (double (*)(double)) &acos);
        def("atan", (Interval (*)(const Interval&)) &atan);
        def("atan", (double (*)(double)) &atan);
        
        implicitly_convertible<double, Interval>();
    }
}
