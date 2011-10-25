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

#include <iostream>

#include <cxxtest/TestSuite.h>

#include <OpenSolid/Scalar/Comparison.hpp>
#include <OpenSolid/Common/Error.hpp>
#include <OpenSolid/Function/Function.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Script/Script.hpp>

using namespace OpenSolid;
using namespace boost::python;

MatrixXd twice(const MatrixXd& argument) {return 2 * argument;}

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
        _vector(1, 2, 3) {}
        
    void setValue(double value) {_value = value;}

    double value() const {return _value;}
    
    void setFunction(const Function& function) {_function = function;}

    Function function() const {return _function;}
    
    void setVector(const MatrixXd& vector) {_vector = vector;}

    MatrixXd vector() const {return _vector;}
};

class ScriptTests : public CxxTest::TestSuite
{
public:
    void testRun() {
        Script script;
        script.run("result = 1 + 2");
        TS_ASSERT_EQUALS(script.get<double>("result"), 3.0);
    }

    void testEvaluation() {
        Script script;
        TS_ASSERT_EQUALS(script.get<double>("1 + 2"), 3.0);
    }
    
    void testExecutionError() {
        Script script;
        std::string text =
            "string = 'cat'       \n"
            "result = 1 + string  \n"
        ;
        TS_ASSERT_THROWS(script.run(text), Error);
        try {
            script.run(text);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(error.expected(), "NoPythonExceptions");
        }
    }
    
    void testSyntaxError() {
        Script script;
        std::string text = "2*/1";
        TS_ASSERT_THROWS(script.run(text), Error);
        try {
            script.run(text);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(error.expected(), "ValidPythonSyntax");
        }
    }
    
    void testEvaluationError() {
        Script script;
        script.set("a", Interval(1));
        script.set("b", MatrixXd(Vector3d(2, 3, 4)));
        TS_ASSERT_THROWS(script.get<MatrixXd>("a.cross(b)"), Error);
        try {
            script.get<MatrixXd>("a.cross(b)");
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(error.expected(), "NoPythonExceptions");
        }
    }
    
    void testParameter() {
        Script script;
        script.set("a", 3.0);
        script.set("b", 2.0);
        TS_ASSERT_EQUALS(script.get<double>("a + b"), 5.0);
    }
    
    void testString() {
        Script script;
        script.set("a", std::string("hello"));
        script.set("b", std::string("world"));
        TS_ASSERT_EQUALS(script.get<std::string>("' '.join((a, b))"), std::string("hello world"));
    }
    
    void testInterval() {
        Script script;
        script.set("a", Interval(1,2));
        Interval result = script.get<Interval>("a + Interval(3,4)");
        TS_ASSERT_EQUALS(result.lower(), 4.0);
        TS_ASSERT_EQUALS(result.upper(), 6.0);
    }
    
    void testMixedScalarOperations() {
        Script script;
        Interval result = script.get<Interval>("2 * Interval(3, 4)");
        TS_ASSERT_EQUALS(result.lower(), 6.0);
        TS_ASSERT_EQUALS(result.upper(), 8.0);
    }
    
    void testMatrixXd() {
        Script script;
        script.set("v", MatrixXd(Vector3d(1, 2, 3)));
        script.set("a", 4.0);
        script.set("b", 5.0);
        Vector3d result = script.get<MatrixXd>("v + a * Vector([1, 0, 0]) + b * Vector([0, 1, 0])");
        TS_ASSERT((result - Vector3d(5, 7, 3)).isZero());
    }
    
    void testMatrixXI() {
        Script script;
        Vector3I vector(Interval(1.0, 2.0), Interval(2.0, 3.0), Interval(3.0, 4.0));
        script.set("v", MatrixXI(vector));
        script.set("a", Interval(4.0, 5.0));
        script.set("b", Interval(5.0, 6.0));
        Vector3I result = script.get<MatrixXI>("v + a * Vector([1, 0, 0]) + b * Vector([0, 1, 0])");
        TS_ASSERT_EQUALS(result.x().lower(), 5.0);
        TS_ASSERT_EQUALS(result.x().upper(), 7.0);
        TS_ASSERT_EQUALS(result.y().lower(), 7.0);
        TS_ASSERT_EQUALS(result.y().upper(), 9.0);
        TS_ASSERT_EQUALS(result.z().lower(), 3.0);
        TS_ASSERT_EQUALS(result.z().upper(), 4.0);
    }

    void testColwise() {
        Script script;
        script.run("matrix = Matrix([[1, 2], [3, 4], [5, 6]])");
        RowVectorXd squared_norms = script.get<MatrixXd>("matrix.colwise().squaredNorm()");
        TS_ASSERT_EQUALS(squared_norms, RowVector3d(5, 25, 61));
    }

    void testMatrixTransformation() {
        Script script;
        script.run("from math import pi");
        script.run("point = Vector([3, 2, 1])");
        Vector3d transformed;
        transformed = script.get<MatrixXd>("point.rotated(pi / 2, Frame3d().zAxis())");
        TS_ASSERT((transformed - Vector3d(-2, 3, 1)).isZero());
        transformed = script.get<MatrixXd>("point.rotated(pi / 2, Frame3d().xAxis())");
        TS_ASSERT((transformed - Vector3d(3, -1, 2)).isZero());
        transformed = script.get<MatrixXd>("point.translated(Vector([1, 1, 1]))");
        TS_ASSERT((transformed - Vector3d(4, 3, 2)).isZero());
        transformed = script.get<MatrixXd>("point.mirrored(Frame3d().yzPlane())");
        TS_ASSERT((transformed - Vector3d(-3, 2, 1)).isZero());
        transformed = script.get<MatrixXd>("(2 * point).mirrored(Frame3d().xyPlane())");
        TS_ASSERT((transformed - Vector3d(6, 4, -2)).isZero());
    }
    
    void testInternalConversionError() {
        Script script;
        std::string text =
            "a = Interval(1)                    \n"
            "result = Vector([1, 0, 0]).dot(a)  \n"
        ;
        TS_ASSERT_THROWS(script.run(text), Error);
        try {
            script.run(text);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(error.expected(), "NoPythonExceptions");
        }
    }
    
    void testMultipleLineNumbers() {
        Script script;
        std::string text =
            "def foo(a, b):       \n"
            "   return a.dot(b)   \n"
            "                     \n"
            "a = Interval(1)      \n"
            "b = Interval(2)      \n"
            "c = foo(a, b)        \n"
            "d = 3                \n"
        ;
        TS_ASSERT_THROWS(script.run(text), Error);
        try {
            script.run(text);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(error.expected(), "NoPythonExceptions");
        }
    }
    
    void testMultilineEvaluate() {
        Script script;
        std::string text =
            "a = Vector([1, 2, 3])  \n"
            "b = Vector([4, 5, 6])  \n"
            "a.dot(b)               \n"
        ;
        TS_ASSERT_EQUALS(script.get<double>(text), 32.0);
    }
    
    void testIntervalConversion() {
        Script script;
        Interval result = script.get<Interval>("2 + 2");
        TS_ASSERT_EQUALS(result.lower(), 4.0);
        TS_ASSERT_EQUALS(result.upper(), 4.0);
    }
    
    void testErrorTranslation() {
        Script script;
        std::string text =
            "a = Vector([1, 2])    \n"
            "b = Vector([1, 2, 3]) \n"
            "c = a + b             \n"
        ;
        TS_ASSERT_THROWS(script.run(text), Error);
        try {
            script.run(text);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(error.expected(), "SameSizeMatrices");
            TS_ASSERT_EQUALS(error.get<int>("first_rows"), 2);
            TS_ASSERT_EQUALS(error.get<int>("second_rows"), 3);
        }
    }
    
    void testLinSpaced() {
        Script script;
        MatrixXd result = script.get<MatrixXd>("RowVector.LinSpaced(3, Interval(0, 1))");
        TS_ASSERT_EQUALS(result, RowVectorXd::LinSpaced(3, Interval(0, 1)));
        TS_ASSERT_EQUALS(result, RowVector3d(0, 0.5, 1));
    }
    
    void testMatrixOperators() {
        Script script;
        script.set<MatrixXd>("a", Vector3d(1, 2, 3));
        script.set<MatrixXd>("b", Vector3d(1, 2, 3));
        TS_ASSERT(script.get<bool>("(a - b).isZero()"));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("-a"), Vector3d(-1, -2, -3));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a + b"), Vector3d(2, 4, 6));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a - b"), Vector3d(0, 0, 0));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a * 2"), Vector3d(2, 4, 6));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("3 * a"), Vector3d(3, 6, 9));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a / 2"), Vector3d(0.5, 1, 1.5));
    }
    
    void testExtraction() {
        Script script;
        std::string expression = "Vector([1, 2]) + Vector([Interval(1, 2), Interval(2, 3)])";
        TS_ASSERT_THROWS(script.get<MatrixXd>(expression), Error);
        try {
            script.get<MatrixXd>(expression);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(error.expected(), "CompatiblePythonType");
            TS_ASSERT_EQUALS(error.get<std::string>("expected_type"), "MatrixXd");
            TS_ASSERT_EQUALS(error.get<std::string>("type"), "MatrixXI");
        }
    }
    
    void testFunction() {
        Script script;
        script.run("u = Function.Parameter(2, 0)");
        script.run("v = Function.Parameter(2 ,1)");
        script.run("f = u.squaredNorm() * 1.0 + v.squaredNorm() * 1.0");
        double result = script.get<double>("f(Vector([1, 2]))[0]");
        TS_ASSERT_EQUALS(result, 5.0);
        result = script.get<double>("f.derivative(0)(Vector([3, 4])).value()");
        TS_ASSERT_EQUALS(result, 6.0);
        result = script.get<double>("f.derivative(1).derivative(1)(Vector([5, 6])).value()");
        TS_ASSERT_EQUALS(result, 2.0);
        std::string expression =
            "f.derivative(0)(Vector([Interval(1, 2), Interval(3, 4)])).value()";
        TS_ASSERT_EQUALS(script.get<Interval>(expression).lower(), 2);
        TS_ASSERT_EQUALS(script.get<Interval>(expression).upper(), 4);
    }
    
    void testIntervalBisected() {
        Script script;
        script.run("x = Interval(4, 5)");
        script.run("a, b = x.bisected()");
        Interval a = script.get<Interval>("a");
        Interval b = script.get<Interval>("b");
        TS_ASSERT_EQUALS(a.lower(), 4);
        TS_ASSERT_EQUALS(a.upper(), 4.5);
        TS_ASSERT_EQUALS(b.lower(), 4.5);
        TS_ASSERT_EQUALS(b.upper(), 5);
    }

    void testIntervalContainment() {
        Script script;
        TS_ASSERT(script.get<bool>("4 in Interval(3, 5)"));
        TS_ASSERT(script.get<bool>("Interval(3, 4) in Interval(2, 5)"));
        TS_ASSERT(!script.get<bool>("Interval(2, 4) in Interval(3, 5)"));
    }
    
    void testMatrixOverlap() {
        Script script;
        script.run("u = Vector([1, 2, 3])");
        script.run("v = Vector([Interval(1, 2), Interval(2, 3), Interval(3, 4)])");
        TS_ASSERT(script.get<bool>("v.contains(u)"));
        TS_ASSERT(!script.get<bool>("v.contains(3 * u)"));
        TS_ASSERT(script.get<bool>("u in v"));
    }
    
    void testMatrixHull() {
        Script script;
        script.run("u = Vector([1, 2, 3])");
        script.run("v = Vector([Interval(1, 2), Interval(2, 3), Interval(3, 4)])");
        script.run("result = (3 * u).hull(v)");
        TS_ASSERT_EQUALS(script.get<MatrixXd>("result.cwiseLower()"), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("result.cwiseUpper()"), Vector3d(3, 6, 9));
        script.run("result = v.hull(3 * u)");
        TS_ASSERT_EQUALS(script.get<MatrixXd>("result.cwiseLower()"), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("result.cwiseUpper()"), Vector3d(3, 6, 9));
    }
    
    void testMatrixIntersection() {
        Script script;
        script.run("v = Vector([Interval(1, 2), Interval(2, 3), Interval(3, 4)])");
        script.run("x = (v + Vector.Constant(3, 0.5)).intersection(v)");
        script.run("y = Vector([Interval(1.5, 2), Interval(2.5, 3), Interval(3.5, 4)])");
        TS_ASSERT_EQUALS(
            script.get<MatrixXd>("x.cwiseLower()"),
            script.get<MatrixXd>("y.cwiseLower()")
        );
        TS_ASSERT_EQUALS(
            script.get<MatrixXd>("x.cwiseUpper()"),
            script.get<MatrixXd>("y.cwiseUpper()")
        );
    }

    void testCustomVariable() {
        Script script1;
        Script script2;
        script1.environment().attr("a") = 3;
        TS_ASSERT_EQUALS(script1.get<double>("a"), 3);
        TS_ASSERT_THROWS(script2.get<double>("a"), Error);
    }

    void testVariableThroughScope() {
        Script script1;
        Script script2;
        scope s = script1.environment();
        s.attr("a") = 3;
        TS_ASSERT_EQUALS(script1.get<double>("a"), 3);
        TS_ASSERT_THROWS(script2.get<double>("a"), Error);
    }
    
    void testCustomFunction() {
        Script script1;
        Script script2;

        scope s = script1.environment();
        def("twice", twice);

        TS_ASSERT_EQUALS(script1.get<MatrixXd>("twice(Vector([1, 2, 3]))"), Vector3d(2, 4, 6));
        TS_ASSERT_THROWS(script2.run("twice(Vector([1, 2, 3]))"), Error);
    }
    
    void testCustomClass() {
        Script script1;
        Script script2;

        scope s = script1.environment();
        class_<CustomClass>("CustomClass")
            .def(init<>())
            .def("setValue", &CustomClass::setValue)
            .def("value", &CustomClass::value)
            .def("setFunction", &CustomClass::setFunction)
            .def("function", &CustomClass::function)
            .def("setVector", &CustomClass::setVector)
            .def("vector", &CustomClass::vector);

        script1.run("a = CustomClass()");
        script1.run("a.setValue(10)");
        TS_ASSERT_EQUALS(script1.get<double>("a.value()"), 10.0);
        TS_ASSERT((script1.get<MatrixXd>("a.function()(3.0)") - Vector3d(3, 3, 3)).isZero());
        TS_ASSERT_EQUALS(script1.get<MatrixXd>("a.vector()"), Vector3d(1, 2, 3));
        TS_ASSERT_THROWS(script2.run("b = CustomClass()"), Error);
    }
    
    void testTranspose() {
        Script script;
        MatrixXd a = script.get<MatrixXd>("Vector([1, 2, 3]).transpose()");
        MatrixXd b = script.get<MatrixXd>("RowVector([1, 2, 3])");
        TS_ASSERT_EQUALS(a, b);
    }
    
    void testMatrixIndexing() {
        Script script;
        script.run("a = Matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]]).transpose()");
        script.run("b = Vector([10, 11, 12])");
        TS_ASSERT_EQUALS(script.get<double>("b[-1]"), 12.0);
        TS_ASSERT_EQUALS(script.get<MatrixXd>("b[:]"), Vector3d(10, 11, 12));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("b[-2:]"), Vector2d(11, 12));
        TS_ASSERT_EQUALS(script.get<double>("a[1, 1]"), 5.0);
        TS_ASSERT_EQUALS(script.get<double>("a[-2, -1]"), 6.0);
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a[:, 0]"), Vector3d(1, 4, 7));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a[2, :]"), RowVector3d(7, 8, 9));
        MatrixXd test(2, 3);
        test << RowVector3d(4, 5, 6), RowVector3d(7, 8, 9);
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a[1:2, :]"), test);
        script.run("a[1,1:] = b[1:].transpose()");
        test.resize(3, 3);
        test << RowVector3d(1, 2, 3), RowVector3d(4, 11, 12), RowVector3d(7, 8, 9);
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a"), test);
    }
    
    void testMatrixEquality() {
        Script script;
        script.run("a1 = Vector([1, 2])");
        script.run("a2 = Vector([1, 2])");
        script.run("b1 = Vector([Interval(1), Interval(2)])");
        script.run("b2 = Vector([Interval(1), Interval(2)])");
        TS_ASSERT(script.get<bool>("(a1 - a2).isZero()"));
        TS_ASSERT(script.get<bool>("not (a1 - 2 * a2).isZero()"));
        TS_ASSERT(script.get<bool>("(b1 - b2).isZero()"));
        TS_ASSERT(script.get<bool>("not (b1 - 2 * b2).isZero()"));
        TS_ASSERT(script.get<bool>("(a1 - b1).isZero()"));
        TS_ASSERT(script.get<bool>("not (a1 - 2 * b1).isZero()"));
        TS_ASSERT(script.get<bool>("(b1 - a1).isZero()"));
        TS_ASSERT(script.get<bool>("not (b1 - 2 * a1).isZero()"));
    }

    void testOverloading() {
        Script script;
        script.set("f1", 3 * Function::Parameter());
        Function f2 = Vector3d(2, 0, 0) * Function::Parameter(2, 0) +
            Vector3d(0, 0.5, 0) * Function::Parameter(2, 1);
        script.set("f2", f2);
        TS_ASSERT(script.get<double>("f1(2).value()") - 6 == Zero());
        Interval interval_bounds = script.get<Interval>("f1(Interval(2, 3)).value()");
        TS_ASSERT(interval_bounds.lower() - 6 == Zero());
        TS_ASSERT(interval_bounds.upper() - 9 == Zero());
        TS_ASSERT((script.get<MatrixXd>("f2(Vector([1, 1]))") - Vector3d(2, 0.5, 0)).isZero());
        MatrixXI matrix_bounds = script.get<MatrixXI>(
            "f2(Vector([Interval(1, 2), Interval(2, 3)]))"
        );
        TS_ASSERT((matrix_bounds.cwiseLower() - Vector3d(2, 1, 0)).isZero());
        TS_ASSERT((matrix_bounds.cwiseUpper() - Vector3d(4, 1.5, 0)).isZero());
    }

    void testExplicitModule() {
        Script script;
        TS_ASSERT_EQUALS(
            script.get<std::string>("str(opensolid)"),
            "<module 'opensolid' (built-in)>"
        );
        script.run("f = opensolid.Function.Parameter() * opensolid.Vector([1, 2, 3])");
        MatrixXI bounds = script.get<MatrixXI>(
            "f(opensolid.Vector([opensolid.Interval(1, 2), 0]))"
        );
        TS_ASSERT((bounds.cwiseLower() - Vector3d(1, 2, 3)).isZero());
        TS_ASSERT((bounds.cwiseUpper() - Vector3d(2, 4, 6)).isZero());
    }

    void testFunctionExtraction() {
        Script script;
        Function f = script.get<Function>("sin(Function.Parameter()) + 1");
        TS_ASSERT(f(0).value() - 1 == Zero());
        TS_ASSERT(f(M_PI / 2).value() - 2 == Zero());
        f = script.get<Function>("Function.Parameter(2, 0) + 3 * Function.Parameter(2, 1)");
        TS_ASSERT(f.parameters() == 2);
        TS_ASSERT(f.dimensions() == 1);
        TS_ASSERT(f(Vector2d(1, 2)).value() - 7 == Zero());
    }

    void testComparisons() {
        Script script;
        script.run("a1 = Vector([1, 2, 3])");
        script.run("a2 = Vector([1, 2, 3])");
        script.run("b1 = Vector([Interval(1), 2, 3])");
        script.run("b2 = Vector([1, Interval(2), 3])");

        TS_ASSERT(script.get<bool>("a1 == a2"));
        TS_ASSERT(script.get<bool>("(a1 - a2).isZero()"));
        TS_ASSERT(script.get<bool>("a1 != 2 * a2"));
        TS_ASSERT(script.get<bool>("not (a1 - 2 * a2).isZero()"));

        TS_ASSERT(script.get<bool>("b1 == b2"));
        TS_ASSERT(script.get<bool>("(b1 - b2).isZero()"));
        TS_ASSERT(script.get<bool>("b1 != 2 * b2"));
        TS_ASSERT(script.get<bool>("not (b1 - 2 * b2).isZero()"));

        TS_ASSERT(script.get<bool>("a1 == b1"));
        TS_ASSERT(script.get<bool>("(a1 - b1).isZero()"));
        TS_ASSERT(script.get<bool>("a1 != 2 * b1"));
        TS_ASSERT(script.get<bool>("not (a1 - 2 * b1).isZero()"));
    }

    void testPickling() {
        Script script;
        double a = 3;
        Interval b(4, 5);
        Matrix2d c;
        c(0, 0) = 6;
        c(0, 1) = 7;
        c(1, 0) = 8;
        c(1, 1) = 9;
        Vector2I d(Interval(10, 11), Interval(12, 13));
        Frame3d e = Frame3d().rotated(M_PI / 4, Frame3d().zAxis()).translated(Vector3d(0, 1, 0));
        script.run("import pickle");
        script.set("a", a);
        script.set("b", b);
        script.set<MatrixXd>("c", c);
        script.set<MatrixXI>("d", d);
        script.set<DatumXd>("e", e);
        script.run("a_pickled = pickle.dumps(a)");
        script.run("b_pickled = pickle.dumps(b)");
        script.run("c_pickled = pickle.dumps(c)");
        script.run("d_pickled = pickle.dumps(d)");
        script.run("e_pickled = pickle.dumps(e)");
        script.run("a_unpickled = pickle.loads(a_pickled)");
        script.run("b_unpickled = pickle.loads(b_pickled)");
        script.run("c_unpickled = pickle.loads(c_pickled)");
        script.run("d_unpickled = pickle.loads(d_pickled)");
        script.run("e_unpickled = pickle.loads(e_pickled)");
        double a_extracted = script.get<double>("a_unpickled");
        Interval b_extracted = script.get<Interval>("b_unpickled");
        Matrix2d c_extracted = script.get<MatrixXd>("c_unpickled");
        Vector2I d_extracted = script.get<MatrixXI>("d_unpickled");
        Frame3d e_extracted = script.get<DatumXd>("e_unpickled");
        TS_ASSERT(a - a_extracted == Zero());
        TS_ASSERT(b.lower() - b_extracted.lower() == Zero());
        TS_ASSERT(b.upper() - b_extracted.upper() == Zero());
        TS_ASSERT((c - c_extracted).isZero());
        TS_ASSERT((d.cwiseLower() - d_extracted.cwiseLower()).isZero());
        TS_ASSERT((d.cwiseUpper() - d_extracted.cwiseUpper()).isZero());
        TS_ASSERT((e.origin() - e_extracted.origin()).isZero());
        TS_ASSERT((e.basis() - e_extracted.basis()).isZero());
    }

    void testOverloadOrder() {
        Script script;
        TS_ASSERT(script.get<double>("sqrt(4)") - 2 == Zero());
    }

    void testFunctionRoots() {
        Script script;
        std::string text =
            "x = Function.Parameter() \n"
            "f = x * x * x - 4 * x * x + 5 * x - 2\n"
            "roots = f.roots(Interval(0, 3))\n"
            "derivative_roots = f.derivative().roots(Interval(0, 3))\n"
            "second_derivative_roots = f.derivative().derivative().roots(Interval(0, 3))\n"
        ;
        script.run(text);
        TS_ASSERT((script.get<MatrixXd>("roots") - RowVector2d(1, 2)).isZero());
        TS_ASSERT((script.get<MatrixXd>("derivative_roots") - RowVector2d(1, 5.0 / 3.0)).isZero());
        TS_ASSERT(script.get<MatrixXd>("second_derivative_roots").value() - 4.0 / 3.0 == Zero());
    }

    void testDatum() {
        Script script;
        script.run("import math");
        script.run("frame = Frame3d(Vector([1, 1, 1]), Matrix([[1, 1, 0], [-1, 1, 0]]))");
        script.run("product = Vector([1, 1, 1]) * frame");
        TS_ASSERT(script.get<bool>("(product - Vector([1, 1 + sqrt(2), 2])).isZero()"));
        script.run("product = Vector([1, 1, 1]) * frame.orientation()");
        TS_ASSERT(script.get<bool>("(product - Vector([0, sqrt(2), 1])).isZero()"));
        script.run("quotient = Vector([1, 0, 0]) / frame");
        TS_ASSERT(
            script.get<bool>("(quotient - Vector([-1 / sqrt(2), -1 / sqrt(2), -1])).isZero()")
        );
        script.run("linear_quotient = Vector([1, 0, 0]) / frame.orientation()");
        TS_ASSERT(
            script.get<bool>("(linear_quotient - Vector([1 / sqrt(2), -1 / sqrt(2), 0])).isZero()")
        );
        script.run("global_frame = Frame3d()");
        script.run(
            "frame = global_frame.translated(Vector([1, 1, 1])).rotated(-math.pi / 2, global_frame.xAxis())"
        );
        TS_ASSERT(script.get<bool>("(Vector([1, 2, 3]) * frame - Vector([2, 4, -3])).isZero()"));
    }

    /*
    void xtestDatumTransformation() {
        Frame3d global;
        Frame3d frame = global.translated(Vector3d(1, 1, 1)).rotated(-M_PI / 2, global.xAxis());
        TS_ASSERT(((Vector3d(1, 2, 3) * frame) - Vector3d(2, 4, -3)).isZero());
    }
    
    void xtestDatumComposition() {
        Frame3d frame(Vector3d::UnitX(), Matrix3d::Identity());
        frame = frame.rotated(-M_PI / 4, frame.yAxis());
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

    void xtestAdvancedDatumComposition() {
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
    
    void xtest2d() {
        Frame2d frame(Vector2d::UnitX(), Vector2d(1, 1));
        TS_ASSERT_EQUALS(frame.basis().rows(), 2);
        TS_ASSERT_EQUALS(frame.basis().cols(), 2);
        TS_ASSERT((frame.basis().col(0) - Vector2d(1, 1).normalized()).isZero());
        TS_ASSERT((frame.basis().col(1) - Vector2d(-1, 1).normalized()).isZero());
        TS_ASSERT((Vector2d(2, 2) * frame - Vector2d(1, 2 * sqrt(2.0))).isZero());
        TS_ASSERT((Vector2d(2, 1) / frame - Vector2d(sqrt(2.0), 0)).isZero());
    }
    
    void xtestAccuracy() {
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
    
    void xtestNonOrthogonal() {
        CoordinateSystem<3, 3> coordinate_system(
            Vector3d(1, 2, 3),
            Matrix3d::Ones().triangularView<Upper>()
        );
        TS_ASSERT((Vector3d(1, 1, 1) * coordinate_system - Vector3d(4, 4, 4)).isZero());
        TS_ASSERT((Vector3d(4, 4, 4) / coordinate_system - Vector3d(1, 1, 1)).isZero());
    }

    void xtestPlaneFromNormal() {
        Plane3d plane(Vector3d(1, 1, 1), Vector3d::UnitZ());
        TS_ASSERT(plane.basis().isUnitary());
        TS_ASSERT((plane.basis().col(0).cross(plane.basis().col(1)) - Vector3d::UnitZ()).isZero());
        Vector3d point(2, 2, 2);
        Vector3d projected_point = point % plane;
        Vector3d expected_projected(2, 2, 1);
        TS_ASSERT((projected_point - expected_projected).isZero());
    }

    void xtestReversed() {
        TS_ASSERT((Frame3d().xAxis().reversed().point(1) - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((Frame3d().reversed(2).point(1, 2, 3) - Vector3d(1, 2, -3)).isZero());
        Vector3d point = Frame3d().translated(Vector3d(1, 1, 1)).yReversed().point(1, 2, 3);
        Vector3d expected(2, -1, 4);
        TS_ASSERT((point - expected).isZero());
    }
    */
};
