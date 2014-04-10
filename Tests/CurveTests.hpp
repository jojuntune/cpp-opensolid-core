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
            UnitVector3d::Z(),
            startPoint,
            endPoint
        );

        std::vector<double> parameterValues(13);
        for (int i = 0; i < 13; ++i) {
            parameterValues[i] = i / 12.0;
        }

        TS_ASSERT((arc.evaluate(0.0) - Point3d(3, 1, 1)).isZero());
        TS_ASSERT((arc.evaluate(1.0 / 3.0) - Point3d(1, 3, 1)).isZero());
        TS_ASSERT((arc.evaluate(1.0) - Point3d(1, -1, 1)).isZero());
        
        ParametricExpression<3, 1> derivative = arc.expression().derivative();
        double derivativeMagnitude = 3 * M_PI;
        TS_ASSERT((derivative.evaluate(0) -  Matrix3x1(0, derivativeMagnitude, 0)).isZero());
        TS_ASSERT((derivative.evaluate(1 / 3.0) - Matrix3x1(-derivativeMagnitude, 0, 0)).isZero());
        TS_ASSERT((derivative.evaluate(2 / 3.0) - Matrix3x1(0, -derivativeMagnitude, 0)).isZero());
        TS_ASSERT((derivative.evaluate(1) - Matrix3x1(derivativeMagnitude, 0, 0)).isZero());
        
        ParametricExpression<3, 1> tangent = arc.tangentVector();
        TS_ASSERT((tangent.evaluate(0) - Matrix3x1(0, 1, 0)).isZero());
        TS_ASSERT((tangent.evaluate(1 / 3.0) - Matrix3x1(-1, 0, 0)).isZero());
        TS_ASSERT((tangent.evaluate(2 / 3.0) - Matrix3x1(0, -1, 0)).isZero());
        TS_ASSERT((tangent.evaluate(1) - Matrix3x1(1, 0, 0)).isZero());
        
        ParametricExpression<3, 1> secondDerivative =
            arc.expression().derivative().derivative();
        double secondDerivativeMagnitude = 4.5 * M_PI * M_PI;
        Matrix3x1 expectedValue;
        
        expectedValue = Matrix3x1(-secondDerivativeMagnitude, 0, 0);
        TS_ASSERT((secondDerivative.evaluate(0.0) - expectedValue).isZero());
        
        expectedValue = Matrix3x1(0, -secondDerivativeMagnitude, 0);
        TS_ASSERT((secondDerivative.evaluate(1.0 / 3.0) - expectedValue).isZero());
        
        expectedValue = Matrix3x1(secondDerivativeMagnitude, 0, 0);
        TS_ASSERT((secondDerivative.evaluate(2.0 / 3.0) - expectedValue).isZero());
        
        expectedValue = Matrix3x1(0, secondDerivativeMagnitude, 0);
        TS_ASSERT((secondDerivative.evaluate(1.0) - expectedValue).isZero());
        
        ParametricExpression<3, 1> normal = arc.normalVector();
        TS_ASSERT((normal.evaluate(0.0) - Matrix3x1(-1, 0, 0)).isZero());
        TS_ASSERT((normal.evaluate(1.0 / 3.0) - Matrix3x1(0, -1, 0)).isZero());
        TS_ASSERT((normal.evaluate(2.0 / 3.0) - Matrix3x1(1, 0, 0)).isZero());
        TS_ASSERT((normal.evaluate(1.0) - Matrix3x1(0, 1, 0)).isZero());
    }

    void testFullArc() {
        Axis3d axis(Point3d(0, 3, 3), UnitVector3d::X());
        Point3d point(1, 3, 1);
        ParametricCurve3d arc = ParametricCurve3d::Arc(axis, point, point);

        TS_ASSERT((arc.evaluate(0.25) - Point3d(1, 5, 3)).isZero());
        TS_ASSERT((arc.evaluate(0.75) - Point3d(1, 1, 3)).isZero());
    }

    void testArc2d() {
        ParametricCurve2d arc2d = ParametricCurve2d::Arc(
            Point2d(2, 1),
            ParametricCurve2d::COUNTERCLOCKWISE,
            Point2d(3, 1),
            Point2d(2, 2)
        );

        TS_ASSERT((arc2d.evaluate(0.0) - Point2d(3, 1)).isZero());
        TS_ASSERT((arc2d.evaluate(0.5) - Point2d(2 + 1 / sqrt(2.0), 1 + 1 / sqrt(2.0))).isZero());
        TS_ASSERT((arc2d.evaluate(1.0) - Point2d(2, 2)).isZero());
    }
    
    void testCurveOperations() {
        ParametricExpression<1, 1> t = ParametricExpression<1, 1>::t();
        ParametricExpression<3, 1> expression =
            ParametricExpression<3, 1>::FromComponents(t, t.squared(), 0.0);
        ParametricCurve3d parabola(expression, Interval(-2, 2));

        Matrix3x1 tangentVector = parabola.tangentVector().evaluate(1.0);
        double curvature = parabola.curvature().evaluate(1.0).value();
        Matrix3x1 normalVector = parabola.normalVector().evaluate(1.0);
        Matrix3x1 binormalVector = parabola.binormalVector().evaluate(1.0);

        TS_ASSERT((tangentVector - Vector3d(1, 2, 0).normalized().components()).isZero());
        TS_ASSERT(curvature - 2 / (5 * sqrt(5.0)) == Zero());
        TS_ASSERT((normalVector - Vector3d(-2, 1, 0).normalized().components()).isZero());
        TS_ASSERT((binormalVector - Matrix3x1(0, 0, 1)).isZero());

        ParametricCurve3d reversed = parabola.reversed();
        TS_ASSERT((reversed.evaluate(-1.0) - Point3d(1, 1, 0)).isZero());
        TS_ASSERT((reversed.evaluate(1.0) - Point3d(-1, 1, 0)).isZero());
    }

    void testMultiEvaluation() {
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

        TS_ASSERT((points[0] - Point2d(1, 0)).isZero());
        TS_ASSERT((points[1] - Point2d(1 / sqrt(2.0), 1 / sqrt(2.0))).isZero());
        TS_ASSERT((points[2] - Point2d(0, 1)).isZero());
    }
};
