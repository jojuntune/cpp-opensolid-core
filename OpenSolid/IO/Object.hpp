/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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
*************************************************************************************/

#pragma once
 
#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Error.hpp>

#include <string>
#include <memory>
#include <cstdint>

namespace opensolid
{
    class Object : public Convertible<Object>
    {
    private:
        struct Data;

        std::auto_ptr<Data> m_data;

        OPENSOLID_IO_EXPORT void clear(const std::string& key);
        OPENSOLID_IO_EXPORT void append(const std::string& key, std::int64_t value);
        OPENSOLID_IO_EXPORT void append(const std::string& key, double value);
        OPENSOLID_IO_EXPORT void append(const std::string& key, const std::string& value);
        OPENSOLID_IO_EXPORT void append(const std::string& key, const Object& value);

        template <class Type>
        Type getItem(const std::string& key, std::int64_t index, const Type& default_value) const;
    public:
        enum ItemType {NO_ITEM, MULTIPLE_ITEMS, INT_ITEM, DOUBLE_ITEM, STRING_ITEM, OBJECT_ITEM};

        OPENSOLID_IO_EXPORT Object();
        OPENSOLID_IO_EXPORT Object(const Object& other);

        template <class Type>
        Object(const Type& argument);

        OPENSOLID_IO_EXPORT Object& operator=(const Object& other);
        
        OPENSOLID_IO_EXPORT Object& set(const std::string& key, std::int64_t value);
        OPENSOLID_IO_EXPORT Object& set(const std::string& key, double value);
        OPENSOLID_IO_EXPORT Object& set(const std::string& key, const std::string& value);
        OPENSOLID_IO_EXPORT Object& set(const std::string& key, const Object& value);

        template <class Iterator>
        Object& set(const std::string& key, Iterator begin, Iterator end);

        OPENSOLID_IO_EXPORT bool has(const std::string& key) const;
        OPENSOLID_IO_EXPORT std::int64_t size(const std::string& key) const;

        OPENSOLID_IO_EXPORT std::int64_t getInt(const std::string& key, std::int64_t index = 0) const;
        OPENSOLID_IO_EXPORT double getDouble(const std::string& key, std::int64_t index = 0) const;
        OPENSOLID_IO_EXPORT std::string getString(const std::string& key, std::int64_t index = 0) const;
        OPENSOLID_IO_EXPORT Object getObject(const std::string& key, std::int64_t index = 0) const;
        
        template <class Type>
        Type get(const std::string& key, std::int64_t index = 0) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    Object::Object(const Type& argument) {
        *this = Conversion<Type, Object>(argument);
    }
    
    template <class Iterator>
    Object& Object::set(const std::string& key, Iterator begin, Iterator end) {
        clear(key);
        for (Iterator iterator = begin; iterator != end; ++iterator) {append(key, *iterator);}
        return *this;
    }
        
    template <class Type>
    Type Object::get(const std::string& key, std::int64_t index) const {
        return getObject(key, index).as<Type>();
    }
}
