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

#include <OpenSolid/Core/ParametricExpression/NegatedExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    NegatedExpression::numDimensionsImpl() const {
        return operand()->numDimensions();
    }

    void
    NegatedExpression::evaluateImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluate(operand(), parameterView);
        resultView *= -1.0;
    }

    void
    NegatedExpression::evaluateImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluate(operand(), parameterView);
        resultView *= -1.0;
    }

    void
    NegatedExpression::evaluateJacobianImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView *= -1.0;
    }
    
    void
    NegatedExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView *= -1.0;
    }

    ExpressionImplementationPtr
    NegatedExpression::derivativeImpl(int parameterIndex) const {
        return -operand()->derivative(parameterIndex);
    }

    bool
    NegatedExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
 
    ExpressionImplementationPtr
    NegatedExpression::componentsImpl(int startIndex, int numComponents) const {
        return -operand()->components(startIndex, numComponents);
    }

    ExpressionImplementationPtr
    NegatedExpression::scalingImpl(double scale) const {
        return (-scale) * operand();
    }

    ExpressionImplementationPtr
    NegatedExpression::transformationImpl(const MatrixXd& matrix) const {
        return (-matrix) * operand();
    }

    ExpressionImplementationPtr
    NegatedExpression::normImpl() const {
        return operand()->norm();
    }

    ExpressionImplementationPtr
    NegatedExpression::normalizedImpl() const {
        return -operand()->normalized();
    }

    ExpressionImplementationPtr
    NegatedExpression::squaredNormImpl() const {
        return operand()->squaredNorm();
    }

    ExpressionImplementationPtr
    NegatedExpression::negatedImpl() const {
        return operand();
    }

    ExpressionImplementationPtr
    NegatedExpression::sinImpl() const {
        return -sin(operand());
    }

    ExpressionImplementationPtr
    NegatedExpression::cosImpl() const {
        return cos(operand());
    }

    ExpressionImplementationPtr
    NegatedExpression::tanImpl() const {
        return -tan(operand());
    }

    ExpressionImplementationPtr
    NegatedExpression::acosImpl() const {
        return M_PI - acos(operand());
    }

    ExpressionImplementationPtr
    NegatedExpression::asinImpl() const {
        return -asin(operand());
    }

    void
    NegatedExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "NegatedExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    NegatedExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
        return -newOperand;
    }

    NegatedExpression::NegatedExpression(const ExpressionImplementationPtr& operand) :
        UnaryOperation(operand) {
    }
}
