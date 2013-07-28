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

#include <OpenSolid/Core/FunctionImplementation/LogarithmFunction.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{       
    int
    LogarithmFunction::numDimensionsImpl() const {
        return 1;
    }

    bool
    LogarithmFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
        
    void
    LogarithmFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd operandValues = evaluator.evaluate(operand(), parameterValues);
        if (operandValues.minCoeff() <= Zero()) {
            throw PlaceholderError();
        }
        results = operandValues.array().log();
    }

    void
    LogarithmFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterBounds);
        if (operandBounds.cwiseUpper().minCoeff() <= Zero()) {
            throw PlaceholderError();
        }
        results = operandBounds.array().log();
    }

    void
    LogarithmFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        double operandValue = evaluator.evaluate(operand(), parameterValues).value();
        if (operandValue <= Zero()) {
            throw PlaceholderError();
        }
        results = evaluator.evaluateJacobian(operand(), parameterValues) / operandValue;
    }
    
    void
    LogarithmFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        Interval operandBounds = evaluator.evaluate(operand(), parameterBounds).value();
        if (operandBounds.upperBound() <= Zero()) {
            throw PlaceholderError();
        }
        results = evaluator.evaluateJacobian(operand(), parameterBounds) / operandBounds;
    }

    FunctionImplementationPtr
    LogarithmFunction::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex) / operand();
    }
        
    void
    LogarithmFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "LogarithmFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    LogarithmFunction::withNewOperandImpl(const FunctionImplementationPtr& newOperand) const {
        return log(newOperand);
    }

    LogarithmFunction::LogarithmFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {
        
        assert(operand->numDimensions() == 1);
    }
}
