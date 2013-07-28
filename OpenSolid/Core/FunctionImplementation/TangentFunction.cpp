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

#include <OpenSolid/Core/FunctionImplementation/TangentFunction.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{   
    int
    TangentFunction::numDimensionsImpl() const {
        return 1;
    }
    
    void
    TangentFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd operandValues = evaluator.evaluate(operand(), parameterValues);
        results = operandValues.array().sin() / operandValues.array().cos();
    }
    
    void
    TangentFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterBounds);
        results = operandBounds.array().sin() / operandBounds.array().cos();
    }

    void
    TangentFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        double operandValue = evaluator.evaluate(operand(), parameterValues).value();
        MapXcd operandJacobian = evaluator.evaluateJacobian(operand(), parameterValues);
        double cosine = cos(operandValue);
        if (cosine == Zero()) {
            throw PlaceholderError();
        }
        results = operandJacobian / (cosine * cosine);
    }
    
    void
    TangentFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        Interval operandBounds = evaluator.evaluate(operand(), parameterBounds).value();
        MapXcI operandJacobian = evaluator.evaluateJacobian(operand(), parameterBounds);
        Interval cosine = cos(operandBounds);
        if (cosine == Zero()) {
            throw PlaceholderError();
        }
        results = operandJacobian / cosine.squared();
    }

    FunctionImplementationPtr
    TangentFunction::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex) / cos(operand())->squaredNorm();
    }

    bool
    TangentFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    TangentFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "TangentFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    TangentFunction::withNewOperandImpl(const FunctionImplementationPtr& newOperand) const {
        return tan(newOperand);
    }

    TangentFunction::TangentFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {
        
        assert(operand->numDimensions() == 1);
    }
}
