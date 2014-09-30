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

#include <OpenSolid/Core/ParametricExpression/TangentExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    namespace detail
    {
        int
        TangentExpression::numDimensionsImpl() const {
            return 1;
        }
        
        void
        TangentExpression::evaluateImpl(
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
                            return opensolid::tan(value);
                        }
                    );
                }
            );
        }
        
        void
        TangentExpression::evaluateImpl(
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
                            return opensolid::tan(value);
                        }
                    );
                }
            );
        }

        void
        TangentExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(operand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                resultID,
                [] (ConstMatrixViewXd operandValues, MatrixViewXd results) {
                    double cosine = opensolid::cos(operandValues.value());
                    if (cosine == Zero()) {
                        throw Error(new PlaceholderError());
                    }
                    results *= (1.0 / (cosine * cosine));
                }
            );
        }
        
        void
        TangentExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluateJacobian(operand(), parameterID, resultID);
            expressionCompiler.compute(
                expressionCompiler.evaluate(operand(), parameterID),
                resultID,
                [] (ConstIntervalMatrixViewXd operandValues, IntervalMatrixViewXd results) {
                    Interval cosine = opensolid::cos(operandValues.value());
                    if (cosine == Zero()) {
                        throw Error(new PlaceholderError());
                    }
                    results *= (1.0 / cosine.squared());
                }
            );
        }

        ExpressionImplementationPtr
        TangentExpression::derivativeImpl(int parameterIndex) const {
            return operand()->derivative(parameterIndex) / cos(operand())->squaredNorm();
        }

        bool
        TangentExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return duplicateOperands(other);
        }
        
        void
        TangentExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "TangentExpression" << std::endl;
            operand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        TangentExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
            return tan(newOperand);
        }

        TangentExpression::TangentExpression(const ExpressionImplementationPtr& operand) :
            UnaryOperation(operand) {
            
            assert(operand->numDimensions() == 1);
        }
    }
}
