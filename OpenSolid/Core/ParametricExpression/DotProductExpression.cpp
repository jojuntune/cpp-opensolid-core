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

#include <OpenSolid/Core/ParametricExpression/DotProductExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{ 
    namespace detail
    {
        int
        DotProductExpression::numDimensionsImpl() const {
            return 1;
        }
        
        void
        DotProductExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                expressionCompiler.evaluate(firstOperand(), parameterID),
                expressionCompiler.evaluate(secondOperand(), parameterID),
                resultID,
                [] (
                    ConstMatrixViewXd firstValues,
                    ConstMatrixViewXd secondValues,
                    MatrixViewXd results
                ) {
                    for (int columnIndex = 0; columnIndex < results.numColumns(); ++columnIndex) {
                        results(0, columnIndex) = firstValues.column(columnIndex).binaryFold(
                            secondValues.column(columnIndex),
                            0.0,
                            [] (double result, double firstValue, double secondValue) {
                                return result + firstValue * secondValue;
                            }
                        );
                    }
                }
            );
        }
        
        void
        DotProductExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                expressionCompiler.evaluate(firstOperand(), parameterID),
                expressionCompiler.evaluate(secondOperand(), parameterID),
                resultID,
                [] (
                    ConstIntervalMatrixViewXd firstValues,
                    ConstIntervalMatrixViewXd secondValues,
                    IntervalMatrixViewXd results
                ) {
                    for (int columnIndex = 0; columnIndex < results.numColumns(); ++columnIndex) {
                        results(0, columnIndex) = firstValues.column(columnIndex).binaryFold(
                            secondValues.column(columnIndex),
                            Interval(0.0),
                            [] (Interval result, Interval firstValue, Interval secondValue) {
                                return result + firstValue * secondValue;
                            }
                        );
                    }
                }
            );
        }

        void
        DotProductExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            MatrixID<double> secondTransposeProductID = expressionCompiler.createTemporary(
                1,
                numParameters()
            );
            expressionCompiler.compute(
                expressionCompiler.evaluate(firstOperand(), parameterID),
                expressionCompiler.evaluate(secondOperand(), parameterID),
                expressionCompiler.evaluateJacobian(firstOperand(), parameterID),
                expressionCompiler.evaluateJacobian(secondOperand(), parameterID),
                secondTransposeProductID,
                resultID,
                [] (
                    ConstMatrixViewXd firstValues,
                    ConstMatrixViewXd secondValues,
                    ConstMatrixViewXd firstJacobian,
                    ConstMatrixViewXd secondJacobian,
                    MatrixViewXd secondTransposeProduct,
                    MatrixViewXd results
                ) {
                    results.setTransposeProduct(firstValues, secondJacobian);
                    secondTransposeProduct.setTransposeProduct(secondValues, firstJacobian);
                    results += secondTransposeProduct;
                }
            );
        }
        
        void
        DotProductExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            MatrixID<Interval> secondTransposeProductID = expressionCompiler.createTemporary(
                1,
                numParameters()
            );
            expressionCompiler.compute(
                expressionCompiler.evaluate(firstOperand(), parameterID),
                expressionCompiler.evaluate(secondOperand(), parameterID),
                expressionCompiler.evaluateJacobian(firstOperand(), parameterID),
                expressionCompiler.evaluateJacobian(secondOperand(), parameterID),
                secondTransposeProductID,
                resultID,
                [] (
                    ConstIntervalMatrixViewXd firstValues,
                    ConstIntervalMatrixViewXd secondValues,
                    ConstIntervalMatrixViewXd firstJacobian,
                    ConstIntervalMatrixViewXd secondJacobian,
                    IntervalMatrixViewXd secondTransposeProduct,
                    IntervalMatrixViewXd results
                ) {
                    results.setTransposeProduct(firstValues, secondJacobian);
                    secondTransposeProduct.setTransposeProduct(secondValues, firstJacobian);
                    results += secondTransposeProduct;
                }
            );
        }

        ExpressionImplementationPtr
        DotProductExpression::derivativeImpl(int parameterIndex) const {
            return (
                firstOperand()->derivative(parameterIndex)->dot(secondOperand()) +
                firstOperand()->dot(secondOperand()->derivative(parameterIndex))
            );
        }

        bool
        DotProductExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return duplicateOperands(other, true);
        }
        
        void
        DotProductExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "DotProductExpression" << std::endl;
            firstOperand()->debug(stream, indent + 1);
            secondOperand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        DotProductExpression::withNewOperandsImpl(
            const ExpressionImplementationPtr& newFirstOperand,
            const ExpressionImplementationPtr& newSecondOperand
        ) const {
            return newFirstOperand->dot(newSecondOperand);
        }

        DotProductExpression::DotProductExpression(
            const ExpressionImplementationPtr& firstOperand,
            const ExpressionImplementationPtr& secondOperand
        ) : BinaryOperation(firstOperand, secondOperand) {

            assert(firstOperand->numDimensions() == secondOperand->numDimensions());
        }
    }
}
