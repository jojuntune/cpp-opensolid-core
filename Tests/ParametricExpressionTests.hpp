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
************************************************************************************/

#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/Evaluator.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <boost/timer.hpp>
#include <cxxtest/TestSuite.h>

#include <vector>

using namespace opensolid;

inline
Matrix1x1
scalarMatrix(double value) {
    Matrix1x1 result;
    result.value() = value;
    return result;
}

inline
ColMatrix2x1
colMatrix(double x, double y) {
    ColMatrix2x1 result;
    result(0) = x;
    result(1) = y;
    return result;
}

inline
ColMatrix3x1
colMatrix(double x, double y, double z) {
    ColMatrix3x1 result;
    result(0) = x;
    result(1) = y;
    result(2) = z;
    return result;
}

inline
IntervalMatrix1x1
scalarMatrix(Interval value) {
    IntervalMatrix1x1 result;
    result.value() = value;
    return result;
}

inline
IntervalColMatrix2x1
colMatrix(Interval x, Interval y) {
    IntervalColMatrix2x1 result;
    result(0) = x;
    result(1) = y;
    return result;
}

inline
IntervalColMatrix3x1
colMatrix(Interval x, Interval y, Interval z) {
    IntervalColMatrix3x1 result;
    result(0) = x;
    result(1) = y;
    result(2) = z;
    return result;
}

ParametricExpression<1, 2>
scalarSquiggle() {
    ParametricExpression<1, 2> u = ParametricExpression<1, 2>::u();
    ParametricExpression<1, 2> v = ParametricExpression<1, 2>::v();
    return sin(2 * M_PI * u) + cos(2 * M_PI * v);
}

ParametricExpression<3, 2>
vectorSquiggle() {
    ParametricExpression<1, 2> u = ParametricExpression<1, 2>::u();
    ParametricExpression<1, 2> v = ParametricExpression<1, 2>::v();
    return ParametricExpression<3, 2>::FromComponents(u, v, scalarSquiggle());
}

std::vector<ColMatrix2x1>
squiggleParameterValues() {
    std::vector<ColMatrix2x1> results(25);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            results[i * 5 + j] = colMatrix(i / 5.0 + 0.1, j / 5.0 + 0.1);
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
    TS_ASSERT((jacobian - expectedJacobian).isZero());
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
        shiftedParameterValues.col(0) = parameterValues;
        shiftedParameterValues.col(1) = parameterValues;
        shiftedParameterValues(j, 0) -= 1e-6 / 2;
        shiftedParameterValues(j, 1) += 1e-6 / 2;
        Matrix<double, iNumDimensions, 2> shiftedValues =
            expression.evaluate(shiftedParameterValues);
        Matrix<double, iNumDimensions, 1> numericalDerivative = shiftedValues.col(1);
        numericalDerivative = (shiftedValues.col(1) - shiftedValues.col(0)) / 1e-6;
        TS_ASSERT((numericalDerivative - jacobian.col(j)).isZero(1e-3));
        if (!(numericalDerivative - jacobian.col(j)).isZero(1e-3)) {
            std::cout << "ParametricExpression:" << std::endl;
            std::cout << expression << std::endl;
            std::cout << "Numerical derivative " << j << ": " << std::endl;
            std::cout << numericalDerivative.transpose() << std::endl;
            std::cout << "Jacobian derivative: " << std::endl;
            std::cout << jacobian.col(j).transpose() << std::endl;
        }
    }
}

class ParametricExpressionTests : public CxxTest::TestSuite
{
private:
    ParametricExpression<1, 1> t;
    ParametricExpression<1, 2> u;
    ParametricExpression<1, 2> v;
public:
    void setUp() {
        t = ParametricExpression<1, 1>::t();
        u = ParametricExpression<1, 2>::u();
        v = ParametricExpression<1, 2>::v();
    }

    void testConstant() {
        ParametricExpression<1, 1> expression = ParametricExpression<1, 1>::Constant(3.0);
        TS_ASSERT(expression.implementation()->isConstantExpression());
        TS_ASSERT(expression.evaluate(0.0).value() - 3 == Zero());
    }
    
    void testArithmetic() {
        ParametricExpression<1, 2> expression = 2.0 + u * 1.0 - 1.0 * v;
        
        TS_ASSERT(expression.evaluate(0, 0).value() - 2 == Zero());
        TS_ASSERT(expression.evaluate(1, 0).value() - 3 == Zero());
        TS_ASSERT(expression.evaluate(1, 1).value() - 2 == Zero());
        TS_ASSERT(expression.evaluate(0, 1).value() - 1 == Zero());
        TS_ASSERT(expression.derivative(0).evaluate(0, 0).value() - 1 == Zero());
        TS_ASSERT(expression.derivative(1).evaluate(0, 0).value() + 1 == Zero());
        
        ParametricExpression<1, 2> negated = -expression;
        
        TS_ASSERT(negated.evaluate(0, 0).value() + 2 == Zero());
        TS_ASSERT(negated.evaluate(1, 0).value() + 3 == Zero());
        TS_ASSERT(negated.evaluate(1, 1).value() + 2 == Zero());
        TS_ASSERT(negated.evaluate(0, 1).value() + 1 == Zero());
        TS_ASSERT(negated.derivative(0).evaluate(0, 0).value() + 1 == Zero());
        TS_ASSERT(negated.derivative(1).evaluate(0, 0).value() - 1 == Zero());
    }

    void testMultiplication() {
        ParametricExpression<1, 2> expression = 1.0 + u / 1.0 * v / 1.0;
    
        TS_ASSERT(expression.evaluate(0, 0).value() - 1 == Zero());
        TS_ASSERT(expression.evaluate(1, 0).value() - 1 == Zero());
        TS_ASSERT(expression.evaluate(1, 1).value() - 2 == Zero());
        TS_ASSERT(expression.evaluate(0, 1).value() - 1 == Zero());
    
        ParametricExpression<1, 2> uDerivative = expression.derivative(0);
        
        TS_ASSERT(uDerivative.evaluate(0, 0).value() == Zero());
        TS_ASSERT(uDerivative.evaluate(1, 0).value() == Zero());
        TS_ASSERT(uDerivative.evaluate(1, 1).value() - 1 == Zero());
        TS_ASSERT(uDerivative.evaluate(0, 1).value() - 1 == Zero());
    
        ParametricExpression<1, 2> vDerivative = expression.derivative(1);
        
        TS_ASSERT(vDerivative.evaluate(0, 0).value() == Zero());
        TS_ASSERT(vDerivative.evaluate(1, 0).value() - 1 == Zero());
        TS_ASSERT(vDerivative.evaluate(1, 1).value() - 1 == Zero());
        TS_ASSERT(vDerivative.evaluate(0, 1).value() == Zero());
    }
    
    void testSquare() {
        ParametricExpression<1, 2> expression = u.squared() * 1.0 + v.squared() * 1.0;
        TS_ASSERT(expression.evaluate(1, 2).value() - 5 == Zero());
        ParametricExpression<1, 2> uDerivative = expression.derivative(0);
        TS_ASSERT(uDerivative.evaluate(3, 4).value() - 6 == Zero());
        ParametricExpression<1, 2> vSecondDerivative = expression.derivative(1).derivative(1);
        TS_ASSERT(vSecondDerivative.evaluate(5, 6).value() - 2 == Zero());
    }

    void testNorm() {
        ParametricExpression<2, 1> arc = 3 * (cos(t) * colMatrix(1, 0) + colMatrix(0, 1) * sin(t));
        ColMatrix2x1 evaluated = arc.normalized().evaluate(M_PI / 4);
        ColMatrix2x1 expected = colMatrix(1 / sqrt(2.0), 1 / sqrt(2.0));
        TS_ASSERT((evaluated - expected).isZero());
    }
    
    void testConversion() {
        {
            ParametricExpression<1, 2> expression = u * v;
            TS_ASSERT(expression.evaluate(2, 3).value() - 6 == Zero());
        }
        {
            ParametricExpression<1, 1> expression = ParametricExpression<1, 1>::Constant(2.0);

            RowMatrix1x3 parameterValues;
            parameterValues(0) = 1;
            parameterValues(1) = 2;
            parameterValues(2) = 3;

            TS_ASSERT(expression.evaluate(parameterValues) == RowMatrix1x3::Constant(2.0));
        }
    }
    
    void testSine() {
        ParametricExpression<1, 1> expression = sin(t);

        std::vector<double> parameterValues(4);
        parameterValues[0] = 0;
        parameterValues[1] = M_PI / 2;
        parameterValues[2] = M_PI;
        parameterValues[3] = 3 * M_PI / 2;
        std::vector<Matrix1x1> resultValues = expression.evaluate(parameterValues);
        TS_ASSERT(resultValues[0].value() == Zero());
        TS_ASSERT(resultValues[1].value() - 1 == Zero());
        TS_ASSERT(resultValues[2].value() == Zero());
        TS_ASSERT(resultValues[3].value() + 1 == Zero());

        std::vector<Interval> parameterBounds(4);
        parameterBounds[0] = Interval(0, M_PI / 2);
        parameterBounds[1] = Interval(M_PI / 2, M_PI);
        parameterBounds[2] = Interval(M_PI, 3 * M_PI / 2);
        parameterBounds[3] = Interval(0, 2 * M_PI);
        std::vector<IntervalMatrix1x1> resultBounds = expression.evaluate(parameterBounds);
        TS_ASSERT(resultBounds[0].value().lowerBound() == Zero());
        TS_ASSERT(resultBounds[0].value().upperBound() - 1 == Zero());
        TS_ASSERT(resultBounds[1].value().lowerBound() == Zero());
        TS_ASSERT(resultBounds[1].value().upperBound() - 1 == Zero());
        TS_ASSERT(resultBounds[2].value().lowerBound() + 1 == Zero());
        TS_ASSERT(resultBounds[2].value().upperBound() == Zero());
        TS_ASSERT(resultBounds[3].value().lowerBound() + 1 == Zero());
        TS_ASSERT(resultBounds[3].value().upperBound() - 1 == Zero());
    }
    
    void testCosine() {
        ParametricExpression<1, 1> expression = cos(t);

        std::vector<double> parameterValues(4);
        parameterValues[0] = 0;
        parameterValues[1] = M_PI / 2;
        parameterValues[2] = M_PI;
        parameterValues[3] = 3 * M_PI / 2;
        std::vector<Matrix1x1> resultValues = expression.evaluate(parameterValues);
        TS_ASSERT(resultValues[0].value() - 1 == Zero());
        TS_ASSERT(resultValues[1].value() == Zero());
        TS_ASSERT(resultValues[2].value() + 1 == Zero());
        TS_ASSERT(resultValues[3].value() == Zero());

        std::vector<Interval> parameterBounds(4);
        parameterBounds[0] = Interval(0, M_PI / 2);
        parameterBounds[1] = Interval(M_PI / 2, M_PI);
        parameterBounds[2] = Interval(M_PI, 3 * M_PI / 2);
        parameterBounds[3] = Interval(0, 2 * M_PI);
        std::vector<IntervalMatrix1x1> resultBounds = expression.evaluate(parameterBounds);
        TS_ASSERT(resultBounds[0].value().lowerBound() == Zero());
        TS_ASSERT(resultBounds[0].value().upperBound() - 1 == Zero());
        TS_ASSERT(resultBounds[1].value().lowerBound() + 1 == Zero());
        TS_ASSERT(resultBounds[1].value().upperBound() == Zero());
        TS_ASSERT(resultBounds[2].value().lowerBound() + 1 == Zero());
        TS_ASSERT(resultBounds[2].value().upperBound() == Zero());
        TS_ASSERT(resultBounds[3].value().lowerBound() + 1 == Zero());
        TS_ASSERT(resultBounds[3].value().upperBound() - 1 == Zero());
    }
    
    void testComponent() {
        ParametricExpression<3, 1> expression = colMatrix(1, 2, 3) + t * colMatrix(1, 2, 3);
        
        RowMatrix1x3 parameterValues;
        parameterValues(0) = 0.0;
        parameterValues(1) = 0.5;
        parameterValues(2) = 1.0;

        RowMatrix1x3 results = expression.component(1).evaluate(parameterValues);
        std::cout << std::endl << "First: " << results << std::endl;
        TS_ASSERT(results(0) - 2.0 == Zero());
        TS_ASSERT(results(1) - 3.0 == Zero());
        TS_ASSERT(results(2) - 4.0 == Zero());

        results = expression.evaluate(parameterValues).row(1);
        std::cout << "Temp:" << std::endl << expression.evaluate(parameterValues) << std::endl;
        std::cout << "Second: " << results << std::endl;
        TS_ASSERT(results(0) - 2.0 == Zero());
        TS_ASSERT(results(1) - 3.0 == Zero());
        TS_ASSERT(results(2) - 4.0 == Zero());

        double value = expression.z().evaluate(0.5).value();
        TS_ASSERT(value - 4.5 == Zero());
    }
    
    void testTransformation() {
        CoordinateSystem3d coordinateSystem = CoordinateSystem3d::Global();
        coordinateSystem = coordinateSystem.translatedBy(Vector3d(1, 1, 1));
        coordinateSystem = coordinateSystem.rotatedAbout(coordinateSystem.zAxis(), M_PI / 4);
        ParametricExpression<3, 1> linear = ColMatrix3x1::Ones() * t;
        ParametricExpression<3, 1> product = coordinateSystem.basisMatrix() * linear +
            coordinateSystem.originPoint().components();
        ParametricExpression<3, 1> quotient = coordinateSystem.inverseMatrix() *
            (linear - coordinateSystem.originPoint().components());

        std::vector<double> parameterValues(5);
        std::vector<ColMatrix3x1> expectedProductValues(5);
        std::vector<ColMatrix3x1> expectedQuotientValues(5);
        for (int i = 0; i < 5; ++i) {
            parameterValues[i] = i / 4.0;
            expectedProductValues[i] = parameterValues[i] * colMatrix(0, sqrt(2.0), 1) +
                colMatrix(1, 1, 1);
            expectedQuotientValues[i] = parameterValues[i] * colMatrix(sqrt(2.0), 0, 1) +
                colMatrix(-sqrt(2.0), 0, -1);
        }
        std::vector<ColMatrix3x1> productValues = product.evaluate(parameterValues);
        std::vector<ColMatrix3x1> quotientValues = quotient.evaluate(parameterValues);
        for (int i = 0; i < 5; ++i) {
            TS_ASSERT((productValues[i] - expectedProductValues[i]).isZero());
            TS_ASSERT((quotientValues[i] - expectedQuotientValues[i]).isZero());
        }
    }
    
    void testConcatenation() {
        ParametricExpression<1, 1> x = t;
        ParametricExpression<1, 1> y = ParametricExpression<1, 1>::Constant(3.0);
        ParametricExpression<1, 1> z = t.squared();
        ParametricExpression<3, 1> concatenated =
            ParametricExpression<3, 1>::FromComponents(x, y, z);
        TS_ASSERT((concatenated.evaluate(2.0) - colMatrix(2.0, 3.0, 4.0)).isZero());
    }

    void testArccosine() {
        ParametricExpression<1, 1> expression = acos(t);
        Interval bounds;
        bounds = expression.evaluate(Interval(-1, 0)).value();
        TS_ASSERT(bounds.lowerBound() - M_PI / 2 == Zero());
        TS_ASSERT(bounds.upperBound() - M_PI == Zero());
        bounds = expression.evaluate(Interval(0.5, 1.5)).value();
        TS_ASSERT(bounds.lowerBound() == Zero());
        TS_ASSERT(bounds.upperBound() - M_PI / 3 == Zero());
        bounds = expression.evaluate(Interval(1 + 1e-14, 1 + 1e-10)).value();
        TS_ASSERT(bounds.lowerBound() == Zero());
        TS_ASSERT(bounds.upperBound() == Zero());

        testJacobian(expression, scalarMatrix(-0.5));
        testJacobian(expression, scalarMatrix(0.0));
        testJacobian(expression, scalarMatrix(0.5));

        ParametricExpression<1, 2> expression2 = acos(u - v);
        testJacobian(expression2, colMatrix(0.5, 0));
        testJacobian(expression2, colMatrix(0, 0.25));
        testJacobian(expression2, colMatrix(-0.5, 0));
        testJacobian(expression2, colMatrix(0, -0.25));
        testJacobian(expression2, colMatrix(0, 0));
    }

    void testArcsine() {
        ParametricExpression<1,1 > expression = asin(t);
        Interval bounds;
        bounds = expression.evaluate(Interval(-1, 0)).value();
        TS_ASSERT(bounds.lowerBound() + M_PI / 2 == Zero());
        TS_ASSERT(bounds.upperBound() == Zero());
        bounds = expression.evaluate(Interval(0.5, 1.5)).value();
        TS_ASSERT(bounds.lowerBound() - M_PI / 6 == Zero());
        TS_ASSERT(bounds.upperBound() - M_PI / 2 == Zero());
        bounds = expression.evaluate(Interval(1 + 1e-14, 1 + 1e-10)).value();
        TS_ASSERT(bounds.lowerBound() - M_PI / 2 == Zero());
        TS_ASSERT(bounds.upperBound() - M_PI / 2 == Zero());
    }

    void testNormalVector() {
        ParametricExpression<2, 1> expression =
            colMatrix(1, 1) + 2 * ParametricExpression<2, 1>::FromComponents(cos(t), sin(t));
        TS_ASSERT((expression.evaluate(-M_PI / 2) - colMatrix(1, -1)).isZero());
        TS_ASSERT((expression.evaluate(0) - colMatrix(3, 1)).isZero());
        TS_ASSERT((expression.evaluate(M_PI / 2) - colMatrix(1, 3)).isZero());

        ParametricExpression<2, 1> normalVector =
            expression.derivative().normalized().derivative().normalized();
        std::vector<double> parameterValues(5);
        parameterValues[0] = -M_PI / 2;
        parameterValues[1] = -M_PI / 4;
        parameterValues[2] = 0.0;
        parameterValues[3] = M_PI / 4;
        parameterValues[4] = M_PI / 2;

        std::vector<ColMatrix2x1> expressionValues = expression.evaluate(parameterValues);
        std::vector<ColMatrix2x1> normalValues = normalVector.evaluate(parameterValues);
        for (unsigned i = 0; i < expressionValues.size(); ++i) {
            TS_ASSERT((expressionValues[i] + 2 * normalValues[i] - colMatrix(1, 1)).isZero());
        }
    }

    void testDeduplication() {
        {
            ParametricExpression<3, 1> constant1 =
                ParametricExpression<3, 1>::Constant(colMatrix(1, 2, 3));
            ParametricExpression<3, 1> constant2 =
                ParametricExpression<3, 1>::Constant(colMatrix(1, 2, 3));
            ParametricExpression<3, 1> constant3 =
                ParametricExpression<3, 1>::Constant(colMatrix(1, 2, 4));
            ParametricExpression<3, 2> constant4 =
                ParametricExpression<3, 2>::Constant(colMatrix(1, 2, 3));

            TS_ASSERT(constant1.implementation()->isDuplicateOf(constant2.implementation()));
            TS_ASSERT(!constant1.implementation()->isDuplicateOf(constant3.implementation()));
            TS_ASSERT(!constant1.implementation()->isDuplicateOf(constant4.implementation()));
        }

        {
            ParametricExpression<1, 1> expression1 = t.squared() + 2 * t;
            ParametricExpression<1, 1> expression2 = t * 2 + t.squared();

            TS_ASSERT(expression1.implementation()->isDuplicateOf(expression2.implementation()));
        }

        {
            ParametricExpression<1, 2> expression1 = cos(u.squared() + v.squared());
            ParametricExpression<1, 2> expression2 = cos(v.squared() + u.squared());

            TS_ASSERT(expression1.implementation()->isDuplicateOf(expression2.implementation()));
        }

        {
            ParametricExpression<1, 2> expression1 = u.squared();
            ParametricExpression<1, 2> expression2 = v.squared();

            TS_ASSERT(!expression1.implementation()->isDuplicateOf(expression2.implementation()));
        }

        {
            ParametricExpression<1, 1> expression1 = sin(t);
            ParametricExpression<1, 1> expression2 = expression1;

            TS_ASSERT(expression1.implementation()->isDuplicateOf(expression1.implementation()));
            TS_ASSERT(expression1.implementation()->isDuplicateOf(expression2.implementation()));
        }

        {
            ParametricExpression<1, 2> expression1 = sin(sqrt(u));
            ParametricExpression<1, 2> expression2 = sin(sqrt(u));

            TS_ASSERT(expression1.implementation()->isDuplicateOf(expression2.implementation()));
        }
    }

    void testDeduplicatedOutput() {
        ParametricExpression<1, 1> expression = t.squared() + sin(t.squared());
        std::cout << expression << std::endl;
    }

    void testEvaluatorDouble() {
        ParametricExpression<1, 1> expression = t.squared();
        Evaluator evaluator;

        RowMatrix1x3 parameterValues;
        parameterValues(0) = 1.0;
        parameterValues(1) = 2.0;
        parameterValues(2) = 3.0;

        ConstMatrixViewXxX parameterMap(parameterValues.data(), 1, 3, 1);
        ConstMatrixViewXxX results1 = evaluator.evaluate(expression.implementation(), parameterMap);
        ConstMatrixViewXxX results2 = evaluator.evaluate(expression.implementation(), parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results2.data());
        ConstMatrixViewXxX results3 = evaluator.evaluate(expression.implementation(), parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results3.data());
    }

    void testEvaluatorInterval() {
        ParametricExpression<1, 1> expression = t.squared();
        Evaluator evaluator;

        IntervalRowMatrix1x3 parameterValues;
        parameterValues(0) = Interval(1, 2);
        parameterValues(1) = Interval(3, 4);
        parameterValues(2) = Interval(5, 6);

        ConstIntervalMatrixViewXxX parameterMap(parameterValues.data(), 1, 3, 1);
        ConstIntervalMatrixViewXxX results1 =
            evaluator.evaluate(expression.implementation(), parameterMap);
        ConstIntervalMatrixViewXxX results2 =
            evaluator.evaluate(expression.implementation(), parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results2.data());
        ConstIntervalMatrixViewXxX results3 =
            evaluator.evaluate(expression.implementation(), parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results3.data());
    }

    void testEllipseJacobian() {
        ParametricExpression<2, 1> ellipseExpression =
            colMatrix(3, 1) * cos(t) + colMatrix(1, 3) * sin(t);
        testJacobian(ellipseExpression, scalarMatrix(0.0));
        testJacobian(ellipseExpression, scalarMatrix(M_PI / 4));
        testJacobian(ellipseExpression, scalarMatrix(M_PI / 2));
        testJacobian(ellipseExpression, scalarMatrix(3 * M_PI / 4));
    }

    void testEllipsoidJacobian() {
        ParametricExpression<3, 2> ellipsoidExpression = sin(v) * colMatrix(1, 1, 3) +
            cos(v) * (sin(u) * colMatrix(1, 3, 1) + cos(u) * colMatrix(3, 1, 1));
        testJacobian(ellipsoidExpression, colMatrix(0, 0));
        testJacobian(ellipsoidExpression, colMatrix(M_PI / 4, 0));
        testJacobian(ellipsoidExpression, colMatrix(0, M_PI / 4));
        testJacobian(ellipsoidExpression, colMatrix(M_PI / 4, M_PI / 4));
        testJacobian(ellipsoidExpression, colMatrix(M_PI / 2, 0));
        testJacobian(ellipsoidExpression, colMatrix(0, 3 * M_PI / 4));
    }

    void testSquiggleJacobians() {
        ParametricExpression<1, 2> scalar = scalarSquiggle();
        ParametricExpression<3, 2> vector = vectorSquiggle();
        std::vector<ColMatrix2x1> parameterValues = squiggleParameterValues();
        Matrix3x3 transformationMatrix = Rotation3d(Axis3d::X(), M_PI / 4).transformationMatrix();

        for (unsigned i = 0; i < parameterValues.size(); ++i) {
            testJacobian(scalar, parameterValues[i]);
            testJacobian(vector, parameterValues[i]);

            testJacobian(acos(scalar / 2), parameterValues[i]);
            testJacobian(asin(scalar / 2), parameterValues[i]);
            testJacobian(vector.components<2>(1), parameterValues[i]);
            testJacobian(cos(scalar), parameterValues[i]);
            testJacobian(vector.cross(vector + colMatrix(0, 0, 1)), parameterValues[i]);
            testJacobian(vector - u * colMatrix(0, 0, 1), parameterValues[i]);
            testJacobian(vector.dot(vector + colMatrix(0, 0, 1)), parameterValues[i]);
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
            testJacobian(vector + u * colMatrix(0, 0, 1), parameterValues[i]);
            testJacobian(tan(scalar), parameterValues[i]);
            testJacobian(vector + colMatrix(1, 2, 3), parameterValues[i]);

            // Composition?
            // Concatenation?
        }
    }

    void testDotProductWithConstant() {
        ParametricExpression<3, 1> line = ColMatrix3x1::Ones() + ColMatrix3x1::Ones() * t;
        ParametricExpression<1, 1> dotProduct = line.dot(colMatrix(0, 1, 0));
        TS_ASSERT(dotProduct.evaluate(0.0).value() - 1.0 == Zero());
        TS_ASSERT(dotProduct.evaluate(1.0).value() - 2.0 == Zero());
    }

    void testCrossProductWithConstant() {
        ParametricExpression<3, 1> line = ColMatrix3x1::Ones() + ColMatrix3x1::Ones() * t;
        ParametricExpression<3, 1> crossProduct = line.cross(colMatrix(0, 1, 0));
        TS_ASSERT((crossProduct.evaluate(0.0) - colMatrix(-1, 0, 1)).isZero());
        TS_ASSERT((crossProduct.evaluate(1.0) - colMatrix(-2, 0, 2)).isZero());
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
