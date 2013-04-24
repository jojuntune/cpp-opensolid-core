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

#include <OpenSolid/Core/Function/FunctionConstructors.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/FunctionImplementation/ConstantFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/EllipticalFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/IdentityFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/LinearFunction.hpp>
#include <OpenSolid/Core/FunctionImplementation/ParameterFunction.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>

namespace opensolid
{
    Function
    FunctionConstructors::Zero(int numDimensions, int numParameters) {
        return Constant(VectorXd::Zero(numDimensions), numParameters);
    }

    Function
    FunctionConstructors::Constant(double value, int numParameters) {
        return Constant(VectorXd::Constant(1, value), numParameters);
    }

    Function
    FunctionConstructors::Constant(const VectorXd& vector, int numParameters) {
        return new ConstantFunction(vector, numParameters);
    }

    Function
    FunctionConstructors::Identity(int numDimensions) {
        return new IdentityFunction(numDimensions);
    }

    Function
    FunctionConstructors::t() {
        return new ParameterFunction(1, 0);
    }

    Function
    FunctionConstructors::u() {
        return new ParameterFunction(2, 0);
    }

    Function
    FunctionConstructors::v() {
        return new ParameterFunction(2, 1);
    }

    Function
    FunctionConstructors::Parameter(int numParameters, int index) {
        return new ParameterFunction(numParameters, index);
    }
    
    Function
    FunctionConstructors::FromComponents(
        const Function& xFunction,
        const Function& yFunction
    ) {
        return xFunction.concatenate(yFunction);
    }
    
    Function
    FunctionConstructors::FromComponents(
        const Function& xFunction,
        const Function& yFunction,
        const Function& zFunction
    ) {
        return xFunction.concatenate(yFunction).concatenate(zFunction);
    }
        
    Function
    FunctionConstructors::Linear(const Axis<2>& axis) {
        return new LinearFunction<2, 1>(axis);
    }

    Function
    FunctionConstructors::Linear(const Frame<2>& frame) {
        return new LinearFunction<2, 2>(frame);
    }

    Function
    FunctionConstructors::Linear(const Axis<3>& axis) {
        return new LinearFunction<3, 1>(axis);
    }

    Function
    FunctionConstructors::Linear(const Plane3d& plane) {
        return new LinearFunction<3, 2>(plane);
    }

    Function
    FunctionConstructors::Linear(const Frame<3>& frame) {
        return new LinearFunction<3, 3>(frame);
    }
    
    Function
    FunctionConstructors::Elliptical(const Frame<2>& frame) {
        return new EllipticalFunction<2, 2>(frame, Matrix1b::Constant(true));
    }

    Function
    FunctionConstructors::Elliptical(const Plane3d& plane) {
        return new EllipticalFunction<3, 2>(plane, Matrix1b::Constant(true));
    }

    Function
    FunctionConstructors::Elliptical(const Frame<3>& frame) {
        return new EllipticalFunction<3, 3>(frame, RowVector2b::Constant(true));
    }
}
