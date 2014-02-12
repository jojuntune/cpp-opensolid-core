/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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

#include <OpenSolid/Core/AxisPlaneIntersection3d.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    inline
    const Axis3d&
    Intersection<Axis3d, Plane3d>::axis() const {
        return _axis;
    }

    inline
    const Plane3d&
    Intersection<Axis3d, Plane3d>::plane() const {
        return _plane;
    }

    inline
    double
    Intersection<Axis3d, Plane3d>::precision() const {
        return _precision;
    }

    inline
    bool
    Intersection<Axis3d, Plane3d>::exists() const {
        return _dotProduct != Zero(_precision) || _originDistance == Zero(_precision);
    }

    inline
    bool
    Intersection<Axis3d, Plane3d>::isPoint() const {
        return _dotProduct != Zero(_precision);
    }

    inline
    bool
    Intersection<Axis3d, Plane3d>::isCoincident() const {
        return _dotProduct == Zero(_precision) && _originDistance == Zero(_precision);
    }
}
