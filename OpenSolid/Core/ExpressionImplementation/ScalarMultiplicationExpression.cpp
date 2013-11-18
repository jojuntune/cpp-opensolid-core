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
*************************************************************************************/

#include <OpenSolid/Core/ExpressionImplementation/ScalarMultiplicationExpression.hpp>

#include <OpenSolid/Core/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    ScalarMultiplicationExpression::numDimensionsImpl() const {
        return operand()->numDimensions();
    }
    
    void
    ScalarMultiplicationExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = scale() * evaluator.evaluate(operand(), parameterValues);
    }
    
    void
    ScalarMultiplicationExpression::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = Interval(scale()) * evaluator.evaluate(operand(), parameterBounds);
    }

    void
    ScalarMultiplicationExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = scale() * evaluator.evaluateJacobian(operand(), parameterValues);
    }
    
    void
    ScalarMultiplicationExpression::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = Interval(scale()) * evaluator.evaluateJacobian(operand(), parameterBounds);
    }
    
    ExpressionImplementationPtr
    ScalarMultiplicationExpression::derivativeImpl(int parameterIndex) const {
        return scale() * operand()->derivative(parameterIndex);
    }

    bool
    ScalarMultiplicationExpression::isDuplicateOfImpl(
        const ExpressionImplementationPtr& other
    ) const {
        return duplicateOperands(other) &&
            this->scale() == other->cast<ScalarMultiplicationExpression>()->scale();
    }

    ExpressionImplementationPtr
    ScalarMultiplicationExpression::scalarMultiplicationImpl(double scale) const {
        return (scale * this->scale()) * operand();
    }

    ExpressionImplementationPtr
    ScalarMultiplicationExpression::matrixMultiplicationImpl(const MatrixXd& matrix) const {
        return (scale() * matrix) * operand();
    }
    
    void
    ScalarMultiplicationExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "ScalarMultiplicationExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    ScalarMultiplicationExpression::withNewOperandImpl(
        const ExpressionImplementationPtr& newOperand
    ) const {
        return scale() * newOperand;
    }

    ScalarMultiplicationExpression::ScalarMultiplicationExpression(
        double scale,
        const ExpressionImplementationPtr& operand
    ) : UnaryOperation(operand),
        _scale(scale) {
    }
}
