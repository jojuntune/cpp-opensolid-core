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

#include <OpenSolid/Core/ParametricExpression/TransformationExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    TransformationExpression::numDimensionsImpl() const {
        return int(matrix().numRows());
    }
    
    void
    TransformationExpression::evaluateImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView = matrix() * evaluator.evaluate(operand(), parameterView);
    }
    
    void
    TransformationExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView = matrix() * evaluator.evaluate(operand(), parameterView);
    }

    void
    TransformationExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView = matrix() * evaluator.evaluateJacobian(operand(), parameterView);
    }
    
    void
    TransformationExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView = matrix() * evaluator.evaluateJacobian(operand(), parameterView);
    }
    
    ExpressionImplementationPtr
    TransformationExpression::derivativeImpl(int parameterIndex) const {
        return matrix() * operand()->derivative(parameterIndex);
    }

    bool
    TransformationExpression::isDuplicateOfImpl(
        const ExpressionImplementationPtr& other
    ) const {
        MatrixXxX otherMatrix = other->cast<TransformationExpression>()->matrix();
        return duplicateOperands(other) && (matrix() - otherMatrix).isZero();
    }

    ExpressionImplementationPtr
    TransformationExpression::scalingImpl(double scale) const {
        return (scale * matrix()) * operand();
    }

    ExpressionImplementationPtr
    TransformationExpression::transformationImpl(const MatrixXxX& matrix) const {
        return (matrix * this->matrix()) * operand();
    }
    
    void
    TransformationExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "TransformationExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    TransformationExpression::withNewOperandImpl(
        const ExpressionImplementationPtr& newOperand
    ) const {
        return matrix() * newOperand;
    }

    TransformationExpression::TransformationExpression(
        const MatrixXxX& matrix,
        const ExpressionImplementationPtr& operand
    ) : UnaryOperation(operand),
        _matrix(matrix) {

        assert(matrix.numColumns() == operand->numDimensions());
    }
}
