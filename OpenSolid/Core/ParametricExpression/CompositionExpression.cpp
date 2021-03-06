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

#include <OpenSolid/Core/ParametricExpression/CompositionExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    namespace detail
    {
        int
        CompositionExpression::numDimensionsImpl() const {
            return outerExpression()->numDimensions();
        }
        
        int
        CompositionExpression::numParametersImpl() const {
            return innerExpression()->numParameters();
        }

        void
        CompositionExpression::evaluateImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(
                outerExpression(),
                expressionCompiler.evaluate(innerExpression(), parameterID),
                resultID
            );
        }

        void
        CompositionExpression::evaluateImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.evaluate(
                outerExpression(),
                expressionCompiler.evaluate(innerExpression(), parameterID),
                resultID
            );
        }

        void
        CompositionExpression::evaluateJacobianImpl(
            const MatrixID<const double>& parameterID,
            const MatrixID<double>& resultID,
            ExpressionCompiler<double>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                expressionCompiler.evaluateJacobian(innerExpression(), parameterID),
                expressionCompiler.evaluateJacobian(
                    outerExpression(),
                    expressionCompiler.evaluate(innerExpression(), parameterID)
                ),
                resultID,
                [] (
                    ConstMatrixViewXd innerJacobian,
                    ConstMatrixViewXd outerJacobian,
                    MatrixViewXd results
                ) {
                    results.setProduct(outerJacobian, innerJacobian);
                }
            );
        }
        
        void
        CompositionExpression::evaluateJacobianImpl(
            const MatrixID<const Interval>& parameterID,
            const MatrixID<Interval>& resultID,
            ExpressionCompiler<Interval>& expressionCompiler
        ) const {
            expressionCompiler.compute(
                expressionCompiler.evaluateJacobian(innerExpression(), parameterID),
                expressionCompiler.evaluateJacobian(
                    outerExpression(),
                    expressionCompiler.evaluate(innerExpression(), parameterID)
                ),
                resultID,
                [] (
                    ConstIntervalMatrixViewXd innerJacobian,
                    ConstIntervalMatrixViewXd outerJacobian,
                    IntervalMatrixViewXd results
                ) {
                    results.setProduct(outerJacobian, innerJacobian);
                }
            );
        }

        ExpressionImplementationPtr
        CompositionExpression::derivativeImpl(int parameterIndex) const {
            ExpressionImplementationPtr innerDerivative =
                innerExpression()->derivative(parameterIndex);

            ExpressionImplementationPtr result =
                outerExpression()->derivative(0)->composed(innerExpression()) *
                innerDerivative->component(0);

            for (int innerIndex = 1; innerIndex < outerExpression()->numParameters(); ++innerIndex)
            {
                result = (
                    result +
                    outerExpression()->derivative(innerIndex)->composed(innerExpression()) *
                    innerDerivative->component(innerIndex)
                );
            }

            return result;
        }

        bool
        CompositionExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            ExpressionImplementationPtr otherOuterExpression = (
                other->cast<CompositionExpression>()->outerExpression()
            );
            ExpressionImplementationPtr otherInnerExpression = (
                other->cast<CompositionExpression>()->innerExpression()
            );
            return (
                outerExpression()->isDuplicateOf(otherOuterExpression) &&
                innerExpression()->isDuplicateOf(otherInnerExpression)
            );
        }

        ExpressionImplementationPtr
        CompositionExpression::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
            ExpressionImplementationPtr deduplicatedOuterExpression = (
                outerExpression()->deduplicated(deduplicationCache)
            );
            ExpressionImplementationPtr deduplicatedInnerExpression = (
                innerExpression()->deduplicated(deduplicationCache)
            );
            return std::make_shared<CompositionExpression>(
                deduplicatedOuterExpression,
                deduplicatedInnerExpression
            );
        }
            
        ExpressionImplementationPtr
        CompositionExpression::composedImpl(
            const ExpressionImplementationPtr& innerExpression
        ) const {
            return outerExpression()->composed(this->innerExpression()->composed(innerExpression));
        }
        
        void
        CompositionExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "CompositionExpression" << std::endl;
            outerExpression()->debug(stream, indent + 1);
            innerExpression()->debug(stream, indent + 1);
        }

        CompositionExpression::CompositionExpression(
            const ExpressionImplementationPtr& outerExpression,
            const ExpressionImplementationPtr& innerExpression
        ) : _outerExpression(outerExpression),
            _innerExpression(innerExpression) {

            assert(outerExpression->numParameters() == innerExpression->numDimensions());
        }
    }
}
