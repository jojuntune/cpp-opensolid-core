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

#include <OpenSolid/Common/Comparison.hpp>
#include "Geometry.hpp"

using namespace OpenSolid;

class GeometryTestSuite : public CxxTest::TestSuite
{
public:
    void testLine() {
        Vector3d start(1, 2, 3);
        Vector3d end(4, 5, 6);
        Geometry line = Geometry::Line(start, end);
        std::cout << line(0.5) << std::endl;
        TS_ASSERT(Comparison::equal(line(0.5), Vector3d(2.5, 3.5, 4.5)));
    }
    
    void testArc() {
        Vector3d center(1, 1, 1);
        Vector3d start(3, 1, 1);
        Vector3d end(1, -1, 1);
        Geometry arc = Geometry::Arc(Axis3d(center, Vector3d::UnitZ()), start, end);
        Interval domain = arc.domain().interval();
        std::cout << "Domain interval: " << domain << std::endl;
        RowVectorXd parameter_values = RowVectorXd::LinSpaced(13, domain);
        std::cout << "Parameter values:" << std::endl;
        std::cout << parameter_values << std::endl << std::endl;
        std::cout << "Values:" << std::endl;
        std::cout << arc(parameter_values) << std::endl;
        TS_ASSERT(Comparison::equal(arc(M_PI / 2), Vector3d(1, 3, 1)));
        TS_ASSERT(Comparison::equal(arc(3 * M_PI / 2), Vector3d(1, -1, 1)));
        
        Geometry derivative = arc.derivative();
        std::cout << "Derivative function: " << std::endl << derivative.function() << std::endl;
        std::cout << "Derivative values:" << std::endl;
        std::cout << derivative(parameter_values) << std::endl;
        TS_ASSERT(Comparison::equal(derivative(0.0), Vector3d(0, 2, 0)));
        TS_ASSERT(Comparison::equal(derivative(M_PI / 2), Vector3d(-2, 0, 0)));
        TS_ASSERT(Comparison::equal(derivative(M_PI), Vector3d(0, -2, 0)));
        TS_ASSERT(Comparison::equal(derivative(3 * M_PI / 2), Vector3d(2, 0, 0)));
        
        Geometry tangent = arc.tangent();
        std::cout << "Tangent function: " << std::endl << tangent.function() << std::endl;
        std::cout << "Tangent values:" << std::endl;
        std::cout << tangent(parameter_values) << std::endl;
        TS_ASSERT(Comparison::equal(tangent(0.0), Vector3d(0, 1, 0)));
        TS_ASSERT(Comparison::equal(tangent(M_PI / 2), Vector3d(-1, 0, 0)));
        TS_ASSERT(Comparison::equal(tangent(M_PI), Vector3d(0, -1, 0)));
        TS_ASSERT(Comparison::equal(tangent(3 * M_PI / 2), Vector3d(1, 0, 0)));
        
        Geometry second_derivative = arc.derivative().derivative();
        std::cout << "Second derivative function: " << std::endl;
        std::cout << second_derivative.function() << std::endl;
        std::cout << "Second derivative values:" << std::endl;
        std::cout << second_derivative(parameter_values) << std::endl;
        
        TS_ASSERT(Comparison::equal(second_derivative(0.0), Vector3d(-2, 0, 0)));
        TS_ASSERT(Comparison::equal(second_derivative(M_PI / 2), Vector3d(0, -2, 0)));
        TS_ASSERT(Comparison::equal(second_derivative(M_PI), Vector3d(2, 0, 0)));
        TS_ASSERT(Comparison::equal(second_derivative(M_PI * 3 / 2), Vector3d(0, 2, 0)));
        
        Geometry normal = arc.tangent().tangent();
        std::cout << "Normal function: " << std::endl << normal.function() << std::endl;
        std::cout << "Normal values:" << std::endl;
        std::cout << normal(parameter_values) << std::endl;
        
        TS_ASSERT(Comparison::equal(normal(0.0), Vector3d(-1, 0, 0)));
        TS_ASSERT(Comparison::equal(normal(M_PI / 2), Vector3d(0, -1, 0)));
        TS_ASSERT(Comparison::equal(normal(M_PI), Vector3d(1, 0, 0)));
        TS_ASSERT(Comparison::equal(normal(3 * M_PI / 2), Vector3d(0, 1, 0)));
    }
    
    void testCurveOperations() {
        Geometry parabola(
            Function::t * Vector3d::UnitX() + Function::t.squaredNorm() * Vector3d::UnitY(),
            Interval(-2, 2)
        );
        Vector3d tangent = parabola.tangent()(1);
        double curvature = parabola.curvature()(1).scalar();
        Vector3d normal = parabola.normal()(1);
        Vector3d binormal = parabola.binormal()(1);
        
        TS_ASSERT(Comparison::equal(parabola.tangent()(1), Vector3d(1, 2, 0).normalized()));
        TS_ASSERT(Comparison::equal(parabola.curvature()(1).scalar(), 2 / (5 * sqrt(5.0))));
        TS_ASSERT(Comparison::equal(parabola.normal()(1), Vector3d(-2, 1, 0).normalized()));
        TS_ASSERT(Comparison::equal(parabola.binormal()(1), Vector3d::UnitZ()));
    }
    
    void testHashing() {
        Geometry line = Geometry::Line(Vector2d::Zero(), Vector2d::Ones());
        boost::unordered_map<Geometry, std::string> colors;
        colors[line] = "red";
        Geometry line_copy = line;
        TS_ASSERT_DIFFERS(colors.find(line_copy), colors.end());
        TS_ASSERT_EQUALS(colors[line_copy], "red");
    }
};
