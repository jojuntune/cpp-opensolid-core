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

#ifndef OPENSOLID__SERIALIZED__INTERVAL_HPP
#define OPENSOLID__SERIALIZED__INTERVAL_HPP

#include <OpenSolid/config.hpp>

#include "opensolid.pb.h"

#include <OpenSolid/Common/Convertible.hpp>
#include <OpenSolid/Scalar/Interval.hpp>

namespace OpenSolid
{
    template <>
    struct Conversion<Serialized::Interval, Interval>
    {
        OPENSOLID_CORE_EXPORT Interval operator()(const Serialized::Interval& argument) const;
    };

    template <>
    struct Conversion<Interval, Serialized::Interval>
    {
        OPENSOLID_CORE_EXPORT Serialized::Interval operator()(const Interval& argument) const;
    };
}

#endif
