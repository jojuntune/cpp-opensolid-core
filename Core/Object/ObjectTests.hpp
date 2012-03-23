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
        TS_ASSERT_THROWS(object.get<int>("c"), ObjectPropertyError);
    }

    void testSerialization() {
        Object object;
        object.set("value", 1.0);
        object.set("vector", Vector3d(1, 2, 3));
        Object component;
        component.set("axis", Axis3d(Vector3d::Zero(), Vector3d(4, 5, 6)));
        component.set("facet", Triangle3d(Matrix3d::Ones()));
        object.set("component", component);
        Serialization<Object> serialization;
        std::string serialized = serialization(object);
        Deserialization<Object> deserialization;
        Object deserialized = deserialization(serialized);
        TS_ASSERT_EQUALS(deserialized.get<double>("value"), 1.0);
        TS_ASSERT_EQUALS(deserialized.get<Vector3d>("vector"), Vector3d(1, 2, 3));
        Axis3d axis = deserialized.get<Object>("component").get<Axis3d>("axis");
        TS_ASSERT_EQUALS(axis.origin(), Vector3d::Zero());
        TS_ASSERT((axis.direction() - Vector3d(4, 5, 6).normalized()).isZero());
        Triangle3d facet = deserialized.get<Object>("component").get<Triangle3d>("facet");
        TS_ASSERT_EQUALS(facet.vertices(), Matrix3d::Ones());
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
};
