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

#pragma once

#include <opensolid/config.hpp>

#include <exception>
#include <string>

namespace opensolid
{
    class Error : public std::exception
    {
    };

    class NotImplementedError : public Error
    {
    private:
        std::string _file;
        int _line;
    public:
        OPENSOLID_CORE_EXPORT NotImplementedError(const std::string& file, int line);
        
        OPENSOLID_CORE_EXPORT ~NotImplementedError() throw ();

        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
        OPENSOLID_CORE_EXPORT std::string file() const;
        OPENSOLID_CORE_EXPORT int line() const;
    };
}
