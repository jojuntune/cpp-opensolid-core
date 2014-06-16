/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#include <cxxtest/TestSuite.h>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/IO/Object.hpp>

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
        std::string operator()() const {
            return "CustomType";
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
        TS_ASSERT_EQUALS(object.get<Interval>("b").upperBound(), 5.0);
        TS_ASSERT_THROWS(object.get<int>("c"), ObjectGetValueError);
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
        TS_ASSERT_EQUALS(object.get<Object>("custom").get<double>("value"), original.value);
        TS_ASSERT_EQUALS(object.get<Object>("custom").get<Vector3d>("vector"), original.vector);
        CustomType reconstructed = object.get<CustomType>("custom");
        TS_ASSERT_EQUALS(reconstructed.value, original.value);
        TS_ASSERT_EQUALS(reconstructed.vector, original.vector);
    }
};
