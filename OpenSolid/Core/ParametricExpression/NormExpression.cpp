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

#include <OpenSolid/Core/ParametricExpression/NormExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    namespace detail
    {
        int
        NormExpression::numDimensionsImpl() const {
            return 1;
        }

        bool
        NormExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return duplicateOperands(other);
        }
        
        void
        NormExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                resultID,
                [] (ConstMatrixViewXd operandValues, MatrixViewXd results) {
                    for (int columnIndex = 0; columnIndex < results.numColumns(); ++columnIndex) {
                        results(0, columnIndex) = opensolid::sqrt(
                            operandValues.column(columnIndex).fold(
                                0.0,
                                [] (double result, double value) {
                                    return result + value * value;
                                }
                            )
                        );
                    }
                }
            );
        }
        
        void 
        NormExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                resultID,
                [] (ConstIntervalMatrixViewXd operandValues, IntervalMatrixViewXd results) {
                    for (int columnIndex = 0; columnIndex < results.numColumns(); ++columnIndex) {
                        results(0, columnIndex) = opensolid::sqrt(
                            operandValues.column(columnIndex).fold(
                                Interval(0.0),
                                [] (Interval result, Interval value) {
                                    return result + value * value;
                                }
                            )
                        );
                    }
                }
            );
        }

        void
        NormExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                expressionCompiler.createTemporary(operand()->numDimensions(), 1),
                expressionCompiler.evaluateJacobian(operand(), parameterID),
                resultID,
                [] (
                    ConstMatrixViewXd operandValues,
                    MatrixViewXd operandNormalized,
                    ConstMatrixViewXd operandJacobian,
                    MatrixViewXd results
                ) {
                    double operandNorm = opensolid::sqrt(operandValues.cwiseSquared().sum());
                    if (operandNorm == Zero()) {
                        throw Error(new PlaceholderError());
                    }
                    operandNormalized = operandValues;
                    operandNormalized /= operandNorm;
                    results.setTransposeProduct(operandNormalized, operandJacobian);
                }
            );
        }
        
        void
        NormExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                expressionCompiler.createTemporary(operand()->numDimensions(), 1),
                expressionCompiler.evaluateJacobian(operand(), parameterID),
                resultID,
                [] (
                    ConstIntervalMatrixViewXd operandValues,
                    IntervalMatrixViewXd operandNormalized,
                    ConstIntervalMatrixViewXd operandJacobian,
                    IntervalMatrixViewXd results
                ) {
                    Interval operandNorm = opensolid::sqrt(operandValues.cwiseSquared().sum());
                    if (operandNorm == Zero()) {
                        throw Error(new PlaceholderError());
                    }
                    operandNormalized = operandValues;
                    operandNormalized /= operandNorm;
                    results.setTransposeProduct(operandNormalized, operandJacobian);
                }
            );
        }

        ExpressionImplementationPtr
        NormExpression::derivativeImpl(int parameterIndex) const {
            return operand()->derivative(parameterIndex)->dot(operand()->normalized());
        }

        ExpressionImplementationPtr
        NormExpression::normImpl() const {
            return self();
        }
        
        void
        NormExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "NormExpression" << std::endl;
            operand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        NormExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
            return newOperand->norm();
        }

        NormExpression::NormExpression(const ExpressionImplementationPtr& operand) :
            UnaryOperation(operand) {
        }
    }
}
