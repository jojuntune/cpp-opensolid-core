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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

#include <catch/catch.hpp>

using namespace opensolid;

TEST_CASE("Axis/plane intersection") {
    Plane3d plane(Point3d(1, 1, 1), Vector3d(1, 1, 1).normalized());
    Axis3d crossingAxis(Point3d(0, -1, 0), Vector3d(1, 0, 1).normalized());
    Axis3d coincidentAxis(Point3d(3, 0, 0), Vector3d(-1, 1, 0).normalized());
    Axis3d offsetAxis(Point3d(-1, -1, 0), Vector3d(-1, -1, 2).normalized());

    auto crossingIntersection = crossingAxis.intersection(plane);
    REQUIRE(crossingIntersection.exists());
    REQUIRE(crossingIntersection.isPoint());
    REQUIRE_FALSE(crossingIntersection.isCoincident());
    REQUIRE(crossingIntersection.point().distanceTo(plane) == Zero());

    auto coincidentIntersection = coincidentAxis.intersection(plane);
    REQUIRE(coincidentIntersection.exists());
    REQUIRE(coincidentIntersection.isCoincident());
    REQUIRE_FALSE(coincidentIntersection.isPoint());

    auto offsetIntersection = offsetAxis.intersection(plane);
    REQUIRE_FALSE(offsetIntersection.exists());
    REQUIRE_FALSE(offsetIntersection.isPoint());
}

TEST_CASE("3D axis/triangle intersection") {
    Triangle3d triangle(Point3d(1, 0, 0), Point3d(0, 1, 0), Point3d(0, 0, 1));
    Axis3d intersectionAxis(Point3d::Origin(), Vector3d(1, 1, 1).normalized());
    Axis3d missingAxis(Point3d(0, -1, 0), UnitVector3d::Z());
    Axis3d offsetAxis(Point3d(1, 1, 1), Vector3d(1, -1, 0).normalized());
    Axis3d overlappingAxis(Point3d(0.5, 0.5, 0), Vector3d(0, -1, 1).normalized());
    Axis3d edgeCoincidentAxis(Point3d(0, 0, 1), Vector3d(1, 0, -1).normalized());
    Axis3d edgeIntersectionAxis(Point3d::Origin(), Vector3d(1, 1, 0).normalized());
    Axis3d vertexIntersectionAxis(Point3d(1, 0, 1), UnitVector3d::X());

    auto intersection = intersectionAxis.intersection(triangle);
    REQUIRE(intersection.exists());
    REQUIRE(intersection.isPoint());
    REQUIRE(intersection.point().distanceTo(triangle.plane()) == Zero());

    auto missingIntersection = missingAxis.intersection(triangle);
    REQUIRE_FALSE(missingIntersection.exists());   
}

TEST_CASE("Non-orthogonal plane transformation") {
    Plane3d original = Plane3d(Point3d(1, 0, 1), Vector3d(1, 0, 1).normalized());
    CoordinateSystem3d coordinateSystem = CoordinateSystem3d(
        Point3d::Origin(),
        Vector3d(2, 0, 0),
        Vector3d(0, 1, 0),
        Vector3d(0, 0, 1)
    );
    Plane3d transformed = coordinateSystem * original;
    REQUIRE((transformed.originPoint() - Point3d(2, 0, 1)).isZero());
    REQUIRE((transformed.normalVector() - Vector3d(1, 0, 2).normalized()).isZero());
}

TEST_CASE("Plane mirroring") {
    Plane3d original = Plane3d(Point3d(1, 0, 1), Vector3d(-1, 0, -2).normalized());
    Plane3d mirrored = original.mirroredAbout(Plane3d::xy());
    REQUIRE((mirrored.originPoint() - Point3d(1, 0, -1)).isZero());
    REQUIRE((mirrored.normalVector() - Vector3d(-1, 0, 2).normalized()).isZero());
}
