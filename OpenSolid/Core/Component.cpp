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

#include <OpenSolid/Core/Component.hpp>

#include <OpenSolid/Core/Error.hpp>

namespace opensolid
{
    Component::Component() {
    }

    Component::Component(const Component& other) :
        _map(other._map) {
    }

    Component::Component(Component&& other) :
        _map(std::move(other._map)) {
    }

    bool
    Component::has(const std::string& key) const {
        return _map.find(key) != _map.end();
    }

    const Variant&
    Component::operator[](const std::string& key) const {
        auto iterator = _map.find(key);
        if (iterator == _map.end()) {
            throw PlaceholderError();
        }
        return iterator->second;
    }

    Variant&
    Component::operator[](const std::string& key) {
        return _map[key];
    }

    std::vector<std::string>
    Component::keys() const {
        std::vector<std::string> results;
        results.reserve(_map.size());
        for (auto iterator = _map.begin(); iterator != _map.end(); ++iterator) {
            results.push_back(iterator->first);
        }
        return results;
    }
}
