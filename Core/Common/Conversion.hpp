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

#ifndef OPENSOLID__CONVERSION_HPP
#define OPENSOLID__CONVERSION_HPP

#include <OpenSolid/Core/config.hpp>

#include <string>

namespace opensolid
{
    template <class Type, class OtherType>
    struct Conversion;

    template <>
    struct Conversion<bool, std::string>
    {
        OPENSOLID_CORE_EXPORT std::string operator()(bool argument) const;
    };

    template <>
    struct Conversion<std::string, bool>
    {
        OPENSOLID_CORE_EXPORT bool operator()(const std::string& argument) const;
    };

    template <>
    struct Conversion<int, std::string>
    {
        OPENSOLID_CORE_EXPORT std::string operator()(int argument) const;
    };

    template <>
    struct Conversion<std::string, int>
    {
        OPENSOLID_CORE_EXPORT int operator()(const std::string& argument) const;
    };

    template <>
    struct Conversion<double, std::string>
    {
        OPENSOLID_CORE_EXPORT std::string operator()(double argument) const;
    };

    template <>
    struct Conversion<std::string, double>
    {
        OPENSOLID_CORE_EXPORT double operator()(const std::string& argument) const;
    };

    template <class Type>
    struct Conversion<Type, std::string>
    {
        std::string operator()(const Type& argument) const;
    };

    template <class Type>
    struct Conversion<std::string, Type>
    {
        Type operator()(const std::string& argument) const;
    };

    template <class Type>
    struct Conversion<Type, Type>
    {
        const Type& operator()(const Type& argument) const;
    };

    template <>
    struct Conversion<std::string, std::string>
    {
        const std::string& operator()(const std::string& argument) const;
    };

    template <class DerivedType>
    struct Convertible
    {
        template <class OtherType>
        OtherType as() const;

        template <class OtherType>
        static DerivedType from(const OtherType& argument);
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    std::string Conversion<Type, std::string>::operator()(const Type& argument) const {
        return Object::from(argument).as<std::string>();
    }

    template <class Type>
    Type Conversion<std::string, Type>::operator()(const std::string& argument) const {
        return Object::from(argument).as<Type>();
    }

    template <class Type>
    inline const Type& Conversion<Type, Type>::operator()(const Type& argument) const {
        return argument;
    }

    inline const std::string& Conversion<std::string, std::string>::operator()(
        const std::string& argument
    ) const {return argument;}

    template <class DerivedType> template <class OtherType>
    inline OtherType Convertible<DerivedType>::as() const {
        return Conversion<DerivedType, OtherType>()(static_cast<const DerivedType&>(*this));
    }

    template <class DerivedType> template <class OtherType>
    inline DerivedType Convertible<DerivedType>::from(const OtherType& argument) {
        return Conversion<OtherType, DerivedType>()(argument);
    }
}

#endif
