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

#include <OpenSolid/Core/Common/Error.hpp>
#include <OpenSolid/Core/Generic/Conversion.hpp>
#include <OpenSolid/Core/Generic/TypeName.hpp>
#include <OpenSolid/Core/config.hpp>

#include <boost/variant.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace opensolid
{
    class List;

    class Value : public Convertible<Value>
    {
    private:
        boost::variant<
            int,
            double,
            std::string,
            boost::recursive_wrapper<List>
        > _value;

        template <class Type>
        const Type& extract() const;

        template <class Type, class ExtractedType>
        Type convert() const;

        template <class Type, class OtherType>
        friend struct Conversion;
    public:
        OPENSOLID_CORE_EXPORT Value();

        OPENSOLID_CORE_EXPORT Value(bool argument);
        OPENSOLID_CORE_EXPORT Value(short argument);
        OPENSOLID_CORE_EXPORT Value(unsigned short argument);
        OPENSOLID_CORE_EXPORT Value(int argument);
        OPENSOLID_CORE_EXPORT Value(unsigned argument);
        OPENSOLID_CORE_EXPORT Value(long argument);
        OPENSOLID_CORE_EXPORT Value(unsigned long argument);
        OPENSOLID_CORE_EXPORT Value(long long argument);
        OPENSOLID_CORE_EXPORT Value(unsigned long long argument);

        OPENSOLID_CORE_EXPORT Value(float argument);
        OPENSOLID_CORE_EXPORT Value(double argument);
        OPENSOLID_CORE_EXPORT Value(long double argument);
        
        OPENSOLID_CORE_EXPORT Value(const char* argument);
        OPENSOLID_CORE_EXPORT Value(const std::string& argument);

        OPENSOLID_CORE_EXPORT Value(const List& argument);

        template <class Type>
        Value(const Type& argument);

        OPENSOLID_CORE_EXPORT void operator=(bool argument);
        OPENSOLID_CORE_EXPORT void operator=(short argument);
        OPENSOLID_CORE_EXPORT void operator=(unsigned short argument);
        OPENSOLID_CORE_EXPORT void operator=(int argument);
        OPENSOLID_CORE_EXPORT void operator=(unsigned argument);
        OPENSOLID_CORE_EXPORT void operator=(long argument);
        OPENSOLID_CORE_EXPORT void operator=(unsigned long argument);
        OPENSOLID_CORE_EXPORT void operator=(long long argument);
        OPENSOLID_CORE_EXPORT void operator=(unsigned long long argument);

        OPENSOLID_CORE_EXPORT void operator=(float argument);
        OPENSOLID_CORE_EXPORT void operator=(double argument);
        OPENSOLID_CORE_EXPORT void operator=(long double argument);
        
        OPENSOLID_CORE_EXPORT void operator=(const char* argument);
        OPENSOLID_CORE_EXPORT void operator=(const std::string& argument);

        OPENSOLID_CORE_EXPORT void operator=(const List& argument);

        template <class Type>
        void operator=(const Type& argument);

        template <class VisitorType>
        typename VisitorType::result_type accept(const VisitorType& visitor) const;

        OPENSOLID_CORE_EXPORT std::string type() const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class ValueConversionError : public Error
    {
    private:
        Value _value;
        std::string _expected_type;
    public:
        OPENSOLID_CORE_EXPORT ValueConversionError(const Value& value, const std::string& expected_type);

        OPENSOLID_CORE_EXPORT Value value() const;
        OPENSOLID_CORE_EXPORT std::string expectedType() const;

        OPENSOLID_CORE_EXPORT const char* what() const override;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TypeName<Value>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct Conversion<Value, bool>
    {
        OPENSOLID_CORE_EXPORT bool operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, short>
    {
        OPENSOLID_CORE_EXPORT short operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, unsigned short>
    {
        OPENSOLID_CORE_EXPORT unsigned short operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, int>
    {
        OPENSOLID_CORE_EXPORT int operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, unsigned>
    {
        OPENSOLID_CORE_EXPORT unsigned operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, long>
    {
        OPENSOLID_CORE_EXPORT long operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, unsigned long>
    {
        OPENSOLID_CORE_EXPORT unsigned long operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, long long>
    {
        OPENSOLID_CORE_EXPORT long long operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, unsigned long long>
    {
        OPENSOLID_CORE_EXPORT unsigned long long operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, float>
    {
        OPENSOLID_CORE_EXPORT float operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, double>
    {
        OPENSOLID_CORE_EXPORT double operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, long double>
    {
        OPENSOLID_CORE_EXPORT long double operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, std::string>
    {
        OPENSOLID_CORE_EXPORT const std::string& operator()(const Value& argument) const;
    };

    template <>
    struct Conversion<Value, List>
    {
        OPENSOLID_CORE_EXPORT const List& operator()(const Value& argument) const;
    };

    template <class Type>
    struct Conversion<Value, Type>
    {
        Type operator()(const Value& argument) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    inline const Type& Value::extract() const {
        if (const Type* extracted = boost::get<Type>(&_value)) {
            return *extracted;
        } else {
            throw ValueConversionError(*this, TypeName<Type>()());
        }
    }

    template <class Type, class ExtractedType>
    inline Type Value::convert() const {
        if (const ExtractedType* extracted = boost::get<ExtractedType>(&_value)) {
            // Disable warning about casting integer types to bool
            #pragma warning(disable: 4800)
            return Type(*extracted);
        } else {
            throw ValueConversionError(*this, TypeName<Type>()());
        }
    }

    template <class Type>
    Value::Value(const Type& argument) : _value(Conversion<Type, List>()(argument)) {}

    template <class Type>
    void Value::operator=(const Type& argument) {_value = Conversion<Type, List>()(argument);}

    template <class VisitorType>
    typename VisitorType::result_type Value::accept(const VisitorType& visitor) const {
        return boost::apply_visitor(visitor, _value);
    }

    template <class Type>
    Type Conversion<Value, Type>::operator()(const Value& argument) const {
        return Conversion<List, Type>()(argument.as<List>());
    }
}

#include <OpenSolid/Core/Common/List.hpp>
