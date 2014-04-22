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

#include <OpenSolid/Core/ParametricExpression/ArcsineExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    ArcsineExpression::numDimensionsImpl() const {
        return 1;
    }
    
    void
    ArcsineExpression::evaluateImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        evaluator.evaluate(operand(), parameterView).map(
            [] (double value) {
                Interval domain(-1, 1);
                assert(domain.contains(value));
                return asin(domain.clamp(value));
            },
            resultView
        );
    }
    
    void
    ArcsineExpression::evaluateImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        evaluator.evaluate(operand(), parameterView).map(
            [] (Interval value) {
                Interval domain(-1, 1);
                assert(domain.overlaps(value));
                return asin(domain.clamp(value));
            },
            resultView
        );
    }

    void
    ArcsineExpression::evaluateJacobianImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        double operandValue = evaluator.evaluate(operand(), parameterView).value();
        if (abs(operandValue) - 1 >= Zero()) {
            throw Error(new PlaceholderError());
        }
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView *= 1.0 / sqrt(1 - operandValue * operandValue);
    }
    
    void
    ArcsineExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        Interval operandBounds = evaluator.evaluate(operand(), parameterView).value();
        if (abs(operandBounds).lowerBound() - 1 >= Zero()) {
            throw Error(new PlaceholderError());
        }
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView *= 1.0 / sqrt(1 - operandBounds.squared());
    }
    
    ExpressionImplementationPtr
    ArcsineExpression::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex) / sqrt(1.0 - operand()->squaredNorm());
    }
    
    bool
    ArcsineExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    ArcsineExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "ArcsineExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    ArcsineExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
        return asin(newOperand);
    }

    ArcsineExpression::ArcsineExpression(const ExpressionImplementationPtr& operand) :
        UnaryOperation(operand) {

        assert(operand->numDimensions() == 1);
    }
}
