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

#include <exception>
#include <iostream>
#include <string>
#include <typeinfo>

#include <boost/intrusive_ptr.hpp>

#include <OpenSolid/opensolid.pb.h>
#include <OpenSolid/Common/Convertible.hpp>
#include <OpenSolid/Error/ErrorImplementation/ErrorImplementation.hpp>

namespace OpenSolid
{
    class Error : public std::exception, public Convertible<Error> 
    {
    private:
        boost::intrusive_ptr<const ErrorImplementation> _implementation;
        const std::type_info* _type;

        mutable std::string _what;
    public:
        enum {
            INCOMPATIBLE_TYPES,
            DIVISION_BY_ZERO,
            INCOMPATIBLE_SIZES,
            INCOMPATIBLE_DIMENSIONS,
            INCOMPATIBLE_PARAMETERS
        };

        OPENSOLID_CORE_EXPORT Error();
        OPENSOLID_CORE_EXPORT Error(const ErrorImplementation* implementation);

        const ErrorImplementation* implementation() const;
        const std::type_info& type() const;

        OPENSOLID_CORE_EXPORT const char* what() const override;
        OPENSOLID_CORE_EXPORT int problem() const;
    };

    template <>
    struct Conversion<Error, Serialized::Error>
    {
        OPENSOLID_CORE_EXPORT Serialized::Error operator()(const Error& argument) const;
    };

    template <>
    struct Conversion<Serialized::Error, Error>
    {
        OPENSOLID_CORE_EXPORT Error operator()(const Serialized::Error& argument) const;
    };
    
    OPENSOLID_CORE_EXPORT std::ostream& operator<<(std::ostream& stream, const Error& error);
}

#endif
