/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef OPENSOLID__SERIALIZATION_HPP
#define OPENSOLID__SERIALIZATION_HPP

#include <string>

#include <OpenSolid/Core/config.hpp>

namespace opensolid
{
    template <class Type>
    struct Serialization;

    template <>
    struct Serialization<bool>
    {
        std::string operator()(bool argument) const;
    };

    template <>
    struct Serialization<int>
    {
        std::string operator()(int argument) const;
    };

    template <>
    struct Serialization<double>
    {
        OPENSOLID_CORE_EXPORT std::string operator()(double argument) const;
    };

    template <>
    struct Serialization<std::string>
    {
        const std::string& operator()(const std::string& argument) const;
    };
}

////////// Implementation //////////

#include <boost/lexical_cast.hpp>

namespace opensolid
{
    inline std::string Serialization<bool>::operator()(bool argument) const {
        return boost::lexical_cast<std::string>(argument);
    }

    inline std::string Serialization<int>::operator()(int argument) const {
        return boost::lexical_cast<std::string>(argument);
    }

    inline const std::string& Serialization<std::string>::operator()(
        const std::string& argument
    ) const {return argument;}
}

#endif
