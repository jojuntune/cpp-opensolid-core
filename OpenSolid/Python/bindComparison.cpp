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

#include <OpenSolid/Scalar/Comparison.hpp>
#include <OpenSolid/Scalar/double.hpp>
#include <OpenSolid/Scalar/Interval.hpp>
#include <OpenSolid/Python/BoostPython.hpp>

using namespace boost::python;

namespace OpenSolid
{
    Comparison zero() {return Zero();}
    
    Comparison zeroP(double precision) {return Zero(precision);}
    
    Comparison approxI(const Interval& argument) {return Approx(argument);}
    
    Comparison approxIP(const Interval& argument, double precision) {
        return Approx(argument, precision;)
    }
    
    Comparison approxD(double argument) {return Approx(argument);}
    
    Comparison approxDP(double argument, double precision) {
        return Approx(argument, precision;)
    }
    
    void bindComparison() {
        class_<Comparison>("Comparison", no_init());
        def("Zero", &zero);
        def("Zero", &zeroP);
        def("Approx", &approxI);
        def("Approx", &approxIP);
        def("Approx", &approxD);
        def("Approx", &approxDP);
    }
}
