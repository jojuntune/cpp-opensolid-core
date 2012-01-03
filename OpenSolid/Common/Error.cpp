/*****************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                     *
 *   ian.e.mackenzie@gmail.com                                               *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <algorithm>

#include <OpenSolid/Common/Error.hpp>

namespace OpenSolid
{
    Error::Error() : _id(0), _data(), _what() {}

    Error::~Error() throw () {}

    int Error::id() const {return _id;}

    bool Error::has(const std::string& key) const {return _data.find(key) != _data.end();}

    const char* Error::what() const {
        std::stringstream stream;
        stream << "Error " << id();
        if (!_data.empty()) {
            auto iterator = _data.begin();
            stream << ": " << iterator->first << " = " << iterator->second;
            ++iterator;
            std::for_each(
                iterator,
                _data.end(),
                [&] (const std::pair<std::string, std::string>& key_value_pair) {
                    stream << ", " << key_value_pair.first << " = " << key_value_pair.second;
                }
            );
        }
        _what = stream.str();
        return _what.c_str();
    }
    
    std::ostream& operator<<(std::ostream& stream, const Error& error) {
        stream << error.what();
        return stream;
    }
}
