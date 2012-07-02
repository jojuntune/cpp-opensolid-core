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
#include <OpenSolid/Core/Generic/TypeName.hpp>
#include <OpenSolid/Core/config.hpp>

#include <vector>
#include <utility>
#include <string>

namespace opensolid
{
    class Object;

    class TypeSchema
    {
    private:
        std::vector<std::pair<std::string, std::string>> _schema;
    public:
        typedef std::vector<std::pair<std::string, std::string>>::const_iterator Iterator;

        template <class Type>
        void addItem(const std::string& name);

        template <class Type>
        void addList(const std::string& name);

        OPENSOLID_CORE_EXPORT bool isEmpty() const;
        OPENSOLID_CORE_EXPORT int size() const;
        OPENSOLID_CORE_EXPORT const std::string& name(int index) const;
        OPENSOLID_CORE_EXPORT const std::string& type(int index) const;

        OPENSOLID_CORE_EXPORT Iterator begin() const;
        OPENSOLID_CORE_EXPORT Iterator end() const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class SchemaIndexError : public Error
    {
    private:
        TypeSchema _schema;
        int _index;
    public:
        OPENSOLID_CORE_EXPORT SchemaIndexError(const TypeSchema& schema, int index);

        OPENSOLID_CORE_EXPORT TypeSchema schema() const;
        OPENSOLID_CORE_EXPORT int index() const;

        OPENSOLID_CORE_EXPORT const char* what() const override;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TypeName<TypeSchema>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    void TypeSchema::addItem(const std::string& name) {
        _schema.push_back(std::pair<std::string, std::string>(name, TypeName<Type>()()));
    }

    template <class Type>
    void TypeSchema::addList(const std::string& name) {
        _schema.push_back(std::pair<std::string, std::string>(name, TypeName<List>()() + ":" + TypeName<Type>()()));
    }
}
