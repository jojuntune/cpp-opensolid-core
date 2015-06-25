/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
************************************************************************************/

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <boost/timer.hpp>
#include <catch/catch.hpp>

#include <vector>

using namespace opensolid;

ParametricExpression<double, Point2d>
scalarSquiggle() {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    return sin(2 * M_PI * u) + cos(2 * M_PI * v);
}

ParametricExpression<Vector3d, Point2d>
vectorSquiggle() {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    return ParametricExpression<Vector3d, Point2d>::fromComponents(u, v, scalarSquiggle());
}

std::vector<Point2d>
squiggleParameterValues() {
    std::vector<Point2d> results(25);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            results[i * 5 + j] = Point2d(i / 5.0 + 0.1, j / 5.0 + 0.1);
        }
    }
    return results;
}

namespace
{
    Matrix1d
    matrixComponents(double value) {
        return Matrix1d(value);
    }

    template <int iNumDimensions>
    Matrix<double, iNumDimensions, 1>
    matrixComponents(const Vector<double, iNumDimensions>& vector) {
        return vector.components();
    }

    template <int iNumDimensions>
    Matrix<double, iNumDimensions, 1>
    matrixComponents(const Point<iNumDimensions>& point) {
        return point.components();
    }

    double
    offsetParameter(double parameterValue, int index, double amount) {
        assert(index == 0);
        return parameterValue + amount;
    }

    template <int iNumDimensions>
    Vector<double, iNumDimensions>
    offsetParameter(const Vector<double, iNumDimensions>& vector, int index, double amount) {
        assert(index >= 0 && index < iNumDimensions);
        return vector + amount * Vector<double, iNumDimensions>::unit(index);
    }

    template <int iNumDimensions>
    Point<iNumDimensions>
    offsetParameter(const Point<iNumDimensions>& point, int index, double amount) {
        assert(index >= 0 && index < iNumDimensions);
        return point + amount * Vector<double, iNumDimensions>::unit(index);
    }
}

template <class TValue, class TParameter>
void testJacobian(
    const ParametricExpression<TValue, TParameter>& expression,
    const TParameter& parameterValues
) {
    Matrix<
        double,
        NumDimensions<TValue>::Value,
        NumDimensions<TParameter>::Value
    > jacobian = expression.jacobian(parameterValues);

    Matrix<
        double,
        NumDimensions<TValue>::Value,
        NumDimensions<TParameter>::Value
    > expectedJacobian;

    for (int j = 0; j < NumDimensions<TParameter>::Value; ++j) {
        Matrix<double, NumDimensions<TValue>::Value, 1> partialDerivative = matrixComponents(
            expression.derivative(j).evaluate(parameterValues)
        );
        for (int i = 0; i < NumDimensions<TValue>::Value; ++i) {
            expectedJacobian(i, j) = partialDerivative(i);
        }
    }
    CAPTURE(expression);
    CAPTURE(parameterValues);
    CAPTURE(jacobian);
    CAPTURE(expectedJacobian);
    REQUIRE((jacobian - expectedJacobian).isZero());
    for (int j = 0; j < NumDimensions<TParameter>::Value; ++j) {
        std::vector<TParameter> shiftedParameterValues(2);
        shiftedParameterValues[0] = offsetParameter(parameterValues, j, -1e-6 / 2.0);
        shiftedParameterValues[1] = offsetParameter(parameterValues, j, 1e-6 / 2.0);
        std::vector<TValue> shiftedValues = expression.evaluate(shiftedParameterValues);
        Matrix<double, NumDimensions<TValue>::Value, 1> numericalDerivative = matrixComponents(
            shiftedValues[1] - shiftedValues[0]
        ) / 1e-6;
        Matrix<double, NumDimensions<TValue>::Value, 1> jacobianDerivative = jacobian.column(j);
        CAPTURE(expression);
        CAPTURE(numericalDerivative);
        CAPTURE(jacobianDerivative);
        REQUIRE((numericalDerivative - jacobianDerivative).isZero(1e-3));
    }
}

TEST_CASE("Constant") {
    ParametricExpression<double, double> expression = (
        ParametricExpression<double, double>::constant(3.0)
    );
    REQUIRE(expression.implementation()->isConstantExpression());
    REQUIRE((expression.evaluate(0.0) - 3.0) == Zero());
}

TEST_CASE("Arithmetic") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<double, Point2d> expression = 2.0 + u * 1.0 - 1.0 * v;
    
    REQUIRE((expression.evaluate(Point2d(0.0, 0.0)) - 2.0) == Zero());
    REQUIRE((expression.evaluate(Point2d(1.0, 0.0)) - 3.0) == Zero());
    REQUIRE((expression.evaluate(Point2d(1.0, 1.0)) - 2.0) == Zero());
    REQUIRE((expression.evaluate(Point2d(0.0, 1.0)) - 1.0) == Zero());
    REQUIRE((expression.derivative(u).evaluate(Point2d(0.0, 0.0)) - 1.0) == Zero());
    REQUIRE((expression.derivative(v).evaluate(Point2d(0.0, 0.0)) + 1.0) == Zero());
    
    ParametricExpression<double, Point2d> negated = -expression;
    
    REQUIRE((negated.evaluate(Point2d(0.0, 0.0)) + 2.0) == Zero());
    REQUIRE((negated.evaluate(Point2d(1.0, 0.0)) + 3.0) == Zero());
    REQUIRE((negated.evaluate(Point2d(1.0, 1.0)) + 2.0) == Zero());
    REQUIRE((negated.evaluate(Point2d(0.0, 1.0)) + 1.0) == Zero());
    REQUIRE((negated.derivative(u).evaluate(Point2d(0.0, 0.0)) + 1.0) == Zero());
    REQUIRE((negated.derivative(v).evaluate(Point2d(0.0, 0.0)) - 1.0) == Zero());
}

TEST_CASE("Multiplication") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<double, Point2d> expression = 1.0 + u / 1.0 * v / 1.0;

    REQUIRE((expression.evaluate(Point2d(0.0, 0.0)) - 1.0) == Zero());
    REQUIRE((expression.evaluate(Point2d(1.0, 0.0)) - 1.0) == Zero());
    REQUIRE((expression.evaluate(Point2d(1.0, 1.0)) - 2.0) == Zero());
    REQUIRE((expression.evaluate(Point2d(0.0, 1.0)) - 1.0) == Zero());

    ParametricExpression<double, Point2d> uDerivative = expression.derivative(u);
    
    REQUIRE(uDerivative.evaluate(Point2d(0.0, 0.0)) == Zero());
    REQUIRE(uDerivative.evaluate(Point2d(1.0, 0.0)) == Zero());
    REQUIRE((uDerivative.evaluate(Point2d(1.0, 1.0)) - 1.0) == Zero());
    REQUIRE((uDerivative.evaluate(Point2d(0.0, 1.0)) - 1.0) == Zero());

    ParametricExpression<double, Point2d> vDerivative = expression.derivative(v);
    
    REQUIRE(vDerivative.evaluate(Point2d(0.0, 0.0)) == Zero());
    REQUIRE((vDerivative.evaluate(Point2d(1.0, 0.0)) - 1.0) == Zero());
    REQUIRE((vDerivative.evaluate(Point2d(1.0, 1.0)) - 1.0) == Zero());
    REQUIRE(vDerivative.evaluate(Point2d(0.0, 1.0)) == Zero());
}

TEST_CASE("Square") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<double, Point2d> expression = u.squared() * 1.0 + v.squared() * 1.0;
    REQUIRE((expression.evaluate(Point2d(1.0, 2.0)) - 5.0) == Zero());
    ParametricExpression<double, Point2d> uDerivative = expression.derivative(u);
    REQUIRE((uDerivative.evaluate(Point2d(3.0, 4.0)) - 6.0) == Zero());
    ParametricExpression<double, Point2d> vSecondDerivative = (
        expression.derivative(v).derivative(v)
    );
    REQUIRE((vSecondDerivative.evaluate(Point2d(5.0, 6.0)) - 2.0) == Zero());
}

TEST_CASE("Norm") {
    Parameter1d t;
    ParametricExpression<Vector2d, double> arc = (
        3.0 * (cos(t) * Vector2d(1.0, 0.0) + Vector2d(0.0, 1.0) * sin(t))
    );
    Vector2d evaluated = arc.normalized().evaluate(M_PI / 4.0);
    Vector2d expected(1.0 / sqrt(2.0), 1.0 / sqrt(2.0));
    REQUIRE((evaluated - expected).isZero());
}

TEST_CASE("Sine") {
    Parameter1d t;
    ParametricExpression<double, double> expression = sin(t);

    std::vector<double> parameterValues(4);
    parameterValues[0] = 0.0;
    parameterValues[1] = M_PI / 2.0;
    parameterValues[2] = M_PI;
    parameterValues[3] = 3.0 * M_PI / 2.0;
    std::vector<double> resultValues = expression.evaluate(parameterValues);
    REQUIRE(resultValues[0] == Zero());
    REQUIRE((resultValues[1] - 1.0) == Zero());
    REQUIRE(resultValues[2] == Zero());
    REQUIRE((resultValues[3] + 1.0) == Zero());

    std::vector<Interval> parameterBounds(4);
    parameterBounds[0] = Interval(0.0, M_PI / 2.0);
    parameterBounds[1] = Interval(M_PI / 2.0, M_PI);
    parameterBounds[2] = Interval(M_PI, 3.0 * M_PI / 2.0);
    parameterBounds[3] = Interval(0.0, 2.0 * M_PI);
    std::vector<Interval> resultBounds = expression.evaluate(parameterBounds);
    REQUIRE(resultBounds[0].lowerBound() == Zero());
    REQUIRE((resultBounds[0].upperBound() - 1) == Zero());
    REQUIRE(resultBounds[1].lowerBound() == Zero());
    REQUIRE((resultBounds[1].upperBound() - 1) == Zero());
    REQUIRE((resultBounds[2].lowerBound() + 1) == Zero());
    REQUIRE(resultBounds[2].upperBound() == Zero());
    REQUIRE((resultBounds[3].lowerBound() + 1) == Zero());
    REQUIRE((resultBounds[3].upperBound() - 1) == Zero());
}

TEST_CASE("Cosine") {
    Parameter1d t;
    ParametricExpression<double, double> expression = cos(t);

    std::vector<double> parameterValues(4);
    parameterValues[0] = 0;
    parameterValues[1] = M_PI / 2;
    parameterValues[2] = M_PI;
    parameterValues[3] = 3 * M_PI / 2;
    std::vector<double> resultValues = expression.evaluate(parameterValues);
    REQUIRE((resultValues[0] - 1.0) == Zero());
    REQUIRE(resultValues[1] == Zero());
    REQUIRE((resultValues[2] + 1.0) == Zero());
    REQUIRE(resultValues[3] == Zero());

    std::vector<Interval> parameterBounds(4);
    parameterBounds[0] = Interval(0, M_PI / 2);
    parameterBounds[1] = Interval(M_PI / 2, M_PI);
    parameterBounds[2] = Interval(M_PI, 3 * M_PI / 2);
    parameterBounds[3] = Interval(0, 2 * M_PI);
    std::vector<Interval> resultBounds = expression.evaluate(parameterBounds);
    REQUIRE(resultBounds[0].lowerBound() == Zero());
    REQUIRE((resultBounds[0].upperBound() - 1) == Zero());
    REQUIRE((resultBounds[1].lowerBound() + 1) == Zero());
    REQUIRE(resultBounds[1].upperBound() == Zero());
    REQUIRE((resultBounds[2].lowerBound() + 1) == Zero());
    REQUIRE(resultBounds[2].upperBound() == Zero());
    REQUIRE((resultBounds[3].lowerBound() + 1) == Zero());
    REQUIRE((resultBounds[3].upperBound() - 1) == Zero());
}

TEST_CASE("Component") {
    Parameter1d t;
    ParametricExpression<Vector3d, double> expression = Vector3d(1, 2, 3) + t * Vector3d(1, 2, 3);
    std::vector<double> parameterValues(3);
    parameterValues[0] = 0.0;
    parameterValues[1] = 0.5;
    parameterValues[2] = 1.0;

    std::vector<Vector3d> vectorResults = expression.evaluate(parameterValues);
    REQUIRE((vectorResults[0].y() - 2.0) == Zero());
    REQUIRE((vectorResults[1].y() - 3.0) == Zero());
    REQUIRE((vectorResults[2].y() - 4.0) == Zero());

    std::vector<double> componentResults = expression.component(1).evaluate(parameterValues);
    REQUIRE((componentResults[0] - 2.0) == Zero());
    REQUIRE((componentResults[1] - 3.0) == Zero());
    REQUIRE((componentResults[2] - 4.0) == Zero());

    double value = expression.z().evaluate(0.5);
    REQUIRE((value - 4.5) == Zero());
}

TEST_CASE("Transformation") {
    Frame3d frame;
    frame = frame.translatedBy(Vector3d(1, 1, 1));
    frame = frame.rotatedAbout(frame.zAxis(), M_PI / 4);

    Parameter1d t;
    ParametricExpression<Point3d, double> linear = Point3d::origin() + Vector3d(1.0, 1.0, 1.0) * t;
    ParametricExpression<Point3d, double> product = linear.toGlobalFrom(frame);
    ParametricExpression<Point3d, double> quotient = linear.toLocalIn(frame);

    std::vector<double> parameterValues(5);
    std::vector<Point3d> expectedProductValues(5);
    std::vector<Point3d> expectedQuotientValues(5);
    for (int i = 0; i < 5; ++i) {
        parameterValues[i] = i / 4.0;
        Point3d expectedValue =  Point3d::origin() + Vector3d(1.0, 1.0, 1.0) * parameterValues[i];
        expectedProductValues[i] = expectedValue.toGlobalFrom(frame);
        expectedQuotientValues[i] = expectedValue.toLocalIn(frame);
    }
    std::vector<Point3d> productValues = product.evaluate(parameterValues);
    std::vector<Point3d> quotientValues = quotient.evaluate(parameterValues);
    for (int i = 0; i < 5; ++i) {
        REQUIRE((productValues[i] - expectedProductValues[i]).isZero());
        REQUIRE((quotientValues[i] - expectedQuotientValues[i]).isZero());
    }
}

TEST_CASE("Concatenation") {
    Parameter1d t;
    ParametricExpression<double, double> x = t;
    ParametricExpression<double, double> y = ParametricExpression<double, double>::constant(3.0);
    ParametricExpression<double, double> z = t.squared();
    ParametricExpression<Point3d, double> concatenated = (
        ParametricExpression<Point3d, double>::fromComponents(x, y, z)
    );
    REQUIRE((concatenated.evaluate(2.0) - Point3d(2.0, 3.0, 4.0)).isZero());
}

TEST_CASE("Arccosine") {
    Parameter1d t;
    ParametricExpression<double, double> expression = acos(t);
    Interval bounds;
    bounds = expression.evaluate(Interval(-1, 0));
    REQUIRE((bounds.lowerBound() - M_PI / 2) == Zero());
    REQUIRE((bounds.upperBound() - M_PI) == Zero());
    bounds = expression.evaluate(Interval(0.5, 1.5));
    REQUIRE(bounds.lowerBound() == Zero());
    REQUIRE((bounds.upperBound() - M_PI / 3) == Zero());
    bounds = expression.evaluate(Interval(1 + 1e-14, 1 + 1e-10));
    REQUIRE(bounds.lowerBound() == Zero());
    REQUIRE(bounds.upperBound() == Zero());

    testJacobian(expression, -0.5);
    testJacobian(expression, 0.0);
    testJacobian(expression, 0.5);

    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<double, Point2d> expression2 = acos(u - v);
    testJacobian(expression2, Point2d(0.5, 0));
    testJacobian(expression2, Point2d(0, 0.25));
    testJacobian(expression2, Point2d(-0.5, 0));
    testJacobian(expression2, Point2d(0, -0.25));
    testJacobian(expression2, Point2d(0, 0));
}

TEST_CASE("Arcsine") {
    Parameter1d t;
    ParametricExpression<double, double> expression = asin(t);
    Interval bounds;
    bounds = expression.evaluate(Interval(-1, 0));
    REQUIRE((bounds.lowerBound() + M_PI / 2) == Zero());
    REQUIRE(bounds.upperBound() == Zero());
    bounds = expression.evaluate(Interval(0.5, 1.5));
    REQUIRE((bounds.lowerBound() - M_PI / 6) == Zero());
    REQUIRE((bounds.upperBound() - M_PI / 2) == Zero());
    bounds = expression.evaluate(Interval(1 + 1e-14, 1 + 1e-10));
    REQUIRE((bounds.lowerBound() - M_PI / 2) == Zero());
    REQUIRE((bounds.upperBound() - M_PI / 2) == Zero());
}

TEST_CASE("Normal vector") {
    Parameter1d t;
    ParametricExpression<Point2d, double> expression = (
        Point2d(1.0, 1.0) +
        2.0 * ParametricExpression<Vector2d, double>::fromComponents(cos(t), sin(t))
    );
    REQUIRE((expression.evaluate(-M_PI / 2) - Point2d(1, -1)).isZero());
    REQUIRE((expression.evaluate(0) - Point2d(3, 1)).isZero());
    REQUIRE((expression.evaluate(M_PI / 2) - Point2d(1, 3)).isZero());

    ParametricExpression<Vector2d, double> normalVector =
        expression.derivative().normalized().derivative().normalized();
    std::vector<double> parameterValues(5);
    parameterValues[0] = -M_PI / 2;
    parameterValues[1] = -M_PI / 4;
    parameterValues[2] = 0.0;
    parameterValues[3] = M_PI / 4;
    parameterValues[4] = M_PI / 2;

    std::vector<Point2d> expressionValues = expression.evaluate(parameterValues);
    std::vector<Vector2d> normalValues = normalVector.evaluate(parameterValues);
    for (unsigned i = 0; i < expressionValues.size(); ++i) {
        REQUIRE((expressionValues[i] + 2 * normalValues[i] - Point2d(1, 1)).isZero());
    }
}

TEST_CASE("Deduplication") {
    Parameter1d t;
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    {
        ParametricExpression<Point3d, double> constant1 =
            ParametricExpression<Point3d, double>::constant(Point3d(1, 2, 3));
        ParametricExpression<Point3d, double> constant2 =
            ParametricExpression<Point3d, double>::constant(Point3d(1, 2, 3));
        ParametricExpression<Point3d, double> constant3 =
            ParametricExpression<Point3d, double>::constant(Point3d(1, 2, 4));
        ParametricExpression<Point3d, Point2d> constant4 =
            ParametricExpression<Point3d, Point2d>::constant(Point3d(1, 2, 3));

        REQUIRE(constant1.implementation()->isDuplicateOf(constant2.implementation()));
        REQUIRE_FALSE(constant1.implementation()->isDuplicateOf(constant3.implementation()));
        REQUIRE_FALSE(constant1.implementation()->isDuplicateOf(constant4.implementation()));
    }

    {
        ParametricExpression<double, double> expression1 = t.squared() + 2.0 * t;
        ParametricExpression<double, double> expression2 = t * 2.0 + t.squared();

        REQUIRE(expression1.implementation()->isDuplicateOf(expression2.implementation()));
    }

    {
        ParametricExpression<double, Point2d> expression1 = cos(u.squared() + v.squared());
        ParametricExpression<double, Point2d> expression2 = cos(v.squared() + u.squared());

        REQUIRE(expression1.implementation()->isDuplicateOf(expression2.implementation()));
    }

    {
        ParametricExpression<double, Point2d> expression1 = u.squared();
        ParametricExpression<double, Point2d> expression2 = v.squared();

        REQUIRE_FALSE(expression1.implementation()->isDuplicateOf(expression2.implementation()));
    }

    {
        ParametricExpression<double, double> expression1 = sin(t);
        ParametricExpression<double, double> expression2 = expression1;

        REQUIRE(expression1.implementation()->isDuplicateOf(expression1.implementation()));
        REQUIRE(expression1.implementation()->isDuplicateOf(expression2.implementation()));
    }

    {
        ParametricExpression<double, Point2d> expression1 = sin(sqrt(u));
        ParametricExpression<double, Point2d> expression2 = sin(sqrt(u));

        REQUIRE(expression1.implementation()->isDuplicateOf(expression2.implementation()));
    }
}

TEST_CASE("Deduplicated output") {
    Parameter1d t;
    ParametricExpression<double, double> expression = t.squared() + sin(t.squared());
    std::cout << expression << std::endl;
}

TEST_CASE("Ellipse Jacobian") {
    Parameter1d t;
    ParametricExpression<Vector2d, double> ellipseExpression =
        Vector2d(3, 1) * cos(t) + Vector2d(1, 3) * sin(t);
    testJacobian(ellipseExpression, 0.0);
    testJacobian(ellipseExpression, M_PI / 4);
    testJacobian(ellipseExpression, M_PI / 2);
    testJacobian(ellipseExpression, 3 * M_PI / 4);
}

TEST_CASE("Ellipsoid Jacobian") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<Vector3d, Point2d> ellipsoidExpression = sin(v) * Vector3d(1, 1, 3) +
        cos(v) * (sin(u) * Vector3d(1, 3, 1) + cos(u) * Vector3d(3, 1, 1));
    testJacobian(ellipsoidExpression, Point2d(0, 0));
    testJacobian(ellipsoidExpression, Point2d(M_PI / 4, 0));
    testJacobian(ellipsoidExpression, Point2d(0, M_PI / 4));
    testJacobian(ellipsoidExpression, Point2d(M_PI / 4, M_PI / 4));
    testJacobian(ellipsoidExpression, Point2d(M_PI / 2, 0));
    testJacobian(ellipsoidExpression, Point2d(0, 3 * M_PI / 4));
}

TEST_CASE("Squiggle Jacobians") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<double, Point2d> scalar = scalarSquiggle();
    ParametricExpression<Vector3d, Point2d> vector = vectorSquiggle();
    std::vector<Point2d> parameterValues = squiggleParameterValues();

    for (unsigned i = 0; i < parameterValues.size(); ++i) {
        testJacobian(scalar, parameterValues[i]);
        testJacobian(vector, parameterValues[i]);

        testJacobian(acos(scalar / 2.0), parameterValues[i]);
        testJacobian(asin(scalar / 2.0), parameterValues[i]);
        testJacobian(cos(scalar), parameterValues[i]);
        testJacobian(vector.cross(vector + Vector3d(0, 0, 1)), parameterValues[i]);
        testJacobian(vector - u * Vector3d(0, 0, 1), parameterValues[i]);
        testJacobian(vector.dot(vector + Vector3d(0, 0, 1)), parameterValues[i]);
        testJacobian(exp(scalar), parameterValues[i]);
        testJacobian(log(scalar + 2.0), parameterValues[i]);
        testJacobian(vector.rotatedAbout(Vector3d::unitX(), M_PI / 4), parameterValues[i]);
        testJacobian(-vector, parameterValues[i]);
        testJacobian(vector.normalized(), parameterValues[i]);
        testJacobian(vector.norm(), parameterValues[i]);
        testJacobian(v, parameterValues[i]);
        testJacobian(pow(2.0, scalar), parameterValues[i]);
        testJacobian(pow(scalar + 2.0, 3.0), parameterValues[i]);
        testJacobian(vector * (scalar + 1.0), parameterValues[i]);
        testJacobian(vector / (scalar + 2.0), parameterValues[i]);
        testJacobian(3.0 * vector, parameterValues[i]);
        testJacobian(sin(scalar), parameterValues[i]);
        testJacobian(vector.squaredNorm(), parameterValues[i]);
        testJacobian(sqrt(scalar + 2.0), parameterValues[i]);
        testJacobian(vector + u * Vector3d(0, 0, 1), parameterValues[i]);
        testJacobian(tan(scalar), parameterValues[i]);
        testJacobian(vector + Vector3d(1, 2, 3), parameterValues[i]);

        // Composition?
        // Concatenation?
    }
}

TEST_CASE("Dot product with constant") {
    Parameter1d t;
    ParametricExpression<Vector3d, double> line = (
        Vector3d(1.0, 1.0, 1.0) + Vector3d(1.0, 1.0, 1.0) * t
    );
    ParametricExpression<double, double> dotProduct = line.dot(Vector3d(0, 1, 0));
    REQUIRE((dotProduct.evaluate(0.0) - 1.0) == Zero());
    REQUIRE((dotProduct.evaluate(1.0) - 2.0) == Zero());
}

TEST_CASE("Cross product with constant") {
    Parameter1d t;
    ParametricExpression<Vector3d, double> line = (
        Vector3d(1.0, 1.0, 1.0) + Vector3d(1.0, 1.0, 1.0) * t
    );
    ParametricExpression<Vector3d, double> crossProduct = line.cross(Vector3d(0.0, 1.0, 0.0));
    REQUIRE((crossProduct.evaluate(0.0) - Vector3d(-1.0, 0.0, 1.0)).isZero());
    REQUIRE((crossProduct.evaluate(1.0) - Vector3d(-2.0, 0.0, 2.0)).isZero());
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

//    functions[1] = x.squared() - 1;
//    domains[1] = Interval(-2, 2);
//    expected_function_zeros[1] = RowVector2d(-1, 1);
//    expected_derivative_zeros[1] = RowVectorXd::Constant(1, 0.0);
//    expected_second_derivative_zeros[1] = RowVectorXd();

//    functions[2] = x * x * x - 4 * x * x + 5 * x - 2;
//    domains[2] = Interval(0, 3);
//    expected_function_zeros[2] = RowVector2d(1, 2);
//    expected_derivative_zeros[2] = RowVector2d(1, 5.0 / 3.0);
//    expected_second_derivative_zeros[2] = RowVectorXd::Constant(1, 4.0 / 3.0);

//    functions[3] = sin(x).squared() + 2 * sin(x) + 1;
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
//        REQUIRE(function_values.isZero());
//        REQUIRE(derivative_values.isZero());
//        REQUIRE(second_derivative_values.isZero());
//        
//        RowVectorXd function_zeros;
//        boost::timer timer;
//        for (int j = 0; j < 100; ++j) {function_zeros = function.roots(domains[i]);}
//        double elapsed = timer.elapsed();
//        RowVectorXd derivative_zeros = derivative.roots(domains[i]);
//        RowVectorXd second_derivative_zeros = second_derivative.roots(domains[i]);
//            
//        REQUIRE(function_zeros.isApprox(expected_function_zeros[i]));
//        REQUIRE(derivative_zeros.isApprox(expected_derivative_zeros[i]));
//        REQUIRE(second_derivative_zeros.isApprox(expected_second_derivative_zeros[i]));
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
//    REQUIRE(root.size() == 1);
//    REQUIRE((root.value() - 0.052786404500042038) == Zero());
//}
