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
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

#include <catch/catch.hpp>

using namespace opensolid;

TEST_CASE("Globalization") {
    CoordinateSystem3d coordinateSystem = CoordinateSystem3d(
        Point3d(1, 1, 1),
        Vector3d(1, 1, 0),
        Vector3d(-1, 1, 0),
        UnitVector3d::Z()
    ).normalized();

    Point3d globalizedPoint = coordinateSystem * Point3d(1, 1, 1);
    REQUIRE((globalizedPoint - Point3d(1, 1 + sqrt(2.0), 2)).isZero());

    Vector3d globalizedVector = coordinateSystem * Vector3d(1, 1, 1);
    REQUIRE((globalizedVector - Vector3d(0, sqrt(2.0), 1)).isZero());
}

TEST_CASE("Localization") {
    CoordinateSystem3d coordinateSystem = CoordinateSystem3d(
        Point3d(1, 1, 1),
        Vector3d(1, 1, 0),
        Vector3d(-1, 1, 0),
        UnitVector3d::Z()
    ).normalized();

    Point3d localizedPoint = Point3d(1, 0, 0) / coordinateSystem;
    REQUIRE((localizedPoint - Point3d(-1 / sqrt(2.0), -1 / sqrt(2.0), -1)).isZero());

    Vector3d localizedVector = Vector3d(1, 0, 0) / coordinateSystem;
    REQUIRE((localizedVector - Vector3d(1 / sqrt(2.0), -1 / sqrt(2.0), 0)).isZero());
}

TEST_CASE("Transformation") {
    CoordinateSystem3d global = CoordinateSystem3d::Global();
    CoordinateSystem3d coordinateSystem =
        global.translatedBy(Vector3d(1, 1, 1)).rotatedAbout(global.xAxis(), -M_PI / 2);
    REQUIRE((coordinateSystem * Point3d(1, 2, 3) - Point3d(2, 4, -3)).isZero());
}

TEST_CASE("Composition") {
    CoordinateSystem3d coordinateSystem = CoordinateSystem3d(Point3d(1, 0, 0));
    coordinateSystem = coordinateSystem.rotatedAbout(coordinateSystem.yAxis(), -M_PI / 4);

    CoordinateSystem3d globalized = coordinateSystem * coordinateSystem;
    Point3d expectedProductOrigin(1 + 1 / sqrt(2.0), 0, 1 / sqrt(2.0));

    REQUIRE((globalized.originPoint() - expectedProductOrigin).isZero());
    REQUIRE((globalized.xAxis().directionVector() - Vector3d(0, 0, 1)).isZero());
    REQUIRE((globalized.yAxis().directionVector() - Vector3d(0, 1, 0)).isZero());
    REQUIRE((globalized.zAxis().directionVector() - Vector3d(-1, 0, 0)).isZero());

    CoordinateSystem3d localized = coordinateSystem / coordinateSystem;
    REQUIRE(localized.originPoint().isOrigin());
    REQUIRE(localized.basisMatrix().isIdentity());
}

TEST_CASE("2D") {
    CoordinateSystem2d coordinateSystem = CoordinateSystem2d(
        Point2d(1, 0),
        Vector2d(1, 1).normalized(),
        Vector2d(1, 1).unitOrthogonal()
    );

    REQUIRE((coordinateSystem * Point2d(2, 2) - Point2d(1, 2 * sqrt(2.0))).isZero());
    REQUIRE((Point2d(2, 1) / coordinateSystem - Point2d(sqrt(2.0), 0)).isZero());
}

TEST_CASE("Accuracy") {
    CoordinateSystem3d coordinateSystem;
    for (int i = 0; i < 3; ++i) {
        Vector3d xDirection = Vector3d::Random();
        Vector3d yDirection = Vector3d::Random();
        Vector3d zDirection = Vector3d::Random();

        coordinateSystem = CoordinateSystem3d(
            Point3d(1, 1, 1),
            xDirection,
            yDirection,
            zDirection
        ).normalized();

        CAPTURE(coordinateSystem.basisMatrix());
        
        Matrix3d shouldBeIdentity =
            coordinateSystem.basisMatrix() * coordinateSystem.basisMatrix().transpose();
        CAPTURE(shouldBeIdentity);
        REQUIRE(shouldBeIdentity.isIdentity());

        Vector3d xDirectionLocalized = xDirection / coordinateSystem;
        Vector3d yDirectionLocalized = yDirection / coordinateSystem;
        Vector3d zDirectionLocalized = zDirection / coordinateSystem;

        CAPTURE(xDirectionLocalized);
        CAPTURE(yDirectionLocalized);
        CAPTURE(zDirectionLocalized);

        REQUIRE(xDirectionLocalized.x() > Zero());
        REQUIRE(xDirectionLocalized.y() == Zero());
        REQUIRE(xDirectionLocalized.z() == Zero());
        
        REQUIRE(yDirectionLocalized.y() > Zero());
        REQUIRE(yDirectionLocalized.z() == Zero());
    }
}

TEST_CASE("Non-orthogonal") {
    Matrix3d upperTriangularMatrix;
    upperTriangularMatrix(0, 0) = 1;
    upperTriangularMatrix(0, 1) = 1;
    upperTriangularMatrix(1, 1) = 1;
    upperTriangularMatrix(0, 2) = 1;
    upperTriangularMatrix(1, 2) = 1;
    upperTriangularMatrix(2, 2) = 1;

    CoordinateSystem3d coordinateSystem(Point3d(1, 2, 3), upperTriangularMatrix);
    
    REQUIRE((coordinateSystem * Point3d(1, 1, 1) - Point3d(4, 4, 4)).isZero());
    REQUIRE((Point3d(4, 4, 4) / coordinateSystem - Point3d(1, 1, 1)).isZero());
}

TEST_CASE("Degenerate") {
    RowMatrix3d basisMatrix;
    basisMatrix(0) = 1.0;
    basisMatrix(1) = 2.0;
    basisMatrix(2) = 3.0;
    CoordinateSystem<1, 3> coordinateSystem(Point1d::Origin(), basisMatrix);
    Point1d original(3.0);
    Point3d transformed = original / coordinateSystem;
    CAPTURE(transformed);
    Point1d reconstructed = coordinateSystem * transformed;
    REQUIRE((reconstructed.value() - original.value()) == Zero());
}
