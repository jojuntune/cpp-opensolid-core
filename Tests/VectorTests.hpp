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

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Vector.hpp>

#include <cxxtest/TestSuite.h>

#include <typeinfo>
#include <vector>

using namespace opensolid;

struct MyVector
{
    MyVector(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {
    }

    double x;
    double y;
    double z;
};

namespace opensolid
{
    template <>
    struct ConversionFunction<MyVector, Vector3d>
    {
        Vector3d operator()(const MyVector& argument) const {
            return Vector3d(argument.x, argument.y, argument.z);
        }
    };

    template <>
    struct ConversionFunction<Vector3d, MyVector>
    {
        MyVector operator()(const Vector3d& argument) const {
            return MyVector(argument.x(), argument.y(), argument.z());
        }
    };
}

class VectorTests : public CxxTest::TestSuite
{
private:
    double a;
    Interval b;
    Vector3d u;
    IntervalVector3d v;
public:
    void setUp() {
        a = 2;
        b = Interval(2, 3);
        u = Vector3d(1, 2, 3);
        v = IntervalVector3d(Interval(1, 2), Interval(2, 3), Interval(3, 4));
    }

    void testContainment() {
        TS_ASSERT(v.contains(u));
        TS_ASSERT(!v.contains(3 * u));
    }
    
    void testHull() {
        IntervalVector3d result = (3 * u).hull(v);
        TS_ASSERT_EQUALS(result.minVertex(), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(result.maxVertex(), Vector3d(3, 6, 9));
        result = v.hull(3 * u);
        TS_ASSERT_EQUALS(result.minVertex(), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(result.maxVertex(), Vector3d(3, 6, 9));
        result = Vector3d(4, 2, 6).hull(Vector3d(1, 5, 3));
        TS_ASSERT_EQUALS(result.minVertex(), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(result.maxVertex(), Vector3d(4, 5, 6));
    }
    
    void testIntersection() {
        IntervalVector3d result = (v + Vector3d(0.5, 0.5, 0.5)).intersection(v);
        TS_ASSERT((result.minVertex() - Vector3d(1.5, 2.5, 3.5)).isZero());
        TS_ASSERT((result.maxVertex() - Vector3d(2, 3, 4)).isZero());
    }
    
    void testIsZero() {
        Vector3d zero(0, 0, 0);
        TS_ASSERT(zero.isZero());
        TS_ASSERT(!u.isZero());
    }

    void testRandom() {
        IntervalVector3d bounds = IntervalVector3d::Random();
        TS_ASSERT(bounds.diagonalVector().minComponent() > 0);
        for (int i = 0; i < 10; ++i) {
            Vector3d random = bounds.randomVector();
            TS_ASSERT(bounds.contains(random));
        }
    }

    void testConversion() {
        MyVector my_vector = MyVector(1, 2, 3);
        Vector3d from = Vector3d::From(my_vector);
        TS_ASSERT_EQUALS(from, Vector3d(1, 2, 3));
        MyVector to = Vector3d(1, 1, 1).to<MyVector>();
        TS_ASSERT_EQUALS(to.x, 1.0);
        TS_ASSERT_EQUALS(to.y, 1.0);
        TS_ASSERT_EQUALS(to.z, 1.0);
    }

    void testIntervalVectorVertices() {
        IntervalVector3d testVector(Interval(1, 2), Interval(3, 4), Interval(5, 6));

        IntervalVector3d reconstructed = testVector.vertices().fold(
            IntervalVector3d(),
            [] (const IntervalVector3d& result, const Vector3d& vertex) -> IntervalVector3d {
                return result.hull(vertex);
            }
        );
        TS_ASSERT(testVector.contains(reconstructed));
        TS_ASSERT(reconstructed.contains(testVector));

        bool shouldBeTrue = testVector.vertices().all(
            [] (const Vector3d& vector) -> bool {
                return vector.norm() > 2.0;
            }
        );
        TS_ASSERT(shouldBeTrue);

        bool shouldBeFalse = testVector.vertices().any(
            [] (const Vector3d& vector) -> bool {
                return vector.norm() > 10.0;
            }
        );
        TS_ASSERT(!shouldBeFalse);
    }

    void testUnitOrthogonal2d() {
        Vector2d testVector(2, 3);
        UnitVector2d expected(-3 / sqrt(13.0), 2 / sqrt(13.0));
        TS_ASSERT((testVector.unitOrthogonal() - expected).isZero());
    }

    void testUnitOrthogonal3d() {
        Vector3d testVector(4, 3, 0);
        UnitVector3d expected(-0.6, 0.8, 0.0);
        TS_ASSERT((testVector.unitOrthogonal() - expected).isZero());
    }
};
