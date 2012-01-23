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

        /// Buffer for error message returned from what().
        mutable char _what[32];
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

    class ConversionToStringError
    {
    public:
        static const int error_code = 23;

        ConversionToStringError(const Error& error);
    };

    class ConversionFromStringError
    {
    public:
        static const int error_code = 24;

        ConversionFromStringError(const Error& error);
    };
    
    OPENSOLID_CORE_EXPORT std::ostream& operator<<(std::ostream& stream, const Error& error);
}

////////// Implementation //////////

namespace OpenSolid
{
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
}

#endif
