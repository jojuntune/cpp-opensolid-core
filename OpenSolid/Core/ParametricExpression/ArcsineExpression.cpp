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

#include <OpenSolid/Core/ParametricExpression/ArcsineExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    namespace detail
    {
        int
        ArcsineExpression::numDimensionsImpl() const {
            return 1;
        }
        
        void
        ArcsineExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(operand(), parameterID, resultID);
            expressionCompiler.compute(
                resultID,
                [] (MatrixViewXd results) {
                    results.setMap(
                        results,
                        [] (double value) {
                            Interval domain(-1, 1);
                            if (!domain.contains(value)) {
                                throw Error(new PlaceholderError());
                            }
                            return opensolid::asin(domain.clamp(value));
                        }
                    );
                }
            );
        }
        
        void
        ArcsineExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(operand(), parameterID, resultID);
            expressionCompiler.compute(
                resultID,
                [] (IntervalMatrixViewXd results) {
                    results.setMap(
                        results,
                        [] (Interval value) {
                            Interval domain(-1, 1);
                            if (!domain.overlaps(value)) {
                                throw Error(new PlaceholderError());
                            }
                            return opensolid::asin(domain.clamp(value));
                        }
                    );
                }
            );
        }

        void
        ArcsineExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(operand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                resultID,
                [] (ConstMatrixViewXd operandValues, MatrixViewXd results) {
                    double operandValue = operandValues.value();
                    if (!Interval(-1, 1).strictlyContains(operandValue)) {
                        throw Error(new PlaceholderError());
                    }
                    results *= 1.0 / opensolid::sqrt(1 - operandValue * operandValue);
                }
            );
        }
        
        void
        ArcsineExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(operand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                resultID,
                [] (ConstIntervalMatrixViewXd operandValues, IntervalMatrixViewXd results) {
                    Interval operandValue = operandValues.value();
                    if (!Interval(-1, 1).strictlyOverlaps(operandValue)) {
                        throw Error(new PlaceholderError());
                    }
                    results *= 1.0 / opensolid::sqrt(1 - operandValue.squared());
                }
            );
        }
        
        ExpressionImplementationPtr
        ArcsineExpression::derivativeImpl(int parameterIndex) const {
            return operand()->derivative(parameterIndex) / sqrt(1.0 - operand()->squaredNorm());
        }
        
        bool
        ArcsineExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return duplicateOperands(other);
        }
        
        void
        ArcsineExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "ArcsineExpression" << std::endl;
            operand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        ArcsineExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
            return asin(newOperand);
        }

        ArcsineExpression::ArcsineExpression(const ExpressionImplementationPtr& operand) :
            UnaryOperation(operand) {

            assert(operand->numDimensions() == 1);
        }
    }
}
