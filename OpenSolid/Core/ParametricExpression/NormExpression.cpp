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

#include <OpenSolid/Core/ParametricExpression/NormExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    NormExpression::numDimensionsImpl() const {
        return 1;
    }

    bool
    NormExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    NormExpression::evaluateImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        ConstMatrixViewXd operandValues = evaluator.evaluate(operand(), parameterView);
        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            resultView(0, columnIndex) = sqrt(
                operandValues.column(columnIndex).fold(
                    0.0,
                    [] (double result, double value) {
                        return result + value * value;
                    }
                )
            );
        }
    }
    
    void 
    NormExpression::evaluateImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        ConstIntervalMatrixViewXd operandValues = evaluator.evaluate(operand(), parameterView);
        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            resultView(0, columnIndex) = sqrt(
                operandValues.column(columnIndex).fold(
                    Interval(0.0),
                    [] (Interval result, Interval value) {
                        return result + value.squared();
                    }
                )
            );
        }
    }

    void
    NormExpression::evaluateJacobianImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        ConstMatrixViewXd operandValue = evaluator.evaluate(operand(), parameterView);
        double operandNorm = sqrt(operandValue.cwiseSquared().sum());
        if (operandNorm == Zero()) {
            throw Error(new PlaceholderError());
        }
        ColumnMatrixXd operandNormalized = operandValue;
        operandNormalized /= operandNorm;

        ConstMatrixViewXd operandJacobian = evaluator.evaluateJacobian(operand(), parameterView);
        
        resultView = operandNormalized.transpose() * operandJacobian;
    }
    
    void
    NormExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        ConstIntervalMatrixViewXd operandValue = evaluator.evaluate(operand(), parameterView);
        Interval operandNorm = sqrt(operandValue.cwiseSquared().sum());
        if (operandNorm == Zero()) {
            throw Error(new PlaceholderError());
        }
        IntervalColumnMatrixXd operandNormalized = operandValue;
        operandNormalized /= operandNorm;

        ConstIntervalMatrixViewXd operandJacobian =
            evaluator.evaluateJacobian(operand(), parameterView);

        resultView = operandNormalized.transpose() * operandJacobian;
    }

    ExpressionImplementationPtr
    NormExpression::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex)->dot(operand()->normalized());
    }

    ExpressionImplementationPtr
    NormExpression::normImpl() const {
        return this;
    }
    
    void
    NormExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "NormExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    NormExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
        return newOperand->norm();
    }

    NormExpression::NormExpression(const ExpressionImplementationPtr& operand) :
        UnaryOperation(operand) {
    }
}
