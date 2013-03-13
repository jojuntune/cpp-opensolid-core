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
    template <int iErrorNumber = 0>
    class Error;

    template <int iErrorNumber>
    struct UniqueErrorNumber;

    template <>
    class Error<0> : public std::exception
    {
    private:
        int _errorNumber;
    
        template <int iErrorNumber>
        Error(UniqueErrorNumber<iErrorNumber>);
    
        template <int iErrorNumber> friend class Error;
    public:
        int errorNumber() const;
    };

    template <int iErrorNumber>
    class Error : public Error<>
    {
    public:
        static const int ErrorNumber = iErrorNumber;
    
        Error();
    };

    class FeatureNotImplemented : public Error<1>
    {
        const char* what() const throw() {
            return "FeatureNotImplemented";
        }
    };

    template <> struct UniqueErrorNumber<FeatureNotImplemented::ErrorNumber> {};
}

namespace opensolid
{
    template <int iErrorNumber>
    Error<0>::Error(UniqueErrorNumber<iErrorNumber>) :
        _errorNumber(iErrorNumber) {
    }

    inline int
    Error<0>::errorNumber() const {
        return _errorNumber;
    }

    template <int iErrorNumber>
    inline Error<iErrorNumber>::Error() :
        Error<>(UniqueErrorNumber<iErrorNumber>()) {
    }
}
