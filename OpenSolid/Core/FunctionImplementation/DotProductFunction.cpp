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

#include <OpenSolid/Core/FunctionImplementation/DotProductFunction.hpp>

namespace opensolid
{   
    int
    DotProductFunction::numDimensionsImpl() const {
        return 1;
    }
    
    void
    DotProductFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd firstValues = evaluator.evaluate(firstOperand(), parameterValues);
        MapXcd secondValues = evaluator.evaluate(secondOperand(), parameterValues);
        results = firstValues.cwiseProduct(secondValues).colwise().sum();
    }
    
    void
    DotProductFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI firstBounds = evaluator.evaluate(firstOperand(), parameterBounds);
        MapXcI secondBounds = evaluator.evaluate(secondOperand(), parameterBounds);
        results = firstBounds.cwiseProduct(secondBounds).colwise().sum();
    }

    void
    DotProductFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd firstValue = evaluator.evaluate(firstOperand(), parameterValues);
        MapXcd secondValue = evaluator.evaluate(secondOperand(), parameterValues);
        MapXcd firstJacobian = evaluator.evaluateJacobian(firstOperand(), parameterValues);
        MapXcd secondJacobian = evaluator.evaluateJacobian(secondOperand(), parameterValues);
        results = firstValue.transpose() * secondJacobian +
            secondValue.transpose() * firstJacobian;
    }
    
    void
    DotProductFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI firstBounds = evaluator.evaluate(firstOperand(), parameterBounds);
        MapXcI secondBounds = evaluator.evaluate(secondOperand(), parameterBounds);
        MapXcI firstJacobian = evaluator.evaluateJacobian(firstOperand(), parameterBounds);
        MapXcI secondJacobian = evaluator.evaluateJacobian(secondOperand(), parameterBounds);
        results = firstBounds.transpose() * secondJacobian +
            secondBounds.transpose() * firstJacobian;
    }

    FunctionImplementationPtr
    DotProductFunction::derivativeImpl(int parameterIndex) const {
        return firstOperand()->derivative(parameterIndex)->dot(secondOperand())
            + firstOperand()->dot(secondOperand()->derivative(parameterIndex));
    }

    bool
    DotProductFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other, true);
    }
    
    void
    DotProductFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "DotProductFunction" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    DotProductFunction::withNewOperandsImpl(
        const FunctionImplementationPtr& newFirstOperand,
        const FunctionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand->dot(newSecondOperand);
    }

    DotProductFunction::DotProductFunction(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(firstOperand->numDimensions() == secondOperand->numDimensions());
    }
}
