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

#include <sstream>
#include <iostream>

#include "Error.hpp"

namespace OpenSolid
{
    Error::Error() : _expected(""), _caller("") {}
    
    Error::Error(const std::string& expected, const std::string& caller) :
        _expected(expected), _caller(caller) {}

    Error::~Error() throw () {}

    std::string Error::expected() const {return _expected;}
    
    std::string Error::caller() const {return _caller;}

    bool Error::has(const std::string& name) const {return _data.find(name) != _data.end();}
    
    std::ostream& operator<<(std::ostream& stream, const Error& error) {
        stream << "Error(\"" << error.expected() << "\", \"" << error.caller() << "\")";
        return stream;
    }
}
