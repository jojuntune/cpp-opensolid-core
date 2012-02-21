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
    void testObject() {
        Object object;
        TS_ASSERT(!object.hasValue());
        object = Interval(2, 3);
        TS_ASSERT(object.hasValue());
        TS_ASSERT_EQUALS(object.as<Interval>().lower(), 2);
        TS_ASSERT_EQUALS(object.as<Interval>().upper(), 3);
    }

    void testTransformation() {
        Object object;
        object = Interval(2, 3);
        object.set("vector", Vector3d(1, 2, 3));
        Object translated = object.translated(Vector3d::Ones());
        TS_ASSERT(translated.has("vector"));
        TS_ASSERT_EQUALS(translated.as<Interval>().lower(), 2);
        TS_ASSERT_EQUALS(translated.as<Interval>().upper(), 3);
        TS_ASSERT((Vector3d(2, 3, 4) - translated.get("vector").as<Vector3d>()).isZero());
    }

    void testConversionError() {
        Object object = 2.0;
        TS_ASSERT_THROWS(object.as<Vector3d>(), ObjectConversionError);
        TS_ASSERT_EQUALS(object.as<double>(), 2.0);
        object = Vector3d(1, 2, 3);
        TS_ASSERT_THROWS(object.as<Vector2d>(), ObjectConversionError);
        TS_ASSERT_EQUALS(object.as<MatrixXd>(), Vector3d(1, 2, 3));
    }

    void testProperty() {
        Object object;
        object.set("a", 1.0);
        object.set("b", Interval(2, 5));
        TS_ASSERT(object.has("a"));
        TS_ASSERT(object.has("b"));
        TS_ASSERT(!object.has("c"));
        TS_ASSERT_EQUALS(object.get("a").as<double>(), 1.0);
        TS_ASSERT_EQUALS(object.get("b").as<Interval>().upper(), 5.0);
        TS_ASSERT_THROWS(object.get("c"), ObjectPropertyError);
    }
};
