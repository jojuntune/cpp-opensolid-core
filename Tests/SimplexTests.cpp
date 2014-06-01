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

#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
#include <OpenSolid/Core/Tetrahedron.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <catch/catch.hpp>

using namespace opensolid;

TEST_CASE("Localization") {
    Triangle3d triangle3d(Point3d(1, 1, 1), Point3d(3, 1, 2), Point3d(2, 2, 4));
    PlanarCoordinateSystem3d xyCoordinateSystem(
        Point3d::Origin(),
        UnitVector3d::i(),
        UnitVector3d::j()
    );
    PlanarCoordinateSystem3d yzCoordinateSystem(
        Point3d::Origin(),
        UnitVector3d::j(),
        UnitVector3d::k()
    );
    PlanarCoordinateSystem3d xzCoordinateSystem(
        Point3d::Origin(),
        UnitVector3d::i(),
        UnitVector3d::k()
    );

    Triangle2d xyComponents = triangle3d / xyCoordinateSystem;
    REQUIRE((xyComponents.vertex(0) - Point2d(1, 1)).isZero());
    REQUIRE((xyComponents.vertex(1) - Point2d(3, 1)).isZero());
    REQUIRE((xyComponents.vertex(2) - Point2d(2, 2)).isZero());
    double xyArea = xyComponents.area();
    REQUIRE(xyArea > 0.0);

    Triangle2d yzComponents = triangle3d / yzCoordinateSystem;
    REQUIRE((yzComponents.vertex(0) - Point2d(1, 1)).isZero());
    REQUIRE((yzComponents.vertex(1) - Point2d(1, 2)).isZero());
    REQUIRE((yzComponents.vertex(2) - Point2d(2, 4)).isZero());
    double yzArea = yzComponents.area();
    REQUIRE(yzArea < 0.0);

    double xzArea = (triangle3d / xzCoordinateSystem).area();

    double areaFromComponents = sqrt(xyArea * xyArea + yzArea * yzArea + xzArea * xzArea);
    REQUIRE((triangle3d.area() - areaFromComponents) == Zero());
}

TEST_CASE("Volumes") {
    Tetrahedron3d tetrahedron(
        Point3d(1, 1, 1),
        Point3d(2, 1, 1),
        Point3d(1, 2, 1),
        Point3d(1, 1, 2)
    );

    REQUIRE((tetrahedron.volume() - 1.0 / 6.0) == Zero());
    REQUIRE((tetrahedron.face(1).area() - 0.5) == Zero());
}

TEST_CASE("Tetrahedron centroid") {
    Tetrahedron3d tetrahedron(
        Point3d(1, 1, 1),
        Point3d(2, 1, 1),
        Point3d(1, 2, 1),
        Point3d(1, 1, 2)
    );
    REQUIRE((tetrahedron.centroid() - Point3d(1.25, 1.25, 1.25)).isZero());
}

TEST_CASE("Triangle centroid") {
    Triangle2d triangle(Point2d(1, 1), Point2d(2, 2), Point2d(1, 3));
    REQUIRE((triangle.centroid() - Point2d(4.0 / 3.0, 2)).isZero());
}

TEST_CASE("Line normal") {
    LineSegment2d line(Point2d(1, 1), Point2d(3, 2));
    REQUIRE((line.normalVector() - Vector2d(-1, 2).normalized()).isZero());
}

TEST_CASE("Triangle normal") {
    Triangle3d triangle(Point3d(1, 1, 1), Point3d(3, 1, 2), Point3d(2, 2, 4));
    UnitVector3d expectedNormal = Vector3d(2, 0, 1).cross(Vector3d(1, 1, 3)).normalized();
    REQUIRE((triangle.normalVector() - expectedNormal).isZero());
}

TEST_CASE("Coordinate system") {
    Triangle3d triangle(Point3d::Origin(), Point3d(2, 0, 0), Point3d(1, 2, 0));
    PlanarCoordinateSystem3d coordinateSystem = triangle.coordinateSystem();

    Point3d globalized = coordinateSystem * Point2d(0.5, 0.5);
    REQUIRE((globalized - Point3d(1.5, 1, 0)).isZero());

    Point2d localized = Point3d(1, 0, 0) / coordinateSystem;
    REQUIRE((localized - Point2d(0.5, 0)).isZero());

    localized = Point3d(3, 2, 0) / coordinateSystem;
    REQUIRE((localized - Point2d(1, 1)).isZero());

    Point3d projection = Point3d(3, 4, 5).projectedOnto(triangle.plane());
    REQUIRE((projection - Point3d(3, 4, 0)).isZero());
}

TEST_CASE("1D line segment") {
    LineSegment3d lineSegment3d(Point3d(1, 2, 3), Point3d(4, 5, 6));
    AxialCoordinateSystem3d axialCoordinateSystem(Point3d::Origin(), UnitVector3d::j());
    
    LineSegment1d localized = lineSegment3d / axialCoordinateSystem;
    REQUIRE((localized.startVertex() - Point1d(2)).isZero());
    REQUIRE((localized.endVertex() - Point1d(5)).isZero());

    LineSegment3d globalized = lineSegment3d.coordinateSystem() *
        LineSegment1d(Point1d(1.0 / 3.0), Point1d(2.0 / 3.0));
    REQUIRE((globalized.startVertex() - Point3d(2, 3, 4)).isZero());
    REQUIRE((globalized.endVertex() - Point3d(3, 4, 5)).isZero());
}

TEST_CASE("Set") {
    std::vector<Triangle3d> triangles(3);
    triangles[0] = Triangle3d(Point3d::Origin(), Point3d(1, 0, 0), Point3d(0, 1, 0));
    triangles[1] = Triangle3d(Point3d(2, 1, 0), Point3d(3, 0, 0), Point3d(3, 1, 0));
    triangles[2] = Triangle3d(Point3d(0, 0, 1), Point3d(1, 0, 1), Point3d(1, 1, 1));

    SpatialSet<Triangle3d> set(triangles);

    std::vector<Triangle3d> overlapping = set.overlapping(triangles[0].bounds());
    REQUIRE(overlapping.size() == 1u);
    REQUIRE(overlapping.front() == triangles[0]);
}

TEST_CASE("Vector") {
    LineSegment3d lineSegment(Point3d(1, 2, 3), Point3d(4, 5, 6));
    REQUIRE((lineSegment.vector() - Vector3d(3, 3, 3)).isZero());
}

TEST_CASE("Scaling") {
    Triangle2d triangle(Point2d(2, 2), Point2d(4, 2), Point2d(3, 3));
    Triangle2d scaled = triangle.scaledAbout(Point2d(1, 1), 2.0);
    REQUIRE((scaled.vertex(0) - Point2d(3, 3)).isZero());
    REQUIRE((scaled.vertex(1) - Point2d(7, 3)).isZero());
    REQUIRE((scaled.vertex(2) - Point2d(5, 5)).isZero());
}

TEST_CASE("Line segment vertices") {
    LineSegment3d lineSegment(Point3d(1, 2, 3), Point3d(-4, -5, -6));
    REQUIRE(lineSegment.vertices().size() == 2);

    std::vector<Point3d> vertices = lineSegment.vertices();
    REQUIRE(vertices.size() == 2u);
    REQUIRE(vertices[0] == Point3d(1, 2, 3));
    REQUIRE(vertices[1] == Point3d(-4, -5, -6));
}

TEST_CASE("Triangle vertices") {
    Triangle3d triangle(Point3d(1, 1, -1), Point3d(3, 0, 2), Point3d(1, 2, 1));
    auto hasPositiveZ = [] (const Point3d& point) {
        return point.z() > Zero();
    };
    REQUIRE(triangle.vertices().any(hasPositiveZ));
    REQUIRE_FALSE(triangle.vertices().all(hasPositiveZ));
    REQUIRE(triangle.vertices().where(hasPositiveZ).size() == 2);
}

TEST_CASE("Triangle edges") {
    auto lengthAccumulator = [] (double lengthSoFar, const LineSegment2d& edge) {
        return lengthSoFar + edge.length();
    };
    double circumference = Triangle2d::unit().edges().fold(0.0, lengthAccumulator);
    REQUIRE((circumference - (2.0 + sqrt(2.0))) == Zero());
}

TEST_CASE("Tetrahedron vertices") {
    auto pointIsOrigin = [] (const Point3d& point) {
        return point.isOrigin();
    };
    REQUIRE(Tetrahedron3d::unit().vertices().where(pointIsOrigin).size() == 1);
}

TEST_CASE("Tetrahedron edges") {
    double totalLength = Tetrahedron3d::unit().edges().fold(
        0.0,
        [] (double lengthSoFar, const LineSegment3d& edge) {
            return lengthSoFar + edge.length();
        }
    );
    REQUIRE((totalLength - (3 + 3 * sqrt(2.0))) == Zero());
}

TEST_CASE("Tetrahedron faces") {
    double totalArea = Tetrahedron3d::unit().faces().fold(
        0.0,
        [] (double areaSoFar, const Triangle3d& face) {
            return areaSoFar + face.area();
        }
    );
    REQUIRE((totalArea - (1.5 + 3 / (2 * sqrt(3.0)))) == Zero());
}

TEST_CASE("Line segment/plane intersection") {
    Plane3d plane(Point3d(0, 0, 1), UnitVector3d::k());

    LineSegment3d firstSegment(Point3d(0, 0, 2), Point3d(2, 2, 2));
    LineSegment3d secondSegment(Point3d(0, 0, 1), Point3d(1, 1, 1));
    LineSegment3d thirdSegment(Point3d::Origin(), Point3d(2, 2, 2));

    auto firstIntersection = firstSegment.intersection(plane);
    auto secondIntersection = secondSegment.intersection(plane);
    auto thirdIntersection = thirdSegment.intersection(plane);

    REQUIRE_FALSE(firstIntersection.exists());
    REQUIRE(secondIntersection.isCoincident());
    
    REQUIRE(thirdIntersection.isPoint());
    REQUIRE((thirdIntersection.point() - Point3d(1, 1, 1)).isZero());
}

TEST_CASE("Triangle containment") {
    Triangle2d triangle(Point2d(1, 1), Point2d(3, 1), Point2d(2, 2));

    REQUIRE(triangle.contains(triangle.vertex(2)));
    REQUIRE(triangle.contains(triangle.centroid()));
    REQUIRE(triangle.strictlyContains(triangle.centroid()));
    REQUIRE_FALSE(triangle.strictlyContains(triangle.vertex(2)));
    REQUIRE_FALSE(triangle.contains(Point2d::Origin()));
    REQUIRE_FALSE(triangle.strictlyContains(Point2d::Origin()));
}

TEST_CASE("Tetrahedron containment") {
    Tetrahedron3d tetrahedron = Tetrahedron3d::unit();

    REQUIRE(tetrahedron.contains(tetrahedron.vertex(2)));
    REQUIRE(tetrahedron.contains(tetrahedron.centroid()));
    REQUIRE(tetrahedron.strictlyContains(tetrahedron.centroid()));
    REQUIRE_FALSE(tetrahedron.strictlyContains(tetrahedron.vertex(2)));
    REQUIRE(tetrahedron.contains(Point3d::Origin()));
    REQUIRE_FALSE(tetrahedron.strictlyContains(Point3d::Origin()));
}
