/*************************************************************************************
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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Datum.hpp>

namespace opensolid
{
    class Plane3d : public Datum<3, 2>
    {
    public:
        OPENSOLID_CORE_EXPORT Plane3d();

        Plane3d(const Datum<3, 2>& otherPlane);

        OPENSOLID_CORE_EXPORT Plane3d(
            const Vector3d& originPoint,
            const Vector3d& xVector,
            const Vector3d& xyVector
        );

        OPENSOLID_CORE_EXPORT static Plane3d FromPointAndNormal(
            const Vector3d& originPoint,
            const Vector3d& normalVector
        );

        OPENSOLID_CORE_EXPORT static Plane3d ThroughPoints(
            const Vector3d& originPoint,
            const Vector3d& xPoint,
            const Vector3d& xyPoint
        );

        OPENSOLID_CORE_EXPORT static Plane3d Midplane(
            const Vector3d& pointBelow,
            const Vector3d& pointAbove
        );

        OPENSOLID_CORE_EXPORT static Plane3d Midplane(
            const Plane3d planeBelow,
            const Plane3d planeAbove
        );

        OPENSOLID_CORE_EXPORT static Plane3d ThroughAxisAndPoint(
            const Axis3d& axis,
            const Vector3d& point
        );

        OPENSOLID_CORE_EXPORT static Plane3d ThroughAxis(
            const Axis3d& axis
        );

        OPENSOLID_CORE_EXPORT static Plane3d XY();
        OPENSOLID_CORE_EXPORT static Plane3d XY(const Vector3d& originPoint);

        OPENSOLID_CORE_EXPORT static Plane3d XZ();
        OPENSOLID_CORE_EXPORT static Plane3d XZ(const Vector3d& originPoint);
        
        OPENSOLID_CORE_EXPORT static Plane3d YX();
        OPENSOLID_CORE_EXPORT static Plane3d YX(const Vector3d& originPoint);

        OPENSOLID_CORE_EXPORT static Plane3d YZ();
        OPENSOLID_CORE_EXPORT static Plane3d YZ(const Vector3d& originPoint);

        OPENSOLID_CORE_EXPORT static Plane3d ZX();
        OPENSOLID_CORE_EXPORT static Plane3d ZX(const Vector3d& originPoint);

        OPENSOLID_CORE_EXPORT static Plane3d ZY();
        OPENSOLID_CORE_EXPORT static Plane3d ZY(const Vector3d& originPoint);

        OPENSOLID_CORE_EXPORT static Plane3d FromBasisVectors(
            const Vector3d& originPoint,
            const Vector3d& xBasisVector,
            const Vector3d& yBasisVector
        );

        OPENSOLID_CORE_EXPORT static Plane3d FromBasisMatrix(
            const Vector3d& originPoint,
            const Matrix<double, 3, 2>& basisMatrix
        );
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Plane3d::Plane3d(const Datum<3, 2>& otherPlane) : Datum<3, 2>(otherPlane) {
    }
}
