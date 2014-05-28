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

#include <OpenSolid/Core/Quaternion.hpp>
#include <OpenSolid/Core/Rotation.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

#include <catch/catch.hpp>

using namespace opensolid;

TEST_CASE("Basic rotations") {
    Matrix3d quaternionMatrix;
    Matrix3d expectedMatrix;

    SECTION("X") {
        quaternionMatrix = Quaternion3d(UnitVector3d::X(), M_PI / 4).rotationMatrix();
        expectedMatrix = Rotation3d(Axis3d::x(), M_PI / 4).transformationMatrix();
    }

    SECTION("Y") {
        quaternionMatrix = Quaternion3d(-UnitVector3d::Y(), M_PI / 4).rotationMatrix();
        expectedMatrix = Rotation3d(Axis3d::y().flipped(), M_PI / 4).transformationMatrix();
    }

    SECTION("Z") {
        quaternionMatrix = Quaternion3d(UnitVector3d::Z(), -M_PI / 4).rotationMatrix();
        expectedMatrix = Rotation3d(Axis3d::z(), -M_PI / 4).transformationMatrix();
    }

    REQUIRE((quaternionMatrix - expectedMatrix).isZero());
}

TEST_CASE("Composite rotation") {
    double inclinationAngle = acos(sqrt(2.0 / 3.0));
    Quaternion3d quaternion = Quaternion3d(UnitVector3d::Z(), M_PI / 4) *
        Quaternion3d(UnitVector3d::Y(), -inclinationAngle);
    CoordinateSystem3d coordinateSystem(
        Point3d::Origin(),
        Vector3d(1, 1, 1).normalized(),
        Vector3d(-1, 1, 0).normalized(),
        Vector3d(-1, -1, 2).normalized()
    );
    REQUIRE((quaternion.rotationMatrix() - coordinateSystem.basisMatrix()).isZero());
}

TEST_CASE("Angle and unit vector extraction") {
    for (int i = 0; i < 100; ++i) {
        UnitVector3d unitVector = UnitVector3d::Random();
        double angle = Interval(-3 * M_PI / 4, 3 * M_PI / 4).randomValue();
        Quaternion3d quaternion = Quaternion3d(unitVector, angle);
        UnitVector3d extractedUnitVector = quaternion.unitVector();
        double extractedAngle = quaternion.angle();
        if (extractedUnitVector.dot(unitVector) < 0.0) {
            INFO("Flipping...")
            extractedUnitVector = -extractedUnitVector;
            extractedAngle = -extractedAngle;
        }
        CAPTURE(angle);
        CAPTURE(unitVector);
        CAPTURE(extractedAngle);
        CAPTURE(extractedUnitVector);
        REQUIRE((extractedAngle - angle) == Zero());
        REQUIRE((extractedUnitVector - unitVector).isZero());
    }
}

TEST_CASE("Slerp") {
    Quaternion3d initial = Quaternion3d::Identity();
    Quaternion3d final =
        Quaternion3d(UnitVector3d::Z(), M_PI / 2) * Quaternion3d(UnitVector3d::X(), -M_PI / 2);
    Quaternion3d relative = final * initial.inverse();
    CAPTURE(relative.unitVector())
    CAPTURE(relative.angle());
    Axis3d axis(Point3d::Origin(), relative.unitVector());
    double angle = relative.angle();

    SECTION("Initial") {
        Quaternion3d interpolated = Quaternion3d::Slerp(initial, final, 0.0);
        Matrix3d rotationMatrix = interpolated.rotationMatrix();
        REQUIRE(rotationMatrix.isIdentity());
    }

    SECTION("Mid") {
        Quaternion3d interpolated = Quaternion3d::Slerp(initial, final, 0.5);
        Matrix3d rotationMatrix = interpolated.rotationMatrix();
        Vector3d xBasisVector = Vector3d(rotationMatrix.column(0));
        Vector3d yBasisVector = Vector3d(rotationMatrix.column(1));
        Vector3d zBasisVector = Vector3d(rotationMatrix.column(2));
        Rotation3d rotation(axis, angle * 0.5);
        REQUIRE((xBasisVector - UnitVector3d::X().transformedBy(rotation)).isZero());
        REQUIRE((yBasisVector - UnitVector3d::Y().transformedBy(rotation)).isZero());
        REQUIRE((zBasisVector - UnitVector3d::Z().transformedBy(rotation)).isZero());
    }

    SECTION("Final") {
        Quaternion3d interpolated = Quaternion3d::Slerp(initial, final, 1.0);
        Matrix3d rotationMatrix = interpolated.rotationMatrix();
        Vector3d xBasisVector = Vector3d(rotationMatrix.column(0));
        Vector3d yBasisVector = Vector3d(rotationMatrix.column(1));
        Vector3d zBasisVector = Vector3d(rotationMatrix.column(2));
        REQUIRE((xBasisVector - UnitVector3d::Y()).isZero());
        REQUIRE((yBasisVector + UnitVector3d::Z()).isZero());
        REQUIRE((zBasisVector + UnitVector3d::X()).isZero());
    }
}

TEST_CASE("Slerp of equal quaternions") {
    Quaternion3d quaternion(Vector3d(1, 1, 1).normalized(), M_PI / 3);

    SECTION("Initial") {
        Quaternion3d interpolated = Quaternion3d::Slerp(quaternion, quaternion, 0.0);
        REQUIRE((interpolated.components() - quaternion.components()).isZero());
    }

    SECTION("Mid") {
        Quaternion3d interpolated = Quaternion3d::Slerp(quaternion, quaternion, 0.5);
        REQUIRE((interpolated.components() - quaternion.components()).isZero());
    }

    SECTION("Final") {
        Quaternion3d interpolated = Quaternion3d::Slerp(quaternion, quaternion, 1.0);
        REQUIRE((interpolated.components() - quaternion.components()).isZero());
    }
}

TEST_CASE("Degenerate slerp") {
    Quaternion3d initial = Quaternion3d(UnitVector3d::Z(), -M_PI);
    Quaternion3d final = Quaternion3d(UnitVector3d::Z(), M_PI);
    CAPTURE(initial.dot(final));

    SECTION("0.0") {
        Quaternion3d interpolated = Quaternion3d::Slerp(initial, final, 0.0);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - initial.components()).isZero());
    }

    SECTION("0.25") {
        Quaternion3d interpolated = Quaternion3d::Slerp(initial, final, 0.25);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - initial.components()).isZero());
    }

    SECTION("0.5") {
        Quaternion3d interpolated = Quaternion3d::Slerp(initial, final, 0.5);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE(interpolated.rotationMatrix().isIdentity());
    }

    SECTION("0.75") {
        Quaternion3d interpolated = Quaternion3d::Slerp(initial, final, 0.75);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - final.components()).isZero());
    }

    SECTION("1.0") {
        Quaternion3d interpolated = Quaternion3d::Slerp(initial, final, 1.0);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - final.components()).isZero());
    }
}
