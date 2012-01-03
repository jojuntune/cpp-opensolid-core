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

namespace OpenSolid
{
    template <int id_>
    struct Check;

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

        template <int id_>
        explicit Error(const Check<id_>&);
        
        OPENSOLID_CORE_EXPORT ~Error() throw ();

        OPENSOLID_CORE_EXPORT int id() const;
        
        template <class Type>
        Error& set(const std::string& key, const Type& value);
        
        OPENSOLID_CORE_EXPORT bool has(const std::string& key) const;
        
        template <class Type>
        Type get(const std::string& key) const;

        OPENSOLID_CORE_EXPORT const char* what() const override;
    };

    /// Check that an object can be converted to a string.
    template <>
    struct Check<23>
    {
        /// Perform the actual check.
        template <class Type>
        static std::string ValidConversionToString(const Type& value);
    };
    
    /// Check that a string can be converted to an object of specified type.
    template <>
    struct Check<24>
    {
        /// Perform the actual check.
        template <class Type>
        static Type ValidConversionFromString(const std::string& value);
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
