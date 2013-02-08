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

#include <OpenSolid/Core/Function/ComponentsFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ComponentsFunction::ComponentsFunction(
        const Function& operand,
        int startIndex,
        int numComponents
    ) : UnaryOperation(operand), _startIndex(startIndex), _numComponents(numComponents) {

        assert(startIndex >= 0);
        assert(numComponents > 0);
        assert(startIndex + numComponents <= operand.numDimensions());
    }

    int ComponentsFunction::numDimensions() const {
        return numComponents();
    }
    
    void ComponentsFunction::getValues(const MapXcd& parameterValues, MapXd& results) const {
        MatrixXd operandValues = operand()(parameterValues);
        results = operandValues.middleRows(startIndex(), numComponents());
    }
    
    void ComponentsFunction::getBounds(const MapXcI& parameterBounds, MapXI& results) const {
        MatrixXI operandBounds = operand()(parameterBounds);
        results = operandBounds.middleRows(startIndex(), numComponents());
    }

    void ComponentsFunction::getDerivative(int parameterIndex, Function& result) const {
        result = operand().derivative(parameterIndex).components(startIndex(), numComponents());
    }
    
    void ComponentsFunction::getComponents(
        int startIndex,
        int numComponents,
        Function& result
    ) const {
        assert(startIndex >= 0 && startIndex < this->numComponents());
        assert(numComponents <= this->numComponents());
        result = operand().components(this->startIndex() + startIndex, numComponents);
    }
    
    void ComponentsFunction::getComposition(const Function& innerFunction, Function& result) const {
        result = operand()(innerFunction).components(startIndex(), numComponents());
    }
    
    void ComponentsFunction::debug(std::ostream& stream, int indent) const {
        stream << "ComponentsFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
