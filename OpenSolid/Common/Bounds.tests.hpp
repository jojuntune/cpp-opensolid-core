/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <cxxtest/TestSuite.h>

#include <OpenSolid/Common/Bounds.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>
#include <OpenSolid/Simplex/Simplex.hpp>
#include <OpenSolid/Set/Set.hpp>

using namespace OpenSolid;

class BoundsTestSuite : public CxxTest::TestSuite
{
public:
    void testPair() {
        Triangle3d first_triangle(
            Vector3d::Zero(),
            Vector3d(1, 0, 0),
            Vector3d(0, 1, 0)
        );
        Triangle3d second_triangle(
            Vector3d(1, 1, 1),
            Vector3d(2, 0, 1),
            Vector3d(2, 1, 1)
        );
        auto pair = std::make_pair(first_triangle, second_triangle);
        Set<decltype(pair)> set;
        set.insert(pair);
        Vector3I bounds = set.bounds();
        TS_ASSERT(bounds.cwiseLower().isApprox(Vector3d(0, 0, 0)));
        TS_ASSERT(bounds.cwiseUpper().isApprox(Vector3d(2, 1, 1)));
    }

    void testList() {
        Vector2d first_vector = Vector2d::Zero();
        Vector2d second_vector(1, 2);
        Vector2d third_vector(3, 1);
        std::list<Vector2d> first_list;
        first_list.push_back(first_vector);
        first_list.push_back(second_vector);
        std::list<Vector2d> second_list;
        second_list.push_back(third_vector);
        Set<std::list<Vector2d>> set;
        set.insert(first_list);
        set.insert(second_list);
        Vector2I bounds = set.bounds();
        TS_ASSERT(bounds.cwiseLower().isApprox(Vector2d(0, 0)));
        TS_ASSERT(bounds.cwiseUpper().isApprox(Vector2d(3, 2)));
    }

    void testVector() {
        std::vector<double> first_vector(3);
        first_vector[0] = 2;
        first_vector[1] = 1;
        first_vector[2] = 3;
        std::vector<double> second_vector;
        Set<std::vector<double>> set;
        set.insert(first_vector);
        set.insert(second_vector);
        Interval bounds = set.bounds();
        TS_ASSERT(bounds.lower() == One());
        TS_ASSERT(bounds.upper() == Approx(3));
    }
};
