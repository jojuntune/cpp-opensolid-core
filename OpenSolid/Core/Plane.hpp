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

#include <OpenSolid/Core/Plane.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

namespace opensolid
{
    inline
    const Point<3>&
    Plane3d::originPoint() const {
        return _originPoint;
    }

    inline
    const UnitVector3d&
    Plane3d::normalVector() const {
        return _normalVector;
    }
    
    inline
    bool
    Plane3d::contains(const Point3d& point, double precision) const {
        return point.distanceTo(*this) == Zero(precision);
    }

    inline
    Plane3d
    ScalingFunction<Plane3d>::operator()(
        const Plane3d& plane,
        const Point3d& originPoint,
        double scale
    ) const {
        return Plane3d(
            scaled(plane.originPoint(), originPoint, scale),
            scale >= 0.0 ? plane.normalVector() : -plane.normalVector()
        );
    }

    inline
    Plane3d
    TranslationFunction<Plane3d>::operator()(
        const Plane3d& plane,
        const Vector<double, 3>& vector
    ) const {
        return Plane3d(
            translated(plane.originPoint(), vector),
            plane.normalVector()
        );
    }
}
