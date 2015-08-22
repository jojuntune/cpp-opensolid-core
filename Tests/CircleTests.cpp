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

#include <OpenSolid/Core/Circle.hpp>

#include <catch/catch.hpp>

using namespace opensolid;

TEST_CASE("Rotation") {
    SECTION("2D") {
        Circle2d original(Point2d(1, 1), 1.0);
        Circle2d rotated = original.rotatedAbout(Point2d::origin(), M_PI / 4.0);
        REQUIRE((rotated.centerPoint() - Point2d(0.0, sqrt(2.0))).isZero());
        REQUIRE((rotated.radius() - 1.0) == Zero());
    }
    SECTION("3D") {
        Circle3d original(Point3d(1.0, 0.0, 1.0), UnitVector3d::Z(), 1.0);
        Circle3d rotated = original.rotatedAbout(Axis3d::x(), M_PI / 2.0);
        REQUIRE((rotated.centerPoint() - Point3d(1.0, -1.0 , 0.0)).isZero());
        REQUIRE(rotated.normalVector().equals(-UnitVector3d::Y()));
        REQUIRE((rotated.radius() - 1.0) == Zero());
    }
}

TEST_CASE("Scaling") {
    SECTION("2D") {
        Circle2d original(Point2d::origin(), 1.0);
        Circle2d scaled = original.scaledAbout(Point2d(-1.0, -1.0), 2.0);
        REQUIRE((scaled.centerPoint() - Point2d(1.0, 1.0)).isZero());
        REQUIRE((scaled.radius() - 2.0) == Zero());
    }
    SECTION("3D") {
        Circle3d original(Point3d(1.0, 0.0, 1.0), UnitVector3d::Z(), 1.0);
        Circle3d scaled = original.scaledAbout(original.centerPoint(), 3.0);
        REQUIRE((scaled.centerPoint() - original.centerPoint()).isZero());
        REQUIRE(scaled.normalVector().equals(original.normalVector()));
        REQUIRE((scaled.radius() - 3.0) == Zero());
    }
}

TEST_CASE("Mirroring") {
    SECTION("2D") {
        Circle2d original(Point2d(0.0, 3.0), 2.0);
        Axis2d slopedAxis(Point2d::origin(), Vector2d(1.0, 1.0).normalized());
        Circle2d mirrored = original.mirroredAbout(slopedAxis);
        REQUIRE((mirrored.centerPoint() - Point2d(3.0, 0.0)).isZero());
        REQUIRE((mirrored.radius() - original.radius()) == Zero());
    }
    SECTION("3D") {
        Circle3d original(Point3d(1.0, 1.0, 1.0), Vector3d(1.0, 1.0, 1.0).normalized(), 1.0);
        Circle3d mirrored = original.mirroredAbout(Plane3d::xy());
        REQUIRE((mirrored.centerPoint() - Point3d(1.0, 1.0, -1.0)).isZero());
        REQUIRE(mirrored.normalVector().equals(Vector3d(1.0, 1.0, -1.0).normalized()));
        REQUIRE((mirrored.radius() - original.radius()) == Zero());
    }
}
