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

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Parameter.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>

namespace opensolid
{
    Plane3d::Plane3d() :
        _handedness(Handedness::rightHanded()) {
    }

    Plane3d::Plane3d(
        const Point3d& originPoint,
        const UnitVector3d& xDirectionVector,
        const UnitVector3d& yDirectionVector
    ) : FrameBase<3, 2>(
            originPoint,
            Matrix<double, 3, 2>::fromColumns(
                xDirectionVector.components(),
                yDirectionVector.components()
            )
        ),
        _normalVector(xDirectionVector.cross(yDirectionVector).components()),
        _handedness(Handedness::rightHanded()) {

        assert(xDirectionVector.dot(yDirectionVector) == Zero());
    }

    Plane3d::Plane3d(
        const Point3d& originPoint,
        const UnitVector3d& xDirectionVector,
        const UnitVector3d& yDirectionVector,
        const UnitVector3d& normalVector,
        Handedness handedness
    ) : FrameBase<3, 2>(
            originPoint,
            Matrix<double, 3, 2>::fromColumns(
                xDirectionVector.components(),
                yDirectionVector.components()
            )
        ),
        _normalVector(normalVector),
        _handedness(handedness) {

        assert(xDirectionVector.dot(yDirectionVector) == Zero());
        assert(
            xDirectionVector.cross(yDirectionVector).dot(normalVector) - handedness.sign() == Zero()
        );
    }

    namespace
    {
        inline
        Matrix<double, 3, 2>
        normalBasisMatrix(const UnitVector3d& normalVector) {
            UnitVector3d xDirectionVector = normalVector.unitOrthogonal();
            return Matrix<double, 3, 2>::fromColumns(
                xDirectionVector.components(),
                (normalVector.cross(xDirectionVector).components())
            );
        }
    }

    Plane3d::Plane3d(const Point3d& originPoint, const UnitVector3d& normalVector) :
        FrameBase<3, 2>(originPoint, normalBasisMatrix(normalVector)),
        _normalVector(normalVector),
        _handedness(Handedness::rightHanded()) {
    }

    Plane3d
    Plane3d::throughPoints(
        const Point3d& firstPoint,
        const Point3d& secondPoint,
        const Point3d& thirdPoint
    ) {
        Vector3d firstLeg = secondPoint - firstPoint;
        Vector3d secondLeg = thirdPoint - firstPoint;
        UnitVector3d xDirectionVector = firstLeg.normalized();
        UnitVector3d normalVector = firstLeg.cross(secondLeg).normalized();
        UnitVector3d yDirectionVector(normalVector.cross(xDirectionVector).components());
        return Plane3d(firstPoint, xDirectionVector, yDirectionVector, normalVector);
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
            (belowNormalVector + 0.5 * (aboveNormalVector - belowNormalVector)).components()
        );
        return Plane3d(originPoint, normalVector);
    }

    Plane3d
    Plane3d::throughAxisAndPoint(const Axis3d& axis, const Point3d& point) {
        Vector3d crossProduct = (point - axis.originPoint()).cross(axis.directionVector());
        if (crossProduct.isZero()) {
            // Point is on axis
            throw Error(new PlaceholderError());
        }
        UnitVector3d normalVector = crossProduct.normalized();
        return Plane3d(
            axis.originPoint(),
            axis.directionVector(),
            UnitVector3d(normalVector.cross(axis.directionVector()).components()),
            normalVector
        );
    }

    Plane3d
    Plane3d::throughAxis(const Axis3d& axis) {
        UnitVector3d normalVector = axis.directionVector().unitOrthogonal();
        return Plane3d(
            axis.originPoint(),
            axis.directionVector(),
            UnitVector3d(normalVector.cross(axis.directionVector()).components()),
            normalVector
        );
    }

    Plane3d
    Plane3d::xy() {
        return Plane3d(Point3d::origin(), Vector3d::unitX(), Vector3d::unitY(), Vector3d::unitZ());
    }

    Plane3d
    Plane3d::xz() {
        return Plane3d(Point3d::origin(), Vector3d::unitX(), Vector3d::unitZ(), -Vector3d::unitY());
    }
    
    Plane3d
    Plane3d::yx() {
        return Plane3d(Point3d::origin(), Vector3d::unitY(), Vector3d::unitX(), -Vector3d::unitZ());
    }

    Plane3d
    Plane3d::yz() {
        return Plane3d(Point3d::origin(), Vector3d::unitY(), Vector3d::unitZ(), Vector3d::unitX());
    }

    Plane3d
    Plane3d::zx() {
        return Plane3d(Point3d::origin(), Vector3d::unitZ(), Vector3d::unitX(), Vector3d::unitY());
    }
    
    Plane3d
    Plane3d::zy() {
        return Plane3d(Point3d::origin(), Vector3d::unitZ(), Vector3d::unitY(), -Vector3d::unitX());
    }
    
    Plane3d
    Plane3d::offsetBy(double distance) const {
        return Plane3d(
            originPoint() + distance * normalVector(),
            xDirectionVector(),
            yDirectionVector(),
            normalVector(),
            handedness()
        );
    }

    Plane3d
    Plane3d::flipped() const {
        return Plane3d(
            originPoint(),
            xDirectionVector(),
            yDirectionVector(),
            -normalVector(),
            -handedness()
        );
    }

    Axis3d
    Plane3d::normalAxis() const {
        return Axis3d(originPoint(), normalVector());
    }

    Plane3d
    Plane3d::scaledAbout(const Point3d& point, double scale) const {
        return Plane3d(
            originPoint().scaledAbout(point, scale),
            xDirectionVector(),
            yDirectionVector(),
            normalVector(),
            handedness()
        );
    }

    Plane3d
    Plane3d::rotatedAbout(const Point3d& point, const Matrix3d& rotationMatrix) const {
        return Plane3d(
            originPoint().rotatedAbout(point, rotationMatrix),
            xDirectionVector().rotatedBy(rotationMatrix),
            yDirectionVector().rotatedBy(rotationMatrix),
            normalVector().rotatedBy(rotationMatrix),
            handedness()
        );
    }

    Plane3d
    Plane3d::translatedBy(const Vector3d& vector) const {
        return Plane3d(
            originPoint().translatedBy(vector),
            xDirectionVector(),
            yDirectionVector(),
            normalVector(),
            handedness()
        );
    }

    Plane3d
    Plane3d::toLocalIn(const Frame3d& frame) const {
        return Plane3d(
            originPoint().toLocalIn(frame),
            xDirectionVector().toLocalIn(frame),
            yDirectionVector().toLocalIn(frame),
            normalVector().toLocalIn(frame),
            handedness()
        );
    }

    Plane3d
    Plane3d::toGlobalFrom(const Frame3d& frame) const {
        return Plane3d(
            originPoint().toGlobalFrom(frame),
            xDirectionVector().toGlobalFrom(frame),
            yDirectionVector().toGlobalFrom(frame),
            normalVector().toGlobalFrom(frame),
            handedness()
        );
    }

    Plane3d
    Plane3d::mirroredAbout(const Point3d& point, const UnitVector3d& directionVector) const {
        return Plane3d(
            originPoint().mirroredAbout(point, directionVector),
            xDirectionVector().mirroredAlong(directionVector),
            yDirectionVector().mirroredAlong(directionVector),
            normalVector().mirroredAlong(directionVector),
            -handedness()
        );
    }

    ParametricExpression<Point3d, Point2d>
    Plane3d::expression() const {
        Parameter2d u(0);
        Parameter2d v(1);
        return originPoint() + u * xDirectionVector() + v * yDirectionVector();
    }
}
