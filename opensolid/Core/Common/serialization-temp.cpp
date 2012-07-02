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

#include <OpenSolid/Core/Common/Key.hpp>
#include <OpenSolid/Core/Common/Value.hpp>
#include <OpenSolid/Core/Object/Object.hpp>

#include <OpenSolid/Core/Common/serialization.pb.h>

namespace opensolid
{
    ////////// Key //////////

    template <>
    struct Conversion<serialized::Key, std::string>
    {
        std::string operator()(const serialized::Key& argument) const {
            return argument.SerializeAsString();
        }
    };

    template <>
    struct Conversion<std::string, serialized::Key>
    {
        serialized::Key operator()(const std::string& argument) const {
            serialized::Key result;
            result.ParseFromString(argument);
            return result;
        }
    };

    template <>
    struct Conversion<Key, serialized::Key>
    {
        struct Visitor
        {
            typedef serialized::Key result_type;

            serialized::Key operator()(int64_t key) const {
                serialized::Key result;
                result.set_int_key(key);
                return result;
            }

            serialized::Key operator()(const std::string& key) const {
                serialized::Key result;
                result.set_string_key(key);
                return result;
            }
        };

        serialized::Key operator()(const Key& argument) {return argument.accept(Visitor());}
    };

    template <>
    struct Conversion<serialized::Key, Key>
    {
        Key operator()(const serialized::Key& argument) const {
            if (argument.has_int_key()) {
                return argument.int_key();
            } else {
                return argument.string_key();
            }
        }
    };

    std::string Conversion<Key, std::string>::operator()(const Key& argument) const {
        return Conversion<Key, serialized::Key>()(argument).SerializeAsString();
    }

    Key Conversion<std::string, Key>::operator()(const std::string& argument) const {
        serialized::Key temp = Conversion<std::string, serialized::Key>()(argument);
        return Conversion<serialized::Key, Key>()(temp);
    }

    ////////// Value //////////

    template <>
    struct Conversion<serialized::Value, std::string>
    {
        std::string operator()(const serialized::Value& argument) const {
            return argument.SerializeAsString();
        }
    };

    template <>
    struct Conversion<std::string, serialized::Value>
    {
        serialized::Value operator()(const std::string& argument) const {
            serialized::Value result;
            result.ParseFromString(argument);
            return result;
        }
    };

    template <>
    struct Conversion<Value, serialized::Value>
    {
        struct Visitor
        {
            typedef serialized::Value result_type;

            serialized::Value operator()(int64_t value) const {
                serialized::Value result;
                result.set_int_value(value);
                return result;
            }

            serialized::Value operator()(double value) const {
                serialized::Value result;
                result.set_double_value(value);
                return result;
            }

            serialized::Value operator()(const std::string& value) const {
                serialized::Value result;
                result.set_string_value(value);
                return result;
            }

            serialized::Value operator()(const Object& value) const {
                serialized::Value result;
                *result.mutable_object_value() = value.as<serialized::Object>();
                return result;
            }
        };

        serialized::Value operator()(const Value& argument) {return argument.accept(Visitor());}
    };

    template <>
    struct Conversion<serialized::Value, Value>
    {
        Value operator()(const serialized::Value& argument) const {
            if (argument.has_int_value()) {
                return argument.int_value();
            } else if (argument.has_double_value()) {
                return argument.double_value();
            } else if (argument.has_string_value()) {
                return argument.string_value();
            } else {
                return Object::from(argument.object_value());
            }
        }
    };

    std::string Conversion<Value, std::string>::operator()(const Value& argument) const {
        return Conversion<Value, serialized::Value>()(argument).SerializeAsString();
    }

    Value Conversion<std::string, Value>::operator()(const std::string& argument) const {
        serialized::Value temp = Conversion<std::string, serialized::Value>()(argument);
        return Conversion<serialized::Value, Value>()(temp);
    }

    ////////// Object //////////

    template <>
    struct Conversion<serialized::Object, std::string>
    {
        std::string operator()(const serialized::Object& argument) const {
            return argument.SerializeAsString();
        }
    };

    template <>
    struct Conversion<std::string, serialized::Object>
    {
        serialized::Object operator()(const std::string& argument) const {
            serialized::Object result;
            result.ParseFromString(argument);
            return result;
        }
    };

    template <>
    struct Conversion<Object, serialized::Object>
    {
        serialized::Object operator()(const Object& argument) const {
            serialized::Object result;
            Conversion<Key, serialized::Key> key_serializer;
            Conversion<Value, serialized::Value> value_serializer;
            std::for_each(
                argument.begin(),
                argument.end(),
                [&] (const std::pair<const Key, const Value>& key_value_pair) {
                    serialized::KeyValuePair* temp = result.add_key_value_pair();
                    *temp->mutable_key() = key_serializer(key_value_pair.first);
                    *temp->mutable_value() = value_serializer(key_value_pair.second);
                }
            );
            return result;
        }
    };

    template <>
    struct Conversion<serialized::Object, Object>
    {
        Object operator()(const serialized::Object& argument) const {
            Object result;
            Conversion<serialized::Key, Key> key_deserializer;
            Conversion<serialized::Value, Value> value_deserializer;
            for (int i = 0; i < argument.key_value_pair_size(); ++i) {
                Key key = key_deserializer(argument.key_value_pair(i).key());
                Value value = value_deserializer(argument.key_value_pair(i).value());
                result.set(key, value);
            }
            return result;
        }
    };

    std::string Conversion<Object, std::string>::operator()(const Object& argument) const {
        return Conversion<Object, serialized::Object>()(argument).SerializeAsString();
    }

    Object Conversion<std::string, Object>::operator()(const std::string& argument) const {
        serialized::Object temp = Conversion<std::string, serialized::Object>()(argument);
        return Conversion<serialized::Object, Object>()(temp);
    }

}
