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

#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Quaternion.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    template <class TDerived>
    inline
    const TDerived&
    Transformable<TDerived, 2>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, 2>::rotatedAbout(const Point2d& point, double angle) const {
        return derived().rotatedAbout(point, Quaternion2d(angle).rotationMatrix());
    }
    
    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, 2>::translatedAlong(const Axis2d& axis, double distance) const {
        return derived().translatedBy(distance * axis.directionVector());
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, 2>::mirroredAbout(const Axis2d& axis) const {
        return derived().mirroredAbout(axis.originPoint(), axis.normalVector());
    }

    template <class TDerived>
    inline
    const TDerived&
    Transformable<TDerived, 3>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, 3>::rotatedAbout(const Axis3d& axis, double angle) const {
        return derived().rotatedAbout(
            axis.originPoint(),
            Quaternion3d(axis.directionVector(), angle).rotationMatrix()
        );
    }
    
    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, 3>::translatedAlong(const Axis3d& axis, double distance) const {
        return derived().translatedBy(distance * axis.directionVector());
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, 3>::mirroredAbout(const Plane3d& plane) const {
        return derived().mirroredAbout(plane.originPoint(), plane.normalVector());
    }
}
