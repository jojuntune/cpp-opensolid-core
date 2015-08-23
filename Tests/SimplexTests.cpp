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

#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
#include <OpenSolid/Core/Tetrahedron.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <catch/catch.hpp>

using namespace opensolid;

struct MyPoint3d
{
    double x;
    double y;
    double z;

    MyPoint3d(double x_, double y_, double z_) :
        x(x_),
        y(y_),
        z(z_) {
    }
};

inline
bool
operator==(const MyPoint3d& myFirstPoint, const MyPoint3d& mySecondPoint) {
    return (
        myFirstPoint.x == mySecondPoint.x &&
        myFirstPoint.y == mySecondPoint.y &&
        myFirstPoint.z == mySecondPoint.z
    );
}

struct MyLineSegment3d
{
    MyPoint3d startPoint;
    MyPoint3d endPoint;

    MyLineSegment3d(const MyPoint3d& startPoint_, const MyPoint3d& endPoint_) :
        startPoint(startPoint_),
        endPoint(endPoint_) {
    }
};

inline
bool
operator==(const MyLineSegment3d& myFirstLineSegment, const MyLineSegment3d& mySecondLineSegment) {
    return (
        myFirstLineSegment.startPoint == mySecondLineSegment.startPoint &&
        myFirstLineSegment.endPoint == mySecondLineSegment.endPoint
    );
}

struct MyTriangle3d
{
    MyPoint3d point1;
    MyPoint3d point2;
    MyPoint3d point3;

    MyTriangle3d(const MyPoint3d& point1_, const MyPoint3d& point2_, const MyPoint3d& point3_) :
        point1(point1_),
        point2(point2_),
        point3(point3_) {
    }
};

inline
bool
operator==(const MyTriangle3d& myFirstTriangle, const MyTriangle3d& mySecondTriangle) {
    return ( 
        myFirstTriangle.point1 == mySecondTriangle.point1 &&
        myFirstTriangle.point2 == mySecondTriangle.point2 &&
        myFirstTriangle.point3 == mySecondTriangle.point3
    );
}

struct MyTetrahedron3d
{
    MyPoint3d point1;
    MyPoint3d point2;
    MyPoint3d point3;
    MyPoint3d point4;

    MyTetrahedron3d(
        const MyPoint3d& point1_,
        const MyPoint3d& point2_,
        const MyPoint3d& point3_,
        const MyPoint3d& point4_
    ) : point1(point1_),
        point2(point2_),
        point3(point3_),
        point4(point4_) {
    }
};

inline
bool
operator==(const MyTetrahedron3d& myFirstTetrahedron, const MyTetrahedron3d& mySecondTetrahedron) {
    return (
        myFirstTetrahedron.point1 == mySecondTetrahedron.point1 &&
        myFirstTetrahedron.point2 == mySecondTetrahedron.point2 &&
        myFirstTetrahedron.point3 == mySecondTetrahedron.point3 &&
        myFirstTetrahedron.point4 == mySecondTetrahedron.point4
    );
}

namespace opensolid
{
    template <>
    struct ConversionFunction<MyPoint3d, Point3d>
    {
        const Point3d
        operator()(const MyPoint3d& myPoint) const {
            return Point3d(myPoint.x, myPoint.y, myPoint.z);
        }
    };

    template <>
    struct ConversionFunction<Point3d, MyPoint3d>
    {
        const MyPoint3d
        operator()(const Point3d& point) const {
            return MyPoint3d(point.x(), point.y(), point.z());
        }
    };

    template <>
    struct ConversionFunction<MyLineSegment3d, LineSegment3d>
    {
        const LineSegment3d
        operator()(const MyLineSegment3d& myLineSegment) const {
            return LineSegment3d(
                Point3d::from(myLineSegment.startPoint),
                Point3d::from(myLineSegment.endPoint)
            );
        }
    };

    template <>
    struct ConversionFunction<LineSegment3d, MyLineSegment3d>
    {
        const MyLineSegment3d
        operator()(const LineSegment3d& lineSegment) const {
            return MyLineSegment3d(
                lineSegment.startVertex().to<MyPoint3d>(),
                lineSegment.endVertex().to<MyPoint3d>()
            );
        }
    };

    template <>
    struct ConversionFunction<MyTriangle3d, Triangle3d>
    {
        const Triangle3d
        operator()(const MyTriangle3d& myTriangle) const {
            return Triangle3d(
                Point3d::from(myTriangle.point1),
                Point3d::from(myTriangle.point2),
                Point3d::from(myTriangle.point3)
            );
        }
    };

    template <>
    struct ConversionFunction<Triangle3d, MyTriangle3d>
    {
        const MyTriangle3d
        operator()(const Triangle3d& triangle) const {
            return MyTriangle3d(
                triangle.vertex(0).to<MyPoint3d>(),
                triangle.vertex(1).to<MyPoint3d>(),
                triangle.vertex(2).to<MyPoint3d>()
            );
        }
    };

    template <>
    struct ConversionFunction<MyTetrahedron3d, Tetrahedron3d>
    {
        const Tetrahedron3d
        operator()(const MyTetrahedron3d& myTetrahedron) const {
            return Tetrahedron3d(
                Point3d::from(myTetrahedron.point1),
                Point3d::from(myTetrahedron.point2),
                Point3d::from(myTetrahedron.point3),
                Point3d::from(myTetrahedron.point4)
            );
        }
    };

    template <>
    struct ConversionFunction<Tetrahedron3d, MyTetrahedron3d>
    {
        const MyTetrahedron3d
        operator()(const Tetrahedron3d& tetrahedron) const {
            return MyTetrahedron3d(
                tetrahedron.vertex(0).to<MyPoint3d>(),
                tetrahedron.vertex(1).to<MyPoint3d>(),
                tetrahedron.vertex(2).to<MyPoint3d>(),
                tetrahedron.vertex(3).to<MyPoint3d>()
            );
        }
    };
}

TEST_CASE("Localization") {
    Triangle3d triangle3d(Point3d(1, 1, 1), Point3d(3, 1, 2), Point3d(2, 2, 4));

    Triangle2d xyComponents = triangle3d.projectedInto(Plane3d::XY());
    REQUIRE(xyComponents.vertex(0).isEqualTo(Point2d(1, 1)));
    REQUIRE(xyComponents.vertex(1).isEqualTo(Point2d(3, 1)));
    REQUIRE(xyComponents.vertex(2).isEqualTo(Point2d(2, 2)));
    double xyArea = xyComponents.area();
    REQUIRE(xyArea > 0.0);

    Triangle2d yzComponents = triangle3d.projectedInto(Plane3d::YZ());
    REQUIRE(yzComponents.vertex(0).isEqualTo(Point2d(1, 1)));
    REQUIRE(yzComponents.vertex(1).isEqualTo(Point2d(1, 2)));
    REQUIRE(yzComponents.vertex(2).isEqualTo(Point2d(2, 4)));
    double yzArea = yzComponents.area();
    REQUIRE(yzArea < 0.0);

    double xzArea = triangle3d.projectedInto(Plane3d::XZ()).area();

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
    REQUIRE(line.normalVector().equals(Vector2d(-1, 2).normalized()));
}

TEST_CASE("Triangle normal") {
    Triangle3d triangle(Point3d(1, 1, 1), Point3d(3, 1, 2), Point3d(2, 2, 4));
    UnitVector3d expectedNormal = Vector3d(2, 0, 1).cross(Vector3d(1, 1, 3)).normalized();
    REQUIRE(triangle.normalVector().equals(expectedNormal));
}

TEST_CASE("Projection") {
    Triangle3d triangle(Point3d::ORIGIN(), Point3d(2, 0, 0), Point3d(1, 2, 0));
    Point3d projection = Point3d(3, 4, 5).projectedOnto(triangle.plane());
    REQUIRE((projection - Point3d(3, 4, 0)).isZero());
}

TEST_CASE("Set") {
    std::vector<Triangle3d> triangles(3);
    triangles[0] = Triangle3d(Point3d::ORIGIN(), Point3d(1, 0, 0), Point3d(0, 1, 0));
    triangles[1] = Triangle3d(Point3d(2, 1, 0), Point3d(3, 0, 0), Point3d(3, 1, 0));
    triangles[2] = Triangle3d(Point3d(0, 0, 1), Point3d(1, 0, 1), Point3d(1, 1, 1));

    SpatialSet<Triangle3d> set(triangles);

    std::vector<Indexed<Triangle3d>> overlapping = set.overlapping(triangles[0].bounds());
    REQUIRE(overlapping.size() == 1u);
    REQUIRE(overlapping.front() == triangles[0]);
    REQUIRE(overlapping.front().index() == 0);
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
    double circumference = Triangle2d::UNIT().edges().fold(0.0, lengthAccumulator);
    REQUIRE((circumference - (2.0 + sqrt(2.0))) == Zero());
}

TEST_CASE("Tetrahedron vertices") {
    auto pointIsOrigin = [] (const Point3d& point) {
        return point.isOrigin();
    };
    REQUIRE(Tetrahedron3d::UNIT().vertices().where(pointIsOrigin).size() == 1);
}

TEST_CASE("Tetrahedron edges") {
    double totalLength = Tetrahedron3d::UNIT().edges().fold(
        0.0,
        [] (double lengthSoFar, const LineSegment3d& edge) {
            return lengthSoFar + edge.length();
        }
    );
    REQUIRE((totalLength - (3 + 3 * sqrt(2.0))) == Zero());
}

TEST_CASE("Tetrahedron faces") {
    double totalArea = Tetrahedron3d::UNIT().faces().fold(
        0.0,
        [] (double areaSoFar, const Triangle3d& face) {
            return areaSoFar + face.area();
        }
    );
    REQUIRE((totalArea - (1.5 + 3 / (2 * sqrt(3.0)))) == Zero());
}

TEST_CASE("Line segment/plane intersection") {
    Plane3d plane(Point3d(0, 0, 1), UnitVector3d::Z());

    LineSegment3d firstSegment(Point3d(0, 0, 2), Point3d(2, 2, 2));
    LineSegment3d secondSegment(Point3d(0, 0, 1), Point3d(1, 1, 1));
    LineSegment3d thirdSegment(Point3d::ORIGIN(), Point3d(2, 2, 2));

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

    CAPTURE(detail::crossProduct2d(triangle.vertex(0), triangle.vertex(2), triangle.vertex(1)));
    CAPTURE(detail::crossProduct2d(triangle.vertex(1), triangle.vertex(0), triangle.vertex(2)));
    CAPTURE(detail::crossProduct2d(triangle.vertex(2), triangle.vertex(1), triangle.vertex(0)));

    REQUIRE(triangle.contains(triangle.vertex(2)));
    REQUIRE(triangle.contains(triangle.centroid()));
    REQUIRE(triangle.contains(triangle.centroid()));
    REQUIRE_FALSE(triangle.contains(Point2d::ORIGIN()));
}

// TEST_CASE("Tetrahedron containment") {
//     Tetrahedron3d tetrahedron = Tetrahedron3d::unit();

//     REQUIRE(tetrahedron.contains(tetrahedron.vertex(2)));
//     REQUIRE(tetrahedron.contains(tetrahedron.centroid()));
//     REQUIRE(tetrahedron.contains(tetrahedron.centroid(), -1e-12));
//     REQUIRE_FALSE(tetrahedron.contains(tetrahedron.vertex(2), -1e-12));
//     REQUIRE(tetrahedron.contains(Point3d::ORIGIN()));
//     REQUIRE_FALSE(tetrahedron.contains(Point3d::ORIGIN(), -1e-12));
// }

TEST_CASE("Line segment conversion") {
    MyLineSegment3d initial = MyLineSegment3d(MyPoint3d(1, 0, 1), MyPoint3d(2, 0, 2));
    LineSegment3d converted = LineSegment3d::from(initial);
    MyLineSegment3d final = converted.to<MyLineSegment3d>();

    REQUIRE((converted.squaredLength() - 2) == Zero());
    REQUIRE(initial == final);
}

TEST_CASE("Triangle conversion") {
    MyTriangle3d initial = MyTriangle3d(MyPoint3d(1, 1, 0), MyPoint3d(2, 1, 0), MyPoint3d(1, 2, 0));
    Triangle3d converted = Triangle3d::from(initial);
    MyTriangle3d final = converted.to<MyTriangle3d>();

    REQUIRE((converted.area() - 0.5) == Zero());
    REQUIRE(initial == final);
}

TEST_CASE("Tetrahedron conversion") {
    Tetrahedron3d initial = Tetrahedron3d::UNIT();
    MyTetrahedron3d converted = initial.to<MyTetrahedron3d>();
    MyTetrahedron3d expected = MyTetrahedron3d(
        MyPoint3d(0, 0, 0),
        MyPoint3d(1, 0, 0),
        MyPoint3d(0, 1, 0),
        MyPoint3d(0, 0, 1)
    );
    Tetrahedron3d final = Tetrahedron3d::from(converted);

    REQUIRE(converted == expected);
    REQUIRE(initial == final);
}
