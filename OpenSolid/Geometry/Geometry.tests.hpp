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

#include <boost/unordered_map.hpp>

#include <cxxtest/TestSuite.h>

#include <OpenSolid/Common/HashFunction.hpp>
#include <OpenSolid/Geometry/Geometry.hpp>

using namespace OpenSolid;

class GeometryTestSuite : public CxxTest::TestSuite
{
public:
    void testLine() {
        Vector3D start(1, 2, 3);
        Vector3D end(4, 5, 6);
        Geometry line = Geometry::Line(start, end);
        std::cout << line(0.5) << std::endl;
        TS_ASSERT(line(0.5).isEqualTo(Vector3D(2.5, 3.5, 4.5)));
    }
    
    void testArc() {
        Vector3D center(1, 1, 1);
        Vector3D start(3, 1, 1);
        Vector3D end(1, -1, 1);
        Geometry arc = Geometry::Arc(Axis3D(center, Vector3D::UnitZ()), start, end);
        Interval domain = arc.domain().bounds().value();
        std::cout << "Domain interval: " << domain << std::endl;
        RowVectorXD parameter_values = RowVectorXD::LinSpaced(13, domain);
        std::cout << "Parameter values:" << std::endl;
        std::cout << parameter_values << std::endl << std::endl;
        std::cout << "Values:" << std::endl;
        std::cout << arc(parameter_values) << std::endl;
        TS_ASSERT(arc(M_PI / 2).isEqualTo(Vector3D(1, 3, 1)));
        TS_ASSERT(arc(3 * M_PI / 2).isEqualTo(Vector3D(1, -1, 1)));
        
        Geometry derivative = arc.derivative();
        std::cout << "Derivative function: " << std::endl << derivative.function() << std::endl;
        std::cout << "Derivative values:" << std::endl;
        std::cout << derivative(parameter_values) << std::endl;
        TS_ASSERT(derivative(0.0).isEqualTo(Vector3D(0, 2, 0)));
        TS_ASSERT(derivative(M_PI / 2).isEqualTo(Vector3D(-2, 0, 0)));
        TS_ASSERT(derivative(M_PI).isEqualTo(Vector3D(0, -2, 0)));
        TS_ASSERT(derivative(3 * M_PI / 2).isEqualTo(Vector3D(2, 0, 0)));
        
        Geometry tangent = arc.tangent();
        std::cout << "Tangent function: " << std::endl << tangent.function() << std::endl;
        std::cout << "Tangent values:" << std::endl;
        std::cout << tangent(parameter_values) << std::endl;
        TS_ASSERT(tangent(0.0).isEqualTo(Vector3D(0, 1, 0)));
        TS_ASSERT(tangent(M_PI / 2).isEqualTo(Vector3D(-1, 0, 0)));
        TS_ASSERT(tangent(M_PI).isEqualTo(Vector3D(0, -1, 0)));
        TS_ASSERT(tangent(3 * M_PI / 2).isEqualTo(Vector3D(1, 0, 0)));
        
        Geometry second_derivative = arc.derivative().derivative();
        std::cout << "Second derivative function: " << std::endl;
        std::cout << second_derivative.function() << std::endl;
        std::cout << "Second derivative values:" << std::endl;
        std::cout << second_derivative(parameter_values) << std::endl;
        
        TS_ASSERT(second_derivative(0.0).isEqualTo(Vector3D(-2, 0, 0)));
        TS_ASSERT(second_derivative(M_PI / 2).isEqualTo(Vector3D(0, -2, 0)));
        TS_ASSERT(second_derivative(M_PI).isEqualTo(Vector3D(2, 0, 0)));
        TS_ASSERT(second_derivative(M_PI * 3 / 2).isEqualTo(Vector3D(0, 2, 0)));
        
        Geometry normal = arc.tangent().tangent();
        std::cout << "Normal function: " << std::endl << normal.function() << std::endl;
        std::cout << "Normal values:" << std::endl;
        std::cout << normal(parameter_values) << std::endl;
        
        TS_ASSERT(normal(0.0).isEqualTo(Vector3D(-1, 0, 0)));
        TS_ASSERT(normal(M_PI / 2).isEqualTo(Vector3D(0, -1, 0)));
        TS_ASSERT(normal(M_PI).isEqualTo(Vector3D(1, 0, 0)));
        TS_ASSERT(normal(3 * M_PI / 2).isEqualTo(Vector3D(0, 1, 0)));
    }
    
    void testCurveOperations() {
        Geometry parabola(
            Function::t * Vector3D::UnitX() + Function::t.squaredNorm() * Vector3D::UnitY(),
            Interval(-2, 2)
        );
        Vector3D tangent = parabola.tangent()(1);
        Double curvature = parabola.curvature()(1).value();
        Vector3D normal = parabola.normal()(1);
        Vector3D binormal = parabola.binormal()(1);
        
        TS_ASSERT(parabola.tangent()(1).isEqualTo(Vector3D(1, 2, 0).normalized()));
        TS_ASSERT(parabola.curvature()(1).value().isEqualTo(2 / (5 * sqrt(5.0))));
        TS_ASSERT(parabola.normal()(1).isEqualTo(Vector3D(-2, 1, 0).normalized()));
        TS_ASSERT(parabola.binormal()(1).isEqualTo(Vector3D::UnitZ()));
    }
    
    void testHashing() {
        Geometry line = Geometry::Line(Vector2D::Zero(), Vector2D::Ones());
        boost::unordered_map<Geometry, std::string, HashFunction> colors;
        colors[line] = "red";
        Geometry line_copy = line;
        TS_ASSERT_DIFFERS(colors.find(line_copy), colors.end());
        TS_ASSERT_EQUALS(colors[line_copy], "red");
    }
};
