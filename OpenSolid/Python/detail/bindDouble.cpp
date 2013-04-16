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
*************************************************************************************/

#include "PythonModule.hpp"
#include <OpenSolid/config.hpp>

using namespace boost::python;

namespace opensolid
{
    void bindDouble() {
        def("abs", (double (*)(double)) &abs);
        def("sqrt", (double (*)(double)) &sqrt);
        def("sin", (double (*)(double)) &sin);
        def("cos", (double (*)(double)) &cos);
        def("tan", (double (*)(double)) &tan);
        def("asin", (double (*)(double)) &asin);
        def("acos", (double (*)(double)) &acos);
        def("atan", (double (*)(double)) &atan);
        def("atan2", (double (*)(double, double)) &atan2);
        def("exp", (double (*)(double)) &exp);
        def("log", (double (*)(double)) &log);
        def("pow", (double (*)(double, double)) &pow);
    }
}
