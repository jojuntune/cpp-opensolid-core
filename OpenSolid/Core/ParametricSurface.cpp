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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/ParametricSurface.hpp>

namespace opensolid
{
    ParametricSurface3d::ParametricSurface3d() {
    }

    ParametricSurface3d::ParametricSurface3d(const ParametricSurface3d& other) :
        _expression(other.expression()),
        _domain(other.domain()),
        _bounds(other.bounds()) {
    }

    ParametricSurface3d::ParametricSurface3d(ParametricSurface3d&& other) :
        _expression(std::move(other.expression())),
        _domain(other.domain()),
        _bounds(other.bounds()) {
    }

    ParametricSurface3d::ParametricSurface3d(
        const ParametricExpression<Point3d, Point2d>& expression,
        const BoundedArea2d& domain
    ) : _expression(expression),
        _domain(domain),
        _bounds(expression.evaluate(domain.bounds())) {
    }

    Point3d
    ParametricSurface3d::evaluate(const Point2d& parameterValues) const {
        return expression().evaluate(parameterValues);
    }

    Box3d
    ParametricSurface3d::evaluate(const Box2d& parameterBounds) const {
        return expression().evaluate(parameterBounds);
    }

    ParametricExpression<Vector3d, Point2d>
    ParametricSurface3d::normalVector() const {
        return expression().derivative(0).cross(expression().derivative(1)).normalized();
    }

    ParametricSurface3d
    ScalingFunction<ParametricSurface3d>::operator()(
        const ParametricSurface3d& surface,
        const Point3d& originPoint,
        double scale
    ) const {
        return ParametricSurface3d(
            scaled(surface.expression(), originPoint, scale),
            surface.domain()
        );
    }

    ParametricSurface3d
    TranslationFunction<ParametricSurface3d>::operator()(
        const ParametricSurface3d& surface,
        const Vector3d& vector
    ) const {
        return ParametricSurface3d(surface.expression() + vector, surface.domain());
    }

    ParametricSurface3d
    TransformationFunction<ParametricSurface3d, 3>::operator()(
        const ParametricSurface3d& surface,
        const Point3d& originPoint,
        const Matrix3d& transformationMatrix,
        const Point3d& destinationPoint
    ) const {
        return ParametricSurface3d(
            transformed(surface.expression(), originPoint, transformationMatrix, destinationPoint),
            surface.domain()
        );
    }

    ParametricSurface3d
    MorphingFunction<ParametricSurface3d, ParametricExpression<Point3d, Point3d>>::operator()(
        const ParametricSurface3d& surface,
        const ParametricExpression<Point3d, Point3d>& morphingExpression
    ) const {
        return ParametricSurface3d(
            morphingExpression.composed(surface.expression()),
            surface.domain()
        );
    }
}
