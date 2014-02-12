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
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

#include <cxxtest/TestSuite.h>

using namespace opensolid;

class DatumTests : public CxxTest::TestSuite
{
public:
    void testAxisPlaneIntersection() {
        Plane3d plane(Point3d(1, 1, 1), Vector3d(1, 1, 1).normalized());
        Axis3d crossingAxis(Point3d(0, -1, 0), Vector3d(1, 0, 1).normalized());
        Axis3d coincidentAxis(Point3d(3, 0, 0), Vector3d(-1, 1, 0).normalized());
        Axis3d offsetAxis(Point3d(-1, -1, 0), Vector3d(-1, -1, 2).normalized());

        auto crossingIntersection = crossingAxis.intersection(plane);
        TS_ASSERT(crossingIntersection.exists());
        TS_ASSERT(crossingIntersection.isPoint());
        TS_ASSERT(!crossingIntersection.isCoincident());
        TS_ASSERT(crossingIntersection.point().distanceTo(plane) == Zero());

        auto coincidentIntersection = coincidentAxis.intersection(plane);
        TS_ASSERT(coincidentIntersection.exists());
        TS_ASSERT(coincidentIntersection.isCoincident());
        TS_ASSERT(!coincidentIntersection.isPoint());

        auto offsetIntersection = offsetAxis.intersection(plane);
        TS_ASSERT(!offsetIntersection.exists());
        TS_ASSERT(!offsetIntersection.isPoint());
    }
};
