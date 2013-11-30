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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialList.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>

#include <boost/timer.hpp>
#include <cxxtest/TestSuite.h>

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
        TS_ASSERT(leftChildPtr != nullptr);
        TS_ASSERT(rightChildPtr != nullptr);
        TS_ASSERT(nodePtr->bounds.contains(leftChildPtr->bounds));
        TS_ASSERT(nodePtr->bounds.contains(rightChildPtr->bounds));
        testSet(leftChildPtr);
        testSet(rightChildPtr);
    }
}

Interval randomInterval() {
    double mid = 10 * double(rand()) / RAND_MAX;
    double width = double(rand()) / RAND_MAX;
    return Interval(mid - width / 2, mid + width / 2);
}

Vector3I randomVector() {
    return Vector3I(randomInterval(), randomInterval(), randomInterval());
}

class SetTests : public CxxTest::TestSuite
{
public:
    void testInteger() {
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

        TS_ASSERT_EQUALS(actual, expected);
    }
    
    void testInterval() {
        std::vector<Interval> list(2);
        list[0] = Interval(1, 2);
        list[1] = Interval(0, 2);
        SpatialSet<Interval> set(list.begin(), list.end());
        testSet(set.rootNode());
    }
    
    void testInterval2() {
        std::vector<Interval> list;
        list.push_back(Interval(0, 2));
        list.push_back(Interval(1, 2));
        SpatialSet<Interval> set(list.begin(), list.end());
        testSet(set.rootNode());
    }
    
    void testInterval3() {
        std::vector<Interval> list(3);
        list[0] = Interval(0, 1);
        list[1] = Interval(0, 4);
        list[2] = Interval(0, 2);
        SpatialSet<Interval> set(list.begin(), list.end());
        testSet(set.rootNode());
    }
    
    void testVector2I() {
        std::vector<Vector2I> list(5);
        list[0] = Vector2I(Interval(1, 6), Interval(4, 5));
        list[1] = Vector2I(Interval(2, 5), Interval(5, 7));
        list[2] = Vector2I(Interval(4, 7), Interval(3, 6));
        list[3] = Vector2I(Interval(6, 9), Interval(5, 8));
        list[4] = Vector2I(Interval(8, 10), Interval(2, 6));
        SpatialSet<Vector2I> set(list.begin(), list.end());
        testSet(set.rootNode());
    }
    
    void testDoubleOverlapping() {
        std::vector<double> list(5);
        list[0] = 5;
        list[1] = 3;
        list[2] = 1;
        list[3] = 4;
        list[4] = 2;
        SpatialSet<double> set(list);
        std::vector<double> overlapping = set.overlapping(Interval(2.5, 4.5));
        TS_ASSERT_EQUALS(overlapping.size(), 2u);
        TS_ASSERT_EQUALS(overlapping.front(), 3);
        TS_ASSERT_EQUALS(overlapping.back(), 4);
    }
    
    void testVector2dOverlapping() {
        std::vector<Vector2d> list(4);
        list[0] = Vector2d(1, 1);
        list[1] = Vector2d(5, 1);
        list[2] = Vector2d(1, 3);
        list[3] = Vector2d(5, 3);
        SpatialSet<Vector2d> set(list.begin(), list.end());
        std::vector<Vector2d> check = set.overlapping(Vector2I(Interval(1, 5), Interval(2, 4)));
        TS_ASSERT_EQUALS(check.size(), 2u);
        TS_ASSERT_EQUALS(check[0], Vector2d(1, 3));
        TS_ASSERT_EQUALS(check[1], Vector2d(5, 3));
    }

    void testPoint3d() {
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
        TS_ASSERT_EQUALS(overlappingPoints.size(), 2);
        TS_ASSERT_EQUALS(overlappingPoints[0], Point3d(1, 2, 3));
        TS_ASSERT_EQUALS(overlappingPoints[1], Point3d(2, 4, 6));
    }

    void testPointSetTransformation() {
        std::vector<Point3d> pointList(3);
        pointList[0] = Point3d(1, -1, 1);
        pointList[1] = Point3d(1, 0, 1);
        pointList[2] = Point3d(1, 1, 1);

        SpatialSet<Point3d> pointSet(pointList);
        Axis3d rotationAxis(Point3d(1, 0, 0), Vector3d::UnitZ());
        std::vector<Point3d> rotatedPoints = pointSet.rotatedAbout(rotationAxis, M_PI / 2);

        TS_ASSERT((rotatedPoints[0] - Point3d(2, 0, 1)).isZero());
        TS_ASSERT((rotatedPoints[1] - Point3d(1, 0, 1)).isZero());
        TS_ASSERT((rotatedPoints[2] - Point3d(0, 0, 1)).isZero());
    }

    void testVectorSetTransformation() {
        std::vector<Vector3d> vectorList(3);
        vectorList[0] = Vector3d(1, -1, 1);
        vectorList[1] = Vector3d(1, 0, 1);
        vectorList[2] = Vector3d(1, 1, 1);

        SpatialSet<Vector3d> vectorSet(vectorList);
        Axis3d rotationAxis(Point3d(1, 0, 0), Vector3d::UnitZ());
        std::vector<Vector3d> rotatedVectors = vectorSet.rotatedAbout(rotationAxis, M_PI / 2);

        TS_ASSERT((rotatedVectors[0] - Vector3d(1, 1, 1)).isZero());
        TS_ASSERT((rotatedVectors[1] - Vector3d(0, 1, 1)).isZero());
        TS_ASSERT((rotatedVectors[2] - Vector3d(-1, 1, 1)).isZero());
    }

    void testSwap() {
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

        TS_ASSERT_EQUALS(firstSet.size(), 2u);
        TS_ASSERT_EQUALS(secondSet.size(), 3u);
        TS_ASSERT_EQUALS(firstSet[0], 4);
        TS_ASSERT_EQUALS(secondSet[0], 1);
    }

    void testRValue() {
        std::vector<double> values(3);
        values[0] = 1;
        values[1] = 2;
        values[2] = 3;

        SpatialSet<double> set1(values);
        const detail::SpatialSetNode<double>* rootNodePtr = set1.rootNode();

        SpatialSet<double> set2(std::move(set1));

        TS_ASSERT_EQUALS(set1.size(), 0u);
        TS_ASSERT_EQUALS(set2.size(), 3u);
        TS_ASSERT_EQUALS(set1.rootNode(), nullptr);
        TS_ASSERT_EQUALS(set2.rootNode(), rootNodePtr);

        SpatialSet<double> set3;
        set3 = std::move(set2);

        TS_ASSERT_EQUALS(set2.size(), 0u);
        TS_ASSERT_EQUALS(set3.size(), 3u);
        TS_ASSERT_EQUALS(set2.rootNode(), nullptr);
        TS_ASSERT_EQUALS(set3.rootNode(), rootNodePtr);
    }

    void testUnique() {
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

        SpatialList<Point2d> uniquePointsTolerant = SpatialSet<Point2d>(testPoints).uniqueItems();
        SpatialList<Point2d> uniquePointsExact = SpatialSet<Point2d>(testPoints).uniqueItems(0.0);

        TS_ASSERT_EQUALS(uniquePointsTolerant.size(), 4);
        TS_ASSERT_LESS_THAN(uniquePointsTolerant.size(), uniquePointsExact.size());

        std::vector<Point2d> sortedPoints = uniquePointsTolerant;
        std::sort(
            sortedPoints.begin(),
            sortedPoints.end(),
            [] (const Point2d& firstPoint, const Point2d& secondPoint) {
                return (firstPoint.y() - firstPoint.x()) < (secondPoint.y() - secondPoint.x());
            }
        );

        TS_ASSERT((sortedPoints[0] - Point2d(2, 1)).isZero());
        TS_ASSERT((sortedPoints[1] - Point2d(2, 2)).isZero());
        TS_ASSERT((sortedPoints[2] - Point2d(1, 2)).isZero());
        TS_ASSERT((sortedPoints[3] - Point2d(0, 2)).isZero());
    }

    void testUniqueMapping() {
        std::vector<double> values(5);
        values[0] = 1.0;
        values[1] = 2.0;
        values[2] = 2.0 + 1e-14;
        values[3] = 3.0;
        values[4] = 3.0;

        std::vector<std::int64_t> mapping;
        SpatialList<double> uniqueItems = SpatialSet<double>(values).uniqueItems(mapping);

        TS_ASSERT_EQUALS(mapping.size(), 5);
        TS_ASSERT_EQUALS(mapping[0], 0);
        TS_ASSERT_EQUALS(mapping[1], 1);
        TS_ASSERT_EQUALS(mapping[2], 1);
        TS_ASSERT_EQUALS(mapping[3], 2);
        TS_ASSERT_EQUALS(mapping[4], 2);
    }

    void testUniquePoints() {
        std::vector<Point3d> points(6);
        points[0] = Point3d(6.6731209754944, 2, -17.180282592773);
        points[1] = Point3d(6.6731209754944, 2, -9.1802825927734);
        points[2] = Point3d(14.673119544983, 2, -9.1802825927734);
        points[3] = Point3d(6.6731209754944, 2, -17.180282592773);
        points[4] = Point3d(14.673119544983, 2, -9.1802825927734);
        points[5] = Point3d(14.673119544983, 2, -17.180282592773);

        SpatialSet<Point3d> pointSet(points);
        std::vector<Point3d> uniquePoints = pointSet.uniqueItems();

        TS_ASSERT_EQUALS(uniquePoints.size(), 4u);
    }

    void testFind() {
        std::vector<LineSegment2d> lineSegments(5);
        lineSegments[0] = LineSegment2d(Point2d(1, 1), Point2d(3, 1));
        lineSegments[1] = LineSegment2d(Point2d(2, 2), Point2d(4, 2));
        lineSegments[2] = LineSegment2d(Point2d(3, 3), Point2d(5, 3));
        lineSegments[3] = LineSegment2d(Point2d(4, 4), Point2d(6, 4));
        lineSegments[4] = LineSegment2d(Point2d(5, 5), Point2d(7, 5));

        SpatialSet<LineSegment2d> set(lineSegments);
        auto iterator = set.find(LineSegment2d(Point2d(3 + 1e-14, 3), Point2d(5, 3 - 1e-14)));
        TS_ASSERT_DIFFERS(iterator, set.end());
        LineSegment2d foundSegment = *iterator;
        TS_ASSERT_EQUALS(foundSegment.startPoint().x(), 3.0);
        TS_ASSERT_EQUALS(foundSegment.startPoint().y(), 3.0);
        TS_ASSERT_EQUALS(foundSegment.endPoint().x(), 5.0);
        TS_ASSERT_EQUALS(foundSegment.endPoint().y(), 3.0);

        TS_ASSERT_EQUALS(set.find(LineSegment2d(Point2d(1, 1), Point2d(7, 5))), set.end());
    }
};
