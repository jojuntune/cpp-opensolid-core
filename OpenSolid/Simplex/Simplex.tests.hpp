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

#include <OpenSolid/Simplex/Simplex.hpp>

using namespace OpenSolid;

class SimplexTestSuite : public CxxTest::TestSuite
{
public:
    void testEdges() {
        Triangle3D triangle(Vector3D::Zero(), Vector3D(1, 0, 1), Vector3D(0, 1, 1));
        std::cout << "EDGES" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << i << ":" << std::endl;
            std::cout << triangle.edge(i, (i + 1) % 3).vertices() << std::endl;
        }
    }
    
    void testFaces() {
        Tetrahedron3D tetrahedron(
            Vector3D::Zero(),
            Vector3D(2, 1, 0),
            Vector3D(1, 2, 0),
            Vector3D(1, 1, 2)
        );
        std::cout << "FACES" << std::endl;
        for (int i = 0; i < 4; ++i) {
            std::cout << i << ":" << std::endl;
            std::cout << tetrahedron.face(i).vertices() << std::endl;
        }
    }
    
    void testDatumQuotient() {
        Triangle3D triangle3D(Vector3D(1, 1, 1), Vector3D(3, 1, 2), Vector3D(2, 2, 4));
        Triangle2D xy_projection = triangle3D / Frame3D().xyPlane();
        
        TS_ASSERT(xy_projection.vertex(0).isEqualTo(Vector2D(1, 1)));
        TS_ASSERT(xy_projection.vertex(1).isEqualTo(Vector2D(3, 1)));
        TS_ASSERT(xy_projection.vertex(2).isEqualTo(Vector2D(2, 2)));
        
        Double xy_area = xy_projection.area();
        TS_ASSERT(xy_area > 0.0);
        Triangle2D yz_projection = triangle3D / Frame3D().yzPlane();
        
        TS_ASSERT(yz_projection.vertex(0).isEqualTo(Vector2D(1, 1)));
        TS_ASSERT(yz_projection.vertex(1).isEqualTo(Vector2D(1, 2)));
        TS_ASSERT(yz_projection.vertex(2).isEqualTo(Vector2D(2, 4)));
        
        Double yz_area = yz_projection.area();
        TS_ASSERT(yz_area < 0.0);
        Double xz_area = (triangle3D / Frame3D().xzPlane()).area();
        Double area_from_components =
            sqrt(xy_area * xy_area + yz_area * yz_area + xz_area * xz_area);
            
        TS_ASSERT(triangle3D.area().isEqualTo(area_from_components));
    }
    
    void testVolumes() {
        Tetrahedron3D tetrahedron(
            Vector3D(1, 1, 1),
            Vector3D(2, 1, 1),
            Vector3D(1, 2, 1),
            Vector3D(1, 1, 2)
        );
        TS_ASSERT(tetrahedron.volume().isEqualTo(1.0 / 6.0));
        TS_ASSERT(tetrahedron.face(1).area().isEqualTo(0.5));
        TS_ASSERT(tetrahedron.edge(1, 3).length().isEqualTo(sqrt(2.0)));
    }
    
    void testCentroid() {
        Tetrahedron3D tetrahedron(
            Vector3D(1, 1, 1),
            Vector3D(2, 1, 1),
            Vector3D(1, 2, 1),
            Vector3D(1, 1, 2)
        );
        TS_ASSERT(tetrahedron.centroid().isEqualTo(Vector3D::Constant(1.25)));
        Triangle2D triangle(Vector2D(1, 1), Vector2D(2, 2), Vector2D(1, 3));
        TS_ASSERT(triangle.centroid().isEqualTo(Vector2D(4.0 / 3.0, 2)));
    }
    
    void testNormal() {
        LineSegment2D line_segment(Vector2D(1, 1), Vector2D(3, 2));
        TS_ASSERT(line_segment.normal().isEqualTo(Vector2D(-1, 2).normalized()));
        Triangle3D triangle(Vector3D(1, 1, 1), Vector3D(3, 1, 2), Vector3D(2, 2, 4));
        Vector3D expected_normal = Vector3D(2, 0, 1).cross(Vector3D(1, 1, 3)).normalized();
        TS_ASSERT(triangle.normal().isEqualTo(expected_normal));
    }
    
    void testCopyingAndEquality() {
        Triangle2D triangle(Vector2D::Zero(), Vector2D::UnitX(), Vector2D::UnitY());
        LineSegment2D line_segment = triangle.edge(1, 2);
        SimplexXD simplex = triangle;
        simplex = triangle.edge(1, 2);
        TS_ASSERT_EQUALS(line_segment, simplex);
    }
    
    void testHashing() {
        LineSegment2D first_line(Vector2D::Zero(), Vector2D::Ones());
        LineSegment2D second_line(Vector2D::Zero(), Vector2D::Ones());
        TS_ASSERT_EQUALS(first_line.hashValue(), second_line.hashValue());
    }
    
    void testCoordinateSystem() {
        Triangle3D triangle(Vector3D::Zero(), Vector3D(2, 0, 0), Vector3D(1, 2, 0));
        CoordinateSystem<3, 2> coordinate_system = triangle.coordinateSystem();
        Vector3D product = Vector2D(0.5, 0.5) * coordinate_system;
        TS_ASSERT(product.isEqualTo(Vector3D(1.5, 1, 0)));
        Vector2D quotient = Vector3D(1, 0, 0) / coordinate_system;
        TS_ASSERT(quotient.isEqualTo(Vector2D(0.5, 0)));
        quotient = Vector3D(3, 2, 0) / coordinate_system;
        TS_ASSERT(quotient.isEqualTo(Vector2D(1, 1)));
        Vector3D projection = (Vector3D(3, 4, 5) / coordinate_system) * coordinate_system;
        TS_ASSERT(projection.isEqualTo(Vector3D(3, 4, 0)));
    }
    
    void testLineSegment1D() {
        LineSegment3D segment_3d(Vector3D(1, 2, 3), Vector3D(4, 5, 6));
        LineSegment1D quotient = segment_3d / Frame3D().yAxis();
        LineSegment1D segment_1d(2, 5);
        TS_ASSERT(quotient.vertices().isEqualTo(segment_1d.vertices()));
        LineSegment3D product =
            LineSegment1D(1.0 / 3.0, 2.0 / 3.0) * segment_3d.coordinateSystem();
        TS_ASSERT(product.vertex(0).isEqualTo(Vector3D(2, 3, 4)));
        TS_ASSERT(product.vertex(1).isEqualTo(Vector3D(3, 4, 5)));
    }
};
