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

#include "Conversion.hpp"
#include "TypeName.hpp"

#include <string>

namespace opensolid
{
    class ObjectData;

    class Object : public Convertible<Object>
    {
    private:
        ObjectData* _data;
        
        friend class Conversion<Object, std::string>;
    public:
        OPENSOLID_IO_EXPORT Object();
        OPENSOLID_IO_EXPORT Object(const Object& other);
        OPENSOLID_IO_EXPORT Object(Object&& other);

        OPENSOLID_IO_EXPORT bool has(int key) const;
        OPENSOLID_IO_EXPORT bool has(const std::string& key) const;
        
        OPENSOLID_IO_EXPORT Object& set(int key, int value);
        OPENSOLID_IO_EXPORT Object& set(int key, double value);
        OPENSOLID_IO_EXPORT Object& set(int key, const std::string& value);
        OPENSOLID_IO_EXPORT Object& set(int key, const Object& value);
        
        OPENSOLID_IO_EXPORT Object& set(const std::string& key, int value);
        OPENSOLID_IO_EXPORT Object& set(const std::string& key, double value);
        OPENSOLID_IO_EXPORT Object& set(const std::string& key, const std::string& value);
        OPENSOLID_IO_EXPORT Object& set(const std::string& key, const Object& value);

        template <class Type>
        Object& set(int key, const Type& value);

        template <class Type>
        Object& set(const std::string& key, const Type& value);
        
        template <class Type>
        Type get(int key) const;
        
        template <class Type>
        Type get(const std::string& key) const;
    };

    template <> OPENSOLID_IO_EXPORT int Object::get<int>(int) const;
    template <> OPENSOLID_IO_EXPORT double Object::get<double>(int) const;
    template <> OPENSOLID_IO_EXPORT std::string Object::get<std::string>(int) const;
    template <> OPENSOLID_IO_EXPORT Object Object::get<Object>(int) const;

    template <> OPENSOLID_IO_EXPORT int Object::get<int>(const std::string&) const;
    template <> OPENSOLID_IO_EXPORT double Object::get<double>(const std::string&) const;
    template <> OPENSOLID_IO_EXPORT std::string Object::get<std::string>(const std::string&) const;
    template <> OPENSOLID_IO_EXPORT Object Object::get<Object>(const std::string&) const;
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
    class ObjectKeyError : public std::exception
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
