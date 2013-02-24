/*************************************************************************************
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
 
#include <OpenSolid/Core/Geometry/GeometryConstructors.hpp>

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    Geometry GeometryConstructors::Arc2d(
        const Frame2d& frame,
        double radius,
        double startAngle,
        double endAngle
    ) {
        Frame2d datum = frame.scaled(radius, frame.originPoint());
        Function angleFunction;
        if (endAngle - startAngle == Zero()) {
            angleFunction = 2 * M_PI * Function::t();
        } else if (endAngle > startAngle) {
            angleFunction = startAngle + (endAngle - startAngle) * Function::t();
        } else {
            datum = datum.xReversed();
            angleFunction = M_PI - startAngle + (startAngle - endAngle) * Function::t();
        }

        return Geometry(Function::Elliptical(datum)(angleFunction), Interval::Unit());
    }
        
    Geometry GeometryConstructors::Arc2d(
        const Vector2d& center,
        bool isCounterclockwise,
        const Vector2d& startPoint,
        const Vector2d& endPoint
    ) {
        Vector2d radialVector = startPoint - center;
        double radius = radialVector.norm();

        Frame2d datum = Frame2d::FromXAxis(Axis2d(center, radialVector.normalized()));
        datum = datum.scaled(radius, center);
        if (!isCounterclockwise) {
            datum = datum.yReversed();
        }

        Vector2d localEndPoint = endPoint / datum;
        double sweptAngle = atan2(localEndPoint.y(), localEndPoint.x());
        if (sweptAngle <= Zero()) {
            sweptAngle += 2 * M_PI;
        }
        Function angleFunction = sweptAngle * Function::t();

        return Geometry(Function::Elliptical(datum)(angleFunction), Interval::Unit());
    }

    Geometry GeometryConstructors::Arc2d(
        const Vector2d& startPoint,
        const Vector2d& innerPoint,
        const Vector2d& endPoint
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
        Vector2d center = t1 * endPoint + t2 * startPoint + t3 * innerPoint;

        Vector2d firstLeg = innerPoint - startPoint;
        Vector2d secondLeg = endPoint - innerPoint;
        bool isCounterclockwise =
            (firstLeg.x() * secondLeg.y() - firstLeg.y() - secondLeg.x()) >= Zero();
        Vector2d startRadialVector = startPoint - center;
        Vector2d endRadialVector = endPoint - center;
        double startAngle = atan2(startRadialVector.y(), startRadialVector.x());
        double endAngle = atan2(endRadialVector.y(), endRadialVector.x());
        if (isCounterclockwise && endAngle < startAngle) {
            endAngle += 2 * M_PI;
        } else if (!isCounterclockwise && endAngle > startAngle) {
            endAngle -= 2 * M_PI;
        }

        return Geometry::Arc2d(Frame2d::XY(center), radius, startAngle, endAngle);
    }

    Geometry GeometryConstructors::Arc3d(
        const Plane3d& plane,
        double radius,
        double startAngle,
        double endAngle
    ) {
        return plane * Geometry::Arc2d(Frame2d::XY(), radius, startAngle, endAngle);
    }

    Geometry GeometryConstructors::Arc3d(
        const Axis3d& axis,
        const Vector3d& startPoint,
        const Vector3d& endPoint
    ) {
        Vector3d center = startPoint.projected(axis);
        Plane3d plane = Plane3d::FromPointAndNormal(center, axis.basisVector());
        return plane * Geometry::Arc2d(Vector2d::Zero(), true, startPoint / plane, endPoint / plane);
    }

    Geometry GeometryConstructors::Arc3d(
        const Vector3d& startPoint,
        const Vector3d& innerPoint,
        const Vector3d& endPoint
    ) {
        Plane3d plane = Plane3d::FromPointAndNormal(
            innerPoint,
            (startPoint - innerPoint).cross(endPoint - innerPoint).normalized()
        );
        return plane * Geometry::Arc2d(startPoint / plane, innerPoint / plane, endPoint / plane);
    }

    Geometry GeometryConstructors::Circle2d(
        const Vector2d& center,
        double radius,
        bool isFilled
    ) {
        if (isFilled) {
            Function arcFunction = Geometry::Arc2d(Frame2d::XY(), radius, 0, 2 * M_PI).function();
            Function u = Function::u();
            Function v = Function::v();
            Function circleFunction = center + u * arcFunction(v);
            return Geometry(circleFunction, Domain(Interval::Unit(), Interval::Unit()));
        } else {
            return Geometry::Arc2d(Frame2d::XY(center), radius, 0, 2 * M_PI);
        }
    }

    Geometry GeometryConstructors::Circle3d(
        const Axis3d& axis,
        double radius,
        bool isFilled
    ) {
        return axis.normalPlane() * Geometry::Circle2d(Vector2d::Zero(), radius, isFilled);
    }

    Geometry GeometryConstructors::Circle3d(
        const Plane3d& plane,
        double radius,
        bool isFilled
    ) {
        return plane * Geometry::Circle2d(Vector2d::Zero(), radius, isFilled);
    }
        
    Geometry GeometryConstructors::Helix3d(
        const Frame3d& frame,
        double radius,
        double pitch,
        Interval turnInterval
    ) {
        Plane3d plane = frame.xyPlane().scaled(radius, frame.originPoint());
        Function angleFunction = 2 * M_PI * Function::t();
        Function planarFunction = Function::Elliptical(plane)(angleFunction);

        Axis3d axis = frame.zAxis().scaled(pitch, frame.originPoint());
        Function axialFunction = Function::Linear(axis);

        return Geometry(planarFunction + axialFunction, turnInterval);
    }
}
