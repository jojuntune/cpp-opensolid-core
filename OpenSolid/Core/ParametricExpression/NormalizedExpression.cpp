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

#include <OpenSolid/Core/ParametricExpression/NormalizedExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    NormalizedExpression::numDimensionsImpl() const {
        return operand()->numDimensions();
    }

    bool
    NormalizedExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other);
    }

    void
    NormalizedExpression::evaluateImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcd operandValues = evaluator.evaluate(operand(), parameterView);
        RowMatrixXd squaredNorms = operandValues.colwise().squaredNorm();
        resultView = operandValues * squaredNorms.cwiseSqrt().cwiseInverse().asDiagonal();
    }

    void
    NormalizedExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterView);
        RowMatrixXI squaredNorms = operandBounds.colwise().squaredNorm();
        resultView = operandBounds * squaredNorms.cwiseSqrt().cwiseInverse().asDiagonal();
    }

    void
    NormalizedExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcd operandValue = evaluator.evaluate(operand(), parameterView);
        double operandNorm = operandValue.norm();
        if (operandNorm == Zero()) {
            throw Error(new PlaceholderError());
        }
        ColumnMatrixXd operandNormalized = operandValue / operandNorm;
        MapXcd operandJacobian = evaluator.evaluateJacobian(operand(), parameterView);

        resultView = (operandJacobian - operandNormalized * (operandNormalized.transpose() *
            operandJacobian)) / operandNorm;
    }
    
    void
    NormalizedExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterView);
        Interval operandNorm = operandBounds.norm();
        if (operandNorm == Zero()) {
            throw Error(new PlaceholderError());
        }
        ColumnMatrixXI operandNormalized = operandBounds / operandNorm;
        MapXcI operandJacobian = evaluator.evaluateJacobian(operand(), parameterView);

        resultView = (operandJacobian - operandNormalized * (operandNormalized.transpose() *
            operandJacobian)) / operandNorm;
    }

    ExpressionImplementationPtr
    NormalizedExpression::derivativeImpl(int parameterIndex) const {
        ExpressionImplementationPtr operandDerivative = operand()->derivative(parameterIndex);
        ExpressionImplementationPtr operandNormalized = operand()->normalized();
        return
            (operandDerivative - operandDerivative->dot(operandNormalized) * operandNormalized) /
            operand()->norm();
    }
    
    ExpressionImplementationPtr
    NormalizedExpression::normImpl() const {
        return new ConstantExpression(1.0, numParameters());
    }
    
    ExpressionImplementationPtr
    NormalizedExpression::normalizedImpl() const {
        return this;
    }
    
    ExpressionImplementationPtr
    NormalizedExpression::squaredNormImpl() const {
        return new ConstantExpression(1.0, numParameters());
    }
    
    void
    NormalizedExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "NormalizedExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    NormalizedExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
        return newOperand->normalized();
    }

    NormalizedExpression::NormalizedExpression(const ExpressionImplementationPtr& operand) :
        UnaryOperation(operand) {
    }
}
