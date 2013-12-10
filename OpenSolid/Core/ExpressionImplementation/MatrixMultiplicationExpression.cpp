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

#include <OpenSolid/Core/ExpressionImplementation/MatrixMultiplicationExpression.hpp>

#include <OpenSolid/Core/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    MatrixMultiplicationExpression::numDimensionsImpl() const {
        return matrix().rows();
    }
    
    void
    MatrixMultiplicationExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = matrix() * evaluator.evaluate(operand(), parameterValues);
    }
    
    void
    MatrixMultiplicationExpression::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = matrix().cast<Interval>() * evaluator.evaluate(operand(), parameterBounds);
    }

    void
    MatrixMultiplicationExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = matrix() * evaluator.evaluateJacobian(operand(), parameterValues);
    }
    
    void
    MatrixMultiplicationExpression::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = matrix().cast<Interval>() *
            evaluator.evaluateJacobian(operand(), parameterBounds);
    }
    
    ExpressionImplementationPtr
    MatrixMultiplicationExpression::derivativeImpl(int parameterIndex) const {
        return matrix() * operand()->derivative(parameterIndex);
    }

    bool
    MatrixMultiplicationExpression::isDuplicateOfImpl(
        const ExpressionImplementationPtr& other
    ) const {
        MatrixXd otherMatrix = other->cast<MatrixMultiplicationExpression>()->matrix();
        return duplicateOperands(other) && (matrix() - otherMatrix).isZero();
    }

    ExpressionImplementationPtr
    MatrixMultiplicationExpression::scalarMultiplicationImpl(double scale) const {
        return (scale * matrix()) * operand();
    }

    ExpressionImplementationPtr
    MatrixMultiplicationExpression::matrixMultiplicationImpl(const MatrixXd& matrix) const {
        return (matrix * this->matrix()) * operand();
    }
    
    void
    MatrixMultiplicationExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "MatrixMultiplicationExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    MatrixMultiplicationExpression::withNewOperandImpl(
        const ExpressionImplementationPtr& newOperand
    ) const {
        return matrix() * newOperand;
    }

    MatrixMultiplicationExpression::MatrixMultiplicationExpression(
        const MatrixXd& matrix,
        const ExpressionImplementationPtr& operand
    ) : UnaryOperation(operand),
        _matrix(matrix) {

        assert(matrix.cols() == operand->numDimensions());
    }
}
