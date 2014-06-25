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

#include <OpenSolid/Core/Projection.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Plane.hpp>

namespace opensolid
{
    Projection2d::Projection2d(const Axis<2>& axis) :
        LinearTransformation<2>(
            axis.originPoint(),
            axis.directionVector().components() * axis.directionVector().components().transpose()
        ) {
    }

    Projection3d::Projection3d(const Axis<3>& axis) :
        LinearTransformation<3>(
            axis.originPoint(),
            axis.directionVector().components() * axis.directionVector().components().transpose()
        ) {
    }

    Projection3d::Projection3d(const Plane3d& plane) :
        LinearTransformation<3>(
            plane.originPoint(),
            Matrix3d::identity() -
                plane.normalVector().components() * plane.normalVector().components().transpose()
        ) {
    }
}
