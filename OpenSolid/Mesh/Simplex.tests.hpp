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

#include "Simplex.hpp"

using namespace OpenSolid;

class SimplexTestSuite : public CxxTest::TestSuite
{
public:
    void testEdges() {
        Triangle3d triangle(Vector3d::Zero(), Vector3d(1, 0, 1), Vector3d(0, 1, 1));
        std::cout << "EDGES" << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << i << ":" << std::endl;
            std::cout << triangle.edge(i).vertices() << std::endl;
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
    
};
