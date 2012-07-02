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

#pragma once

#include <OpenSolid/Core/Common/Value.hpp>
#include <OpenSolid/Core/Generic/Conversion.hpp>
#include <OpenSolid/Core/Generic/TypeName.hpp>
#include <OpenSolid/Core/config.hpp>

#include <string>

namespace opensolid
{
    class Message : public std::string, public Convertible<Message>
    {
    public:
        Message(const std::string& argument);
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TypeName<Message>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct Conversion<Value, Message>
    {
        OPENSOLID_CORE_EXPORT Message operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Message, Value>
    {
        OPENSOLID_CORE_EXPORT Value operator()(const Message& argument) const;
    };

    template <class Type>
    struct Conversion<Type, Message>
    {
        Message operator()(const Type& argument) const;
    };

    template <class Type>
    struct Conversion<Message, Type>
    {
        Type operator()(const Message& argument) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Message::Message(const std::string& argument) : std::string(argument) {}

    template <class Type>
    Message Conversion<Type, Message>::operator()(const Type& argument) const {
        return Conversion<Value, Message>()(Conversion<Type, Value>()(argument));
    }

    template <class Type>
    Type Conversion<Message, Type>::operator()(const Message& argument) const {
        return Conversion<Value, Type>()(Conversion<Message, Value>()(argument));
    }
}
