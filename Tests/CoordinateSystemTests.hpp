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
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

#include <cxxtest/TestSuite.h>

using namespace opensolid;

class CoordinateSystemTests : public CxxTest::TestSuite
{
public:
    void testGlobalization() {
        CoordinateSystem3d coordinateSystem = CoordinateSystem3d(
            Point3d(1, 1, 1),
            Vector3d(1, 1, 0),
            Vector3d(-1, 1, 0),
            UnitVector3d::Z()
        ).normalized();

        Point3d globalizedPoint = coordinateSystem * Point3d(1, 1, 1);
        TS_ASSERT((globalizedPoint - Point3d(1, 1 + sqrt(2.0), 2)).isZero());

        Vector3d globalizedVector = coordinateSystem * Vector3d(1, 1, 1);
        TS_ASSERT((globalizedVector - Vector3d(0, sqrt(2.0), 1)).isZero());
    }
    
    void testLocalization() {
        CoordinateSystem3d coordinateSystem = CoordinateSystem3d(
            Point3d(1, 1, 1),
            Vector3d(1, 1, 0),
            Vector3d(-1, 1, 0),
            UnitVector3d::Z()
        ).normalized();

        Point3d localizedPoint = Point3d(1, 0, 0) / coordinateSystem;
        TS_ASSERT((localizedPoint - Point3d(-1 / sqrt(2.0), -1 / sqrt(2.0), -1)).isZero());

        Vector3d localizedVector = Vector3d(1, 0, 0) / coordinateSystem;
        TS_ASSERT((localizedVector - Vector3d(1 / sqrt(2.0), -1 / sqrt(2.0), 0)).isZero());
    }
    
    void testCoordinateSystemTransformation() {
        CoordinateSystem3d global = CoordinateSystem3d::Global();
        CoordinateSystem3d coordinateSystem =
            global.translatedBy(Vector3d(1, 1, 1)).rotatedAbout(global.xAxis(), -M_PI / 2);
        TS_ASSERT((coordinateSystem * Point3d(1, 2, 3) - Point3d(2, 4, -3)).isZero());
    }
    
    void testCoordinateSystemComposition() {
        CoordinateSystem3d coordinateSystem = CoordinateSystem3d(Point3d(1, 0, 0));
        coordinateSystem = coordinateSystem.rotatedAbout(coordinateSystem.yAxis(), -M_PI / 4);

        CoordinateSystem3d globalized = coordinateSystem * coordinateSystem;
        Point3d expectedProductOrigin(1 + 1 / sqrt(2.0), 0, 1 / sqrt(2.0));

        TS_ASSERT((globalized.originPoint() - expectedProductOrigin).isZero());
        TS_ASSERT((globalized.xAxis().directionVector() - Vector3d(0, 0, 1)).isZero());
        TS_ASSERT((globalized.yAxis().directionVector() - Vector3d(0, 1, 0)).isZero());
        TS_ASSERT((globalized.zAxis().directionVector() - Vector3d(-1, 0, 0)).isZero());

        CoordinateSystem3d localized = coordinateSystem / coordinateSystem;
        TS_ASSERT(localized.originPoint().isOrigin());
        TS_ASSERT(localized.basisMatrix().isIdentity());
    }
    
    void test2d() {
        CoordinateSystem2d coordinateSystem = CoordinateSystem2d(
            Point2d(1, 0),
            Vector2d(1, 1).normalized(),
            Vector2d(1, 1).unitOrthogonal()
        );

        TS_ASSERT(
            (coordinateSystem * Point2d(2, 2) - Point2d(1, 2 * sqrt(2.0))).isZero()
        );
        TS_ASSERT(
            (Point2d(2, 1) / coordinateSystem - Point2d(sqrt(2.0), 0)).isZero()
        );
    }
    
    void testAccuracy() {
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

            std::cout << coordinateSystem.basisMatrix() << std::endl;
            std::cout << std::endl;
            Matrix3x3 shouldBeIdentity =
                coordinateSystem.basisMatrix() * coordinateSystem.basisMatrix().transpose();
            std::cout << shouldBeIdentity << std::endl;
            std::cout << std::endl;
            std::cout << xDirection / coordinateSystem << std::endl;
            std::cout << yDirection / coordinateSystem << std::endl;
            std::cout << zDirection / coordinateSystem << std::endl;
            std::cout << std::endl;
        }
    }
    
    void testNonOrthogonal() {
        Matrix3x3 upperTriangularMatrix;
        upperTriangularMatrix(0, 0) = 1;
        upperTriangularMatrix(0, 1) = 1;
        upperTriangularMatrix(1, 1) = 1;
        upperTriangularMatrix(0, 2) = 1;
        upperTriangularMatrix(1, 2) = 1;
        upperTriangularMatrix(2, 2) = 1;

        CoordinateSystem3d coordinateSystem(Point3d(1, 2, 3), upperTriangularMatrix);
        
        TS_ASSERT((coordinateSystem * Point3d(1, 1, 1) - Point3d(4, 4, 4)).isZero());
        TS_ASSERT((Point3d(4, 4, 4) / coordinateSystem - Point3d(1, 1, 1)).isZero());
    }
};
