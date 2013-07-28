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

#include <OpenSolid/Core/FunctionImplementation/ComponentsFunction.hpp>

#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{
    int
    ComponentsFunction::numDimensionsImpl() const {
        return numComponents();
    }
    
    void
    ComponentsFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd operandValues = evaluator.evaluate(operand(), parameterValues);
        results = operandValues.middleRows(startIndex(), numComponents());
    }
    
    void
    ComponentsFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterBounds);
        results = operandBounds.middleRows(startIndex(), numComponents());
    }

    void
    ComponentsFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd operandJacobian = evaluator.evaluateJacobian(operand(), parameterValues);
        results = operandJacobian.middleRows(startIndex(), numComponents());
    }
    
    void
    ComponentsFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI operandJacobian = evaluator.evaluateJacobian(operand(), parameterBounds);
        results = operandJacobian.middleRows(startIndex(), numComponents());
    }

    FunctionImplementationPtr
    ComponentsFunction::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex)->components(startIndex(), numComponents());
    }

    bool
    ComponentsFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other) &&
            this->startIndex() == other->cast<ComponentsFunction>()->startIndex() &&
            this->numComponents() == other->cast<ComponentsFunction>()->numComponents();
    }
    
    FunctionImplementationPtr
    ComponentsFunction::componentsImpl(int startIndex, int numComponents) const {
        return operand()->components(this->startIndex() + startIndex, numComponents);
    }
    
    void
    ComponentsFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "ComponentsFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    ComponentsFunction::withNewOperandImpl(const FunctionImplementationPtr& newOperand) const {
        return newOperand->components(startIndex(), numComponents());
    }

    ComponentsFunction::ComponentsFunction(
        const FunctionImplementationPtr& operand,
        int startIndex,
        int numComponents
    ) : UnaryOperation(operand),
        _startIndex(startIndex),
        _numComponents(numComponents) {

        assert(startIndex >= 0);
        assert(numComponents > 0);
        assert(startIndex + numComponents <= operand->numDimensions());
    }
}
