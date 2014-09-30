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

#include <OpenSolid/Core/ParametricExpression/NormalizedExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    namespace detail
    {
        int
        NormalizedExpression::numDimensionsImpl() const {
            return operand()->numDimensions();
        }

        bool
        NormalizedExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return duplicateOperands(other);
        }

        void
        NormalizedExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(operand(), parameterID, resultID);
            expressionCompiler.compute(
                resultID,
                [] (MatrixViewXd results) {
                    for (int columnIndex = 0; columnIndex < results.numColumns(); ++columnIndex) {
                        auto column = results.column(columnIndex);
                        double norm = opensolid::sqrt(
                            column.fold(
                                0.0,
                                [] (double result, double value) {
                                    return result + value * value;
                                }
                            )
                        );
                        if (norm == Zero()) {
                            throw PlaceholderError();
                        }
                        column /= norm;
                    }
                }
            );
        }

        void
        NormalizedExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(operand(), parameterID, resultID);
            expressionCompiler.compute(
                resultID,
                [] (IntervalMatrixViewXd results) {
                    for (int columnIndex = 0; columnIndex < results.numColumns(); ++columnIndex) {
                        auto column = results.column(columnIndex);
                        Interval norm = opensolid::sqrt(
                            column.fold(
                                Interval(0.0),
                                [] (Interval result, Interval value) {
                                    return result + value * value;
                                }
                            )
                        );
                        if (norm == Zero()) {
                            throw PlaceholderError();
                        }
                        column /= norm;
                    }
                }
            );
        }

        void
        NormalizedExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(operand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                expressionCompiler.createTemporary(numDimensions(), 1),
                expressionCompiler.createTemporary(1, numParameters()),
                expressionCompiler.createTemporary(numDimensions(), numParameters()),
                resultID,
                [] (
                    ConstMatrixViewXd operandValues,
                    MatrixViewXd operandNormalized,
                    MatrixViewXd transposeProduct,
                    MatrixViewXd outerProduct,
                    MatrixViewXd results
                ) {
                    double operandNorm = opensolid::sqrt(operandValues.cwiseSquared().sum());
                    if (operandNorm == Zero()) {
                        throw Error(new PlaceholderError());
                    }
                    operandNormalized = operandValues;
                    operandNormalized /= operandNorm;
                    transposeProduct.setTransposeProduct(operandNormalized, results);
                    outerProduct.setProduct(operandNormalized, transposeProduct);
                    results -= outerProduct;
                    results /= operandNorm;
                }
            );
        }
        
        void
        NormalizedExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(operand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                expressionCompiler.createTemporary(numDimensions(), 1),
                expressionCompiler.createTemporary(1, numParameters()),
                expressionCompiler.createTemporary(numDimensions(), numParameters()),
                resultID,
                [] (
                    ConstIntervalMatrixViewXd operandValues,
                    IntervalMatrixViewXd operandNormalized,
                    IntervalMatrixViewXd transposeProduct,
                    IntervalMatrixViewXd outerProduct,
                    IntervalMatrixViewXd results
                ) {
                    Interval operandNorm = opensolid::sqrt(operandValues.cwiseSquared().sum());
                    if (operandNorm == Zero()) {
                        throw Error(new PlaceholderError());
                    }
                    operandNormalized = operandValues;
                    operandNormalized /= operandNorm;
                    transposeProduct.setTransposeProduct(operandNormalized, results);
                    outerProduct.setProduct(operandNormalized, transposeProduct);
                    results -= outerProduct;
                    results /= operandNorm;
                }
            );
        }

        ExpressionImplementationPtr
        NormalizedExpression::derivativeImpl(int parameterIndex) const {
            ExpressionImplementationPtr operandDerivative = operand()->derivative(parameterIndex);
            ExpressionImplementationPtr operandNormalized = operand()->normalized();
            return (
                operandDerivative -
                operandDerivative->dot(operandNormalized) * operandNormalized
            ) / operand()->norm();
        }
        
        ExpressionImplementationPtr
        NormalizedExpression::normImpl() const {
            return new ConstantExpression(1.0, numParameters());
        }
        
        ExpressionImplementationPtr
        NormalizedExpression::normalizedImpl() const {
            return this;
        }
        
        ExpressionImplementationPtr
        NormalizedExpression::squaredNormImpl() const {
            return new ConstantExpression(1.0, numParameters());
        }
        
        void
        NormalizedExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "NormalizedExpression" << std::endl;
            operand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        NormalizedExpression::withNewOperandImpl(
            const ExpressionImplementationPtr& newOperand
        ) const {
            return newOperand->normalized();
        }

        NormalizedExpression::NormalizedExpression(const ExpressionImplementationPtr& operand) :
            UnaryOperation(operand) {
        }
    }
}
