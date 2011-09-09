/*****************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                     *
 *   ian.e.mackenzie@gmail.com                                               *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <cxxtest/TestSuite.h>

#include <OpenSolid/Datum/Datum.hpp>

using namespace OpenSolid;

class DatumTests : public CxxTest::TestSuite
{
public:
    void testProduct() {
        MatrixXd vectors(3, 2);
        vectors << Vector3d(1, 1, 0), Vector3d(-1, 1, 0);
        Frame3d frame(Vector3d(1, 1, 1), vectors);
        std::cout << frame.basis() << std::endl;
        Vector3d product = Vector3d(1, 1, 1) * frame;
        std::cout << product << std::endl;
        TS_ASSERT((product - Vector3d(1, 1 + sqrt(2.0), 2)).isZero());
        product = Vector3d(1, 1, 1) * frame.orientation();
        std::cout << product.transpose() << std::endl;
        TS_ASSERT((product - Vector3d(0, sqrt(2.0), 1)).isZero());
    }
    
    void testQuotient() {
        MatrixXd vectors(3, 2);
        vectors << Vector3d(1, 1, 0), Vector3d(-1, 1, 0);
        Frame3d frame(Vector3d(1, 1, 1), vectors);
        Vector3d quotient = Vector3d(1, 0, 0) / frame;
        std::cout << quotient.transpose() << std::endl;
        TS_ASSERT((quotient - Vector3d(-1 / sqrt(2.0), -1 / sqrt(2.0), -1)).isZero());
        Vector3d linear_quotient = Vector3d(1, 0, 0) / frame.orientation();
        std::cout << linear_quotient.transpose() << std::endl;
        TS_ASSERT((linear_quotient - Vector3d(1 / sqrt(2.0), -1 / sqrt(2.0), 0)).isZero());
    }
    
    void testDatumTransformation() {
        Frame3d global;
        Frame3d frame = global.translated(Vector3d(1, 1, 1)).rotated(-M_PI / 2, global.xAxis());
        TS_ASSERT(((Vector3d(1, 2, 3) * frame) - Vector3d(2, 4, -3)).isZero());
    }
    
    void testDatumComposition() {
        Frame3d frame(Vector3d::UnitX(), Matrix3d::Identity());
        frame = frame.rotated(-M_PI / 4, frame.yAxis()); // localXAxis(), localYAxis(), localAxis(int index)
        Frame3d product = frame * frame;
        Vector3d expected_product_origin(1 + 1 / sqrt(2.0), 0, 1 / sqrt(2.0));
        Frame3d quotient = frame / frame;
        TS_ASSERT((product.origin() - expected_product_origin).isZero());
        TS_ASSERT((product.xAxis().direction() - Vector3d(0, 0, 1)).isZero());
        TS_ASSERT((product.yAxis().direction() - Vector3d(0, 1, 0)).isZero());
        TS_ASSERT((product.zAxis().direction() - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT(quotient.origin().isZero());
        TS_ASSERT(quotient.basis().isIdentity());
    }

    void testAdvancedDatumComposition() {
        Plane3d plane(Vector3d(1, 1, 1), Vector3d(1, 0, 1), Vector3d(0, 1, 0));
        TS_ASSERT(plane.basis().col(0).norm() == One());
        TS_ASSERT(plane.basis().col(1).norm() == One());
        CoordinateSystem<3, 2> projected = plane % Frame3d().xyPlane();
        TS_ASSERT((projected.basis().col(0) - Vector3d(1 / sqrt(2.0), 0, 0)).isZero());
        TS_ASSERT((projected.basis().col(1) - Vector3d(0, 1, 0)).isZero());
        Axis3d axis = Axis2d(Vector2d::Zero(), Vector2d(1, 1)) * plane;
        TS_ASSERT((axis.origin() - plane.origin()).isZero());
        Vector3d expected_axis_vector = Vector3d(1 / sqrt(2.0), 1, 1 / sqrt(2.0)).normalized();
        TS_ASSERT((axis.basis() - expected_axis_vector).isZero());
    }
    
    void test2d() {
        Frame2d frame(Vector2d::UnitX(), Vector2d(1, 1));
        TS_ASSERT_EQUALS(frame.basis().rows(), 2);
        TS_ASSERT_EQUALS(frame.basis().cols(), 2);
        TS_ASSERT((frame.basis().col(0) - Vector2d(1, 1).normalized()).isZero());
        TS_ASSERT((frame.basis().col(1) - Vector2d(-1, 1).normalized()).isZero());
        TS_ASSERT((Vector2d(2, 2) * frame - Vector2d(1, 2 * sqrt(2.0))).isZero());
        TS_ASSERT((Vector2d(2, 1) / frame - Vector2d(sqrt(2.0), 0)).isZero());
    }
    
    void testAccuracy() {
        Matrix3d vectors;
        Frame3d frame;
        for (int i = 0; i < 3; ++i) {
            vectors = Matrix3d::Random();
            frame = Frame3d(Vector3d::Ones(), vectors);
            std::cout << frame.basis() << std::endl;
            std::cout << std::endl;
            std::cout << frame.basis() * frame.basis().transpose() << std::endl;
            std::cout << std::endl;
            std::cout << vectors / frame.orientation() << std::endl;
            std::cout << std::endl;
        }
    }
    
    void testNonOrthogonal() {
        CoordinateSystem3d coordinate_system(
            Vector3d(1, 2, 3),
            Matrix3d::Ones().triangularView<Upper>()
        );
        TS_ASSERT((Vector3d(1, 1, 1) * coordinate_system - Vector3d(4, 4, 4)).isZero());
        TS_ASSERT((Vector3d(4, 4, 4) / coordinate_system - Vector3d(1, 1, 1)).isZero());
    }

    void testPlaneFromNormal() {
        Plane3d plane(Vector3d(1, 1, 1), Vector3d::UnitZ());
        TS_ASSERT(plane.basis().isUnitary());
        TS_ASSERT((plane.basis().col(0).cross(plane.basis().col(1)) - Vector3d::UnitZ()).isZero());
        Vector3d point(2, 2, 2);
        Vector3d projected_point = point % plane;
        Vector3d expected_projected(2, 2, 1);
        TS_ASSERT((projected_point - expected_projected).isZero());
    }
};
