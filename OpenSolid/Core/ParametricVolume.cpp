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

#include <OpenSolid/Core/ParametricVolume.hpp>

namespace opensolid
{
    ParametricVolume3d::ParametricVolume3d() {
    }

    ParametricVolume3d::ParametricVolume3d(const ParametricVolume3d& other) :
        _expression(other.expression()),
        _domain(other.domain()),
        _bounds(other.bounds()) {
    }

    ParametricVolume3d::ParametricVolume3d(ParametricVolume3d&& other) :
        _expression(std::move(other.expression())),
        _domain(other.domain()),
        _bounds(other.bounds()) {
    }

    ParametricVolume3d::ParametricVolume3d(
        const ParametricExpression<3, 3>& expression,
        const BoundedVolume3d& domain
    ) : _expression(expression),
        _domain(domain),
        _bounds(expression.evaluate(domain.bounds().vector())) {
    }

    Point3d
    ParametricVolume3d::evaluate(double u, double v, double w) const {
        return Point3d(expression().evaluate(Vector3d(u, v, w)));
    }

    Box3d
    ParametricVolume3d::evaluate(Interval u, Interval v, Interval w) const {
        return Box3d(expression().evaluate(Vector3I(u, v, w)));
    }

    ParametricVolume3d
    ScalingFunction<ParametricVolume3d>::operator()(
        const ParametricVolume3d& parametricArea,
        double scale
    ) const {
        return ParametricVolume3d(scale * parametricArea.expression(), parametricArea.domain());
    }

    ParametricVolume3d
    TranslationFunction<ParametricVolume3d>::operator()(
        const ParametricVolume3d& parametricArea,
        const Vector3d& vector
    ) const {
        return ParametricVolume3d(parametricArea.expression() + vector, parametricArea.domain());
    }

    ParametricVolume3d
    TransformationFunction<ParametricVolume3d, 3>::operator()(
        const ParametricVolume3d& parametricArea,
        const Matrix3d& matrix
    ) const {
        return ParametricVolume3d(matrix * parametricArea.expression(), parametricArea.domain());
    }

    ParametricVolume3d
    MorphingFunction<ParametricVolume3d, 3>::operator()(
        const ParametricVolume3d& parametricArea,
        const ParametricExpression<3, 3>& morphingExpression
    ) const {
        return ParametricVolume3d(
            morphingExpression.composed(parametricArea.expression()),
            parametricArea.domain()
        );
    }
}
