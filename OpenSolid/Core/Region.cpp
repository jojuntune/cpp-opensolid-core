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

namespace opensolid
{
    Region2d::Region2d() :
        Domain<2>() {
    }

    Region2d::Region2d(const Domain<2>& domain) :
        Domain<2>(domain) {
    }

    Region2d::Region2d(const Set<Geometry<2, 1>>& boundaries) :
        Domain<2>(boundaries) {
    }

    namespace
    {
        Set<Geometry<2, 1>>
        boxBoundaries(const Box<2>& box) {
            Point2d lowerLeft = box.interpolated(0, 0);
            Point2d lowerRight = box.interpolated(1, 0);
            Point2d upperRight = box.interpolated(1, 1);
            Point2d upperLeft = box.interpolated(0, 1);

            LineSegment2d lowerEdge(lowerLeft, lowerRight);
            LineSegment2d rightEdge(lowerRight, upperRight);
            LineSegment2d upperEdge(upperRight, upperLeft);
            LineSegment2d leftEdge(upperLeft, lowerLeft);

            Set<Geometry<2, 1>> results;
            results.insert(lowerEdge);
            results.insert(rightEdge);
            results.insert(upperEdge);
            results.insert(leftEdge);
            return results;
        }
    }

    Region2d::Region2d(const Box<2>& box) :
        Domain<2>(boxBoundaries(box)) {
    }

    namespace
    {
        Set<Geometry<2, 1>>
        triangleBoundaries(const Triangle<2>& triangle) {
            Set<Geometry<2, 1>> results;
            results.insert(triangle.edge(0));
            results.insert(triangle.edge(1));
            results.insert(triangle.edge(2));
            return results;
        }
    }
 
    Region2d::Region2d(const Triangle<2>& triangle) :
        Domain<2>(triangleBoundaries(triangle)) {
    }

    Region2d
    Region2d::Disk(const Point2d& centerPoint, double radius) {
        Set<Geometry<2, 1>> boundaries;
        boundaries.insert(Curve2d::Circle(centerPoint, radius));
        return Region2d(boundaries);
    }
}
