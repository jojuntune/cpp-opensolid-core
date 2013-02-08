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

#include <OpenSolid/Core/Function/ConcatenationFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ConcatenationFunction::ConcatenationFunction(
        const Function& firstOperand,
        const Function& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {
    }
    
    int ConcatenationFunction::numDimensions() const {
        return firstOperand().numDimensions() + secondOperand().numDimensions();
    }
    
    void ConcatenationFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        results.topRows(firstOperand().numDimensions()) = firstOperand()(parameterValues);
        results.bottomRows(secondOperand().numDimensions()) = secondOperand()(parameterValues);
    }
    
    void ConcatenationFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        results.topRows(firstOperand().numDimensions()) = firstOperand()(parameterBounds);
        results.bottomRows(secondOperand().numDimensions()) = secondOperand()(parameterBounds);
    }
    
    void ConcatenationFunction::getDerivative(int index, Function& result) const {
        result = firstOperand().derivative(index).concatenate(secondOperand().derivative(index));
    }
    
    void ConcatenationFunction::getComponents(
        int startIndex,
        int numComponents,
        Function& result
    ) const {
        int firstDimensions = firstOperand().numDimensions();
        if (startIndex + numComponents <= firstDimensions) {
            result = firstOperand().components(startIndex, numComponents);
        } else if (startIndex >= firstDimensions) {
            result = secondOperand().components(startIndex - firstDimensions, numComponents);
        } else {
            result = new ConcatenationFunction(
                firstOperand().components(startIndex, firstDimensions - startIndex),
                secondOperand().components(0, startIndex + numComponents - firstDimensions)
            );
        }
    }
    
    void ConcatenationFunction::getComposition(
        const Function& innerFunction,
        Function& result
    ) const {
        result = firstOperand()(innerFunction).concatenate(secondOperand()(innerFunction));
    }
    
    void ConcatenationFunction::debug(std::ostream& stream, int indent) const {
        stream << "ConcatenationFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
