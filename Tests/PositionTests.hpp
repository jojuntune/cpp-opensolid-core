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
        TS_ASSERT(origin.vector().isZero());
        TS_ASSERT(origin.isOrigin());
        TS_ASSERT((point1 + Vector3d::Constant(3) - point3).isZero());
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
        Vector3I difference1 = point - box;
        Vector3I difference2 = box - point;
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
};
