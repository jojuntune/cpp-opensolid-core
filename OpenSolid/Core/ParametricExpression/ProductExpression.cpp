/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#include <OpenSolid/Core/ParametricExpression/ProductExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    ProductExpression::numDimensionsImpl() const {
        return secondOperand()->numDimensions();
    }
    
    void
    ProductExpression::evaluateImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        ConstMatrixViewXd multiplierValues = evaluator.evaluate(firstOperand(), parameterView);
        resultView = evaluator.evaluate(secondOperand(), parameterView);
        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            resultView.column(columnIndex) *= multiplierValues(0, columnIndex);
        }
    }
    
    void
    ProductExpression::evaluateImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        ConstIntervalMatrixViewXd multiplierValues =
            evaluator.evaluate(firstOperand(), parameterView);
        resultView = evaluator.evaluate(secondOperand(), parameterView);
        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            resultView.column(columnIndex) *= multiplierValues(0, columnIndex);
        }
    }

    void
    ProductExpression::evaluateJacobianImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        double multiplierValue = evaluator.evaluate(firstOperand(), parameterView).value();
        ConstMatrixViewXd multiplicandValue =
            evaluator.evaluate(secondOperand(), parameterView);
        ConstMatrixViewXd multiplierJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        ConstMatrixViewXd multiplicandJacobian =
            evaluator.evaluateJacobian(secondOperand(), parameterView);
        resultView =
            multiplierValue * multiplicandJacobian + multiplicandValue * multiplierJacobian;
    }
    
    void
    ProductExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        Interval multiplierValue = evaluator.evaluate(firstOperand(), parameterView).value();
        ConstIntervalMatrixViewXd multiplicandValue =
            evaluator.evaluate(secondOperand(), parameterView);
        ConstIntervalMatrixViewXd multiplierJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        ConstIntervalMatrixViewXd multiplicandJacobian =
            evaluator.evaluateJacobian(secondOperand(), parameterView);
        resultView =
            multiplierValue * multiplicandJacobian + multiplicandValue * multiplierJacobian;
    }

    ExpressionImplementationPtr
    ProductExpression::derivativeImpl(int parameterIndex) const {
        return firstOperand()->derivative(parameterIndex) * secondOperand()
            + firstOperand() * secondOperand()->derivative(parameterIndex);
    }

    bool
    ProductExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other, true);
    }
    
    void
    ProductExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "ProductExpression" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    ProductExpression::withNewOperandsImpl(
        const ExpressionImplementationPtr& newFirstOperand,
        const ExpressionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand * newSecondOperand;
    }

    ProductExpression::ProductExpression(
        const ExpressionImplementationPtr& multiplier,
        const ExpressionImplementationPtr& multiplicand
    ) : BinaryOperation(multiplier, multiplicand) {

        assert(multiplier->numDimensions() == 1);
    }
}
