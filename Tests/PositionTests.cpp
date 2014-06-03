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
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

#include <catch/catch.hpp>

using namespace opensolid;

TEST_CASE("Transformation") {
    Point3d point(3, 2, 1);
    REQUIRE((point.rotatedAbout(Axis3d::Z(), M_PI / 2) - Point3d(-2, 3, 1)).isZero());
    REQUIRE((point.rotatedAbout(Axis3d::X(), M_PI / 2) - Point3d(3, -1, 2)).isZero());
    REQUIRE((point.mirroredAbout(Plane3d::YZ()) - Point3d(-3, 2, 1)).isZero());
}

TEST_CASE("Points") {
    Point3d point1(1, 2, 3);
    Point3d point2(Vector3d(1, 2, 3));
    Point3d point3(4, 5, 6);
    Point3d origin = Point3d::Origin();
    REQUIRE((point1 - point2).isZero());
    REQUIRE(origin.components().isZero());
    REQUIRE(origin.isOrigin());
    REQUIRE((point1 + Vector3d(3, 3, 3) - point3).isZero());
    REQUIRE((point1.rotatedAbout(Axis3d::X(), M_PI / 2) - Point3d(1, -3, 2)).isZero());
}

TEST_CASE("Boxes") {
    Box3d box1(Interval(1, 2), Interval(3, 4), Interval(5, 6));
    Box3d projected = box1.projectedOnto(Plane3d::YZ());
    REQUIRE(projected.x().lowerBound() == Zero());
    REQUIRE(projected.x().upperBound() == Zero());
    REQUIRE((projected.y().lowerBound() - box1.y().lowerBound()) == Zero());
    REQUIRE((projected.y().upperBound() - box1.y().upperBound()) == Zero());
    REQUIRE((projected.z().lowerBound() - box1.z().lowerBound()) == Zero());
    REQUIRE((projected.z().upperBound() - box1.z().upperBound()) == Zero());
}

TEST_CASE("Mixed operations") {
    Point3d point(1, 2, 3);
    Box3d box(Interval(1, 2), Interval(3, 4), Interval(5, 6));
    IntervalVector3d difference1 = point - box;
    IntervalVector3d difference2 = box - point;
    Box3d reconstructed1 = point - difference1;
    Box3d reconstructed2 = point + difference2;
    for (int i = 0; i < 3; ++i) {
        REQUIRE((reconstructed1(i).lowerBound() - box(i).lowerBound()) == Zero());
        REQUIRE((reconstructed1(i).upperBound() - box(i).upperBound()) == Zero());
        REQUIRE((reconstructed2(i).lowerBound() - box(i).lowerBound()) == Zero());
        REQUIRE((reconstructed2(i).upperBound() - box(i).upperBound()) == Zero());
    }
}

TEST_CASE("Distance") {
    Point2d point2d(0, 2);
    Axis2d axis2d(Point2d(1, 1), Vector2d(1, 1).normalized());
    REQUIRE((point2d.distanceTo(axis2d) - sqrt(2.0)) == Zero());

    Point3d point3d(2, 2, 0);
    Plane3d plane3d(Point3d(0, 0, 1), Vector3d(-1, -1, 1).normalized());
    REQUIRE((point3d.distanceTo(plane3d) + 5.0 / sqrt(3.0)) == Zero());
}

TEST_CASE("Box vertices") {
    Box3d box(Interval(1, 2), Interval(3, 4), Interval(5, 6));
    auto pointIsContained = [&box] (const Point3d& point) {
        return box.contains(point);
    };
    auto pointIsStrictlyContained = [&box] (const Point3d& point) {
        return box.strictlyContains(point);
    };
    REQUIRE(box.vertices().all(pointIsContained));
    REQUIRE(!box.vertices().any(pointIsStrictlyContained));

    Box3d computedBox = box.vertices().fold(
        Box3d(),
        [] (const Box3d& result, const Point3d& point) {
            return result.hull(point);
        }
    );
    REQUIRE(computedBox.contains(box));
    REQUIRE(box.contains(computedBox));

    REQUIRE(box.vertex(0) == box.minVertex());
    REQUIRE(box.vertex(7) == box.maxVertex());
}

TEST_CASE("Box interpolation") {
    Box3d box(Interval(1, 2), Interval(3, 4), Interval(5, 6));
    REQUIRE((box.interpolated(0.5, 0.5, 0.5) - Point3d(1.5, 3.5, 5.5)).isZero());
    REQUIRE((box.interpolated(0.0, 0.0, 0.0) - Point3d(1, 3, 5)).isZero());
    Box3d wholeBox = box.interpolated(Interval::Unit(), Interval::Unit(), Interval::Unit());
    REQUIRE(wholeBox.contains(box));
    REQUIRE(box.contains(wholeBox));
}

TEST_CASE("2D point predicates") {
    Axis2d axis(Point2d(1, 1), Vector2d(2, 1).normalized());
    LineSegment2d lineSegment(Point2d(0, 1), Point2d(1, 0));

    REQUIRE(axis.contains(Point2d(3, 2)));
    REQUIRE_FALSE(axis.contains(Point2d(3, 3)));

    REQUIRE(lineSegment.contains(Point2d(0.5, 0.5)));
    REQUIRE(lineSegment.contains(Point2d(0, 1)));
    REQUIRE_FALSE(lineSegment.contains(Point2d(-1, 2)));
    REQUIRE_FALSE(lineSegment.contains(Point2d(1, 1)));
}

TEST_CASE("3D point predicates") {
    Axis3d axis(Point3d(1, 1, 1), Vector3d(1, 2, 3).normalized());
    Plane3d plane(Point3d(0, 1, 1), Vector3d(0, 1, 1).normalized());
    LineSegment3d lineSegment(Point3d(0, 0, 1), Point3d(1, 1, 0));
    Triangle3d triangle(Point3d(1, 0, 0), Point3d(0, 1, 0), Point3d(0, 0, 1));

    REQUIRE(axis.contains(Point3d(2, 3, 4)));
    REQUIRE_FALSE(axis.contains(Point3d(2, 3, 5)));

    REQUIRE(plane.contains(Point3d(0, 0, 2)));
    REQUIRE_FALSE(plane.contains(Point3d::Origin()));

    REQUIRE(lineSegment.contains(lineSegment.centroid()));
    REQUIRE(lineSegment.contains(lineSegment.endVertex()));
    Point3d extendedPoint(2, 2, -1);
    REQUIRE(lineSegment.axis().contains(extendedPoint));
    REQUIRE_FALSE(lineSegment.contains(extendedPoint));

    REQUIRE(triangle.contains(triangle.centroid()));
    REQUIRE(triangle.contains(triangle.vertex(1)));
    Point3d planarPoint(-1, 0, 2);
    REQUIRE(triangle.plane().contains(planarPoint));
    REQUIRE_FALSE(triangle.contains(planarPoint));
    REQUIRE_FALSE(triangle.contains(Point3d(1, 1, 1)));
}

TEST_CASE("Hull") {
    Point3d point1(1, 2, 3);
    Point3d point2(4, 5, 6);
    Box3d box1(Interval(0, 1), Interval(2, 3), Interval(4, 5));
    Box3d box2(Interval(-1, 0), Interval(-3, -2), Interval(-5, -4));

    SECTION("Point-point") {
        Box3d hull = point1.hull(point2);
        REQUIRE(hull.x().lowerBound() == 1);
        REQUIRE(hull.x().upperBound() == 4);
        REQUIRE(hull.y().lowerBound() == 2);
        REQUIRE(hull.y().upperBound() == 5);
        REQUIRE(hull.z().lowerBound() == 3);
        REQUIRE(hull.z().upperBound() == 6);
    }

    SECTION("Point-box") {
        Box3d hull = point1.hull(box2);
        REQUIRE(hull.x().lowerBound() == -1);
        REQUIRE(hull.x().upperBound() == 1);
        REQUIRE(hull.y().lowerBound() == -3);
        REQUIRE(hull.y().upperBound() == 2);
        REQUIRE(hull.z().lowerBound() == -5);
        REQUIRE(hull.z().upperBound() == 3);
    }

    SECTION("Box-point") {
        Box3d hull = box1.hull(point2);
        REQUIRE(hull.x().lowerBound() == 0);
        REQUIRE(hull.x().upperBound() == 4);
        REQUIRE(hull.y().lowerBound() == 2);
        REQUIRE(hull.y().upperBound() == 5);
        REQUIRE(hull.z().lowerBound() == 4);
        REQUIRE(hull.z().upperBound() == 6);
    }

    SECTION("Box-box") {
        Box3d hull = box1.hull(box2);
        REQUIRE(hull.x().lowerBound() == -1);
        REQUIRE(hull.x().upperBound() == 1);
        REQUIRE(hull.y().lowerBound() == -3);
        REQUIRE(hull.y().upperBound() == 3);
        REQUIRE(hull.z().lowerBound() == -5);
        REQUIRE(hull.z().upperBound() == 5);
    }
}
