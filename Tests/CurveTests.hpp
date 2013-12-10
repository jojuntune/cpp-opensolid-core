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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/ParametricCurve.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <cxxtest/TestSuite.h>

#include <unordered_map>

using namespace opensolid;

class CurveTests : public CxxTest::TestSuite
{
public:
    // void xtestLine() {
    //     Point3d start(1, 2, 3);
    //     Point3d end(4, 5, 6);
    //     Curve3d line = LineSegment3d(start, end);
    //     TS_ASSERT((line(0.5) - Point3d(2.5, 3.5, 4.5)).isZero());
    // }
    
    void testArc() {
        Point3d centerPoint(1, 1, 1);
        Point3d startPoint(3, 1, 1);
        Point3d endPoint(1, -1, 1);
        ParametricCurve3d arc = ParametricCurve3d::Arc(
            centerPoint,
            Vector3d::UnitZ(),
            startPoint,
            endPoint
        );

        RowVectorXd parameterValues = RowVectorXd::LinSpaced(13, Interval::Unit());

        TS_ASSERT((arc.evaluate(0.0) - Point3d(3, 1, 1)).isZero());
        TS_ASSERT((arc.evaluate(1.0 / 3.0) - Point3d(1, 3, 1)).isZero());
        TS_ASSERT((arc.evaluate(1.0) - Point3d(1, -1, 1)).isZero());
        
        ParametricExpression<3, 1> derivative = arc.expression().derivative();
        double derivativeMagnitude = 3 * M_PI;
        TS_ASSERT((derivative.evaluate(0.0) -  Vector3d(0, derivativeMagnitude, 0)).isZero());
        TS_ASSERT((derivative.evaluate(1.0 / 3.0) - Vector3d(-derivativeMagnitude, 0, 0)).isZero());
        TS_ASSERT((derivative.evaluate(2.0 / 3.0) - Vector3d(0, -derivativeMagnitude, 0)).isZero());
        TS_ASSERT((derivative.evaluate(1.0) - Vector3d(derivativeMagnitude, 0, 0)).isZero());
        
        ParametricExpression<3, 1> tangent = arc.expression().tangentVector();
        TS_ASSERT((tangent.evaluate(0.0) - Vector3d(0, 1, 0)).isZero());
        TS_ASSERT((tangent.evaluate(1.0 / 3.0) - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((tangent.evaluate(2.0 / 3.0) - Vector3d(0, -1, 0)).isZero());
        TS_ASSERT((tangent.evaluate(1.0) - Vector3d(1, 0, 0)).isZero());
        
        ParametricExpression<3, 1> secondDerivative =
            arc.expression().derivative().derivative();
        double secondDerivativeMagnitude = 4.5 * M_PI * M_PI;
        Vector3d expectedValue;
        
        expectedValue = Vector3d(-secondDerivativeMagnitude, 0, 0);
        TS_ASSERT((secondDerivative.evaluate(0.0) - expectedValue).isZero());
        
        expectedValue = Vector3d(0, -secondDerivativeMagnitude, 0);
        TS_ASSERT((secondDerivative.evaluate(1.0 / 3.0) - expectedValue).isZero());
        
        expectedValue = Vector3d(secondDerivativeMagnitude, 0, 0);
        TS_ASSERT((secondDerivative.evaluate(2.0 / 3.0) - expectedValue).isZero());
        
        expectedValue = Vector3d(0, secondDerivativeMagnitude, 0);
        TS_ASSERT((secondDerivative.evaluate(1.0) - expectedValue).isZero());
        
        ParametricExpression<3, 1> normal =
            arc.expression().tangentVector().tangentVector();
        TS_ASSERT((normal.evaluate(0.0) - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((normal.evaluate(1.0 / 3.0) - Vector3d(0, -1, 0)).isZero());
        TS_ASSERT((normal.evaluate(2.0 / 3.0) - Vector3d(1, 0, 0)).isZero());
        TS_ASSERT((normal.evaluate(1.0) - Vector3d(0, 1, 0)).isZero());
    }

    void testFullArc() {
        Axis3d axis(Point3d(0, 3, 3), Vector3d::UnitX());
        Point3d point(1, 3, 1);
        ParametricCurve3d arc = ParametricCurve3d::Arc(axis, point, point);

        TS_ASSERT((arc.evaluate(0.25) - Point3d(1, 5, 3)).isZero());
        TS_ASSERT((arc.evaluate(0.75) - Point3d(1, 1, 3)).isZero());
    }
    
    void testCurveOperations() {
        ParametricExpression<1, 1> t = ParametricExpression<1, 1>::t();
        ParametricExpression<3, 1> expression =
            ParametricExpression<3, 1>::FromComponents(t, t.squared(), 0.0);
        ParametricCurve3d parabola(expression, Interval(-2, 2));

        Vector3d tangentVector = expression.tangentVector().evaluate(1.0);
        double curvature = expression.curvature().evaluate(1.0).value();
        Vector3d normalVector = expression.normalVector().evaluate(1.0);
        Vector3d binormalVector = expression.binormalVector().evaluate(1.0);

        TS_ASSERT((tangentVector - Vector3d(1, 2, 0).normalized()).isZero());
        TS_ASSERT(curvature - 2 / (5 * sqrt(5.0)) == Zero());
        TS_ASSERT((normalVector - Vector3d(-2, 1, 0).normalized()).isZero());
        TS_ASSERT((binormalVector - Vector3d::UnitZ()).isZero());

        ParametricCurve3d reversed = parabola.reversed();
        TS_ASSERT((reversed.evaluate(-1.0) - Point3d(1, 1, 0)).isZero());
        TS_ASSERT((reversed.evaluate(1.0) - Point3d(-1, 1, 0)).isZero());
    }
};
