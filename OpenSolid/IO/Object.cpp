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

#include <OpenSolid/IO/Object.hpp>

#include <boost/variant.hpp>

#include <unordered_map>

namespace opensolid
{
    typedef boost::variant<int, double, std::string, Object> Variant;

    struct Object::Data
    {
        std::unordered_map<std::string, std::vector<Variant>> map;
    };

    void Object::clear(const std::string& key) {m_data->map[key].clear();}

    template <class Type>
    Type Object::getItem(const std::string& key, int index, const Type& default_value) const {
        auto iterator = m_data->map.find(key);
        // Check if key exists
        if (iterator == m_data->map.end()) {
            assert(false);
            return default_value;
        }
        // Check if index is in range
        if (index < 0 || index >= int(iterator->second.size())) {
            assert(false);
            return default_value;
        }
        // Check if item is of the correct type
        if (Type* result = boost::get<Type>(&iterator->second.front())) {
            return *result;
        } else {
            assert(false);
            return default_value;
        }
    }

    Object::Object() : m_data(new Data()) {}

    Object::Object(const Object& other) : m_data(new Data(*other.m_data)) {}

    Object& Object::operator=(const Object& other) {
        m_data.reset(new Data(*other.m_data));
        return *this;
    }

    Object& Object::set(const std::string& key, int value) {
        clear(key);
        m_data->map[key].push_back(value);
        return *this;
    }

    Object& Object::set(const std::string& key, double value) {
        clear(key);
        m_data->map[key].push_back(value);
        return *this;
    }

    Object& Object::set(const std::string& key, const std::string& value) {
        clear(key);
        m_data->map[key].push_back(value);
        return *this;
    }

    Object& Object::set(const std::string& key, const Object& value) {
        clear(key);
        m_data->map[key].push_back(value);
        return *this;
    }

    Object& Object::append(const std::string& key, int value) {
        m_data->map[key].push_back(value);
        return *this;
    }

    Object& Object::append(const std::string& key, double value) {
        m_data->map[key].push_back(value);
        return *this;
    }

    Object& Object::append(const std::string& key, const std::string& value) {
        m_data->map[key].push_back(value);
        return *this;
    }

    Object& Object::append(const std::string& key, const Object& value) {
        m_data->map[key].push_back(value);
        return *this;
    }

    bool Object::has(const std::string& key) const {
        return m_data->map.find(key) != m_data->map.end();
    }

    int Object::size(const std::string& key) const {
        auto iterator = m_data->map.find(key);
        if (iterator == m_data->map.end()) {
            assert(false);
            return 0;
        } else {
            return iterator->second.size();
        }
    }

    struct ItemTypeVisitor
    {
        typedef Object::ItemType result_type;

        Object::ItemType operator()(int) const {return Object::INT_ITEM;}

        Object::ItemType operator()(double) const {return Object::DOUBLE_ITEM;}

        Object::ItemType operator()(const std::string&) const {return Object::STRING_ITEM;}

        Object::ItemType operator()(const Object&) const {return Object::OBJECT_ITEM;}
    };

    Object::ItemType variantType(const Variant& variant) {
        return boost::apply_visitor(ItemTypeVisitor(), variant);
    }

    Object::ItemType Object::itemType(const std::string& key) const {
        auto iterator = m_data->map.find(key);
        if (iterator == m_data->map.end() || iterator->second.empty()) {
            return NO_ITEM;
        }
        if (iterator->second.size() > 1) {
            return MULTIPLE_ITEMS;
        }
        return boost::apply_visitor(ItemTypeVisitor(), iterator->second.front());
    }

    Object::ItemType Object::itemType(const std::string& key, int index) const {
        auto iterator = m_data->map.find(key);
        if (iterator == m_data->map.end() || iterator->second.empty()) {
            return NO_ITEM;
        }
        if (index < 0 || index >= int(iterator->second.size())) {
            return NO_ITEM;
        }
        return boost::apply_visitor(ItemTypeVisitor(), iterator->second[index]);
    }

    int Object::getInt(const std::string& key) const {
        return getItem<int>(key, 0, 0);
    }

    double Object::getDouble(const std::string& key) const {
        return getItem<double>(key, 0, 0.0);
    }

    std::string Object::getString(const std::string& key) const {
        return getItem<std::string>(key, 0, std::string());
    }

    Object Object::getObject(const std::string& key) const {
        return getItem<Object>(key, 0, Object());
    }

    int Object::getInt(const std::string& key, int index) const {
        return getItem<int>(key, index, 0);
    }

    double Object::getDouble(const std::string& key, int index) const {
        return getItem<double>(key, index, 0.0);
    }

    std::string Object::getString(const std::string& key, int index) const {
        return getItem<std::string>(key, index, std::string());
    }

    Object Object::getObject(const std::string& key, int index) const {
        return getItem<Object>(key, index, Object());
    }
}
