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

#include <OpenSolid/Core/ParametricExpression/ParameterExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    namespace detail
    {
        int
        ParameterExpression::numDimensionsImpl() const {
            return 1;
        }

        int
        ParameterExpression::numParametersImpl() const {
            return _numParameters;
        }
        
        void
        ParameterExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            int parameterIndex = this->parameterIndex();
            expressionCompiler.compute(
                parameterID,
                resultID,
                [parameterIndex] (
                    ConstMatrixViewXd parameterValues,
                    MatrixViewXd results
                ) {
                    results = parameterValues.row(parameterIndex);
                }
            );
        }
        
        void
        ParameterExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            int parameterIndex = this->parameterIndex();
            expressionCompiler.compute(
                parameterID,
                resultID,
                [parameterIndex] (
                    ConstIntervalMatrixViewXd parameterValues,
                    IntervalMatrixViewXd results
                ) {
                    results = parameterValues.row(parameterIndex);
                }
            );
        }

        void
        ParameterExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            int parameterIndex = this->parameterIndex();
            expressionCompiler.compute(
                resultID,
                [parameterIndex] (MatrixViewXd results) {
                    results.setZero();
                    results(0, parameterIndex) = 1.0;
                }
            );
        }
        
        void
        ParameterExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            int parameterIndex = this->parameterIndex();
            expressionCompiler.compute(
                resultID,
                [parameterIndex] (IntervalMatrixViewXd results) {
                    results.setZero();
                    results(0, parameterIndex) = Interval(1.0);
                }
            );
        }

        ExpressionImplementationPtr
        ParameterExpression::derivativeImpl(int parameterIndex) const {
            return new ConstantExpression(
                parameterIndex == this->parameterIndex() ? 1.0 : 0.0,
                numParameters()
            );
        }

        bool
        ParameterExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return this->parameterIndex() == other->cast<ParameterExpression>()->parameterIndex();
        }

        ExpressionImplementationPtr
        ParameterExpression::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
            return this;
        }
        
        ExpressionImplementationPtr
        ParameterExpression::composedImpl(
            const ExpressionImplementationPtr& innerExpression
        ) const {
            return innerExpression->component(parameterIndex());
        }
        
        void
        ParameterExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "ParameterExpression: parameter index = " << parameterIndex() << std::endl;
        }

        ParameterExpression::ParameterExpression(int numParameters, int parameterIndex) :
            _numParameters(numParameters),
            _parameterIndex(parameterIndex) {

            assert(numParameters > 0);
            assert(parameterIndex >= 0 && parameterIndex < numParameters);
        }
    }
}
