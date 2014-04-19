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

#include <OpenSolid/Core/ParametricExpression/ConcatenationExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    ConcatenationExpression::numDimensionsImpl() const {
        return firstOperand()->numDimensions() + secondOperand()->numDimensions();
    }
    
    void
    ConcatenationExpression::evaluateImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView.topRows(firstOperand()->numDimensions()) =
            evaluator.evaluate(firstOperand(), parameterView);
        resultView.bottomRows(secondOperand()->numDimensions()) =
            evaluator.evaluate(secondOperand(), parameterView);
    }
    
    void
    ConcatenationExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView.topRows(firstOperand()->numDimensions()) =
            evaluator.evaluate(firstOperand(), parameterView);
        resultView.bottomRows(secondOperand()->numDimensions()) =
            evaluator.evaluate(secondOperand(), parameterView);
    }

    void
    ConcatenationExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView.topRows(firstOperand()->numDimensions()) =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        resultView.bottomRows(secondOperand()->numDimensions()) =
            evaluator.evaluateJacobian(secondOperand(), parameterView);
    }
    
    void
    ConcatenationExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView.topRows(firstOperand()->numDimensions()) =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        resultView.bottomRows(secondOperand()->numDimensions()) =
            evaluator.evaluateJacobian(secondOperand(), parameterView);
    }
    
    ExpressionImplementationPtr
    ConcatenationExpression::derivativeImpl(int parameterIndex) const {
        return firstOperand()->derivative(parameterIndex)->concatenated(
            secondOperand()->derivative(parameterIndex)
        );
    }

    bool
    ConcatenationExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other, false);
    }
    
    ExpressionImplementationPtr
    ConcatenationExpression::componentsImpl(int startIndex, int numComponents) const {
        int firstDimensions = firstOperand()->numDimensions();
        if (startIndex + numComponents <= firstDimensions) {
            return firstOperand()->components(startIndex, numComponents);
        } else if (startIndex >= firstDimensions) {
            return secondOperand()->components(startIndex - firstDimensions, numComponents);
        } else {
            return new ConcatenationExpression(
                firstOperand()->components(startIndex, firstDimensions - startIndex),
                secondOperand()->components(0, startIndex + numComponents - firstDimensions)
            );
        }
    }
    
    void
    ConcatenationExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "ConcatenationExpression" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    ConcatenationExpression::withNewOperandsImpl(
        const ExpressionImplementationPtr& newFirstOperand,
        const ExpressionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand->concatenated(newSecondOperand);
    }

    ConcatenationExpression::ConcatenationExpression(
        const ExpressionImplementationPtr& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {
    }
}
