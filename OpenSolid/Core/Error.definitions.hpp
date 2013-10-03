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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Error.declarations.hpp>

#include <exception>
#include <memory>
#include <string>

namespace opensolid
{
    typedef std::shared_ptr<ErrorConditionBase> ErrorConditionPtr;

    class Error :
        public std::exception
    {
    private:
        ErrorConditionPtr _condition;
        int _code;
        std::string _what;
    public:
        OPENSOLID_CORE_EXPORT
        Error(ErrorConditionBase* condition);

        OPENSOLID_CORE_EXPORT
        Error(const ErrorConditionPtr& condition);

        OPENSOLID_CORE_EXPORT
        const ErrorConditionPtr&
        condition() const;

        OPENSOLID_CORE_EXPORT
        int
        code() const;

        OPENSOLID_CORE_EXPORT
        const char*
        what() const throw() override;
    };

    class ErrorConditionBase
    {
    private:
        int _errorCode;
    protected:
        template <int iErrorCode>
        ErrorConditionBase(UniqueErrorCode<iErrorCode>);
    public:
        OPENSOLID_CORE_EXPORT
        int
        errorCode() const;

        OPENSOLID_CORE_EXPORT
        virtual std::string
        name() const = 0;
    };

    template <int iErrorCode>
    class ErrorCondition :
        public ErrorConditionBase
    {
    public:
        static const int ErrorCode = iErrorCode;
    protected:
        ErrorCondition();
    };

    class PlaceholderError :
        public ErrorCondition<0>
    {
    public:
        OPENSOLID_CORE_EXPORT
        std::string
        name() const override;
    };

    template <> struct UniqueErrorCode<PlaceholderError::ErrorCode> {};

    class FeatureNotImplemented :
        public ErrorCondition<1>
    {
    public:
        OPENSOLID_CORE_EXPORT
        std::string
        name() const override;
    };

    template <> struct UniqueErrorCode<FeatureNotImplemented::ErrorCode> {};
}
