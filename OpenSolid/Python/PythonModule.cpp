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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Common/Error.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
{
    void bindFunction();
    void bindDatum();
    void bindSimplex();
    void bindMatrixConstructors();
    void bindMatrix();
    void bindComparison();
    void bindInterval();
    void bindDouble();
    void bindError();

    void PythonModule::initialize() {
        bindFunction();
        bindDatum();
        bindSimplex();
        bindMatrix();
        bindMatrixConstructors();
        bindComparison();
        bindInterval();
        bindDouble();
        bindError();
    }

    BOOST_PYTHON_MODULE(opensolid) {PythonModule::initialize();}
}
