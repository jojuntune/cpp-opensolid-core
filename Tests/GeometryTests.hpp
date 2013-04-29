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
*************************************************************************************/

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Curve.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <cxxtest/TestSuite.h>

#include <unordered_map>

using namespace opensolid;

class GeometryTests : public CxxTest::TestSuite
{
public:
    void testLine() {
        Point3d start(1, 2, 3);
        Point3d end(4, 5, 6);
        Curve3d line = LineSegment3d(start, end);
        TS_ASSERT((line(0.5) - Point3d(2.5, 3.5, 4.5)).isZero());
    }
    
    void testArc() {
        Point3d centerPoint(1, 1, 1);
        Point3d startPoint(3, 1, 1);
        Point3d endPoint(1, -1, 1);
        Axis3d axis(centerPoint, Vector3d::UnitZ());
        Curve3d arc = Curve3d::ArcFromAxisAndEndpoints(axis, startPoint, endPoint);

        RowVectorXd parameterValues = RowVectorXd::LinSpaced(13, Interval::Unit());

        TS_ASSERT((arc(0.0) - Point3d(3, 1, 1)).isZero());
        TS_ASSERT((arc(1.0 / 3.0) - Point3d(1, 3, 1)).isZero());
        TS_ASSERT((arc(1.0) - Point3d(1, -1, 1)).isZero());
        
        Function derivative = arc.function().derivative();
        double derivativeMagnitude = 3 * M_PI;
        TS_ASSERT((derivative(0.0) -  Vector3d(0, derivativeMagnitude, 0)).isZero());
        TS_ASSERT((derivative(1.0 / 3.0) - Vector3d(-derivativeMagnitude, 0, 0)).isZero());
        TS_ASSERT((derivative(2.0 / 3.0) - Vector3d(0, -derivativeMagnitude, 0)).isZero());
        TS_ASSERT((derivative(1.0) - Vector3d(derivativeMagnitude, 0, 0)).isZero());
        
        Function tangent = arc.function().tangentVector();
        TS_ASSERT((tangent(0.0) - Vector3d(0, 1, 0)).isZero());
        TS_ASSERT((tangent(1.0 / 3.0) - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((tangent(2.0 / 3.0) - Vector3d(0, -1, 0)).isZero());
        TS_ASSERT((tangent(1.0) - Vector3d(1, 0, 0)).isZero());
        
        Function secondDerivative = arc.function().derivative().derivative();
        double secondDerivativeMagnitude = 4.5 * M_PI * M_PI;
        Vector3d expectedValue;
        
        expectedValue = Vector3d(-secondDerivativeMagnitude, 0, 0);
        TS_ASSERT((secondDerivative(0.0) - expectedValue).isZero());
        
        expectedValue = Vector3d(0, -secondDerivativeMagnitude, 0);
        TS_ASSERT((secondDerivative(1.0 / 3.0) - expectedValue).isZero());
        
        expectedValue = Vector3d(secondDerivativeMagnitude, 0, 0);
        TS_ASSERT((secondDerivative(2.0 / 3.0) - expectedValue).isZero());
        
        expectedValue = Vector3d(0, secondDerivativeMagnitude, 0);
        TS_ASSERT((secondDerivative(1.0) - expectedValue).isZero());
        
        Function normal = arc.function().tangentVector().tangentVector();
        TS_ASSERT((normal(0.0) - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((normal(1.0 / 3.0) - Vector3d(0, -1, 0)).isZero());
        TS_ASSERT((normal(2.0 / 3.0) - Vector3d(1, 0, 0)).isZero());
        TS_ASSERT((normal(1.0) - Vector3d(0, 1, 0)).isZero());
    }

    void testFullArc() {
        Axis3d axis(Point3d(0, 3, 3), Vector3d::UnitX());
        Point3d point(1, 3, 1);
        Curve3d arc = Curve3d::ArcFromAxisAndEndpoints(axis, point, point);

        TS_ASSERT((arc(0.25) - Point3d(1, 5, 3)).isZero());
        TS_ASSERT((arc(0.75) - Point3d(1, 1, 3)).isZero());
    }
    
    void testCurveOperations() {
        Function t = Function::t();
        Curve3d parabola(
            Function::FromComponents(t, t.squaredNorm(), Function::Constant(0.0, 1)),
            Interval(-2, 2)
        );

        TS_ASSERT((parabola.function().tangentVector()(1) - Vector3d(1, 2, 0).normalized()).isZero());
        TS_ASSERT(parabola.function().curvature()(1).value() - 2 / (5 * sqrt(5.0)) == Zero());
        TS_ASSERT((parabola.function().normalVector()(1) - Vector3d(-2, 1, 0).normalized()).isZero());
        TS_ASSERT((parabola.function().binormalVector()(1) - Vector3d::UnitZ()).isZero());

        Curve3d reversed = parabola.reversed();
        TS_ASSERT((reversed(-1) - Point3d(1, 1, 0)).isZero());
        TS_ASSERT((reversed(1) - Point3d(-1, 1, 0)).isZero());
    }
};
