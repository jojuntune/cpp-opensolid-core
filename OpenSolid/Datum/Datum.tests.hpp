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

#include <OpenSolid/Value/Tolerance.hpp>
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
        TS_ASSERT((product - Vector3d(1, 1 + sqrt(2.0), 2)).isZero(Tolerance::roundoff()));
        product = Vector3d(1, 1, 1) * frame.linear();
        std::cout << product.transpose() << std::endl;
        TS_ASSERT((product - Vector3d(0, sqrt(2.0), 1)).isZero(Tolerance::roundoff()));
    }
    
    void testQuotient() {
        MatrixXd vectors(3, 2);
        vectors << Vector3d(1, 1, 0), Vector3d(-1, 1, 0);
        Frame3d frame(Vector3d(1, 1, 1), vectors);
        Vector3d quotient = Vector3d(1, 0, 0) / frame;
        std::cout << quotient.transpose() << std::endl;
        Vector3d quotient_error = quotient - Vector3d(-1 / sqrt(2.0), -1 / sqrt(2.0), -1);
        TS_ASSERT(quotient_error.isZero(Tolerance::roundoff()));
        Vector3d linear_quotient = Vector3d(1, 0, 0) / frame.linear();
        std::cout << linear_quotient.transpose() << std::endl;
        Vector3d linear_quotient_error =
            linear_quotient - Vector3d(1 / sqrt(2.0), -1 / sqrt(2.0), 0);
        TS_ASSERT(linear_quotient_error.isZero(Tolerance::roundoff()));
    }
    
    void testDatumTransformation() {
        Frame3d global;
        Frame3d frame = global.translatedBy(Vector3d(1, 1, 1)).rotatedBy(-M_PI / 2, global.xAxis());
        TS_ASSERT((Vector3d(1, 2, 3) * frame - Vector3d(2, 4, -3)).isZero(Tolerance::roundoff()));
    }
    
    void testDatumComposition() {
        Frame3d frame(Vector3d::UnitX(), Matrix3d::Identity());
        frame = frame.rotatedBy(-M_PI / 4, frame.yAxis());
        Frame3d product = frame * frame;
        Frame3d quotient = frame / frame;
        Vector3d origin_error = product.origin() - Vector3d(1 + 1 / sqrt(2.0), 0, 1 / sqrt(2.0));
        TS_ASSERT(origin_error.isZero(Tolerance::roundoff()));
        TS_ASSERT((product.xVector() - Vector3d(0, 0, 1)).isZero(Tolerance::roundoff()));
        TS_ASSERT((product.yVector() - Vector3d(0, 1, 0)).isZero(Tolerance::roundoff()));
        TS_ASSERT((product.zVector() - Vector3d(-1, 0, 0)).isZero(Tolerance::roundoff()));
        TS_ASSERT(quotient.origin().isZero(Tolerance::roundoff()));
        TS_ASSERT(quotient.vectors().isIdentity(Tolerance::roundoff()));
    }
    
    void test2D() {
        Frame2d frame(Vector2d::UnitX(), Vector2d(1, 1));
        TS_ASSERT_EQUALS(frame.vectors().rows(), 2);
        TS_ASSERT_EQUALS(frame.vectors().cols(), 2);
        TS_ASSERT((frame.xVector() - Vector2d(1, 1).normalized()).isZero(Tolerance::roundoff()));
        TS_ASSERT((frame.yVector() - Vector2d(-1, 1).normalized()).isZero(Tolerance::roundoff()));
        Vector2d product_error = Vector2d(2, 2) * frame - Vector2d(1, 2 * sqrt(2.0));
        TS_ASSERT(product_error.isZero(Tolerance::roundoff()));
        Vector2d quotient_error = Vector2d(2, 1) / frame - Vector2d(sqrt(2.0), 0);
        TS_ASSERT(quotient_error.isZero(Tolerance::roundoff()));
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
        Datum3d datum(
            Vector3d(1, 2, 3),
            Matrix3d::Ones().triangularView<Upper>()
        );
        Vector3d product_error = Vector3d(1, 1, 1) * datum - Vector3d(4, 4, 4);
        TS_ASSERT(product_error.isZero(Tolerance::roundoff()));
        Vector3d quotient_error = Vector3d(4, 4, 4) / datum - Vector3d(1, 1, 1);
        TS_ASSERT(quotient_error.isZero(Tolerance::roundoff()));
    }
};
