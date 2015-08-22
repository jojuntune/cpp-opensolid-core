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

#include <OpenSolid/Core/ParametricExpression/QuotientExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{  
    namespace detail
    {
        int
        QuotientExpression::numDimensionsImpl() const {
            return firstOperand()->numDimensions();
        }
        
        void
        QuotientExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(firstOperand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(secondOperand(), parameterID),
                resultID,
                [] (ConstMatrixViewXd divisorValues, MatrixViewXd results) {
                    for (int columnIndex = 0; columnIndex < results.numColumns(); ++columnIndex) {
                        double divisorValue = divisorValues(0, columnIndex);
                        if (divisorValue == Zero()) {
                            throw Error(new PlaceholderError());
                        }
                        results.column(columnIndex) /= divisorValue;
                    }
                }
            );
        }
        
        void
        QuotientExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(firstOperand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(secondOperand(), parameterID),
                resultID,
                [] (ConstIntervalMatrixViewXd divisorValues, IntervalMatrixViewXd results) {
                    for (int columnIndex = 0; columnIndex < results.numColumns(); ++columnIndex) {
                        Interval divisorValue = divisorValues(0, columnIndex);
                        if (divisorValue == Zero()) {
                            throw Error(new PlaceholderError());
                        }
                        results.column(columnIndex) /= divisorValue;
                    }
                }
            );
        }

        void
        QuotientExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(firstOperand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(firstOperand(), parameterID),
                expressionCompiler.evaluate(secondOperand(), parameterID),
                expressionCompiler.evaluateJacobian(secondOperand(), parameterID),
                expressionCompiler.createTemporary(numDimensions(), numParameters()),
                resultID,
                [] (
                    ConstMatrixViewXd dividendValues,
                    ConstMatrixViewXd divisorValues,
                    ConstMatrixViewXd divisorJacobian,
                    MatrixViewXd tempProduct,
                    MatrixViewXd results
                ) {
                    double divisorValue = divisorValues.value();
                    if (divisorValue == Zero()) {
                        throw Error(new PlaceholderError());
                    }
                    results *= divisorValue;
                    tempProduct.setProduct(dividendValues, divisorJacobian);
                    results -= tempProduct;
                    results *= (1.0 / (divisorValue * divisorValue));
                }
            );
        }
        
        void
        QuotientExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(firstOperand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(firstOperand(), parameterID),
                expressionCompiler.evaluate(secondOperand(), parameterID),
                expressionCompiler.evaluateJacobian(secondOperand(), parameterID),
                expressionCompiler.createTemporary(numDimensions(), numParameters()),
                resultID,
                [] (
                    ConstIntervalMatrixViewXd dividendValues,
                    ConstIntervalMatrixViewXd divisorValues,
                    ConstIntervalMatrixViewXd divisorJacobian,
                    IntervalMatrixViewXd tempProduct,
                    IntervalMatrixViewXd results
                ) {
                    Interval divisorValue = divisorValues.value();
                    if (divisorValue == Zero()) {
                        throw Error(new PlaceholderError());
                    }
                    results *= divisorValue;
                    tempProduct.setProduct(dividendValues, divisorJacobian);
                    results -= tempProduct;
                    results *= (1.0 / divisorValue.squared());
                }
            );
        }

        ExpressionImplementationPtr
        QuotientExpression::derivativeImpl(int parameterIndex) const {
            ExpressionImplementationPtr firstDerivative = (
                firstOperand()->derivative(parameterIndex)
            );
            ExpressionImplementationPtr secondDerivative = (
                secondOperand()->derivative(parameterIndex)
            );
            return (
                (firstDerivative * secondOperand() - firstOperand() * secondDerivative) /
                secondOperand()->squaredNorm()
            );
        }

        bool
        QuotientExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return duplicateOperands(other, false);
        }
        
        void
        QuotientExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "QuotientExpression" << std::endl;
            firstOperand()->debug(stream, indent + 1);
            secondOperand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        QuotientExpression::withNewOperandsImpl(
            const ExpressionImplementationPtr& newFirstOperand,
            const ExpressionImplementationPtr& newSecondOperand
        ) const {
            return newFirstOperand / newSecondOperand;
        }

        QuotientExpression::QuotientExpression(
            const ExpressionImplementationPtr& firstOperand,
            const ExpressionImplementationPtr& secondOperand
        ) : BinaryOperation(firstOperand, secondOperand) {

            assert(secondOperand->numDimensions() == 1);
        }
    }
}
