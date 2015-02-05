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

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Vector.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

#include <catch/catch.hpp>

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

    template <>
    struct ConversionFunction<MyVector, UnitVector3d>
    {
        UnitVector3d operator()(const MyVector& argument) const {
            return Vector3d(argument.x, argument.y, argument.z).normalized();
        }
    };
}

TEST_CASE("Bounds-related functionality") {
    Vector3d u = Vector3d(1, 2, 3);
    IntervalVector3d v = IntervalVector3d(Interval(1, 2), Interval(2, 3), Interval(3, 4));

    SECTION("Containment") {
        REQUIRE(v.contains(u));
        REQUIRE_FALSE(v.contains(3 * u));
    }

    SECTION("Hull") {
        SECTION("Double vector, Interval vector") {
            IntervalVector3d result = (3 * u).hull(v);
            REQUIRE(result.minVertex() == Vector3d(1, 2, 3));
            REQUIRE(result.maxVertex() == Vector3d(3, 6, 9));
        }
        
        SECTION("Interval vector, double vector") {
            IntervalVector3d result = v.hull(3 * u);
            REQUIRE(result.minVertex() == Vector3d(1, 2, 3));
            REQUIRE(result.maxVertex() == Vector3d(3, 6, 9));
        }

        SECTION("Double vector, double vector") {
            IntervalVector3d result = Vector3d(4, 2, 6).hull(Vector3d(1, 5, 3));
            REQUIRE(result.minVertex() == Vector3d(1, 2, 3));
            REQUIRE(result.maxVertex() == Vector3d(4, 5, 6));
        }
    }

    SECTION("Intersection") {
        IntervalVector3d result = (v + Vector3d(0.5, 0.5, 0.5)).intersection(v);
        REQUIRE((result.minVertex() - Vector3d(1.5, 2.5, 3.5)).isZero());
        REQUIRE((result.maxVertex() - Vector3d(2, 3, 4)).isZero());
    }
}

TEST_CASE("Zero-checking") {
    Vector3d zero(0, 0, 0);
    REQUIRE(zero.isZero());
    REQUIRE_FALSE(Vector3d(1, 2, 3).isZero());
}

TEST_CASE("Random vector generation") {
    IntervalVector3d bounds = IntervalVector3d::random();
    REQUIRE(bounds.diagonalVector().components().minComponent() > 0);
    for (int i = 0; i < 10; ++i) {
        Vector3d random = bounds.randomVector();
        REQUIRE(bounds.contains(random));
    }
}

TEST_CASE("Custom vector type conversion") {
    SECTION("Conversion from custom type") {
        Vector3d from = Vector3d::from(MyVector(1, 2, 3));
        REQUIRE(from == Vector3d(1, 2, 3));
    }

    SECTION("Conversion to custom type") {
        MyVector to = Vector3d(1, 1, 1).to<MyVector>();
        REQUIRE(to.x == 1.0);
        REQUIRE(to.y == 1.0);
        REQUIRE(to.z == 1.0);
    }
}

TEST_CASE("Interval vector vertices") {
    IntervalVector3d testVector(Interval(1, 2), Interval(3, 4), Interval(5, 6));

    IntervalVector3d reconstructed = testVector.vertices().fold(
        IntervalVector3d(),
        [] (const IntervalVector3d& result, const Vector3d& vertex) -> IntervalVector3d {
            return result.hull(vertex);
        }
    );
    REQUIRE(testVector.contains(reconstructed));
    REQUIRE(reconstructed.contains(testVector));

    bool shouldBeTrue = testVector.vertices().all(
        [] (const Vector3d& vector) -> bool {
            return vector.norm() > 2.0;
        }
    );
    REQUIRE(shouldBeTrue);

    bool shouldBeFalse = testVector.vertices().any(
        [] (const Vector3d& vector) -> bool {
            return vector.norm() > 10.0;
        }
    );
    REQUIRE_FALSE(shouldBeFalse);
}

TEST_CASE("2D unit orthogonal vector") {
    Vector2d testVector(2, 3);
    UnitVector2d expected(-3 / sqrt(13.0), 2 / sqrt(13.0));
    REQUIRE((testVector.unitOrthogonal() - expected).isZero());
}

TEST_CASE("3D unit orthogonal vector") {
    SECTION("Simple") {
        Vector3d testVector(4, 3, 0);
        UnitVector3d expected(-0.6, 0.8, 0.0);
        REQUIRE((testVector.unitOrthogonal() - expected).isZero());
    }
    SECTION("Negative components") {
        Vector3d testVector(0, 0, -1);
        UnitVector3d expected(0, 1, 0);
        REQUIRE((testVector.unitOrthogonal() - expected).isZero());
    }
}

TEST_CASE("Interval vector normalization") {
    for (int i = 0; i < 100; ++i) {
        IntervalVector3d intervalVector = 5 * IntervalVector3d::random();
        IntervalVector3d normalized = intervalVector.normalized();
        REQUIRE(normalized.contains(intervalVector.centroid().normalized()));
        for (const Vector3d& vertex : intervalVector.vertices()) {
            REQUIRE(normalized.contains(vertex.normalized()));
        }
    }
}

TEST_CASE("Unit vector translation") {
    UnitVector3d original = Vector3d(1, 2, 3).normalized();
    UnitVector3d translated = original.translatedBy(Vector3d(4, 5, 6));
    REQUIRE(translated == original);
}

TEST_CASE("Unit vector rotation") {
    UnitVector2d original = Vector2d(1, 1).normalized();
    UnitVector2d rotated = original.rotatedAbout(Point2d::origin(), M_PI / 4);
    REQUIRE((rotated - UnitVector2d::unitY()).isZero());
}

TEST_CASE("Unit vector mirroring") {
    UnitVector3d original = Vector3d(4, 5, 6).normalized();
    UnitVector3d mirrored = original.mirroredAbout(Plane3d::yz());
    REQUIRE((original.x() + mirrored.x()) == Zero());
    REQUIRE((original.y() - mirrored.y()) == Zero());
    REQUIRE((original.z() - mirrored.z()) == Zero());
}

TEST_CASE("Unit vector projection") {
    UnitVector3d original = Vector3d(1, 0, 1).normalized();
    Vector3d projected = original.projectedOnto(Plane3d::xy());
    REQUIRE((projected - Vector3d(1.0 / sqrt(2.0), 0.0, 0.0)).isZero());
}

TEST_CASE("Unit vector conversion") {
    SECTION("Conversion from custom type") {
        UnitVector3d from = UnitVector3d::from(MyVector(1, 2, 3));
        REQUIRE((from - Vector3d(1, 2, 3).normalized()).isZero());
    }

    SECTION("Conversion to custom type") {
        MyVector to = Vector3d(1, 1, 1).normalized().to<MyVector>();
        REQUIRE((to.x - 1.0 / sqrt(3.0)) == Zero());
        REQUIRE((to.y - 1.0 / sqrt(3.0)) == Zero());
        REQUIRE((to.z - 1.0 / sqrt(3.0)) == Zero());
    }
}
