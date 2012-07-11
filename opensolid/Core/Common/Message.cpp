
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

#include <OpenSolid/Core/Common/Message.hpp>
#include <OpenSolid/Core/Common/Value.hpp>
#include <OpenSolid/Core/Common/List.hpp>
#include <OpenSolid/Core/Common/serialization.pb.h>

namespace opensolid
{
    std::string TypeName<Message>::operator()() const {return "Message";}

    void serialize(const Value& argument, serialized::Value* result);
    void serialize(const List& argument, serialized::List* result);

    struct ValueSerializationVisitor
    {
        typedef void result_type;

        serialized::Value* _result;

        ValueSerializationVisitor(serialized::Value* result) : _result(result) {}

        inline void operator()(int argument) const {_result->set_int_value(argument);}

        inline void operator()(double argument) const {_result->set_double_value(argument);}

        inline void operator()(const std::string& argument) const {
            _result->set_string_value(argument);
        }

        void operator()(const List& argument) const {
            serialize(argument, _result->mutable_list_value());
        }
    };

    void serialize(const Value& argument, serialized::Value* result) {
        argument.accept(ValueSerializationVisitor(result));
    }

    void serialize(const List& argument, serialized::List* result) {
        std::for_each(
            argument.begin(),
            argument.end(),
            [result] (const Value& item) {
                serialized::Value* temp = result->add_item();
                serialize(item, temp);
            }
        );
    }

    Message Conversion<Value, Message>::operator()(const Value& argument) const {
        serialized::Value temp;
        serialize(argument, &temp);
        return temp.SerializeAsString();
    }

    Value deserialized(const serialized::Value& argument);
    List deserialized(const serialized::List& argument);

    Value deserialized(const serialized::Value& argument) {
        if (argument.has_int_value()) {
            return argument.int_value();
        } else if (argument.has_double_value()) {
            return argument.double_value();
        } else if (argument.has_string_value()) {
            return argument.string_value();
        } else if (argument.has_list_value()) {
            return deserialized(argument.list_value());
        } else {
            return Value();
        }
    }

    List deserialized(const serialized::List& argument) {
        List result;
        for (int i = 0; i < argument.item_size(); ++i) {
            result.append(deserialized(argument.item(i)));
        }
        return result;
    }

    Value Conversion<Message, Value>::operator()(const Message& message) const {
        serialized::Value temp;
        temp.ParseFromString(message);
        return deserialized(temp);
    }
}