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

#include <OpenSolid/Core/Object/Object.hpp>

using namespace OpenSolid;

class ObjectTests : public CxxTest::TestSuite
{
public:
    void testTransformation() {
        Object object;
        object.set("vector", Vector3d(1, 2, 3));
        Object translated = object.translated(Vector3d::Ones());
        TS_ASSERT(translated.has("vector"));
        TS_ASSERT((Vector3d(2, 3, 4) - translated.get<Vector3d>("vector")).isZero());
    }

    void testProperty() {
        Object object;
        object.set("a", 1.0);
        object.set("b", Interval(2, 5));
        TS_ASSERT(object.has("a"));
        TS_ASSERT(object.has("b"));
        TS_ASSERT(!object.has("c"));
        TS_ASSERT_EQUALS(object.get<double>("a"), 1.0);
        TS_ASSERT_EQUALS(object.get<Interval>("b").upper(), 5.0);
        TS_ASSERT_THROWS(object.get<int>("c"), ObjectPropertyError);
    }
};
