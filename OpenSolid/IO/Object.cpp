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
************************************************************************************/

#include <OpenSolid/IO/Object.hpp>

#include <boost/variant.hpp>

#include <unordered_map>

namespace opensolid
{
    typedef boost::variant<std::int64_t, double, std::string, Object> Variant;

    struct Object::Data
    {
        std::unordered_map<std::string, std::vector<Variant>> map;
    };

    void Object::clear(const std::string& key) {m_data->map[key].clear();}

    void Object::append(const std::string& key, std::int64_t value) {
        m_data->map[key].push_back(value);
    }

    void Object::append(const std::string& key, double value) {
        m_data->map[key].push_back(value);
    }

    void Object::append(const std::string& key, const std::string& value) {
        m_data->map[key].push_back(value);
    }

    void Object::append(const std::string& key, const Object& value) {
        m_data->map[key].push_back(value);
    }

    template <class Type>
    Type Object::getItem(const std::string& key, std::int64_t index, const Type& default_value) const {
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

    Object& Object::set(const std::string& key, std::int64_t value) {
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

    bool Object::has(const std::string& key) const {
        return m_data->map.find(key) != m_data->map.end();
    }

    int Object::size(const std::string& key) const {
        auto iterator = m_data->map.find(key);
        if (iterator == m_data->map.end()) {
            assert(false);
            return 0;
        }
        return iterator->second.size();
    }

    std::int64_t Object::getInt(const std::string& key, std::int64_t index) const {
        return getItem<int>(key, index, 0);
    }

    double Object::getDouble(const std::string& key, std::int64_t index) const {
        return getItem<double>(key, index, 0.0);
    }

    std::string Object::getString(const std::string& key, std::int64_t index) const {
        return getItem<std::string>(key, index, std::string());
    }

    Object Object::getObject(const std::string& key, std::int64_t index) const {
        return getItem<Object>(key, index, Object());
    }
}
