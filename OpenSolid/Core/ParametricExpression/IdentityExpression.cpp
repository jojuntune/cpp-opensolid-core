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

#include <OpenSolid/Core/ParametricExpression/IdentityExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    namespace detail
    {
        int
        IdentityExpression::numDimensionsImpl() const {
            return _numDimensions;
        }

        int
        IdentityExpression::numParametersImpl() const {
            return _numDimensions;
        }
        
        void
        IdentityExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                parameterID,
                resultID,
                [] (ConstMatrixViewXd parameterValues, MatrixViewXd results) {
                    results = parameterValues;
                }
            );
        }
        
        void
        IdentityExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                parameterID,
                resultID,
                [] (ConstIntervalMatrixViewXd parameterValues, IntervalMatrixViewXd results) {
                    results = parameterValues;
                }
            );
        }

        void
        IdentityExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                resultID,
                [] (MatrixViewXd results) {
                    results.setIdentity();
                }
            );
        }
        
        void
        IdentityExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                resultID,
                [] (IntervalMatrixViewXd results) {
                    results.setIdentity();
                }
            );
        }

        ExpressionImplementationPtr
        IdentityExpression::derivativeImpl(int parameterIndex) const {
            ColumnMatrixXd result(numDimensions());
            result(parameterIndex) = 1.0;
            return std::make_shared<ConstantExpression>(result, numDimensions());
        }

        bool
        IdentityExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            // ExpressionImplementation already checks that numbers of parameters/dimensions are equal
            return true;
        }

        ExpressionImplementationPtr
        IdentityExpression::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
            return self();
        }
        
        ExpressionImplementationPtr
        IdentityExpression::composedImpl(const ExpressionImplementationPtr& innerExpression) const {
            return innerExpression;
        }
        
        void
        IdentityExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "IdentityExpression" << std::endl;
        }

        IdentityExpression::IdentityExpression(int numDimensions) :
            _numDimensions(numDimensions) {

            assert(numDimensions > 0);
        }
    }
}
