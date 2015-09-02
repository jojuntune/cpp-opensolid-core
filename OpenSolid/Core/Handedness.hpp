/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Sign.hpp>

namespace opensolid
{
    inline
    Handedness::Handedness() {
    }

    inline
    Handedness::Handedness(Sign sign) :
        _sign(sign) {
    }

    inline
    Sign
    Handedness::sign() const {
        return _sign;
    }

    template <class TTransformation>
    inline
    Handedness
    Handedness::transformedBy(const TTransformation& transformation) const {
        return transformation.transform(*this);
    }

    inline 
    bool
    Handedness::operator==(Handedness other) const {
        return sign() == other.sign();
    }

    inline
    Handedness
    Handedness::operator-() const {
        return Handedness(-sign());
    }

    inline
    Handedness
    Handedness::operator*(Handedness other) const {
        return Handedness(sign() * other.sign());
    }

    inline
    Handedness
    Handedness::RIGHT_HANDED() {
        return Handedness(Sign::POSITIVE());
    }

    inline
    Handedness
    Handedness::LEFT_HANDED() {
        return Handedness(Sign::NEGATIVE());
    }
}
