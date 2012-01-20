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

#ifndef OPENSOLID__ERROR_HPP
#define OPENSOLID__ERROR_HPP

#include <OpenSolid/config.hpp>

#include <string>
#include <iostream>
#include <map>
#include <cassert>
#include <exception>

#include <boost/lexical_cast.hpp>

#include <OpenSolid/Common/Convertible.hpp>

namespace OpenSolid
{
    class Error : public std::exception
    {
    private:
        /// ID specifying the type of error.
        int _id;

        /// Additional data about the cause of the error.
        std::map<std::string, std::string> _data;
        mutable std::string _what;
    public:
        OPENSOLID_CORE_EXPORT Error();
        
        OPENSOLID_CORE_EXPORT ~Error() throw ();

        OPENSOLID_CORE_EXPORT int id() const;
        
        template <class Type>
        Error& set(const std::string& key, const Type& value);
        
        OPENSOLID_CORE_EXPORT bool has(const std::string& key) const;
        
        template <class Type>
        Type get(const std::string& key) const;

        OPENSOLID_CORE_EXPORT const char* what() const override;
    };

    template <int code_>
    struct ErrorCode;

    template <class ErrorType>
    struct Conversion<ErrorType, Error>
    {
        Error operator()(const ErrorType& argument) const;
    };

    template <class ErrorType>
    struct Conversion<Error, ErrorType>
    {
        ErrorType operator()(const Error& argument) const;
    };

    class ConversionToStringError
    {
    public:
        static const int error_code = 23;
        ConversionToStringError(const Error& error);
    };

    template <>
    struct ErrorCode<23>
    {
        typedef ConversionToStringError ErrorType;
    };

    class ConversionFromStringError
    {
    public:
        static const int error_code = 24;
        ConversionFromStringError(const Error& error);
    };

    template <>
    struct ErrorCode<24>
    {
        typedef ConversionFromStringError ErrorType;
    };
    
    OPENSOLID_CORE_EXPORT std::ostream& operator<<(std::ostream& stream, const Error& error);
}

////////// Implementation //////////

namespace OpenSolid
{
    template <int id_>
    Error::Error(const Check<id_>&) : _id(id_), _data(), _what() {}

    template <class Type>
    Error& Error::set(const std::string& key, const Type& value) {
        std::string string = Check<23>::ValidConversionToString(value);
        _data[key] = string;
        return *this;
    }
    
    template <class Type>
    Type Error::get(const std::string& key) const {
        auto position = _data.find(key);
        if (position == _data.end()) {
            return Type();
        } else {
            return Check<24>::ValidConversionFromString<Type>(position->second);
        }
    }

    template <class ErrorType>
    Error Conversion<ErrorType, Error>::operator()(const ErrorType& argument) const {
        static_assert(std::is_same<ErrorType, ErrorCode<ErrorType::error_code>::ErrorType>::value);
        return argument;
    }

    template <class ErrorType>
    ErrorType Conversion<Error, ErrorType>::operator()(const Error& argument) const {
        static_assert(std::is_same<ErrorType, ErrorCode<ErrorType::error_code>::ErrorType>::value);
        return ErrorType(argument);
    }

    template <class Type>
    std::string Check<23>::ValidConversionToString(const Type& value) {
        try {
            return boost::lexical_cast<std::string>(value);
        } catch (const boost::bad_lexical_cast&) {
            throw Error(Check());
        }
    }

    template <class Type>
    Type Check<24>::ValidConversionFromString(const std::string& string) {
        try {
            return boost::lexical_cast<Type>(string);
        } catch (const boost::bad_lexical_cast&) {
            throw Error(Check()).set("string", string);
        }
    }
}

#endif
