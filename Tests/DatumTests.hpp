/*************************************************************************************
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
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Plane.hpp>

#include <cxxtest/TestSuite.h>

using namespace opensolid;

class DatumTests : public CxxTest::TestSuite
{
public:
    void testProduct() {
        MatrixXd vectors(3, 2);
        vectors << Vector3d(1, 1, 0), Vector3d(-1, 1, 0);
        Frame3d frame(Vector3d(1, 1, 1), Vector3d(1, 1, 0), Vector3d(-1, 1, 0), Vector3d::UnitZ());
        std::cout << frame.basisMatrix() << std::endl;
        Vector3d product = frame * Vector3d(1, 1, 1);
        std::cout << product << std::endl;
        TS_ASSERT((product - Vector3d(1, 1 + sqrt(2.0), 2)).isZero());
        product = frame.linear() * Vector3d(1, 1, 1);
        std::cout << product.transpose() << std::endl;
        TS_ASSERT((product - Vector3d(0, sqrt(2.0), 1)).isZero());
    }
    
    void testQuotient() {
        MatrixXd vectors(3, 2);
        Frame3d frame(Vector3d(1, 1, 1), Vector3d(1, 1, 0), Vector3d(-1, 1, 0), Vector3d::UnitZ());
        Vector3d quotient = Vector3d(1, 0, 0) / frame;
        std::cout << quotient.transpose() << std::endl;
        TS_ASSERT((quotient - Vector3d(-1 / sqrt(2.0), -1 / sqrt(2.0), -1)).isZero());
        Vector3d linearQuotient = Vector3d(1, 0, 0) / frame.linear();
        std::cout << linearQuotient.transpose() << std::endl;
        TS_ASSERT((linearQuotient - Vector3d(1 / sqrt(2.0), -1 / sqrt(2.0), 0)).isZero());
    }
    
    void testDatumTransformation() {
        Frame3d global = Frame3d::XYZ();
        Frame3d frame = (global + Vector3d(1, 1, 1)).rotated(-M_PI / 2, global.xAxis());
        TS_ASSERT(((frame * Vector3d(1, 2, 3)) - Vector3d(2, 4, -3)).isZero());
    }
    
    void testDatumComposition() {
        Frame3d frame = Frame3d::XYZ(Vector3d::UnitX());
        frame = frame.rotated(-M_PI / 4, frame.yAxis());
        Frame3d product = frame * frame;
        Vector3d expectedProductOrigin(1 + 1 / sqrt(2.0), 0, 1 / sqrt(2.0));
        Frame3d quotient = frame / frame;
        TS_ASSERT((product.originPoint() - expectedProductOrigin).isZero());
        TS_ASSERT((product.xAxis().basisVector() - Vector3d(0, 0, 1)).isZero());
        TS_ASSERT((product.yAxis().basisVector() - Vector3d(0, 1, 0)).isZero());
        TS_ASSERT((product.zAxis().basisVector() - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT(quotient.originPoint().isZero());
        TS_ASSERT(quotient.basisMatrix().isIdentity());
    }

    void testAdvancedDatumComposition() {
        Plane3d plane(Vector3d(1, 1, 1), Vector3d(1, 0, 1), Vector3d(0, 1, 0));
        TS_ASSERT(plane.basisMatrix().col(0).norm() - 1 == Zero());
        TS_ASSERT(plane.basisMatrix().col(1).norm() - 1 == Zero());
        Datum<3, 2> projected = plane.projected(Frame3d().xyPlane());
        TS_ASSERT((projected.basisMatrix().col(0) - Vector3d(1 / sqrt(2.0), 0, 0)).isZero());
        TS_ASSERT((projected.basisMatrix().col(1) - Vector3d(0, 1, 0)).isZero());
        Axis3d axis = plane * Axis2d(Vector2d::Zero(), Vector2d(1, 1));
        TS_ASSERT((axis.originPoint() - plane.originPoint()).isZero());
        Vector3d expectedAxisVector = Vector3d(1 / sqrt(2.0), 1, 1 / sqrt(2.0)).normalized();
        TS_ASSERT((axis.basisMatrix() - expectedAxisVector).isZero());
    }
    
    void test2d() {
        Frame2d frame = Frame2d::FromXAxis(Axis2d(Vector2d::UnitX(), Vector2d(1, 1)));
        TS_ASSERT_EQUALS(frame.basisMatrix().rows(), 2);
        TS_ASSERT_EQUALS(frame.basisMatrix().cols(), 2);
        TS_ASSERT((frame.basisMatrix().col(0) - Vector2d(1, 1).normalized()).isZero());
        TS_ASSERT((frame.basisMatrix().col(1) - Vector2d(-1, 1).normalized()).isZero());
        TS_ASSERT((frame * Vector2d(2, 2) - Vector2d(1, 2 * sqrt(2.0))).isZero());
        TS_ASSERT((Vector2d(2, 1) / frame - Vector2d(sqrt(2.0), 0)).isZero());
    }
    
    void testAccuracy() {
        Frame3d frame;
        for (int i = 0; i < 3; ++i) {
            Vector3d xDirection = Vector3d::Random();
            Vector3d yDirection = Vector3d::Random();
            Vector3d zDirection = Vector3d::Random();
            frame = Frame3d(Vector3d::Ones(), xDirection, yDirection, zDirection).normalized();
            std::cout << frame.basisMatrix() << std::endl;
            std::cout << std::endl;
            std::cout << frame.basisMatrix() * frame.basisMatrix().transpose() << std::endl;
            std::cout << std::endl;
            std::cout << xDirection / frame.linear() << std::endl;
            std::cout << yDirection / frame.linear() << std::endl;
            std::cout << zDirection / frame.linear() << std::endl;
            std::cout << std::endl;
        }
    }
    
    void testNonOrthogonal() {
        Datum<3, 3> coordinateSystem(Vector3d(1, 2, 3), Matrix3d::Ones().triangularView<Upper>());
        TS_ASSERT((coordinateSystem * Vector3d(1, 1, 1) - Vector3d(4, 4, 4)).isZero());
        TS_ASSERT((Vector3d(4, 4, 4) / coordinateSystem - Vector3d(1, 1, 1)).isZero());
    }

    void testPlaneFromNormal() {
        Plane3d plane = Plane3d::FromPointAndNormal(Vector3d(1, 1, 1), Vector3d::UnitZ());
        TS_ASSERT(plane.basisMatrix().isUnitary());
        TS_ASSERT((plane.basisVector(0).cross(plane.basisVector(1)) - Vector3d::UnitZ()).isZero());
        Vector3d point(2, 2, 2);
        Vector3d projectedPoint = point.projected(plane);
        Vector3d expectedProjected(2, 2, 1);
        TS_ASSERT((projectedPoint - expectedProjected).isZero());
    }

    void testReversed() {
        TS_ASSERT((Frame3d().xAxis().reversed().point(1) - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((Frame3d().reversed(2).point(1, 2, 3) - Vector3d(1, 2, -3)).isZero());
        Vector3d point = (Frame3d() + Vector3d(1, 1, 1)).yReversed().point(1, 2, 3);
        Vector3d expected(2, -1, 4);
        TS_ASSERT((point - expected).isZero());
    }
};
