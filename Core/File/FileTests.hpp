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

#include <cstdio>

#include <cxxtest/TestSuite.h>

#include <OpenSolid/Core/File/File.hpp>

using namespace OpenSolid;

class FileTests : public CxxTest::TestSuite
{
public:
    void testFile() {
        std::remove("test.db");
        File file("test.db");

        file.open("rw");
        file.set("vector", Vector3d(1, 2, 3));
        file.set("interval", Interval(4, 5));
        file.close();

        file.open("r");
        Vector3d vector = file.get<Vector3d>("vector");
        Interval interval = file.get<Interval>("interval");
        file.close();

        TS_ASSERT_EQUALS(vector, Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(interval.lower(), 4);
        TS_ASSERT_EQUALS(interval.upper(), 5);
    }
};
