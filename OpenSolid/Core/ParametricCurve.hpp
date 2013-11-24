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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ParametricCurve.definitions.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    inline
    ParametricCurve<iNumDimensions>::ParametricCurve() {
    }

    template <int iNumDimensions>
    inline
    ParametricCurve<iNumDimensions>::ParametricCurve(const ParametricCurve<iNumDimensions>& other) :
        _expression(other.expression()),
        _domain(other.domain()),
        _bounds(other.bounds()) {
    }

    template <int iNumDimensions>
    inline
    ParametricCurve<iNumDimensions>::ParametricCurve(ParametricCurve<iNumDimensions>&& other) :
        _expression(std::move(other._expression)),
        _domain(other.domain()),
        _bounds(other.bounds()) {
    }

    template <int iNumDimensions>
    inline
    ParametricCurve<iNumDimensions>::ParametricCurve(
        const ParametricExpression<iNumDimensions, 1>& expression,
        Interval domain
    ) : _expression(expression),
        _domain(domain),
        _bounds(expression.evaluate(domain)) {
    }

    template <int iNumDimensions>
    inline
    const ParametricExpression<iNumDimensions, 1>&
    ParametricCurve<iNumDimensions>::expression() const {
        return _expression;
    }

    template <int iNumDimensions>
    inline
    Interval
    ParametricCurve<iNumDimensions>::domain() const {
        return _domain;
    }

    template <int iNumDimensions>
    const Box<iNumDimensions>&
    ParametricCurve<iNumDimensions>::bounds() const {
        return _bounds;
    }

    template <int iNumDimensions>
    Point<iNumDimensions>
    ParametricCurve<iNumDimensions>::evaluate(double parameterValue) const {
        return Point<iNumDimensions>(expression().evaluate(parameterValue));
    }

    template <int iNumDimensions>
    Box<iNumDimensions>
    ParametricCurve<iNumDimensions>::evaluate(Interval parameterBounds) const {
        return Box<iNumDimensions>(expression().evaluate(parameterBounds));
    }

    template <int iNumDimensions>
    ParametricExpression<iNumDimensions, 1>
    ParametricCurve<iNumDimensions>::tangentVector() const {
        return expression().tangentVector();
    }

    template <int iNumDimensions>
    ParametricExpression<iNumDimensions, 1>
    ParametricCurve<iNumDimensions>::normalVector() const {
        return expression().normalVector();
    }

    template <int iNumDimensions>
    ParametricExpression<iNumDimensions, 1>
    ParametricCurve<iNumDimensions>::binormalVector() const {
        return expression().binormalVector();
    }

    template <int iNumDimensions>
    ParametricExpression<1, 1>
    ParametricCurve<iNumDimensions>::curvature() const {
        return expression().curvature();
    }

    template <int iNumDimensions>
    ParametricCurve<iNumDimensions>
    ParametricCurve<iNumDimensions>::reversed() const {
        ParametricExpression<1, 1> reversedParameter =
            domain().upperBound() + domain().lowerBound() - ParametricExpression<1, 1>::t();
        return ParametricCurve<iNumDimensions>(expression().composed(reversedParameter), domain());
    }

    template <int iNumDimensions>
    Point<iNumDimensions>
    ParametricCurve<iNumDimensions>::startPoint() const {
        return evaluate(domain().lowerBound());
    }

    template <int iNumDimensions>
    Point<iNumDimensions>
    ParametricCurve<iNumDimensions>::endPoint() const {
        return evaluate(domain().upperBound());
    }

    template <int iNumDimensions>
    ParametricCurve<iNumDimensions>
    ScalingFunction<ParametricCurve<iNumDimensions>>::operator()(
        const ParametricCurve<iNumDimensions>& curve,
        double scale
    ) const {
        return ParametricCurve<iNumDimensions>(scale * curve.expression(), curve.domain());
    }

    template <int iNumDimensions> template <class TVector>
    ParametricCurve<iNumDimensions>
    TranslationFunction<ParametricCurve<iNumDimensions>>::operator()(
        const ParametricCurve<iNumDimensions>& curve,
        const EigenBase<TVector>& vector
    ) const {
        return ParametricCurve<iNumDimensions>(
            curve.expression() + vector.derived(),
            curve.domain()
        );
    }

    template <int iNumDimensions, int iNumResultDimensions> template <class TMatrix>
    ParametricCurve<iNumResultDimensions>
    TransformationFunction<ParametricCurve<iNumDimensions>, iNumResultDimensions>::operator()(
        const ParametricCurve<iNumDimensions>& curve,
        const EigenBase<TMatrix>& matrix
    ) const {
        return ParametricCurve<iNumResultDimensions>(
            matrix.derived() * curve.expression(),
            curve.domain()
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    ParametricCurve<iNumResultDimensions>
    MorphingFunction<ParametricCurve<iNumDimensions>, iNumResultDimensions>::operator()(
        const ParametricCurve<iNumDimensions>& curve,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return ParametricCurve<iNumResultDimensions>(
            morphingExpression.composed(curve.expression()),
            curve.domain()
        );
    }
}
