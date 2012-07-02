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

#include <OpenSolid/Core/Generic/TypeName.hpp>
#include <OpenSolid/Core/Object/Object.hpp>

namespace opensolid
{
    Object::Object() {}

    bool Object::has(const std::string& key) const {return _map.find(key) != _map.end();}

    Value& Object::operator[](const std::string& key) {return _map[key];}

    const Value& Object::operator[](const std::string& key) const {
        std::unordered_map<std::string, Value>::const_iterator iterator = _map.find(key);
        if (iterator == _map.end()) {throw ObjectGetError(*this, key);}
        return iterator->second;
    }

    Object::Iterator Object::begin() const {return _map.begin();}

    Object::Iterator Object::end() const {return _map.end();}

    std::string TypeName<Object>::operator()() const {return "OpenSolidObject";}

    ObjectGetError::ObjectGetError(const Object& object, const std::string& key) :
        _object(object), _key(key) {}

    const char* ObjectGetError::what() const throw() {
        return "ObjectGetError";
    }

    Object ObjectGetError::object() const {return _object;}

    std::string ObjectGetError::key() const {return _key;}

}
