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
#include <OpenSolid/Core/Common/Value.hpp>
#include <OpenSolid/Core/Generic/TypeName.hpp>
#include <OpenSolid/Core/Generic/Conversion.hpp>
#include <OpenSolid/Core/config.hpp>

#include <string>
#include <unordered_map>

namespace opensolid
{
    class Object : public Convertible<Object>
    {
    private:
        std::unordered_map<std::string, Value> _map;
    public:
        typedef std::unordered_map<std::string, Value>::const_iterator Iterator;

        OPENSOLID_CORE_EXPORT Object();

        OPENSOLID_CORE_EXPORT bool has(const std::string& key) const;

        OPENSOLID_CORE_EXPORT Value& operator[](const std::string& key);
        OPENSOLID_CORE_EXPORT const Value& operator[](const std::string& key) const;

        OPENSOLID_CORE_EXPORT Iterator begin() const;
        OPENSOLID_CORE_EXPORT Iterator end() const;
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
    class ObjectGetError : public Error
    {
    private:
        Object _object;
        std::string _key;
    public:
        OPENSOLID_CORE_EXPORT ObjectGetError(
            const Object& object,
            const std::string& key
        );
        
        ~ObjectGetError() throw () {}

        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
        OPENSOLID_CORE_EXPORT Object object() const;
        OPENSOLID_CORE_EXPORT std::string key() const;
    };
}
