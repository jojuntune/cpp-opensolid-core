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
#include <OpenSolid/Core/Plane.hpp>

namespace opensolid
{
    class Frame2d : public Datum<2, 2>
    {
    public:
        OPENSOLID_CORE_EXPORT Frame2d();

        Frame2d(const Frame2d& otherFrame);

        OPENSOLID_CORE_EXPORT explicit Frame2d(const Vector2d& originPoint);

        OPENSOLID_CORE_EXPORT Frame2d(
            const Vector2d& originPoint,
            const Vector2d& xVector,
            const Vector2d& yVector
        );
        
        template <int iNumDimensions, int iNumAxes>
        Frame2d(const Datum<iNumDimensions, iNumAxes>& otherFrame);

        OPENSOLID_CORE_EXPORT static Frame2d Unit();
        OPENSOLID_CORE_EXPORT static Frame2d Unit(const Vector2d& originPoint);
        OPENSOLID_CORE_EXPORT static Frame2d FromXAxis(const Axis2d& xAxis);
        OPENSOLID_CORE_EXPORT static Frame2d FromYAxis(const Axis2d& yAxis);
    };

    
    class Frame3d : public Datum<3, 3>
    {
    public:
        OPENSOLID_CORE_EXPORT Frame3d();

        Frame3d(const Frame3d& otherFrame);

        OPENSOLID_CORE_EXPORT explicit Frame3d(const Vector3d& originPoint);
        
        OPENSOLID_CORE_EXPORT Frame3d(
            const Vector3d& originPoint,
            const Vector3d& xVector,
            const Vector3d& yVector,
            const Vector3d& zVector
        );
        
        template <int iNumDimensions, int iNumAxes>
        Frame3d(const Datum<iNumDimensions, iNumAxes>& otherFrame);

        OPENSOLID_CORE_EXPORT static Frame3d Unit();
        OPENSOLID_CORE_EXPORT static Frame3d Unit(const Vector3d& originPoint);
        OPENSOLID_CORE_EXPORT static Frame3d FromXYPlane(const Plane3d& xyPlane);
        OPENSOLID_CORE_EXPORT static Frame3d FromXZPlane(const Plane3d& xzPlane);
        OPENSOLID_CORE_EXPORT static Frame3d FromYXPlane(const Plane3d& yxPlane);
        OPENSOLID_CORE_EXPORT static Frame3d FromYZPlane(const Plane3d& yzPlane);
        OPENSOLID_CORE_EXPORT static Frame3d FromZXPlane(const Plane3d& zxPlane);
        OPENSOLID_CORE_EXPORT static Frame3d FromZYPlane(const Plane3d& zyPlane);
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Frame2d::Frame2d(const Frame2d& otherFrame) : Datum<2, 2>(otherFrame) {
    }

    template <int iNumDimensions, int iNumAxes>
    inline Frame2d::Frame2d(const Datum<iNumDimensions, iNumAxes>& otherFrame) :
        Datum<2, 2>(otherFrame) {
    }

    inline Frame3d::Frame3d(const Frame3d& otherFrame) : Datum<3, 3>(otherFrame) {
    }

    template <int iNumDimensions, int iNumAxes>
    inline Frame3d::Frame3d(const Datum<iNumDimensions, iNumAxes>& otherFrame) :
        Datum<3, 3>(otherFrame) {
    }
}
