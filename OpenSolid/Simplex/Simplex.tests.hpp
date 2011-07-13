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

#include <cxxtest/TestSuite.h>

#include <OpenSolid/Scalar/Comparison.hpp>
#include <OpenSolid/Simplex/Simplex.hpp>

using namespace OpenSolid;

class SimplexTestSuite : public CxxTest::TestSuite
{
public:
    void testEdges() {
        Triangle3d triangle(Vector3d::Zero(), Vector3d(1, 0, 1), Vector3d(0, 1, 1));
        std::cout << "EDGES" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << i << ":" << std::endl;
            std::cout << triangle.edge(i, (i + 1) % 3).vertices() << std::endl;
        }
    }
    
    void testFaces() {
        Tetrahedron3d tetrahedron(
            Vector3d::Zero(),
            Vector3d(2, 1, 0),
            Vector3d(1, 2, 0),
            Vector3d(1, 1, 2)
        );
        std::cout << "FACES" << std::endl;
        for (int i = 0; i < 4; ++i) {
            std::cout << i << ":" << std::endl;
            std::cout << tetrahedron.face(i).vertices() << std::endl;
        }
    }
    
    void testDatumQuotient() {
        Triangle3d triangle3d(Vector3d(1, 1, 1), Vector3d(3, 1, 2), Vector3d(2, 2, 4));
        Triangle2d xy_projection = triangle3d / Frame3d().xyPlane();
        
        TS_ASSERT(xy_projection.vertex(0).isApprox(Vector2d(1, 1)));
        TS_ASSERT(xy_projection.vertex(1).isApprox(Vector2d(3, 1)));
        TS_ASSERT(xy_projection.vertex(2).isApprox(Vector2d(2, 2)));
        
        double xy_area = xy_projection.area();
        TS_ASSERT(xy_area > 0.0);
        Triangle2d yz_projection = triangle3D / Frame3d().yzPlane();
        
        TS_ASSERT(yz_projection.vertex(0).isApprox(Vector2d(1, 1)));
        TS_ASSERT(yz_projection.vertex(1).isApprox(Vector2d(1, 2)));
        TS_ASSERT(yz_projection.vertex(2).isApprox(Vector2d(2, 4)));
        
        double yz_area = yz_projection.area();
        TS_ASSERT(yz_area < 0.0);
        double xz_area = (triangle3D / Frame3d().xzPlane()).area();
        double area_from_components =
            sqrt(xy_area * xy_area + yz_area * yz_area + xz_area * xz_area);
            
        TS_ASSERT(triangle3d.area() == Approx(area_from_components));
    }
    
    void testVolumes() {
        Tetrahedron3d tetrahedron(
            Vector3d(1, 1, 1),
            Vector3d(2, 1, 1),
            Vector3d(1, 2, 1),
            Vector3d(1, 1, 2)
        );
        TS_ASSERT(tetrahedron.volume() == Approx(1.0 / 6.0));
        TS_ASSERT(tetrahedron.face(1).area() == Approx(0.5));
        TS_ASSERT(tetrahedron.edge(1, 3).length() == Approx(sqrt(2.0)));
    }
    
    void testCentroid() {
        Tetrahedron3d tetrahedron(
            Vector3d(1, 1, 1),
            Vector3d(2, 1, 1),
            Vector3d(1, 2, 1),
            Vector3d(1, 1, 2)
        );
        TS_ASSERT(tetrahedron.centroid().isApprox(Vector3d::Constant(1.25)));
        Triangle2d triangle(Vector2d(1, 1), Vector2d(2, 2), Vector2d(1, 3));
        TS_ASSERT(triangle.centroid().isApprox(Vector2d(4.0 / 3.0, 2)));
    }
    
    void testNormal() {
        LineSegment2d line_segment(Vector2d(1, 1), Vector2d(3, 2));
        TS_ASSERT(line_segment.normal().isApprox(Vector2d(-1, 2).normalized()));
        Triangle3d triangle(Vector3d(1, 1, 1), Vector3d(3, 1, 2), Vector3d(2, 2, 4));
        Vector3d expected_normal = Vector3d(2, 0, 1).cross(Vector3d(1, 1, 3)).normalized();
        TS_ASSERT(triangle.normal().isApprox(expected_normal));
    }
    
    void testCopyingAndEquality() {
        Triangle2d triangle(Vector2d::Zero(), Vector2d::UnitX(), Vector2d::UnitY());
        LineSegment2d line_segment = triangle.edge(1, 2);
        SimplexXd simplex = triangle;
        simplex = triangle.edge(1, 2);
        TS_ASSERT_EQUALS(line_segment, simplex);
    }
    
    void testHashing() {
        LineSegment2d first_line(Vector2d::Zero(), Vector2d::Ones());
        LineSegment2d second_line(Vector2d::Zero(), Vector2d::Ones());
        TS_ASSERT_EQUALS(
            Traits<LineSegment2d>::hash(first_line),
            Traits<LineSegment2d>::hash(second_line)
        );
    }
    
    void testCoordinateSystem() {
        Triangle3d triangle(Vector3d::Zero(), Vector3d(2, 0, 0), Vector3d(1, 2, 0));
        CoordinateSystem<3, 2> coordinate_system = triangle.coordinateSystem();
        Vector3d product = Vector2d(0.5, 0.5) * coordinate_system;
        TS_ASSERT(product.isApprox(Vector3d(1.5, 1, 0)));
        Vector2d quotient = Vector3d(1, 0, 0) / coordinate_system;
        TS_ASSERT(quotient.isApprox(Vector2d(0.5, 0)));
        quotient = Vector3d(3, 2, 0) / coordinate_system;
        TS_ASSERT(quotient.isApprox(Vector2d(1, 1)));
        Vector3d projection = (Vector3d(3, 4, 5) / coordinate_system) * coordinate_system;
        TS_ASSERT(projection.isApprox(Vector3d(3, 4, 0)));
    }
    
    void testLineSegment1d() {
        LineSegment3d segment_3d(Vector3d(1, 2, 3), Vector3d(4, 5, 6));
        LineSegment1d quotient = segment_3d / Frame3d().yAxis();
        LineSegment1d segment_1d(2, 5);
        TS_ASSERT(quotient.vertices().isApprox(segment_1d.vertices()));
        LineSegment3d product =
            LineSegment1d(1.0 / 3.0, 2.0 / 3.0) * segment_3d.coordinateSystem();
        TS_ASSERT(product.vertex(0).isApprox(Vector3d(2, 3, 4)));
        TS_ASSERT(product.vertex(1).isApprox(Vector3d(3, 4, 5)));
    }
};
