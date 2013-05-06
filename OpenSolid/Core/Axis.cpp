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
*************************************************************************************/

#include <OpenSolid/Core/Axis.hpp>

#include <OpenSolid/Core/Datum.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    Axis<2>::Axis() :
        Datum<2, 1>() {
    }

    Axis<2>::Axis(const Point2d& originPoint, const Vector2d& directionVector) :
        Datum<2, 1>(originPoint, directionVector.normalized()) {
    }

    Axis<2>
    Axis<2>::X(const Point2d& originPoint) {
        return Axis<2>(originPoint, Vector2d::UnitX());
    }

    Axis<2>
    Axis<2>::Y(const Point2d& originPoint) {
        return Axis<2>(originPoint, Vector2d::UnitY());
    }

    Axis<2>
    Axis<2>::FromBasisVector(const Point2d& originPoint, const Vector2d& basisVector) {
        return Datum<2, 1>(originPoint, basisVector);
    }

    Axis<3>::Axis() :
        Datum<3, 1>() {
    }

    Axis<3>::Axis(const Point3d& originPoint, const Vector3d& directionVector) :
        Datum<3, 1>(originPoint, directionVector.normalized()) {
    }

    Axis<3>
    Axis<3>::X(const Point3d& originPoint) {
        return Axis<3>(originPoint, Vector3d::UnitX());
    }

    Axis<3>
    Axis<3>::Y(const Point3d& originPoint) {
        return Axis<3>(originPoint, Vector3d::UnitY());
    }

    Axis<3>
    Axis<3>::Z(const Point3d& originPoint) {
        return Axis<3>(originPoint, Vector3d::UnitZ());
    }

    Axis<3>
    Axis<3>::FromBasisVector(const Point3d& originPoint, const Vector3d& basisVector) {
        return Datum<3, 1>(originPoint, basisVector);
    }
}
