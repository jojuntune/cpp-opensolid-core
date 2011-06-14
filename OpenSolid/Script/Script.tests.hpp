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
#include <OpenSolid/Common/Comparison.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include "Script.hpp"

using namespace OpenSolid;
using namespace boost::python;

struct MatrixDoubler
{
    inline object operator()(tuple arguments, dict keyword_arguments) {
        return object(MatrixXd(2 * extract<MatrixXd>(arguments[0])));
    }
};

class CustomClass
{
private:
    double _value;
    Function _function;
    Vector3d _vector;
public:
    CustomClass() :
        _value(3), _function(Function::Parameter(1, 0) * Vector3d(1, 1, 1)), _vector(1, 2, 3) {}
        
    void setValue(double value) {_value = value;}
    double value() const {return _value;}
    
    void setFunction(const Function& function) {_function = function;}
    Function function() const {return _function;}
    
    void setVector(const MatrixXd& vector) {_vector = vector;}
    MatrixXd vector() const {return _vector;}
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
    
    void testMatrixXd() {
        Script script;
        script.set("v", MatrixXd(Vector3d(1, 2, 3)));
        script.set("a", 4.0);
        script.set("b", 5.0);
        Vector3d result = script.get<MatrixXd>("v + a * Vector3d(1, 0, 0) + b * Vector3d(0, 1, 0)");
        TS_ASSERT(Comparison::equal(result,  Vector3d(5, 7, 3)));
    }
    
    void testMatrixXI() {
        Script script;
        Vector3I vector(Interval(1.0, 2.0), Interval(2.0, 3.0), Interval(3.0, 4.0));
        script.set("v", MatrixXI(vector));
        script.set("a", Interval(4.0, 5.0));
        script.set("b", Interval(5.0, 6.0));
        Vector3I result = script.get<MatrixXI>("v + a * Vector3d(1, 0, 0) + b * Vector3d(0, 1, 0)");
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
            "result = Vector3d(1, 0, 0).dot(a)  \n"
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
            "a = Vector3d(1, 2, 3)  \n"
            "b = Vector3d(4, 5, 6)  \n"
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
            "a = Vector2d(1, 2)    \n"
            "b = Vector3d(1, 2, 3) \n"
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
        MatrixXd result = script.get<MatrixXd>("RowVectorXd.LinSpaced(3, Interval(0, 1))");
        TS_ASSERT_EQUALS(result, RowVectorXd::LinSpaced(3, Interval(0, 1)));
        TS_ASSERT_EQUALS(result, RowVector3d(0, 0.5, 1));
    }
    
    void testMatrixOperators() {
        Script script;
        script.set<MatrixXd>("a", Vector3d(1, 2, 3));
        script.set<MatrixXd>("b", Vector3d(1, 2, 3));
        TS_ASSERT(script.get<bool>("a == b"));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("-a"), Vector3d(-1, -2, -3));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a + b"), Vector3d(2, 4, 6));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a - b"), Vector3d(0, 0, 0));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a * 2"), Vector3d(2, 4, 6));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("3 * a"), Vector3d(3, 6, 9));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("a / 2"), Vector3d(0.5, 1, 1.5));
    }
    
    void testExtraction() {
        Script script;
        std::string expression = "Vector2d(1, 2) + Vector2I(Interval(1, 2), Interval(2, 3))";
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
        script.run("f = Function.u.squaredNorm() * 1.0 + Function.v.squaredNorm() * 1.0");
        double result = script.get<double>("f(Vector2d(1, 2)).scalar()");
        TS_ASSERT_EQUALS(result, 5.0);
        result = script.get<double>("f.derivative(0)(Vector2d(3, 4)).scalar()");
        TS_ASSERT_EQUALS(result, 6.0);
        result = script.get<double>("f.derivative(1).derivative(1)(Vector2d(5, 6)).scalar()");
        TS_ASSERT_EQUALS(result, 2.0);
        std::string expression =
            "f.derivative(0)(Vector2I(Interval(1, 2), Interval(3, 4))).scalar()";
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
        script.run("u = Vector3d(1, 2, 3)");
        script.run("v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4))");
        TS_ASSERT(script.get<bool>("v.contain(u)"));
        TS_ASSERT(!script.get<bool>("v.contain(3 * u)"));
    }
    
    void testMatrixHull() {
        Script script;
        script.run("u = Vector3d(1, 2, 3)");
        script.run("v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4))");
        script.run("result = (3 * u).hull(v)");
        TS_ASSERT_EQUALS(script.get<MatrixXd>("result.cwiseLower()"), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("result.cwiseUpper()"), Vector3d(3, 6, 9));
        script.run("result = v.hull(3 * u)");
        TS_ASSERT_EQUALS(script.get<MatrixXd>("result.cwiseLower()"), Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(script.get<MatrixXd>("result.cwiseUpper()"), Vector3d(3, 6, 9));
    }
    
    void testMatrixIntersection() {
        Script script;
        script.run("v = Vector3I(Interval(1, 2), Interval(2, 3), Interval(3, 4))");
        script.run("x = (v + Vector3I.Constant(Interval(0.5))).intersection(v)");
        script.run("y = Vector3I(Interval(1.5, 2), Interval(2.5, 3), Interval(3.5, 4))");
        TS_ASSERT_EQUALS(
            script.get<MatrixXd>("x.cwiseLower()"),
            script.get<MatrixXd>("y.cwiseLower()")
        );
        TS_ASSERT_EQUALS(
            script.get<MatrixXd>("x.cwiseUpper()"),
            script.get<MatrixXd>("y.cwiseUpper()")
        );
    }
    
    void testCustomFunction() {
        Script script1;
        Script script2;
        script1.def("twice", MatrixDoubler());
        TS_ASSERT_EQUALS(script1.get<MatrixXd>("twice(Vector3d(1, 2, 3))"), Vector3d(2, 4, 6));
        TS_ASSERT_THROWS(script2.run("twice(Vector3d(1, 2, 3))"), Error);
    }
    
    void testCustomClass() {
        Script script1;
        Script script2;
        script1.extend(bindCustomClass);
        script1.run("a = CustomClass()");
        script1.run("a.setValue(10)");
        TS_ASSERT_EQUALS(script1.get<double>("a.value()"), 10.0);
        TS_ASSERT(script1.get<MatrixXd>("a.function()(3.0)").isApprox(Vector3d(3, 3, 3)));
        TS_ASSERT_EQUALS(script1.get<MatrixXd>("a.vector()"), Vector3d(1, 2, 3));
        TS_ASSERT_THROWS(script2.run("b = CustomClass()"), Error);
    }
    
    void testTranspose() {
        Script script;
        MatrixXd a = script.get<MatrixXd>("Vector3d(1, 2, 3).transpose()");
        MatrixXd b = script.get<MatrixXd>("RowVector3d(1, 2, 3)");
        TS_ASSERT_EQUALS(a, b);
    }
    
    void testMatrixIndexing() {
        Script script;
        script.run("a = Matrix3d(1, 2, 3, 4, 5, 6, 7, 8, 9)");
        script.run("b = Vector3d(10, 11, 12)");
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
        script.run("a1 = Vector2d(1, 2)");
        script.run("a2 = Vector2d(1, 2)");
        script.run("b1 = Vector2I(Interval(1), Interval(2))");
        script.run("b2 = Vector2I(Interval(1), Interval(2))");
        TS_ASSERT(script.get<bool>("a1 == a2"));
        TS_ASSERT(script.get<bool>("a1 != 2 * a2"));
        TS_ASSERT(!script.get<bool>("a1 != a2"));
        TS_ASSERT(!script.get<bool>("a1 == 2 * a2"));
        TS_ASSERT(script.get<bool>("b1 == b2"));
        TS_ASSERT(script.get<bool>("b1 != 2 * b2"));
        TS_ASSERT(script.get<bool>("a1 == b1"));
        TS_ASSERT(script.get<bool>("a1 != 2 * b1"));
        TS_ASSERT(script.get<bool>("b1 == a1"));
        TS_ASSERT(script.get<bool>("b1 != 2 * a1"));
    }

    void testOverloading() {
        Script script;
        script.set("f1", 3 * Function::Parameter(1, 0));
        Function f2 = Vector3d(2, 0, 0) * Function::Parameter(2, 0) +
            Vector3d(0, 0.5, 0) * Function::Parameter(2, 1);
        script.set("f2", f2);
        TS_ASSERT(Comparison::equal(script.get<double>("f1(2).scalar()"), 6.0));
        TS_ASSERT(
            Comparison::equal(script.get<Interval>("f1(Interval(2, 3)).scalar()"), Interval(6, 9))
        );
        TS_ASSERT(
            Comparison::equal(script.get<MatrixXd>("f2(Vector2d(1, 1))"), Vector3d(2, 0.5, 0))
        );
        TS_ASSERT(
            Comparison::equal(
                script.get<MatrixXI>("f2(Vector2I(Interval(1, 2), Interval(2, 3)))"),
                Vector3I(Interval(2, 4), Interval(1, 1.5), 0.0)
            )
        );
    }

    void testExplicitModule() {
        Script script;
        script.run("f = OpenSolid.Function.Parameter(1, 0) * OpenSolid.Vector3d(1, 2, 3)");
        TS_ASSERT(
            Comparison::equal(
                script.get<MatrixXI>("f(OpenSolid.Vector2I(OpenSolid.Interval(1, 2), 0))"),
                Vector3I(Interval(1, 2), Interval(2, 4), Interval(3, 6))
            )
        );
    }
};
