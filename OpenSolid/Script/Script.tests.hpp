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

#include <OpenSolid/Common/Error.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Script/Script.hpp>

using namespace OpenSolid;
using namespace boost::python;

struct MatrixDoubler
{
    inline object operator()(tuple arguments, dict keyword_arguments) {
        return object(MatrixXD(2 * extract<MatrixXD>(arguments[0])));
    }
};

class CustomClass
{
private:
    Double _value;
    Function _function;
    Vector3D _vector;
public:
    CustomClass() :
        _value(3), _function(Function::Parameter(1, 0) * Vector3D(1, 1, 1)), _vector(1, 2, 3) {}
        
    void setValue(Double value) {_value = value;}
    Double value() const {return _value;}
    
    void setFunction(const Function& function) {_function = function;}
    Function function() const {return _function;}
    
    void setVector(const MatrixXD& vector) {_vector = vector;}
    MatrixXD vector() const {return _vector;}
};

void bindCustomClass() {
    class_<CustomClass>("CustomClass")
        .def(init<>())
        .def("setValue", &CustomClass::setValue)
        .def("value", &CustomClass::value)
        .def("setFunction", &CustomClass::setFunction)
        .def("function", &CustomClass::function)
        .def("setVector", &CustomClass::setVector)
        .def("vector", &CustomClass::vector);
}

class ScriptingTestSuite : public CxxTest::TestSuite
{
public:
    void testRun() {
        Script script;
        script.run("result = 1 + 2");
        TS_ASSERT_EQUALS(script.get<Double>("result"), 3.0);
    }

    void testEvaluation() {
        Script script;
        TS_ASSERT_EQUALS(script.get<Double>("1 + 2"), 3.0);
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
        script.set("b", MatrixXD(Vector3D(2, 3, 4)));
        TS_ASSERT_THROWS(script.get<MatrixXD>("a.cross(b)"), Error);
        try {
            script.get<MatrixXD>("a.cross(b)");
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(error.expected(), "NoPythonExceptions");
        }
    }
    
    void testParameter() {
        Script script;
        script.set("a", 3.0);
        script.set("b", 2.0);
        TS_ASSERT_EQUALS(script.get<Double>("a + b"), 5.0);
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
    
    void testMatrixXD() {
        Script script;
        script.set("v", MatrixXD(Vector3D(1, 2, 3)));
        script.set("a", 4.0);
        script.set("b", 5.0);
        Vector3D result = script.get<MatrixXD>("v + a * Vector3D(1, 0, 0) + b * Vector3D(0, 1, 0)");
        TS_ASSERT(result.isEqualTo(Vector3D(5, 7, 3)));
    }
    
    void testMatrixXI() {
        Script script;
        Vector3I vector(Interval(1.0, 2.0), Interval(2.0, 3.0), Interval(3.0, 4.0));
        script.set("v", MatrixXI(vector));
        script.set("a", Interval(4.0, 5.0));
        script.set("b", Interval(5.0, 6.0));
        Vector3I result = script.get<MatrixXI>("v + a * Vector3D(1, 0, 0) + b * Vector3D(0, 1, 0)");
        TS_ASSERT_EQUALS(result.x().lower(), 5.0);
        TS_ASSERT_EQUALS(result.x().upper(), 7.0);
        TS_ASSERT_EQUALS(result.y().lower(), 7.0);
        TS_ASSERT_EQUALS(result.y().upper(), 9.0);
        TS_ASSERT_EQUALS(result.z().lower(), 3.0);
        TS_ASSERT_EQUALS(result.z().upper(), 4.0);
    }
    
    void testInternalConversionError() {
        Script script;
        std::string text =
            "a = Interval(1)                    \n"
            "result = Vector3D(1, 0, 0).dot(a)  \n"
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
            "a = Vector3D(1, 2, 3)  \n"
            "b = Vector3D(4, 5, 6)  \n"
            "a.dot(b)               \n"
        ;
        TS_ASSERT_EQUALS(script.get<Double>(text), 32.0);
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
            "a = Vector2D(1, 2)    \n"
            "b = Vector3D(1, 2, 3) \n"
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
        MatrixXD result = script.get<MatrixXD>("RowVectorXD.LinSpaced(3, Interval(0, 1))");
        TS_ASSERT_EQUALS(result, RowVectorXD::LinSpaced(3, Interval(0, 1)));
        TS_ASSERT_EQUALS(result, RowVector3D(0, 0.5, 1));
    }
    
    void testMatrixOperators() {
        Script script;
        script.set<MatrixXD>("a", Vector3D(1, 2, 3));
        script.set<MatrixXD>("b", Vector3D(1, 2, 3));
        TS_ASSERT(script.get<bool>("a.isEqualTo(b)"));
        TS_ASSERT_EQUALS(script.get<MatrixXD>("-a"), Vector3D(-1, -2, -3));
        TS_ASSERT_EQUALS(script.get<MatrixXD>("a + b"), Vector3D(2, 4, 6));
        TS_ASSERT_EQUALS(script.get<MatrixXD>("a - b"), Vector3D(0, 0, 0));
        TS_ASSERT_EQUALS(script.get<MatrixXD>("a * 2"), Vector3D(2, 4, 6));
        TS_ASSERT_EQUALS(script.get<MatrixXD>("3 * a"), Vector3D(3, 6, 9));
        TS_ASSERT_EQUALS(script.get<MatrixXD>("a / 2"), Vector3D(0.5, 1, 1.5));
    }
    
    void testExtraction() {
        Script script;
        std::string expression = "Vector2D(1, 2) + Vector2I(Interval(1, 2), Interval(2, 3))";
        TS_ASSERT_THROWS(script.get<MatrixXD>(expression), Error);
        try {
            script.get<MatrixXD>(expression);
        } catch (const Error& error) {
            TS_ASSERT_EQUALS(error.expected(), "CompatiblePythonType");
            TS_ASSERT_EQUALS(error.get<std::string>("expected_type"), "MatrixXD");
            TS_ASSERT_EQUALS(error.get<std::string>("type"), "MatrixXI");
        }
    }
    
    void testFunction() {
        Script script;
        script.run("f = Function.u.squaredNorm() * 1.0 + Function.v.squaredNorm() * 1.0");
        Double result = script.get<Double>("f(Vector2D(1, 2))[0]");
        TS_ASSERT_EQUALS(result, 5.0);
        result = script.get<Double>("f.derivative(0)(Vector2D(3, 4)).value()");
        TS_ASSERT_EQUALS(result, 6.0);
        result = script.get<Double>("f.derivative(1).derivative(1)(Vector2D(5, 6)).value()");
        TS_ASSERT_EQUALS(result, 2.0);
        std::string expression =
            "f.derivative(0)(Vector2I(Interval(1, 2), Interval(3, 4))).value()";
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
    
    void testMatrixOverlap() {
        Script script;
        script.run("u = Vector3D(1, 2, 3)");
        script.run("v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4))");
        TS_ASSERT(script.get<bool>("v.contains(u)"));
        TS_ASSERT(!script.get<bool>("v.contains(3 * u)"));
    }
    
    void testMatrixHull() {
        Script script;
        script.run("u = Vector3D(1, 2, 3)");
        script.run("v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4))");
        script.run("result = (3 * u).hull(v)");
        TS_ASSERT_EQUALS(script.get<MatrixXD>("result.cwiseLower()"), Vector3D(1, 2, 3));
        TS_ASSERT_EQUALS(script.get<MatrixXD>("result.cwiseUpper()"), Vector3D(3, 6, 9));
        script.run("result = v.hull(3 * u)");
        TS_ASSERT_EQUALS(script.get<MatrixXD>("result.cwiseLower()"), Vector3D(1, 2, 3));
        TS_ASSERT_EQUALS(script.get<MatrixXD>("result.cwiseUpper()"), Vector3D(3, 6, 9));
    }
    
    void testMatrixIntersection() {
        Script script;
        script.run("v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4))");
        script.run("x = (v + Vector3I.Constant(Interval(0.5))).intersection(v)");
        script.run("y = Vector3I(Interval(1.5, 2), Interval(2.5, 3), Interval(3.5, 4))");
        TS_ASSERT_EQUALS(
            script.get<MatrixXD>("x.cwiseLower()"),
            script.get<MatrixXD>("y.cwiseLower()")
        );
        TS_ASSERT_EQUALS(
            script.get<MatrixXD>("x.cwiseUpper()"),
            script.get<MatrixXD>("y.cwiseUpper()")
        );
    }
    
    void testCustomFunction() {
        Script script1;
        Script script2;
        script1.def("twice", MatrixDoubler());
        TS_ASSERT_EQUALS(script1.get<MatrixXD>("twice(Vector3D(1, 2, 3))"), Vector3D(2, 4, 6));
        TS_ASSERT_THROWS(script2.run("twice(Vector3D(1, 2, 3))"), Error);
    }
    
    void testCustomClass() {
        Script script1;
        Script script2;
        script1.extend(bindCustomClass);
        script1.run("a = CustomClass()");
        script1.run("a.setValue(10)");
        TS_ASSERT_EQUALS(script1.get<Double>("a.value()"), 10.0);
        TS_ASSERT(script1.get<MatrixXD>("a.function()(3.0)").isApprox(Vector3D(3, 3, 3)));
        TS_ASSERT_EQUALS(script1.get<MatrixXD>("a.vector()"), Vector3D(1, 2, 3));
        TS_ASSERT_THROWS(script2.run("b = CustomClass()"), Error);
    }
    
    void testTranspose() {
        Script script;
        MatrixXD a = script.get<MatrixXD>("Vector3D(1, 2, 3).transpose()");
        MatrixXD b = script.get<MatrixXD>("RowVector3D(1, 2, 3)");
        TS_ASSERT_EQUALS(a, b);
    }
    
    void testMatrixIndexing() {
        Script script;
        script.run("a = Matrix3D(1, 2, 3, 4, 5, 6, 7, 8, 9)");
        script.run("b = Vector3D(10, 11, 12)");
        TS_ASSERT_EQUALS(script.get<Double>("b[-1]"), 12.0);
        TS_ASSERT_EQUALS(script.get<MatrixXD>("b[:]"), Vector3D(10, 11, 12));
        TS_ASSERT_EQUALS(script.get<MatrixXD>("b[-2:]"), Vector2D(11, 12));
        TS_ASSERT_EQUALS(script.get<Double>("a[1, 1]"), 5.0);
        TS_ASSERT_EQUALS(script.get<Double>("a[-2, -1]"), 6.0);
        TS_ASSERT_EQUALS(script.get<MatrixXD>("a[:, 0]"), Vector3D(1, 4, 7));
        TS_ASSERT_EQUALS(script.get<MatrixXD>("a[2, :]"), RowVector3D(7, 8, 9));
        MatrixXD test(2, 3);
        test << RowVector3D(4, 5, 6), RowVector3D(7, 8, 9);
        TS_ASSERT_EQUALS(script.get<MatrixXD>("a[1:2, :]"), test);
        script.run("a[1,1:] = b[1:].transpose()");
        test.resize(3, 3);
        test << RowVector3D(1, 2, 3), RowVector3D(4, 11, 12), RowVector3D(7, 8, 9);
        TS_ASSERT_EQUALS(script.get<MatrixXD>("a"), test);
    }
    
    void testMatrixEquality() {
        Script script;
        script.run("a1 = Vector2D(1, 2)");
        script.run("a2 = Vector2D(1, 2)");
        script.run("b1 = Vector2I(1, 2)");
        script.run("b2 = Vector2I(1, 2)");
        TS_ASSERT(script.get<bool>("a1.isEqualTo(a2)"));
        TS_ASSERT(script.get<bool>("a1.isNotEqualTo(2 * a2)"));
        TS_ASSERT(script.get<bool>("b1.isEqualTo(b2)"));
        TS_ASSERT(script.get<bool>("b1.isNotEqualTo(2 * b2)"));
        TS_ASSERT(script.get<bool>("a1.isEqualTo(b1)"));
        TS_ASSERT(script.get<bool>("a1.isNotEqualTo(2 * b1)"));
        TS_ASSERT(script.get<bool>("b1.isEqualTo(a1)"));
        TS_ASSERT(script.get<bool>("b1.isNotEqualTo(2 * a1)"));
    }

    void testOverloading() {
        Script script;
        script.set("f1", 3 * Function::Parameter(1, 0));
        Function f2 = Vector3D(2, 0, 0) * Function::Parameter(2, 0) +
            Vector3D(0, 0.5, 0) * Function::Parameter(2, 1);
        script.set("f2", f2);
        TS_ASSERT(script.get<Double>("f1(2).value()").isEqualTo(6.0));
        Interval interval_bounds = script.get<Interval>("f1(Interval(2, 3)).value()");
        TS_ASSERT(interval_bounds.lower().isEqualTo(6));
        TS_ASSERT(interval_bounds.upper().isEqualTo(9));
        TS_ASSERT(
            script.get<MatrixXD>("f2(Vector2D(1, 1))").isEqualTo(Vector3D(2, 0.5, 0))
        );
        MatrixXI matrix_bounds = script.get<MatrixXI>(
            "f2(Vector2I(Interval(1, 2), Interval(2, 3)))"
        );
        TS_ASSERT(matrix_bounds.cwiseLower().isEqualTo(Vector3D(2, 1, 0)));
        TS_ASSERT(matrix_bounds.cwiseUpper().isEqualTo(Vector3D(4, 1.5, 0)));
    }

    void testExplicitModule() {
        Script script;
        TS_ASSERT_EQUALS(
            script.get<std::string>("str(opensolid)"),
            "<module 'opensolid' (built-in)>"
        );
        script.run("f = opensolid.Function.Parameter(1, 0) * opensolid.Vector3D(1, 2, 3)");
        MatrixXI bounds = script.get<MatrixXI>(
            "f(opensolid.Vector2I(opensolid.Interval(1, 2), 0))"
        );
        TS_ASSERT(bounds.cwiseLower().isEqualTo(Vector3D(1, 2, 3)));
        TS_ASSERT(bounds.cwiseUpper().isEqualTo(Vector3D(2, 4, 6)));
    }
};
