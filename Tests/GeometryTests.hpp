/*************************************************************************************
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
#include <OpenSolid/Core/Geometry.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <cxxtest/TestSuite.h>

#include <unordered_map>

using namespace opensolid;

class GeometryTests : public CxxTest::TestSuite
{
public:
    void testLine() {
        Vector3d start(1, 2, 3);
        Vector3d end(4, 5, 6);
        Geometry line = LineSegment3d(start, end);
        TS_ASSERT((line(0.5) - Vector3d(2.5, 3.5, 4.5)).isZero());
    }

    void testTriangle() {
        Geometry triangle = Triangle2d(Vector2d::Zero(), Vector2d(3, 1), Vector2d(1, 3));
        TS_ASSERT((triangle(Vector2d(1, 0)) - Vector2d(3, 1)).isZero());
        TS_ASSERT((triangle(Vector2d(0, 1)) - Vector2d(1, 3)).isZero());
        TS_ASSERT((triangle(Vector2d(0.5, 0.5)) - Vector2d(2, 2)).isZero());
    }
    
    void testArc() {
        Vector3d center(1, 1, 1);
        Vector3d start(3, 1, 1);
        Vector3d end(1, -1, 1);
        Geometry arc = Geometry::Arc3d(Axis3d(center, Vector3d::UnitZ()), start, end);

        RowVectorXd parameter_values = RowVectorXd::LinSpaced(13, Interval::Unit());
        TS_ASSERT((arc(0.0) - Vector3d(3, 1, 1)).isZero());
        TS_ASSERT((arc(1.0 / 3.0) - Vector3d(1, 3, 1)).isZero());
        TS_ASSERT((arc(1.0) - Vector3d(1, -1, 1)).isZero());
        
        Function derivative = arc.function().derivative();
        double derivative_magnitude = 3 * M_PI;
        TS_ASSERT((derivative(0.0) - derivative_magnitude * Vector3d(0, 1, 0)).isZero());
        TS_ASSERT((derivative(1.0 / 3.0) - derivative_magnitude * Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((derivative(2.0 / 3.0) - derivative_magnitude * Vector3d(0, -1, 0)).isZero());
        TS_ASSERT((derivative(1.0) - derivative_magnitude * Vector3d(1, 0, 0)).isZero());
        
        Function tangent = arc.function().tangentVector();
        TS_ASSERT((tangent(0.0) - Vector3d(0, 1, 0)).isZero());
        TS_ASSERT((tangent(1.0 / 3.0) - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((tangent(2.0 / 3.0) - Vector3d(0, -1, 0)).isZero());
        TS_ASSERT((tangent(1.0) - Vector3d(1, 0, 0)).isZero());
        
        Function second_derivative = arc.function().derivative().derivative();
        double second_derivative_magnitude = 4.5 * M_PI * M_PI;
        Vector3d expected_value;
        expected_value = second_derivative_magnitude * Vector3d(-1, 0, 0);
        TS_ASSERT((second_derivative(0.0) - expected_value).isZero());
        expected_value = second_derivative_magnitude * Vector3d(0, -1, 0);
        TS_ASSERT((second_derivative(1.0 / 3.0) - expected_value).isZero());
        expected_value = second_derivative_magnitude * Vector3d(1, 0, 0);
        TS_ASSERT((second_derivative(2.0 / 3.0) - expected_value).isZero());
        expected_value = second_derivative_magnitude * Vector3d(0, 1, 0);
        TS_ASSERT((second_derivative(1.0) - expected_value).isZero());
        
        Function normal = arc.function().tangentVector().tangentVector();
        TS_ASSERT((normal(0.0) - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((normal(1.0 / 3.0) - Vector3d(0, -1, 0)).isZero());
        TS_ASSERT((normal(2.0 / 3.0) - Vector3d(1, 0, 0)).isZero());
        TS_ASSERT((normal(1.0) - Vector3d(0, 1, 0)).isZero());
    }

    void testFullArc() {
        Axis3d axis(Vector3d(0, 3, 3), Vector3d::UnitX());
        Vector3d point(1, 3, 1);
        Geometry arc = Geometry::Arc3d(axis, point, point);
        TS_ASSERT((arc(0.25) - Vector3d(1, 5, 3)).isZero());
        TS_ASSERT((arc(0.75) - Vector3d(1, 1, 3)).isZero());
    }
    
    void testCurveOperations() {
        Function t = Function::t();
        Geometry parabola(
            Function::FromComponents(t, t.squaredNorm(), Function::Constant(0.0, 1)),
            Interval(-2, 2)
        );
        TS_ASSERT((parabola.function().tangentVector()(1) - Vector3d(1, 2, 0).normalized()).isZero());
        TS_ASSERT(parabola.function().curvature()(1).value() - 2 / (5 * sqrt(5.0)) == Zero());
        TS_ASSERT((parabola.function().normalVector()(1) - Vector3d(-2, 1, 0).normalized()).isZero());
        TS_ASSERT((parabola.function().binormalVector()(1) - Vector3d::UnitZ()).isZero());
        Geometry reversed = parabola.reversed();
        TS_ASSERT((reversed(-1) - Vector3d(1, 1, 0)).isZero());
        TS_ASSERT((reversed(1) - Vector3d(-1, 1, 0)).isZero());
    }
};
