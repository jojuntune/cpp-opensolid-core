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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.definitions.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/MatrixView.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/Evaluator.hpp>
#include <OpenSolid/Core/ParametricExpression/IdentityExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ParameterExpression.hpp>

namespace opensolid
{
    inline
    ExpressionImplementationPtr
    ExpressionImplementation::self() const {
        return this;
    }

    inline
    bool
    ExpressionImplementation::isConstantExpression() const {
        return typeid(*this) == typeid(ConstantExpression);
    }
    
    inline
    bool
    ExpressionImplementation::isIdentityExpression() const {
        return typeid(*this) == typeid(IdentityExpression);
    }
    
    inline
    bool
    ExpressionImplementation::isParameterExpression() const {
        return typeid(*this) == typeid(ParameterExpression);
    }
    
    template <class TExpressionImplementation>
    const TExpressionImplementation*
    ExpressionImplementation::cast() const {
        assert(dynamic_cast<const TExpressionImplementation*>(this));
        return static_cast<const TExpressionImplementation*>(this);
    }

    inline
    int
    ExpressionImplementation::numDimensions() const {
        return numDimensionsImpl();
    }
    
    inline
    int
    ExpressionImplementation::numParameters() const {
        return numParametersImpl();
    }
    
    inline
    void
    ExpressionImplementation::evaluate(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        evaluateImpl(parameterView, resultView, evaluator);
    }
    
    inline
    void
    ExpressionImplementation::evaluate(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        evaluateImpl(parameterView, resultView, evaluator);
    }
    
    inline
    void
    ExpressionImplementation::evaluateJacobian(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        evaluateJacobianImpl(parameterView, resultView, evaluator);
    }

    inline
    void
    ExpressionImplementation::evaluateJacobian(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        evaluateJacobianImpl(parameterView, resultView, evaluator);
    }
}
