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

    class TypeDescription
    {
    public:
        static const int MAX_SIZE = 20;

        class Item
        {
        private:
            std::string _type_name;
            bool _is_list;
            std::string _name;
        public:
            Item(const std::string& type_name, bool is_list, const std::string& name) :
                _type_name(type_name), _is_list(is_list), _name(name) {}

            const std::string& typeName() const {return _type_name;}

            bool isList() const {return _is_list;}

            const std::string& name() const {return _name;}
        };
    private:
        std::vector<Item> _items;

        OPENSOLID_CORE_EXPORT TypeDescription& addItem(
            const std::string& type_name,
            bool is_list,
            const std::string& name
        );
    public:
        typedef std::vector<Item>::const_iterator Iterator;

        OPENSOLID_CORE_EXPORT TypeDescription& addInt(const std::string& name);
        OPENSOLID_CORE_EXPORT TypeDescription& addDouble(const std::string& name);
        OPENSOLID_CORE_EXPORT TypeDescription& addString(const std::string& name);
        
        template <class Type>
        TypeDescription& addObject(const std::string& name);

        OPENSOLID_CORE_EXPORT TypeDescription& addListOfInts(const std::string& name);
        OPENSOLID_CORE_EXPORT TypeDescription& addListOfDoubles(const std::string& name);
        OPENSOLID_CORE_EXPORT TypeDescription& addListOfStrings(const std::string& name);
        
        template <class Type>
        TypeDescription& addListOfObjects(const std::string& name);

        OPENSOLID_CORE_EXPORT bool isEmpty() const;
        OPENSOLID_CORE_EXPORT int size() const;

        OPENSOLID_CORE_EXPORT const std::string& typeName(int index) const;
        OPENSOLID_CORE_EXPORT bool isList(int index) const;
        OPENSOLID_CORE_EXPORT const std::string& name(int index) const;

        OPENSOLID_CORE_EXPORT Iterator begin() const;
        OPENSOLID_CORE_EXPORT Iterator end() const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class TypeDescriptionError : public Error
    {
    private:
        TypeDescription _type_description;
    public:
        OPENSOLID_CORE_EXPORT TypeDescriptionError(const TypeDescription& type_description);

        OPENSOLID_CORE_EXPORT TypeDescription typeDescription() const;
    };

    class TypeDescriptionSizeError : public TypeDescriptionError
    {
    private:
        int _max_size;
    public:
        OPENSOLID_CORE_EXPORT TypeDescriptionSizeError(
            const TypeDescription& type_description,
            int max_size
        );

        OPENSOLID_CORE_EXPORT int maxSize() const;

        OPENSOLID_CORE_EXPORT const char* what() const override;
    };

    class TypeDescriptionIndexError : public TypeDescriptionError
    {
    private:
        int _index;
    public:
        OPENSOLID_CORE_EXPORT TypeDescriptionIndexError(
            const TypeDescription& type_description,
            int index
        );

        OPENSOLID_CORE_EXPORT int index() const;

        OPENSOLID_CORE_EXPORT const char* what() const override;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TypeName<TypeDescription>
    {
        OPENSOLID_CORE_EXPORT const std::string& operator()() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    TypeDescription& TypeDescription::addObject(const std::string& name) {
        static const std::string type_name = TypeName<Type>()();
        return addItem(type, false, name);
    }

    template <class Type>
    TypeDescription& TypeDescription::addListOfObjects(const std::string& name) {
        static const std::string type_name = TypeName<Type>()();
        return addItem(type_name, true, name);
    }
}
