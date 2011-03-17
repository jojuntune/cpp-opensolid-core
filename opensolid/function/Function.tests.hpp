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

#include <opensolid/value/TempMatrix.hpp>
#include <opensolid/value/Tolerance.hpp>
#include <opensolid/value/check.hpp>
#include "Function.hpp"
#include "implementations/ConstantFunction.hpp"

using namespace opensolid;

void assertIsApprox(const MatrixXI& first_argument, const MatrixXI& second_argument) {
    checkSameSize(
        first_argument.rows(),
        first_argument.cols(),
        second_argument.rows(),
        second_argument.cols(),
        __func__
    );
    for (int j = 0; j < first_argument.cols(); ++j) {
        for (int i = 0; i < first_argument.rows(); ++i) {
            TS_ASSERT_DELTA(
                first_argument(i, j).lower(),
                second_argument(i, j).lower(),
                Tolerance::roundoff()
            );
            TS_ASSERT_DELTA(
                first_argument(i, j).upper(),
                second_argument(i, j).upper(),
                Tolerance::roundoff()
            );
        }
    }
}

class FunctionTestSuite : public CxxTest::TestSuite
{
public:
    void testConstant() {
        Function f = 3.0;
        TS_ASSERT(f.isA<ConstantFunction>());
        TS_ASSERT_EQUALS(f(0.0).scalar(), 3.0);
        TS_ASSERT_EQUALS(f.as<ConstantFunction>().value().scalar(), 3.0);
    }
    
    void testArithmetic() {
        Function function = 2.0 + Function::u * 1.0 - 1.0 * Function::v;
        
        TS_ASSERT_EQUALS(function(Vector2d(0, 0)).scalar(), 2.0);
        TS_ASSERT_EQUALS(function(Vector2d(1, 0)).scalar(), 3.0);
        TS_ASSERT_EQUALS(function(Vector2d(1, 1)).scalar(), 2.0);
        TS_ASSERT_EQUALS(function(Vector2d(0, 1)).scalar(), 1.0);
        TS_ASSERT_EQUALS(function.derivative(0)(Vector2d(0, 0)).scalar(), 1.0);
        TS_ASSERT_EQUALS(function.derivative(1)(Vector2d(0, 0)).scalar(), -1.0);
        
        Function negated = -function;
        
        TS_ASSERT_EQUALS(negated(Vector2d(0, 0)).scalar(), -2.0);
        TS_ASSERT_EQUALS(negated(Vector2d(1, 0)).scalar(), -3.0);
        TS_ASSERT_EQUALS(negated(Vector2d(1, 1)).scalar(), -2.0);
        TS_ASSERT_EQUALS(negated(Vector2d(0, 1)).scalar(), -1.0);
        TS_ASSERT_EQUALS(negated.derivative(0)(Vector2d(0, 0)).scalar(), -1.0);
        TS_ASSERT_EQUALS(negated.derivative(1)(Vector2d(0, 0)).scalar(), 1.0);
    }

    void testMultiplication() {
        Function function = 1.0 + Function::u / 1.0 * Function::v / 1.0;
    
        TS_ASSERT_EQUALS(function(Vector2d(0, 0)).scalar(), 1.0);
        TS_ASSERT_EQUALS(function(Vector2d(1, 0)).scalar(), 1.0);
        TS_ASSERT_EQUALS(function(Vector2d(1, 1)).scalar(), 2.0);
        TS_ASSERT_EQUALS(function(Vector2d(0, 1)).scalar(), 1.0);
    
        Function u_derivative = function.derivative(0);
        
        TS_ASSERT_EQUALS(u_derivative(Vector2d(0, 0)).scalar(), 0.0);
        TS_ASSERT_EQUALS(u_derivative(Vector2d(1, 0)).scalar(), 0.0);
        TS_ASSERT_EQUALS(u_derivative(Vector2d(1, 1)).scalar(), 1.0);
        TS_ASSERT_EQUALS(u_derivative(Vector2d(0, 1)).scalar(), 1.0);
    
        Function v_derivative = function.derivative(1);
        
        TS_ASSERT_EQUALS(v_derivative(Vector2d(0, 0)).scalar(), 0.0);
        TS_ASSERT_EQUALS(v_derivative(Vector2d(1, 0)).scalar(), 1.0);
        TS_ASSERT_EQUALS(v_derivative(Vector2d(1, 1)).scalar(), 1.0);
        TS_ASSERT_EQUALS(v_derivative(Vector2d(0, 1)).scalar(), 0.0);
    }
    
    void testSquare() {
        Function function = Function::u.squaredNorm() * 1.0 + Function::v.squaredNorm() * 1.0;
        TS_ASSERT_EQUALS(function(Vector2d(1, 2)).scalar(), 5.0);
        Function u_derivative = function.derivative(0);
        TS_ASSERT_EQUALS(u_derivative(Vector2d(3, 4)).scalar(), 6.0);
        Function v_second_derivative = function.derivative(1).derivative(1);
        TS_ASSERT_EQUALS(v_second_derivative(Vector2d(5, 6)).scalar(), 2.0);
    }

    void testNorm() {
        Function arc = 3 * (cos(Function::t) * Vector2d(1, 0) +
            Vector2d::UnitY() * sin(Function::t));
        TS_ASSERT(arc.normalized()(M_PI / 4).isApprox(Vector2d(1 / sqrt(2.0), 1 / sqrt(2.0))))
    }
    
    void testValue() {
        Function f = Vector3d(1, 2, 3);
        TS_ASSERT(f.isA<ConstantFunction>());
        TS_ASSERT(f.as<ConstantFunction>().value() == Vector3d(1, 2, 3));
        TS_ASSERT(f.as<ConstantFunction>().value().transpose() == RowVector3d(1, 2, 3));
    }
    
    void testConversion() {
        Function function = Function::u * Function::v;
        TS_ASSERT_EQUALS(function(Vector2d(2, 3)).scalar(), 6.0);
    }
    
    void testSine() {
        Function f = sin(Function::t);
        RowVector4d result = f(RowVector4d(0, M_PI / 2, M_PI, 3 * M_PI / 2));
        TS_ASSERT(result.isApprox(RowVector4d(0, 1, 0, -1)));
        RowVector4I bounds = f(
            RowVector4I(
                Interval(0, M_PI / 2),
                Interval(M_PI / 2, M_PI),
                Interval(M_PI, 3 * M_PI / 2),
                Interval(0, 2 * M_PI)
            )
        );
        assertIsApprox(
            bounds,
            RowVector4I(Interval(0, 1), Interval(0, 1), Interval(-1, 0), Interval(-1, 1))
        );
    }
    
    void testCosine() {
        Function f = cos(Function::t);
        RowVector4d result = f(RowVector4d(0, M_PI / 2, M_PI, 3 * M_PI / 2));
        TS_ASSERT(result.isApprox(RowVector4d(1, 0, -1, 0)));
        RowVector4I bounds = f(
            RowVector4I(
                Interval(0, M_PI / 2),
                Interval(M_PI / 2, M_PI),
                Interval(M_PI, 3 * M_PI / 2),
                Interval(0, 2 * M_PI)
            )
        );
        assertIsApprox(
            bounds,
            RowVector4I(Interval(0, 1), Interval(-1, 0), Interval(-1, 0), Interval(-1, 1))
        );
    }
    
    void testComponent() {
        Function f = Vector3d(1, 2, 3) + Function::t * Vector3d(1, 2, 3);
        RowVector3d result = f.component(1)(RowVector3d(0, 0.5, 1));
        TS_ASSERT_EQUALS(result, RowVector3d(2, 3, 4));
        result = f(RowVector3d(0, 0.5, 1)).row(1);
        TS_ASSERT_EQUALS(result, RowVector3d(2, 3, 4));
    }
    
    void testTransformation() {
        Frame3d frame;
        frame = frame.translatedBy(Vector3d(1, 1, 1));
        frame = frame.rotatedBy(M_PI / 4, frame.zAxis());
        Function linear = Vector3d::Ones() * Function::t;
        Function product = linear * frame;
        std::cout << "product:" << std::endl << product << std::endl;
        Function quotient = linear / frame;
        std::cout << "quotient:" << std::endl << quotient << std::endl;
        RowVectorXd parameter_values = RowVectorXd::LinSpaced(5, Interval(0, 1));
        MatrixXd product_values = (Vector3d(0, sqrt(2.0), 1) * parameter_values).colwise() +
            Vector3d(1, 1, 1);
        MatrixXd quotient_values = (Vector3d(sqrt(2.0), 0, 1) * parameter_values).colwise() +
            Vector3d(-sqrt(2.0), 0, -1);
        TS_ASSERT((product(parameter_values) - product_values).isZero(Tolerance::roundoff()));
        TS_ASSERT((quotient(parameter_values) - quotient_values).isZero(Tolerance::roundoff()));
    }
    
    void testTempMatrix() {
        Vector3d vector = Vector3d::Random();
        TempMatrixXd temp(vector, 5);
        TS_ASSERT_EQUALS(temp, vector.replicate(1, 5));
    }
};