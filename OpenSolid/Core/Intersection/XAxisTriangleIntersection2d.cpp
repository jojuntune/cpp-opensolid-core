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
************************************************************************************/

#include <OpenSolid/Core/Intersection/XAxisTriangleIntersection2d.hpp>

#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Triangle.hpp>

namespace opensolid
{
    namespace detail
    {
        namespace
        {
            inline
            Point2d
            intersectionPoint(const Point2d& firstPoint, const Point2d& secondPoint) {
                double x1 = firstPoint.x();
                double y1 = firstPoint.y();
                double x2 = secondPoint.x();
                double y2 = secondPoint.y();
                return Point2d((x1 * y2 - x2 * y1) / (y1 - y2), 0.0);
            }

            inline
            LineSegment2d
            forwardsLineSegment(const Point2d& firstPoint, const Point2d& secondPoint) {
                if (firstPoint.x() <= secondPoint.x()) {
                    return LineSegment2d(firstPoint, secondPoint);
                } else {
                    return LineSegment2d(secondPoint, firstPoint);
                }
            }
        }

        XAxisTriangleIntersection2d::XAxisTriangleIntersection2d(
            const Triangle2d& triangle,
            double precision
        ) : _type(NONE) {

            Point2d v0 = triangle.vertex(0);
            Point2d v1 = triangle.vertex(1);
            Point2d v2 = triangle.vertex(2);
            double x0 = v0.x();
            double y0 = v0.y();
            double x1 = v1.x();
            double y1 = v1.y();
            double x2 = v2.x();
            double y2 = v2.y();
            Zero zero(precision);

            if (y0 > zero) {
                if (y1 > zero) {
                    if (y2 > zero) { // +, +, +
                        _type = NONE;
                    } else if (y2 < zero) { // +, +, -
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(
                            intersectionPoint(v2, v0),
                            intersectionPoint(v2, v1)
                        );
                    } else { // +, +, 0
                        _type = POINT;
                        _point = v2;
                    }
                } else if (y1 < zero) {
                    if (y2 > zero) { // +, -, +
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(
                            intersectionPoint(v1, v0),
                            intersectionPoint(v1, v2)
                        );
                    } else if (y2 < zero) { // +, -, -
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(
                            intersectionPoint(v0, v1),
                            intersectionPoint(v0, v2)
                        );
                    } else { // +, -, 0
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(intersectionPoint(v0, v1), v2);
                    }
                } else {
                    if (y2 > zero) { // +, 0, +
                        _type = POINT;
                        _point = v1;
                    } else if (y2 < zero) { // +, 0, -
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(intersectionPoint(v0, v2), v1);
                    } else { // +, 0, 0
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(v1, v2);
                    }
                }
            } else if (y0 < zero) {
                if (y1 > zero) {
                    if (y2 > zero) { // -, +, +
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(
                            intersectionPoint(v0, v1),
                            intersectionPoint(v0, v2)
                        );
                    } else if (y2 < zero) { // -, +, -
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(
                            intersectionPoint(v1, v0),
                            intersectionPoint(v1, v2)
                        );
                    } else { // -, +, 0
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(intersectionPoint(v0, v1), v2);
                    }
                } else if (y1 < zero) {
                    if (y2 > zero) { // -, -, +
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(
                            intersectionPoint(v2, v0),
                            intersectionPoint(v2, v1)
                        );
                    } else if (y2 < zero) { // -, -, -
                        _type = NONE;
                    } else { // -, -, 0
                        _type = POINT;
                        _point = v2;
                    }
                } else {
                    if (y2 > zero) { // -, 0, +
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(intersectionPoint(v0, v2), v1);
                    } else if (y2 < zero) { // -, 0, -
                        _type = POINT;
                        _point = v1;
                    } else { // -, 0, 0
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(v1, v2);
                    }
                }
            } else {
                if (y1 > zero) {
                    if (y2 > zero) { // 0, +, +
                        _type = POINT;
                        _point = v0;
                    } else if (y2 < zero) { // 0, +, -
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(v0, intersectionPoint(v1, v2));
                    } else { // 0, +, 0
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(v0, v2);
                    }
                } else if (y1 < zero) {
                    if (y2 > zero) { // 0, -, +
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(v0, intersectionPoint(v1, v2));
                    } else if (y2 < zero) { // 0, -, -
                        _type = POINT;
                        _point = v0;
                    } else { // 0, -, 0
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(v0, v2);
                    }
                } else {
                    if (y2 == zero) { // 0, 0, 0
                        _type = COINCIDENT;
                    } else { // 0, 0, +/-
                        _type = LINE_SEGMENT;
                        _lineSegment = forwardsLineSegment(v0, v1);
                    }
                }
            }
        }
    }
}
