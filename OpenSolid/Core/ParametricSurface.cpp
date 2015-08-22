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
    ParametricSurface3d::ParametricSurface3d() :
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    ParametricSurface3d::ParametricSurface3d(const ParametricSurface3d& other) :
        _expression(other.expression()),
        _domain(other.domain()),
        _handedness(other.handedness()),
        _bounds(other.bounds()) {
    }

    ParametricSurface3d::ParametricSurface3d(ParametricSurface3d&& other) :
        _expression(std::move(other.expression())),
        _domain(other.domain()),
        _handedness(other.handedness()),
        _bounds(other.bounds()) {
    }

    ParametricSurface3d::ParametricSurface3d(
        const ParametricExpression<Point3d, Point2d>& expression,
        const BoundedArea2d& domain
    ) : _expression(expression),
        _domain(domain),
        _handedness(Handedness::RIGHT_HANDED()),
        _bounds(expression.evaluate(domain.bounds())) {
    }

    ParametricSurface3d::ParametricSurface3d(
        const ParametricExpression<Point3d, Point2d>& expression,
        const BoundedArea2d& domain,
        Handedness handedness
    ) : _expression(expression),
        _domain(domain),
        _handedness(handedness),
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

    ParametricExpression<UnitVector3d, Point2d>
    ParametricSurface3d::normalVector() const {
        return (
            handedness().sign() *
            expression().derivative(0).cross(expression().derivative(1)).normalized()
        );
    }

    ParametricArea2d
    ParametricSurface3d::projectedInto(const Plane3d& plane) const {
        return ParametricArea2d(expression().projectedInto(plane), domain(), handedness());
    }

    ParametricSurface3d
    ParametricSurface3d::projectedOnto(const Plane3d& plane) const {
        return ParametricSurface3d(expression().projectedOnto(plane), domain(), handedness());
    }
}
