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

namespace opensolid
{
    template <int iErrorNumber>
    struct UniqueErrorNumber;

    template <int iErrorNumber>
    class NumberedError;

    class Error : public std::exception
    {
    private:
        int _errorNumber;
    
        template <int iErrorNumber>
        Error(UniqueErrorNumber<iErrorNumber>);
    
        template <int iErrorNumber> friend class NumberedError;
    public:
        int errorNumber() const;
    };

    template <int iErrorNumber>
    class NumberedError : public Error
    {
    public:
        static const int ErrorNumber = iErrorNumber;
    protected:
        NumberedError();
    };

    class FeatureNotImplemented : public NumberedError<1>
    {
    public:
        const char* what() const throw() override {
            return "Feature not implemented";
        }
    };

    template <> struct UniqueErrorNumber<FeatureNotImplemented::ErrorNumber> {};
}

////////// Implementation //////////

namespace opensolid
{
    template <int iErrorNumber>
    Error::Error(UniqueErrorNumber<iErrorNumber>) :
        _errorNumber(iErrorNumber) {
    }

    inline int
    Error::errorNumber() const {
        return _errorNumber;
    }

    template <int iErrorNumber>
    NumberedError<iErrorNumber>::NumberedError() :
        Error(UniqueErrorNumber<iErrorNumber>()) {
    }
}
