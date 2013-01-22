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

using namespace opensolid;

class FileTests : public CxxTest::TestSuite
{
public:
    void testFile() {
        std::string filename = "FileTests.testFile.db";
        std::remove(filename.c_str());

        {
            File save_file(filename, "rw");
            save_file.set("vector", Vector3d(1, 2, 3));
            save_file.set("interval", Interval(4, 5));
            save_file.set("value", M_PI);
        }

        File load_file(filename, "r");
        Vector3d vector = load_file.get<Vector3d>("vector");
        Interval interval = load_file.get<Interval>("interval");
        double value = load_file.get<double>("value");

        TS_ASSERT_EQUALS(vector, Vector3d(1, 2, 3));
        TS_ASSERT_EQUALS(interval.lowerBound(), 4);
        TS_ASSERT_EQUALS(interval.upperBound(), 5);
        TS_ASSERT_EQUALS(value, M_PI);
    }

    void testFileErrors() {
        std::string filename = "FileTests.testFileErrors.db";
        std::remove(filename.c_str());

        {
            File save_file(filename, "rw");
            save_file.set("vector", Vector3d(1, 2, 3));
        }

        File load_file(filename, "r");
        TS_ASSERT_THROWS(load_file.set("one", 1.0), FileSetValueError);
        TS_ASSERT_THROWS(load_file.get<Vector2d>("vector"), FileGetValueError);
        TS_ASSERT_EQUALS(load_file.get<Vector3d>("vector"), Vector3d(1, 2, 3));
    }
};
