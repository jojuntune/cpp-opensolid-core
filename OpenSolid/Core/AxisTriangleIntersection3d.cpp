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

#include <OpenSolid/Core/AxisTriangleIntersection3d.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/AxisPlaneIntersection3d.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Intersection/XAxisTriangleIntersection2d.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Triangle.hpp>

namespace opensolid
{
    Intersection<Axis3d, Triangle3d>::Intersection(
        const Axis3d& axis,
        const Triangle3d& triangle,
        double precision
    ) : _type(NONE) {

        Plane3d plane = triangle.plane();
        Intersection<Axis3d, Plane3d> axisPlaneIntersection = axis.intersection(plane, precision);
        if (axisPlaneIntersection.exists()) {
            if (axisPlaneIntersection.isPoint()) {
                Point3d intersectionPoint = axisPlaneIntersection.point();
                if ((intersectionPoint - triangle.vertex(0)).isZero(precision)) {
                    _type = POINT;
                    _point = triangle.vertex(0);
                } else if ((intersectionPoint - triangle.vertex(1)).isZero(precision)) {
                    _type = POINT;
                    _point = triangle.vertex(1);
                } else if ((intersectionPoint - triangle.vertex(2)).isZero(precision)) {
                    _type = POINT;
                    _point = triangle.vertex(2);
                } else {
                    Point2d triangleCoordinates = intersectionPoint / triangle.coordinateSystem();
                    if (
                        triangleCoordinates.x() >= Zero(precision) &&
                        triangleCoordinates.y() >= Zero(precision) &&
                        triangleCoordinates.x() + triangleCoordinates.y() - 1 <= Zero(precision)
                    ) {
                        _type = POINT;
                        _point = intersectionPoint;
                    }
                }
            } else { // Axis is coincident with triangle plane: cast into 2D
                PlanarCoordinateSystem3d planarCoordinateSystem(
                    axis.originPoint(),
                    axis.directionVector(),
                    plane.normalVector().cross(axis.directionVector())
                );
                Triangle2d triangle2d = triangle / planarCoordinateSystem;
                detail::XAxisTriangleIntersection2d intersection2d(triangle2d, precision);
                if (intersection2d.isPoint()) {
                    _type = POINT;
                    _point = planarCoordinateSystem * intersection2d.point();
                } else if (intersection2d.isLineSegment()) {
                    _type = LINE_SEGMENT;
                    _lineSegment = planarCoordinateSystem * intersection2d.lineSegment();
                }
            }
        }
    }
}
