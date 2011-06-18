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

#include <OpenSolid/Common/Comparison.hpp>
#include "Datum.hpp"

using namespace OpenSolid;

class DatumTestSuite : public CxxTest::TestSuite
{
public:
    void testProduct() {
        MatrixXD vectors(3, 2);
        vectors << Vector3D(1, 1, 0), Vector3D(-1, 1, 0);
        Frame3D frame(Vector3D(1, 1, 1), vectors);
        std::cout << frame.vectors() << std::endl;
        Vector3D product = Vector3D(1, 1, 1) * frame;
        std::cout << product << std::endl;
        TS_ASSERT(product.isEqualTo(Vector3D(1, 1 + sqrt(2.0), 2)));
        product = Vector3D(1, 1, 1) * frame.linear();
        std::cout << product.transpose() << std::endl;
        TS_ASSERT(product.isEqualTo(Vector3D(0, sqrt(2.0), 1)));
    }
    
    void testQuotient() {
        MatrixXD vectors(3, 2);
        vectors << Vector3D(1, 1, 0), Vector3D(-1, 1, 0);
        Frame3D frame(Vector3D(1, 1, 1), vectors);
        Vector3D quotient = Vector3D(1, 0, 0) / frame;
        std::cout << quotient.transpose() << std::endl;
        TS_ASSERT(quotient.isEqualTo(Vector3D(-1 / sqrt(2.0), -1 / sqrt(2.0), -1)));
        Vector3D linear_quotient = Vector3D(1, 0, 0) / frame.linear();
        std::cout << linear_quotient.transpose() << std::endl;
        TS_ASSERT(linear_quotient.isEqualTo(Vector3D(1 / sqrt(2.0), -1 / sqrt(2.0), 0)));
    }
    
    void testDatumTransformation() {
        Frame3D global;
        Frame3D frame = global.translatedBy(Vector3D(1, 1, 1)).rotatedBy(-M_PI / 2, global.xAxis());
        TS_ASSERT((Vector3D(1, 2, 3) * frame).isEqualTo(Vector3D(2, 4, -3)));
    }
    
    void testDatumComposition() {
        Frame3D frame(Vector3D::UnitX(), Matrix3D::Identity());
        frame = frame.rotatedBy(-M_PI / 4, frame.yAxis());
        Frame3D product = frame * frame;
        Vector3D expected_product_origin(1 + 1 / sqrt(2.0), 0, 1 / sqrt(2.0));
        Frame3D quotient = frame / frame;
        TS_ASSERT(product.origin().isEqualTo(expected_product_origin));
        TS_ASSERT(product.xVector().isEqualTo(Vector3D(0, 0, 1)));
        TS_ASSERT(product.yVector().isEqualTo(Vector3D(0, 1, 0)));
        TS_ASSERT(product.zVector().isEqualTo(Vector3D(-1, 0, 0)));
        TS_ASSERT(quotient.origin().isZero());
        TS_ASSERT(quotient.vectors().isIdentity());
    }
    
    void test2D() {
        Frame2D frame(Vector2D::UnitX(), Vector2D(1, 1));
        TS_ASSERT_EQUALS(frame.vectors().rows(), 2);
        TS_ASSERT_EQUALS(frame.vectors().cols(), 2);
        TS_ASSERT(frame.xVector().isEqualTo(Vector2D(1, 1).normalized()));
        TS_ASSERT(frame.yVector().isEqualTo(Vector2D(-1, 1).normalized()));
        TS_ASSERT((Vector2D(2, 2) * frame).isEqualTo(Vector2D(1, 2 * sqrt(2.0))));
        TS_ASSERT((Vector2D(2, 1) / frame).isEqualTo(Vector2D(sqrt(2.0), 0)));
    }
    
    void testAccuracy() {
        Matrix3D vectors;
        Frame3D frame;
        
        vectors = Matrix3D::Random();
        frame = Frame3D(Vector3D::Ones(), vectors);
        std::cout << frame.vectors() << std::endl;
        std::cout << std::endl;
        std::cout << frame.vectors() * frame.vectors().transpose() << std::endl;
        std::cout << std::endl;
        std::cout << vectors / frame.linear() << std::endl;
        std::cout << std::endl;
        
        vectors = Matrix3D::Random();
        frame = Frame3D(Vector3D::Ones(), vectors);
        std::cout << frame.vectors() << std::endl;
        std::cout << std::endl;
        std::cout << frame.vectors() * frame.vectors().transpose() << std::endl;
        std::cout << std::endl;
        std::cout << vectors / frame.linear() << std::endl;
        std::cout << std::endl;
        
        vectors = Matrix3D::Random();
        frame = Frame3D(Vector3D::Ones(), vectors);
        std::cout << frame.vectors() << std::endl;
        std::cout << std::endl;
        std::cout << frame.vectors() * frame.vectors().transpose() << std::endl;
        std::cout << std::endl;
        std::cout << vectors / frame.linear() << std::endl;
        std::cout << std::endl;
    }
    
    void testNonOrthogonal() {
        CoordinateSystem3D coordinate_system(
            Vector3D(1, 2, 3),
            Matrix3D::Ones().triangularView<Upper>()
        );
        TS_ASSERT((Vector3D(1, 1, 1) * coordinate_system).isEqualTo(Vector3D(4, 4, 4)));
        TS_ASSERT((Vector3D(4, 4, 4) / coordinate_system).isEqualTo(Vector3D(1, 1, 1)));
    }
};
