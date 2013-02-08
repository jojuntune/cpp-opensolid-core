/*************************************************************************************
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
 *************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <exception>
#include <cstdio>

namespace opensolid
{
    template <int iNumber = 0>
    class Error;

    template <int iNumber>
    struct UniqueErrorNumber;

    template <>
    class Error<0> : public std::exception
    {
    private:
        char _buffer[32];
        int _number;
    
        template <int iNumber>
        Error(UniqueErrorNumber<iNumber>);
    
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

    typedef Error<1> NotImplementedError;
    template <> struct UniqueErrorNumber<1> {};
}

namespace opensolid
{
    template <int iNumber>
    Error<0>::Error(UniqueErrorNumber<iNumber>) : _number(iNumber) {
        sprintf(_buffer, "OpenSolid error %i", iNumber);
    }

    template <int iNumber>
    inline Error<iNumber>::Error() : Error<>(UniqueErrorNumber<iNumber>()) {
    }
}
