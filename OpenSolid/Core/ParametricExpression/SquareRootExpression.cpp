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

#include <OpenSolid/Core/ParametricExpression/SquareRootExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    SquareRootExpression::numDimensionsImpl() const {
        return 1;
    }
    
    void
    SquareRootExpression::evaluateImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        resultView.setMap(
            evaluator.evaluate(operand(), parameterView),
            [] (double value) {
                if (value < Zero()) {
                    throw Error(new PlaceholderError());
                }
                return value > 0.0 ? sqrt(value) : 0.0;
            }            
        );
    }
    
    void
    SquareRootExpression::evaluateImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        resultView.setMap(
            evaluator.evaluate(operand(), parameterView),
            [] (Interval value) {
                return sqrt(value);
            }            
        );
    }

    void
    SquareRootExpression::evaluateJacobianImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        double operandValue = evaluator.evaluate(operand(), parameterView).value();
        if (operandValue <= Zero()) {
            throw Error(new PlaceholderError());
        }
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView *= 0.5 / sqrt(operandValue);
    }
    
    void
    SquareRootExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        Interval operandValue = evaluator.evaluate(operand(), parameterView).value();
        if (operandValue <= Zero()) {
            throw Error(new PlaceholderError());
        }
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView *= 0.5 / sqrt(operandValue);
    }

    ExpressionImplementationPtr
    SquareRootExpression::derivativeImpl(int parameterIndex) const {
        return 0.5 * operand()->derivative(parameterIndex) / self();
    }

    bool
    SquareRootExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    ExpressionImplementationPtr
    SquareRootExpression::squaredNormImpl() const {
        return operand();
    }
    
    void
    SquareRootExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "SquareRootExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    SquareRootExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
        return sqrt(newOperand);
    }

    SquareRootExpression::SquareRootExpression(const ExpressionImplementationPtr& operand) :
        UnaryOperation(operand) {
        
        assert(operand->numDimensions() == 1);
    }
}
