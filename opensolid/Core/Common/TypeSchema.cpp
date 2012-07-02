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

#include <OpenSolid/Core/Common/TypeSchema.hpp>

namespace opensolid
{
    bool TypeSchema::isEmpty() const {return _schema.empty();}

    int TypeSchema::size() const {return _schema.size();}

    const std::string& TypeSchema::name(int index) const {
        if (index < 0 || index >= size()) {throw SchemaIndexError(*this, index);}
        return _schema[index].first;
    }

    const std::string& TypeSchema::type(int index) const {
        if (index < 0 || index >= size()) {throw SchemaIndexError(*this, index);}
        return _schema[index].second;
    }

    TypeSchema::Iterator TypeSchema::begin() const {return _schema.begin();}

    TypeSchema::Iterator TypeSchema::end() const {return _schema.end();}

    SchemaIndexError::SchemaIndexError(const TypeSchema& schema, int index) :
        _schema(schema), _index(index) {}

    TypeSchema SchemaIndexError::schema() const {return _schema;}

    int SchemaIndexError::index() const {return _index;}

    std::string TypeName<TypeSchema>::operator()() const {return "TypeSchema";}
}
