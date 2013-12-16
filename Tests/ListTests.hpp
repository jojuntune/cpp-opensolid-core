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
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialList.hpp>
#include <OpenSolid/Core/Triangle.hpp>

#include <cxxtest/TestSuite.h>

#include <vector>

using namespace opensolid;

class ListTests : public CxxTest::TestSuite
{
public:
    void testPointListTransformation() {
        std::vector<Point3d> points(3);
        points[0] = Point3d(1, -1, 1);
        points[1] = Point3d(1, 0, 1);
        points[2] = Point3d(1, 1, 1);

        SpatialList<Point3d> pointList(points);
        Axis3d rotationAxis(Point3d(1, 0, 0), Vector3d::UnitZ());
        SpatialList<Point3d> rotatedPoints = pointList.rotatedAbout(rotationAxis, M_PI / 2);

        TS_ASSERT((rotatedPoints[0] - Point3d(2, 0, 1)).isZero());
        TS_ASSERT((rotatedPoints[1] - Point3d(1, 0, 1)).isZero());
        TS_ASSERT((rotatedPoints[2] - Point3d(0, 0, 1)).isZero());
    }

    void testVectorListTransformation() {
        std::vector<Vector3d> vectors(3);
        vectors[0] = Vector3d(1, -1, 1);
        vectors[1] = Vector3d(1, 0, 1);
        vectors[2] = Vector3d(1, 1, 1);

        SpatialList<Vector3d> vectorList(vectors);
        Axis3d rotationAxis(Point3d(1, 0, 0), Vector3d::UnitZ());
        SpatialList<Vector3d> rotatedVectors = vectorList.rotatedAbout(rotationAxis, M_PI / 2);

        TS_ASSERT((rotatedVectors[0] - Vector3d(1, 1, 1)).isZero());
        TS_ASSERT((rotatedVectors[1] - Vector3d(0, 1, 1)).isZero());
        TS_ASSERT((rotatedVectors[2] - Vector3d(-1, 1, 1)).isZero());
    }

    void testSwap() {
        std::vector<double> firstValues(3);
        firstValues[0] = 1;
        firstValues[1] = 2;
        firstValues[2] = 3;
        SpatialList<double> firstList(firstValues);

        std::vector<double> secondValues(2);
        secondValues[0] = 4;
        secondValues[1] = 5;
        SpatialList<double> secondList(secondValues);

        firstList.swap(secondList);

        TS_ASSERT_EQUALS(firstList.size(), 2);
        TS_ASSERT_EQUALS(secondList.size(), 3);
        TS_ASSERT_EQUALS(firstList[0], 4);
        TS_ASSERT_EQUALS(secondList[0], 1);
    }

    void testRValue() {
        std::vector<double> values(3);
        values[0] = 1;
        values[1] = 2;
        values[2] = 3;

        SpatialList<double> list1(values);

        SpatialList<double> list2(std::move(list1));

        TS_ASSERT_EQUALS(list1.size(), 0);
        TS_ASSERT_EQUALS(list2.size(), 3);

        SpatialList<double> list3;
        list3 = std::move(list2);

        TS_ASSERT_EQUALS(list2.size(), 0);
        TS_ASSERT_EQUALS(list3.size(), 3);
    }

    void testSimpleMapping() {
        std::vector<Vector2d> vectors(3);
        vectors[0] = Vector2d(1, 2);
        vectors[1] = Vector2d(3, 4);
        vectors[2] = Vector2d(5, 6);

        SpatialList<Vector2d> list(vectors);

        SpatialList<double> squaredNorms = list.map(
            [] (const Vector2d& vector) {
                return vector.squaredNorm();
            }
        );

        TS_ASSERT(squaredNorms[0] - 5.0 == Zero());
        TS_ASSERT(squaredNorms[1] - 25.0 == Zero());
        TS_ASSERT(squaredNorms[2] - 61.0 == Zero());
    }

    void testMappingBounds() {
        Interval edgeLengthBounds = Triangle2d::Unit().edges().map(
            [] (const LineSegment2d& edge) {
                return edge.length();
            }
        ).bounds();

        TS_ASSERT(edgeLengthBounds.lowerBound() - 1.0 == Zero());
        TS_ASSERT(edgeLengthBounds.upperBound() - sqrt(2.0) == Zero());
    }

    void testMappingTransformation() {
        SpatialList<Point2d> rotatedMidpoints = Triangle2d::Unit().edges().map(
            [] (const LineSegment2d& edge) {
                return edge.midpoint();
            }
        ).rotatedAbout(Point2d::Origin(), M_PI / 4);

        TS_ASSERT_EQUALS(rotatedMidpoints.size(), 3);
        std::cout << rotatedMidpoints[0] << std::endl;
        std::cout << rotatedMidpoints[1] << std::endl;
        std::cout << rotatedMidpoints[2] << std::endl;
        TS_ASSERT(
            (rotatedMidpoints[0] - Point2d(0, 1 / sqrt(2.0))).isZero()
        );
        TS_ASSERT(
            (rotatedMidpoints[1] - Point2d(-1 / (2 * sqrt(2.0)), 1 / (2 * sqrt(2.)))).isZero()
        );
        TS_ASSERT(
            (rotatedMidpoints[2] - Point2d(1 / (2 * sqrt(2.0)), 1 / (2 * sqrt(2.)))).isZero()
        );
    }
};
