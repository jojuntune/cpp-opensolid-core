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

#include <OpenSolid/Core/Function/NegationFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    NegationFunction::NegationFunction(const Function& operand) : UnaryOperation(operand) {
    }
    
    int NegationFunction::numDimensions() const {
        return operand().numDimensions();
    }
    
    void NegationFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        results = -operand()(parameterValues);
    }
    
    void NegationFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        results = -operand()(parameterBounds);
    }

    void NegationFunction::getDerivative(int index, Function& result) const {
        result = -operand().derivative(index);
    }

    void NegationFunction::getComponents(
        int startIndex,
        int numComponents,
        Function& result
    ) const {
        result = -operand().components(startIndex, numComponents);
    }
    
    void NegationFunction::getComposition(
        const Function& innerFunction,
        Function& result
    ) const {
        result = -operand()(innerFunction);
    }
    
    void NegationFunction::getTransformed(
        const MatrixXd& transformationMatrix,
        const VectorXd& translationVector,
        Function& result
    ) const {
        result = operand().transformed(-transformationMatrix, translationVector);
    }
    
    void NegationFunction::getNorm(Function& result) const {
        result = operand().norm();
    }
    
    void NegationFunction::getSquaredNorm(Function& result) const {
        result = operand().squaredNorm();
    }
    
    void NegationFunction::debug(std::ostream& stream, int indent) const {
        stream << "NegationFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
