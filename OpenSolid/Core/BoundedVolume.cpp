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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/BoundedVolume.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/ParametricSurface.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

namespace opensolid
{
    BoundedVolume3d::BoundedVolume3d() {
    }

    BoundedVolume3d::BoundedVolume3d(const BoundedVolume3d& other) :
        _boundaries(other.boundaries()) {
    }

    BoundedVolume3d::BoundedVolume3d(BoundedVolume3d&& other) :
        _boundaries(std::move(other.boundaries())) {
    }

    BoundedVolume3d::BoundedVolume3d(const SpatialSet<ParametricSurface3d>& boundaries) :
        _boundaries(boundaries) {
    }

    BoundedVolume3d::BoundedVolume3d(SpatialSet<ParametricSurface3d>&& boundaries) :
        _boundaries(std::move(boundaries)) {
    }
}
