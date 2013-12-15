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

#include <OpenSolid/Core/ParametricExpression/VectorAdditionExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    VectorAdditionExpression::numDimensionsImpl() const {
        return operand()->numDimensions();
    }
    
    void
    VectorAdditionExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd operandValues = evaluator.evaluate(operand(), parameterValues);
        results = operandValues.colwise() + vector();
    }
    
    void
    VectorAdditionExpression::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterBounds);
        results = operandBounds.colwise() + vector().cast<Interval>();
    }

    void
    VectorAdditionExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluateJacobian(operand(), parameterValues);
    }
    
    void
    VectorAdditionExpression::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluateJacobian(operand(), parameterBounds);
    }
    
    ExpressionImplementationPtr
    VectorAdditionExpression::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex);
    }

    bool
    VectorAdditionExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other) &&
            (vector() - other->cast<VectorAdditionExpression>()->vector()).isZero();
    }

    ExpressionImplementationPtr
    VectorAdditionExpression::vectorAdditionImpl(const VectorXd& vector) const {
        return operand() + (this->vector() + vector);
    }
    
    void
    VectorAdditionExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "VectorAdditionExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    VectorAdditionExpression::withNewOperandImpl(
        const ExpressionImplementationPtr& newOperand
    ) const {
        return newOperand + vector();
    }

    VectorAdditionExpression::VectorAdditionExpression(
        const ExpressionImplementationPtr& operand,
        const VectorXd& vector
    ) : UnaryOperation(operand),
        _vector(vector) {

        assert(vector.size() == operand->numDimensions());
    }
}
