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
        const ParametricExpression<Point2d, Point2d>& expression,
        const BoundedArea2d& domain
    ) : _expression(expression),
        _domain(domain),
        _bounds(expression.evaluate(domain.bounds())) {
    }

    Point2d
    ParametricArea2d::evaluate(const Point2d& parameterValues) const {
        return expression().evaluate(parameterValues);
    }

    Box2d
    ParametricArea2d::evaluate(const Box2d& parameterBounds) const {
        return expression().evaluate(parameterBounds);
    }

    ParametricArea2d
    ParametricArea2d::scaledAbout(const Point2d& point, double scale) const {
        return ParametricArea2d(expression().scaledAbout(point, scale), domain());
    }

    ParametricArea2d
    ParametricArea2d::rotatedAbout(const Point2d& point, const Matrix2d& rotationMatrix) const {
        return ParametricArea2d(expression().rotatedAbout(point, rotationMatrix), domain());
    }

    ParametricArea2d
    ParametricArea2d::translatedBy(const Vector2d& vector) const {
        return ParametricArea2d(expression().translatedBy(vector), domain());
    }

    ParametricArea2d
    ParametricArea2d::toLocalIn(const Frame2d& frame) const {
        return ParametricArea2d(expression().toLocalIn(frame), domain());
    }

    ParametricArea2d
    ParametricArea2d::toGlobalFrom(const Frame2d& frame) const {
        return ParametricArea2d(expression().toGlobalFrom(frame), domain());
    }

    ParametricSurface3d
    ParametricArea2d::toGlobalFrom(const Plane3d& plane) const {
        return ParametricSurface3d(expression().toGlobalFrom(plane), domain());
    }

    ParametricArea2d
    ParametricArea2d::mirroredAbout(
        const Point2d& point,
        const UnitVector2d& mirrorDirection
    ) const {
        return ParametricArea2d(expression().mirroredAbout(point, mirrorDirection), domain());
    }
}
