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

#include <OpenSolid/Core/ParametricExpression/DotProductExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    DotProductExpression::numDimensionsImpl() const {
        return 1;
    }
    
    void
    DotProductExpression::evaluateImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcd firstValues = evaluator.evaluate(firstOperand(), parameterView);
        MapXcd secondValues = evaluator.evaluate(secondOperand(), parameterView);
        resultView = firstValues.cwiseProduct(secondValues).colwise().sum();
    }
    
    void
    DotProductExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcI firstBounds = evaluator.evaluate(firstOperand(), parameterView);
        MapXcI secondBounds = evaluator.evaluate(secondOperand(), parameterView);
        resultView = firstBounds.cwiseProduct(secondBounds).colwise().sum();
    }

    void
    DotProductExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcd firstValue = evaluator.evaluate(firstOperand(), parameterView);
        MapXcd secondValue = evaluator.evaluate(secondOperand(), parameterView);
        MapXcd firstJacobian = evaluator.evaluateJacobian(firstOperand(), parameterView);
        MapXcd secondJacobian = evaluator.evaluateJacobian(secondOperand(), parameterView);
        resultView = firstValue.transpose() * secondJacobian +
            secondValue.transpose() * firstJacobian;
    }
    
    void
    DotProductExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcI firstBounds = evaluator.evaluate(firstOperand(), parameterView);
        MapXcI secondBounds = evaluator.evaluate(secondOperand(), parameterView);
        MapXcI firstJacobian = evaluator.evaluateJacobian(firstOperand(), parameterView);
        MapXcI secondJacobian = evaluator.evaluateJacobian(secondOperand(), parameterView);
        resultView = firstBounds.transpose() * secondJacobian +
            secondBounds.transpose() * firstJacobian;
    }

    ExpressionImplementationPtr
    DotProductExpression::derivativeImpl(int parameterIndex) const {
        return firstOperand()->derivative(parameterIndex)->dot(secondOperand())
            + firstOperand()->dot(secondOperand()->derivative(parameterIndex));
    }

    bool
    DotProductExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other, true);
    }
    
    void
    DotProductExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "DotProductExpression" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    DotProductExpression::withNewOperandsImpl(
        const ExpressionImplementationPtr& newFirstOperand,
        const ExpressionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand->dot(newSecondOperand);
    }

    DotProductExpression::DotProductExpression(
        const ExpressionImplementationPtr& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(firstOperand->numDimensions() == secondOperand->numDimensions());
    }
}
