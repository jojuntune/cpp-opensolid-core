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

#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/Common/Conversion.hpp>
#include <OpenSolid/Core/Object/Object.hpp>

using namespace opensolid;

struct CustomType
{
    double value;
    Vector3d vector;
};

namespace opensolid
{
    template <>
    struct Conversion<CustomType, Object>
    {
        Object operator()(const CustomType& argument) const {
            Object result;
            result.set("value", argument.value);
            result.set("vector", argument.vector);
            return result;
        }
    };

    template <>
    struct Conversion<Object, CustomType>
    {
        CustomType operator()(const Object& argument) const {
            CustomType result;
            result.value = argument.get<double>("value");
            result.vector = argument.get<Vector3d>("vector");
            return result;
        }
    };

    template <>
    struct TypeName<CustomType>
    {
        std::string operator()() const {return "CustomType";}
    };
}

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
        TS_ASSERT_THROWS(object.get<int>("c"), ObjectGetValueError);
    }

    void testCustomConversion() {
        CustomType original;
        original.value = M_PI;
        original.vector = Vector3d::Random();
        Object converted = Object::from<CustomType>(original);
        CustomType reconstructed = converted.as<CustomType>();
        TS_ASSERT_EQUALS(reconstructed.value, original.value);
        TS_ASSERT_EQUALS(reconstructed.vector, original.vector);
    }

    void testIndexedAccess() {
        Object object;
        Vector3d vector(1, 2, 3);
        double value = 4.5;
        object.set(1, vector);
        object.set("2", value);
        TS_ASSERT_EQUALS(object.get<Vector3d>("1"), vector);
        TS_ASSERT_EQUALS(object.get<double>(2), value);
    }

    void testAutomaticConversion() {
        CustomType original;
        original.value = M_PI;
        original.vector = Vector3d::Random();
        Object object;
        object.set("custom", original);
        Object converted = object.get<Object>("custom");
        TS_ASSERT_EQUALS(converted.get<double>("value"), original.value);
        TS_ASSERT_EQUALS(converted.get<Vector3d>("vector"), original.vector);
        CustomType reconstructed = object.get<CustomType>("custom");
        TS_ASSERT_EQUALS(reconstructed.value, original.value);
        TS_ASSERT_EQUALS(reconstructed.vector, original.vector);
    }
};
