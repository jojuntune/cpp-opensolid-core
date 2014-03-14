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
************************************************************************************/

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

#include <cxxtest/TestSuite.h>

#include <typeinfo>
#include <vector>

using namespace opensolid;

class PositionTests : public CxxTest::TestSuite
{
public:
    void testTransformed() {
        Point3d point(3, 2, 1);
        TS_ASSERT((point.rotatedAbout(Axis3d::Z(), M_PI / 2) - Point3d(-2, 3, 1)).isZero());
        TS_ASSERT((point.rotatedAbout(Axis3d::X(), M_PI / 2) - Point3d(3, -1, 2)).isZero());
        TS_ASSERT((point.mirroredAbout(Plane3d::YZ()) - Point3d(-3, 2, 1)).isZero());
    }

    void testPoint() {
        Point3d point1(1, 2, 3);
        Point3d point2(Vector3d(1, 2, 3));
        Point3d point3(4, 5, 6);
        Point3d origin = Point3d::Origin();
        TS_ASSERT((point1 - point2).isZero());
        TS_ASSERT(origin.components().isZero());
        TS_ASSERT(origin.isOrigin());
        TS_ASSERT((point1 + Vector3d(3, 3, 3) - point3).isZero());
        TS_ASSERT((point1.rotatedAbout(Axis3d::X(), M_PI / 2) - Point3d(1, -3, 2)).isZero());
    }

    void testBox() {
        Box3d box1(Interval(1, 2), Interval(3, 4), Interval(5, 6));
        Box3d projected = box1.projectedOnto(Plane3d::YZ());
        TS_ASSERT(projected.x().lowerBound() == Zero());
        TS_ASSERT(projected.x().upperBound() == Zero());
        TS_ASSERT(projected.y().lowerBound() - box1.y().lowerBound() == Zero());
        TS_ASSERT(projected.y().upperBound() - box1.y().upperBound() == Zero());
        TS_ASSERT(projected.z().lowerBound() - box1.z().lowerBound() == Zero());
        TS_ASSERT(projected.z().upperBound() - box1.z().upperBound() == Zero());
    }

    void testMixedOperations() {
        Point3d point(1, 2, 3);
        Box3d box(Interval(1, 2), Interval(3, 4), Interval(5, 6));
        IntervalVector3d difference1 = point - box;
        IntervalVector3d difference2 = box - point;
        Box3d reconstructed1 = point - difference1;
        Box3d reconstructed2 = point + difference2;
        for (int i = 0; i < 3; ++i) {
            TS_ASSERT(reconstructed1(i).lowerBound() - box(i).lowerBound() == Zero());
            TS_ASSERT(reconstructed1(i).upperBound() - box(i).upperBound() == Zero());
            TS_ASSERT(reconstructed2(i).lowerBound() - box(i).lowerBound() == Zero());
            TS_ASSERT(reconstructed2(i).upperBound() - box(i).upperBound() == Zero());
        }
    }

    void testDistance() {
        Point2d point2d(0, 2);
        Axis2d axis2d(Point2d(1, 1), Vector2d(1, 1).normalized());
        TS_ASSERT(point2d.distanceTo(axis2d) - sqrt(2.0) == Zero());

        Point3d point3d(2, 2, 0);
        Plane3d plane3d(Point3d(0, 0, 1), Vector3d(-1, -1, 1).normalized());
        TS_ASSERT(point3d.distanceTo(plane3d) + 5.0 / sqrt(3.0) == Zero());
    }

    void testboxVertices() {
        Box3d box(Interval(1, 2), Interval(3, 4), Interval(5, 6));
        auto pointIsContained = [&box] (const Point3d& point) {
            return box.contains(point);
        };
        auto pointIsStrictlyContained = [&box] (const Point3d& point) {
            return box.strictlyContains(point);
        };
        TS_ASSERT(box.vertices().all(pointIsContained));
        TS_ASSERT(!box.vertices().any(pointIsStrictlyContained));

        Box3d computedBox = box.vertices().fold(
            Box3d(),
            [] (const Box3d& result, const Point3d& point) {
                return result.hull(point);
            }
        );
        TS_ASSERT(computedBox.contains(box));
        TS_ASSERT(box.contains(computedBox));

        TS_ASSERT(box.vertex(0) == box.minVertex());
        TS_ASSERT(box.vertex(7) == box.maxVertex());
    }

    void testBoxInterpolation() {
        Box3d box(Interval(1, 2), Interval(3, 4), Interval(5, 6));
        TS_ASSERT((box.interpolated(0.5, 0.5, 0.5) - Point3d(1.5, 3.5, 5.5)).isZero());
        TS_ASSERT((box.interpolated(0.0, 0.0, 0.0) - Point3d(1, 3, 5)).isZero());
        Box3d wholeBox = box.interpolated(Interval::Unit(), Interval::Unit(), Interval::Unit());
        TS_ASSERT(wholeBox.contains(box));
        TS_ASSERT(box.contains(wholeBox));
    }

    void testPointPredicates2d() {
        Axis2d axis(Point2d(1, 1), Vector2d(2, 1).normalized());
        LineSegment2d lineSegment(Point2d(0, 1), Point2d(1, 0));

        TS_ASSERT(Point2d(3, 2).isOn(axis));
        TS_ASSERT(!Point2d(3, 3).isOn(axis));

        TS_ASSERT(Point2d(0.5, 0.5).isOn(lineSegment));
        TS_ASSERT(Point2d(0, 1).isOn(lineSegment));
        TS_ASSERT(!Point2d(-1, 2).isOn(lineSegment));
        TS_ASSERT(!Point2d(1, 1).isOn(lineSegment));
    }

    void testPointPredicates3d() {
        Axis3d axis(Point3d(1, 1, 1), Vector3d(1, 2, 3).normalized());
        Plane3d plane(Point3d(0, 1, 1), Vector3d(0, 1, 1).normalized());
        LineSegment3d lineSegment(Point3d(0, 0, 1), Point3d(1, 1, 0));
        Triangle3d triangle(Point3d(1, 0, 0), Point3d(0, 1, 0), Point3d(0, 0, 1));

        TS_ASSERT(Point3d(2, 3, 4).isOn(axis));
        TS_ASSERT(!Point3d(2, 3, 5).isOn(axis));

        TS_ASSERT(Point3d(0, 0, 2).isOn(plane));
        TS_ASSERT(!Point3d::Origin().isOn(plane));

        TS_ASSERT(lineSegment.midpoint().isOn(lineSegment));
        TS_ASSERT(lineSegment.endVertex().isOn(lineSegment));
        Point3d extendedPoint(2, 2, -1);
        TS_ASSERT(extendedPoint.isOn(lineSegment.axis()));
        TS_ASSERT(!extendedPoint.isOn(lineSegment));

        TS_ASSERT(triangle.centroid().isOn(triangle));
        TS_ASSERT(triangle.vertex(1).isOn(triangle));
        Point3d planarPoint(-1, 0, 2);
        TS_ASSERT(planarPoint.isOn(triangle.plane()));
        TS_ASSERT(!planarPoint.isOn(triangle));
        TS_ASSERT(!Point3d(1, 1, 1).isOn(triangle));
    }
};
