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
        MatrixXd vectors(3, 2);
        vectors << Vector3d(1, 1, 0), Vector3d(-1, 1, 0);
        Frame3d frame(Vector3d(1, 1, 1), vectors);
        std::cout << frame.vectors() << std::endl;
        Vector3d product = Vector3d(1, 1, 1) * frame;
        std::cout << product << std::endl;
        TS_ASSERT(Comparison::equal(product, Vector3d(1, 1 + sqrt(2.0), 2)));
        product = Vector3d(1, 1, 1) * frame.linear();
        std::cout << product.transpose() << std::endl;
        TS_ASSERT(Comparison::equal(product, Vector3d(0, sqrt(2.0), 1)));
    }
    
    void testQuotient() {
        MatrixXd vectors(3, 2);
        vectors << Vector3d(1, 1, 0), Vector3d(-1, 1, 0);
        Frame3d frame(Vector3d(1, 1, 1), vectors);
        Vector3d quotient = Vector3d(1, 0, 0) / frame;
        std::cout << quotient.transpose() << std::endl;
        TS_ASSERT(Comparison::equal(quotient, Vector3d(-1 / sqrt(2.0), -1 / sqrt(2.0), -1)));
        Vector3d linear_quotient = Vector3d(1, 0, 0) / frame.linear();
        std::cout << linear_quotient.transpose() << std::endl;
        TS_ASSERT(Comparison::equal(linear_quotient, Vector3d(1 / sqrt(2.0), -1 / sqrt(2.0), 0)));
    }
    
    void testDatumTransformation() {
        Frame3d global;
        Frame3d frame = global.translatedBy(Vector3d(1, 1, 1)).rotatedBy(-M_PI / 2, global.xAxis());
        TS_ASSERT(Comparison::equal(Vector3d(1, 2, 3) * frame, Vector3d(2, 4, -3)));
    }
    
    void testDatumComposition() {
        Frame3d frame(Vector3d::UnitX(), Matrix3d::Identity());
        frame = frame.rotatedBy(-M_PI / 4, frame.yAxis());
        Frame3d product = frame * frame;
        Vector3d expected_product_origin(1 + 1 / sqrt(2.0), 0, 1 / sqrt(2.0));
        Frame3d quotient = frame / frame;
        TS_ASSERT(Comparison::equal(product.origin(), expected_product_origin));
        TS_ASSERT(Comparison::equal(product.xVector(), Vector3d(0, 0, 1)));
        TS_ASSERT(Comparison::equal(product.yVector(), Vector3d(0, 1, 0)));
        TS_ASSERT(Comparison::equal(product.zVector(), Vector3d(-1, 0, 0)));
        TS_ASSERT(Comparison::zero(quotient.origin()));
        TS_ASSERT(quotient.vectors().isIdentity(Comparison::tolerance()));
    }
    
    void test2D() {
        Frame2d frame(Vector2d::UnitX(), Vector2d(1, 1));
        TS_ASSERT_EQUALS(frame.vectors().rows(), 2);
        TS_ASSERT_EQUALS(frame.vectors().cols(), 2);
        TS_ASSERT(Comparison::equal(frame.xVector(), Vector2d(1, 1).normalized()));
        TS_ASSERT(Comparison::equal(frame.yVector(), Vector2d(-1, 1).normalized()));
        TS_ASSERT(Comparison::equal(Vector2d(2, 2) * frame, Vector2d(1, 2 * sqrt(2.0))));
        TS_ASSERT(Comparison::equal(Vector2d(2, 1) / frame, Vector2d(sqrt(2.0), 0)));
    }
    
    void testAccuracy() {
        Matrix3d vectors;
        Frame3d frame;
        
        vectors = Matrix3d::Random();
        frame = Frame3d(Vector3d::Ones(), vectors);
        std::cout << frame.vectors() << std::endl;
        std::cout << std::endl;
        std::cout << frame.vectors() * frame.vectors().transpose() << std::endl;
        std::cout << std::endl;
        std::cout << vectors / frame.linear() << std::endl;
        std::cout << std::endl;
        
        vectors = Matrix3d::Random();
        frame = Frame3d(Vector3d::Ones(), vectors);
        std::cout << frame.vectors() << std::endl;
        std::cout << std::endl;
        std::cout << frame.vectors() * frame.vectors().transpose() << std::endl;
        std::cout << std::endl;
        std::cout << vectors / frame.linear() << std::endl;
        std::cout << std::endl;
        
        vectors = Matrix3d::Random();
        frame = Frame3d(Vector3d::Ones(), vectors);
        std::cout << frame.vectors() << std::endl;
        std::cout << std::endl;
        std::cout << frame.vectors() * frame.vectors().transpose() << std::endl;
        std::cout << std::endl;
        std::cout << vectors / frame.linear() << std::endl;
        std::cout << std::endl;
    }
    
    void testNonOrthogonal() {
        CoordinateSystem3d coordinate_system(
            Vector3d(1, 2, 3),
            Matrix3d::Ones().triangularView<Upper>()
        );
        TS_ASSERT(Comparison::equal(Vector3d(1, 1, 1) * coordinate_system, Vector3d(4, 4, 4)));
        TS_ASSERT(Comparison::equal(Vector3d(4, 4, 4) / coordinate_system, Vector3d(1, 1, 1)));
    }
};
