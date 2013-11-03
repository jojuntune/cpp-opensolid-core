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

#include <OpenSolid/util/Zero.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Simplex.hpp>
#include <OpenSolid/Python/PythonEnvironment.hpp>

#include <cxxtest/TestSuite.h>

#include <iostream>

using namespace opensolid;
using namespace boost::python;

MatrixXd twice(const MatrixXd& argument) {
    return 2 * argument;
}

class CustomClass
{
private:
    double _value;
    Function _function;
    Vector3d _vector;
public:
    CustomClass() :
        _value(3),
        _function(Function::Parameter() * Vector3d(1, 1, 1)),
        _vector(1, 2, 3) {
    }
        
    void setValue(double value) {
        value = value;
    }

    double value() const {
        return _value;
    }
    
    void setFunction(const Function& function) {
        _function = function;
    }

    Function function() const {
        return _function;
    }
    
    void setVector(const MatrixXd& vector) {
        _vector = vector;
    }

    MatrixXd vector() const {
        return _vector;
    }
};

struct UnregisteredType
{
};

class PythonTests : public CxxTest::TestSuite
{
public:
    void testRun() {
        PythonEnvironment environment;
        environment.run("result = 1 + 2");
        TS_ASSERT_EQUALS(environment.get<double>("result"), 3.0);
    }

    void testEvaluation() {
        PythonEnvironment environment;
        TS_ASSERT_EQUALS(environment.get<double>("1 + 2"), 3.0);
    }
    
    void testExecutionError() {
        PythonEnvironment environment;
        std::string text =
            "string = 'cat'       \n"
            "result = 1 + string  \n"
        ;
        TS_ASSERT_THROWS(environment.run(text), PythonTypeError);
        try {
            environment.run(text);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(std::string(error.what()), "PythonTypeError");
            std::cout << environment.formattedTraceback() << std::endl;
            std::vector<PythonStackFrame> stack_trace = environment.stackTrace();
            TS_ASSERT_EQUALS(stack_trace.size(), 1u);
            TS_ASSERT_EQUALS(stack_trace.front().lineNumber(), 2);
        }
    }
    
    void testSyntaxError() {
        PythonEnvironment environment;
        std::string text = "2*/1";
        TS_ASSERT_THROWS(environment.run(text), PythonSyntaxError);
        try {
            environment.run(text);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(std::string(error.what()), "PythonSyntaxError");
            std::cout << environment.formattedTraceback() << std::endl;
        }
    }
    
    void testEvaluationError() {
        PythonEnvironment environment;
        environment.set("a", Interval(1));
        environment.set("b", MatrixXd(Vector3d(2, 3, 4)));
        TS_ASSERT_THROWS(environment.get<Vector3d>("a.cross(b)"), PythonAttributeError);
        try {
            environment.get<Vector3d>("a.cross(b)");
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(std::string(error.what()), "PythonAttributeError");
            std::cout << environment.formattedTraceback() << std::endl;

        }
    }

    void testUnregisteredType() {
        PythonEnvironment environment;
        TS_ASSERT_THROWS(environment.set("a", UnregisteredType()), ConversionToPythonError);
    }
    
    void testParameter() {
        PythonEnvironment environment;
        environment.set("a", 3.0);
        environment.set("b", 2.0);
        TS_ASSERT_EQUALS(environment.get<double>("a + b"), 5.0);
    }
    
    void testString() {
        PythonEnvironment environment;
        environment.set("a", std::string("hello"));
        environment.set("b", std::string("world"));
        std::string result = environment.get<std::string>("' '.join((a, b))");
        TS_ASSERT_EQUALS(result, "hello world");
    }
    
    void testInterval() {
        PythonEnvironment environment;
        environment.set("a", Interval(1,2));
        Interval result = environment.get<Interval>("a + Interval(3,4)");
        TS_ASSERT_EQUALS(result.lowerBound(), 4.0);
        TS_ASSERT_EQUALS(result.upperBound(), 6.0);
    }
    
    void testMixedScalarOperations() {
        PythonEnvironment environment;
        Interval result = environment.get<Interval>("2 * Interval(3, 4)");
        TS_ASSERT_EQUALS(result.lowerBound(), 6.0);
        TS_ASSERT_EQUALS(result.upperBound(), 8.0);
    }
    
    void xtestMatrixXd() {
        PythonEnvironment environment;
        environment.set("v", MatrixXd(Vector3d(1, 2, 3)));
        environment.set("a", 4.0);
        environment.set("b", 5.0);
        std::string expression("v + a * Vector3d(1, 0, 0) + b * Vector3d(0, 1, 0)");
        Vector3d result = environment.get<Vector3d>(expression);
        TS_ASSERT((result - Vector3d(5, 7, 3)).isZero());
    }
    
    void testMatrixXI() {
        PythonEnvironment environment;
        Vector3I vector(Interval(1.0, 2.0), Interval(2.0, 3.0), Interval(3.0, 4.0));
        environment.set("v", MatrixXI(vector));
        environment.set("a", Interval(4.0, 5.0));
        environment.set("b", Interval(5.0, 6.0));
        std::string expression("v + a * Vector3d(1, 0, 0) + b * Vector3d(0, 1, 0)");
        Vector3I result = environment.get<VectorXI>(expression);
        TS_ASSERT_EQUALS(result.x().lowerBound(), 5.0);
        TS_ASSERT_EQUALS(result.x().upperBound(), 7.0);
        TS_ASSERT_EQUALS(result.y().lowerBound(), 7.0);
        TS_ASSERT_EQUALS(result.y().upperBound(), 9.0);
        TS_ASSERT_EQUALS(result.z().lowerBound(), 3.0);
        TS_ASSERT_EQUALS(result.z().upperBound(), 4.0);
    }

    void testColwise() {
        PythonEnvironment environment;
        environment.run("matrix = MatrixXd([[1, 2], [3, 4], [5, 6]])");
        RowVectorXd squared_norms = environment.get<MatrixXd>("matrix.colwise().squaredNorm()");
        TS_ASSERT_EQUALS(squared_norms, RowVector3d(5, 25, 61));
    }

    void testMatrixTransformation() {
        PythonEnvironment environment;
        environment.run("from math import pi");
        environment.run("point = Vector3d(3, 2, 1)");
        Vector3d transformed;
        transformed = environment.get<Vector3d>("point.rotated(pi / 2, Frame3d().zAxis())");
        TS_ASSERT((transformed - Vector3d(-2, 3, 1)).isZero());
        transformed = environment.get<Vector3d>("point.rotated(pi / 2, Frame3d().xAxis())");
        TS_ASSERT((transformed - Vector3d(3, -1, 2)).isZero());
        transformed = environment.get<Vector3d>("point.translated(Vector3d.Ones())");
        TS_ASSERT((transformed - Vector3d(4, 3, 2)).isZero());
        transformed = environment.get<Vector3d>("point.mirrored(Frame3d().yzPlane())");
        TS_ASSERT((transformed - Vector3d(-3, 2, 1)).isZero());
        transformed = environment.get<Vector3d>("(2 * point).mirrored(Frame3d().xyPlane())");
        TS_ASSERT((transformed - Vector3d(6, 4, -2)).isZero());

        environment.run("a = MatrixXd([[1, 0, 0], [1, 1, 0]])");
        environment.set("theta", M_PI / 4);
        environment.run("m = Matrix3d([[cos(theta), sin(theta), 0], [-sin(theta), cos(theta), 0], [0, 0, 1]])");
        environment.run("v = Vector3d(1, 2, 3)");
        MatrixXd transformed_matrix = environment.get<MatrixXd>("a.transformed(m, v)");
        Vector3d first_expected(1 + 1 / sqrt(2.0), 2 + 1 / sqrt(2.0), 3);
        Vector3d second_expected(1, 2 + sqrt(2.0), 3);
        TS_ASSERT((transformed_matrix.col(0) - first_expected).isZero());
        TS_ASSERT((transformed_matrix.col(1) - second_expected).isZero());
    }
    
    void testInternalConversionError() {
        PythonEnvironment environment;
        std::string text =
            "a = Interval(1)                   \n"
            "result = Vector3d.UnitX().dot(a)  \n"
        ;
        TS_ASSERT_THROWS(environment.run(text), PythonTypeError);
        try {
            environment.run(text);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(std::string(error.what()), "PythonTypeError");
            std::cout << environment.formattedTraceback() << std::endl;
        }
    }
    
    void testMultipleLineNumbers() {
        PythonEnvironment environment;
        std::string text =
            "def foo(a, b):       \n"
            "   return a.dot(b)   \n"
            "                     \n"
            "a = Interval(1)      \n"
            "b = Interval(2)      \n"
            "c = foo(a, b)        \n"
            "d = 3                \n"
        ;
        TS_ASSERT_THROWS(environment.run(text), PythonAttributeError);
        try {
            environment.run(text);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(std::string(error.what()), "PythonAttributeError");
            std::vector<PythonStackFrame> stack_trace = environment.stackTrace();
            TS_ASSERT_EQUALS(stack_trace[0].lineNumber(), 6);
            TS_ASSERT_EQUALS(stack_trace[1].lineNumber(), 2);
            TS_ASSERT_EQUALS(stack_trace[1].functionName(), "foo");
            std::cout << environment.formattedTraceback() << std::endl;
        }
    }
    
    void testMultilineEvaluate() {
        PythonEnvironment environment;
        std::string text =
            "a = Vector3d(1, 2, 3)  \n"
            "b = Vector3d(4, 5, 6)  \n"
            "a.dot(b)               \n"
        ;
        TS_ASSERT_EQUALS(environment.get<double>(text), 32.0);
    }
    
    void testIntervalConversion() {
        PythonEnvironment environment;
        Interval result = environment.get<Interval>("2 + 2");
        TS_ASSERT_EQUALS(result.lowerBound(), 4.0);
        TS_ASSERT_EQUALS(result.upperBound(), 4.0);
    }
    
    void testErrorTranslation() {
        PythonEnvironment environment;
        std::string text =
            "a = Vector2d(1, 2)    \n"
            "b = Vector3d(1, 2, 3) \n"
            "c = a + b             \n"
        ;
        TS_ASSERT_THROWS(environment.run(text), MatrixXdSumMatrixXdError);
        try {
            environment.run(text);
        } catch (const MatrixXdSumMatrixXdError& error) {
            TS_ASSERT_EQUALS(std::string(error.what()), "MatrixXdSumMatrixXdError");
            TS_ASSERT_EQUALS(error.firstMatrix().rows(), 2);
            TS_ASSERT_EQUALS(error.secondMatrix().rows(), 3);
            TS_ASSERT_EQUALS(error.firstMatrix(), Vector2d(1, 2));
            TS_ASSERT_EQUALS(error.secondMatrix(), Vector3d(1, 2, 3));
            std::cout << environment.formattedTraceback() << std::endl;
        }
    }
    
    void testLinSpaced() {
        PythonEnvironment environment;
        RowVector3d result = environment.get<RowVector3d>(
            "RowVector3d.LinSpaced(Interval::Unit())"
        );
        TS_ASSERT_EQUALS(result, RowVector3d::LinSpaced(Interval::Unit()));
        TS_ASSERT_EQUALS(result, RowVector3d(0, 0.5, 1));
    }
    
    void testMatrixOperators() {
        PythonEnvironment environment;
        environment.set<MatrixXd>("a", Vector3d(1, 2, 3));
        environment.set<MatrixXd>("b", Vector3d(1, 2, 3));
        TS_ASSERT(environment.get<bool>("(a - b).isZero()"));
        TS_ASSERT_EQUALS(environment.get<Vector3d>("-a"), Vector3d(-1, -2, -3));
        TS_ASSERT_EQUALS(environment.get<Vector3d>("a + b"), Vector3d(2, 4, 6));
        TS_ASSERT_EQUALS(environment.get<Vector3d>("a - b"), Vector3d(0, 0, 0));
        TS_ASSERT_EQUALS(environment.get<Vector3d>("a * 2"), Vector3d(2, 4, 6));
        TS_ASSERT_EQUALS(environment.get<Vector3d>("3 * a"), Vector3d(3, 6, 9));
        TS_ASSERT_EQUALS(environment.get<Vector3d>("a / 2"), Vector3d(0.5, 1, 1.5));
    }
    
    void testExtraction() {
        PythonEnvironment environment;
        std::string expression = "Vector2d(1, 2) + Vector2I(Interval(1, 2), Interval(2, 3))";
        TS_ASSERT_THROWS(environment.get<Vector2d>(expression), ConversionFromPythonError);
        try {
            environment.get<Vector2d>(expression);
        } catch (const ConversionFromPythonError& error) {
            std::cout << environment.formattedTraceback() << std::endl;
            TS_ASSERT_EQUALS(std::string(error.what()), "ConversionFromPythonError");
            TS_ASSERT(extract<MatrixXI>(error.pythonObject()).check());
        }
    }
    
    void testFunction() {
        PythonEnvironment environment;
        environment.run("u = Function.Parameter(2, 0)");
        environment.run("v = Function.Parameter(2 ,1)");
        environment.run("f = u.squaredNorm() * 1.0 + v.squaredNorm() * 1.0");
        double result = environment.get<double>("f(Vector2d(1, 2))[0]");
        TS_ASSERT_EQUALS(result, 5.0);
        result = environment.get<double>("f.derivative(0)(Vector2d(3, 4)).value()");
        TS_ASSERT_EQUALS(result, 6.0);
        result = environment.get<double>("f.derivative(1).derivative(1)(Vector2d(5, 6)).value()");
        TS_ASSERT_EQUALS(result, 2.0);
        std::string expression =
            "f.derivative(0)(Vector2I(Interval(1, 2), Interval(3, 4))).value()";
        TS_ASSERT_EQUALS(environment.get<Interval>(expression).lowerBound(), 2);
        TS_ASSERT_EQUALS(environment.get<Interval>(expression).upperBound(), 4);
    }
    
    void testIntervalBisected() {
        PythonEnvironment environment;
        environment.run("x = Interval(4, 5)");
        environment.run("a, b = x.bisected()");
        Interval a = environment.get<Interval>("a");
        Interval b = environment.get<Interval>("b");
        TS_ASSERT_EQUALS(a.lowerBound(), 4);
        TS_ASSERT_EQUALS(a.upperBound(), 4.5);
        TS_ASSERT_EQUALS(b.lowerBound(), 4.5);
        TS_ASSERT_EQUALS(b.upperBound(), 5);
    }

    void testIntervalContainment() {
        PythonEnvironment environment;
        TS_ASSERT(environment.get<bool>("4 in Interval(3, 5)"));
        TS_ASSERT(environment.get<bool>("Interval(3, 4) in Interval(2, 5)"));
        TS_ASSERT(!environment.get<bool>("Interval(2, 4) in Interval(3, 5)"));
    }
    
    void testMatrixOverlap() {
        PythonEnvironment environment;
        environment.run("u = Vector3d(1, 2, 3)");
        environment.run("v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4))");
        TS_ASSERT(environment.get<bool>("v.contains(u)"));
        TS_ASSERT(!environment.get<bool>("v.contains(3 * u)"));
        TS_ASSERT(environment.get<bool>("u in v"));
    }
    
    void testMatrixHull() {
        PythonEnvironment environment;
        environment.run("u = Vector3d(1, 2, 3)");
        environment.run("v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4))");
        environment.run("result = (3 * u).hull(v)");
        TS_ASSERT_EQUALS(environment.get<Vector3d>("result.cwiseLower()"), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(environment.get<Vector3d>("result.cwiseUpper()"), Vector3d(3, 6, 9));
        environment.run("result = v.hull(3 * u)");
        TS_ASSERT_EQUALS(environment.get<Vector3d>("result.cwiseLower()"), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(environment.get<Vector3d>("result.cwiseUpper()"), Vector3d(3, 6, 9));
    }
    
    void testMatrixIntersection() {
        PythonEnvironment environment;
        environment.run("v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4))");
        environment.run("x = (v + Vector3d.Constant(0.5)).intersection(v)");
        environment.run("y = Vector3I(Interval(1.5, 2), Interval(2.5, 3), Interval(3.5, 4))");
        TS_ASSERT_EQUALS(
            environment.get<Vector3d>("x.cwiseLower()"),
            environment.get<Vector3d>("y.cwiseLower()")
        );
        TS_ASSERT_EQUALS(
            environment.get<Vector3d>("x.cwiseUpper()"),
            environment.get<Vector3d>("y.cwiseUpper()")
        );
    }

    void testCustomVariable() {
        PythonEnvironment environment1;
        PythonEnvironment environment2;
        environment1.environment().attr("a") = 3;
        TS_ASSERT_EQUALS(environment1.get<double>("a"), 3);
        TS_ASSERT_THROWS(environment2.get<double>("a"), PythonNameError);
    }

    void testVariableThroughScope() {
        PythonEnvironment environment1;
        PythonEnvironment environment2;
        scope s = environment1.environment();
        s.attr("a") = 3;
        TS_ASSERT_EQUALS(environment1.get<double>("a"), 3);
        TS_ASSERT_THROWS(environment2.get<double>("a"), PythonNameError);
    }
    
    void testCustomFunction() {
        PythonEnvironment environment1;
        PythonEnvironment environment2;

        scope s = environment1.environment();
        def("twice", twice);

        TS_ASSERT_EQUALS(environment1.get<Vector3d>("twice(Vector3d(1, 2, 3))"), Vector3d(2, 4, 6));
        TS_ASSERT_THROWS(environment2.run("twice(Vector3d(1, 2, 3))"), PythonNameError);
    }
    
    void testCustomClass() {
        PythonEnvironment environment1;
        PythonEnvironment environment2;

        scope s = environment1.environment();
        class_<CustomClass>("CustomClass")
            .def(init<>())
            .def("setValue", &CustomClass::setValue)
            .def("value", &CustomClass::value)
            .def("setFunction", &CustomClass::setFunction)
            .def("function", &CustomClass::function)
            .def("setVector", &CustomClass::setVector)
            .def("vector", &CustomClass::vector);

        environment1.run("a = CustomClass()");
        environment1.run("a.setValue(10)");
        TS_ASSERT_EQUALS(environment1.get<double>("a.value()"), 10.0);
        TS_ASSERT((environment1.get<Vector3d>("a.function()(3.0)") - Vector3d(3, 3, 3)).isZero());
        TS_ASSERT_EQUALS(environment1.get<Vector3d>("a.vector()"), Vector3d(1, 2, 3));
        TS_ASSERT_THROWS(environment2.run("b = CustomClass()"), PythonNameError);
    }
    
    void testTranspose() {
        PythonEnvironment environment;
        RowVector3d a = environment.get<RowVector3d>("Vector3d(1, 2, 3).transpose()");
        RowVector3d b = environment.get<RowVector3d>("RowVector3d(1, 2, 3)");
        TS_ASSERT_EQUALS(a, b);
    }
    
    void testMatrixIndexing() {
        PythonEnvironment environment;
        environment.run("a = Matrix3d([[1, 2, 3], [4, 5, 6], [7, 8, 9]]).transpose()");
        environment.run("b = Vector3d(10, 11, 12)");
        TS_ASSERT_EQUALS(environment.get<double>("b[-1]"), 12.0);
        TS_ASSERT_EQUALS(environment.get<Vector3d>("b[:]"), Vector3d(10, 11, 12));
        TS_ASSERT_EQUALS(environment.get<Vector2d>("b[-2:]"), Vector2d(11, 12));
        TS_ASSERT_EQUALS(environment.get<double>("a[1, 1]"), 5.0);
        TS_ASSERT_EQUALS(environment.get<double>("a[-2, -1]"), 6.0);
        TS_ASSERT_EQUALS(environment.get<Vector3d>("a[:, 0]"), Vector3d(1, 4, 7));
        TS_ASSERT_EQUALS(environment.get<RowVector3d>("a[2, :]"), RowVector3d(7, 8, 9));
        MatrixXd test(2, 3);
        test << RowVector3d(4, 5, 6), RowVector3d(7, 8, 9);
        TS_ASSERT_EQUALS(environment.get<MatrixXd>("a[1:2, :]"), test);
        environment.run("a[1,1:] = b[1:].transpose()");
        test.resize(3, 3);
        test << RowVector3d(1, 2, 3), RowVector3d(4, 11, 12), RowVector3d(7, 8, 9);
        TS_ASSERT_EQUALS(environment.get<Matrix3d>("a"), test);
    }
    
    void testMatrixEquality() {
        PythonEnvironment environment;
        environment.run("a1 = Vector2d(1, 2)");
        environment.run("a2 = Vector2d([1, 2])");
        environment.run("b1 = Vector2I(Interval(1), Interval(2))");
        environment.run("b2 = Vector2I([Interval(1), Interval(2)])");
        TS_ASSERT(environment.get<bool>("(a1 - a2).isZero()"));
        TS_ASSERT(environment.get<bool>("not (a1 - 2 * a2).isZero()"));
        TS_ASSERT(environment.get<bool>("(b1 - b2).isZero()"));
        TS_ASSERT(environment.get<bool>("not (b1 - 2 * b2).isZero()"));
        TS_ASSERT(environment.get<bool>("(a1 - b1).isZero()"));
        TS_ASSERT(environment.get<bool>("not (a1 - 2 * b1).isZero()"));
        TS_ASSERT(environment.get<bool>("(b1 - a1).isZero()"));
        TS_ASSERT(environment.get<bool>("not (b1 - 2 * a1).isZero()"));
    }

    void testOverloading() {
        PythonEnvironment environment;
        environment.set("f1", 3 * Function::Parameter());
        Function f2 = Vector3d(2, 0, 0) * Function::Parameter(2, 0) +
            Vector3d(0, 0.5, 0) * Function::Parameter(2, 1);
        environment.set("f2", f2);
        TS_ASSERT(environment.get<double>("f1(2).value()") - 6 == Zero());
        Interval interval_bounds = environment.get<Interval>("f1(Interval(2, 3)).value()");
        TS_ASSERT(interval_bounds.lowerBound() - 6 == Zero());
        TS_ASSERT(interval_bounds.upperBound() - 9 == Zero());
        Vector3d vector = environment.get<Vector3d>("f2(Vector2d.Ones())");
        TS_ASSERT((vector - Vector3d(2, 0.5, 0)).isZero());
        Vector3I vector_bounds = environment.get<Vector3I>(
            "f2(Vector2I(Interval(1, 2), Interval(2, 3)))"
        );
        TS_ASSERT((vector_bounds.cwiseLower() - Vector3d(2, 1, 0)).isZero());
        TS_ASSERT((vector_bounds.cwiseUpper() - Vector3d(4, 1.5, 0)).isZero());
    }

    void testExplicitModule() {
        PythonEnvironment environment;
        TS_ASSERT_EQUALS(
            environment.get<std::string>("str(opensolid)"),
            "<module 'opensolid' (built-in)>"
        );
        environment.run("f = opensolid.Function.Parameter() * opensolid.Vector3d(1, 2, 3)");
        MatrixXI bounds = environment.get<MatrixXI>(
            "f(opensolid.Vector2I(opensolid.Interval(1, 2), 0))"
        );
        TS_ASSERT((bounds.cwiseLower() - Vector3d(1, 2, 3)).isZero());
        TS_ASSERT((bounds.cwiseUpper() - Vector3d(2, 4, 6)).isZero());
    }

    void testFunctionExtraction() {
        PythonEnvironment environment;
        Function f = environment.get<Function>("sin(Function.Parameter()) + 1");
        TS_ASSERT(f(0).value() - 1 == Zero());
        TS_ASSERT(f(M_PI / 2).value() - 2 == Zero());
        f = environment.get<Function>("Function.Parameter(2, 0) + 3 * Function.Parameter(2, 1)");
        TS_ASSERT(f.numParameters() == 2);
        TS_ASSERT(f.numDimensions() == 1);
        TS_ASSERT(f(Vector2d(1, 2)).value() - 7 == Zero());
    }

    void testComparisons() {
        PythonEnvironment environment;
        environment.run("a1 = Vector3d(1, 2, 3)");
        environment.run("a2 = Vector3d([1, 2, 3])");
        environment.run("b1 = Vector3I(Interval(1), 2, 3)");
        environment.run("b2 = Vector3I([1, Interval(2), 3])");

        TS_ASSERT(environment.get<bool>("a1 == a2"));
        TS_ASSERT(environment.get<bool>("(a1 - a2).isZero()"));
        TS_ASSERT(environment.get<bool>("a1 != 2 * a2"));
        TS_ASSERT(environment.get<bool>("not (a1 - 2 * a2).isZero()"));

        TS_ASSERT(environment.get<bool>("b1 == b2"));
        TS_ASSERT(environment.get<bool>("(b1 - b2).isZero()"));
        TS_ASSERT(environment.get<bool>("b1 != 2 * b2"));
        TS_ASSERT(environment.get<bool>("not (b1 - 2 * b2).isZero()"));

        TS_ASSERT(environment.get<bool>("a1 == b1"));
        TS_ASSERT(environment.get<bool>("(a1 - b1).isZero()"));
        TS_ASSERT(environment.get<bool>("a1 != 2 * b1"));
        TS_ASSERT(environment.get<bool>("not (a1 - 2 * b1).isZero()"));
    }

    void testPickling() {
        PythonEnvironment environment;
        double a = 3;
        Interval b(4, 5);
        Matrix2d c;
        c(0, 0) = 6;
        c(0, 1) = 7;
        c(1, 0) = 8;
        c(1, 1) = 9;
        Vector2I d(Interval(10, 11), Interval(12, 13));
        Frame3d e = Frame3d().rotated(M_PI / 4, Frame3d().zAxis()).translated(Vector3d(0, 1, 0));
        Triangle3d f(Vector3d(1, 1, 1), Vector3d(2, 1, 1), Vector3d(1, 2, 1));
        environment.run("import pickle");
        environment.set("a", a);
        environment.set("b", b);
        environment.set("c", c);
        environment.set("d", d);
        environment.set<DatumXd>("e", e);
        environment.set<SimplexXd>("f", f);
        environment.run("a_pickled = pickle.dumps(a)");
        environment.run("b_pickled = pickle.dumps(b)");
        environment.run("c_pickled = pickle.dumps(c)");
        environment.run("d_pickled = pickle.dumps(d)");
        environment.run("e_pickled = pickle.dumps(e)");
        environment.run("f_pickled = pickle.dumps(f)");
        environment.run("a_unpickled = pickle.loads(a_pickled)");
        environment.run("b_unpickled = pickle.loads(b_pickled)");
        environment.run("c_unpickled = pickle.loads(c_pickled)");
        environment.run("d_unpickled = pickle.loads(d_pickled)");
        environment.run("e_unpickled = pickle.loads(e_pickled)");
        environment.run("f_unpickled = pickle.loads(f_pickled)");
        double a_extracted = environment.get<double>("a_unpickled");
        Interval b_extracted = environment.get<Interval>("b_unpickled");
        Matrix2d c_extracted = environment.get<Matrix2d>("c_unpickled");
        Vector2I d_extracted = environment.get<Vector2I>("d_unpickled");
        Frame3d e_extracted = environment.get<DatumXd>("e_unpickled");
        Triangle3d f_extracted = environment.get<SimplexXd>("f_unpickled");
        TS_ASSERT_EQUALS(a, a_extracted);
        TS_ASSERT_EQUALS(b.lowerBound(), b_extracted.lowerBound());
        TS_ASSERT_EQUALS(b.upperBound(), b_extracted.upperBound());
        TS_ASSERT_EQUALS(c, c_extracted);
        TS_ASSERT_EQUALS(d.cwiseLower(), d_extracted.cwiseLower());
        TS_ASSERT_EQUALS(d.cwiseUpper(), d_extracted.cwiseUpper());
        TS_ASSERT_EQUALS(e.origin(), e_extracted.origin());
        TS_ASSERT((e.basis() - e_extracted.basis()).isZero());
        TS_ASSERT_EQUALS(f, f_extracted);
    }

    void testOverloadOrder() {
        PythonEnvironment environment;
        TS_ASSERT(environment.get<double>("sqrt(4)") - 2 == Zero());
    }

    //void xtestFunctionRoots() {
    //    PythonEnvironment environment;
    //    std::string text =
    //        "x = Function.Parameter() \n"
    //        "f = x * x * x - 4 * x * x + 5 * x - 2\n"
    //        "roots = f.roots(Interval(0, 3))\n"
    //        "derivative_roots = f.derivative().roots(Interval(0, 3))\n"
    //        "second_derivative_roots = f.derivative().derivative().roots(Interval(0, 3))\n"
    //    ;
    //    environment.run(text);
    //    RowVectorXd roots = environment.get<RowVectorXd>("roots");
    //    TS_ASSERT((roots - RowVector2d(1, 2)).isZero());
    //    roots = environment.get<RowVectorXd>("derivative_roots");
    //    TS_ASSERT((roots - RowVector2d(1, 5.0 / 3.0)).isZero());
    //    roots = environment.get<RowVectorXd>("second_derivative_roots");
    //    TS_ASSERT(roots.value() - 4.0 / 3.0 == Zero());
    //}

    void testDatum() {
        PythonEnvironment environment;
        environment.run("import math");
        environment.run("frame = Frame3d(Vector3d(1, 1, 1), Vector3d(1, 1, 0), Vector3d(-1, 1, 0))");
        environment.run("product = Vector3d.Ones() * frame");
        TS_ASSERT(environment.get<bool>("(product - Vector3d(1, 1 + sqrt(2), 2)).isZero()"));
        environment.run("product = Vector3d.Ones() * frame.orientation()");
        TS_ASSERT(environment.get<bool>("(product - Vector3d(0, sqrt(2), 1)).isZero()"));
        environment.run("quotient = Vector3d.UnitX() / frame");
        TS_ASSERT(
            environment.get<bool>("(quotient - Vector3d(-1 / sqrt(2), -1 / sqrt(2), -1)).isZero()")
        );
        environment.run("linear_quotient = Vector3d.UnitX() / frame.orientation()");
        std::string expression("(linear_quotient - Vector3d(1 / sqrt(2), -1 / sqrt(2), 0)).isZero()");
        TS_ASSERT(environment.get<bool>(expression));
        environment.run("global_frame = Frame3d()");
        environment.run("frame = global_frame.translated(Vector3d.Ones())");
        environment.run("frame = frame.rotated(-math.pi / 2, global_frame.xAxis())");
        expression = "(Vector3d(1, 2, 3) * frame - Vector3d(2, 4, -3)).isZero()";
        TS_ASSERT(environment.get<bool>(expression));
    }

    void testSimplex() {
        PythonEnvironment environment;
        environment.run("import math");
        environment.run(
            "triangle = Triangle3d(Vector3d(1, 1, 1), Vector3d(2, 1, 1), Vector3d(1, 2, 1))"
        );
        TS_ASSERT(environment.get<double>("triangle.area()") - 0.5 == Zero());
        TS_ASSERT((environment.get<Vector3d>("triangle.normal()") - Vector3d::UnitZ()).isZero());
        TS_ASSERT(
            (environment.get<Vector3d>("triangle.edge(1).vector()") - Vector3d(-1, 1, 0)).isZero()
        );
        TS_ASSERT(  
            environment.get<bool>(
                "(triangle.mirrored(Frame3d().yzPlane()).vertex(0) - Vector3d(-1, 1, 1)).isZero()"
            )
        );
        SimplexXd projected = environment.get<SimplexXd>("triangle % Frame3d().xyPlane()");
        TS_ASSERT((projected.vertex(0) - Vector3d(1, 1, 0)).isZero());
    }

    void testMatrixCopying() {
        PythonEnvironment environment;
        environment.run("a1 = Matrix2d([[1, 2], [3, 4]])");
        environment.run("a2 = MatrixXd([[1, 2], [3, 4]])");
        environment.run("b1 = Matrix2d(a2)");
        environment.run("b2 = MatrixXd(a1)");
        environment.run("b1[1, 1] = 5");
        environment.run("b2[1, 1] = 5");
        TS_ASSERT_EQUALS(environment.get<MatrixXd>("a1")(1, 1), 4.0);
        TS_ASSERT_EQUALS(environment.get<Matrix2d>("a2")(1, 1), 4.0);
        TS_ASSERT_EQUALS(environment.get<MatrixXd>("b1")(1, 1), 5.0);
        TS_ASSERT_EQUALS(environment.get<Matrix2d>("b2")(1, 1), 5.0);
    }
};
