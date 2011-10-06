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

#include <unordered_map>

#include <cxxtest/TestSuite.h>

#include <OpenSolid/Function/FunctionImplementation/EllipticalFunction.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>
#include <OpenSolid/Geometry/Arc.hpp>
#include <OpenSolid/Scalar/Comparison.hpp>
#include <OpenSolid/Simplex/Simplex.hpp>
#include <OpenSolid/Support/STL.hpp>

using namespace OpenSolid;

class GeometryTests : public CxxTest::TestSuite
{
public:
    void testLine() {
        Vector3d start(1, 2, 3);
        Vector3d end(4, 5, 6);
        Geometry line = LineSegment3d(start, end);
        std::cout << line(0.5) << std::endl;
        TS_ASSERT(line(0.5).isApprox(Vector3d(2.5, 3.5, 4.5)));
    }
    
    void testArc() {
        Vector3d center(1, 1, 1);
        Vector3d start(3, 1, 1);
        Vector3d end(1, -1, 1);
        Geometry arc = Arc3d(Axis3d(center, Vector3d::UnitZ()), start, end);

        Interval domain = arc.domain().bounds().value();
        RowVectorXd parameter_values = RowVectorXd::LinSpaced(13, domain);
        TS_ASSERT((arc(0.0) - Vector3d(3, 1, 1)).isZero());
        TS_ASSERT((arc(M_PI / 2) - Vector3d(1, 3, 1)).isZero());
        TS_ASSERT((arc(3 * M_PI / 2) - Vector3d(1, -1, 1)).isZero());
        
        Function derivative = arc.function().derivative();
        TS_ASSERT((derivative(0.0) - Vector3d(0, 2, 0)).isZero());
        TS_ASSERT((derivative(M_PI / 2) - Vector3d(-2, 0, 0)).isZero());
        TS_ASSERT((derivative(M_PI) - Vector3d(0, -2, 0)).isZero());
        TS_ASSERT((derivative(3 * M_PI / 2) - Vector3d(2, 0, 0)).isZero());
        
        Function tangent = arc.function().tangent();
        TS_ASSERT((tangent(0.0) - Vector3d(0, 1, 0)).isZero());
        TS_ASSERT((tangent(M_PI / 2) - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((tangent(M_PI) - Vector3d(0, -1, 0)).isZero());
        TS_ASSERT((tangent(3 * M_PI / 2) - Vector3d(1, 0, 0)).isZero());
        
        Function second_derivative = arc.function().derivative().derivative();
        TS_ASSERT((second_derivative(0.0) - Vector3d(-2, 0, 0)).isZero());
        TS_ASSERT((second_derivative(M_PI / 2) - Vector3d(0, -2, 0)).isZero());
        TS_ASSERT((second_derivative(M_PI) - Vector3d(2, 0, 0)).isZero());
        TS_ASSERT((second_derivative(M_PI * 3 / 2) - Vector3d(0, 2, 0)).isZero());
        
        Function normal = arc.function().tangent().tangent();
        TS_ASSERT((normal(0.0) - Vector3d(-1, 0, 0)).isZero());
        TS_ASSERT((normal(M_PI / 2) - Vector3d(0, -1, 0)).isZero());
        TS_ASSERT((normal(M_PI) - Vector3d(1, 0, 0)).isZero());
        TS_ASSERT((normal(3 * M_PI / 2) - Vector3d(0, 1, 0)).isZero());
    }
    
    void testCurveOperations() {
        Geometry parabola(
            Parameter() * Vector3d::UnitX() + Parameter().squaredNorm() * Vector3d::UnitY(),
            Interval(-2, 2)
        );
        TS_ASSERT((parabola.function().tangent()(1) - Vector3d(1, 2, 0).normalized()).isZero());
        TS_ASSERT(parabola.function().curvature()(1).value() - 2 / (5 * sqrt(5.0)) == Zero());
        TS_ASSERT((parabola.function().normal()(1) - Vector3d(-2, 1, 0).normalized()).isZero());
        TS_ASSERT((parabola.function().binormal()(1) - Vector3d::UnitZ()).isZero());
        Geometry reversed = parabola.reversed();
        TS_ASSERT((reversed(-1) - Vector3d(1, 1, 0)).isZero());
        TS_ASSERT((reversed(1) - Vector3d(-1, 1, 0)).isZero());

    }
    
    void testHashing() {
        Geometry line = LineSegment2d(Vector2d::Zero(), Vector2d::Ones());
        std::unordered_map<Geometry, std::string> colors;
        colors[line] = "red";
        Geometry line_copy = line;
        TS_ASSERT_DIFFERS(colors.find(line_copy), colors.end());
        TS_ASSERT_EQUALS(colors[line_copy], "red");
    }
};
