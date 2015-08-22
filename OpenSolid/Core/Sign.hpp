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

#include <OpenSolid/Core/Sign.definitions.hpp>

namespace opensolid
{
    inline
    Sign::Sign(int value) :
        _value(value) {

        assert(value == -1 || value == 0 || value == 1);
    }

    inline
    Sign::Sign() :
        _value(0) {
    }

    inline
    int
    Sign::value() const {
        return _value;
    }

    inline
    Sign::operator int() const {
        return _value;
    }

    inline
    bool
    Sign::operator==(Sign other) const {
        return value() == other.value();
    }

    inline
    bool
    Sign::operator!=(Sign other) const {
        return value() != other.value();
    }

    inline
    Sign
    Sign::operator-() const {
        return Sign(-value());
    }

    inline
    Sign
    Sign::operator*(Sign other) const {
        return Sign(value() * other.value());
    }

    inline
    Sign
    Sign::ZERO() {
        return Sign(0);
    }
    
    inline
    Sign
    Sign::POSITIVE() {
        return Sign(1);
    }
    
    inline
    Sign
    Sign::NEGATIVE() {
        return Sign(-1);
    }
}
