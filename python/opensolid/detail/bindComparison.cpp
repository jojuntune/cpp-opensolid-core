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

#include <opensolid/detail/PythonModule.hpp>
#include <opensolid/Comparison.hpp>
#include <opensolid/Interval.hpp>

using namespace boost::python;

namespace opensolid
{
    Comparison zero() {return Zero();}
    
    Comparison zeroP(double precision) {return Zero(precision);}

    bool equalI(const Comparison& comparison, const Interval& argument) {
        return argument == comparison;
    }

    bool equalD(const Comparison& comparison, double argument) {
        return argument == comparison;
    }

    bool notEqualI(const Comparison& comparison, const Interval& argument) {
        return argument != comparison;
    }

    bool notEqualD(const Comparison& comparison, double argument) {
        return argument != comparison;
    }

    bool lessI(const Comparison& comparison, const Interval& argument) {
        return argument > comparison;
    }

    bool lessD(const Comparison& comparison, double argument) {
        return argument > comparison;
    }

    bool greaterI(const Comparison& comparison, const Interval& argument) {
        return argument < comparison;
    }

    bool greaterD(const Comparison& comparison, double argument) {
        return argument < comparison;
    }

    bool lessOrEqualI(const Comparison& comparison, const Interval& argument) {
        return argument >= comparison;
    }

    bool lessOrEqualD(const Comparison& comparison, double argument) {
        return argument >= comparison;
    }

    bool greaterOrEqualI(const Comparison& comparison, const Interval& argument) {
        return argument <= comparison;
    }

    bool greaterOrEqualD(const Comparison& comparison, double argument) {
        return argument <= comparison;
    }
    
    void bindComparison() {
        class_<Comparison>("Comparison", no_init)
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
        def("Zero", &zero);
        def("Zero", &zeroP);
    }
}
