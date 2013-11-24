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

#include <OpenSolid/Core/Axis.hpp>

#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    Axis2d::Axis2d(const Point2d& originPoint, const Vector2d& directionVector) :
        Axis<2>(originPoint, directionVector) {
    }

    Axis2d::Axis2d(const Axis<2>& other) :
        Axis<2>(other) {
    }

    Axis2d
    Axis2d::X() {
        return Axis2d(Point2d::Origin(), Vector2d::UnitX());
    }

    Axis2d
    Axis2d::Y() {
        return Axis2d(Point2d::Origin(), Vector2d::UnitY());
    }

    Axis3d::Axis3d(const Point3d& originPoint, const Vector3d& directionVector) :
        Axis<3>(originPoint, directionVector) {
    }

    Axis3d::Axis3d(const Axis<3>& other) :
        Axis<3>(other) {
    }

    Axis3d
    Axis3d::X() {
        return Axis3d(Point3d::Origin(), Vector3d::UnitX());
    }

    Axis3d
    Axis3d::Y() {
        return Axis3d(Point3d::Origin(), Vector3d::UnitY());
    }

    Axis3d
    Axis3d::Z() {
        return Axis3d(Point3d::Origin(), Vector3d::UnitZ());
    }

    Plane3d
    Axis3d::normalPlane() const {
        return Plane3d(originPoint(), directionVector());
    }
}
