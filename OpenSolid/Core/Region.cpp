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

#include <OpenSolid/Core/Region.hpp>

#include <OpenSolid/Core/Curve.hpp>
#include <OpenSolid/Core/LineSegment.hpp>

namespace opensolid
{
    Region2d::Region2d() :
        Domain<2>() {
    }

    Region2d::Region2d(const Domain<2>& domain) :
        Domain<2>(domain) {
    }

    Region2d::Region2d(const SpatialSet<Geometry<2, 1>>& boundaries) :
        Domain<2>(boundaries) {
    }

    namespace
    {
        SpatialSet<Geometry<2, 1>>
        boxBoundaries(const Box<2>& box) {
            Point2d lowerLeft = box.interpolated(0, 0);
            Point2d lowerRight = box.interpolated(1, 0);
            Point2d upperRight = box.interpolated(1, 1);
            Point2d upperLeft = box.interpolated(0, 1);

            LineSegment2d edges[4];
            edges[0] = LineSegment2d(lowerLeft, lowerRight);
            edges[1] = LineSegment2d(lowerRight, upperRight);
            edges[2] = LineSegment2d(upperRight, upperLeft);
            edges[3] = LineSegment2d(upperLeft, lowerLeft);

            return SpatialSet<Geometry<2, 1>>(edges, edges + 4);
        }
    }

    Region2d::Region2d(const Box<2>& box) :
        Domain<2>(boxBoundaries(box)) {
    }

    namespace
    {
        SpatialSet<Geometry<2, 1>>
        triangleBoundaries(const Triangle<2>& triangle) {
            LineSegment2d edges[3];
            edges[0] = triangle.edge(0);
            edges[1] = triangle.edge(1);
            edges[2] = triangle.edge(2);

            return SpatialSet<Geometry<2, 1>>(edges, edges + 3);
        }
    }
 
    Region2d::Region2d(const Triangle<2>& triangle) :
        Domain<2>(triangleBoundaries(triangle)) {
    }

    Region2d
    Region2d::Disk(const Point2d& centerPoint, double radius) {
        Curve2d boundary = Curve2d::Circle(centerPoint, radius);
        return Region2d(SpatialSet<Geometry<2, 1>>(&boundary, &boundary + 1));
    }
}
