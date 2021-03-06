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

#include <OpenSolid/Core/ParametricExpression/ScalingExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    namespace detail
    {
        int
        ScalingExpression::numDimensionsImpl() const {
            return operand()->numDimensions();
        }
        
        void
        ScalingExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(operand(), parameterID, resultID);
            double scale = this->scale();
            expressionCompiler.compute(
                resultID,
                [scale] (MatrixViewXd results) {
                    results *= scale;
                }
            );
        }
        
        void
        ScalingExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(operand(), parameterID, resultID);
            double scale = this->scale();
            expressionCompiler.compute(
                resultID,
                [scale] (IntervalMatrixViewXd results) {
                    results *= scale;
                }
            );
        }

        void
        ScalingExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(operand(), parameterID, resultID);
            double scale = this->scale();
            expressionCompiler.compute(
                resultID,
                [scale] (MatrixViewXd results) {
                    results *= scale;
                }
            );
        }
        
        void
        ScalingExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(operand(), parameterID, resultID);
            double scale = this->scale();
            expressionCompiler.compute(
                resultID,
                [scale] (IntervalMatrixViewXd results) {
                    results *= scale;
                }
            );
        }
        
        ExpressionImplementationPtr
        ScalingExpression::derivativeImpl(int parameterIndex) const {
            return scale() * operand()->derivative(parameterIndex);
        }

        bool
        ScalingExpression::isDuplicateOfImpl(
            const ExpressionImplementationPtr& other
        ) const {
            return (
                duplicateOperands(other) &&
                this->scale() == other->cast<ScalingExpression>()->scale()
            );
        }

        ExpressionImplementationPtr
        ScalingExpression::scalingImpl(double scale) const {
            return (scale * this->scale()) * operand();
        }

        ExpressionImplementationPtr
        ScalingExpression::transformationImpl(const MatrixXd& matrix) const {
            return (scale() * matrix) * operand();
        }
        
        void
        ScalingExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "ScalingExpression: scale = " << scale() << std::endl;
            operand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        ScalingExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
            return scale() * newOperand;
        }

        ScalingExpression::ScalingExpression(
            double scale, 
            const ExpressionImplementationPtr& operand
        ) :
            UnaryOperation(operand),
            _scale(scale) {
        }
    }
}
