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

#include <OpenSolid/Core/Common/TypeDescription.hpp>
#include <OpenSolid/Core/Common/List.hpp>

namespace opensolid
{
    TypeDescription& TypeDescription::addItem(
        const std::string& type_name,
        bool is_list,
        const std::string& name
    ) {
        _items.push_back(Item(type_name, is_list, name));
        if (_items.size() > MAX_SIZE) {throw TypeDescriptionSizeError(*this, MAX_SIZE);}
        return *this;
    }

    TypeDescription& TypeDescription::addInt(const std::string& name) {
        static const std::string type_name = TypeName<int>()();
        return addItem(type_name, false, name);
    }

    TypeDescription& TypeDescription::addDouble(const std::string& name) {
        static const std::string type_name = TypeName<double>()();
        return addItem(type_name, false, name);
    }

    TypeDescription& TypeDescription::addString(const std::string& name) {
        static const std::string type_name = TypeName<std::string>()();
        return addItem(type_name, false, name);
    }

    TypeDescription& TypeDescription::addListOfInts(const std::string& name) {
        static const std::string type_name = TypeName<int>()();
        return addItem(type_name, true, name);
    }

    TypeDescription& TypeDescription::addListOfDoubles(const std::string& name) {
        static const std::string type_name = TypeName<double>()();
        return addItem(type_name, true, name);
    }

    TypeDescription& TypeDescription::addListOfStrings(const std::string& name) {
        static const std::string type_name = TypeName<std::string>()();
        return addItem(type_name, true, name);
    }

    bool TypeDescription::isEmpty() const {return _items.empty();}

    int TypeDescription::size() const {return _items.size();}

    const std::string& TypeDescription::typeName(int index) const {
        if (index < 0 || index >= size()) {throw TypeDescriptionIndexError(*this, index);}
        return _items[index].typeName();
    }

    bool TypeDescription::isList(int index) const {
        if (index < 0 || index >= size()) {throw TypeDescriptionIndexError(*this, index);}
        return _items[index].isList();
    }

    const std::string& TypeDescription::name(int index) const {
        if (index < 0 || index >= size()) {throw TypeDescriptionIndexError(*this, index);}
        return _items[index].name();
    }

    TypeDescription::Iterator TypeDescription::begin() const {return _items.begin();}

    TypeDescription::Iterator TypeDescription::end() const {return _items.end();}

    TypeDescriptionError::TypeDescriptionError(const TypeDescription& type_description) :
        _type_description(type_description) {}

    TypeDescription TypeDescriptionError::typeDescription() const {return _type_description;}

    TypeDescriptionSizeError::TypeDescriptionSizeError(const TypeDescription& schema, int max_size) :
        TypeDescriptionError(schema), _max_size(max_size) {}

    int TypeDescriptionSizeError::maxSize() const {return _max_size;}

    TypeDescriptionIndexError::TypeDescriptionIndexError(const TypeDescription& schema, int index) :
        TypeDescriptionError(schema), _index(index) {}

    int TypeDescriptionIndexError::index() const {return _index;}

    const std::string& TypeName<TypeDescription>::operator()() const {
        const static std::string result("TypeDescription");
        return result;
    }
}
