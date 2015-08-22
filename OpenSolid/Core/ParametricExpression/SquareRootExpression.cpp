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

#include <OpenSolid/Core/ParametricExpression/SquareRootExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{ 
    namespace detail
    {
        int
        SquareRootExpression::numDimensionsImpl() const {
            return 1;
        }
        
        void
        SquareRootExpression::evaluateImpl(
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
                            if (value < Zero()) {
                                throw Error(new PlaceholderError());
                            }
                            return value > 0.0 ? opensolid::sqrt(value) : 0.0;
                        }
                    );
                }
            );
        }
        
        void
        SquareRootExpression::evaluateImpl(
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
                            return opensolid::sqrt(value);
                        }
                    );
                }
            );
        }

        void
        SquareRootExpression::evaluateJacobianImpl(
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
                    if (operandValue <= Zero()) {
                        throw Error(new PlaceholderError());
                    }
                    results *= (0.5 / opensolid::sqrt(operandValue));
                }
            );
        }
        
        void
        SquareRootExpression::evaluateJacobianImpl(
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
                    if (operandValue.upperBound() <= Zero()) {
                        throw Error(new PlaceholderError());
                    }
                    results *= (0.5 / opensolid::sqrt(operandValue));
                }
            );
        }

        ExpressionImplementationPtr
        SquareRootExpression::derivativeImpl(int parameterIndex) const {
            return 0.5 * operand()->derivative(parameterIndex) / self();
        }

        bool
        SquareRootExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return duplicateOperands(other);
        }
        
        ExpressionImplementationPtr
        SquareRootExpression::squaredNormImpl() const {
            return operand();
        }
        
        void
        SquareRootExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "SquareRootExpression" << std::endl;
            operand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        SquareRootExpression::withNewOperandImpl(
            const ExpressionImplementationPtr& newOperand
        ) const {
            return sqrt(newOperand);
        }

        SquareRootExpression::SquareRootExpression(const ExpressionImplementationPtr& operand) :
            UnaryOperation(operand) {
            
            assert(operand->numDimensions() == 1);
        }
    }
}
