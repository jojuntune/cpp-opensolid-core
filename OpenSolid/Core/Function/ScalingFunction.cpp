/*************************************************************************************
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

#include <OpenSolid/Core/Function/ScalingFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ScalingFunction::ScalingFunction(double scale, const Function& operand) :
        UnaryOperation(operand),
        _scale(scale) {
    }

    int ScalingFunction::numDimensions() const {
        return operand().numDimensions();
    }
    
    void ScalingFunction::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        results = scale() * operand()(parameterValues);
    }
    
    void ScalingFunction::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        results = Interval(scale()) * operand()(parameterBounds);
    }
    
    Function ScalingFunction::derivative(int index) const {
        return scale() * operand().derivative(index);
    }
    
    Function ScalingFunction::compose(const Function& innerFunction) const {
        return scale() * operand()(innerFunction);
    }

    Function ScalingFunction::scaled(double scale) const {
        return new ScalingFunction(scale * this->scale(), operand());
    }

    Function ScalingFunction::transformed(const MatrixXd& transformationMatrix) const {
        return (scale() * transformationMatrix) * operand();
    }
    
    void ScalingFunction::debug(std::ostream& stream, int indent) const {
        stream << "ScalingFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
