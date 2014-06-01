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
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Parameter.hpp>
#include <OpenSolid/Core/ParametricCurve.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <catch/catch.hpp>

#include <unordered_map>

using namespace opensolid;

TEST_CASE("Arc") {
    Point3d centerPoint(1, 1, 1);
    Point3d startPoint(3, 1, 1);
    Point3d endPoint(1, -1, 1);
    ParametricCurve3d arc = ParametricCurve3d::Arc(
        centerPoint,
        UnitVector3d::k(),
        startPoint,
        endPoint
    );

    std::vector<double> parameterValues(13);
    for (int i = 0; i < 13; ++i) {
        parameterValues[i] = i / 12.0;
    }

    REQUIRE((arc.evaluate(0.0) - Point3d(3, 1, 1)).isZero());
    REQUIRE((arc.evaluate(1.0 / 3.0) - Point3d(1, 3, 1)).isZero());
    REQUIRE((arc.evaluate(1.0) - Point3d(1, -1, 1)).isZero());
    
    ParametricExpression<3, 1> derivative = arc.expression().derivative();
    REQUIRE((Vector3d(derivative.evaluate(0)) -  Vector3d(0, 3 * M_PI, 0)).isZero());
    REQUIRE((Vector3d(derivative.evaluate(1 / 3.0)) - Vector3d(-3 * M_PI, 0, 0)).isZero());
    REQUIRE((Vector3d(derivative.evaluate(2 / 3.0)) - Vector3d(0, -3 * M_PI, 0)).isZero());
    REQUIRE((Vector3d(derivative.evaluate(1)) - Vector3d(3 * M_PI, 0, 0)).isZero());
    
    ParametricExpression<3, 1> tangent = arc.tangentVector();
    REQUIRE((Vector3d(tangent.evaluate(0)) - Vector3d(0, 1, 0)).isZero());
    REQUIRE((Vector3d(tangent.evaluate(1 / 3.0)) - Vector3d(-1, 0, 0)).isZero());
    REQUIRE((Vector3d(tangent.evaluate(2 / 3.0)) - Vector3d(0, -1, 0)).isZero());
    REQUIRE((Vector3d(tangent.evaluate(1)) - Vector3d(1, 0, 0)).isZero());
    
    ParametricExpression<3, 1> secondDerivative =
        arc.expression().derivative().derivative();
    double secondDerivativeMagnitude = 4.5 * M_PI * M_PI;
    Vector3d expectedValue;
    
    expectedValue = Vector3d(-secondDerivativeMagnitude, 0, 0);
    REQUIRE((Vector3d(secondDerivative.evaluate(0.0)) - expectedValue).isZero());
    
    expectedValue = Vector3d(0, -secondDerivativeMagnitude, 0);
    REQUIRE((Vector3d(secondDerivative.evaluate(1.0 / 3.0)) - expectedValue).isZero());
    
    expectedValue = Vector3d(secondDerivativeMagnitude, 0, 0);
    REQUIRE((Vector3d(secondDerivative.evaluate(2.0 / 3.0)) - expectedValue).isZero());
    
    expectedValue = Vector3d(0, secondDerivativeMagnitude, 0);
    REQUIRE((Vector3d(secondDerivative.evaluate(1.0)) - expectedValue).isZero());
    
    ParametricExpression<3, 1> normal = arc.normalVector();
    REQUIRE((Vector3d(normal.evaluate(0.0)) - Vector3d(-1, 0, 0)).isZero());
    REQUIRE((Vector3d(normal.evaluate(1.0 / 3.0)) - Vector3d(0, -1, 0)).isZero());
    REQUIRE((Vector3d(normal.evaluate(2.0 / 3.0)) - Vector3d(1, 0, 0)).isZero());
    REQUIRE((Vector3d(normal.evaluate(1.0)) - Vector3d(0, 1, 0)).isZero());
}

TEST_CASE("Full arc") {
    Axis3d axis(Point3d(0, 3, 3), UnitVector3d::i());
    Point3d point(1, 3, 1);
    ParametricCurve3d arc = ParametricCurve3d::Arc(axis, point, point);

    REQUIRE((arc.evaluate(0.25) - Point3d(1, 5, 3)).isZero());
    REQUIRE((arc.evaluate(0.75) - Point3d(1, 1, 3)).isZero());
}

TEST_CASE("2D arc") {
    ParametricCurve2d arc2d = ParametricCurve2d::Arc(
        Point2d(2, 1),
        ParametricCurve2d::COUNTERCLOCKWISE,
        Point2d(3, 1),
        Point2d(2, 2)
    );

    REQUIRE((arc2d.evaluate(0.0) - Point2d(3, 1)).isZero());
    REQUIRE((arc2d.evaluate(0.5) - Point2d(2 + 1 / sqrt(2.0), 1 + 1 / sqrt(2.0))).isZero());
    REQUIRE((arc2d.evaluate(1.0) - Point2d(2, 2)).isZero());
}

TEST_CASE("Curve operations") {
    Parameter1d t;
    ParametricExpression<3, 1> expression =
        ParametricExpression<3, 1>::fromComponents(t, t.squared(), 0.0);
    ParametricCurve3d parabola(expression, Interval(-2, 2));

    Vector3d tangentVector(parabola.tangentVector().evaluate(1.0));
    double curvature = parabola.curvature().evaluate(1.0).value();
    Vector3d normalVector(parabola.normalVector().evaluate(1.0));
    Vector3d binormalVector(parabola.binormalVector().evaluate(1.0));

    REQUIRE((tangentVector - Vector3d(1, 2, 0).normalized()).isZero());
    REQUIRE((curvature - 2 / (5 * sqrt(5.0))) == Zero());
    REQUIRE((normalVector - Vector3d(-2, 1, 0).normalized()).isZero());
    REQUIRE((binormalVector - Vector3d(0, 0, 1)).isZero());

    ParametricCurve3d reversed = parabola.reversed();
    REQUIRE((reversed.evaluate(-1.0) - Point3d(1, 1, 0)).isZero());
    REQUIRE((reversed.evaluate(1.0) - Point3d(-1, 1, 0)).isZero());
}

TEST_CASE("Multi-evaluation") {
    ParametricCurve2d arc = ParametricCurve2d::Arc(
        Point2d::Origin(),
        ParametricCurve2d::COUNTERCLOCKWISE,
        Point2d(1, 0),
        Point2d(0, 1)
    );

    std::vector<double> parameterValues(3);
    parameterValues[0] = 0.0;
    parameterValues[1] = 0.5;
    parameterValues[2] = 1.0;

    std::vector<Point2d> points = arc.evaluate(parameterValues);
    REQUIRE((points[0] - Point2d(1, 0)).isZero());
    REQUIRE((points[1] - Point2d(1 / sqrt(2.0), 1 / sqrt(2.0))).isZero());
    REQUIRE((points[2] - Point2d(0, 1)).isZero());
}
