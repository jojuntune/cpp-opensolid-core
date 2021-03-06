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

#include <OpenSolid/Core/BoundedVolume.definitions.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/ParametricSurface.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    inline
    const SpatialSet<ParametricSurface3d>&
    BoundedVolume3d::boundaries() const {
        return _boundaries;
    }

    inline
    bool
    BoundedVolume3d::isEmpty() const {
        return boundaries().isEmpty();
    }

    inline
    Box3d
    BoundedVolume3d::bounds() const {
        return boundaries().bounds();
    }

    template <class TTransformation>
    BoundedVolume3d
    BoundedVolume3d::transformedBy(const TTransformation& transformation) const {
        return BoundedVolume3d(
            SpatialSet<ParametricSurface3d>(
                boundaries().map(
                    [&transformation] (const ParametricSurface3d& boundarySurface) {
                        return boundarySurface.transformedBy(transformation);
                    }
                )
            )
        );
    }
}
