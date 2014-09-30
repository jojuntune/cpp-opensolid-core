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

#include <OpenSolid/Core/ParametricExpression/DifferenceExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    namespace detail
    {
        int
        DifferenceExpression::numDimensionsImpl() const {
            return firstOperand()->numDimensions();
        }
        
        void
        DifferenceExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(firstOperand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(secondOperand(), parameterID),
                resultID,
                [] (ConstMatrixViewXd secondValues, MatrixViewXd results) {
                    results -= secondValues;
                }
            );
        }
        
        void
        DifferenceExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(firstOperand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(secondOperand(), parameterID),
                resultID,
                [] (ConstIntervalMatrixViewXd secondValues, IntervalMatrixViewXd results) {
                    results -= secondValues;
                }
            );
        }

        void
        DifferenceExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(firstOperand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluateJacobian(secondOperand(), parameterID),
                resultID,
                [] (ConstMatrixViewXd secondJacobian, MatrixViewXd results) {
                    results -= secondJacobian;
                }
            );
        }
        
        void
        DifferenceExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(firstOperand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluateJacobian(secondOperand(), parameterID),
                resultID,
                [] (ConstIntervalMatrixViewXd secondJacobian, IntervalMatrixViewXd results) {
                    results -= secondJacobian;
                }
            );
        }

        ExpressionImplementationPtr
        DifferenceExpression::derivativeImpl(int parameterIndex) const {
            return (
                firstOperand()->derivative(parameterIndex) -
                secondOperand()->derivative(parameterIndex)
            );
        }

        bool
        DifferenceExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return duplicateOperands(other, false);
        }
        
        void
        DifferenceExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "DifferenceExpression" << std::endl;
            firstOperand()->debug(stream, indent + 1);
            secondOperand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        DifferenceExpression::withNewOperandsImpl(
            const ExpressionImplementationPtr& newFirstOperand,
            const ExpressionImplementationPtr& newSecondOperand
        ) const {
            return newFirstOperand - newSecondOperand;
        }

        DifferenceExpression::DifferenceExpression(
            const ExpressionImplementationPtr& firstOperand,
            const ExpressionImplementationPtr& secondOperand
        ) : BinaryOperation(firstOperand, secondOperand) {

            assert(firstOperand->numDimensions() == secondOperand->numDimensions());
        }
    }
}
