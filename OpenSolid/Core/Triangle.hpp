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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Triangle.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    inline
    Triangle2d::Triangle() {
    }

    inline
    Triangle2d::Triangle(
        const Point2d& firstVertex,
        const Point2d& secondVertex,
        const Point2d& thirdVertex
    ) {
        _vertices[0] = firstVertex;
        _vertices[1] = secondVertex;
        _vertices[2] = thirdVertex;
    }

    inline
    const Point2d&
    Triangle2d::vertex(int index) const {
        assert(index >= 0 && index < 3);
        return _vertices[index];
    }

    inline
    LineSegment2d
    Triangle2d::edge(int oppositeIndex) const {
        return LineSegment2d(
            vertex((oppositeIndex + 1) % 3),
            vertex((oppositeIndex + 2) % 3)
        );
    }

    inline
    Box2d
    Triangle2d::bounds() const {
        return vertex(0).hull(vertex(1)).hull(vertex(2));
    }

    inline
    bool
    Triangle2d::operator==(const Triangle2d& other) const {
        return vertex(0) == other.vertex(0) &&
            vertex(1) == other.vertex(1) &&
            vertex(2) == other.vertex(2);
    }

    inline
    Triangle3d::Triangle() {
    }

    inline
    Triangle3d::Triangle(
        const Point3d& firstVertex,
        const Point3d& secondVertex,
        const Point3d& thirdVertex
    ) {
        _vertices[0] = firstVertex;
        _vertices[1] = secondVertex;
        _vertices[2] = thirdVertex;
    }

    inline
    const Point3d&
    Triangle3d::vertex(int index) const {
        assert(index >= 0 && index < 3);
        return _vertices[index];
    }

    inline
    LineSegment3d
    Triangle3d::edge(int oppositeIndex) const {
        assert(index >= 0 && index < 3);
        return LineSegment3d(
            vertex((oppositeIndex + 1) % 3),
            vertex((oppositeIndex + 2) % 3)
        );
    }

    inline
    Box3d
    Triangle3d::bounds() const {
        return vertex(0).hull(vertex(1)).hull(vertex(2));
    }

    inline
    bool
    Triangle3d::operator==(const Triangle3d& other) const {
        return vertex(0) == other.vertex(0) &&
            vertex(1) == other.vertex(1) &&
            vertex(2) == other.vertex(2);
    }
}
