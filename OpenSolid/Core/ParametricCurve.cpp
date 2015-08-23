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

#include <OpenSolid/Core/ParametricCurve.hpp>

#include <OpenSolid/Core/Circle.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Parameter.hpp>

namespace opensolid
{
    namespace detail
    {
        WindingDirection
        computeWindingDirection(
            const Point2d& firstPoint,
            const Point2d& secondPoint,
            const Point2d& thirdPoint
        ) {
            Vector2d firstLeg = secondPoint - firstPoint;
            Vector2d secondLeg = thirdPoint - secondPoint;
            double determinant = firstLeg.x() * secondLeg.y() - firstLeg.y() * secondLeg.x();

            if (determinant == Zero()) {
                // Points are collinear
                throw Error(new PlaceholderError());
            }

            return determinant > 0.0 ? COUNTERCLOCKWISE : CLOCKWISE;
        }

        bool
        computeHelixParameters(double& pitch, double& numTurns, double& length) {
            bool hasPitch = (pitch > Zero());
            bool hasNumTurns = (numTurns > Zero());
            bool hasLength = (length > Zero());

            if (hasPitch && hasNumTurns && hasLength) {
                if (pitch * numTurns - length != Zero()) {
                    // Parameter values contradict each other
                    assert(false);
                    pitch = 0.0;
                    numTurns = 0.0;
                    length = 0.0;
                    return false;
                } else {
                    return true;
                }
            } else if (hasPitch && hasNumTurns) {
                length = pitch * numTurns;
                return true;
            } else if (hasPitch && hasLength) {
                numTurns = length / pitch;
                return true;
            } else if (hasNumTurns && hasLength) {
                pitch = length / numTurns;
                return true;
            } else {
                // Not enough parameters supplied
                assert(false);
                pitch = 0.0;
                numTurns = 0.0;
                length = 0.0;
                return false;
            }
        }

        ParametricCurve3d
        helix(
            const Point3d& centerPoint,
            const Vector3d& xVector,
            const Vector3d& yVector,
            const Vector3d& zVector,
            WindingDirection windingDirection,
            double numTurns
        ) {
            Parameter1d t;
            ParametricExpression<double, double> theta = 2 * M_PI * numTurns * t;
            Vector3d sidewaysVector = yVector;
            if (windingDirection == CLOCKWISE) {
                sidewaysVector = -sidewaysVector;
            }
            ParametricExpression<Point3d, double> curveExpression = (
                centerPoint + cos(theta) * xVector + sin(theta) * sidewaysVector + t * zVector
            );
            return ParametricCurve3d(curveExpression, Interval::UNIT());
        }
    }

    ParametricCurve2d
    ParametricCurve2d::reversed() const {
        ParametricExpression<double, double> reversedParameter = (
            domain().upperBound() + domain().lowerBound() - Parameter1d()
        );
        return ParametricCurve2d(expression().composed(reversedParameter), domain(), -handedness());
    }

    ParametricExpression<UnitVector2d, double>
    ParametricCurve2d::normalVector() const {
        return handedness().sign() * tangentVector().unitOrthogonal();
    }

    ParametricExpression<double, double>
    ParametricCurve2d::curvature() const {
        return tangentVector().derivative().dot(normalVector());
    }

    ParametricCurve3d
    ParametricCurve2d::placedOnto(const Plane3d& plane) const {
        return ParametricCurve3d(expression().placedOnto(plane), domain());
    }

    ParametricCurve2d
    ParametricCurve2d::arc(
        const Point2d& centerPoint,
        double radius,
        double startAngle,
        double endAngle
    ) {
        if (radius <= Zero()) {
            throw Error(new PlaceholderError());
        }
        if (endAngle - startAngle == Zero()) {
            throw Error(new PlaceholderError());
        }
        Parameter1d t;
        ParametricExpression<double, double> angleExpression = (
            startAngle + (endAngle - startAngle) * t
        );
        ParametricExpression<double, double> xExpression = (
            centerPoint.x() + radius * cos(angleExpression)
        );
        ParametricExpression<double, double> yExpression = (
            centerPoint.y() + radius * sin(angleExpression)
        );
        ParametricExpression<Point2d, double> curveExpression = (
            ParametricExpression<Point2d, double>::fromComponents(xExpression, yExpression)
        );
        return ParametricCurve2d(curveExpression, Interval::UNIT());
    }
    
    ParametricCurve2d
    ParametricCurve2d::arc(
        const Point2d& centerPoint,
        WindingDirection windingDirection,
        const Point2d& startPoint,
        const Point2d& endPoint
    ) {
        Vector2d startRadialVector = startPoint - centerPoint;
        Vector2d endRadialVector = endPoint - centerPoint;

        // Find radius to start point
        double startRadius = startRadialVector.norm();
        if (startRadius == Zero()) {
            // Start point is coincident with center point
            throw Error(new PlaceholderError());
        }

        // Find radius to end point
        double endRadius = endRadialVector.norm();
        if (endRadius == Zero()) {
            // End point is coincident with center point
            throw Error(new PlaceholderError());
        }

        // Check that radii are equal within a tolerance and take their mean as
        // the actual radius (attempt to average out any rounding errors)
        if (startRadius - endRadius != Zero()) {
            throw Error(new PlaceholderError());
        }
        double radius = startRadius + (endRadius - startRadius) / 2;

        // Determine start and end angles of arc, respecting the given winding direction
        double startAngle = std::atan2(startRadialVector.y(), startRadialVector.x());
        double endAngle = std::atan2(endRadialVector.y(), endRadialVector.x());
        if (windingDirection == COUNTERCLOCKWISE && endAngle - startAngle <= Zero()) {
            endAngle += 2 * M_PI;
        } else if (windingDirection == CLOCKWISE && endAngle - startAngle >= Zero()) {
            endAngle -= 2 * M_PI;
        }
        return arc(centerPoint, radius, startAngle, endAngle);
    }

    ParametricCurve2d
    ParametricCurve2d::arc(
        double radius,
        WindingDirection windingDirection, 
        const Point2d& startPoint,
        const Point2d& endPoint
    ) {
        return arc(
            Circle2d(radius, windingDirection, startPoint, endPoint).centerPoint(),
            windingDirection,
            startPoint,
            endPoint
        );
    }

    ParametricCurve2d
    ParametricCurve2d::arc(
        const Point2d& startPoint,
        const Point2d& innerPoint,
        const Point2d& endPoint
    ) {
        return arc(
            Circle2d(startPoint, innerPoint, endPoint).centerPoint(),
            detail::computeWindingDirection(startPoint, innerPoint, endPoint),
            startPoint,
            endPoint
        );
    }

    ParametricCurve2d
    ParametricCurve2d::circle(const Point2d& centerPoint, double radius) {
        return arc(centerPoint, radius, 0, 2 * M_PI);
    }

    ParametricCurve2d
    ParametricCurve2d::circle(
        const Point2d& centerPoint,
        double radius,
        WindingDirection windingDirection,
        double startAngle
    ) {
        return arc(
            centerPoint,
            radius,
            startAngle,
            startAngle + (windingDirection == COUNTERCLOCKWISE ? 2.0 * M_PI : -2.0 * M_PI)
        );
    }

    ParametricCurve2d
    ParametricCurve2d::circle(
        const Point2d& centerPoint,
        WindingDirection windingDirection,
        const Point2d& startPoint
    ) {
        return arc(centerPoint, windingDirection, startPoint, startPoint);
    }

    ParametricCurve2d
    ParametricCurve2d::circle(
        double radius,
        WindingDirection windingDirection,
        const Point2d& startPoint,
        const Point2d& secondPoint
    ) {
        return circle(
            Circle2d(radius, windingDirection, startPoint, secondPoint).centerPoint(),
            windingDirection,
            startPoint
        );
    }

    ParametricCurve2d
    ParametricCurve2d::circle(
        const Point2d& startPoint,
        const Point2d& secondPoint,
        const Point2d& thirdPoint
    ) {
        return circle(
            Circle2d(startPoint, secondPoint, thirdPoint).centerPoint(),
            detail::computeWindingDirection(startPoint, secondPoint, thirdPoint),
            startPoint
        );
    }

    ParametricCurve2d
    ParametricCurve2d::circumcircle(const Triangle2d& triangle) {
        return circle(triangle.vertex(0), triangle.vertex(1), triangle.vertex(2));
    }

    ParametricCurve3d
    ParametricCurve3d::reversed() const {
        ParametricExpression<double, double> reversedParameter = (
            domain().upperBound() + domain().lowerBound() - Parameter1d()
        );
        return ParametricCurve3d(expression().composed(reversedParameter), domain());
    }

    ParametricExpression<UnitVector3d, double>
    ParametricCurve3d::normalVector() const {
        return tangentVector().derivative().normalized();
    }

    ParametricExpression<UnitVector3d, double>
    ParametricCurve3d::binormalVector() const {
        return tangentVector().cross(normalVector()).implementation();
    }

    ParametricExpression<double, double>
    ParametricCurve3d::curvature() const {
        return tangentVector().derivative().norm() / expression().derivative().norm();
    }

    ParametricCurve2d
    ParametricCurve3d::projectedInto(const Plane3d& plane) const {
        return ParametricCurve2d(expression().projectedInto(plane), domain());
    }

    ParametricCurve3d
    ParametricCurve3d::projectedOnto(const Plane3d& plane) const {
        return ParametricCurve3d(expression().projectedOnto(plane), domain());
    }

    ParametricCurve3d
    ParametricCurve3d::arc(
        const Point3d& centerPoint,
        const UnitVector3d& normalVector,
        const Point3d& startPoint,
        const Point3d& endPoint
    ) {
        Vector3d startRadialVector = startPoint - centerPoint;
        if (startRadialVector.dot(normalVector) != Zero()) {
            // Start point not coplanar with center
            throw Error(new PlaceholderError());
        }
        Vector3d endRadialVector = endPoint - centerPoint;
        if (endRadialVector.dot(normalVector) != Zero()) {
            // End point not coplanar with center
            throw Error(new PlaceholderError());
        }
        if (startRadialVector.squaredNorm() - endRadialVector.squaredNorm() != Zero()) {
            // Start and end points are different distances from the center
            throw Error(new PlaceholderError());
        }
        Plane3d plane(
            centerPoint,
            startRadialVector.normalized(),
            normalVector.cross(startRadialVector).normalized(),
            normalVector
        );
        return ParametricCurve2d::arc(
            Point2d::ORIGIN(),
            COUNTERCLOCKWISE,
            startPoint.projectedInto(plane),
            endPoint.projectedInto(plane)
        ).placedOnto(plane);
    }

    ParametricCurve3d
    ParametricCurve3d::arc(
        const Plane3d& plane,
        const Point3d& startPoint,
        const Point3d& endPoint
    ) {
        return arc(plane.originPoint(), plane.normalVector(), startPoint, endPoint);
    }

    ParametricCurve3d
    ParametricCurve3d::arc(
        const Axis3d& axis,
        const Point3d& startPoint,
        const Point3d& endPoint
    ) {
        Point3d projectedStartPoint = startPoint.projectedOnto(axis);
        Vector3d startRadialVector = startPoint - projectedStartPoint;
        if (startRadialVector.isZero()) {
            // Start point is on axis
            throw Error(new PlaceholderError());
        }

        Point3d projectedEndPoint = endPoint.projectedOnto(axis);
        Vector3d endRadialVector = endPoint - projectedEndPoint;
        if (endRadialVector.isZero()) {
            // End point is on axis
            throw Error(new PlaceholderError());
        }

        if (startRadialVector.squaredNorm() - endRadialVector.squaredNorm() != Zero()) {
            // Start and end points are different distances from the axis
            throw Error(new PlaceholderError());
        }

        if (!(projectedEndPoint - projectedStartPoint).isZero()) {
            // Start and end points are not coplanar with respect to the axis
            throw Error(new PlaceholderError());
        }

        Point3d centerPoint = projectedStartPoint + (projectedEndPoint - projectedStartPoint) / 2;
        return arc(centerPoint, axis.directionVector(), startPoint, endPoint);
    }

    ParametricCurve3d
    ParametricCurve3d::arc(
        const UnitVector3d& normalVector,
        double radius,
        const Point3d& startPoint,
        const Point3d& endPoint
    ) {
        Vector3d displacementVector = endPoint - startPoint;
        if (displacementVector.dot(normalVector) != Zero()) {
            // Start and end points are not coplanar with respect to the axis
            throw Error(new PlaceholderError());
        }
        if (displacementVector.squaredNorm() - 4.0 * radius * radius > Zero()) {
            // Start and end points are too far apart for the given radius
            throw Error(new PlaceholderError());
        }
        Point3d midpoint = startPoint + displacementVector / 2.0;
        Plane3d plane(
            midpoint,
            displacementVector.cross(normalVector).normalized(),
            displacementVector.normalized(),
            normalVector
        );
        return ParametricCurve2d::arc(
            radius,
            COUNTERCLOCKWISE,
            startPoint.projectedInto(plane),
            endPoint.projectedInto(plane)
        ).placedOnto(plane);
    }

    ParametricCurve3d
    ParametricCurve3d::arc(
        const Point3d& startPoint,
        const Point3d& innerPoint,
        const Point3d& endPoint
    ) {
        Vector3d firstLeg = innerPoint - startPoint;
        Vector3d secondLeg = endPoint - innerPoint;
        UnitVector3d normalVector = firstLeg.cross(secondLeg).normalized();
        if (normalVector.isZero()) {
            throw Error(new PlaceholderError());
        }
        Plane3d plane(innerPoint, normalVector);
        return ParametricCurve2d::arc(
            startPoint.projectedInto(plane),
            innerPoint.projectedInto(plane),
            endPoint.projectedInto(plane)
        ).placedOnto(plane);
    }

    ParametricCurve3d
    ParametricCurve3d::circle(
        const Point3d& centerPoint,
        const UnitVector3d& normalVector,
        double radius
    ) {
        if (radius <= Zero()) {
            throw Error(new PlaceholderError());
        }
        return circle(
            centerPoint,
            normalVector,
            centerPoint + radius * normalVector.unitOrthogonal()
        );
    }

    ParametricCurve3d
    ParametricCurve3d::circle(
        const Point3d& centerPoint,
        const UnitVector3d& normalVector,
        const Point3d& startPoint
    ) {
        Vector3d startRadialVector = startPoint - centerPoint;
        if (startRadialVector.isZero()) {
            // Start point is coincident with center
            throw Error(new PlaceholderError());
        }
        if (startRadialVector.dot(normalVector) != Zero()) {
            // Start point is not coplanar with center point
            throw Error(new PlaceholderError());
        }
        return arc(centerPoint, normalVector, startPoint, startPoint);
    }

    ParametricCurve3d
    ParametricCurve3d::circle(const Plane3d& plane, const Point3d& startPoint) {
        return circle(plane.originPoint(), plane.normalVector(), startPoint);
    }

    ParametricCurve3d
    ParametricCurve3d::circle(const Axis3d& axis, const Point3d& startPoint) {
        Point3d centerPoint = startPoint.projectedOnto(axis);
        if ((startPoint - centerPoint).isZero()) {
            // Start point is on axis
            throw Error(new PlaceholderError());
        }
        return circle(centerPoint, axis.directionVector(), startPoint);
    }

    ParametricCurve3d
    ParametricCurve3d::circle(
        double radius,
        const UnitVector3d& normalVector,
        const Point3d& startPoint,
        const Point3d& secondPoint
    ) {
        Vector3d displacementVector = secondPoint - startPoint;
        if (displacementVector.dot(normalVector) != Zero()) {
            // Start and second points are not coplanar with respect to the axis
            throw Error(new PlaceholderError());
        }
        if (displacementVector.squaredNorm() - 4 * radius * radius > Zero()) {
            // Start and second points are too far apart for the given radius
            throw Error(new PlaceholderError());
        }
        Point3d midpoint = startPoint + displacementVector / 2;
        Plane3d plane(
            midpoint,
            displacementVector.cross(normalVector).normalized(),
            displacementVector.normalized(),
            normalVector
        );
        return ParametricCurve2d::circle(
            radius,
            COUNTERCLOCKWISE,
            startPoint.projectedInto(plane),
            secondPoint.projectedInto(plane)
        ).placedOnto(plane);   
    }

    ParametricCurve3d
    ParametricCurve3d::circle(
        const Point3d& startPoint,
        const Point3d& secondPoint,
        const Point3d& thirdPoint
    ) {
        Vector3d firstLeg = secondPoint - startPoint;
        Vector3d secondLeg = thirdPoint - secondPoint;
        UnitVector3d normalVector = firstLeg.cross(secondLeg).normalized();
        if (normalVector.isZero()) {
            throw Error(new PlaceholderError());
        }
        Plane3d plane(secondPoint, normalVector);
        return ParametricCurve2d::arc(
            startPoint.projectedInto(plane),
            secondPoint.projectedInto(plane),
            thirdPoint.projectedInto(plane)
        ).placedOnto(plane);
    }

    ParametricCurve3d
    ParametricCurve3d::circumcircle(const Triangle3d& triangle) {
        return circle(triangle.vertex(0), triangle.vertex(1), triangle.vertex(2));
    }

    ParametricCurve3d
    ParametricCurve3d::helix(
        const Point3d& startCenterPoint,
        const Point3d& endCenterPoint,
        double radius,
        WindingDirection windingDirection,
        double pitch,
        double numTurns
    ) {
        Vector3d lengthVector = endCenterPoint - startCenterPoint;
        double length = lengthVector.norm();

        if (length == Zero()) {
            throw Error(new PlaceholderError());
        }

        if (!detail::computeHelixParameters(pitch, numTurns, length)) {
            throw Error(new PlaceholderError());
        }

        Vector3d xDirection = lengthVector.unitOrthogonal();
        Vector3d yDirection = lengthVector.cross(xDirection).normalized();

        return detail::helix(
            startCenterPoint,
            xDirection * radius,
            yDirection * radius,
            lengthVector,
            windingDirection,
            numTurns
        );
    }

    ParametricCurve3d
    ParametricCurve3d::helix(
        const Point3d& startCenterPoint,
        const Point3d& endCenterPoint,
        WindingDirection windingDirection,
        const Point3d& startPoint,
        double pitch,
        double numTurns
    ) {
        Vector3d lengthVector = endCenterPoint - startCenterPoint;
        double length = lengthVector.norm();
        if (length == Zero()) {
            throw Error(new PlaceholderError());
        }

        Vector3d startRadialVector = startPoint - startCenterPoint;
        double radius = startRadialVector.norm();
        if (radius == Zero()) {
            // Start point is coincident with start center point
            throw Error(new PlaceholderError());
        }
        if (startRadialVector.dot(lengthVector) != Zero()) {
            // Start point not coplanar with start center point
            throw Error(new PlaceholderError());
        }

        if (!detail::computeHelixParameters(pitch, numTurns, length)) {
            throw Error(new PlaceholderError());
        }

        return detail::helix(
            startCenterPoint,
            startRadialVector,
            lengthVector.cross(startRadialVector).normalized() * radius,
            lengthVector,
            windingDirection,
            numTurns
        );
    }

    ParametricCurve3d
    ParametricCurve3d::helix(
        const Point3d& startCenterPoint,
        const UnitVector3d& axisDirection,
        double radius,
        WindingDirection windingDirection,
        double pitch,
        double numTurns,
        double length
    ) {
        if (!detail::computeHelixParameters(pitch, numTurns, length)) {
            throw Error(new PlaceholderError());
        }

        Vector3d xDirection = axisDirection.unitOrthogonal();
        Vector3d yDirection = axisDirection.cross(xDirection);

        return detail::helix(
            startCenterPoint,
            xDirection * radius,
            yDirection * radius,
            axisDirection * length,
            windingDirection,
            numTurns
        );
    }

    ParametricCurve3d
    ParametricCurve3d::helix(
        const Point3d& startCenterPoint,
        const UnitVector3d& axisDirection,
        WindingDirection windingDirection,
        const Point3d& startPoint,
        double pitch,
        double numTurns,
        double length
    ) {
        Vector3d startRadialVector = startPoint - startCenterPoint;
        if (startRadialVector.dot(axisDirection) != Zero()) {
            // Start point and start center point are not coplanar
            throw Error(new PlaceholderError());
        }

        double radius = startRadialVector.norm();
        if (radius == Zero()) {
            throw Error(new PlaceholderError());
        }

        if (!detail::computeHelixParameters(pitch, numTurns, length)) {
            throw Error(new PlaceholderError());
        }

        return detail::helix(
            startCenterPoint,
            startRadialVector,
            axisDirection.cross(startRadialVector).normalized() * radius,
            axisDirection * length,
            windingDirection,
            numTurns
        );
    }

    ParametricCurve3d
    ParametricCurve3d::helix(
        const Axis3d& axis,
        WindingDirection windingDirection,
        const Point3d& startPoint,
        double pitch,
        double numTurns,
        double length
    ) {
        Point3d startCenterPoint = startPoint.projectedOnto(axis);
        Vector3d startRadialVector = startPoint - startCenterPoint;
        
        double radius = startRadialVector.norm();
        if (radius == Zero()) {
            throw Error(new PlaceholderError());
        }

        if (!detail::computeHelixParameters(pitch, numTurns, length)) {
            throw Error(new PlaceholderError());
        }

        return detail::helix(
            startCenterPoint,
            startRadialVector,
            axis.directionVector().cross(startRadialVector),
            axis.directionVector() * length,
            windingDirection,
            numTurns
        );
    }
}
