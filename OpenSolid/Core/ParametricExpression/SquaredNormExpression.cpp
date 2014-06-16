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

#include <OpenSolid/Core/ParametricExpression/SquaredNormExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    namespace detail
    {
        int
        SquaredNormExpression::numDimensionsImpl() const {
            return 1;
        }
        
        void
        SquaredNormExpression::evaluateImpl(
            const ConstMatrixViewXd& parameterView,
            MatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            ConstMatrixViewXd operandValues = evaluator.evaluate(operand(), parameterView);
            for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
                resultView(0, columnIndex) = operandValues.column(columnIndex).fold(
                    0.0,
                    [] (double result, double value) {
                        return result + value * value;
                    }
                );
            }
        }
        
        void
        SquaredNormExpression::evaluateImpl(
            const ConstIntervalMatrixViewXd& parameterView,
            IntervalMatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            ConstIntervalMatrixViewXd operandValues = evaluator.evaluate(operand(), parameterView);
            for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
                resultView(0, columnIndex) = operandValues.column(columnIndex).fold(
                    Interval(0.0),
                    [] (Interval result, Interval value) {
                        return result + value.squared();
                    }
                );
            }
        }

        void
        SquaredNormExpression::evaluateJacobianImpl(
            const ConstMatrixViewXd& parameterView,
            MatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            ConstMatrixViewXd operandValue = evaluator.evaluate(operand(), parameterView);
            ConstMatrixViewXd operandJacobian = 
                evaluator.evaluateJacobian(operand(), parameterView);
            resultView = 2.0 * operandValue.transpose() * operandJacobian;
        }
        
        void
        SquaredNormExpression::evaluateJacobianImpl(
            const ConstIntervalMatrixViewXd& parameterView,
            IntervalMatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            ConstIntervalMatrixViewXd operandBounds = evaluator.evaluate(operand(), parameterView);
            ConstIntervalMatrixViewXd operandJacobian =
                evaluator.evaluateJacobian(operand(), parameterView);
            resultView = 2.0 * operandBounds.transpose() * operandJacobian;
        }

        ExpressionImplementationPtr
        SquaredNormExpression::derivativeImpl(int parameterIndex) const {
            return 2.0 * operand()->dot(operand()->derivative(parameterIndex));
        }

        bool
        SquaredNormExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return duplicateOperands(other);
        }
        
        void
        SquaredNormExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "SquaredNormExpression" << std::endl;
            operand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        SquaredNormExpression::withNewOperandImpl(
            const ExpressionImplementationPtr& newOperand
        ) const {
            return newOperand->squaredNorm();
        }

        SquaredNormExpression::SquaredNormExpression(const ExpressionImplementationPtr& operand) :
            UnaryOperation(operand) {
        }
    }
}
