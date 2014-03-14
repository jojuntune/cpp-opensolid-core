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
************************************************************************************/

#include <OpenSolid/Core/ParametricExpression/SumExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    SumExpression::numDimensionsImpl() const {
        return firstOperand()->numDimensions();
    }
    
    void
    SumExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd firstValues = evaluator.evaluate(firstOperand(), parameterValues);
        MapXcd secondValues = evaluator.evaluate(secondOperand(), parameterValues);
        results = firstValues + secondValues;
    }
    
    void
    SumExpression::evaluateImpl(
        const MapXcI& parameterValues,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI firstBounds = evaluator.evaluate(firstOperand(), parameterValues);
        MapXcI secondBounds = evaluator.evaluate(secondOperand(), parameterValues);
        results = firstBounds + secondBounds;
    }

    void
    SumExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd firstJacobian = evaluator.evaluateJacobian(firstOperand(), parameterValues);
        MapXcd secondJacobian = evaluator.evaluateJacobian(secondOperand(), parameterValues);
        results = firstJacobian + secondJacobian;
    }
    
    void
    SumExpression::evaluateJacobianImpl(
        const MapXcI& parameterValues,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI firstJacobian = evaluator.evaluateJacobian(firstOperand(), parameterValues);
        MapXcI secondJacobian = evaluator.evaluateJacobian(secondOperand(), parameterValues);
        results = firstJacobian + secondJacobian;
    }

    ExpressionImplementationPtr
    SumExpression::derivativeImpl(int parameterIndex) const {
        return firstOperand()->derivative(parameterIndex) +
            secondOperand()->derivative(parameterIndex);
    }

    bool
    SumExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other, true);
    }
    
    void
    SumExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "SumExpression" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    SumExpression::withNewOperandsImpl(
        const ExpressionImplementationPtr& newFirstOperand,
        const ExpressionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand + newSecondOperand;
    }

    SumExpression::SumExpression(
        const ExpressionImplementationPtr& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(firstOperand->numDimensions() == secondOperand->numDimensions());
    }
}
