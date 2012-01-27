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

#include <OpenSolid/Error/Error.hpp>

namespace OpenSolid
{
    Error::Error() : _implementation(), _what() {}

    Error::Error(const ErrorImplementation* implementation) :
        _implementation(implementation), _what() {}

    const ErrorImplementation* Error::implementation() const {return _implementation.get();}

    const char* Error::what() const {
        _what = _implementation->what();
        return _what.c_str();
    }
    
    std::ostream& operator<<(std::ostream& stream, const Error& error) {
        stream << error.what();
        return stream;
    }
}
