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

namespace opensolid
{
    Curve<2>
    CurveConstructors<2>::Arc(
        const Point<2>& centerPoint,
        double radius,
        double startAngle,
        double endAngle
    ) {
        Frame2d datum = Frame2d(centerPoint).scaledAbout(centerPoint, radius);
        Function angleFunction;
        if (endAngle - startAngle == Zero()) {
            angleFunction = 2 * M_PI * Function::t();
        } else if (endAngle > startAngle) {
            angleFunction = startAngle + (endAngle - startAngle) * Function::t();
        } else {
            datum = datum.xReversed();
            angleFunction = M_PI - startAngle + (startAngle - endAngle) * Function::t();
        }
        return Curve<2>(Function::Elliptical(datum).compose(angleFunction), Interval::Unit());
    }
    
    Curve<2>
    CurveConstructors<2>::ArcFromCenterAndEndpoints(
        const Point<2>& centerPoint,
        WindingDirection direction,
        const Point<2>& startPoint,
        const Point<2>& endPoint
    ) {
        Vector2d radialVector = startPoint - centerPoint;
        double radius = radialVector.norm();

        Frame2d datum = Frame2d::FromXAxis(Axis2d(centerPoint, radialVector.normalized()));
        datum = datum.scaledAbout(centerPoint, radius);
        if (direction == Clockwise) {
            datum = datum.yReversed();
        }

        Point2d localEndPoint = endPoint.localizedTo(datum);
        double sweptAngle = atan2(localEndPoint.y(), localEndPoint.x());
        if (sweptAngle <= Zero()) {
            sweptAngle += 2 * M_PI;
        }
        Function angleFunction = sweptAngle * Function::t();

        return Curve<2>(Function::Elliptical(datum).compose(angleFunction), Interval::Unit());
    }

    Curve<2>
    CurveConstructors<2>::ArcFromThreePoints(
        const Point<2>& startPoint,
        const Point<2>& innerPoint,
        const Point<2>& endPoint
    ) {
        double a = (innerPoint - startPoint).norm();
        double b = (endPoint - innerPoint).norm();
        double c = (startPoint - endPoint).norm();
        #ifndef NDEBUG
        double s = (a + b + c) / 2;
        assert(s - a > Zero() && s - b > Zero() && s - c > Zero());
        #endif
        double radius = a * b * c / sqrt((a + b + c) * (b + c - a) * (c + a - b) * (a + b - c));
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
        Point2d centerPoint = Point2d::Origin() +
            t1 * endPoint.vector() + t2 * startPoint.vector() + t3 * innerPoint.vector();

        Vector2d firstLeg = innerPoint - startPoint;
        Vector2d secondLeg = endPoint - innerPoint;
        bool isCounterclockwise =
            (firstLeg.x() * secondLeg.y() - firstLeg.y() - secondLeg.x()) >= Zero();
        Vector2d startRadialVector = startPoint - centerPoint;
        Vector2d endRadialVector = endPoint - centerPoint;
        double startAngle = atan2(startRadialVector.y(), startRadialVector.x());
        double endAngle = atan2(endRadialVector.y(), endRadialVector.x());
        if (isCounterclockwise && endAngle < startAngle) {
            endAngle += 2 * M_PI;
        } else if (!isCounterclockwise && endAngle > startAngle) {
            endAngle -= 2 * M_PI;
        }

        return Curve<2>::Arc(centerPoint, radius, startAngle, endAngle);
    }

    Curve<2>
    CurveConstructors<2>::Circle(const Point<2>& centerPoint, double radius) {
        return Curve<2>::Arc(centerPoint, radius, 0, 2 * M_PI);
    }

    Curve<3>
    CurveConstructors<3>::ArcOnPlane(
        const Plane3d& plane,
        double radius,
        double startAngle,
        double endAngle
    ) {
        Curve<2> localArc = Curve<2>::Arc(Point2d::Origin(), radius, startAngle, endAngle);
        return localArc.globalizedFrom(plane.normalized());
    }

    Curve<3>
    CurveConstructors<3>::ArcFromAxisAndEndpoints(
        const Axis3d& axis,
        const Point3d& startPoint,
        const Point3d& endPoint
    ) {
        Point3d centerPoint = startPoint.projectedOnto(axis);
        Plane3d plane = Plane3d::FromPointAndNormal(centerPoint, axis.basisVector());
        Curve<2> localArc = Curve<2>::ArcFromCenterAndEndpoints(
            Point<2>::Origin(),
            CurveConstructors<2>::Counterclockwise,
            startPoint.localizedTo(plane),
            endPoint.localizedTo(plane)
        );
        return localArc.globalizedFrom(plane);
    }

    Curve<3>
    CurveConstructors<3>::ArcFromThreePoints(
        const Point3d& startPoint,
        const Point3d& innerPoint,
        const Point3d& endPoint
    ) {
        Vector3d normalVector = (startPoint - innerPoint).cross(endPoint - innerPoint);
        if (normalVector.isZero()) {
            assert(false);
            return Curve<3>();
        }
        Plane3d plane = Plane3d::FromPointAndNormal(innerPoint, normalVector.normalized());
        Curve<2> localArc = Curve<2>::ArcFromThreePoints(
            startPoint.localizedTo(plane),
            innerPoint.localizedTo(plane),
            endPoint.localizedTo(plane)
        );
        return localArc.globalizedFrom(plane);
    }

    Curve<3>
    CurveConstructors<3>::CircleAboutAxis(const Axis<3>& axis, double radius) {
        return Curve<2>::Circle(Point2d::Origin(), radius).globalizedFrom(axis.normalPlane());
    }

    Curve<3>
    CurveConstructors<3>::CircleOnPlane(const Plane3d& plane, double radius) {
        return Curve<2>::Circle(Point2d::Origin(), radius).globalizedFrom(plane.normalized());
    }
    
    Curve<3>
    CurveConstructors<3>::HelixFromDatum(const Datum<3, 3>& datum, double numTurns) {
        Function turnFunction = numTurns * Function::t();
        Function angleFunction = 2 * M_PI * turnFunction;

        Function planarFunction = Function::Elliptical(datum.xyPlane()).compose(angleFunction);
        Function axialFunction = Function::Linear(datum.zAxis()).compose(turnFunction);

        return Curve<3>(planarFunction + axialFunction, Interval::Unit());
    }

    Curve<3>
    CurveConstructors<3>::HelixFromFrame(
        const Frame<3>& frame,
        double radius,
        double pitch,
        double numTurns
    ) {
        Matrix3d basisMatrix;
        basisMatrix.col(0) = frame.xBasisVector().normalized() * radius;
        basisMatrix.col(1) = frame.yBasisVector().normalized() * radius;
        basisMatrix.col(2) = frame.zBasisVector().normalized() * pitch;

        return HelixFromDatum(Datum<3, 3>(frame.originPoint(), basisMatrix), numTurns);
    }

    Curve<3>
    CurveConstructors<3>::HelixAboutAxis(
        const Axis<3>& axis,
        const Point<3>& startPoint,
        double pitch,
        double numTurns
    ) {
        Point<3> originPoint = startPoint.projectedOnto(axis);

        Matrix3d basisMatrix;
        basisMatrix.col(2) = pitch * axis.basisVector().normalized();
        basisMatrix.col(0) = startPoint - originPoint;
        basisMatrix.col(1) = axis.basisVector().cross(startPoint - axis.originPoint()).normalized() *
            basisMatrix.col(0).norm();

        return HelixFromDatum(Datum<3, 3>(originPoint, basisMatrix), numTurns);
    }

    Curve<3>
    CurveConstructors<3>::HelixBetweenPoints(
        const Point<3>& startBasePoint,
        const Point<3>& endBasePoint,
        double radius,
        double numTurns
    ) {
        Vector3d displacementVector = (endBasePoint - startBasePoint);

        Matrix3d basisMatrix;
        basisMatrix.col(2) = displacementVector / numTurns;
        basisMatrix.col(0) = displacementVector.unitOrthogonal() * radius;
        basisMatrix.col(1) = displacementVector.cross(basisMatrix.col(0)).normalized() * radius;

        return HelixFromDatum(Datum<3, 3>(startBasePoint, basisMatrix), numTurns);
    }
}
