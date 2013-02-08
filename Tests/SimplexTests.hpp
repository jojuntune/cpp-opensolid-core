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

#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Set.hpp>
#include <OpenSolid/Core/Simplex.hpp>
#include <OpenSolid/Core/Tetrahedron.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/Zero.hpp>

#include <cxxtest/TestSuite.h>

using namespace opensolid;

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
        for (int i = 0; i < 4; ++i) {
            Vector3d vertex = tetrahedron.vertex(i);
            Triangle3d face = tetrahedron.face(i);
            TS_ASSERT((vertex - face.centroid()).dot(face.normalVector()) < Zero());
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
        LineSegment2d line(Vector2d(1, 1), Vector2d(3, 2));
        TS_ASSERT((line.normalVector() - Vector2d(-1, 2).normalized()).isZero());
        Triangle3d triangle(Vector3d(1, 1, 1), Vector3d(3, 1, 2), Vector3d(2, 2, 4));
        Vector3d expected_normal = Vector3d(2, 0, 1).cross(Vector3d(1, 1, 3)).normalized();
        TS_ASSERT((triangle.normalVector() - expected_normal).isZero());
    }
    
    void testCoordinateSystem() {
        Triangle3d triangle(Vector3d::Zero(), Vector3d(2, 0, 0), Vector3d(1, 2, 0));
        Datum<3, 2> datum = triangle.datum();
        Vector3d product = datum * Vector2d(0.5, 0.5);
        TS_ASSERT((product - Vector3d(1.5, 1, 0)).isZero());
        Vector2d quotient = Vector3d(1, 0, 0) / datum;
        TS_ASSERT((quotient - Vector2d(0.5, 0)).isZero());
        quotient = Vector3d(3, 2, 0) / datum;
        TS_ASSERT((quotient - Vector2d(1, 1)).isZero());
        Vector3d projection = Vector3d(3, 4, 5).projected(datum);
        TS_ASSERT((projection - Vector3d(3, 4, 0)).isZero());
    }
    
    void testLineSegment1d() {
        LineSegment3d line3d(Vector3d(1, 2, 3), Vector3d(4, 5, 6));
        LineSegment1d quotient = line3d / Frame3d().yAxis();
        LineSegment1d line1d(2, 5);
        TS_ASSERT((quotient.vertices() - line1d.vertices()).isZero());
        LineSegment3d product = line3d.datum() * LineSegment1d(1.0 / 3.0, 2.0 / 3.0);
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
        LineSegment3d line(Vector3d(1, 2, 3), Vector3d(4, 5, 6));
        TS_ASSERT((line.vector() - Vector3d::Constant(3)).isZero());
    }

    void testBoostGeometry() {
        #if BOOST_VERSION >= 104700
        LineSegment3d line(Vector3d(1, 1, 1), Vector3d(4, 5, 6));
        TS_ASSERT(boost::geometry::length(line) - line.length() == Zero());
        //LineSegment2d line1(Vector2d::Zero(), Vector2d(2, 0));
        //LineSegment2d line2(Vector2d(1, 1), Vector2d(1, 3));
        //LineSegment2d line3(Vector2d(0, 1), Vector2d(2, 3));
        //TS_ASSERT(!boost::geometry::intersects(line1, line2));
        //TS_ASSERT(boost::geometry::intersects(line2, line3));
        #endif
    }
};
