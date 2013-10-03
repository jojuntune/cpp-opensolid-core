/************************************************************************************
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

#include <OpenSolid/Core/Error.hpp>

namespace opensolid
{
    Error::Error(ErrorConditionBase* condition) :
        _condition(condition),
        _code(condition->errorCode()),
        _what(condition->name()) {
    }

    Error::Error(const ErrorConditionPtr& condition) :
        _condition(condition),
        _code(condition->errorCode()),
        _what(condition->name()) {
    }

    const ErrorConditionPtr&
    Error::condition() const {
        return _condition;
    }

    int
    Error::code() const {
        return _code;
    }

    const char*
    Error::what() const throw() {
        return _what.c_str();
    }

    int
    ErrorConditionBase::errorCode() const {
        return _errorCode;
    }

    std::string
    PlaceholderError::name() const {
        return "PlaceholderError";
    }

    std::string
    FeatureNotImplemented::name() const {
        return "FeatureNotImplemented";
    }
}
