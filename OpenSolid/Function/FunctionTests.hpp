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

#include <OpenSolid/Scalar/Comparison.hpp>
#include <OpenSolid/Function/Function.hpp>

using namespace OpenSolid;

class FunctionTests : public CxxTest::TestSuite
{
public:
    void testConstant() {
        Function f = 3.0;
        TS_ASSERT(f.isA<ConstantFunction>());
        TS_ASSERT(f(0.0).value() == Approx(3.0));
        TS_ASSERT(f.as<ConstantFunction>().vector().value() == Approx(3.0));
    }
    
    void testArithmetic() {
        Function function = 2.0 + Parameter(2, 0) * 1.0 - 1.0 * Parameter(2, 1);
        
        TS_ASSERT(function(Vector2d(0, 0)).value() == Approx(2.0));
        TS_ASSERT(function(Vector2d(1, 0)).value() == Approx(3.0));
        TS_ASSERT(function(Vector2d(1, 1)).value() == Approx(2.0));
        TS_ASSERT(function(Vector2d(0, 1)).value() == One());
        TS_ASSERT(function.derivative(0)(Vector2d(0, 0)).value() == One());
        TS_ASSERT(function.derivative(1)(Vector2d(0, 0)).value() == -One());
        
        Function negated = -function;
        
        TS_ASSERT(negated(Vector2d(0, 0)).value() == -Approx(2.0));
        TS_ASSERT(negated(Vector2d(1, 0)).value() == -Approx(3.0));
        TS_ASSERT(negated(Vector2d(1, 1)).value() == -Approx(2.0));
        TS_ASSERT(negated(Vector2d(0, 1)).value() == -One());
        TS_ASSERT(negated.derivative(0)(Vector2d(0, 0)).value() == -One());
        TS_ASSERT(negated.derivative(1)(Vector2d(0, 0)).value() == One());
    }

    void testMultiplication() {
        Function function = 1.0 + Parameter(2, 0) / 1.0 * Parameter(2, 1) / 1.0;
    
        TS_ASSERT(function(Vector2d(0, 0)).value() == One());
        TS_ASSERT(function(Vector2d(1, 0)).value() == One());
        TS_ASSERT(function(Vector2d(1, 1)).value() == Approx(2.0));
        TS_ASSERT(function(Vector2d(0, 1)).value() == One());
    
        Function u_derivative = function.derivative(0);
        
        TS_ASSERT(u_derivative(Vector2d(0, 0)).value() == Zero());
        TS_ASSERT(u_derivative(Vector2d(1, 0)).value() == Zero());
        TS_ASSERT(u_derivative(Vector2d(1, 1)).value() == One());
        TS_ASSERT(u_derivative(Vector2d(0, 1)).value() == One());
    
        Function v_derivative = function.derivative(1);
        
        TS_ASSERT(v_derivative(Vector2d(0, 0)).value() == Zero());
        TS_ASSERT(v_derivative(Vector2d(1, 0)).value() == One());
        TS_ASSERT(v_derivative(Vector2d(1, 1)).value() == One());
        TS_ASSERT(v_derivative(Vector2d(0, 1)).value() == Zero());
    }
    
    void testSquare() {
        Parameter u(2, 0);
        Parameter v(2, 1);
        Function function = u.squaredNorm() * 1.0 + v.squaredNorm() * 1.0;
        TS_ASSERT(function(Vector2d(1, 2)).value() == Approx(5.0));
        Function u_derivative = function.derivative(0);
        TS_ASSERT(u_derivative(Vector2d(3, 4)).value() == Approx(6.0));
        Function v_second_derivative = function.derivative(1).derivative(1);
        TS_ASSERT(v_second_derivative(Vector2d(5, 6)).value() == Approx(2.0));
    }

    void testNorm() {
        Function arc = 3 * (cos(Parameter()) * Vector2d(1, 0) +
            Vector2d::UnitY() * sin(Parameter()));
        TS_ASSERT(arc.normalized()(M_PI / 4).isApprox(Vector2d(1 / sqrt(2.0), 1 / sqrt(2.0))));
    }
    
    void testVector() {
        Function f = Vector3d(1, 2, 3);
        TS_ASSERT(f.isA<ConstantFunction>());
        TS_ASSERT(f.as<ConstantFunction>().vector() == Vector3d(1, 2, 3));
        TS_ASSERT(f.as<ConstantFunction>().vector().transpose() == RowVector3d(1, 2, 3));
    }
    
    void testConversion() {
        Function function = Parameter(2, 0) * Parameter(2, 1);
        TS_ASSERT(function(Vector2d(2, 3)).value() == Approx(6.0));
        function = Function(2);
        TS_ASSERT(function(RowVector3d(1, 2, 3)) == RowVector3d::Constant(2));
    }
    
    void testSine() {
        Function f = sin(Parameter());
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
        RowVector4I expected_bounds(
            Interval(0, 1),
            Interval(0, 1),
            Interval(-1, 0),
            Interval(-1, 1)
        );
        TS_ASSERT(bounds.cwiseLower().isApprox(expected_bounds.cwiseLower()));
        TS_ASSERT(bounds.cwiseUpper().isApprox(expected_bounds.cwiseUpper()));
    }
    
    void testCosine() {
        Function f = cos(Parameter());
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
        RowVector4I expected_bounds(
            Interval(0, 1),
            Interval(-1, 0),
            Interval(-1, 0),
            Interval(-1, 1)
        );
        TS_ASSERT(bounds.cwiseLower().isApprox(expected_bounds.cwiseLower()));
        TS_ASSERT(bounds.cwiseUpper().isApprox(expected_bounds.cwiseUpper()));
    }
    
    void testComponent() {
        Function f = Vector3d(1, 2, 3) + Parameter() * Vector3d(1, 2, 3);
        RowVector3d result = f.component(1)(RowVector3d(0, 0.5, 1));
        TS_ASSERT(result.isApprox(RowVector3d(2, 3, 4)));
        result = f(RowVector3d(0, 0.5, 1)).row(1);
        TS_ASSERT(result.isApprox(RowVector3d(2, 3, 4)));
        double value = f.z()(0.5).value();
        TS_ASSERT(value == Approx(4.5));
    }
    
    void testTransformation() {
        Frame3d frame;
        frame = frame.translatedBy(Vector3d(1, 1, 1));
        frame = frame.rotatedBy(M_PI / 4, frame.zAxis());
        Function linear = Vector3d::Ones() * Parameter();
        Function product = linear * frame;
        Function quotient = linear / frame;
        RowVectorXd parameter_values = RowVectorXd::LinSpaced(5, Interval(0, 1));
        MatrixXd product_values = (Vector3d(0, sqrt(2.0), 1) * parameter_values).colwise() +
            Vector3d(1, 1, 1);
        MatrixXd quotient_values = (Vector3d(sqrt(2.0), 0, 1) * parameter_values).colwise() +
            Vector3d(-sqrt(2.0), 0, -1);
        TS_ASSERT(product(parameter_values).isApprox(product_values));
        TS_ASSERT(quotient(parameter_values).isApprox(quotient_values));
    }
    
    void testConcatenation() {
        Function x = Parameter();
        double y = 3;
        Function z = Parameter().squaredNorm();
        Function concatenated(x, y, z);
        TS_ASSERT(concatenated(2.0).isApprox(Vector3d(2.0, 3.0, 4.0)));
    }

    void testArccosine() {
        Function f = acos(Parameter());
        Interval bounds;
        bounds = f(Interval(-1, 0)).value();
        TS_ASSERT(bounds.lower() - M_PI / 2 == Zero());
        TS_ASSERT(bounds.upper() - M_PI == Zero());
        bounds = f(Interval(0.5, 1.5)).value();
        TS_ASSERT(bounds.lower() == Zero());
        TS_ASSERT(bounds.upper() - M_PI / 3 == Zero());
        bounds = f(Interval(1 + 1e-14, 1 + 1e-10)).value();
        TS_ASSERT(bounds.lower() == Zero());
        TS_ASSERT(bounds.upper() == Zero());
    }

    void testArcsine() {
        Function f = asin(Parameter());
        Interval bounds;
        bounds = f(Interval(-1, 0)).value();
        TS_ASSERT(bounds.lower() + M_PI / 2 == Zero());
        TS_ASSERT(bounds.upper() == Zero());
        bounds = f(Interval(0.5, 1.5)).value();
        TS_ASSERT(bounds.lower() - M_PI / 6 == Zero());
        TS_ASSERT(bounds.upper() - M_PI / 2 == Zero());
        bounds = f(Interval(1 + 1e-14, 1 + 1e-10)).value();
        TS_ASSERT(bounds.lower() - M_PI / 2 == Zero());
        TS_ASSERT(bounds.upper() - M_PI / 2 == Zero());
    }

    void testMirrored() {
        Datum3d mirror = Frame3d().yzPlane().translatedBy(Vector3d(1, 0, 0)).mirror();
        Function f = Vector3d(1, 1, 1) + Parameter() * Vector3d(1, 1, 1);
        Function mirrored1 = f * mirror;
        Function mirrored2 = f / mirror;
        TS_ASSERT((mirrored1(1) - Vector3d(0, 2, 2)).isZero());
        TS_ASSERT((mirrored2(1) - Vector3d(0, 2, 2)).isZero());
        Function derivative1 = mirrored1.derivative();
        Function derivative2 = mirrored2.derivative();
        TS_ASSERT(derivative1.isA<ConstantFunction>());
        TS_ASSERT(derivative2.isA<ConstantFunction>());
        TS_ASSERT((derivative1.as<ConstantFunction>().vector() - Vector3d(-1, 1, 1)).isZero());
        TS_ASSERT((derivative2.as<ConstantFunction>().vector() - Vector3d(-1, 1, 1)).isZero());
    }
    
    void testZeros() {
        std::vector<Function> functions(7);
        std::vector<Interval> domains(7);
        std::vector<RowVectorXd> expected_function_zeros(7);
        std::vector<RowVectorXd> expected_derivative_zeros(7);
        std::vector<RowVectorXd> expected_second_derivative_zeros(7);
        
        Parameter x;

        functions[0] = x - 1;
        domains[0] = Interval(0, 2);
        expected_function_zeros[0] = RowVectorXd::Constant(1, 1.0);
        expected_derivative_zeros[0] = RowVectorXd();
        expected_second_derivative_zeros[0] = RowVectorXd();

        functions[1] = x.squaredNorm() - 1;
        domains[1] = Interval(-2, 2);
        expected_function_zeros[1] = RowVector2d(-1, 1);
        expected_derivative_zeros[1] = RowVectorXd::Constant(1, 0.0);
        expected_second_derivative_zeros[1] = RowVectorXd();

        functions[2] = x * x * x - 4 * x * x + 5 * x - 2;
        domains[2] = Interval(0, 3);
        expected_function_zeros[2] = RowVector2d(1, 2);
        expected_derivative_zeros[2] = RowVector2d(1, 5.0 / 3.0);
        expected_second_derivative_zeros[2] = RowVectorXd::Constant(1, 4.0 / 3.0);

        functions[3] = sin(x).squaredNorm() + 2 * sin(x) + 1;
        domains[3] = Interval(-M_PI, 2 * M_PI);
        expected_function_zeros[3] = RowVector2d(-M_PI / 2, 3 * M_PI / 2);
        expected_derivative_zeros[3] = RowVector3d(-M_PI / 2, M_PI / 2, 3 * M_PI / 2);
        expected_second_derivative_zeros[3] = RowVector4d(
            -M_PI / 2,
            M_PI / 6,
            5 * M_PI / 6,
            3 * M_PI / 2
        );

        functions[4] = sqrt(x) - 0.5;
        domains[4] = Interval(0, 1);
        expected_function_zeros[4] = RowVectorXd::Constant(1, 0.25);
        expected_derivative_zeros[4] = RowVectorXd();
        expected_second_derivative_zeros[4] = RowVectorXd();

        functions[5] = 1 / x - 1;
        domains[5] = Interval(0, 2);
        expected_function_zeros[5] = RowVectorXd::Constant(1, 1.0);
        expected_derivative_zeros[5] = RowVectorXd();
        expected_second_derivative_zeros[5] = RowVectorXd();

        functions[6] = sqrt(x) - x;
        domains[6] = Interval(0, 2);
        expected_function_zeros[6] = RowVector2d(0, 1);
        expected_derivative_zeros[6] = RowVectorXd::Constant(1, 0.25);
        expected_second_derivative_zeros[6] = RowVectorXd();

        for (int i = 0; i < 5; ++i) {
            Function function = functions[i];
            Function derivative = function.derivative();
            Function second_derivative = derivative.derivative();
            
            RowVectorXd function_values = function(expected_function_zeros[i]);
            RowVectorXd derivative_values = derivative(expected_derivative_zeros[i]);
            RowVectorXd second_derivative_values =
                second_derivative(expected_second_derivative_zeros[i]);
                
            TS_ASSERT(function_values.isZero());
            TS_ASSERT(derivative_values.isZero());
            TS_ASSERT(second_derivative_values.isZero());
            
            RowVectorXd function_zeros;
            boost::timer timer;
            for (int j = 0; j < 100; ++j) {function_zeros = function.roots(domains[i]);}
            double elapsed = timer.elapsed();
            RowVectorXd derivative_zeros = derivative.roots(domains[i]);
            RowVectorXd second_derivative_zeros = second_derivative.roots(domains[i]);
                
            TS_ASSERT(function_zeros.isApprox(expected_function_zeros[i]));
            TS_ASSERT(derivative_zeros.isApprox(expected_derivative_zeros[i]));
            TS_ASSERT(second_derivative_zeros.isApprox(expected_second_derivative_zeros[i]));
            
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
        Parameter x;
        double R = 1;
        double r = 0.5;
        double slope = 0.5;
        Function radius_function = R - r + sqrt(x * (2 * r - x));
        Function derivative_difference = radius_function.derivative() - 1 / slope;
        RowVectorXd parameter_values = RowVectorXd::LinSpaced(20, Interval(0, r));
        std::cout << derivative_difference(parameter_values) << std::endl;
        RowVectorXd root = derivative_difference.roots(Interval(0, r));
        std::cout << root << std::endl;
        TS_ASSERT_EQUALS(root.size(), 1);
        TS_ASSERT(root.value() == Approx(0.052786404500042038));
    }
};
