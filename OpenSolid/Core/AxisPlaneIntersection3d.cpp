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

#include <OpenSolid/Core/AxisPlaneIntersection3d.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    Intersection<Axis3d, Plane3d>::Intersection(
        const Axis<3>& axis,
        const Plane3d& plane,
        double precision
    ) {
        Point3d originPoint = axis.originPoint();
        Vector3d directionVector = axis.directionVector();
        double dotProduct = directionVector.dot(plane.normalVector());
        double originDistance = originPoint.distanceTo(plane);
        Zero zero(precision);
        if (dotProduct == zero) {
            if (originDistance == zero) {
                _type = COINCIDENT;
            } else {
                _type = NONE;
            }
        } else {
            _type = POINT;
            _point = originPoint - (originDistance / dotProduct) * directionVector;
        }
    }
}
