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
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isZero_overloads, isZero, 0, 1)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isEqualTo_overloads, isEqualTo, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isLessThan_overloads, isLessThan, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isGreaterThan_overloads, isGreaterThan, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isLessThanOrEqualTo_overloads, isLessThanOrEqualTo, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isGreaterThanOrEqualTo_overloads, isGreaterThanOrEqualTo, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isSubsetOf_overloads, isSubsetOf, 1, 2)
    BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(isProperSubsetOf_overloads, isProperSubsetOf, 1, 2)
    
    void bindDouble() {
        class_<Double>("Double")
            .def(init<double>())
            .def(init<Double>())
            .def("bounds", &Double::bounds)
            .def("hashValue", &Double::hashValue)
            .def("hull", &Double::hull)
            .def("isZero", &Double::isZero, isZero_overloads())
            .def("isEqualTo", &Double::isEqualTo, isEqualTo_overloads())
            .def("isLessThan", &Double::isLessThan, isLessThan_overloads())
            .def("isGreaterThan", &Double::isGreaterThan, isGreaterThan_overloads())
            .def("isLessThanOrEqualTo", &Double::isLessThanOrEqualTo, isLessThanOrEqualTo_overloads())
            .def("isGreaterThanOrEqualTo", &Double::isGreaterThanOrEqualTo, isGreaterThanOrEqualTo_overloads())
            .def("isSubsetOf", &Double::isSubsetOf, isSubsetOf_overloads())
            .def("isProperSubsetOf", &Double::isProperSubsetOf, isProperSubsetOf_overloads())
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
            .def(self + self)
            .def(int() - self)
            .def(float() - self)
            .def(double() - self)
            .def(self - self)
            .def(int() * self)
            .def(float() * self)
            .def(double() * self)
            .def(self * self)
            .def(int() / self)
            .def(float() / self)
            .def(double() / self)
            .def(self / self)
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
        def("exp", (Double (*)(Double))  &exp);
        def("exp", (double (*)(double)) &exp);
        def("log", (Double (*)(Double)) &log);
        def("log", (double (*)(double)) &log);
        
        implicitly_convertible<int, Double>();
        implicitly_convertible<float, Double>();
        implicitly_convertible<double, Double>();
    }
}
