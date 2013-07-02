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

#include <OpenSolid/Core/Curve/CurveConstructors.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Curve.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Triangle.hpp>

namespace opensolid
{
    namespace detail
    {
        bool
        computeCenterPoint(
            double radius,
            WindingDirection direction,
            const Point2d& startPoint,
            const Point2d& endPoint,
            Point2d* result
        ) {
            if (radius <= Zero()) {
                assert(false);
                *result = Point2d();
                return false;
            }

            Vector2d displacementVector = endPoint - startPoint;
            double halfDistance = displacementVector.norm() / 2;

            if (halfDistance == Zero()) {
                // Points are coincident
                assert(false);
                *result = Point2d();
                return false;
            }

            if (halfDistance - radius > Zero()) {
                // Points are too far apart
                assert(false);
                *result = Point2d();
                return false;
            }

            Vector2d sidewaysDirection = displacementVector.unitOrthogonal();
            if (direction == Counterclockwise) {
                sidewaysDirection = -sidewaysDirection;
            }

            double sidewaysDistance = 0.0;
            if (halfDistance - radius == Zero()) {
                sidewaysDistance = radius;
            } else {
                sidewaysDistance = sqrt(halfDistance * halfDistance - radius * radius);
            }

            *result = startPoint + displacementVector / 2 + sidewaysDistance * sidewaysDirection;
            return true;
        }

        bool
        computeCenterPoint(
            const Point2d& firstPoint,
            const Point2d& secondPoint,
            const Point2d& thirdPoint,
            Point2d* result
        ) {
            double a = (secondPoint - firstPoint).norm();
            double b = (thirdPoint - secondPoint).norm();
            double c = (firstPoint - thirdPoint).norm();
            double s = (a + b + c) / 2;

            if(s - a <= Zero() || s - b <= Zero() || s - c <= Zero()) {
                // Points are collinear
                assert(false);
                *result = Point2d();
                return false;
            }

            //double radius = a * b * c / sqrt((a + b + c) * (b + c - a) * (c + a - b) * (a + b - c));
            double a2 = a * a;
            double b2 = b * b;
            double c2 = c * c;
            double t1 = a2 * (b2 + c2 - a2);
            double t2 = b2 * (c2 + a2 - b2);
            double t3 = c2 * (a2 + b2 - c2);
            double sum = t1 + t2 + t3;
            t1 /= sum;
            t2 /= sum;
            t3 /= sum;

            *result = Point2d(
                t1 * thirdPoint.vector() + t2 * firstPoint.vector() + t3 * secondPoint.vector()
            );
            return true;
        }

        bool
        computeWindingDirection(
            const Point2d& firstPoint,
            const Point2d& secondPoint,
            const Point2d& thirdPoint,
            WindingDirection* result
        ) {
            Vector2d firstLeg = secondPoint - firstPoint;
            Vector2d secondLeg = thirdPoint - secondPoint;
            double determinant = firstLeg.x() * secondLeg.y() - firstLeg.y() * secondLeg.x();

            if (determinant == Zero()) {
                // Points are collinear
                assert(false);
                *result = Counterclockwise;
                return false;
            }

            *result = determinant > 0.0 ? Counterclockwise : Clockwise;
            return true;
        }

        bool
        computeHelixParameters(double* pitch, double* numTurns, double* length) {
            bool hasPitch = (*pitch > Zero());
            bool hasNumTurns = (*numTurns > Zero());
            bool hasLength = (*length > Zero());

            if (hasPitch && hasNumTurns && hasLength) {
                if ((*pitch) * (*numTurns) - (*length) != Zero()) {
                    // Parameter values contradict each other
                    assert(false);
                    *pitch = 0.0;
                    *numTurns = 0.0;
                    *length = 0.0;
                    return false;
                } else {
                    return true;
                }
            } else if (hasPitch && hasNumTurns) {
                *length = (*pitch) * (*numTurns);
                return true;
            } else if (hasPitch && hasLength) {
                *numTurns = (*length) / (*pitch);
                return true;
            } else if (hasNumTurns && hasLength) {
                *pitch = (*length) / (*numTurns);
                return true;
            } else {
                // Not enough parameters supplied
                assert(false);
                *pitch = 0.0;
                *numTurns = 0.0;
                *length = 0.0;
                return false;
            }
        }

        Curve<3>
        helix(
            const Point3d& centerPoint,
            const Vector3d& xVector,
            const Vector3d& yVector,
            const Vector3d& zVector,
            WindingDirection direction,
            double numTurns
        ) {
            Function<1, 1> theta = 2 * M_PI * numTurns * Function<1, 1>::t();
            Vector3d sidewaysVector = yVector;
            if (direction == Clockwise) {
                sidewaysVector = -sidewaysVector;
            }
            Function<3, 1> curveFunction = centerPoint.vector() +
                cos(theta) * xVector + sin(theta) * sidewaysVector + Function<1, 1>::t() * zVector;
            return Curve3d(curveFunction, Interval::Unit());
        }
    }

    Curve<2>
    CurveConstructors<2>::Arc(
        const Point<2>& centerPoint,
        double radius,
        double startAngle,
        double endAngle
    ) {
        if (radius <= Zero()) {
            assert(false);
            return Curve2d();
        }
        Frame2d datum = Frame2d(centerPoint).scaledAbout(centerPoint, radius);
        Function<1, 1> angleFunction;
        if (endAngle - startAngle == Zero()) {
            assert(false);
            return Curve2d();
        } else if (endAngle > startAngle) {
            angleFunction = startAngle + (endAngle - startAngle) * Function<1, 1>::t();
        } else {
            datum = datum.xReversed();
            angleFunction = M_PI - startAngle + (startAngle - endAngle) * Function<1, 1>::t();
        }
        return Curve2d(Function<2, 1>::Elliptical(datum).composed(angleFunction), Interval::Unit());
    }
    
    Curve<2>
    CurveConstructors<2>::Arc(
        const Point<2>& centerPoint,
        WindingDirection direction,
        const Point<2>& startPoint,
        const Point<2>& endPoint
    ) {
        // Find radius to start point
        double startRadius = (startPoint - centerPoint).norm();
        if (startRadius == Zero()) {
            // Start point is coincident with center point
            assert(false);
            return Curve2d();
        }

        // Find radius to end point
        double endRadius = (endPoint - centerPoint).norm();
        if (endRadius == Zero()) {
            // End point is coincident with center point
            assert(false);
            return Curve2d();
        }

        // Check that radii are equal within a tolerance and take their mean as
        // the actual radius (attempt to average out any rounding errors)
        if (startRadius - endRadius != Zero()) {
            assert(false);
            return Curve2d();
        }
        double radius = startRadius + (endRadius - startRadius) / 2;

        // Determine start and end angles of arc, respecting the given direction
        double startAngle = std::atan2(startPoint.y(), startPoint.x());
        double endAngle = std::atan2(endPoint.y(), endPoint.x());
        if (direction == Counterclockwise && endAngle - startAngle <= Zero()) {
            endAngle += 2 * M_PI;
        } else if (direction == Clockwise && endAngle - startAngle >= Zero()) {
            endAngle -= 2 * M_PI;
        }
        return Arc(centerPoint, radius, startAngle, endAngle);
    }

    Curve<2>
    CurveConstructors<2>::Arc(
        double radius,
        WindingDirection direction, 
        const Point<2>& startPoint,
        const Point<2>& endPoint
    ) {
        Point2d centerPoint;
        if (!detail::computeCenterPoint(radius, direction, startPoint, endPoint, &centerPoint)) {
            assert(false);
            return Curve2d();
        }
        return Arc(centerPoint, direction, startPoint, endPoint);
    }

    Curve<2>
    CurveConstructors<2>::Arc(
        const Point<2>& startPoint,
        const Point<2>& innerPoint,
        const Point<2>& endPoint
    ) {
        Point2d centerPoint;
        if (!detail::computeCenterPoint(startPoint, innerPoint, endPoint, &centerPoint)) {
            assert(false);
            return Curve2d();
        }
        WindingDirection direction = Counterclockwise;
        if (!detail::computeWindingDirection(startPoint, innerPoint, endPoint, &direction)) {

        }
        return Arc(centerPoint, direction, startPoint, endPoint);
    }

    Curve<2>
    CurveConstructors<2>::Circle(const Point<2>& centerPoint, double radius) {
        return Curve2d::Arc(centerPoint, radius, 0, 2 * M_PI);
    }

    Curve<2>
    CurveConstructors<2>::Circle(
        const Point<2>& centerPoint,
        double radius,
        WindingDirection direction,
        double startAngle
    ) {
        if (direction == Counterclockwise) {
            return Curve2d::Arc(centerPoint, radius, startAngle, startAngle + 2 * M_PI);
        } else {
            return Curve2d::Arc(centerPoint, radius, startAngle, startAngle - 2 * M_PI);
        }
    }

    Curve<2>
    CurveConstructors<2>::Circle(
        const Point<2>& centerPoint,
        WindingDirection direction,
        const Point<2>& startPoint
    ) {
        return Arc(centerPoint, direction, startPoint, startPoint);
    }

    Curve<2>
    CurveConstructors<2>::Circle(
        double radius,
        WindingDirection direction,
        const Point<2>& startPoint,
        const Point<2>& secondPoint
    ) {
        Point2d centerPoint;
        if (!detail::computeCenterPoint(radius, direction, startPoint, secondPoint, &centerPoint)) {
            assert(false);
            return Curve2d();
        }
        return Circle(centerPoint, direction, startPoint);
    }

    Curve<2>
    CurveConstructors<2>::Circle(
        const Point<2>& startPoint,
        const Point<2>& secondPoint,
        const Point<2>& thirdPoint
    ) {
        Point2d centerPoint;
        if (!detail::computeCenterPoint(startPoint, secondPoint, thirdPoint, &centerPoint)) {
            assert(false);
            return Curve2d();
        }
        WindingDirection direction = Counterclockwise;
        if (!detail::computeWindingDirection(startPoint, secondPoint, thirdPoint, &direction)) {
            assert(false);
            return Curve2d();
        }
        return Circle(centerPoint, direction, startPoint);
    }

    Curve<2>
    CurveConstructors<2>::Circumcircle(const Triangle<2>& triangle) {
        return Circle(triangle.vertex(0), triangle.vertex(1), triangle.vertex(2));
    }

    Curve<3>
    CurveConstructors<3>::Arc(
        const Point<3>& centerPoint,
        const Vector3d& axisDirection,
        const Point<3>& startPoint,
        const Point<3>& endPoint
    ) {
        if (axisDirection.squaredNorm() - 1 != Zero()) {
            // Axis direction not a unit vector
            assert(false);
            return Curve3d();
        }
        Vector3d startRadialVector = startPoint - centerPoint;
        if (startRadialVector.dot(axisDirection) != Zero()) {
            // Start point not coplanar with center
            assert(false);
            return Curve3d();
        }
        Vector3d endRadialVector = endPoint - centerPoint;
        if (endRadialVector.dot(axisDirection) != Zero()) {
            // End point not coplanar with center
            assert(false);
            return Curve3d();
        }
        if (startRadialVector.squaredNorm() - endRadialVector.squaredNorm() != Zero()) {
            // Start and end points are different distances from the center
            assert(false);
            return Curve3d();
        }
        Plane3d plane(
            centerPoint,
            startRadialVector.normalized(),
            axisDirection.cross(startRadialVector).normalized()
        );
        return CurveConstructors<2>::Arc(
            Point2d::Origin(),
            Counterclockwise,
            startPoint.localizedTo(plane),
            endPoint.localizedTo(plane)
        ).globalizedFrom(plane);
    }

    Curve<3>
    CurveConstructors<3>::Arc(
        const Axis<3>& axis,
        const Point<3>& startPoint,
        const Point<3>& endPoint
    ) {
        Point3d projectedStartPoint = startPoint.projectedOnto(axis);
        Vector3d startRadialVector = startPoint - projectedStartPoint;
        if (startRadialVector.isZero()) {
            // Start point is on axis
            assert(false);
            return Curve3d();
        }

        Point3d projectedEndPoint = endPoint.projectedOnto(axis);
        Vector3d endRadialVector = endPoint - projectedEndPoint;
        if (endRadialVector.isZero()) {
            // End point is on axis
            assert(false);
            return Curve3d();
        }

        if (startRadialVector.squaredNorm() - endRadialVector.squaredNorm() != Zero()) {
            // Start and end points are different distances from the axis
            assert(false);
            return Curve3d();
        }

        if (!(projectedEndPoint - projectedStartPoint).isZero()) {
            // Start and end points are not coplanar with respect to the axis
            assert(false);
            return Curve3d();
        }

        Point3d centerPoint = projectedStartPoint + (projectedEndPoint - projectedStartPoint) / 2;
        return Arc(centerPoint, axis.basisVector().normalized(), startPoint, endPoint);
    }

    Curve<3>
    CurveConstructors<3>::Arc(
        const Vector3d& axisDirection,
        double radius,
        const Point<3>& startPoint,
        const Point<3>& endPoint
    ) {
        if (axisDirection.squaredNorm() - 1 != Zero()) {
            // Axis direction vector is not a unit vector
            assert(false);
            return Curve3d();
        }
        Vector3d displacementVector = endPoint - startPoint;
        if (displacementVector.dot(axisDirection) != Zero()) {
            // Start and end points are not coplanar with respect to the axis
            assert(false);
            return Curve3d();
        }
        if (displacementVector.squaredNorm() - 4 * radius * radius > Zero()) {
            // Start and end points are too far apart for the given radius
            assert(false);
            return Curve3d();
        }
        Point3d midpoint = startPoint + displacementVector / 2;
        Plane3d plane(
            midpoint,
            displacementVector.cross(axisDirection).normalized(),
            displacementVector.normalized()
        );
        return CurveConstructors<2>::Arc(
            radius,
            Counterclockwise,
            startPoint.localizedTo(plane),
            endPoint.localizedTo(plane)
        ).globalizedFrom(plane);
    }

    Curve<3>
    CurveConstructors<3>::Arc(
        const Point<3>& startPoint,
        const Point<3>& innerPoint,
        const Point<3>& endPoint
    ) {
        Vector3d normalVector = (innerPoint - startPoint).cross(endPoint - innerPoint);
        if (normalVector.isZero()) {
            assert(false);
            return Curve3d();
        }
        Plane3d plane = Plane3d::FromPointAndNormal(innerPoint, normalVector.normalized());
        return CurveConstructors<2>::Arc(
            startPoint.localizedTo(plane),
            innerPoint.localizedTo(plane),
            endPoint.localizedTo(plane)
        ).globalizedFrom(plane);
    }

    Curve<3>
    CurveConstructors<3>::Circle(
        const Point<3>& centerPoint,
        const Vector3d& axisDirection,
        double radius
    ) {
        if (radius <= Zero()) {
            assert(false);
            return Curve3d();
        }
        return Circle(
            centerPoint,
            axisDirection,
            centerPoint + radius * axisDirection.unitOrthogonal()
        );
    }

    Curve<3>
    CurveConstructors<3>::Circle(
        const Point<3>& centerPoint,
        const Vector3d& axisDirection,
        const Point<3>& startPoint
    ) {
        Vector3d startRadialVector = startPoint - centerPoint;
        if (startRadialVector.isZero()) {
            // Start point is coincident with center
            assert(false);
            return Curve3d();
        }
        if (startRadialVector.dot(axisDirection) != Zero()) {
            // Start point is not coplanar with center point
            assert(false);
            return Curve3d();
        }
        return Arc(centerPoint, axisDirection, startPoint, startPoint);
    }

    Curve<3>
    CurveConstructors<3>::Circle(const Axis<3>& axis, const Point<3>& startPoint) {
        Point3d centerPoint = startPoint.projectedOnto(axis);
        if ((startPoint - centerPoint).isZero()) {
            // Start point is on axis
            assert(false);
            return Curve3d();
        }
        return Circle(centerPoint, axis.basisVector().normalized(), startPoint);
    }

    Curve<3>
    CurveConstructors<3>::Circle(
        const Vector3d& axisDirection,
        double radius,
        const Point<3>& startPoint,
        const Point<3>& secondPoint
    ) {
        if (axisDirection.squaredNorm() - 1 != Zero()) {
            // Axis direction vector is not a unit vector
            assert(false);
            return Curve3d();
        }
        Vector3d displacementVector = secondPoint - startPoint;
        if (displacementVector.dot(axisDirection) != Zero()) {
            // Start and second points are not coplanar with respect to the axis
            assert(false);
            return Curve3d();
        }
        if (displacementVector.squaredNorm() - 4 * radius * radius > Zero()) {
            // Start and second points are too far apart for the given radius
            assert(false);
            return Curve3d();
        }
        Point3d midpoint = startPoint + displacementVector / 2;
        Plane3d plane(
            midpoint,
            displacementVector.cross(axisDirection).normalized(),
            displacementVector.normalized()
        );
        return CurveConstructors<2>::Circle(
            radius,
            Counterclockwise,
            startPoint.localizedTo(plane),
            secondPoint.localizedTo(plane)
        ).globalizedFrom(plane);   
    }

    Curve<3>
    CurveConstructors<3>::Circle(
        const Point<3>& startPoint,
        const Point<3>& secondPoint,
        const Point<3>& thirdPoint
    ) {
        Vector3d normalVector = (secondPoint - startPoint).cross(thirdPoint - secondPoint);
        if (normalVector.isZero()) {
            assert(false);
            return Curve3d();
        }
        Plane3d plane = Plane3d::FromPointAndNormal(secondPoint, normalVector.normalized());
        return CurveConstructors<2>::Arc(
            startPoint.localizedTo(plane),
            secondPoint.localizedTo(plane),
            thirdPoint.localizedTo(plane)
        ).globalizedFrom(plane);
    }

    Curve<3>
    CurveConstructors<3>::Circumcircle(const Triangle3d& triangle) {
        return Circle(triangle.vertex(0), triangle.vertex(1), triangle.vertex(2));
    }

    Curve<3>
    CurveConstructors<3>::Helix(
        const Point<3>& startCenterPoint,
        const Point<3>& endCenterPoint,
        double radius,
        WindingDirection direction,
        double pitch,
        double numTurns
    ) {
        Vector3d lengthVector = endCenterPoint - startCenterPoint;
        double length = lengthVector.norm();

        if (length == Zero()) {
            assert(false);
            return Curve3d();
        }

        if (!detail::computeHelixParameters(&pitch, &numTurns, &length)) {
            assert(false);
            return Curve3d();
        }

        Vector3d xDirection = lengthVector.unitOrthogonal();
        Vector3d yDirection = lengthVector.cross(xDirection).normalized();

        return detail::helix(
            startCenterPoint,
            xDirection * radius,
            yDirection * radius,
            lengthVector,
            direction,
            numTurns
        );
    }

    Curve<3>
    CurveConstructors<3>::Helix(
        const Point<3>& startCenterPoint,
        const Point<3>& endCenterPoint,
        WindingDirection direction,
        const Point<3>& startPoint,
        double pitch,
        double numTurns
    ) {
        Vector3d lengthVector = endCenterPoint - startCenterPoint;
        double length = lengthVector.norm();
        if (length == Zero()) {
            assert(false);
            return Curve3d();
        }

        Vector3d startRadialVector = startPoint - startCenterPoint;
        double radius = startRadialVector.norm();
        if (radius == Zero()) {
            // Start point is coincident with start center point
            assert(false);
            return Curve3d();
        }
        if (startRadialVector.dot(lengthVector) != Zero()) {
            // Start point not coplanar with start center point
            assert(false);
            return Curve3d();
        }

        if (!detail::computeHelixParameters(&pitch, &numTurns, &length)) {
            assert(false);
            return Curve3d();
        }

        return detail::helix(
            startCenterPoint,
            startRadialVector,
            lengthVector.cross(startRadialVector).normalized() * radius,
            lengthVector,
            direction,
            numTurns
        );
    }

    Curve<3>
    CurveConstructors<3>::Helix(
        const Point<3>& startCenterPoint,
        const Vector3d& axisDirection,
        double radius,
        WindingDirection direction,
        double pitch,
        double numTurns,
        double length
    ) {
        if (axisDirection.squaredNorm() - 1 != Zero()) {
            assert(false);
            return Curve3d();
        }

        if (!detail::computeHelixParameters(&pitch, &numTurns, &length)) {
            assert(false);
            return Curve3d();
        }

        Vector3d xDirection = axisDirection.unitOrthogonal();
        Vector3d yDirection = axisDirection.cross(xDirection);

        return detail::helix(
            startCenterPoint,
            xDirection * radius,
            yDirection * radius,
            axisDirection * length,
            direction,
            numTurns
        );
    }

    Curve<3>
    CurveConstructors<3>::Helix(
        const Point<3>& startCenterPoint,
        const Vector3d& axisDirection,
        WindingDirection direction,
        const Point<3>& startPoint,
        double pitch,
        double numTurns,
        double length
    ) {
        if (axisDirection.squaredNorm() - 1 != Zero()) {
            assert(false);
            return Curve3d();
        }

        Vector3d startRadialVector = startPoint - startCenterPoint;
        if (startRadialVector.dot(axisDirection) != Zero()) {
            // Start point and start center point are not coplanar
            assert(false);
            return Curve3d();
        }

        double radius = startRadialVector.norm();
        if (radius == Zero()) {
            assert(false);
            return Curve3d();
        }

        if (!detail::computeHelixParameters(&pitch, &numTurns, &length)) {
            assert(false);
            return Curve3d();
        }

        return detail::helix(
            startCenterPoint,
            startRadialVector,
            axisDirection.cross(startRadialVector).normalized() * radius,
            axisDirection * length,
            direction,
            numTurns
        );
    }

    Curve<3>
    CurveConstructors<3>::Helix(
        const Axis<3>& axis,
        WindingDirection direction,
        const Point<3>& startPoint,
        double pitch,
        double numTurns,
        double length
    ) {
        Point3d startCenterPoint = startPoint.projectedOnto(axis);
        Vector3d startRadialVector = startPoint - startCenterPoint;
        
        double radius = startRadialVector.norm();
        if (radius == Zero()) {
            assert(false);
            return Curve3d();
        }

        if (!detail::computeHelixParameters(&pitch, &numTurns, &length)) {
            assert(false);
            return Curve3d();
        }

        return detail::helix(
            startCenterPoint,
            startRadialVector,
            axis.basisVector().cross(startRadialVector).normalized() * radius,
            axis.basisVector().normalized() * length,
            direction,
            numTurns
        );
    }
}
