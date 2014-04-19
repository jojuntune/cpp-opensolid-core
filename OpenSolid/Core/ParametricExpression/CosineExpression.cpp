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

#include <OpenSolid/Core/ParametricExpression/CosineExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    CosineExpression::numDimensionsImpl() const {
        return 1;
    }
    
    void
    CosineExpression::evaluateImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterValues).array().cos();
    }
    
    void
    CosineExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterValues).array().cos();
    }

    void
    CosineExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        double operandValue = evaluator.evaluate(operand(), parameterValues).value();
        MapXcd operandJacobian = evaluator.evaluateJacobian(operand(), parameterValues);
        results = -sin(operandValue) * operandJacobian;
    }
    
    void
    CosineExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        Interval operandBounds = evaluator.evaluate(operand(), parameterValues).value();
        MapXcI operandJacobian = evaluator.evaluateJacobian(operand(), parameterValues);
        results = -sin(operandBounds) * operandJacobian;
    }

    ExpressionImplementationPtr
    CosineExpression::derivativeImpl(int parameterIndex) const {
        return -sin(operand()) * operand()->derivative(parameterIndex);
    }

    bool
    CosineExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    CosineExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "CosineExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    CosineExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
        return cos(newOperand);
    }

    CosineExpression::CosineExpression(const ExpressionImplementationPtr& operand) :
        UnaryOperation(operand) {

        assert(operand->numDimensions() == 1);
    }
}
