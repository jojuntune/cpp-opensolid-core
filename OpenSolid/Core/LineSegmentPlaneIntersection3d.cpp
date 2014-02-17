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

#include <OpenSolid/Core/LineSegmentPlaneIntersection3d.hpp>

#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    namespace
    {
        inline
        Point3d
        intersectionPoint(
            const Point3d& startPoint,
            const Point3d& endPoint,
            double startHeight,
            double endHeight
        ) {
            return startPoint + (startHeight / (startHeight - endHeight)) * (endPoint - startPoint);
        }
    }

    Intersection<LineSegment3d, Plane3d>::Intersection(
        const LineSegment3d& lineSegment,
        const Plane3d& plane,
        double precision
    ) : _type(NONE) {

        Point3d startVertex = lineSegment.startVertex();
        Point3d endVertex = lineSegment.endVertex();
        double startHeight = startVertex.distanceTo(plane);
        double endHeight = endVertex.distanceTo(plane);
        Zero zero(precision);
        
        if (startHeight < zero) {
            if (endHeight < zero) { // -, -
                _type = NONE;
            } else if (endHeight > zero) { // -, +
                _type = POINT;
                _point = intersectionPoint(startVertex, endVertex, startHeight, endHeight);
            } else { // -, 0
                _type = POINT;
                _point = endVertex;
            }
        } else if (startHeight > zero) {
            if (endHeight < zero) { // +, -
                _type = POINT;
                _point = intersectionPoint(startVertex, endVertex, startHeight, endHeight);
            } else if (endHeight > zero) { // +, +
                _type = NONE;
            } else { // +, 0
                _type = POINT;
                _point = endVertex;
            }
        } else {
            if (endHeight < zero) { // 0, -
                _type = POINT;
                _point = startVertex;
            } else if (endHeight > zero) { // 0, +
                _type = POINT;
                _point = startVertex;
            } else { // 0, 0
                _type = COINCIDENT;
            }
        }
    }
}
