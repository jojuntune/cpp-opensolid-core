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

#include <OpenSolid/Core/Sphere.hpp>

#include <catch/catch.hpp>

using namespace opensolid;

TEST_CASE("Projection onto plane") {
    Sphere3d sphere(Point3d(3.0, 3.0, 3.0), 1.0);
    Circle3d circle = sphere.projectedOnto(Plane3d::xy());
    REQUIRE((circle.centerPoint() - Point3d(3.0, 3.0, 0.0)).isZero());
    REQUIRE(circle.normalVector().equals(UnitVector3d::Z()));
    REQUIRE((circle.radius() - sphere.radius()) == Zero());
}

TEST_CASE("Projection onto axis") {
    Sphere3d sphere(Point3d(3.0, 3.0, 3.0), 1.0);
    LineSegment3d segment = sphere.projectedOnto(Axis3d::x());
    REQUIRE((segment.startVertex() - Point3d(2.0, 0.0, 0.0)).isZero());
    REQUIRE((segment.endVertex() - Point3d(4.0, 0.0, 0.0)).isZero());
}
