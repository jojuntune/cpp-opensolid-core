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

#ifndef OPENSOLID__CONVERTIBLE_HPP
#define OPENSOLID__CONVERTIBLE_HPP

namespace OpenSolid
{
    template <class Type, class OtherType>
    struct Conversion;

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

namespace OpenSolid
{
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
