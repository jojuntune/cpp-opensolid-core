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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ParametricArea.hpp>

namespace opensolid
{
    ParametricArea2d::ParametricArea2d() {
    }

    ParametricArea2d::ParametricArea2d(const ParametricArea2d& other) :
        _expression(other.expression()),
        _domain(other.domain()),
        _bounds(other.bounds()) {
    }

    ParametricArea2d::ParametricArea2d(ParametricArea2d&& other) :
        _expression(std::move(other.expression())),
        _domain(other.domain()),
        _bounds(other.bounds()) {
    }

    ParametricArea2d::ParametricArea2d(
        const ParametricExpression<2, 2>& expression,
        const BoundedArea2d& domain
    ) : _expression(expression),
        _domain(domain),
        _bounds(expression.evaluateBounds(domain.bounds().vector())) {
    }

    Point2d
    ParametricArea2d::evaluate(double u, double v) const {
        return Point2d(expression().evaluate(Vector2d(u, v)));
    }

    Box2d
    ParametricArea2d::evaluateBounds(Interval u, Interval v) const {
        return Box2d(expression().evaluateBounds(Vector2I(u, v)));
    }

    ParametricArea2d
    ScalingFunction<ParametricArea2d>::operator()(
        const ParametricArea2d& parametricArea,
        double scale
    ) const {
        return ParametricArea2d(scale * parametricArea.expression(), parametricArea.domain());
    }

    ParametricArea2d
    TranslationFunction<ParametricArea2d>::operator()(
        const ParametricArea2d& parametricArea,
        const Vector2d& vector
    ) const {
        return ParametricArea2d(parametricArea.expression() + vector, parametricArea.domain());
    }

    ParametricArea2d
    TransformationFunction<ParametricArea2d, 2>::operator()(
        const ParametricArea2d& parametricArea,
        const Matrix2d& matrix
    ) const {
        return ParametricArea2d(matrix * parametricArea.expression(), parametricArea.domain());
    }

    ParametricArea2d
    MorphingFunction<ParametricArea2d, 2>::operator()(
        const ParametricArea2d& parametricArea,
        const ParametricExpression<2, 2>& morphingExpression
    ) const {
        return ParametricArea2d(
            morphingExpression.composed(parametricArea.expression()),
            parametricArea.domain()
        );
    }
}
