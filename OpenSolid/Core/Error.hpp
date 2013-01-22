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

#include <OpenSolid/config.hpp>

#include <exception>
#include <cstdio>

namespace opensolid
{
    template <int iNumber = 0>
    class Error;

    template <>
    class Error<0> : public std::exception
    {
    private:
        char _buffer[32];
        int _number;
    
        OPENSOLID_CORE_EXPORT Error(int number);
    
        template <int iNumber> friend class Error;
    public:
        OPENSOLID_CORE_EXPORT const char* what() const throw();
        OPENSOLID_CORE_EXPORT int number() const;
    };

    template <int iNumber>
    class Error : public Error<>
    {
    public:
        static const int Number = iNumber;
    
        Error();
    };

    template <int iNumber>
    struct UniqueErrorNumber;

    typedef Error<1> NotImplementedError;
    template <> struct UniqueErrorNumber<1> {};
}

namespace opensolid
{
    template <int iNumber>
    inline Error<iNumber>::Error() : Error<>(iNumber) {
        UniqueErrorNumber<iNumber> checkForUniqueErrorNumberSpecialization;
    }
}
