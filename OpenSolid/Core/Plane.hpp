/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

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

        OPENSOLID_CORE_EXPORT Plane3d(
            const Vector3d& originPoint,
            const Vector3d& xBasisVector,
            const Vector3d& yBasisVector
        );

        template <int iNumDimensions, int iNumAxes>
        Plane3d(const Datum<iNumDimensions, iNumAxes>& otherPlane);

        OPENSOLID_CORE_EXPORT static Plane3d FromPointAndNormal(
            const Vector3d& originPoint,
            const Vector3d& normalVector
        );

        OPENSOLID_CORE_EXPORT static Plane3d ThroughPoints(
            const Vector3d& originPoint,
            const Vector3d& xAxisPoint,
            const Vector3d& planePoint
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
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    inline Plane3d::Plane3d(const Datum<iNumDimensions, iNumAxes>& otherPlane) :
        Datum<3, 2>(otherPlane) {
    }
}
