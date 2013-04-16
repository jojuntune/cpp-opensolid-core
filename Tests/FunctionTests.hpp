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
*************************************************************************************/

#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <OpenSolid/Core/Function/ResultCache.hpp>
#include <OpenSolid/Core/FunctionImplementation/ConstantFunction.hpp>

#include <boost/timer.hpp>
#include <cxxtest/TestSuite.h>

#include <vector>

using namespace opensolid;

class FunctionTests : public CxxTest::TestSuite
{
private:
    Function t;
    Function u;
    Function v;
public:
    void setUp() {
        t = Function::t();
        u = Function::u();
        v = Function::v();
    }

    void testConstant() {
        Function f = Function::Constant(3.0, 1);
        TS_ASSERT(f.asConstant());
        TS_ASSERT(f(0.0).value() - 3 == Zero());
        TS_ASSERT(f.asConstant()->vector().value() - 3 == Zero());
    }
    
    void testArithmetic() {
        Function function = 2.0 + u * 1.0 - 1.0 * v;
        
        TS_ASSERT(function(Vector2d(0, 0)).value() - 2 == Zero());
        TS_ASSERT(function(Vector2d(1, 0)).value() - 3 == Zero());
        TS_ASSERT(function(Vector2d(1, 1)).value() - 2 == Zero());
        TS_ASSERT(function(Vector2d(0, 1)).value() - 1 == Zero());
        TS_ASSERT(function.derivative(0)(Vector2d(0, 0)).value() - 1 == Zero());
        TS_ASSERT(function.derivative(1)(Vector2d(0, 0)).value() + 1 == Zero());
        
        Function negated = -function;
        
        TS_ASSERT(negated(Vector2d(0, 0)).value() + 2 == Zero());
        TS_ASSERT(negated(Vector2d(1, 0)).value() + 3 == Zero());
        TS_ASSERT(negated(Vector2d(1, 1)).value() + 2 == Zero());
        TS_ASSERT(negated(Vector2d(0, 1)).value() + 1 == Zero());
        TS_ASSERT(negated.derivative(0)(Vector2d(0, 0)).value() + 1 == Zero());
        TS_ASSERT(negated.derivative(1)(Vector2d(0, 0)).value() - 1 == Zero());
    }

    void testMultiplication() {
        Function function = 1.0 + u / 1.0 * v / 1.0;
    
        TS_ASSERT(function(Vector2d(0, 0)).value() - 1 == Zero());
        TS_ASSERT(function(Vector2d(1, 0)).value() - 1 == Zero());
        TS_ASSERT(function(Vector2d(1, 1)).value() - 2 == Zero());
        TS_ASSERT(function(Vector2d(0, 1)).value() - 1 == Zero());
    
        Function u_derivative = function.derivative(0);
        
        TS_ASSERT(u_derivative(Vector2d(0, 0)).value() == Zero());
        TS_ASSERT(u_derivative(Vector2d(1, 0)).value() == Zero());
        TS_ASSERT(u_derivative(Vector2d(1, 1)).value() - 1 == Zero());
        TS_ASSERT(u_derivative(Vector2d(0, 1)).value() - 1 == Zero());
    
        Function v_derivative = function.derivative(1);
        
        TS_ASSERT(v_derivative(Vector2d(0, 0)).value() == Zero());
        TS_ASSERT(v_derivative(Vector2d(1, 0)).value() - 1 == Zero());
        TS_ASSERT(v_derivative(Vector2d(1, 1)).value() - 1 == Zero());
        TS_ASSERT(v_derivative(Vector2d(0, 1)).value() == Zero());
    }
    
    void testSquare() {
        Function function = u.squaredNorm() * 1.0 + v.squaredNorm() * 1.0;
        TS_ASSERT(function(Vector2d(1, 2)).value() - 5 == Zero());
        Function u_derivative = function.derivative(0);
        TS_ASSERT(u_derivative(Vector2d(3, 4)).value() - 6 == Zero());
        Function v_second_derivative = function.derivative(1).derivative(1);
        TS_ASSERT(v_second_derivative(Vector2d(5, 6)).value() - 2 == Zero());
    }

    void testNorm() {
        Function arc = 3 * (cos(t) * Vector2d(1, 0) + Vector2d::UnitY() * sin(t));
        TS_ASSERT((arc.normalized()(M_PI / 4) - Vector2d(1 / sqrt(2.0), 1 / sqrt(2.0))).isZero());
    }
    
    void testVector() {
        Function f = Function::Constant(Vector3d(1, 2, 3), 0);
        TS_ASSERT(f.asConstant());
        TS_ASSERT(f.asConstant()->vector() == Vector3d(1, 2, 3));
        TS_ASSERT(f.asConstant()->vector().transpose() == RowVector3d(1, 2, 3));
    }
    
    void testConversion() {
        Function function = u * v;
        TS_ASSERT(function(Vector2d(2, 3)).value() - 6 == Zero());
        function = Function::Constant(2.0, 1);
        TS_ASSERT(function(RowVector3d(1, 2, 3)) == RowVector3d::Constant(2));
    }
    
    void testSine() {
        typedef Matrix<Interval, 1, 4> RowVector4I;
        Function f = sin(t);
        RowVector4d result = f(RowVector4d(0, M_PI / 2, M_PI, 3 * M_PI / 2));
        TS_ASSERT((result - RowVector4d(0, 1, 0, -1)).isZero());
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
        TS_ASSERT((bounds.cwiseLower() - expected_bounds.cwiseLower()).isZero());
        TS_ASSERT((bounds.cwiseUpper() - expected_bounds.cwiseUpper()).isZero());
    }
    
    void testCosine() {
        typedef Matrix<Interval, 1, 4> RowVector4I;
        Function f = cos(t);
        RowVector4d result = f(RowVector4d(0, M_PI / 2, M_PI, 3 * M_PI / 2));
        TS_ASSERT((result - RowVector4d(1, 0, -1, 0)).isZero());
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
        TS_ASSERT((bounds.cwiseLower() - expected_bounds.cwiseLower()).isZero());
        TS_ASSERT((bounds.cwiseUpper() - expected_bounds.cwiseUpper()).isZero());
    }
    
    void testComponent() {
        Function f = Vector3d(1, 2, 3) + t * Vector3d(1, 2, 3);
        RowVector3d result = f.component(1)(RowVector3d(0, 0.5, 1));
        TS_ASSERT((result - RowVector3d(2, 3, 4)).isZero());
        result = f(RowVector3d(0, 0.5, 1)).row(1);
        TS_ASSERT((result - RowVector3d(2, 3, 4)).isZero());
        double value = f.z()(0.5).value();
        TS_ASSERT(value - 4.5 == Zero());
    }
    
    void testTransformation() {
        Frame3d frame;
        frame = frame.translated(Vector3d(1, 1, 1));
        frame = frame.rotatedAbout(M_PI / 4, frame.zAxis());
        Function linear = Vector3d::Ones() * t;
        Function product = frame.basisMatrix() * linear + frame.originPoint().vector();
        Function quotient = frame.inverseMatrix() * (linear - frame.originPoint().vector());
        RowVectorXd parameter_values = RowVectorXd::LinSpaced(5, Interval::Unit());
        MatrixXd product_values = (Vector3d(0, sqrt(2.0), 1) * parameter_values).colwise() +
            Vector3d(1, 1, 1);
        MatrixXd quotient_values = (Vector3d(sqrt(2.0), 0, 1) * parameter_values).colwise() +
            Vector3d(-sqrt(2.0), 0, -1);
        TS_ASSERT((product(parameter_values) - product_values).isZero());
        TS_ASSERT((quotient(parameter_values) - quotient_values).isZero());
    }
    
    void testConcatenation() {
        Function x = t;
        Function y = Function::Constant(3.0, 1);
        Function z = t.squaredNorm();
        Function concatenated = Function::FromComponents(x, y, z);
        TS_ASSERT((concatenated(2.0) - Vector3d(2.0, 3.0, 4.0)).isZero());
    }

    void testArccosine() {
        Function f = acos(t);
        Interval bounds;
        bounds = f(Interval(-1, 0)).value();
        TS_ASSERT(bounds.lowerBound() - M_PI / 2 == Zero());
        TS_ASSERT(bounds.upperBound() - M_PI == Zero());
        bounds = f(Interval(0.5, 1.5)).value();
        TS_ASSERT(bounds.lowerBound() == Zero());
        TS_ASSERT(bounds.upperBound() - M_PI / 3 == Zero());
        bounds = f(Interval(1 + 1e-14, 1 + 1e-10)).value();
        TS_ASSERT(bounds.lowerBound() == Zero());
        TS_ASSERT(bounds.upperBound() == Zero());
    }

    void testArcsine() {
        Function f = asin(t);
        Interval bounds;
        bounds = f(Interval(-1, 0)).value();
        TS_ASSERT(bounds.lowerBound() + M_PI / 2 == Zero());
        TS_ASSERT(bounds.upperBound() == Zero());
        bounds = f(Interval(0.5, 1.5)).value();
        TS_ASSERT(bounds.lowerBound() - M_PI / 6 == Zero());
        TS_ASSERT(bounds.upperBound() - M_PI / 2 == Zero());
        bounds = f(Interval(1 + 1e-14, 1 + 1e-10)).value();
        TS_ASSERT(bounds.lowerBound() - M_PI / 2 == Zero());
        TS_ASSERT(bounds.upperBound() - M_PI / 2 == Zero());
    }

    void testNormalVector() {
        Function f = Vector2d(1, 1) + 2 * Function::FromComponents(cos(t), sin(t));
        TS_ASSERT((f(-M_PI / 2) - Vector2d(1, -1)).isZero());
        TS_ASSERT((f(0) - Vector2d(3, 1)).isZero());
        TS_ASSERT((f(M_PI / 2) - Vector2d(1, 3)).isZero());

        Function normalVector = f.normalVector();
        TS_ASSERT((f(-M_PI / 2) + 2 * normalVector(-M_PI / 2) - Vector2d(1, 1)).isZero());
        TS_ASSERT((f(-M_PI / 4) + 2 * normalVector(-M_PI / 4) - Vector2d(1, 1)).isZero());
        TS_ASSERT((f(0) + 2 * normalVector(0) - Vector2d(1, 1)).isZero());
        TS_ASSERT((f(M_PI / 4) + 2 * normalVector(M_PI / 4) - Vector2d(1, 1)).isZero());
        TS_ASSERT((f(M_PI / 2) + 2 * normalVector(M_PI / 2) - Vector2d(1, 1)).isZero());
    }

    void testDeduplication() {
        Function constant1 = Function::Constant(Vector3d(1, 2, 3), 1);
        Function constant2 = Function::Constant(Vector3d(1, 2, 3), 1);
        Function constant3 = Function::Constant(Vector3d(1, 2, 4), 1);
        Function constant4 = Function::Constant(Vector3d(1, 2, 3), 2);

        TS_ASSERT(constant1.isDuplicate(constant2));
        TS_ASSERT(!constant1.isDuplicate(constant3));
        TS_ASSERT(!constant1.isDuplicate(constant4));

        Function function1;
        Function function2;

        function1 = t.squaredNorm() + 2 * t;
        function2 = t * 2 + t.squaredNorm();
        TS_ASSERT(function1.isDuplicate(function2));

        function1 = cos(u.squaredNorm() + v.squaredNorm());
        function2 = cos(v.squaredNorm() + u.squaredNorm());
        TS_ASSERT(function1.isDuplicate(function2));

        function1 = u.squaredNorm();
        function2 = v.squaredNorm();
        TS_ASSERT(!function1.isDuplicate(function2));

        function1 = sin(t);
        function1 = function2;
        TS_ASSERT(function1.isDuplicate(function1));
        TS_ASSERT(function1.isDuplicate(function2));

        function1 = sin(sqrt(u));
        function2 = sin(sqrt(u));
        TS_ASSERT(function1.isDuplicate(function2));
    }

    void testDeduplicatedOutput() {
        Function f = t.squaredNorm() + sin(t.squaredNorm());
        std::cout << std::endl;
        f.debug(std::cout, 0);
    }

    void testResultCacheDouble() {
        Function f = t.squaredNorm();
        ResultCache<double> cache;
        RowVector3d parameterValues(1, 2, 3);
        MapXcd parameterMap(parameterValues.data(), 1, 3, Stride<Dynamic, Dynamic>(1, 1));
        MapXcd results1 = cache.results(f, parameterMap);
        MapXcd results2 = cache.results(f, parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results2.data());
        MapXcd results3 = cache.results(f, parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results3.data());
    }

    void testResultCacheInterval() {
        Function f = t.squaredNorm();
        ResultCache<Interval> cache;
        RowVector3I parameterBounds(Interval(1, 2), Interval(3, 4), Interval(5, 6));
        MapXcI parameterMap(parameterBounds.data(), 1, 3, Stride<Dynamic, Dynamic>(1, 1));
        MapXcI results1 = cache.results(f, parameterMap);
        MapXcI results2 = cache.results(f, parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results2.data());
        MapXcI results3 = cache.results(f, parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results3.data());
    }
    
    //void xtestRoots() {
    //    std::vector<Function> functions(7);
    //    std::vector<Interval> domains(7);
    //    std::vector<RowVectorXd> expected_function_zeros(7);
    //    std::vector<RowVectorXd> expected_derivative_zeros(7);
    //    std::vector<RowVectorXd> expected_second_derivative_zeros(7);
    //    
    //    Function x = Function::Parameter();

    //    functions[0] = x - 1;
    //    domains[0] = Interval(0, 2);
    //    expected_function_zeros[0] = RowVectorXd::Constant(1, 1.0);
    //    expected_derivative_zeros[0] = RowVectorXd();
    //    expected_second_derivative_zeros[0] = RowVectorXd();

    //    functions[1] = x.squaredNorm() - 1;
    //    domains[1] = Interval(-2, 2);
    //    expected_function_zeros[1] = RowVector2d(-1, 1);
    //    expected_derivative_zeros[1] = RowVectorXd::Constant(1, 0.0);
    //    expected_second_derivative_zeros[1] = RowVectorXd();

    //    functions[2] = x * x * x - 4 * x * x + 5 * x - 2;
    //    domains[2] = Interval(0, 3);
    //    expected_function_zeros[2] = RowVector2d(1, 2);
    //    expected_derivative_zeros[2] = RowVector2d(1, 5.0 / 3.0);
    //    expected_second_derivative_zeros[2] = RowVectorXd::Constant(1, 4.0 / 3.0);

    //    functions[3] = sin(x).squaredNorm() + 2 * sin(x) + 1;
    //    domains[3] = Interval(-M_PI, 2 * M_PI);
    //    expected_function_zeros[3] = RowVector2d(-M_PI / 2, 3 * M_PI / 2);
    //    expected_derivative_zeros[3] = RowVector3d(-M_PI / 2, M_PI / 2, 3 * M_PI / 2);
    //    expected_second_derivative_zeros[3] = RowVector4d(
    //        -M_PI / 2,
    //        M_PI / 6,
    //        5 * M_PI / 6,
    //        3 * M_PI / 2
    //    );

    //    functions[4] = sqrt(x) - 0.5;
    //    domains[4] = Interval(0, 1);
    //    expected_function_zeros[4] = RowVectorXd::Constant(1, 0.25);
    //    expected_derivative_zeros[4] = RowVectorXd();
    //    expected_second_derivative_zeros[4] = RowVectorXd();

    //    functions[5] = 1 / x - 1;
    //    domains[5] = Interval(0, 2);
    //    expected_function_zeros[5] = RowVectorXd::Constant(1, 1.0);
    //    expected_derivative_zeros[5] = RowVectorXd();
    //    expected_second_derivative_zeros[5] = RowVectorXd();

    //    functions[6] = sqrt(x) - x;
    //    domains[6] = Interval(0, 2);
    //    expected_function_zeros[6] = RowVector2d(0, 1);
    //    expected_derivative_zeros[6] = RowVectorXd::Constant(1, 0.25);
    //    expected_second_derivative_zeros[6] = RowVectorXd();

    //    for (int i = 0; i < 5; ++i) {
    //        Function function = functions[i];
    //        Function derivative = function.derivative();
    //        Function second_derivative = derivative.derivative();
    //        
    //        RowVectorXd function_values = function(expected_function_zeros[i]);
    //        RowVectorXd derivative_values = derivative(expected_derivative_zeros[i]);
    //        RowVectorXd second_derivative_values =
    //            second_derivative(expected_second_derivative_zeros[i]);
    //            
    //        TS_ASSERT(function_values.isZero());
    //        TS_ASSERT(derivative_values.isZero());
    //        TS_ASSERT(second_derivative_values.isZero());
    //        
    //        RowVectorXd function_zeros;
    //        boost::timer timer;
    //        for (int j = 0; j < 100; ++j) {function_zeros = function.roots(domains[i]);}
    //        double elapsed = timer.elapsed();
    //        RowVectorXd derivative_zeros = derivative.roots(domains[i]);
    //        RowVectorXd second_derivative_zeros = second_derivative.roots(domains[i]);
    //            
    //        TS_ASSERT(function_zeros.isApprox(expected_function_zeros[i]));
    //        TS_ASSERT(derivative_zeros.isApprox(expected_derivative_zeros[i]));
    //        TS_ASSERT(second_derivative_zeros.isApprox(expected_second_derivative_zeros[i]));
    //        
    //        std::cout << "i = " << i << std::endl;
    //        std::cout << "  elapsed = " << elapsed << std::endl;
    //        
    //        std::cout << "  function_zeros = " << function_zeros << std::endl;
    //        std::cout << "  function_errors = ";
    //        std::cout << function_zeros - expected_function_zeros[i] << std::endl;
    //        
    //        std::cout << "  derivative_zeros = " << derivative_zeros << std::endl;
    //        std::cout << "  derivative_errors = ";
    //        std::cout << derivative_zeros - expected_derivative_zeros[i] << std::endl;
    //        
    //        std::cout << "  second_derivative_zeros = " << second_derivative_zeros << std::endl;
    //        std::cout << "  second_derivative_errors = ";
    //        std::cout << second_derivative_zeros - expected_second_derivative_zeros[i] << std::endl;
    //    }
    //}
    
    //void xtestCircleDerivativeZeros() {
    //    Function x = Function::Parameter();
    //    double R = 1;
    //    double r = 0.5;
    //    double slope = 0.5;
    //    Function radius_function = R - r + sqrt(x * (2 * r - x));
    //    Function derivative_difference = radius_function.derivative() - 1 / slope;
    //    RowVectorXd parameter_values = RowVectorXd::LinSpaced(20, Interval(0, r));
    //    std::cout << derivative_difference(parameter_values) << std::endl;
    //    RowVectorXd root = derivative_difference.roots(Interval(0, r));
    //    std::cout << root << std::endl;
    //    TS_ASSERT_EQUALS(root.size(), 1);
    //    TS_ASSERT(root.value() - 0.052786404500042038 == Zero());
    //}
};
