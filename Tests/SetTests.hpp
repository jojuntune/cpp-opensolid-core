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
*************************************************************************************/

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Set.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>

#include <boost/timer.hpp>
#include <cxxtest/TestSuite.h>

#include <iterator>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace opensolid;

template <class Type>
void testSet(const SetNode<Type>* node) {
    if (!node) {
        return;
    } else if (node->element()) {
        TS_ASSERT(node->size() == 1u);
    } else {
        const SetNode<Type>* leftChild = node->leftChild();
        const SetNode<Type>* rightChild = node->rightChild();
        TS_ASSERT(node->bounds().contains(leftChild->bounds()));
        TS_ASSERT(node->bounds().contains(rightChild->bounds()));
        TS_ASSERT_EQUALS(node->size(), leftChild->size() + rightChild->size());
        testSet(node->leftChild());
        testSet(node->rightChild());
    }
}

template <class TElement>
void testSet(const spatialset::SetNode<TElement>* node) {
    if (!node) {
        return;
    } else if (node->leftChild) {
        const spatialset::SetNode<TElement>* leftChild = node->leftChild;
        const spatialset::SetNode<TElement>* rightChild = node->leftChild->next;
        TS_ASSERT(leftChild != nullptr);
        TS_ASSERT(rightChild != nullptr);
        TS_ASSERT(node->bounds.contains(leftChild->bounds));
        TS_ASSERT(node->bounds.contains(rightChild->bounds));
        testSet(leftChild);
        testSet(rightChild);
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

struct IntervalIndex
{
    std::size_t index;
};

namespace opensolid
{
    template <>
    struct NumDimensions<IntervalIndex>
    {
        static const int Value = 1;
    };

    template <>
    struct BoundsType<IntervalIndex>
    {
        typedef Interval Type;
    };

    template <>
    struct BoundsFunction<IntervalIndex>
    {
        std::vector<Interval>* intervals;

        Interval
        operator()(IntervalIndex index) const {
            return intervals->at(index.index);
        }
    };
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

        auto temp = set.filtered(
            [] (Interval bounds) -> bool {
                return true;
            }
        );
        std::vector<double> actual(temp.begin(), temp.end());

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
        SpatialSet<double> set(list.begin(), list.end());
        auto subset = set.overlapping(Interval(2.5, 4.5));
        std::vector<double> overlapping(subset.begin(), subset.end());
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
        auto subset = set.overlapping(Vector2I(Interval(1, 5), Interval(2, 4)));
        std::vector<Vector2d> check(subset.begin(), subset.end());
        TS_ASSERT_EQUALS(check.size(), 2u);
        TS_ASSERT_EQUALS(check[0], Vector2d(1, 3));
        TS_ASSERT_EQUALS(check[1], Vector2d(5, 3));
    }
    
    void testdoubleInsertion() {
        Set<double> set;
        set.insert(3);
        set.insert(1);
        set.insert(7);
        set.insert(2);
        set.insert(5);
        std::cout << set << std::endl;
        testSet(set.root());
        TS_ASSERT_EQUALS(set.size(), 5u);
        TS_ASSERT_EQUALS(set.erase(3), 1u);
        std::cout << "3 removed" << std::endl;
        std::cout << set << std::endl;
        testSet(set.root());
        TS_ASSERT_EQUALS(set.size(), 4u);
        set.erase(5);
        std::cout << "5 removed" << std::endl;
        std::cout << set << std::endl;
        testSet(set.root());
        TS_ASSERT_EQUALS(set.size(), 3u);
        set.erase(7);
        std::cout << "7 removed" << std::endl;
        std::cout << set << std::endl;
        testSet(set.root());
        TS_ASSERT_EQUALS(set.size(), 2u);
    }
    
    void testRebalance() {
        Set<double> set;
        for (int i = 1; i <= 12; ++i) {
            set.insert(i);
            std::cout << set << std::endl;
            testSet(set.root());
            TS_ASSERT_EQUALS(set.size(), unsigned(i));
        }
        for (int i = 12; i >= 1; --i) {
            set.erase(i);
            std::cout << set << std::endl;
            testSet(set.root());
            TS_ASSERT_EQUALS(set.size(), unsigned(i - 1));
        }
    }
    
    void testLeafParentBug() {
        Set<Interval> set;
        set.insert(Interval(-2, 2));
        set.insert(Interval(2, 6));
        std::cout << set << std::endl;
        testSet(set.root());
        TS_ASSERT_EQUALS(set.size(), 2u);
        set.insert(Interval(-1, 1));
        std::cout << set << std::endl;
        testSet(set.root());
        TS_ASSERT_EQUALS(set.size(), 3u);
    }
    
    void testRangeOperations() {
        Set<double> set;
        std::vector<double> insertion_list(5);
        insertion_list[0] = 5;
        insertion_list[1] = 1;
        insertion_list[2] = 3;
        insertion_list[3] = 2;
        insertion_list[4] = 4;
        std::vector<double> erasure_list(5);
        erasure_list[0] = 1;
        erasure_list[1] = 3;
        erasure_list[2] = 5;
        erasure_list[3] = 7;
        erasure_list[4] = 9;
        set.insert(insertion_list.begin(), insertion_list.end());
        TS_ASSERT_EQUALS(set.size(), 5u);
        TS_ASSERT_EQUALS(set.erase(erasure_list.begin(), erasure_list.end()), 3u);
        TS_ASSERT_EQUALS(set.size(), 2u);
    }

    void testCustomBoundsFunction() {
        std::vector<Interval> intervals(2);
        intervals[0] = Interval(1, 2);
        intervals[1] = Interval(3, 4);
        std::vector<IntervalIndex> intervalIndices(2);
        intervalIndices[0].index = 0;
        intervalIndices[1].index = 1;
        BoundsFunction<IntervalIndex> boundsFunction;
        boundsFunction.intervals = &intervals;
        SpatialSet<IntervalIndex> indexSet(intervalIndices, boundsFunction);
        Interval bounds = indexSet.bounds();
        TS_ASSERT_EQUALS(bounds.lowerBound(), 1.0);
        TS_ASSERT_EQUALS(bounds.upperBound(), 4.0);
    }

    void testIndexing() {
        Set<double> set;
        set.insert(5);
        set.insert(1);
        set.insert(8);
        set.insert(9);
        set.insert(2);

        TS_ASSERT_EQUALS(set.indexOf(1), 0);
        TS_ASSERT_EQUALS(set.indexOf(2), 1);
        TS_ASSERT_EQUALS(set.indexOf(5), 2);
        TS_ASSERT_EQUALS(set.indexOf(8), 3);
        TS_ASSERT_EQUALS(set.indexOf(9), 4);

        TS_ASSERT_EQUALS(set.indexOf(0), -1);
        TS_ASSERT_EQUALS(set.indexOf(10), -1);

        TS_ASSERT_EQUALS(set.atIndex(0), 1);
        TS_ASSERT_EQUALS(set.atIndex(1), 2);
        TS_ASSERT_EQUALS(set.atIndex(2), 5);
        TS_ASSERT_EQUALS(set.atIndex(3), 8);
        TS_ASSERT_EQUALS(set.atIndex(4), 9);
    }

    void testIndexingSpeed() {
        Set<Vector3d> set;
        int size = 100000;
        for (int i = 0; i < size; ++i) {
            set.insert(Vector3d(rand(), rand(), rand()));
        }

        boost::timer visitationTimer;
        double visitationSquaredNorm = 0.0;
        set.forEach(
            [&] (const Vector3d& vector) {
                visitationSquaredNorm += vector.squaredNorm();
            }
        );
        double visitationTime = visitationTimer.elapsed();

        std::cout << "Visitation: " << visitationTime << " s" << std::endl;

        boost::timer indexingTimer;
        double indexingSquaredNorm = 0.0;
        for (int i = 0; i < size; ++i) {
            indexingSquaredNorm += set.atIndex(i).squaredNorm();
        }
        double indexingTime = indexingTimer.elapsed();

        std::cout << "Indexing: " << indexingTime << " s" << std::endl;

        std::cout << "Visitation " << indexingTime / visitationTime << " times faster" << std::endl;

        TS_ASSERT(visitationSquaredNorm - indexingSquaredNorm == Zero());
    }

    void testPoint3d() {
        std::vector<Point3d> pointList(3);
        pointList[0] = Point3d(1, 2, 3);
        pointList[1] = Point3d(4, 5, 6);
        pointList[2] = Point3d(2, 4, 6);

        SpatialSet<Point3d> pointSet(pointList);
        auto subset = pointSet.overlapping(Box3d(Interval(1, 3), Interval(1, 5), Interval(1, 7)));

        std::vector<Point3d> overlappingPoints(subset.begin(), subset.end());
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
        SpatialSet<Point3d> rotatedPointSet = pointSet.rotatedAbout(rotationAxis, M_PI / 2);

        TS_ASSERT((rotatedPointSet[0] - Point3d(2, 0, 1)).isZero());
        TS_ASSERT((rotatedPointSet[1] - Point3d(1, 0, 1)).isZero());
        TS_ASSERT((rotatedPointSet[2] - Point3d(0, 0, 1)).isZero());
    }

    void testVectorSetTransformation() {
        std::vector<Vector3d> vectorList(3);
        vectorList[0] = Vector3d(1, -1, 1);
        vectorList[1] = Vector3d(1, 0, 1);
        vectorList[2] = Vector3d(1, 1, 1);

        SpatialSet<Vector3d> vectorSet(vectorList);
        Axis3d rotationAxis(Point3d(1, 0, 0), Vector3d::UnitZ());
        SpatialSet<Vector3d> rotatedVectorSet = vectorSet.rotatedAbout(rotationAxis, M_PI / 2);

        TS_ASSERT((rotatedVectorSet[0] - Vector3d(1, 1, 1)).isZero());
        TS_ASSERT((rotatedVectorSet[1] - Vector3d(0, 1, 1)).isZero());
        TS_ASSERT((rotatedVectorSet[2] - Vector3d(-1, 1, 1)).isZero());
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
        const spatialset::SetNode<double>* root = set1.rootNode();

        SpatialSet<double> set2(std::move(set1));

        TS_ASSERT_EQUALS(set1.size(), 0u);
        TS_ASSERT_EQUALS(set2.size(), 3u);
        TS_ASSERT_EQUALS(set1.rootNode(), nullptr);
        TS_ASSERT_EQUALS(set2.rootNode(), root);

        SpatialSet<double> set3;
        set3 = std::move(set2);

        TS_ASSERT_EQUALS(set2.size(), 0u);
        TS_ASSERT_EQUALS(set3.size(), 3u);
        TS_ASSERT_EQUALS(set2.rootNode(), nullptr);
        TS_ASSERT_EQUALS(set3.rootNode(), root);
    }
};
