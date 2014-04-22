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
        ConstMatrixViewXxX firstValues = evaluator.evaluate(firstOperand(), parameterView);
        ConstMatrixViewXxX secondValues = evaluator.evaluate(secondOperand(), parameterView);
        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            resultView(0, columnIndex) = firstValues.column(columnIndex).binaryFold(
                secondValues.column(columnIndex),
                0.0,
                [] (double result, double firstValue, double secondValue) {
                    return result + firstValue * secondValue;
                }
            );
        }
    }
    
    void
    DotProductExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        ConstIntervalMatrixViewXxX firstValues =
            evaluator.evaluate(firstOperand(), parameterView);
        ConstIntervalMatrixViewXxX secondValues =
            evaluator.evaluate(secondOperand(), parameterView);
        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            resultView(0, columnIndex) = firstValues.column(columnIndex).binaryFold(
                secondValues.column(columnIndex),
                Interval(0.0),
                [] (Interval result, Interval firstValue, Interval secondValue) {
                    return result + firstValue * secondValue;
                }
            );
        }
    }

    void
    DotProductExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        ConstMatrixViewXxX firstValue = evaluator.evaluate(firstOperand(), parameterView);
        ConstMatrixViewXxX secondValue = evaluator.evaluate(secondOperand(), parameterView);

        ConstMatrixViewXxX firstJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        ConstMatrixViewXxX secondJacobian =
            evaluator.evaluateJacobian(secondOperand(), parameterView);
        
        resultView = firstValue.transpose() * secondJacobian +
            secondValue.transpose() * firstJacobian;
    }
    
    void
    DotProductExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        ConstIntervalMatrixViewXxX firstValue = evaluator.evaluate(firstOperand(), parameterView);
        ConstIntervalMatrixViewXxX secondValue = evaluator.evaluate(secondOperand(), parameterView);

        ConstIntervalMatrixViewXxX firstJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        ConstIntervalMatrixViewXxX secondJacobian =
            evaluator.evaluateJacobian(secondOperand(), parameterView);
        
        resultView = firstValue.transpose() * secondJacobian +
            secondValue.transpose() * firstJacobian;
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
