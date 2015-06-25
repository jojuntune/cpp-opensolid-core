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
        const ParametricExpression<Point3d, Point3d>& expression,
        const BoundedVolume3d& domain
    ) : _expression(expression),
        _domain(domain),
        _bounds(expression.evaluate(domain.bounds())) {
    }

    Point3d
    ParametricVolume3d::evaluate(const Point3d& parameterValues) const {
        return expression().evaluate(parameterValues);
    }

    Box3d
    ParametricVolume3d::evaluate(const Box3d& parameterBounds) const {
        return expression().evaluate(parameterBounds);
    }

    ParametricVolume3d
    ParametricVolume3d::scaledAbout(const Point3d& point, double scale) const {
        return ParametricVolume3d(expression().scaledAbout(point, scale), domain());
    }

    ParametricVolume3d
    ParametricVolume3d::rotatedAbout(const Point3d& point, const Matrix3d& rotationMatrix) const {
        return ParametricVolume3d(expression().rotatedAbout(point, rotationMatrix), domain());
    }

    ParametricVolume3d
    ParametricVolume3d::translatedBy(const Vector3d& vector) const {
        return ParametricVolume3d(expression().translatedBy(vector), domain());
    }

    ParametricVolume3d
    ParametricVolume3d::toLocalIn(const Frame3d& frame) const {
        return ParametricVolume3d(expression().toLocalIn(frame), domain());
    }

    ParametricVolume3d
    ParametricVolume3d::toGlobalFrom(const Frame3d& frame) const {
        return ParametricVolume3d(expression().toGlobalFrom(frame), domain());
    }

    ParametricVolume3d
    ParametricVolume3d::mirroredAbout(
        const Point3d& point,
        const UnitVector3d& mirrorDirection
    ) const {
        return ParametricVolume3d(expression().mirroredAbout(point, mirrorDirection), domain());
    }
}
