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

#include <OpenSolid/Geometry/Geometry.hpp>
#include <OpenSolid/Scalar/Comparison.hpp>

using namespace OpenSolid;

class GeometryTestSuite : public CxxTest::TestSuite
{
public:
    void testLine() {
        Vector3d start(1, 2, 3);
        Vector3d end(4, 5, 6);
        Geometry line = Geometry::Line(start, end);
        std::cout << line(0.5) << std::endl;
        TS_ASSERT(line(0.5).isApprox(Vector3d(2.5, 3.5, 4.5)));
    }
    
    void testArc() {
        Vector3d center(1, 1, 1);
        Vector3d start(3, 1, 1);
        Vector3d end(1, -1, 1);
        Geometry arc = Geometry::Arc(Axis3d(center, Vector3d::UnitZ()), start, end);
        Interval domain = arc.domain().bounds().value();
        std::cout << "Domain interval: " << domain << std::endl;
        RowVectorXd parameter_values = RowVectorXd::LinSpaced(13, domain);
        std::cout << "Parameter values:" << std::endl;
        std::cout << parameter_values << std::endl << std::endl;
        std::cout << "Values:" << std::endl;
        std::cout << arc(parameter_values) << std::endl;
        TS_ASSERT(arc(M_PI / 2).isApprox(Vector3d(1, 3, 1)));
        TS_ASSERT(arc(3 * M_PI / 2).isApprox(Vector3d(1, -1, 1)));
        
        Function derivative = arc.function().derivative();
        std::cout << "Derivative function: " << std::endl << derivative << std::endl;
        std::cout << "Derivative values:" << std::endl;
        std::cout << derivative(parameter_values) << std::endl;
        TS_ASSERT(derivative(0.0).isApprox(Vector3d(0, 2, 0)));
        TS_ASSERT(derivative(M_PI / 2).isApprox(Vector3d(-2, 0, 0)));
        TS_ASSERT(derivative(M_PI).isApprox(Vector3d(0, -2, 0)));
        TS_ASSERT(derivative(3 * M_PI / 2).isApprox(Vector3d(2, 0, 0)));
        
        Function tangent = arc.function().tangent();
        std::cout << "Tangent function: " << std::endl << tangent << std::endl;
        std::cout << "Tangent values:" << std::endl;
        std::cout << tangent(parameter_values) << std::endl;
        TS_ASSERT(tangent(0.0).isApprox(Vector3d(0, 1, 0)));
        TS_ASSERT(tangent(M_PI / 2).isApprox(Vector3d(-1, 0, 0)));
        TS_ASSERT(tangent(M_PI).isApprox(Vector3d(0, -1, 0)));
        TS_ASSERT(tangent(3 * M_PI / 2).isApprox(Vector3d(1, 0, 0)));
        
        Function second_derivative = arc.function().derivative().derivative();
        std::cout << "Second derivative function: " << std::endl;
        std::cout << second_derivative << std::endl;
        std::cout << "Second derivative values:" << std::endl;
        std::cout << second_derivative(parameter_values) << std::endl;
        
        TS_ASSERT(second_derivative(0.0).isApprox(Vector3d(-2, 0, 0)));
        TS_ASSERT(second_derivative(M_PI / 2).isApprox(Vector3d(0, -2, 0)));
        TS_ASSERT(second_derivative(M_PI).isApprox(Vector3d(2, 0, 0)));
        TS_ASSERT(second_derivative(M_PI * 3 / 2).isApprox(Vector3d(0, 2, 0)));
        
        Function normal = arc.function().tangent().tangent();
        std::cout << "Normal function: " << std::endl << normal << std::endl;
        std::cout << "Normal values:" << std::endl;
        std::cout << normal(parameter_values) << std::endl;
        
        TS_ASSERT(normal(0.0).isApprox(Vector3d(-1, 0, 0)));
        TS_ASSERT(normal(M_PI / 2).isApprox(Vector3d(0, -1, 0)));
        TS_ASSERT(normal(M_PI).isApprox(Vector3d(1, 0, 0)));
        TS_ASSERT(normal(3 * M_PI / 2).isApprox(Vector3d(0, 1, 0)));
    }
    
    void testCurveOperations() {
        Geometry parabola(
            Function::t * Vector3d::UnitX() + Function::t.squaredNorm() * Vector3d::UnitY(),
            Interval(-2, 2)
        );
        TS_ASSERT((parabola.function().tangent()(1) - Vector3d(1, 2, 0).normalized()).isZero());
        TS_ASSERT(parabola.function().curvature()(1).value() - 2 / (5 * sqrt(5.0)) == Zero());
        TS_ASSERT((parabola.function().normal()(1) - Vector3d(-2, 1, 0).normalized()).isZero());
        TS_ASSERT((parabola.function().binormal()(1) - Vector3d::UnitZ()).isZero());
    }
    
    void testHashing() {
        Geometry line = Geometry::Line(Vector2d::Zero(), Vector2d::Ones());
        std::unordered_map<Geometry, std::string> colors;
        colors[line] = "red";
        Geometry line_copy = line;
        TS_ASSERT_DIFFERS(colors.find(line_copy), colors.end());
        TS_ASSERT_EQUALS(colors[line_copy], "red");
    }
};
