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
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>

#include <boost/timer.hpp>
#include <catch/catch.hpp>

#include <iterator>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace opensolid;

template <class TItem>
void testSet(const detail::SpatialSetNode<TItem>* nodePtr) {
    if (!nodePtr) {
        return;
    } else if (nodePtr->leftChildPtr) {
        const detail::SpatialSetNode<TItem>* leftChildPtr = nodePtr->leftChildPtr;
        const detail::SpatialSetNode<TItem>* rightChildPtr = nodePtr->leftChildPtr->nextPtr;
        REQUIRE_FALSE(leftChildPtr == NULL);
        REQUIRE_FALSE(rightChildPtr == NULL);
        REQUIRE(nodePtr->bounds.contains(leftChildPtr->bounds));
        REQUIRE(nodePtr->bounds.contains(rightChildPtr->bounds));
        testSet(leftChildPtr);
        testSet(rightChildPtr);
    }
}

Interval randomInterval() {
    double mid = 10 * double(rand()) / RAND_MAX;
    double width = double(rand()) / RAND_MAX;
    return Interval(mid - width / 2, mid + width / 2);
}

IntervalVector3d randomVector() {
    return IntervalVector3d(randomInterval(), randomInterval(), randomInterval());
}

TEST_CASE("Integer") {
    std::vector<double> list(5);
    list[0] = 3;
    list[1] = 1;
    list[2] = 7;
    list[3] = 2;
    list[4] = 5;
    SpatialSet<double> set(list.begin(), list.end());
    testSet(set.rootNode());

    std::vector<double> expected(list);
    std::sort(expected.begin(), expected.end());

    std::vector<double> actual = set.filtered(
        [] (Interval bounds) -> bool {
            return true;
        }
    );

    REQUIRE(actual == expected);
}

TEST_CASE("Interval") {
    std::vector<Interval> list(2);
    list[0] = Interval(1, 2);
    list[1] = Interval(0, 2);
    SpatialSet<Interval> set(list.begin(), list.end());
    testSet(set.rootNode());
}

TEST_CASE("Interval 2") {
    std::vector<Interval> list;
    list.push_back(Interval(0, 2));
    list.push_back(Interval(1, 2));
    SpatialSet<Interval> set(list.begin(), list.end());
    testSet(set.rootNode());
}

TEST_CASE("Interval 3") {
    std::vector<Interval> list(3);
    list[0] = Interval(0, 1);
    list[1] = Interval(0, 4);
    list[2] = Interval(0, 2);
    SpatialSet<Interval> set(list.begin(), list.end());
    testSet(set.rootNode());
}

TEST_CASE("2D interval vector") {
    std::vector<IntervalVector2d> list(5);
    list[0] = IntervalVector2d(Interval(1, 6), Interval(4, 5));
    list[1] = IntervalVector2d(Interval(2, 5), Interval(5, 7));
    list[2] = IntervalVector2d(Interval(4, 7), Interval(3, 6));
    list[3] = IntervalVector2d(Interval(6, 9), Interval(5, 8));
    list[4] = IntervalVector2d(Interval(8, 10), Interval(2, 6));
    SpatialSet<IntervalVector2d> set(list.begin(), list.end());
    testSet(set.rootNode());
}

TEST_CASE("Double overlapping") {
    std::vector<double> list(5);
    list[0] = 5;
    list[1] = 3;
    list[2] = 1;
    list[3] = 4;
    list[4] = 2;
    SpatialSet<double> set(list);
    std::vector<double> overlapping = set.overlapping(Interval(2.5, 4.5));
    REQUIRE(overlapping.size() == 2u);
    REQUIRE(overlapping.front() == 3);
    REQUIRE(overlapping.back() == 4);
}

TEST_CASE("2D vector overlapping") {
    std::vector<Vector2d> list(4);
    list[0] = Vector2d(1, 1);
    list[1] = Vector2d(5, 1);
    list[2] = Vector2d(1, 3);
    list[3] = Vector2d(5, 3);
    SpatialSet<Vector2d> set(list.begin(), list.end());
    std::vector<Vector2d> check = set.overlapping(
        IntervalVector2d(Interval(1, 5), Interval(2, 4))
    );
    REQUIRE(check.size() == 2u);
    REQUIRE(check[0] == Vector2d(1, 3));
    REQUIRE(check[1] == Vector2d(5, 3));
}

TEST_CASE("3D point") {
    std::vector<Point3d> pointList(3);
    pointList[0] = Point3d(1, 2, 3);
    pointList[1] = Point3d(4, 5, 6);
    pointList[2] = Point3d(2, 4, 6);

    SpatialSet<Point3d> pointSet(pointList);
    Box3d testBox(Interval(1, 3), Interval(1, 5), Interval(1, 7));
    std::vector<Point3d> overlappingPoints = pointSet.overlapping(testBox);
    std::sort(
        overlappingPoints.begin(),
        overlappingPoints.end(),
        [] (const Point3d& firstPoint, const Point3d& secondPoint) {
            return firstPoint.x() < secondPoint.x();
        }
    );
    REQUIRE(overlappingPoints.size() == 2);
    REQUIRE(overlappingPoints[0] == Point3d(1, 2, 3));
    REQUIRE(overlappingPoints[1] == Point3d(2, 4, 6));
}

TEST_CASE("Point set transformation") {
    std::vector<Point3d> pointList(3);
    pointList[0] = Point3d(1, -1, 1);
    pointList[1] = Point3d(1, 0, 1);
    pointList[2] = Point3d(1, 1, 1);

    SpatialSet<Point3d> pointSet(pointList);
    Axis3d rotationAxis(Point3d(1, 0, 0), UnitVector3d::k());
    std::vector<Point3d> rotatedPoints = pointSet.map(Rotation3d(rotationAxis, M_PI / 2));

    REQUIRE((rotatedPoints[0] - Point3d(2, 0, 1)).isZero());
    REQUIRE((rotatedPoints[1] - Point3d(1, 0, 1)).isZero());
    REQUIRE((rotatedPoints[2] - Point3d(0, 0, 1)).isZero());
}

TEST_CASE("Vector set transformation") {
    std::vector<Vector3d> vectorList(3);
    vectorList[0] = Vector3d(1, -1, 1);
    vectorList[1] = Vector3d(1, 0, 1);
    vectorList[2] = Vector3d(1, 1, 1);

    SpatialSet<Vector3d> vectorSet(vectorList);
    Axis3d rotationAxis(Point3d(1, 0, 0), UnitVector3d::k());
    std::vector<Vector3d> rotatedVectors = vectorSet.map(Rotation3d(rotationAxis, M_PI / 2));

    REQUIRE((rotatedVectors[0] - Vector3d(1, 1, 1)).isZero());
    REQUIRE((rotatedVectors[1] - Vector3d(0, 1, 1)).isZero());
    REQUIRE((rotatedVectors[2] - Vector3d(-1, 1, 1)).isZero());
}

TEST_CASE("Swap") {
    std::vector<double> firstValues(3);
    firstValues[0] = 1;
    firstValues[1] = 2;
    firstValues[2] = 3;
    SpatialSet<double> firstSet(firstValues);

    std::vector<double> secondValues(2);
    secondValues[0] = 4;
    secondValues[1] = 5;
    SpatialSet<double> secondSet(secondValues);

    firstSet.swap(secondSet);

    REQUIRE(firstSet.size() == 2u);
    REQUIRE(secondSet.size() == 3u);
    REQUIRE(firstSet[0] == 4);
    REQUIRE(secondSet[0] == 1);
}

TEST_CASE("Rvalue") {
    std::vector<double> values(3);
    values[0] = 1;
    values[1] = 2;
    values[2] = 3;

    SpatialSet<double> set1(values);
    const detail::SpatialSetNode<double>* rootNodePtr = set1.rootNode();

    SpatialSet<double> set2(std::move(set1));

    REQUIRE(set1.size() == 0u);
    REQUIRE(set2.size() == 3u);
    REQUIRE(set1.rootNode() == NULL);
    REQUIRE(set2.rootNode() == rootNodePtr);

    SpatialSet<double> set3;
    set3 = std::move(set2);

    REQUIRE(set2.size() == 0u);
    REQUIRE(set3.size() == 3u);
    REQUIRE(set2.rootNode() == NULL);
    REQUIRE(set3.rootNode() == rootNodePtr);
}

TEST_CASE("Unique") {
    std::vector<Point2d> originalPoints(3);
    originalPoints[0] = Point2d(2, 1);
    originalPoints[1] = Point2d(2, 2);
    originalPoints[2] = Point2d(1, 2);

    std::vector<Point2d> rotatedPoints(6);
    std::transform(
        originalPoints.begin(),
        originalPoints.end(),
        rotatedPoints.begin(),
        [] (const Point2d& point) {
            return point.rotatedAbout(Point2d::Origin(), 2 * M_PI / 3);
        }
    );
    std::transform(
        originalPoints.begin(),
        originalPoints.end(),
        rotatedPoints.begin() + 3,
        [] (const Point2d& point) {
            return point.rotatedAbout(Point2d::Origin(), -4 * M_PI / 3);
        }
    );

    std::vector<Point2d> testPoints(8);
    std::transform(
        rotatedPoints.begin(),
        rotatedPoints.end(),
        testPoints.begin(),
        [] (const Point2d& point) {
            return point.rotatedAbout(Point2d::Origin(), 10 * M_PI / 3);
        }
    );
    testPoints[6] = Point2d(2 + 1e-14, 2 + 1e-14);
    testPoints[7] = Point2d(0, 2);

    std::vector<Point2d> uniquePointsTolerant = SpatialSet<Point2d>(testPoints).uniqueItems();
    std::vector<Point2d> uniquePointsExact = SpatialSet<Point2d>(testPoints).uniqueItems(0.0);

    REQUIRE(uniquePointsTolerant.size() == 4);
    REQUIRE(uniquePointsTolerant.size() < uniquePointsExact.size());

    std::vector<Point2d> sortedPoints = uniquePointsTolerant;
    std::sort(
        sortedPoints.begin(),
        sortedPoints.end(),
        [] (const Point2d& firstPoint, const Point2d& secondPoint) {
            return (firstPoint.y() - firstPoint.x()) < (secondPoint.y() - secondPoint.x());
        }
    );

    REQUIRE((sortedPoints[0] - Point2d(2, 1)).isZero());
    REQUIRE((sortedPoints[1] - Point2d(2, 2)).isZero());
    REQUIRE((sortedPoints[2] - Point2d(1, 2)).isZero());
    REQUIRE((sortedPoints[3] - Point2d(0, 2)).isZero());
}

TEST_CASE("Unique mapping") {
    std::vector<double> values(5);
    values[0] = 1.0;
    values[1] = 2.0;
    values[2] = 2.0 + 1e-14;
    values[3] = 3.0;
    values[4] = 3.0;

    std::vector<std::size_t> mapping;
    std::vector<double> uniqueItems = SpatialSet<double>(values).uniqueItems(mapping);

    REQUIRE(mapping.size() == 5);
    REQUIRE(mapping[0] == 0);
    REQUIRE(mapping[1] == 1);
    REQUIRE(mapping[2] == 1);
    REQUIRE(mapping[3] == 2);
    REQUIRE(mapping[4] == 2);
}

TEST_CASE("Unique points") {
    std::vector<Point3d> points(6);
    points[0] = Point3d(6.6731209754944, 2, -17.180282592773);
    points[1] = Point3d(6.6731209754944, 2, -9.1802825927734);
    points[2] = Point3d(14.673119544983, 2, -9.1802825927734);
    points[3] = Point3d(6.6731209754944, 2, -17.180282592773);
    points[4] = Point3d(14.673119544983, 2, -9.1802825927734);
    points[5] = Point3d(14.673119544983, 2, -17.180282592773);

    SpatialSet<Point3d> pointSet(points);
    std::vector<Point3d> uniquePoints = pointSet.uniqueItems();

    REQUIRE(uniquePoints.size() == 4u);
}

TEST_CASE("Find") {
    std::vector<LineSegment2d> lineSegments(5);
    lineSegments[0] = LineSegment2d(Point2d(1, 1), Point2d(3, 1));
    lineSegments[1] = LineSegment2d(Point2d(2, 2), Point2d(4, 2));
    lineSegments[2] = LineSegment2d(Point2d(3, 3), Point2d(5, 3));
    lineSegments[3] = LineSegment2d(Point2d(4, 4), Point2d(6, 4));
    lineSegments[4] = LineSegment2d(Point2d(5, 5), Point2d(7, 5));

    SpatialSet<LineSegment2d> set(lineSegments);
    auto iterator = set.find(LineSegment2d(Point2d(3 + 1e-14, 3), Point2d(5, 3 - 1e-14)));
    REQUIRE_FALSE(iterator == set.end());
    LineSegment2d foundSegment = *iterator;
    REQUIRE(foundSegment.startVertex().x() == 3.0);
    REQUIRE(foundSegment.startVertex().y() == 3.0);
    REQUIRE(foundSegment.endVertex().x() == 5.0);
    REQUIRE(foundSegment.endVertex().y() == 3.0);

    REQUIRE(set.find(LineSegment2d(Point2d(1, 1), Point2d(7, 5))) == set.end());
}

TEST_CASE("Contains") {
    std::vector<LineSegment2d> lineSegments(5);
    lineSegments[0] = LineSegment2d(Point2d(1, 1), Point2d(3, 1));
    lineSegments[1] = LineSegment2d(Point2d(2, 2), Point2d(4, 2));
    lineSegments[2] = LineSegment2d(Point2d(3, 3), Point2d(5, 3));
    lineSegments[3] = LineSegment2d(Point2d(4, 4), Point2d(6, 4));
    lineSegments[4] = LineSegment2d(Point2d(5, 5), Point2d(7, 5));

    SpatialSet<LineSegment2d> set(lineSegments);
    REQUIRE(set.contains(LineSegment2d(Point2d(3 + 1e-14, 3), Point2d(5, 3 - 1e-14))));
    REQUIRE_FALSE(set.contains(LineSegment2d(Point2d(1, 1), Point2d(7, 5))));
}

