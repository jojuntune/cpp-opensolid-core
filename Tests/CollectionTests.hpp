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

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <cxxtest/TestSuite.h>

#include <algorithm>

using namespace opensolid;

class CollectionTests : public CxxTest::TestSuite
{
private:
    SpatialSet<double> valueSet() {
        std::vector<double> valueList(5);
        valueList[0] = 1;
        valueList[1] = 2;
        valueList[2] = 3;
        valueList[3] = 4;
        valueList[4] = 5;
        return SpatialSet<double>(valueList);
    }

    SpatialSet<Vector2d> vectorSet() {
        std::vector<Vector2d> vectorList(5);
        vectorList[0] = Vector2d(0, 0);
        vectorList[1] = Vector2d(1, 0);
        vectorList[2] = Vector2d(0, 1);
        vectorList[3] = Vector2d(1, 1);
        vectorList[4] = Vector2d(-1, 1);
        return SpatialSet<Vector2d>(vectorList);
    }

    SpatialSet<Box2d> boxSet() {
        std::vector<Box2d> boxList(5);
        boxList[0] = Box2d(Interval(0, 1), Interval(0, 1));
        boxList[1] = Box2d(Interval(1, 2), Interval(1, 2));
        boxList[2] = Box2d(Interval(0.5, 1.5), Interval(0.5, 1.5));
        boxList[3] = Box2d(Interval(0, 2), Interval(0));
        boxList[4] = Box2d(Interval(0, 2), Interval(0, 2));
        return SpatialSet<Box2d>(boxList);
    }
public:
    void testAny() {
        TS_ASSERT(
            valueSet().any(
                [] (double value) -> bool {
                    return value > 3;
                }
            )
        );
        TS_ASSERT(
            !valueSet().any(
                [] (double value) -> bool {
                    return value > 6;
                }
            )
        );
    }

    void testEvery() {
        TS_ASSERT(
            vectorSet().all(
                [] (const Vector2d& vector) -> bool {
                    return vector.norm() < 2;
                }
            )
        );
        TS_ASSERT(
            !vectorSet().all(
                [] (const Vector2d& vector) -> bool {
                    return vector.x() >= Zero();
                }
            )
        );
        Vector2I testBounds(Interval(1), Interval::Whole());
        TS_ASSERT_EQUALS(vectorSet().overlapping(testBounds).size(), 2u);
        TS_ASSERT(
            vectorSet().overlapping(testBounds).all(
                [] (const Vector2d& vector) -> bool {
                    return vector.x() - 1 == Zero();
                }
            )
        );
    }

    void testFold() {
        std::cout << std::endl;
        TS_ASSERT_EQUALS(boxSet().containing(Box2d(1, 1)).size(), 4);
        double sum =
            boxSet().containing(Box2d(1, 1)).fold(
                0.0,
                [] (double value, const Box2d& box) -> double {
                    return value + box.diagonalVector().norm();
                }
            );
        TS_ASSERT(sum - 5 * sqrt(2.0) == Zero());
    }

    void testForEach() {
        double product = 1;
        valueSet().overlapping(Interval(3, INFINITY)).forEach(
            [&product] (double value) {
                product *= value;
            }
        );
        TS_ASSERT_EQUALS(product, 60.0);
    }

    void testReduce() {
        Vector2d sum = vectorSet().reduce(
            [] (const Vector2d& firstVector, const Vector2d& secondVector) {
                return firstVector + secondVector;
            }
        );
        TS_ASSERT((sum - Vector2d(1, 3)).isZero());
    }

    void testWhere() {
        auto predicate = [] (const Box2d& box) -> bool {
            return box.diagonalVector().minCoeff() - 2.0 >= Zero();
        };
        std::int64_t testSize = boxSet().containing(Box2d(0, 0)).where(predicate).size();
        TS_ASSERT_EQUALS(testSize, 1);
    }

    void testVectorConversion() {
        std::vector<double> subset = valueSet().overlapping(Interval(3, 5)).where(
            [] (double value) -> bool {
                return int(value) % 2 != 0;
            }
        );
        TS_ASSERT_EQUALS(subset.size(), 2);
        TS_ASSERT_EQUALS(subset[0], 3.0);
        TS_ASSERT_EQUALS(subset[1], 5.0);
    }

    void testEmpty() {
        auto isInNegativeQuadrant = [] (const Vector2d& vector) -> bool {
            return vector.x() < Zero() && vector.y() < Zero();
        };
        TS_ASSERT(vectorSet().where(isInNegativeQuadrant).isEmpty());
    }

    void testIntCollection() {
        std::vector<int> values(5);
        values[0] = 1;
        values[1] = 2;
        values[2] = 3;
        values[3] = 4;
        values[4] = 5;

        SpatialList<int> list(values);

        int count = list.map(
            [] (int value) {
                return 2 * value;
            }
        ).where(
            [] (int value) {
                return value > 5;
            }
        ).size();

        TS_ASSERT_EQUALS(count, 3);
    }

    void testInt64Collection() {
        std::vector<std::int64_t> values(5);
        values[0] = 1;
        values[1] = 2;
        values[2] = 3;
        values[3] = 4;
        values[4] = 5;

        SpatialList<std::int64_t> list(values);

        Interval bounds = list.map(
            [] (std::int64_t value) -> std::int64_t {
                return 2 * value;
            }
        ).where(
            [] (std::int64_t value) -> std::int64_t {
                return value > 5;
            }
        ).bounds();

        TS_ASSERT_EQUALS(bounds.lowerBound(), 6.0);
        TS_ASSERT_EQUALS(bounds.upperBound(), 10.0);
    }

    void testMapToNonSpatialType() {
        std::vector<std::int64_t> values(5);
        values[0] = 1;
        values[1] = 2;
        values[2] = 3;
        values[3] = 4;
        values[4] = 5;

        SpatialList<std::int64_t> list(values);

        std::int64_t count = list.map(
            [] (std::int64_t value) -> bool {
                return value % 2 == 1;
            }
        ).where(
            [] (bool value) {
                return value;
            }
        ).size();

        TS_ASSERT_EQUALS(count, 3);
    }
};
