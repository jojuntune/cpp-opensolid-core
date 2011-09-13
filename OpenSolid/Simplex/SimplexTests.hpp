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

#include <boost/functional/hash.hpp>
#include <boost/unordered_map.hpp>
#include <boost/geometry.hpp>
#include <cxxtest/TestSuite.h>

#include <OpenSolid/Datum/Frame.hpp>
#include <OpenSolid/Datum/CoordinateSystem.hpp>
#include <OpenSolid/Scalar/Comparison.hpp>
#include <OpenSolid/Simplex/Simplex.hpp>
#include <OpenSolid/Set/Set.hpp>
#include <OpenSolid/Support/Boost.hpp>

using namespace OpenSolid;

class SimplexTests : public CxxTest::TestSuite
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
        
        TS_ASSERT((xy_projection.vertex(0) - Vector2d(1, 1)).isZero());
        TS_ASSERT((xy_projection.vertex(1) - Vector2d(3, 1)).isZero());
        TS_ASSERT((xy_projection.vertex(2) - Vector2d(2, 2)).isZero());
        
        double xy_area = xy_projection.area();
        TS_ASSERT(xy_area > 0.0);
        Triangle2d yz_projection = triangle3d / Frame3d().yzPlane();
        
        TS_ASSERT((yz_projection.vertex(0) - Vector2d(1, 1)).isZero());
        TS_ASSERT((yz_projection.vertex(1) - Vector2d(1, 2)).isZero());
        TS_ASSERT((yz_projection.vertex(2) - Vector2d(2, 4)).isZero());
        
        double yz_area = yz_projection.area();
        TS_ASSERT(yz_area < 0.0);
        double xz_area = (triangle3d / Frame3d().xzPlane()).area();
        double area_from_components =
            sqrt(xy_area * xy_area + yz_area * yz_area + xz_area * xz_area);
            
        TS_ASSERT(triangle3d.area() - area_from_components == Zero());
    }
    
    void testVolumes() {
        Tetrahedron3d tetrahedron(
            Vector3d(1, 1, 1),
            Vector3d(2, 1, 1),
            Vector3d(1, 2, 1),
            Vector3d(1, 1, 2)
        );
        TS_ASSERT(tetrahedron.volume() - 1.0 / 6.0 == Zero());
        TS_ASSERT(tetrahedron.face(1).area() - 0.5 == Zero());
        TS_ASSERT(tetrahedron.edge(1, 3).length() - sqrt(2.0) == Zero());
    }
    
    void testCentroid() {
        Tetrahedron3d tetrahedron(
            Vector3d(1, 1, 1),
            Vector3d(2, 1, 1),
            Vector3d(1, 2, 1),
            Vector3d(1, 1, 2)
        );
        TS_ASSERT((tetrahedron.centroid() - Vector3d::Constant(1.25)).isZero());
        Triangle2d triangle(Vector2d(1, 1), Vector2d(2, 2), Vector2d(1, 3));
        TS_ASSERT((triangle.centroid() - Vector2d(4.0 / 3.0, 2)).isZero());
    }
    
    void testNormal() {
        LineSegment2d line_segment(Vector2d(1, 1), Vector2d(3, 2));
        TS_ASSERT((line_segment.normal() - Vector2d(-1, 2).normalized()).isZero());
        Triangle3d triangle(Vector3d(1, 1, 1), Vector3d(3, 1, 2), Vector3d(2, 2, 4));
        Vector3d expected_normal = Vector3d(2, 0, 1).cross(Vector3d(1, 1, 3)).normalized();
        TS_ASSERT((triangle.normal() - expected_normal).isZero());
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
            std::hash<LineSegment2d>()(first_line),
            std::hash<LineSegment2d>()(second_line)
        );
    }
    
    void testBoostHashing() {
        boost::unordered_map<LineSegment2d, std::string> map;
        LineSegment2d first_line(Vector2d::Zero(), Vector2d::Ones());
        LineSegment2d second_line(Vector2d::Zero(), Vector2d::Ones());
        map[first_line] = "value";
        TS_ASSERT_EQUALS(map[second_line], "value");
    }
    
    void testCoordinateSystem() {
        Triangle3d triangle(Vector3d::Zero(), Vector3d(2, 0, 0), Vector3d(1, 2, 0));
        CoordinateSystem<3, 2> coordinate_system = triangle.coordinateSystem();
        Vector3d product = Vector2d(0.5, 0.5) * coordinate_system;
        TS_ASSERT((product - Vector3d(1.5, 1, 0)).isZero());
        Vector2d quotient = Vector3d(1, 0, 0) / coordinate_system;
        TS_ASSERT((quotient - Vector2d(0.5, 0)).isZero());
        quotient = Vector3d(3, 2, 0) / coordinate_system;
        TS_ASSERT((quotient - Vector2d(1, 1)).isZero());
        Vector3d projection = (Vector3d(3, 4, 5) / coordinate_system) * coordinate_system;
        TS_ASSERT((projection - Vector3d(3, 4, 0)).isZero());
    }
    
    void testLineSegment1d() {
        LineSegment3d segment_3d(Vector3d(1, 2, 3), Vector3d(4, 5, 6));
        LineSegment1d quotient = segment_3d / Frame3d().yAxis();
        LineSegment1d segment_1d(2, 5);
        TS_ASSERT((quotient.vertices() - segment_1d.vertices()).isZero());
        LineSegment3d product =
            LineSegment1d(1.0 / 3.0, 2.0 / 3.0) * segment_3d.coordinateSystem();
        TS_ASSERT((product.vertex(0) - Vector3d(2, 3, 4)).isZero());
        TS_ASSERT((product.vertex(1) - Vector3d(3, 4, 5)).isZero());
    }

    void testSet() {
        Set<Triangle3d> set;
        Triangle3d first_triangle(
            Vector3d::Zero(),
            Vector3d(1, 0, 0),
            Vector3d(0, 1, 0)
        );
        Triangle3d second_triangle(
            Vector3d(2, 1, 0),
            Vector3d(3, 0, 0),
            Vector3d(3, 1, 0)
        );
        Triangle3d third_triangle(
            Vector3d(0, 0, 1),
            Vector3d(1, 0, 1),
            Vector3d(1, 1, 1)
        );
        set.insert(first_triangle);
        set.insert(second_triangle);
        set.insert(third_triangle);
        std::vector<Triangle3d> overlapping;
        set.copyOverlapping(first_triangle.bounds(), std::back_inserter(overlapping));
        TS_ASSERT_EQUALS(overlapping.size(), 1u);
        TS_ASSERT_EQUALS(overlapping.front(), first_triangle);
    }

    void testVector() {
        LineSegment3d line_segment(Vector3d(1, 2, 3), Vector3d(4, 5, 6));
        TS_ASSERT((line_segment.vector() - Vector3d::Constant(3)).isZero());
    }

    void testBoostGeometry() {
        LineSegment3d segment3d(Vector3d(1, 1, 1), Vector3d(4, 5, 6));
        TS_ASSERT(boost::geometry::length(segment3d) - segment3d.length() == Zero());
        //LineSegment2d segment1(Vector2d::Zero(), Vector2d(2, 0));
        //LineSegment2d segment2(Vector2d(1, 1), Vector2d(1, 3));
        //LineSegment2d segment3(Vector2d(0, 1), Vector2d(2, 3));
        //TS_ASSERT(!boost::geometry::intersects(segment1, segment2));
        //TS_ASSERT(boost::geometry::intersects(segment2, segment3));
    }
};
