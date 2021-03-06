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

#include <OpenSolid/Core/ParametricExpression/ComponentsExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    namespace detail
    {
        int
        ComponentsExpression::numDimensionsImpl() const {
            return numComponents();
        }
        
        void
        ComponentsExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            int startIndex = this->startIndex();
            int numComponents = this->numComponents();
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                resultID,
                [startIndex, numComponents] (
                    const ConstMatrixViewXd operandValues,
                    MatrixViewXd results
                ) {
                    results = operandValues.block(
                        startIndex,
                        0,
                        numComponents,
                        operandValues.numColumns()
                    );
                }
            );
        }
        
        void
        ComponentsExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            int startIndex = this->startIndex();
            int numComponents = this->numComponents();
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                resultID,
                [startIndex, numComponents] (
                    ConstIntervalMatrixViewXd operandValues,
                    IntervalMatrixViewXd results
                ) {
                    results = operandValues.block(
                        startIndex,
                        0,
                        numComponents,
                        operandValues.numColumns()
                    );
                }
            );
        }

        void
        ComponentsExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            int startIndex = this->startIndex();
            int numComponents = this->numComponents();
            expressionCompiler.compute(
                expressionCompiler.evaluateJacobian(operand(), parameterID),
                resultID,
                [startIndex, numComponents] (
                    ConstMatrixViewXd operandJacobian,
                    MatrixViewXd results
                ) {
                    results = operandJacobian.block(
                        startIndex,
                        0,
                        numComponents,
                        operandJacobian.numColumns()
                    );
                }
            );
        }
        
        void
        ComponentsExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            int startIndex = this->startIndex();
            int numComponents = this->numComponents();
            expressionCompiler.compute(
                expressionCompiler.evaluateJacobian(operand(), parameterID),
                resultID,
                [startIndex, numComponents] (
                    ConstIntervalMatrixViewXd operandJacobian,
                    IntervalMatrixViewXd results
                ) {
                    results = operandJacobian.block(
                        startIndex,
                        0,
                        numComponents,
                        operandJacobian.numColumns()
                    );
                }
            );
        }

        ExpressionImplementationPtr
        ComponentsExpression::derivativeImpl(int parameterIndex) const {
            return operand()->derivative(parameterIndex)->components(startIndex(), numComponents());
        }

        bool
        ComponentsExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return (
                duplicateOperands(other) &&
                this->startIndex() == other->cast<ComponentsExpression>()->startIndex() &&
                this->numComponents() == other->cast<ComponentsExpression>()->numComponents()
            );
        }
        
        ExpressionImplementationPtr
        ComponentsExpression::componentsImpl(int startIndex, int numComponents) const {
            return operand()->components(this->startIndex() + startIndex, numComponents);
        }
        
        void
        ComponentsExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "ComponentsExpression" << std::endl;
            operand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        ComponentsExpression::withNewOperandImpl(
            const ExpressionImplementationPtr& newOperand
        ) const {
            return newOperand->components(startIndex(), numComponents());
        }

        ComponentsExpression::ComponentsExpression(
            const ExpressionImplementationPtr& operand,
            int startIndex,
            int numComponents
        ) : UnaryOperation(operand),
            _startIndex(startIndex),
            _numComponents(numComponents) {

            assert(startIndex >= 0);
            assert(numComponents > 0);
            assert(startIndex + numComponents <= operand->numDimensions());
        }
    }
}
