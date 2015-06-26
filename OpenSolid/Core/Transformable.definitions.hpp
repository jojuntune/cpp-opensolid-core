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

#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>

namespace opensolid
{
    template <class TDerived>
    class Transformable<TDerived, 2>
    {
    public:
        // To be provided by derived class:
        //   scaledAbout(point, scale)
        //   rotatedAbout(point, rotationMatrix)
        //   translatedBy(vector)
        //   toLocalIn(frame/datum)
        //   toGlobalFrom(frame/datum)
        //   projectedOnto(datum)
        //   mirroredAbout(point, directionVector)

        const TDerived&
        derived() const;

        TDerived
        rotatedAbout(const Point<2>& originPoint, double angle) const;

        TDerived
        translatedAlong(const Axis<2>& axis, double distance) const;

        TDerived
        mirroredAbout(const Axis<2>& axis) const;
    };

    template <class TDerived>
    class Transformable<TDerived, 3>
    {
    public:
        // To be provided by derived class:
        //   scaledAbout(point, scale)
        //   rotatedAbout(point, rotationMatrix)
        //   translatedBy(vector)
        //   toLocalIn(frame/datum)
        //   toGlobalFrom(frame/datum)
        //   projectedOnto(datum)
        //   mirroredAbout(point, directionVector)

        const TDerived&
        derived() const;

        TDerived
        rotatedAbout(const Axis<3>& axis, double angle) const;

        TDerived
        translatedAlong(const Axis<3>& axis, double distance) const;

        TDerived
        mirroredAbout(const Plane3d& plane) const;
    };
}
