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

#ifndef OPENSOLID__DESERIALIZATION_HPP
#define OPENSOLID__DESERIALIZATION_HPP

#include <string>

#include <OpenSolid/Core/config.hpp>

namespace OpenSolid
{
    template <class Type>
    struct Deserialization;

    template <>
    struct Deserialization<bool>
    {
        bool operator()(const std::string& argument) const;
    };

    template <>
    struct Deserialization<int>
    {
        int operator()(const std::string& argument) const;
    };

    template <>
    struct Deserialization<double>
    {
        OPENSOLID_CORE_EXPORT double operator()(const std::string& argument) const;
    };

    template <>
    struct Deserialization<std::string>
    {
        const std::string& operator()(const std::string& argument) const;
    };
}

////////// Implementation //////////

#include <boost/lexical_cast.hpp>

namespace OpenSolid
{
    inline bool Deserialization<bool>::operator()(const std::string& argument) const {
        return boost::lexical_cast<bool>(argument);
    }

    inline int Deserialization<int>::operator()(const std::string& argument) const {
        return boost::lexical_cast<int>(argument);
    }

    inline const std::string& Deserialization<std::string>::operator()(
        const std::string& argument
    ) const {return argument;}
}

#endif
