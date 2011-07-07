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

#include <boost/timer.hpp>
#include <cxxtest/TestSuite.h>

#include <OpenSolid/Function/Function.hpp>

using namespace OpenSolid;

class FunctionTestSuite : public CxxTest::TestSuite
{
public:
    void testConstant() {
        Function f = 3.0;
        TS_ASSERT(f.isA<ConstantFunction>());
        TS_ASSERT(f(0.0).value().isEqualTo(3.0));
        TS_ASSERT(f.as<ConstantFunction>().vector().value().isEqualTo(3.0));
    }
    
    void testArithmetic() {
        Function function = 2.0 + Function::u * 1.0 - 1.0 * Function::v;
        
        TS_ASSERT(function(Vector2D(0, 0)).value().isEqualTo(2.0));
        TS_ASSERT(function(Vector2D(1, 0)).value().isEqualTo(3.0));
        TS_ASSERT(function(Vector2D(1, 1)).value().isEqualTo(2.0));
        TS_ASSERT(function(Vector2D(0, 1)).value().isEqualTo(1.0));
        TS_ASSERT(function.derivative(0)(Vector2D(0, 0)).value().isEqualTo(1.0));
        TS_ASSERT(function.derivative(1)(Vector2D(0, 0)).value().isEqualTo(-1.0));
        
        Function negated = -function;
        
        TS_ASSERT(negated(Vector2D(0, 0)).value().isEqualTo(-2.0));
        TS_ASSERT(negated(Vector2D(1, 0)).value().isEqualTo(-3.0));
        TS_ASSERT(negated(Vector2D(1, 1)).value().isEqualTo(-2.0));
        TS_ASSERT(negated(Vector2D(0, 1)).value().isEqualTo(-1.0));
        TS_ASSERT(negated.derivative(0)(Vector2D(0, 0)).value().isEqualTo(-1.0));
        TS_ASSERT(negated.derivative(1)(Vector2D(0, 0)).value().isEqualTo(1.0));
    }

    void testMultiplication() {
        Function function = 1.0 + Function::u / 1.0 * Function::v / 1.0;
    
        TS_ASSERT(function(Vector2D(0, 0)).value().isEqualTo(1.0));
        TS_ASSERT(function(Vector2D(1, 0)).value().isEqualTo(1.0));
        TS_ASSERT(function(Vector2D(1, 1)).value().isEqualTo(2.0));
        TS_ASSERT(function(Vector2D(0, 1)).value().isEqualTo(1.0));
    
        Function u_derivative = function.derivative(0);
        
        TS_ASSERT(u_derivative(Vector2D(0, 0)).isZero());
        TS_ASSERT(u_derivative(Vector2D(1, 0)).isZero());
        TS_ASSERT(u_derivative(Vector2D(1, 1)).value().isEqualTo(1.0));
        TS_ASSERT(u_derivative(Vector2D(0, 1)).value().isEqualTo(1.0));
    
        Function v_derivative = function.derivative(1);
        
        TS_ASSERT(v_derivative(Vector2D(0, 0)).isZero());
        TS_ASSERT(v_derivative(Vector2D(1, 0)).value().isEqualTo(1.0));
        TS_ASSERT(v_derivative(Vector2D(1, 1)).value().isEqualTo(1.0));
        TS_ASSERT(v_derivative(Vector2D(0, 1)).isZero());
    }
    
    void testSquare() {
        Function function = Function::u.squaredNorm() * 1.0 + Function::v.squaredNorm() * 1.0;
        TS_ASSERT(function(Vector2D(1, 2)).value().isEqualTo(5.0));
        Function u_derivative = function.derivative(0);
        TS_ASSERT(u_derivative(Vector2D(3, 4)).value().isEqualTo(6.0));
        Function v_second_derivative = function.derivative(1).derivative(1);
        TS_ASSERT(v_second_derivative(Vector2D(5, 6)).value().isEqualTo(2.0));
    }

    void testNorm() {
        Function arc = 3 * (cos(Function::t) * Vector2D(1, 0) +
            Vector2D::UnitY() * sin(Function::t));
        TS_ASSERT(arc.normalized()(M_PI / 4).isEqualTo(Vector2D(1 / sqrt(2.0), 1 / sqrt(2.0))))
    }
    
    void testVector() {
        Function f = Vector3D(1, 2, 3);
        TS_ASSERT(f.isA<ConstantFunction>());
        TS_ASSERT(f.as<ConstantFunction>().vector() == Vector3D(1, 2, 3));
        TS_ASSERT(f.as<ConstantFunction>().vector().transpose() == RowVector3D(1, 2, 3));
    }
    
    void testConversion() {
        Function function = Function::u * Function::v;
        TS_ASSERT(function(Vector2D(2, 3)).value().isEqualTo(6.0));
    }
    
    void testSine() {
        Function f = sin(Function::t);
        RowVector4D result = f(RowVector4D(0, M_PI / 2, M_PI, 3 * M_PI / 2));
        TS_ASSERT(result.isEqualTo(RowVector4D(0, 1, 0, -1)));
        RowVector4I bounds = f(
            RowVector4I(
                Interval(0, M_PI / 2),
                Interval(M_PI / 2, M_PI),
                Interval(M_PI, 3 * M_PI / 2),
                Interval(0, 2 * M_PI)
            )
        );
        RowVector4I expected_bounds(
            Interval(0, 1),
            Interval(0, 1),
            Interval(-1, 0),
            Interval(-1, 1)
        );
        TS_ASSERT(bounds.cwiseLower().isEqualTo(expected_bounds.cwiseLower()));
        TS_ASSERT(bounds.cwiseUpper().isEqualTo(expected_bounds.cwiseUpper()));
    }
    
    void testCosine() {
        Function f = cos(Function::t);
        RowVector4D result = f(RowVector4D(0, M_PI / 2, M_PI, 3 * M_PI / 2));
        TS_ASSERT(result.isEqualTo(RowVector4D(1, 0, -1, 0)));
        RowVector4I bounds = f(
            RowVector4I(
                Interval(0, M_PI / 2),
                Interval(M_PI / 2, M_PI),
                Interval(M_PI, 3 * M_PI / 2),
                Interval(0, 2 * M_PI)
            )
        );
        RowVector4I expected_bounds(
            Interval(0, 1),
            Interval(-1, 0),
            Interval(-1, 0),
            Interval(-1, 1)
        );
        TS_ASSERT(bounds.cwiseLower().isEqualTo(expected_bounds.cwiseLower()));
        TS_ASSERT(bounds.cwiseUpper().isEqualTo(expected_bounds.cwiseUpper()));
    }
    
    void testComponent() {
        Function f = Vector3D(1, 2, 3) + Function::t * Vector3D(1, 2, 3);
        RowVector3D result = f.component(1)(RowVector3D(0, 0.5, 1));
        TS_ASSERT(result.isEqualTo(RowVector3D(2, 3, 4)));
        result = f(RowVector3D(0, 0.5, 1)).row(1);
        TS_ASSERT(result.isEqualTo(RowVector3D(2, 3, 4)));
    }
    
    void testTransformation() {
        Frame3D frame;
        frame = frame.translatedBy(Vector3D(1, 1, 1));
        frame = frame.rotatedBy(M_PI / 4, frame.zAxis());
        Function linear = Vector3D::Ones() * Function::t;
        Function product = linear * frame;
        Function quotient = linear / frame;
        RowVectorXD parameter_values = RowVectorXD::LinSpaced(5, Interval(0, 1));
        MatrixXD product_values = (Vector3D(0, sqrt(2.0), 1) * parameter_values).colwise() +
            Vector3D(1, 1, 1);
        MatrixXD quotient_values = (Vector3D(sqrt(2.0), 0, 1) * parameter_values).colwise() +
            Vector3D(-sqrt(2.0), 0, -1);
        TS_ASSERT(product(parameter_values).isEqualTo(product_values));
        TS_ASSERT(quotient(parameter_values).isEqualTo(quotient_values));
    }
    
    void testConcatenation() {
        Function x = Function::t;
        Double y = 3;
        Function z = Function::t.squaredNorm();
        Function concatenated(x, y, z);
        TS_ASSERT(concatenated(2.0).isEqualTo(Vector3D(2.0, 3.0, 4.0)));
    }
    
    void testZeros() {
        std::vector<Function> functions(7);
        std::vector<Interval> domains(7);
        std::vector<RowVectorXD> expected_function_zeros(7);
        std::vector<RowVectorXD> expected_derivative_zeros(7);
        std::vector<RowVectorXD> expected_second_derivative_zeros(7);
        
        Function x = Function::Parameter(1, 0);

        functions[0] = x - 1;
        domains[0] = Interval(0, 2);
        expected_function_zeros[0] = RowVectorXD::Constant(1, 1.0);
        expected_derivative_zeros[0] = RowVectorXD();
        expected_second_derivative_zeros[0] = RowVectorXD();

        functions[1] = x.squaredNorm() - 1;
        domains[1] = Interval(-2, 2);
        expected_function_zeros[1] = RowVector2D(-1, 1);
        expected_derivative_zeros[1] = RowVectorXD::Constant(1, 0.0);
        expected_second_derivative_zeros[1] = RowVectorXD();

        functions[2] = x * x * x - 4 * x * x + 5 * x - 2;
        domains[2] = Interval(0, 3);
        expected_function_zeros[2] = RowVector2D(1, 2);
        expected_derivative_zeros[2] = RowVector2D(1, 5.0 / 3.0);
        expected_second_derivative_zeros[2] = RowVectorXD::Constant(1, 4.0 / 3.0);

        functions[3] = sin(x).squaredNorm() + 2 * sin(x) + 1;
        domains[3] = Interval(-M_PI, 2 * M_PI);
        expected_function_zeros[3] = RowVector2D(-M_PI / 2, 3 * M_PI / 2);
        expected_derivative_zeros[3] = RowVector3D(-M_PI / 2, M_PI / 2, 3 * M_PI / 2);
        expected_second_derivative_zeros[3] = RowVector4D(-M_PI / 2, M_PI / 6, 5 * M_PI / 6, 3 * M_PI / 2);

        functions[4] = sqrt(x) - 0.5;
        domains[4] = Interval(0, 1);
        expected_function_zeros[4] = RowVectorXD::Constant(1, 0.25);
        expected_derivative_zeros[4] = RowVectorXD();
        expected_second_derivative_zeros[4] = RowVectorXD();

        functions[5] = 1 / x - 1;
        domains[5] = Interval(0, 2);
        expected_function_zeros[5] = RowVectorXD::Constant(1, 1.0);
        expected_derivative_zeros[5] = RowVectorXD();
        expected_second_derivative_zeros[5] = RowVectorXD();

        functions[6] = sqrt(x) - x;
        domains[6] = Interval(0, 2);
        expected_function_zeros[6] = RowVector2D(0, 1);
        expected_derivative_zeros[6] = RowVectorXD::Constant(1, 0.25);
        expected_second_derivative_zeros[6] = RowVectorXD();

        for (int i = 0; i < 5; ++i) {
            Function function = functions[i];
            Function derivative = function.derivative();
            Function second_derivative = derivative.derivative();
            
            RowVectorXD function_values = function(expected_function_zeros[i]);
            RowVectorXD derivative_values = derivative(expected_derivative_zeros[i]);
            RowVectorXD second_derivative_values =
                second_derivative(expected_second_derivative_zeros[i]);
                
            TS_ASSERT(function_values.isZero());
            TS_ASSERT(derivative_values.isZero());
            TS_ASSERT(second_derivative_values.isZero());
            
            RowVectorXD function_zeros;
            boost::timer timer;
            for (int j = 0; j < 100; ++j) {function_zeros = function.zeros(domains[i]);}
            Double elapsed = timer.elapsed();
            RowVectorXD derivative_zeros = derivative.zeros(domains[i]);
            RowVectorXD second_derivative_zeros = second_derivative.zeros(domains[i]);
                
            TS_ASSERT(function_zeros.isEqualTo(expected_function_zeros[i]));
            TS_ASSERT(derivative_zeros.isEqualTo(expected_derivative_zeros[i]));
            TS_ASSERT(second_derivative_zeros.isEqualTo(expected_second_derivative_zeros[i]));
            
            std::cout << "i = " << i << std::endl;
            std::cout << "  elapsed = " << elapsed << std::endl;
            
            std::cout << "  function_zeros = " << function_zeros << std::endl;
            std::cout << "  function_errors = ";
            std::cout << function_zeros - expected_function_zeros[i] << std::endl;
            
            std::cout << "  derivative_zeros = " << derivative_zeros << std::endl;
            std::cout << "  derivative_errors = ";
            std::cout << derivative_zeros - expected_derivative_zeros[i] << std::endl;
            
            std::cout << "  second_derivative_zeros = " << second_derivative_zeros << std::endl;
            std::cout << "  second_derivative_errors = ";
            std::cout << second_derivative_zeros - expected_second_derivative_zeros[i] << std::endl;
        }
    }
    
    void xtestCircleDerivativeZeros() {
        Function x = Function::Parameter(1, 0);
        Double R = 1;
        Double r = 0.5;
        Double slope = 0.5;
        Function radius_function = R - r + sqrt(x * (2 * r - x));
        Function derivative_difference = radius_function.derivative() - 1 / slope;
        RowVectorXD parameter_values = RowVectorXD::LinSpaced(20, Interval(0, r));
        std::cout << derivative_difference(parameter_values) << std::endl;
        RowVectorXD root = derivative_difference.zeros(Interval(0, r));
        std::cout << root << std::endl;
        TS_ASSERT_EQUALS(root.size(), 1);
        TS_ASSERT(root.value().isEqualTo(0.052786404500042038));
    }
};
