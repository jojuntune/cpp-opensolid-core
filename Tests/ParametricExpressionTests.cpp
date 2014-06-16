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

#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/Evaluator.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <boost/timer.hpp>
#include <catch/catch.hpp>

#include <vector>

using namespace opensolid;

inline
Matrix1d
scalarMatrix(double value) {
    Matrix1d result;
    result.value() = value;
    return result;
}

inline
ColumnMatrix2d
columnMatrix(double x, double y) {
    ColumnMatrix2d result;
    result(0) = x;
    result(1) = y;
    return result;
}

inline
ColumnMatrix3d
columnMatrix(double x, double y, double z) {
    ColumnMatrix3d result;
    result(0) = x;
    result(1) = y;
    result(2) = z;
    return result;
}

inline
IntervalMatrix1d
scalarMatrix(Interval value) {
    IntervalMatrix1d result;
    result.value() = value;
    return result;
}

inline
IntervalColumnMatrix2d
columnMatrix(Interval x, Interval y) {
    IntervalColumnMatrix2d result;
    result(0) = x;
    result(1) = y;
    return result;
}

inline
IntervalColumnMatrix3d
columnMatrix(Interval x, Interval y, Interval z) {
    IntervalColumnMatrix3d result;
    result(0) = x;
    result(1) = y;
    result(2) = z;
    return result;
}

ParametricExpression<1, 2>
scalarSquiggle() {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    return sin(2 * M_PI * u) + cos(2 * M_PI * v);
}

ParametricExpression<3, 2>
vectorSquiggle() {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    return ParametricExpression<3, 2>::fromComponents(u, v, scalarSquiggle());
}

std::vector<ColumnMatrix2d>
squiggleParameterValues() {
    std::vector<ColumnMatrix2d> results(25);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            results[i * 5 + j] = columnMatrix(i / 5.0 + 0.1, j / 5.0 + 0.1);
        }
    }
    return results;
}

template <int iNumDimensions, int iNumParameters>
void testJacobian(
    const ParametricExpression<iNumDimensions, iNumParameters>& expression,
    const Matrix<double, iNumParameters, 1>& parameterValues
) {
    Matrix<double, iNumDimensions, iNumParameters> jacobian = expression.jacobian(parameterValues);
    Matrix<double, iNumDimensions, iNumParameters> expectedJacobian;;
    for (int j = 0; j < iNumParameters; ++j) {
        Matrix<double, iNumDimensions, 1> partialDerivative =
            expression.derivative(j).evaluate(parameterValues);
        for (int i = 0; i < iNumDimensions; ++i) {
            expectedJacobian(i, j) = partialDerivative(i);
        }
    }
    REQUIRE((jacobian - expectedJacobian).isZero());
    if (!(jacobian - expectedJacobian).isZero()) {
        std::cout << "ParametricExpression:" << std::endl;
        std::cout << expression << std::endl;
        std::cout << "Jacobian ";
        std::cout << "(parameter values " << parameterValues << ")";
        std::cout << ":" << std::endl;
        std::cout << jacobian << std::endl;
        std::cout << "Expected:" << std::endl;
        std::cout << expectedJacobian << std::endl;
        std::cout << "Difference:" << std::endl;
        std::cout << jacobian - expectedJacobian << std::endl;
    }
    for (int j = 0; j < iNumParameters; ++j) {
        Matrix<double, iNumParameters, 2> shiftedParameterValues;
        shiftedParameterValues.column(0) = parameterValues;
        shiftedParameterValues.column(1) = parameterValues;
        shiftedParameterValues(j, 0) -= 1e-6 / 2;
        shiftedParameterValues(j, 1) += 1e-6 / 2;
        Matrix<double, iNumDimensions, 2> shiftedValues =
            expression.evaluate(shiftedParameterValues);
        Matrix<double, iNumDimensions, 1> numericalDerivative = shiftedValues.column(1);
        numericalDerivative = (shiftedValues.column(1) - shiftedValues.column(0)) / 1e-6;
        REQUIRE((numericalDerivative - jacobian.column(j)).isZero(1e-3));
        if (!(numericalDerivative - jacobian.column(j)).isZero(1e-3)) {
            std::cout << "ParametricExpression:" << std::endl;
            std::cout << expression << std::endl;
            std::cout << "Numerical derivative " << j << ": " << std::endl;
            std::cout << numericalDerivative.transpose() << std::endl;
            std::cout << "Jacobian derivative: " << std::endl;
            std::cout << jacobian.column(j).transpose() << std::endl;
        }
    }
}

TEST_CASE("Constant") {
    ParametricExpression<1, 1> expression = ParametricExpression<1, 1>::constant(3.0);
    REQUIRE(expression.implementation()->isConstantExpression());
    REQUIRE((expression.evaluate(0.0).value() - 3) == Zero());
}

TEST_CASE("Arithmetic") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<1, 2> expression = 2.0 + u * 1.0 - 1.0 * v;
    
    REQUIRE((expression.evaluate(0, 0).value() - 2) == Zero());
    REQUIRE((expression.evaluate(1, 0).value() - 3) == Zero());
    REQUIRE((expression.evaluate(1, 1).value() - 2) == Zero());
    REQUIRE((expression.evaluate(0, 1).value() - 1) == Zero());
    REQUIRE((expression.derivative(u).evaluate(0, 0).value() - 1) == Zero());
    REQUIRE((expression.derivative(v).evaluate(0, 0).value() + 1) == Zero());
    
    ParametricExpression<1, 2> negated = -expression;
    
    REQUIRE((negated.evaluate(0, 0).value() + 2) == Zero());
    REQUIRE((negated.evaluate(1, 0).value() + 3) == Zero());
    REQUIRE((negated.evaluate(1, 1).value() + 2) == Zero());
    REQUIRE((negated.evaluate(0, 1).value() + 1) == Zero());
    REQUIRE((negated.derivative(u).evaluate(0, 0).value() + 1) == Zero());
    REQUIRE((negated.derivative(v).evaluate(0, 0).value() - 1) == Zero());
}

TEST_CASE("Multiplication") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<1, 2> expression = 1.0 + u / 1.0 * v / 1.0;

    REQUIRE((expression.evaluate(0, 0).value() - 1) == Zero());
    REQUIRE((expression.evaluate(1, 0).value() - 1) == Zero());
    REQUIRE((expression.evaluate(1, 1).value() - 2) == Zero());
    REQUIRE((expression.evaluate(0, 1).value() - 1) == Zero());

    ParametricExpression<1, 2> uDerivative = expression.derivative(u);
    
    REQUIRE(uDerivative.evaluate(0, 0).value() == Zero());
    REQUIRE(uDerivative.evaluate(1, 0).value() == Zero());
    REQUIRE((uDerivative.evaluate(1, 1).value() - 1) == Zero());
    REQUIRE((uDerivative.evaluate(0, 1).value() - 1) == Zero());

    ParametricExpression<1, 2> vDerivative = expression.derivative(v);
    
    REQUIRE(vDerivative.evaluate(0, 0).value() == Zero());
    REQUIRE((vDerivative.evaluate(1, 0).value() - 1) == Zero());
    REQUIRE((vDerivative.evaluate(1, 1).value() - 1) == Zero());
    REQUIRE(vDerivative.evaluate(0, 1).value() == Zero());
}

TEST_CASE("Square") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<1, 2> expression = u.squared() * 1.0 + v.squared() * 1.0;
    REQUIRE((expression.evaluate(1, 2).value() - 5) == Zero());
    ParametricExpression<1, 2> uDerivative = expression.derivative(u);
    REQUIRE((uDerivative.evaluate(3, 4).value() - 6) == Zero());
    ParametricExpression<1, 2> vSecondDerivative = expression.derivative(v).derivative(v);
    REQUIRE((vSecondDerivative.evaluate(5, 6).value() - 2) == Zero());
}

TEST_CASE("Norm") {
    Parameter1d t;
    ParametricExpression<2, 1> arc =
        3 * (cos(t) * columnMatrix(1, 0) + columnMatrix(0, 1) * sin(t));
    ColumnMatrix2d evaluated = arc.normalized().evaluate(M_PI / 4);
    ColumnMatrix2d expected = columnMatrix(1 / sqrt(2.0), 1 / sqrt(2.0));
    REQUIRE((evaluated - expected).isZero());
}

TEST_CASE("Conversion") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    {
        ParametricExpression<1, 2> expression = u * v;
        REQUIRE((expression.evaluate(2, 3).value() - 6) == Zero());
    }
    {
        ParametricExpression<1, 1> expression = ParametricExpression<1, 1>::constant(2.0);

        RowMatrix3d parameterValues;
        parameterValues(0) = 1;
        parameterValues(1) = 2;
        parameterValues(2) = 3;

        REQUIRE(expression.evaluate(parameterValues) == RowMatrix3d::constant(2.0));
    }
}

TEST_CASE("Sine") {
    Parameter1d t;
    ParametricExpression<1, 1> expression = sin(t);

    std::vector<double> parameterValues(4);
    parameterValues[0] = 0;
    parameterValues[1] = M_PI / 2;
    parameterValues[2] = M_PI;
    parameterValues[3] = 3 * M_PI / 2;
    std::vector<Matrix1d> resultValues = expression.evaluate(parameterValues);
    REQUIRE(resultValues[0].value() == Zero());
    REQUIRE((resultValues[1].value() - 1) == Zero());
    REQUIRE(resultValues[2].value() == Zero());
    REQUIRE((resultValues[3].value() + 1) == Zero());

    std::vector<Interval> parameterBounds(4);
    parameterBounds[0] = Interval(0, M_PI / 2);
    parameterBounds[1] = Interval(M_PI / 2, M_PI);
    parameterBounds[2] = Interval(M_PI, 3 * M_PI / 2);
    parameterBounds[3] = Interval(0, 2 * M_PI);
    std::vector<IntervalMatrix1d> resultBounds = expression.evaluate(parameterBounds);
    REQUIRE(resultBounds[0].value().lowerBound() == Zero());
    REQUIRE((resultBounds[0].value().upperBound() - 1) == Zero());
    REQUIRE(resultBounds[1].value().lowerBound() == Zero());
    REQUIRE((resultBounds[1].value().upperBound() - 1) == Zero());
    REQUIRE((resultBounds[2].value().lowerBound() + 1) == Zero());
    REQUIRE(resultBounds[2].value().upperBound() == Zero());
    REQUIRE((resultBounds[3].value().lowerBound() + 1) == Zero());
    REQUIRE((resultBounds[3].value().upperBound() - 1) == Zero());
}

TEST_CASE("Cosine") {
    Parameter1d t;
    ParametricExpression<1, 1> expression = cos(t);

    std::vector<double> parameterValues(4);
    parameterValues[0] = 0;
    parameterValues[1] = M_PI / 2;
    parameterValues[2] = M_PI;
    parameterValues[3] = 3 * M_PI / 2;
    std::vector<Matrix1d> resultValues = expression.evaluate(parameterValues);
    REQUIRE((resultValues[0].value() - 1) == Zero());
    REQUIRE(resultValues[1].value() == Zero());
    REQUIRE((resultValues[2].value() + 1) == Zero());
    REQUIRE(resultValues[3].value() == Zero());

    std::vector<Interval> parameterBounds(4);
    parameterBounds[0] = Interval(0, M_PI / 2);
    parameterBounds[1] = Interval(M_PI / 2, M_PI);
    parameterBounds[2] = Interval(M_PI, 3 * M_PI / 2);
    parameterBounds[3] = Interval(0, 2 * M_PI);
    std::vector<IntervalMatrix1d> resultBounds = expression.evaluate(parameterBounds);
    REQUIRE(resultBounds[0].value().lowerBound() == Zero());
    REQUIRE((resultBounds[0].value().upperBound() - 1) == Zero());
    REQUIRE((resultBounds[1].value().lowerBound() + 1) == Zero());
    REQUIRE(resultBounds[1].value().upperBound() == Zero());
    REQUIRE((resultBounds[2].value().lowerBound() + 1) == Zero());
    REQUIRE(resultBounds[2].value().upperBound() == Zero());
    REQUIRE((resultBounds[3].value().lowerBound() + 1) == Zero());
    REQUIRE((resultBounds[3].value().upperBound() - 1) == Zero());
}

TEST_CASE("Component") {
    Parameter1d t;
    ParametricExpression<3, 1> expression =
        columnMatrix(1, 2, 3) + t * columnMatrix(1, 2, 3);
    
    RowMatrix3d parameterValues;
    parameterValues(0) = 0.0;
    parameterValues(1) = 0.5;
    parameterValues(2) = 1.0;

    RowMatrix3d results = expression.component(1).evaluate(parameterValues);
    std::cout << std::endl << "First: " << results << std::endl;
    REQUIRE((results(0) - 2.0) == Zero());
    REQUIRE((results(1) - 3.0) == Zero());
    REQUIRE((results(2) - 4.0) == Zero());

    results = expression.evaluate(parameterValues).row(1);
    std::cout << "Temp:" << std::endl << expression.evaluate(parameterValues) << std::endl;
    std::cout << "Second: " << results << std::endl;
    REQUIRE((results(0) - 2.0) == Zero());
    REQUIRE((results(1) - 3.0) == Zero());
    REQUIRE((results(2) - 4.0) == Zero());

    double value = expression.z().evaluate(0.5).value();
    REQUIRE((value - 4.5) == Zero());
}

TEST_CASE("Transformation") {
    CoordinateSystem3d coordinateSystem = CoordinateSystem3d::xyz();
    coordinateSystem = coordinateSystem.translatedBy(Vector3d(1, 1, 1));
    coordinateSystem = coordinateSystem.rotatedAbout(coordinateSystem.zAxis(), M_PI / 4);

    Parameter1d t;
    ParametricExpression<3, 1> linear = ColumnMatrix3d::ones() * t;
    ParametricExpression<3, 1> product = coordinateSystem.basisMatrix() * linear +
        coordinateSystem.originPoint().components();
    ParametricExpression<3, 1> quotient = coordinateSystem.inverseMatrix() *
        (linear - coordinateSystem.originPoint().components());

    std::vector<double> parameterValues(5);
    std::vector<ColumnMatrix3d> expectedProductValues(5);
    std::vector<ColumnMatrix3d> expectedQuotientValues(5);
    for (int i = 0; i < 5; ++i) {
        parameterValues[i] = i / 4.0;
        expectedProductValues[i] = parameterValues[i] * columnMatrix(0, sqrt(2.0), 1) +
            columnMatrix(1, 1, 1);
        expectedQuotientValues[i] = parameterValues[i] * columnMatrix(sqrt(2.0), 0, 1) +
            columnMatrix(-sqrt(2.0), 0, -1);
    }
    std::vector<ColumnMatrix3d> productValues = product.evaluate(parameterValues);
    std::vector<ColumnMatrix3d> quotientValues = quotient.evaluate(parameterValues);
    for (int i = 0; i < 5; ++i) {
        REQUIRE((productValues[i] - expectedProductValues[i]).isZero());
        REQUIRE((quotientValues[i] - expectedQuotientValues[i]).isZero());
    }
}

TEST_CASE("Concatenation") {
    Parameter1d t;
    ParametricExpression<1, 1> x = t;
    ParametricExpression<1, 1> y = ParametricExpression<1, 1>::constant(3.0);
    ParametricExpression<1, 1> z = t.squared();
    ParametricExpression<3, 1> concatenated =
        ParametricExpression<3, 1>::fromComponents(x, y, z);
    REQUIRE((concatenated.evaluate(2.0) - columnMatrix(2.0, 3.0, 4.0)).isZero());
}

TEST_CASE("Arccosine") {
    Parameter1d t;
    ParametricExpression<1, 1> expression = acos(t);
    Interval bounds;
    bounds = expression.evaluate(Interval(-1, 0)).value();
    REQUIRE((bounds.lowerBound() - M_PI / 2) == Zero());
    REQUIRE((bounds.upperBound() - M_PI) == Zero());
    bounds = expression.evaluate(Interval(0.5, 1.5)).value();
    REQUIRE(bounds.lowerBound() == Zero());
    REQUIRE((bounds.upperBound() - M_PI / 3) == Zero());
    bounds = expression.evaluate(Interval(1 + 1e-14, 1 + 1e-10)).value();
    REQUIRE(bounds.lowerBound() == Zero());
    REQUIRE(bounds.upperBound() == Zero());

    testJacobian(expression, scalarMatrix(-0.5));
    testJacobian(expression, scalarMatrix(0.0));
    testJacobian(expression, scalarMatrix(0.5));

    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<1, 2> expression2 = acos(u - v);
    testJacobian(expression2, columnMatrix(0.5, 0));
    testJacobian(expression2, columnMatrix(0, 0.25));
    testJacobian(expression2, columnMatrix(-0.5, 0));
    testJacobian(expression2, columnMatrix(0, -0.25));
    testJacobian(expression2, columnMatrix(0, 0));
}

TEST_CASE("Arcsine") {
    Parameter1d t;
    ParametricExpression<1,1 > expression = asin(t);
    Interval bounds;
    bounds = expression.evaluate(Interval(-1, 0)).value();
    REQUIRE((bounds.lowerBound() + M_PI / 2) == Zero());
    REQUIRE(bounds.upperBound() == Zero());
    bounds = expression.evaluate(Interval(0.5, 1.5)).value();
    REQUIRE((bounds.lowerBound() - M_PI / 6) == Zero());
    REQUIRE((bounds.upperBound() - M_PI / 2) == Zero());
    bounds = expression.evaluate(Interval(1 + 1e-14, 1 + 1e-10)).value();
    REQUIRE((bounds.lowerBound() - M_PI / 2) == Zero());
    REQUIRE((bounds.upperBound() - M_PI / 2) == Zero());
}

TEST_CASE("Normal vector") {
    Parameter1d t;
    ParametricExpression<2, 1> expression =
        columnMatrix(1, 1) + 2 * ParametricExpression<2, 1>::fromComponents(cos(t), sin(t));
    REQUIRE((expression.evaluate(-M_PI / 2) - columnMatrix(1, -1)).isZero());
    REQUIRE((expression.evaluate(0) - columnMatrix(3, 1)).isZero());
    REQUIRE((expression.evaluate(M_PI / 2) - columnMatrix(1, 3)).isZero());

    ParametricExpression<2, 1> normalVector =
        expression.derivative().normalized().derivative().normalized();
    std::vector<double> parameterValues(5);
    parameterValues[0] = -M_PI / 2;
    parameterValues[1] = -M_PI / 4;
    parameterValues[2] = 0.0;
    parameterValues[3] = M_PI / 4;
    parameterValues[4] = M_PI / 2;

    std::vector<ColumnMatrix2d> expressionValues = expression.evaluate(parameterValues);
    std::vector<ColumnMatrix2d> normalValues = normalVector.evaluate(parameterValues);
    for (unsigned i = 0; i < expressionValues.size(); ++i) {
        REQUIRE((expressionValues[i] + 2 * normalValues[i] - columnMatrix(1, 1)).isZero());
    }
}

TEST_CASE("Deduplication") {
    Parameter1d t;
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    {
        ParametricExpression<3, 1> constant1 =
            ParametricExpression<3, 1>::constant(columnMatrix(1, 2, 3));
        ParametricExpression<3, 1> constant2 =
            ParametricExpression<3, 1>::constant(columnMatrix(1, 2, 3));
        ParametricExpression<3, 1> constant3 =
            ParametricExpression<3, 1>::constant(columnMatrix(1, 2, 4));
        ParametricExpression<3, 2> constant4 =
            ParametricExpression<3, 2>::constant(columnMatrix(1, 2, 3));

        REQUIRE(constant1.implementation()->isDuplicateOf(constant2.implementation()));
        REQUIRE_FALSE(constant1.implementation()->isDuplicateOf(constant3.implementation()));
        REQUIRE_FALSE(constant1.implementation()->isDuplicateOf(constant4.implementation()));
    }

    {
        ParametricExpression<1, 1> expression1 = t.squared() + 2 * t;
        ParametricExpression<1, 1> expression2 = t * 2 + t.squared();

        REQUIRE(expression1.implementation()->isDuplicateOf(expression2.implementation()));
    }

    {
        ParametricExpression<1, 2> expression1 = cos(u.squared() + v.squared());
        ParametricExpression<1, 2> expression2 = cos(v.squared() + u.squared());

        REQUIRE(expression1.implementation()->isDuplicateOf(expression2.implementation()));
    }

    {
        ParametricExpression<1, 2> expression1 = u.squared();
        ParametricExpression<1, 2> expression2 = v.squared();

        REQUIRE_FALSE(expression1.implementation()->isDuplicateOf(expression2.implementation()));
    }

    {
        ParametricExpression<1, 1> expression1 = sin(t);
        ParametricExpression<1, 1> expression2 = expression1;

        REQUIRE(expression1.implementation()->isDuplicateOf(expression1.implementation()));
        REQUIRE(expression1.implementation()->isDuplicateOf(expression2.implementation()));
    }

    {
        ParametricExpression<1, 2> expression1 = sin(sqrt(u));
        ParametricExpression<1, 2> expression2 = sin(sqrt(u));

        REQUIRE(expression1.implementation()->isDuplicateOf(expression2.implementation()));
    }
}

TEST_CASE("Deduplicated output") {
    Parameter1d t;
    ParametricExpression<1, 1> expression = t.squared() + sin(t.squared());
    std::cout << expression << std::endl;
}

TEST_CASE("Evaluator double") {
    Parameter1d t;
    ParametricExpression<1, 1> expression = t.squared();
    detail::Evaluator evaluator;

    RowMatrix3d parameterValues;
    parameterValues(0) = 1.0;
    parameterValues(1) = 2.0;
    parameterValues(2) = 3.0;

    ConstMatrixViewXd parameterMap(parameterValues.data(), 1, 3, 1);
    ConstMatrixViewXd results1 = evaluator.evaluate(expression.implementation(), parameterMap);
    ConstMatrixViewXd results2 = evaluator.evaluate(expression.implementation(), parameterMap);
    REQUIRE(results1.data() == results2.data());
    ConstMatrixViewXd results3 = evaluator.evaluate(expression.implementation(), parameterMap);
    REQUIRE(results1.data() == results3.data());
}

TEST_CASE("Evaluator interval") {
    Parameter1d t;
    ParametricExpression<1, 1> expression = t.squared();
    detail::Evaluator evaluator;

    IntervalRowMatrix3d parameterValues;
    parameterValues(0) = Interval(1, 2);
    parameterValues(1) = Interval(3, 4);
    parameterValues(2) = Interval(5, 6);

    ConstIntervalMatrixViewXd parameterMap(parameterValues.data(), 1, 3, 1);
    ConstIntervalMatrixViewXd results1 =
        evaluator.evaluate(expression.implementation(), parameterMap);
    ConstIntervalMatrixViewXd results2 =
        evaluator.evaluate(expression.implementation(), parameterMap);
    REQUIRE(results1.data() == results2.data());
    ConstIntervalMatrixViewXd results3 =
        evaluator.evaluate(expression.implementation(), parameterMap);
    REQUIRE(results1.data() == results3.data());
}

TEST_CASE("Ellipse Jacobian") {
    Parameter1d t;
    ParametricExpression<2, 1> ellipseExpression =
        columnMatrix(3, 1) * cos(t) + columnMatrix(1, 3) * sin(t);
    testJacobian(ellipseExpression, scalarMatrix(0.0));
    testJacobian(ellipseExpression, scalarMatrix(M_PI / 4));
    testJacobian(ellipseExpression, scalarMatrix(M_PI / 2));
    testJacobian(ellipseExpression, scalarMatrix(3 * M_PI / 4));
}

TEST_CASE("Ellipsoid Jacobian") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<3, 2> ellipsoidExpression = sin(v) * columnMatrix(1, 1, 3) +
        cos(v) * (sin(u) * columnMatrix(1, 3, 1) + cos(u) * columnMatrix(3, 1, 1));
    testJacobian(ellipsoidExpression, columnMatrix(0, 0));
    testJacobian(ellipsoidExpression, columnMatrix(M_PI / 4, 0));
    testJacobian(ellipsoidExpression, columnMatrix(0, M_PI / 4));
    testJacobian(ellipsoidExpression, columnMatrix(M_PI / 4, M_PI / 4));
    testJacobian(ellipsoidExpression, columnMatrix(M_PI / 2, 0));
    testJacobian(ellipsoidExpression, columnMatrix(0, 3 * M_PI / 4));
}

TEST_CASE("Squiggle Jacobians") {
    Parameter2d u = Parameter2d(0);
    Parameter2d v = Parameter2d(1);
    ParametricExpression<1, 2> scalar = scalarSquiggle();
    ParametricExpression<3, 2> vector = vectorSquiggle();
    std::vector<ColumnMatrix2d> parameterValues = squiggleParameterValues();
    Matrix3d transformationMatrix = Rotation3d(Axis3d::x(), M_PI / 4).transformationMatrix();

    for (unsigned i = 0; i < parameterValues.size(); ++i) {
        testJacobian(scalar, parameterValues[i]);
        testJacobian(vector, parameterValues[i]);

        testJacobian(acos(scalar / 2), parameterValues[i]);
        testJacobian(asin(scalar / 2), parameterValues[i]);
        testJacobian(vector.components<2>(1), parameterValues[i]);
        testJacobian(cos(scalar), parameterValues[i]);
        testJacobian(vector.cross(vector + columnMatrix(0, 0, 1)), parameterValues[i]);
        testJacobian(vector - u * columnMatrix(0, 0, 1), parameterValues[i]);
        testJacobian(vector.dot(vector + columnMatrix(0, 0, 1)), parameterValues[i]);
        testJacobian(exp(scalar), parameterValues[i]);
        testJacobian(log(scalar + 2), parameterValues[i]);
        testJacobian(transformationMatrix * vector, parameterValues[i]);
        testJacobian(-vector, parameterValues[i]);
        testJacobian(vector.normalized(), parameterValues[i]);
        testJacobian(vector.norm(), parameterValues[i]);
        testJacobian(v, parameterValues[i]);
        testJacobian(pow(2.0, scalar), parameterValues[i]);
        testJacobian(pow(scalar + 2, 3.0), parameterValues[i]);
        testJacobian(vector * (scalar + 1), parameterValues[i]);
        testJacobian(vector / (scalar + 2), parameterValues[i]);
        testJacobian(3.0 * vector, parameterValues[i]);
        testJacobian(sin(scalar), parameterValues[i]);
        testJacobian(vector.squaredNorm(), parameterValues[i]);
        testJacobian(sqrt(scalar + 2), parameterValues[i]);
        testJacobian(vector + u * columnMatrix(0, 0, 1), parameterValues[i]);
        testJacobian(tan(scalar), parameterValues[i]);
        testJacobian(vector + columnMatrix(1, 2, 3), parameterValues[i]);

        // Composition?
        // Concatenation?
    }
}

TEST_CASE("Dot product with constant") {
    Parameter1d t;
    ParametricExpression<3, 1> line = ColumnMatrix3d::ones() + ColumnMatrix3d::ones() * t;
    ParametricExpression<1, 1> dotProduct = line.dot(columnMatrix(0, 1, 0));
    REQUIRE((dotProduct.evaluate(0.0).value() - 1.0) == Zero());
    REQUIRE((dotProduct.evaluate(1.0).value() - 2.0) == Zero());
}

TEST_CASE("Cross product with constant") {
    Parameter1d t;
    ParametricExpression<3, 1> line = ColumnMatrix3d::ones() + ColumnMatrix3d::ones() * t;
    ParametricExpression<3, 1> crossProduct = line.cross(columnMatrix(0, 1, 0));
    REQUIRE((crossProduct.evaluate(0.0) - columnMatrix(-1, 0, 1)).isZero());
    REQUIRE((crossProduct.evaluate(1.0) - columnMatrix(-2, 0, 2)).isZero());
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
