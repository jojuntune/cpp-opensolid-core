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

#include "List.hpp"

using namespace opensolid;

class ListTestSuite : public CxxTest::TestSuite
{
public:
    void testMatrixAdapter() {
        List<double> doubles(1.0, 2.0, 3.0);
        TS_ASSERT_EQUALS(doubles.matrix().rows(), 1);
        TS_ASSERT_EQUALS(doubles.matrix().cols(), 3);
        TS_ASSERT_EQUALS(doubles.matrix()(0, 1), 2.0);
        TS_ASSERT_EQUALS(doubles.matrix(), RowVector3d(1, 2, 3));
        
        List<Vector3d> vectors(
            Vector3d(1, 2, 3),
            Vector3d(4, 5, 6),
            Vector3d(7, 8, 9)
        );
        Matrix3d matrix = 2 * vectors.matrix().transpose();
        TS_ASSERT_EQUALS(matrix.row(0), RowVector3d(2, 4, 6));
    }
    
    void testListAdapter() {
        Matrix3d matrix;
        matrix << Vector3d(1, 2, 3), Vector3d(4, 5, 6), Vector3d(7, 8, 9);
        List<Vector3d> list = (2 * matrix).list();
        TS_ASSERT_EQUALS(list[1], Vector3d(8, 10, 12));
    }
    
};
