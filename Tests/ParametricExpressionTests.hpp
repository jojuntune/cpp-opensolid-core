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

#include <OpenSolid/Core/ExpressionImplementation/ConstantExpression.hpp>
#include <OpenSolid/Core/ExpressionImplementation/Evaluator.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <boost/timer.hpp>
#include <cxxtest/TestSuite.h>

#include <vector>

using namespace opensolid;

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

Matrix2Xd
squiggleParameterValues() {
    Matrix2Xd results(2, 25);
    for (int i = 0; i <= 4; ++i) {
        for (int j = 0; j <= 4; ++j) {
            results.col(i * 5 + j) = Vector2d(i / 5.0 + 0.1, j / 5.0 + 0.1);
        }
    }
    return results;
}

template <int iNumDimensions, int iNumParameters>
void testJacobian(
    const ParametricExpression<iNumDimensions, iNumParameters>& expression,
    const MatrixXd& parameterValues
) {
    for (int i = 0; i < parameterValues.cols(); ++i) {
        MatrixXd jacobian = expression.jacobian(parameterValues.col(i));
        MatrixXd expectedJacobian(iNumDimensions, iNumParameters);
        for (int j = 0; j < iNumParameters; ++j) {
            expectedJacobian.col(j) = expression.derivative(j).evaluate(parameterValues.col(i));
        }
        TS_ASSERT(jacobian.rows() == expectedJacobian.rows());
        TS_ASSERT(jacobian.cols() == expectedJacobian.cols());
        TS_ASSERT((jacobian - expectedJacobian).isZero());
        if (!(jacobian - expectedJacobian).isZero()) {
            std::cout << "ParametricExpression:" << std::endl;
            std::cout << expression << std::endl;
            std::cout << "Jacobian ";
            std::cout << "(parameter values " << parameterValues.col(i).transpose() << ")";
            std::cout << ":" << std::endl;
            std::cout << jacobian << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << expectedJacobian << std::endl;
            std::cout << "Difference:" << std::endl;
            std::cout << jacobian - expectedJacobian << std::endl;
        }
        for (int j = 0; j < iNumParameters; ++j) {
            Matrix<double, iNumParameters, 2> shiftedParameterValues;
            shiftedParameterValues.col(0) = parameterValues.col(i);
            shiftedParameterValues(j, 0) -= 1e-6 / 2;
            shiftedParameterValues.col(1) = parameterValues.col(i);
            shiftedParameterValues(j, 1) += 1e-6 / 2;
            Matrix<double, iNumDimensions, 2> shiftedValues =
                expression.evaluate(shiftedParameterValues);
            Matrix<double, iNumDimensions, 1> numericalDerivative =
                (shiftedValues.col(1) - shiftedValues.col(0)) / 1e-6;
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
        
        TS_ASSERT(expression.evaluate(Vector2d(0, 0)).value() - 2 == Zero());
        TS_ASSERT(expression.evaluate(Vector2d(1, 0)).value() - 3 == Zero());
        TS_ASSERT(expression.evaluate(Vector2d(1, 1)).value() - 2 == Zero());
        TS_ASSERT(expression.evaluate(Vector2d(0, 1)).value() - 1 == Zero());
        TS_ASSERT(expression.derivative(0).evaluate(Vector2d(0, 0)).value() - 1 == Zero());
        TS_ASSERT(expression.derivative(1).evaluate(Vector2d(0, 0)).value() + 1 == Zero());
        
        ParametricExpression<1, 2> negated = -expression;
        
        TS_ASSERT(negated.evaluate(Vector2d(0, 0)).value() + 2 == Zero());
        TS_ASSERT(negated.evaluate(Vector2d(1, 0)).value() + 3 == Zero());
        TS_ASSERT(negated.evaluate(Vector2d(1, 1)).value() + 2 == Zero());
        TS_ASSERT(negated.evaluate(Vector2d(0, 1)).value() + 1 == Zero());
        TS_ASSERT(negated.derivative(0).evaluate(Vector2d(0, 0)).value() + 1 == Zero());
        TS_ASSERT(negated.derivative(1).evaluate(Vector2d(0, 0)).value() - 1 == Zero());
    }

    void testMultiplication() {
        ParametricExpression<1, 2> expression = 1.0 + u / 1.0 * v / 1.0;
    
        TS_ASSERT(expression.evaluate(Vector2d(0, 0)).value() - 1 == Zero());
        TS_ASSERT(expression.evaluate(Vector2d(1, 0)).value() - 1 == Zero());
        TS_ASSERT(expression.evaluate(Vector2d(1, 1)).value() - 2 == Zero());
        TS_ASSERT(expression.evaluate(Vector2d(0, 1)).value() - 1 == Zero());
    
        ParametricExpression<1, 2> uDerivative = expression.derivative(0);
        
        TS_ASSERT(uDerivative.evaluate(Vector2d(0, 0)).value() == Zero());
        TS_ASSERT(uDerivative.evaluate(Vector2d(1, 0)).value() == Zero());
        TS_ASSERT(uDerivative.evaluate(Vector2d(1, 1)).value() - 1 == Zero());
        TS_ASSERT(uDerivative.evaluate(Vector2d(0, 1)).value() - 1 == Zero());
    
        ParametricExpression<1, 2> vDerivative = expression.derivative(1);
        
        TS_ASSERT(vDerivative.evaluate(Vector2d(0, 0)).value() == Zero());
        TS_ASSERT(vDerivative.evaluate(Vector2d(1, 0)).value() - 1 == Zero());
        TS_ASSERT(vDerivative.evaluate(Vector2d(1, 1)).value() - 1 == Zero());
        TS_ASSERT(vDerivative.evaluate(Vector2d(0, 1)).value() == Zero());
    }
    
    void testSquare() {
        ParametricExpression<1, 2> expression = u.squared() * 1.0 + v.squared() * 1.0;
        TS_ASSERT(expression.evaluate(Vector2d(1, 2)).value() - 5 == Zero());
        ParametricExpression<1, 2> uDerivative = expression.derivative(0);
        TS_ASSERT(uDerivative.evaluate(Vector2d(3, 4)).value() - 6 == Zero());
        ParametricExpression<1, 2> vSecondDerivative = expression.derivative(1).derivative(1);
        TS_ASSERT(vSecondDerivative.evaluate(Vector2d(5, 6)).value() - 2 == Zero());
    }

    void testNorm() {
        ParametricExpression<2, 1> arc = 3 * (cos(t) * Vector2d(1, 0) + Vector2d::UnitY() * sin(t));
        Vector2d evaluated = arc.normalized().evaluate(M_PI / 4);
        Vector2d expected(1 / sqrt(2.0), 1 / sqrt(2.0));
        TS_ASSERT((evaluated - expected).isZero());
    }
    
    void testVector() {
        ParametricExpression<3, 1> expression =
            ParametricExpression<3, 1>::Constant(Vector3d(1, 2, 3));
        TS_ASSERT(expression.implementation()->isConstantExpression());
    }
    
    void testConversion() {
        {
            ParametricExpression<1, 2> expression = u * v;
            TS_ASSERT(expression.evaluate(Vector2d(2, 3)).value() - 6 == Zero());
        }
        {
            ParametricExpression<1, 1> expression = ParametricExpression<1, 1>::Constant(2.0);
            TS_ASSERT(expression.evaluate(RowVector3d(1, 2, 3)) == RowVector3d::Constant(2.0));
        }
    }
    
    void testSine() {
        typedef Matrix<Interval, 1, 4> RowVector4I;
        ParametricExpression<1, 1> expression = sin(t);
        RowVector4d result = expression.evaluate(RowVector4d(0, M_PI / 2, M_PI, 3 * M_PI / 2));
        TS_ASSERT((result - RowVector4d(0, 1, 0, -1)).isZero());
        RowVector4I bounds = expression.evaluate(
            RowVector4I(
                Interval(0, M_PI / 2),
                Interval(M_PI / 2, M_PI),
                Interval(M_PI, 3 * M_PI / 2),
                Interval(0, 2 * M_PI)
            )
        );
        RowVector4I expectedBounds(
            Interval(0, 1),
            Interval(0, 1),
            Interval(-1, 0),
            Interval(-1, 1)
        );
        TS_ASSERT((bounds.cwiseLower() - expectedBounds.cwiseLower()).isZero());
        TS_ASSERT((bounds.cwiseUpper() - expectedBounds.cwiseUpper()).isZero());
    }
    
    void testCosine() {
        typedef Matrix<Interval, 1, 4> RowVector4I;
        ParametricExpression<1, 1> expression = cos(t);
        RowVector4d result = expression.evaluate(RowVector4d(0, M_PI / 2, M_PI, 3 * M_PI / 2));
        TS_ASSERT((result - RowVector4d(1, 0, -1, 0)).isZero());
        RowVector4I bounds = expression.evaluate(
            RowVector4I(
                Interval(0, M_PI / 2),
                Interval(M_PI / 2, M_PI),
                Interval(M_PI, 3 * M_PI / 2),
                Interval(0, 2 * M_PI)
            )
        );
        RowVector4I expectedBounds(
            Interval(0, 1),
            Interval(-1, 0),
            Interval(-1, 0),
            Interval(-1, 1)
        );
        TS_ASSERT((bounds.cwiseLower() - expectedBounds.cwiseLower()).isZero());
        TS_ASSERT((bounds.cwiseUpper() - expectedBounds.cwiseUpper()).isZero());
    }
    
    void testComponent() {
        ParametricExpression<3, 1> expression = Vector3d(1, 2, 3) + t * Vector3d(1, 2, 3);
        RowVector3d result = expression.component(1).evaluate(RowVector3d(0, 0.5, 1));
        TS_ASSERT((result - RowVector3d(2, 3, 4)).isZero());
        result = expression.evaluate(RowVector3d(0, 0.5, 1)).row(1);
        TS_ASSERT((result - RowVector3d(2, 3, 4)).isZero());
        double value = expression.z().evaluate(0.5).value();
        TS_ASSERT(value - 4.5 == Zero());
    }
    
    void testTransformation() {
        CoordinateSystem3d coordinateSystem = CoordinateSystem3d::Global();
        coordinateSystem = coordinateSystem.translatedBy(Vector3d(1, 1, 1));
        coordinateSystem = coordinateSystem.rotatedAbout(coordinateSystem.zAxis(), M_PI / 4);
        ParametricExpression<3, 1> linear = Vector3d::Ones() * t;
        ParametricExpression<3, 1> product = coordinateSystem.basisMatrix() * linear +
            coordinateSystem.originPoint().vector();
        ParametricExpression<3, 1> quotient = coordinateSystem.inverseMatrix() *
            (linear - coordinateSystem.originPoint().vector());
        RowVectorXd parameterValues = RowVectorXd::LinSpaced(5, Interval::Unit());
        MatrixXd productValues = (Vector3d(0, sqrt(2.0), 1) * parameterValues).colwise() +
            Vector3d(1, 1, 1);
        MatrixXd quotientValues = (Vector3d(sqrt(2.0), 0, 1) * parameterValues).colwise() +
            Vector3d(-sqrt(2.0), 0, -1);
        TS_ASSERT((product.evaluate(parameterValues) - productValues).isZero());
        TS_ASSERT((quotient.evaluate(parameterValues) - quotientValues).isZero());
    }
    
    void testConcatenation() {
        ParametricExpression<1, 1> x = t;
        ParametricExpression<1, 1> y = ParametricExpression<1, 1>::Constant(3.0);
        ParametricExpression<1, 1> z = t.squared();
        ParametricExpression<3, 1> concatenated =
            ParametricExpression<3, 1>::FromComponents(x, y, z);
        TS_ASSERT((concatenated.evaluate(2.0) - Vector3d(2.0, 3.0, 4.0)).isZero());
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

        testJacobian(expression, RowVector3d(-0.5, 0.0, 0.5));

        ParametricExpression<1, 2> expression2 = acos(u - v);
        testJacobian(expression2, Vector2d(0.5, 0));
        testJacobian(expression2, Vector2d(0, 0.25));
        testJacobian(expression2, Vector2d(-0.5, 0));
        testJacobian(expression2, Vector2d(0, -0.25));
        testJacobian(expression2, Vector2d(0, 0));
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
            Vector2d(1, 1) + 2 * ParametricExpression<2, 1>::FromComponents(cos(t), sin(t));
        TS_ASSERT((expression.evaluate(-M_PI / 2) - Vector2d(1, -1)).isZero());
        TS_ASSERT((expression.evaluate(0) - Vector2d(3, 1)).isZero());
        TS_ASSERT((expression.evaluate(M_PI / 2) - Vector2d(1, 3)).isZero());

        ParametricExpression<2, 1> normalVector = expression.normalVector();
        RowVectorXd parameterValues(5);
        parameterValues(0) = -M_PI / 2;
        parameterValues(1) = -M_PI / 4;
        parameterValues(2) = 0.0;
        parameterValues(3) = M_PI / 4;
        parameterValues(4) = M_PI / 2;

        Matrix2Xd expressionValues = expression.evaluate(parameterValues);
        Matrix2Xd normalValues = normalVector.evaluate(parameterValues);
        TS_ASSERT((expressionValues + 2 * normalValues - Matrix2Xd::Ones(2, 5)).isZero());
    }

    void testDeduplication() {
        {
            ParametricExpression<3, 1> constant1 =
                ParametricExpression<3, 1>::Constant(Vector3d(1, 2, 3));
            ParametricExpression<3, 1> constant2 =
                ParametricExpression<3, 1>::Constant(Vector3d(1, 2, 3));
            ParametricExpression<3, 1> constant3 =
                ParametricExpression<3, 1>::Constant(Vector3d(1, 2, 4));
            ParametricExpression<3, 2> constant4 =
                ParametricExpression<3, 2>::Constant(Vector3d(1, 2, 3));

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
        RowVector3d parameterValues(1, 2, 3);
        MapXcd parameterMap(parameterValues.data(), 1, 3, Stride<Dynamic, Dynamic>(1, 1));
        MapXcd results1 = evaluator.evaluate(expression.implementation(), parameterMap);
        MapXcd results2 = evaluator.evaluate(expression.implementation(), parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results2.data());
        MapXcd results3 = evaluator.evaluate(expression.implementation(), parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results3.data());
    }

    void testEvaluatorInterval() {
        ParametricExpression<1, 1> expression = t.squared();
        Evaluator evaluator;
        RowVector3I parameterBounds(Interval(1, 2), Interval(3, 4), Interval(5, 6));
        MapXcI parameterMap(parameterBounds.data(), 1, 3, Stride<Dynamic, Dynamic>(1, 1));
        MapXcI results1 = evaluator.evaluate(expression.implementation(), parameterMap);
        MapXcI results2 = evaluator.evaluate(expression.implementation(), parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results2.data());
        MapXcI results3 = evaluator.evaluate(expression.implementation(), parameterMap);
        TS_ASSERT_EQUALS(results1.data(), results3.data());
    }

    void testEllipseJacobian() {
        ParametricExpression<2, 1> ellipseExpression =
            Vector2d(3, 1) * cos(t) + Vector2d(1, 3) * sin(t);
        RowVector4d parameterValues(0.0, M_PI / 4, M_PI / 2, 3 * M_PI / 4);
        testJacobian(ellipseExpression, parameterValues);
    }

    void testEllipsoidJacobian() {
        ParametricExpression<3, 2> ellipsoidExpression = sin(v) * Vector3d(1, 1, 3) +
            cos(v) * (sin(u) * Vector3d(1, 3, 1) + cos(u) * Vector3d(3, 1, 1));
        testJacobian(ellipsoidExpression, Vector2d(0, 0));
        testJacobian(ellipsoidExpression, Vector2d(M_PI / 4, 0));
        testJacobian(ellipsoidExpression, Vector2d(0, M_PI / 4));
        testJacobian(ellipsoidExpression, Vector2d(M_PI / 4, M_PI / 4));
        testJacobian(ellipsoidExpression, Vector2d(M_PI / 2, 0));
        testJacobian(ellipsoidExpression, Vector2d(0, 3 * M_PI / 4));
    }

    void testSquiggleJacobians() {
        ParametricExpression<1, 2> scalar = scalarSquiggle();
        ParametricExpression<3, 2> vector = vectorSquiggle();
        Matrix2Xd parameterValues = squiggleParameterValues();
        Matrix3d transformationMatrix = Rotation3d(Axis3d::X(), M_PI / 4).transformationMatrix();

        testJacobian(scalar, parameterValues);
        testJacobian(vector, parameterValues);

        testJacobian(acos(scalar / 2), parameterValues);
        testJacobian(asin(scalar / 2), parameterValues);
        testJacobian(vector.components<2>(1), parameterValues);
        testJacobian(cos(scalar), parameterValues);
        testJacobian(vector.cross(vector + Vector3d::UnitZ()), parameterValues);
        testJacobian(vector - u * Vector3d::UnitZ(), parameterValues);
        testJacobian(vector.dot(vector + Vector3d::UnitZ()), parameterValues);
        testJacobian(exp(scalar), parameterValues);
        testJacobian(log(scalar + 2), parameterValues);
        testJacobian(transformationMatrix * vector, parameterValues);
        testJacobian(-vector, parameterValues);
        testJacobian(vector.normalized(), parameterValues);
        testJacobian(vector.norm(), parameterValues);
        testJacobian(v, parameterValues);
        testJacobian(pow(2.0, scalar), parameterValues);
        testJacobian(pow(scalar + 2, 3.0), parameterValues);
        testJacobian(vector * (scalar + 1), parameterValues);
        testJacobian(vector / (scalar + 2), parameterValues);
        testJacobian(3.0 * vector, parameterValues);
        testJacobian(sin(scalar), parameterValues);
        testJacobian(vector.squaredNorm(), parameterValues);
        testJacobian(sqrt(scalar + 2), parameterValues);
        testJacobian(vector + u * Vector3d::UnitZ(), parameterValues);
        testJacobian(tan(scalar), parameterValues);
        testJacobian(vector + Vector3d(1, 2, 3), parameterValues);

        // Composition?
        // Concatenation?
    }

    void testDotProductWithConstant() {
        ParametricExpression<3, 1> line = Vector3d::Ones() + Vector3d::Ones() * t;
        ParametricExpression<1, 1> dotProduct = line.dot(Vector3d::UnitY());
        TS_ASSERT(dotProduct.evaluate(0.0).value() - 1.0 == Zero());
        TS_ASSERT(dotProduct.evaluate(1.0).value() - 2.0 == Zero());
    }

    void testCrossProductWithConstant() {
        ParametricExpression<3, 1> line = Vector3d::Ones() + Vector3d::Ones() * t;
        ParametricExpression<3, 1> crossProduct = line.cross(Vector3d::UnitY());
        TS_ASSERT((crossProduct.evaluate(0.0) - Vector3d(-1, 0, 1)).isZero());
        TS_ASSERT((crossProduct.evaluate(1.0) - Vector3d(-2, 0, 2)).isZero());
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
