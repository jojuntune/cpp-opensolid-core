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

#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
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
        Triangle3d triangle(Point3d::Origin(), Point3d(1, 0, 1), Point3d(0, 1, 1));

        std::cout << "EDGES" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << i << ":" << std::endl;
            std::cout << triangle.edge(i, (i + 1) % 3).vertices() << std::endl;
        }
    }
    
    void testFaces() {
        Tetrahedron3d tetrahedron(
            Point3d::Origin(),
            Point3d(2, 1, 0),
            Point3d(1, 2, 0),
            Point3d(1, 1, 2)
        );

        for (int i = 0; i < 4; ++i) {
            Point3d vertex = tetrahedron.vertex(i);
            Triangle3d face = tetrahedron.face(i);
            TS_ASSERT((vertex - face.centroid()).dot(face.normalVector()) < Zero());
        }
    }
    
    void testLocalization() {
        Triangle3d triangle3d(Point3d(1, 1, 1), Point3d(3, 1, 2), Point3d(2, 2, 4));
        PlanarCoordinateSystem3d xyCoordinateSystem(
            Point3d::Origin(),
            Vector3d::UnitX(),
            Vector3d::UnitY()
        );
        PlanarCoordinateSystem3d yzCoordinateSystem(
            Point3d::Origin(),
            Vector3d::UnitY(),
            Vector3d::UnitZ()
        );
        PlanarCoordinateSystem3d xzCoordinateSystem(
            Point3d::Origin(),
            Vector3d::UnitX(),
            Vector3d::UnitZ()
        );

        Triangle2d xyComponents = triangle3d / xyCoordinateSystem;
        TS_ASSERT((xyComponents.vertex(0) - Point2d(1, 1)).isZero());
        TS_ASSERT((xyComponents.vertex(1) - Point2d(3, 1)).isZero());
        TS_ASSERT((xyComponents.vertex(2) - Point2d(2, 2)).isZero());
        double xyArea = xyComponents.area();
        TS_ASSERT(xyArea > 0.0);

        Triangle2d yzComponents = triangle3d / yzCoordinateSystem;
        TS_ASSERT((yzComponents.vertex(0) - Point2d(1, 1)).isZero());
        TS_ASSERT((yzComponents.vertex(1) - Point2d(1, 2)).isZero());
        TS_ASSERT((yzComponents.vertex(2) - Point2d(2, 4)).isZero());
        double yzArea = yzComponents.area();
        TS_ASSERT(yzArea < 0.0);

        double xzArea = (triangle3d / xzCoordinateSystem).area();

        double areaFromComponents = sqrt(xyArea * xyArea + yzArea * yzArea + xzArea * xzArea);
        TS_ASSERT(triangle3d.area() - areaFromComponents == Zero());
    }
    
    void testVolumes() {
        Tetrahedron3d tetrahedron(
            Point3d(1, 1, 1),
            Point3d(2, 1, 1),
            Point3d(1, 2, 1),
            Point3d(1, 1, 2)
        );

        TS_ASSERT(tetrahedron.volume() - 1.0 / 6.0 == Zero());
        TS_ASSERT(tetrahedron.face(1).area() - 0.5 == Zero());
        TS_ASSERT(tetrahedron.edge(1, 3).length() - sqrt(2.0) == Zero());
    }
    
    void testTetrahedronCentroid() {
        Tetrahedron3d tetrahedron(
            Point3d(1, 1, 1),
            Point3d(2, 1, 1),
            Point3d(1, 2, 1),
            Point3d(1, 1, 2)
        );
        TS_ASSERT((tetrahedron.centroid() - Point3d(1.25, 1.25, 1.25)).isZero());
    }

    void testTriangleCentroid() {
        Triangle2d triangle(Point2d(1, 1), Point2d(2, 2), Point2d(1, 3));
        TS_ASSERT((triangle.centroid() - Point2d(4.0 / 3.0, 2)).isZero());
    }
    
    void testLineNormal() {
        LineSegment2d line(Point2d(1, 1), Point2d(3, 2));
        TS_ASSERT((line.normalVector() - Vector2d(-1, 2).normalized()).isZero());
    }

    void testTriangleNormal() {
        Triangle3d triangle(Point3d(1, 1, 1), Point3d(3, 1, 2), Point3d(2, 2, 4));
        Vector3d expectedNormal = Vector3d(2, 0, 1).cross(Vector3d(1, 1, 3)).normalized();
        TS_ASSERT((triangle.normalVector() - expectedNormal).isZero());
    }
    
    void testCoordinateSystem() {
        Triangle3d triangle(Point3d::Origin(), Point3d(2, 0, 0), Point3d(1, 2, 0));
        PlanarCoordinateSystem3d coordinateSystem = triangle.coordinateSystem();

        Point3d globalized = coordinateSystem * Point2d(0.5, 0.5);
        TS_ASSERT((globalized - Point3d(1.5, 1, 0)).isZero());

        Point2d localized = Point3d(1, 0, 0) / coordinateSystem;
        TS_ASSERT((localized - Point2d(0.5, 0)).isZero());

        localized = Point3d(3, 2, 0) / coordinateSystem;
        TS_ASSERT((localized - Point2d(1, 1)).isZero());

        Point3d projection = Point3d(3, 4, 5).projectedOnto(triangle.plane());
        TS_ASSERT((projection - Point3d(3, 4, 0)).isZero());
    }
    
    void testLineSegment1d() {
        LineSegment3d lineSegment3d(Point3d(1, 2, 3), Point3d(4, 5, 6));
        AxialCoordinateSystem3d axialCoordinateSystem(Point3d::Origin(), Vector3d::UnitY());
        
        LineSegment1d localized = lineSegment3d / axialCoordinateSystem;
        TS_ASSERT((localized.vertices() - LineSegment1d(2, 5).vertices()).isZero());

        LineSegment3d globalized =
            lineSegment3d.coordinateSystem() * LineSegment1d(1.0 / 3.0, 2.0 / 3.0);
        TS_ASSERT((globalized.vertex(0) - Point3d(2, 3, 4)).isZero());
        TS_ASSERT((globalized.vertex(1) - Point3d(3, 4, 5)).isZero());
    }

    void testSet() {
        std::vector<Triangle3d> triangles(3);
        triangles[0] = Triangle3d(Point3d::Origin(), Point3d(1, 0, 0), Point3d(0, 1, 0));
        triangles[1] = Triangle3d(Point3d(2, 1, 0), Point3d(3, 0, 0), Point3d(3, 1, 0));
        triangles[2] = Triangle3d(Point3d(0, 0, 1), Point3d(1, 0, 1), Point3d(1, 1, 1));

        SpatialSet<Triangle3d> set(triangles);

        std::vector<Triangle3d> overlapping = set.overlapping(triangles[0].bounds());
        TS_ASSERT_EQUALS(overlapping.size(), 1u);
        TS_ASSERT_EQUALS(overlapping.front(), triangles[0]);
    }

    void testVector() {
        LineSegment3d lineSegment(Point3d(1, 2, 3), Point3d(4, 5, 6));
        TS_ASSERT((lineSegment.vector() - Vector3d::Constant(3)).isZero());
    }

    void testScaling() {
        Triangle2d triangle(Point2d(2, 2), Point2d(4, 2), Point2d(3, 3));
        Triangle2d scaled = triangle.scaledAbout(Point2d(1, 1), 2.0);
        TS_ASSERT((scaled.vertex(0) - Point2d(3, 3)).isZero());
        TS_ASSERT((scaled.vertex(1) - Point2d(7, 3)).isZero());
        TS_ASSERT((scaled.vertex(2) - Point2d(5, 5)).isZero());
    }
};
