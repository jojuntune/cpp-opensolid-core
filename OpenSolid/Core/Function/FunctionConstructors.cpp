/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <OpenSolid/Core/Function/FunctionConstructors.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

// Internal headers
#include <OpenSolid/Core/Function/EllipticalFunction.hpp>
#include <OpenSolid/Core/Function/LinearFunction.hpp>
#include <OpenSolid/Core/Function/ParametersFunction.hpp>

namespace opensolid
{
    Function FunctionConstructors::Identity(int numDimensions) {
        return new ParametersFunction(numDimensions, 0, numDimensions);
    }

    Function FunctionConstructors::Parameter() {
        return new ParametersFunction(1, 0, 1);
    }

    Function FunctionConstructors::Parameter(int totalNumParameters, int index) {
        return new ParametersFunction(totalNumParameters, index, 1);
    }

    Function FunctionConstructors::Parameters(int totalNumParameters) {
        return new ParametersFunction(totalNumParameters, 0, totalNumParameters);
    }

    Function FunctionConstructors::Parameters(
        int totalNumParameters,
        int startIndex,
        int numParameters
    ) {
        return new ParametersFunction(totalNumParameters, startIndex, numParameters);
    }
    
    Function FunctionConstructors::Components(
        const Function& xFunction,
        const Function& yFunction
    ) {
        return xFunction.concatenate(yFunction);
    }
    
    Function FunctionConstructors::Components(
        const Function& xFunction,
        const Function& yFunction,
        const Function& zFunction
    ) {
        return xFunction.concatenate(yFunction).concatenate(zFunction);
    }
        
    Function FunctionConstructors::Linear(const Axis2d& axis) {
        return new LinearFunction<2, 1>(axis);
    }

    Function FunctionConstructors::Linear(const Frame2d& frame) {
        return new LinearFunction<2, 2>(frame);
    }

    Function FunctionConstructors::Linear(const Axis3d& axis) {
        return new LinearFunction<3, 1>(axis);
    }

    Function FunctionConstructors::Linear(const Plane3d& plane) {
        return new LinearFunction<3, 2>(plane);
    }

    Function FunctionConstructors::Linear(const Frame3d& frame) {
        return new LinearFunction<3, 3>(frame);
    }
    
    Function FunctionConstructors::Elliptical(const Frame2d& frame) {
        return new EllipticalFunction<2, 2>(frame, Matrix1b::Constant(true));
    }

    Function FunctionConstructors::Elliptical(const Plane3d& plane) {
        return new EllipticalFunction<3, 2>(plane, Matrix1b::Constant(true));
    }

    Function FunctionConstructors::Elliptical(const Frame3d& frame) {
        return new EllipticalFunction<3, 3>(frame, RowVector2b::Constant(true));
    }
}
