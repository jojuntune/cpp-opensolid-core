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

#include <string>
#include <iostream>
#include <map>
#include <cassert>

#include <boost/lexical_cast.hpp>

#include <OpenSolid/config.hpp>

namespace OpenSolid
{
    class Erro
    {
    private:
        std::string _expected;
        std::string _caller;
        std::map<std::string, std::string> _data;

        friend OPENSOLID_CORE_EXPORT std::ostream& operator<<(
            std::ostream& stream,
            const Error& erro
        );
    public:
        OPENSOLID_CORE_EXPORT Error();
        OPENSOLID_CORE_EXPORT Error(const std::string& expected, const std::string& caller);
        OPENSOLID_CORE_EXPORT ~Error() throw ();

        OPENSOLID_CORE_EXPORT std::string expected() const;
        OPENSOLID_CORE_EXPORT std::string caller() const;
        
        template <class Type>
        Error& set(const std::string& name, const Type& argument);
        
        OPENSOLID_CORE_EXPORT bool has(const std::string& name) const;
        
        template <class Type>
        Type get(const std::string& name) const;
    };
    
    OPENSOLID_CORE_EXPORT std::ostream& operator<<(std::ostream& stream, const Error& error);
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class Type>
    Error& Error::set(const std::string& name, const Type& argument) {
        _data[name] = boost::lexical_cast<std::string>(argument);
        return *this;
    }
    
    template <class Type>
    Type Error::get(const std::string& name) const {
        std::map<std::string, std::string>::const_iterator position = _data.find(name);
        assert(position != _data.end());
        return boost::lexical_cast<Type>(position->second);
    }
}

#endif
