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
 
#include <OpenSolid/Core/Geometry/GeometryConstructors.hpp>

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Geometry.hpp>

namespace opensolid
{
    Geometry
    GeometryConstructors::Arc3d(
        const Plane3d& plane,
        double radius,
        double startAngle,
        double endAngle
    ) {
        return plane * Geometry::Arc2d(Frame2d::XY(), radius, startAngle, endAngle);
    }

    Geometry
    GeometryConstructors::Arc3d(
        const Axis3d& axis,
        const Point3d& startPoint,
        const Point3d& endPoint
    ) {
        Point3d center = startPoint.projected(axis);
        Plane3d plane = Plane3d::FromPointAndNormal(center, axis.basisVector());
        return plane * Geometry::Arc2d(
            Point2d::Origin(),
            true,
            startPoint / plane,
            endPoint / plane
        );
    }

    Geometry
    GeometryConstructors::Arc3d(
        const Point3d& startPoint,
        const Point3d& innerPoint,
        const Point3d& endPoint
    ) {
        Plane3d plane = Plane3d::FromPointAndNormal(
            innerPoint,
            (startPoint - innerPoint).cross(endPoint - innerPoint).normalized()
        );
        return plane * Geometry::Arc2d(startPoint / plane, innerPoint / plane, endPoint / plane);
    }

    Geometry
    GeometryConstructors::Circle3d(const Axis3d& axis, double radius, bool isFilled) {
        return axis.normalPlane() * Geometry::Circle2d(Point2d::Origin(), radius, isFilled);
    }

    Geometry
    GeometryConstructors::Circle3d(const Plane3d& plane, double radius, bool isFilled) {
        return plane * Geometry::Circle2d(Point2d::Origin(), radius, isFilled);
    }
        
    Geometry
    GeometryConstructors::Helix3d(
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
