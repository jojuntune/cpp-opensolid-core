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

#include <OpenSolid/Core/Plane.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Point.hpp>

namespace opensolid
{
    Plane3d::Plane3d() :
        _originPoint(Point3d::Origin()),
        _normalVector(Vector3d::Zero()) {
    }

    Plane3d::Plane3d(const Point<3>& originPoint, const Vector3d& normalVector) :
        _originPoint(originPoint) {
    
        if (normalVector.isZero()) {
            throw Error(new PlaceholderError());
        }
        double squaredNorm = normalVector.squaredNorm();
        if (squaredNorm - 1 == Zero()) {
            _normalVector = normalVector;
        } else {
            _normalVector = normalVector / sqrt(squaredNorm);
        }
    }

    Plane3d
    Plane3d::ThroughPoints(
        const Point<3>& firstPoint,
        const Point<3>& secondPoint,
        const Point<3>& thirdPoint
    ) {
        Vector3d normalVector = (secondPoint - firstPoint).cross(thirdPoint - firstPoint);
        return Plane3d(firstPoint, normalVector);
    }

    Plane3d
    Plane3d::Midplane(const Point<3>& pointBelow, const Point<3>& pointAbove) {
        Vector3d displacementVector = pointAbove - pointBelow;
        return Plane3d(pointBelow + 0.5 * displacementVector, displacementVector);
    }

    Plane3d
    Plane3d::Midplane(const Plane3d planeBelow, const Plane3d planeAbove) {
        Vector3d belowNormalVector = planeBelow.normalVector();
        Vector3d aboveNormalVector = planeAbove.normalVector();

        if (!belowNormalVector.cross(aboveNormalVector).isZero()) {
            // Planes are not parallel
            throw Error(new PlaceholderError());
        }

        Vector3d displacementVector = planeAbove.originPoint() - planeBelow.originPoint();
        double belowDotProduct = belowNormalVector.dot(displacementVector);
        double aboveDotProduct = aboveNormalVector.dot(displacementVector);

        if (belowDotProduct == Zero()) {
            // Planes are coplanar; flip above normal vector direction if necessary to match below
            if (aboveNormalVector.dot(belowNormalVector) < 0.0) {
                aboveNormalVector = -aboveNormalVector;
            }
        } else {
            // Flip both normal vectors if necessary to match displacement between planes
            if (belowDotProduct < 0.0) {
                belowNormalVector = -belowNormalVector;
            }
            if (aboveDotProduct < 0.0) {
                aboveNormalVector = -aboveNormalVector;
            }
        }

        Point3d originPoint = planeBelow.originPoint() + 0.5 * displacementVector;
        Vector3d normalVector = belowNormalVector + 0.5 * (aboveNormalVector - belowNormalVector);
        return Plane3d(originPoint, normalVector);
    }

    Plane3d
    Plane3d::ThroughAxisAndPoint(const Axis<3>& axis, const Point<3>& point) {
        Vector3d normalVector = (point - axis.originPoint()).cross(axis.directionVector());
        if (normalVector.isZero()) {
            // Point is on axis
            throw Error(new PlaceholderError());
        }
        return Plane3d(axis.originPoint(), normalVector);
    }

    Plane3d
    Plane3d::ThroughAxis(const Axis<3>& axis) {
        return Plane3d(axis.originPoint(), axis.directionVector().unitOrthogonal());
    }

    Plane3d
    Plane3d::XY() {
        return Plane3d(Point3d::Origin(), Vector3d::UnitZ());
    }

    Plane3d
    Plane3d::XZ() {
        return Plane3d(Point3d::Origin(), -Vector3d::UnitY());
    }
    
    Plane3d
    Plane3d::YX() {
        return Plane3d(Point3d::Origin(), -Vector3d::UnitZ());
    }

    Plane3d
    Plane3d::YZ() {
        return Plane3d(Point3d::Origin(), Vector3d::UnitX());
    }

    Plane3d
    Plane3d::ZX() {
        return Plane3d(Point3d::Origin(), Vector3d::UnitY());
    }
    
    Plane3d
    Plane3d::ZY() {
        return Plane3d(Point3d::Origin(), -Vector3d::UnitX());
    }
    
    Plane3d
    Plane3d::offsetBy(double distance) const {
        return Plane3d(originPoint() + distance * normalVector(), normalVector());
    }

    Plane3d
    Plane3d::flipped() const {
        return Plane3d(originPoint(), -normalVector());
    }

    Axis<3>
    Plane3d::normalAxis() const {
        return Axis3d(originPoint(), normalVector());
    }

    PlanarCoordinateSystem3d
    Plane3d::coordinateSystem() const {
        Vector3d xVector = normalVector().unitOrthogonal();
        Vector3d yVector = normalVector().cross(xVector);
        return PlanarCoordinateSystem3d(originPoint(), xVector, yVector);
    }

    Plane3d
    ScalingFunction<Plane3d>::operator()(const Plane3d& plane, double scale) const {
        return Plane3d(detail::scaled(plane.originPoint(), scale), plane.normalVector());
    }

    Plane3d
    MorphingFunction<Plane3d, 3>::operator()(
        const Plane3d& plane,
        const ParametricExpression<3, 3>& morphingExpression
    ) const {
        return Plane3d(
            plane.originPoint().morphedBy(morphingExpression),
            morphingExpression.jacobian(plane.originPoint().vector()) * plane.normalVector()
        );
    }
}
