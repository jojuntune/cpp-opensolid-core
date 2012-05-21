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

#include <OpenSolid/Core/Common/Conversion.hpp>
#include <OpenSolid/Core/Common/Error.hpp>
#include <OpenSolid/Core/Common/TypeName.hpp>
#include <OpenSolid/Core/config.hpp>

#include <boost/variant.hpp>

#include <string>
#include <functional>

namespace opensolid
{
    class Key
    {
    private:
        boost::variant<int, std::string> _key;
    public:
        Key(int key);
        Key(const std::string& key);

        bool operator==(const Key& other) const;

        template <class VisitorType>
        typename VisitorType::result_type apply(const VisitorType& visitor) const;
    };
}

////////// Specializations //////////

namespace std
{
    template <>
    struct hash<opensolid::Key>
    {
        size_t operator()(const opensolid::Key& key) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Key::Key(int key) : _key(key) {}

    inline Key::Key(const std::string& key) : _key(key) {}

    inline bool Key::operator==(const Key& other) const {return _key == other._key;}

    template <class VisitorType>
    typename VisitorType::result_type Key::apply(const VisitorType& visitor) const {
        return boost::apply_visitor(visitor, _key);
    }
}

namespace std
{
    size_t hash<opensolid::Key>::operator()(const opensolid::Key& key) const {
        struct HashVisitor
        {
            typedef std::size_t result_type;

            std::size_t operator()(int key) const {
                return std::hash<int>()(key);
            }

            std::size_t operator()(const std::string& key) const {
                return std::hash<std::string>()(key);
            }
        };
        return key.apply(HashVisitor());
    }
}
