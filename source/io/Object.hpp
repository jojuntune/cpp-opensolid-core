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

#include "config.hpp"
#include "Error.hpp"
#include "Conversion.hpp"

#include <boost/variant.hpp>

#include <string>
#include <unordered_map>

namespace opensolid
{
    class Object : public Convertible<Object>
    {
    public:
    private:
        std::unordered_map<int, int> _map_int_int;
        std::unordered_map<int, double> _map_int_double;
        std::unordered_map<int, std::string> _map_int_string;
        std::unordered_map<int, Object> _map_int_object;
        std::unordered_map<std::string, int> _map_string_int;
        std::unordered_map<std::string, double> _map_string_double;
        std::unordered_map<std::string, std::string> _map_string_string;
        std::unordered_map<std::string, Object> _map_string_object;
        
        friend class Conversion<Object, std::string>;
    public:
        OPENSOLID_IO_EXPORT Object();

        OPENSOLID_IO_EXPORT bool has(const Key& key) const;
        
        OPENSOLID_IO_EXPORT Object& set(const Key& key, const Value& value) const;
        
        template <class Type>
        Type get(const Key& key) const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TypeName<Object>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class ObjectKeyError : public Error
    {
    private:
        Object _object;
        Object::Key _key;
    public:
        OPENSOLID_CORE_EXPORT ObjectKeyError(
            const Object& object,
            const std::string& key,
            const std::string& requested_type
        );
        
        ~ObjectGetValueError() throw () {}

        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
        OPENSOLID_CORE_EXPORT Object object() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    void Object::setValue(const std::string& key, const Type& value) {_map[key] = value;}

    template <class Type>
    void Object::getValue(const std::string& key, Type& value) const {
        if (const Type* result = boost::get<Type>(&_map.at(key))) {
            value = *result;
        } else {
            throw ObjectGetValueError(*this, key, TypeName<Type>()());
        }
    }
}

#endif
