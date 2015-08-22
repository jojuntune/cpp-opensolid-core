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

#include <OpenSolid/Core/Axis.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Parameter.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>

namespace opensolid
{
    Axis2d
    Axis2d::projectedOnto(const Axis2d& other) const {
        double dotProduct = directionVector().dot(other.directionVector());
        if (dotProduct == Zero()) {
            throw Error(new PlaceholderError());
        }
        return Axis2d(
            originPoint().projectedOnto(other),
            dotProduct > 0.0 ? other.directionVector() : -other.directionVector()
        );
    }

    ParametricExpression<Point2d, double>
    Axis2d::expression() const {
        return originPoint() + Parameter1d() * directionVector();
    }

    Axis2d
    Axis3d::toLocalIn(const Plane3d& plane) const {
        Vector2d localDirection = directionVector().toLocalIn(plane);
        if (localDirection.isZero()) {
            throw Error(new PlaceholderError());
        }
        return Axis2d(originPoint().toLocalIn(plane), localDirection.normalized());
    }

    Axis3d
    Axis3d::projectedOnto(const Plane3d& plane) const {
        Vector3d projectedDirection = directionVector().projectedOnto(plane);
        if (projectedDirection.isZero()) {
            throw Error(new PlaceholderError());
        }
        return Axis3d(originPoint().projectedOnto(plane), projectedDirection.normalized());
    }

    ParametricExpression<Point3d, double>
    Axis3d::expression() const {
        return originPoint() + Parameter1d() * directionVector();
    }
}
