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

#include <OpenSolid/Core/ParametricExpression/QuotientExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    QuotientExpression::numDimensionsImpl() const {
        return firstOperand()->numDimensions();
    }
    
    void
    QuotientExpression::evaluateImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluate(firstOperand(), parameterView);
        ConstMatrixViewXd divisorValues = evaluator.evaluate(secondOperand(), parameterView);
        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            double divisorValue = divisorValues(0, columnIndex);
            if (divisorValue == Zero()) {
                throw Error(new PlaceholderError());
            }
            resultView.column(columnIndex) /= divisorValue;
        }
    }
    
    void
    QuotientExpression::evaluateImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluate(firstOperand(), parameterView);
        ConstIntervalMatrixViewXd divisorValues =
            evaluator.evaluate(secondOperand(), parameterView);
        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            Interval divisorValue = divisorValues(0, columnIndex);
            if (divisorValue == Zero()) {
                throw Error(new PlaceholderError());
            }
            resultView.column(columnIndex) /= divisorValue;
        }
    }

    void
    QuotientExpression::evaluateJacobianImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        double divisorValue = evaluator.evaluate(secondOperand(), parameterView).value();
        if (divisorValue == Zero()) {
            throw Error(new PlaceholderError());
        }
        ConstMatrixViewXd dividendValues =
            evaluator.evaluate(firstOperand(), parameterView);
        ConstMatrixViewXd dividendJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        ConstMatrixViewXd divisorJacobian =
            evaluator.evaluateJacobian(secondOperand(), parameterView);
        resultView = (dividendJacobian * divisorValue - dividendValues * divisorJacobian) / 
            (divisorValue * divisorValue);
    }
    
    void
    QuotientExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        Interval divisorValue = evaluator.evaluate(secondOperand(), parameterView).value();
        if (divisorValue == Zero()) {
            throw Error(new PlaceholderError());
        }
        ConstIntervalMatrixViewXd dividendValues =
            evaluator.evaluate(firstOperand(), parameterView);
        ConstIntervalMatrixViewXd dividendJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        ConstIntervalMatrixViewXd divisorJacobian =
            evaluator.evaluateJacobian(secondOperand(), parameterView);
        resultView = (dividendJacobian * divisorValue - dividendValues * divisorJacobian) / 
            (divisorValue * divisorValue);
    }

    ExpressionImplementationPtr
    QuotientExpression::derivativeImpl(int parameterIndex) const {
        ExpressionImplementationPtr firstDerivative = firstOperand()->derivative(parameterIndex);
        ExpressionImplementationPtr secondDerivative = secondOperand()->derivative(parameterIndex);
        return(firstDerivative * secondOperand() - firstOperand() * secondDerivative) /
            secondOperand()->squaredNorm();
    }

    bool
    QuotientExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other, false);
    }
    
    void
    QuotientExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "QuotientExpression" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    QuotientExpression::withNewOperandsImpl(
        const ExpressionImplementationPtr& newFirstOperand,
        const ExpressionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand / newSecondOperand;
    }

    QuotientExpression::QuotientExpression(
        const ExpressionImplementationPtr& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(secondOperand->numDimensions() == 1);
    }
}
