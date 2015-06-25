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
#include <OpenSolid/Core/UnitVector.hpp>

#include <catch/catch.hpp>

using namespace opensolid;

struct MyQuat
{
    double x;
    double y;
    double z;
    double w;

    MyQuat(double x_, double y_, double z_, double w_) :
        x(x_),
        y(y_),
        z(z_),
        w(w_) {
    }
};

namespace opensolid
{
    template <>
    struct ConversionFunction<Quaternion3d, MyQuat>
    {
        const MyQuat
        operator()(const Quaternion3d& quaternion) const {
            return MyQuat(quaternion.x(), quaternion.y(), quaternion.z(), quaternion.w());
        }
    };

    template <>
    struct ConversionFunction<MyQuat, Quaternion3d>
    {
        const Quaternion3d
        operator()(const MyQuat& myQuat) const {
            return Quaternion3d(myQuat.x, myQuat.y, myQuat.z, myQuat.w);
        }
    };
}

TEST_CASE("Composite rotation 3D") {
    double inclinationAngle = acos(sqrt(2.0 / 3.0));
    Quaternion3d quaternion = Quaternion3d(Vector3d::unitZ(), M_PI / 4) *
        Quaternion3d(Vector3d::unitY(), -inclinationAngle);
    Frame3d frame(
        Point3d::origin(),
        Vector3d(1, 1, 1).normalized(),
        Vector3d(-1, 1, 0).normalized(),
        Vector3d(-1, -1, 2).normalized()
    );
    REQUIRE((quaternion.rotationMatrix() - frame.basisMatrix()).isZero());
}

TEST_CASE("Angle extraction 2D") {
    REQUIRE((Quaternion2d(1 / sqrt(2.0), 1 / sqrt(2.0)).angle() - M_PI / 4) == Zero());
    REQUIRE((Quaternion2d(0, -1).angle() + M_PI / 2) == Zero());
}

TEST_CASE("Angle and unit vector extraction 3D") {
    for (int i = 0; i < 100; ++i) {
        UnitVector3d unitVector = Vector3d::unitRandom();
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

TEST_CASE("Slerp 2D") {
    SECTION("Positive") {
        Quaternion2d initial(M_PI / 4);
        Quaternion2d final(3 * M_PI / 4);
        REQUIRE((Quaternion2d::slerp(initial, final, 0.5).angle() - M_PI / 2) == Zero());
    }

    SECTION("Negative") {
        Quaternion2d initial(-1, 0);
        Quaternion2d final(0, 1);
        REQUIRE((Quaternion2d::slerp(initial, final, 0.25).angle() - 7 * M_PI / 8) == Zero());
    }

    SECTION("Crossing") {
        Quaternion2d initial(M_PI / 4);
        Quaternion2d final(0, -1);
        REQUIRE((Quaternion2d::slerp(initial, final, 0.5).angle() + M_PI / 8) == Zero());
    }
}

TEST_CASE("Slerp 3D") {
    Quaternion3d initial = Quaternion3d::identity();
    Quaternion3d final =
        Quaternion3d(Vector3d::unitZ(), M_PI / 2) * Quaternion3d(Vector3d::unitX(), -M_PI / 2);
    Quaternion3d relative = final * initial.inverse();
    UnitVector3d directionVector = relative.unitVector();
    CAPTURE(relative.unitVector())
    CAPTURE(relative.angle());
    Axis3d axis(Point3d::origin(), directionVector);
    double angle = relative.angle();

    SECTION("Initial") {
        Quaternion3d interpolated = Quaternion3d::slerp(initial, final, 0.0);
        Matrix3d rotationMatrix = interpolated.rotationMatrix();
        REQUIRE(rotationMatrix.isIdentity());
    }

    SECTION("Mid") {
        Quaternion3d interpolated = Quaternion3d::slerp(initial, final, 0.5);
        Matrix3d rotationMatrix = interpolated.rotationMatrix();
        Vector3d xBasisVector = Vector3d(rotationMatrix.column(0));
        Vector3d yBasisVector = Vector3d(rotationMatrix.column(1));
        Vector3d zBasisVector = Vector3d(rotationMatrix.column(2));
        REQUIRE(
            (xBasisVector - Vector3d::unitX().rotatedAbout(directionVector, angle * 0.5)).isZero()
        );
        REQUIRE(
            (yBasisVector - Vector3d::unitY().rotatedAbout(directionVector, angle * 0.5)).isZero()
        );
        REQUIRE(
            (zBasisVector - Vector3d::unitZ().rotatedAbout(directionVector, angle * 0.5)).isZero()
        );
    }

    SECTION("Final") {
        Quaternion3d interpolated = Quaternion3d::slerp(initial, final, 1.0);
        Matrix3d rotationMatrix = interpolated.rotationMatrix();
        Vector3d xBasisVector = Vector3d(rotationMatrix.column(0));
        Vector3d yBasisVector = Vector3d(rotationMatrix.column(1));
        Vector3d zBasisVector = Vector3d(rotationMatrix.column(2));
        REQUIRE((xBasisVector - Vector3d::unitY()).isZero());
        REQUIRE((yBasisVector + Vector3d::unitZ()).isZero());
        REQUIRE((zBasisVector + Vector3d::unitX()).isZero());
    }
}

TEST_CASE("Slerp of equal quaternions 2D") {
    Quaternion2d quaternion(M_PI / 3);

    SECTION("Initial") {
        Quaternion2d interpolated = Quaternion2d::slerp(quaternion, quaternion, 0.0);
        REQUIRE((interpolated.components() - quaternion.components()).isZero());
    }

    SECTION("Mid") {
        Quaternion2d interpolated = Quaternion2d::slerp(quaternion, quaternion, 0.5);
        REQUIRE((interpolated.components() - quaternion.components()).isZero());
    }

    SECTION("Final") {
        Quaternion2d interpolated = Quaternion2d::slerp(quaternion, quaternion, 1.0);
        REQUIRE((interpolated.components() - quaternion.components()).isZero());
    }
}

TEST_CASE("Slerp of equal quaternions 3D") {
    Quaternion3d quaternion(Vector3d(1, 1, 1).normalized(), M_PI / 3);

    SECTION("Initial") {
        Quaternion3d interpolated = Quaternion3d::slerp(quaternion, quaternion, 0.0);
        REQUIRE((interpolated.components() - quaternion.components()).isZero());
    }

    SECTION("Mid") {
        Quaternion3d interpolated = Quaternion3d::slerp(quaternion, quaternion, 0.5);
        REQUIRE((interpolated.components() - quaternion.components()).isZero());
    }

    SECTION("Final") {
        Quaternion3d interpolated = Quaternion3d::slerp(quaternion, quaternion, 1.0);
        REQUIRE((interpolated.components() - quaternion.components()).isZero());
    }
}

TEST_CASE("Degenerate slerp 2D") {
    Quaternion2d initial = Quaternion2d::identity();
    Quaternion2d final(M_PI);
    CAPTURE(initial.dot(final));

    SECTION("0.0") {
        Quaternion2d interpolated = Quaternion2d::slerp(initial, final, 0.0);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - initial.components()).isZero());
    }

    SECTION("0.25") {
        Quaternion2d interpolated = Quaternion2d::slerp(initial, final, 0.25);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - initial.components()).isZero());
    }

    SECTION("0.5") {
        Quaternion2d interpolated = Quaternion2d::slerp(initial, final, 0.5);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE(interpolated.rotationMatrix().isIdentity());
    }

    SECTION("0.75") {
        Quaternion2d interpolated = Quaternion2d::slerp(initial, final, 0.75);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - final.components()).isZero());
    }

    SECTION("1.0") {
        Quaternion2d interpolated = Quaternion2d::slerp(initial, final, 1.0);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - final.components()).isZero());
    }
}

TEST_CASE("Degenerate slerp 3D") {
    Quaternion3d initial = Quaternion3d(Vector3d::unitZ(), -M_PI);
    Quaternion3d final = Quaternion3d(Vector3d::unitZ(), M_PI);
    CAPTURE(initial.dot(final));

    SECTION("0.0") {
        Quaternion3d interpolated = Quaternion3d::slerp(initial, final, 0.0);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - initial.components()).isZero());
    }

    SECTION("0.25") {
        Quaternion3d interpolated = Quaternion3d::slerp(initial, final, 0.25);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - initial.components()).isZero());
    }

    SECTION("0.5") {
        Quaternion3d interpolated = Quaternion3d::slerp(initial, final, 0.5);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE(interpolated.rotationMatrix().isIdentity());
    }

    SECTION("0.75") {
        Quaternion3d interpolated = Quaternion3d::slerp(initial, final, 0.75);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - final.components()).isZero());
    }

    SECTION("1.0") {
        Quaternion3d interpolated = Quaternion3d::slerp(initial, final, 1.0);
        INFO("Rotation matrix:\n" << interpolated.rotationMatrix());
        REQUIRE((interpolated.components() - final.components()).isZero());
    }
}

TEST_CASE("Conversion") {
    Quaternion3d quaternion = Quaternion3d(Vector3d::unitX(), M_PI / 2);
    MyQuat myQuat = quaternion.to<MyQuat>();
    REQUIRE((myQuat.x - 1 / sqrt(2.0)) == Zero());
    REQUIRE(myQuat.y == Zero());
    REQUIRE(myQuat.z == Zero());
    REQUIRE((myQuat.w - 1 / sqrt(2.0)) == Zero());
}
