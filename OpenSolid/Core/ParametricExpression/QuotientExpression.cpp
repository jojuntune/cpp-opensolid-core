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
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        ConstMatrixViewXxX divisorValues = evaluator.evaluate(firstOperand(), parameterView);
        resultView = evaluator.evaluate(secondOperand(), parameterView);
        for (int colIndex = 0; colIndex < resultView.cols(); ++colIndex) {
            double divisorValue = divisorValues(0, colIndex);
            if (divisorValue == Zero()) {
                throw Error(new PlaceholderError());
            }
            resultView.col(colIndex) /= divisorValue;
        }
    }
    
    void
    QuotientExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        ConstIntervalMatrixViewXxX divisorValues =
            evaluator.evaluate(firstOperand(), parameterView);
        resultView = evaluator.evaluate(secondOperand(), parameterView);
        for (int colIndex = 0; colIndex < resultView.cols(); ++colIndex) {
            Interval divisorValue = divisorValues(0, colIndex);
            if (divisorValue == Zero()) {
                throw Error(new PlaceholderError());
            }
            resultView.col(colIndex) /= divisorValue;
        }
    }

    void
    QuotientExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        double divisorValue = evaluator.evaluate(secondOperand(), parameterView).value();
        if (divisorValue == Zero()) {
            throw Error(new PlaceholderError());
        }
        ConstMatrixViewXxX dividendValues =
            evaluator.evaluate(firstOperand(), parameterView);
        ConstMatrixViewXxX dividendJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        ConstMatrixViewXxX divisorJacobian =
            evaluator.evaluateJacobian(secondOperand(), parameterView);
        resultView = (dividendJacobian * divisorValue - dividendValues * divisorJacobian) / 
            (divisorValue * divisorValue);
    }
    
    void
    QuotientExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        Interval divisorValue = evaluator.evaluate(secondOperand(), parameterView).value();
        if (divisorValue == Zero()) {
            throw Error(new PlaceholderError());
        }
        ConstIntervalMatrixViewXxX dividendValues =
            evaluator.evaluate(firstOperand(), parameterView);
        ConstIntervalMatrixViewXxX dividendJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        ConstIntervalMatrixViewXxX divisorJacobian =
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
