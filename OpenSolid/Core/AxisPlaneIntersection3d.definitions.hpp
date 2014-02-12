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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Axis.definitions.hpp>
#include <OpenSolid/Core/Intersection.declarations.hpp>
#include <OpenSolid/Core/Plane.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>

namespace opensolid
{
    template <>
    class Intersection<Axis<3>, Plane3d>
    {
    private:
        Axis<3> _axis;
        Plane3d _plane;
        double _precision;
        double _dotProduct;
        double _originDistance;
    public:
        OPENSOLID_CORE_EXPORT
        Intersection(const Axis<3>& axis, const Plane3d& plane, double precision = 1e-12);
    
        const Axis<3>&
        axis() const;

        const Plane3d&
        plane() const;

        double
        precision() const;

        bool
        exists() const;

        bool
        isPoint() const;

        bool
        isCoincident() const;

        OPENSOLID_CORE_EXPORT
        Point<3>
        point() const;
    };
}
