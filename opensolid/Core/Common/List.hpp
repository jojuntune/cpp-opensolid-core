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

#include <OpenSolid/Core/Common/Value.hpp>
#include <OpenSolid/Core/config.hpp>

#include <vector>

namespace opensolid
{
    class List : public Convertible<List>
    {
    private:
        std::vector<Value> _list;
    public:
        typedef std::vector<Value>::const_iterator Iterator;

        OPENSOLID_CORE_EXPORT List();

        template <class IteratorType>
        List(IteratorType begin, IteratorType end);

        OPENSOLID_CORE_EXPORT List& append(const Value& argument);

        OPENSOLID_CORE_EXPORT int size() const;
        OPENSOLID_CORE_EXPORT const Value& operator[](int index) const;

        OPENSOLID_CORE_EXPORT Iterator begin() const;
        OPENSOLID_CORE_EXPORT Iterator end() const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class ListIndexError
    {
    private:
        List _list;
        int _index;
    public:
        OPENSOLID_CORE_EXPORT ListIndexError(const List& list, int index);

        OPENSOLID_CORE_EXPORT const List& list() const;
        OPENSOLID_CORE_EXPORT int index() const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TypeName<List>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class IteratorType>
    List::List(IteratorType begin, IteratorType end) : _list(begin, end) {}
}
