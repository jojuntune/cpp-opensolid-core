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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Component.declarations.hpp>

#include <OpenSolid/Core/Variant.declarations.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace opensolid
{
    class Component
    {
    private:
        std::unordered_map<std::string, Variant> _map;
    public:
        OPENSOLID_CORE_EXPORT
        Component();

        OPENSOLID_CORE_EXPORT
        Component(const Component& other);

        OPENSOLID_CORE_EXPORT
        Component(Component&& other);

        OPENSOLID_CORE_EXPORT
        bool
        has(const std::string& key) const;

        OPENSOLID_CORE_EXPORT
        const Variant&
        operator[](const std::string& key) const;

        OPENSOLID_CORE_EXPORT
        Variant&
        operator[](const std::string& key);

        OPENSOLID_CORE_EXPORT
        std::vector<std::string>
        keys() const;
    };
}
