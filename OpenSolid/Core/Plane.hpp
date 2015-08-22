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
#include <OpenSolid/Core/Handedness.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

namespace opensolid
{
    inline
    UnitVector3d
    Plane3d::xDirectionVector() const {
        return directionVector(0);
    }

    inline
    UnitVector3d
    Plane3d::yDirectionVector() const {
        return directionVector(1);
    }

    inline
    const UnitVector3d&
    Plane3d::normalVector() const {
        return _normalVector;
    }

    inline
    Handedness
    Plane3d::handedness() const {
        return _handedness;
    }

    template <class TTransformation>
    Plane3d
    Plane3d::transformedBy(const TTransformation& transformation) const {
        return Plane3d(
            originPoint().transformedBy(transformation),
            xDirectionVector().transformedBy(transformation),
            yDirectionVector().transformedBy(transformation),
            normalVector().transformedBy(transformation),
            handedness().transformedBy(transformation)
        );
    }
}
