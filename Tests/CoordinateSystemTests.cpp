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
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

#include <catch/catch.hpp>

using namespace opensolid;

TEST_CASE("Transformation") {
    Frame3d global;
    Frame3d frame = global.translatedBy(Vector3d(1, 1, 1)).rotatedAbout(global.xAxis(), -M_PI / 2);
    CAPTURE(global.xAxis().originPoint());
    CAPTURE(global.xAxis().directionVector());
    CAPTURE(Point3d(1, 1, 1).rotatedAbout(global.xAxis(), -M_PI / 2));
    CAPTURE(frame.originPoint());
    CAPTURE(frame.directionVector(0));
    CAPTURE(frame.directionVector(1));
    CAPTURE(frame.directionVector(2));
    REQUIRE(Point3d(1, 2, 3).placedIn(frame).equals(Point3d(2, 4, -3)));
}

TEST_CASE("Composition") {
    Frame3d frame = Frame3d(Point3d(1, 0, 0));
    frame = frame.rotatedAbout(frame.yAxis(), -M_PI / 4);

    Frame3d globalized = frame.placedIn(frame);
    CAPTURE(globalized.originPoint());
    CAPTURE(globalized.xDirectionVector());
    CAPTURE(globalized.yDirectionVector());
    CAPTURE(globalized.zDirectionVector());
    Point3d expectedProductOrigin(1 + 1 / sqrt(2.0), 0, 1 / sqrt(2.0));

    REQUIRE(globalized.originPoint().equals(expectedProductOrigin));
    REQUIRE(globalized.xAxis().directionVector().equals(Vector3d(0, 0, 1)));
    REQUIRE(globalized.yAxis().directionVector().equals(Vector3d(0, 1, 0)));
    REQUIRE(globalized.zAxis().directionVector().equals(Vector3d(-1, 0, 0)));

    Frame3d localized = frame.relativeTo(frame);
    REQUIRE(localized.originPoint().isOrigin());
    REQUIRE(localized.basisMatrix().isIdentity());
}

TEST_CASE("2D") {
    Frame2d frame(Point2d(1, 0), Vector2d(1, 1).normalized(), Vector2d(1, 1).unitOrthogonal());

    REQUIRE(Point2d(2, 2).placedIn(frame).equals(Point2d(1, 2 * sqrt(2.0))));
    REQUIRE(Point2d(2, 1).relativeTo(frame).equals(Point2d(sqrt(2.0), 0)));
}

TEST_CASE("Planes") {
    REQUIRE(Point2d(5, 6).placedOnto(Plane3d::XY()).equals(Point3d(5, 6, 0)));
    REQUIRE(Point2d(1, 2).placedOnto(Plane3d::ZY()).equals(Point3d(0, 2, 1)));
}
