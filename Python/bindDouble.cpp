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

#include <OpenSolid/Core/config.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
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
