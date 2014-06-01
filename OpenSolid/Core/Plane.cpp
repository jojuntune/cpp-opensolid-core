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

#include <OpenSolid/Core/Plane.hpp>

#include <OpenSolid/Core/ParametricExpression.hpp>

namespace opensolid
{
    Plane3d::Plane3d() {
    }

    Plane3d::Plane3d(const Point3d& originPoint, const UnitVector3d& normalVector) :
        _originPoint(originPoint),
        _normalVector(normalVector) {
    }

    Plane3d
    Plane3d::throughPoints(
        const Point3d& firstPoint,
        const Point3d& secondPoint,
        const Point3d& thirdPoint
    ) {
        return Plane3d(
            firstPoint,
            (secondPoint - firstPoint).cross(thirdPoint - firstPoint).normalized()
        );
    }

    Plane3d
    Plane3d::midplane(const Point3d& pointBelow, const Point3d& pointAbove) {
        Vector3d displacementVector = pointAbove - pointBelow;
        return Plane3d(pointBelow + 0.5 * displacementVector, displacementVector.normalized());
    }

    Plane3d
    Plane3d::midplane(const Plane3d& planeBelow, const Plane3d& planeAbove) {
        UnitVector3d belowNormalVector = planeBelow.normalVector();
        UnitVector3d aboveNormalVector = planeAbove.normalVector();

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
        UnitVector3d normalVector = UnitVector3d(
            belowNormalVector + 0.5 * (aboveNormalVector - belowNormalVector)
        );
        return Plane3d(originPoint, normalVector);
    }

    Plane3d
    Plane3d::throughAxisAndPoint(const Axis3d& axis, const Point3d& point) {
        Vector3d normalVector = (point - axis.originPoint()).cross(axis.directionVector());
        if (normalVector.isZero()) {
            // Point is on axis
            throw Error(new PlaceholderError());
        }
        return Plane3d(axis.originPoint(), normalVector.normalized());
    }

    Plane3d
    Plane3d::throughAxis(const Axis3d& axis) {
        return Plane3d(axis.originPoint(), axis.directionVector().unitOrthogonal());
    }

    Plane3d
    Plane3d::xy() {
        return Plane3d(Point3d::Origin(), UnitVector3d::k());
    }

    Plane3d
    Plane3d::xz() {
        return Plane3d(Point3d::Origin(), -UnitVector3d::j());
    }
    
    Plane3d
    Plane3d::yx() {
        return Plane3d(Point3d::Origin(), -UnitVector3d::k());
    }

    Plane3d
    Plane3d::yz() {
        return Plane3d(Point3d::Origin(), UnitVector3d::i());
    }

    Plane3d
    Plane3d::zx() {
        return Plane3d(Point3d::Origin(), UnitVector3d::j());
    }
    
    Plane3d
    Plane3d::zy() {
        return Plane3d(Point3d::Origin(), -UnitVector3d::i());
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
    TransformationFunction<Plane3d, 3>::operator()(
        const Plane3d& plane,
        const Matrix3d& matrix
    ) const {
        if (matrix.determinant() == Zero()) {
            assert(false);
            return Plane3d();
        }
        Matrix3d normalTransformationMatrix = matrix.inverse().transpose();
        Vector3d transformedNormal = transformationFunction(
            plane.normalVector(),
            normalTransformationMatrix
        );
        double transformedNorm = transformedNormal.norm();
        if (transformedNorm == Zero()) {
            assert(false);
            return Plane3d();
        }
        transformedNormal *= (1.0 / transformedNorm);
        return Plane3d(
            transformationFunction(plane.originPoint(), matrix),
            UnitVector3d(transformedNormal)
        );
    }

    Plane3d
    MorphingFunction<Plane3d, 3>::operator()(
        const Plane3d& plane,
        const ParametricExpression<3, 3>& morphingExpression
    ) const {
        Vector3d morphedNormal = transformationFunction(
            plane.normalVector(),
            morphingExpression.jacobian(plane.originPoint().components())
        );
        double morphedNorm = morphedNormal.norm();
        if (morphedNorm == Zero()) {
            throw PlaceholderError();
        }
        morphedNormal *= (1.0 / morphedNorm);
        return Plane3d(
            morphingFunction(plane.originPoint(), morphingExpression),
            UnitVector3d(morphedNormal)
        );
    }
}
