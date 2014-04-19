/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluate(
            outerExpression(),
            evaluator.evaluate(innerExpression(), parameterView)
        );
    }

    void
    CompositionExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluate(
            outerExpression(),
            evaluator.evaluate(innerExpression(), parameterView)
        );
    }

    void
    CompositionExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        ConstMatrixViewXxX innerJacobian =
            evaluator.evaluateJacobian(innerExpression(), parameterView);
        ConstMatrixViewXxX innerValues =
            evaluator.evaluate(innerExpression(), parameterView);
        ConstMatrixViewXxX outerJacobian =
            evaluator.evaluateJacobian(outerExpression(), innerValues);
        resultView = outerJacobian * innerJacobian;
    }
    
    void
    CompositionExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        ConstIntervalMatrixViewXxX innerJacobian =
            evaluator.evaluateJacobian(innerExpression(), parameterView);
        ConstIntervalMatrixViewXxX innerBounds =
            evaluator.evaluate(innerExpression(), parameterView);
        ConstIntervalMatrixViewXxX outerJacobian =
            evaluator.evaluateJacobian(outerExpression(), innerBounds);
        resultView = outerJacobian * innerJacobian;
    }

    ExpressionImplementationPtr
    CompositionExpression::derivativeImpl(int parameterIndex) const {
        ExpressionImplementationPtr innerDerivative =
            innerExpression()->derivative(parameterIndex);

        ExpressionImplementationPtr result =
            outerExpression()->derivative(0)->composed(innerExpression()) *
            innerDerivative->component(0);

        for (int i = 1; i < outerExpression()->numParameters(); ++i) {
            result = result + outerExpression()->derivative(i)->composed(innerExpression()) *
                innerDerivative->component(i);
        }

        return result;
    }

    bool
    CompositionExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        ExpressionImplementationPtr otherOuterExpression =
            other->cast<CompositionExpression>()->outerExpression();
        ExpressionImplementationPtr otherInnerExpression =
            other->cast<CompositionExpression>()->innerExpression();

        return outerExpression()->isDuplicateOf(otherOuterExpression) &&
            innerExpression()->isDuplicateOf(otherInnerExpression);
    }

    ExpressionImplementationPtr
    CompositionExpression::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        ExpressionImplementationPtr deduplicatedOuterExpression =
            outerExpression()->deduplicated(deduplicationCache);
        ExpressionImplementationPtr deduplicatedInnerExpression =
            innerExpression()->deduplicated(deduplicationCache);
        return new CompositionExpression(deduplicatedOuterExpression, deduplicatedInnerExpression);
    }
        
    ExpressionImplementationPtr
    CompositionExpression::composedImpl(const ExpressionImplementationPtr& innerExpression) const {
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
