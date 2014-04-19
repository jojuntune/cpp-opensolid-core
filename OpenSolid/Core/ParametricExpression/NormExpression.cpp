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
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluate(operand(), parameterView).colwise().norm();
    }
    
    void 
    NormExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluate(operand(), parameterView).colwise().norm();
    }

    void
    NormExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcd operandValue = evaluator.evaluate(operand(), parameterView);
        if (operandValue.isZero()) {
            throw Error(new PlaceholderError());
        }
        ColumnMatrixXd operandNormalized = operandValue.normalized();
        MapXcd operandJacobian = evaluator.evaluateJacobian(operand(), parameterView);
        resultView = operandNormalized.transpose() * operandJacobian;
    }
    
    void
    NormExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterView);
        if (operandBounds.isZero()) {
            throw Error(new PlaceholderError());
        }
        ColumnMatrixXI operandNormalized = operandBounds.normalized();
        MapXcI operandJacobian = evaluator.evaluateJacobian(operand(), parameterView);
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
