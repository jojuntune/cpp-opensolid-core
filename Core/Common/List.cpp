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

#include <OpenSolid/Core/Common/List.hpp>

namespace opensolid
{
    List::List() {}

    List& List::append(const Value& argument) {
        _list.push_back(argument);
        return *this;
    }
    
    int List::size() const {return _list.size();}

    const Value& List::operator[](int index) const {
        if (index < 0 || index > size()) {throw ListIndexError(*this, index);}
        return _list[index];
    }

    List::Iterator List::begin() const {return _list.begin();}

    List::Iterator List::end() const {return _list.end();}

    ListIndexError::ListIndexError(const List& list, int index) : _list(list), _index(index) {}

    const List& ListIndexError::list() const {return _list;}

    int ListIndexError::index() const {return _index;}

    std::string TypeName<List>::operator()() const {return "List";}
}
