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

#include <OpenSolid/Core/FunctionImplementation/SineFunction.hpp>

#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{   
    int
    SineFunction::numDimensionsImpl() const {
        return 1;
    }

    bool
    SineFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    SineFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterValues).array().sin();
    }
    
    void
    SineFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterBounds).array().sin();
    }

    void
    SineFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        double operandValue = evaluator.evaluate(operand(), parameterValues).value();
        MapXcd operandJacobian = evaluator.evaluateJacobian(operand(), parameterValues);
        results = cos(operandValue) * operandJacobian;
    }
    
    void
    SineFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        Interval operandBounds = evaluator.evaluate(operand(), parameterBounds).value();
        MapXcI operandJacobian = evaluator.evaluateJacobian(operand(), parameterBounds);
        results = cos(operandBounds) * operandJacobian;
    }

    FunctionImplementationPtr
    SineFunction::derivativeImpl(int parameterIndex) const {
        return cos(operand()) * operand()->derivative(parameterIndex);
    }
    
    void
    SineFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "SineFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    SineFunction::withNewOperandImpl(const FunctionImplementationPtr& newOperand) const {
        return sin(newOperand);
    }

    SineFunction::SineFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {
        
        assert(operand->numDimensions() == 1);
    }
}
