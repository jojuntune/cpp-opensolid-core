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

#include "PythonModule.hpp"
#include <OpenSolid/util/Zero.hpp>
#include <OpenSolid/Core/Interval.hpp>

using namespace boost::python;

namespace opensolid
{
    bool equalI(const Zero& zero, const Interval& argument) {
        return argument == zero;
    }

    bool equalD(const Zero& zero, double argument) {
        return argument == zero;
    }

    bool notEqualI(const Zero& zero, const Interval& argument) {
        return argument != zero;
    }

    bool notEqualD(const Zero& zero, double argument) {
        return argument != zero;
    }

    bool lessI(const Zero& zero, const Interval& argument) {
        return argument > zero;
    }

    bool lessD(const Zero& zero, double argument) {
        return argument > zero;
    }

    bool greaterI(const Zero& zero, const Interval& argument) {
        return argument < zero;
    }

    bool greaterD(const Zero& zero, double argument) {
        return argument < zero;
    }

    bool lessOrEqualI(const Zero& zero, const Interval& argument) {
        return argument >= zero;
    }

    bool lessOrEqualD(const Zero& zero, double argument) {
        return argument >= zero;
    }

    bool greaterOrEqualI(const Zero& zero, const Interval& argument) {
        return argument <= zero;
    }

    bool greaterOrEqualD(const Zero& zero, double argument) {
        return argument <= zero;
    }
    
    void bindZero() {
        class_<Zero>("Zero")
            .def(init<double>())
            .def("__eq__", &equalI)
            .def("__eq__", &equalD)
            .def("__ne__", &notEqualI)
            .def("__ne__", &notEqualD)
            .def("__lt__", &lessI)
            .def("__lt__", &lessD)
            .def("__gt__", &greaterI)
            .def("__gt__", &greaterD)
            .def("__le__", &lessOrEqualI)
            .def("__le__", &lessOrEqualD)
            .def("__ge__", &greaterOrEqualI)
            .def("__ge__", &greaterOrEqualD);
    }
}
