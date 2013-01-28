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

        Frame2d(const Datum<2, 2>& otherFrame);

        OPENSOLID_CORE_EXPORT explicit Frame2d(const Vector2d& originPoint);

        OPENSOLID_CORE_EXPORT Frame2d(
            const Vector2d& originPoint,
            const Vector2d& xVector,
            const Vector2d& xyVector
        );
        

        OPENSOLID_CORE_EXPORT static Frame2d XY();
        OPENSOLID_CORE_EXPORT static Frame2d XY(const Vector2d& originPoint);

        OPENSOLID_CORE_EXPORT static Frame2d FromXAxis(const Axis2d& xAxis);
        OPENSOLID_CORE_EXPORT static Frame2d FromYAxis(const Axis2d& yAxis);

        OPENSOLID_CORE_EXPORT static Frame2d FromBasisVectors(
            const Vector2d& originPoint,
            const Vector2d& xBasisVector,
            const Vector2d& yBasisVector
        );
        
        OPENSOLID_CORE_EXPORT static Frame2d FromBasisMatrix(
            const Vector2d& originPoint,
            const Matrix2d& basisMatrix
        );
    };

    
    class Frame3d : public Datum<3, 3>
    {
    public:
        OPENSOLID_CORE_EXPORT Frame3d();
        
        Frame3d(const Datum<3, 3>& otherFrame);

        OPENSOLID_CORE_EXPORT explicit Frame3d(const Vector3d& originPoint);
        
        OPENSOLID_CORE_EXPORT Frame3d(
            const Vector3d& originPoint,
            const Vector3d& xVector,
            const Vector3d& xyVector,
            const Vector3d& xyzVector
        );

        OPENSOLID_CORE_EXPORT static Frame3d XYZ();
        OPENSOLID_CORE_EXPORT static Frame3d XYZ(const Vector3d& originPoint);

        OPENSOLID_CORE_EXPORT static Frame3d FromXYPlane(const Plane3d& xyPlane);
        OPENSOLID_CORE_EXPORT static Frame3d FromXZPlane(const Plane3d& xzPlane);
        OPENSOLID_CORE_EXPORT static Frame3d FromYXPlane(const Plane3d& yxPlane);
        OPENSOLID_CORE_EXPORT static Frame3d FromYZPlane(const Plane3d& yzPlane);
        OPENSOLID_CORE_EXPORT static Frame3d FromZXPlane(const Plane3d& zxPlane);
        OPENSOLID_CORE_EXPORT static Frame3d FromZYPlane(const Plane3d& zyPlane);

        OPENSOLID_CORE_EXPORT static Frame3d FromBasisVectors(
            const Vector3d& originPoint,
            const Vector3d& xBasisVector,
            const Vector3d& yBasisVector,
            const Vector3d& zBasisVector
        );
        
        OPENSOLID_CORE_EXPORT static Frame3d FromBasisMatrix(
            const Vector3d& originPoint,
            const Matrix3d& basisMatrix
        );
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Frame2d::Frame2d(const Datum<2, 2>& otherFrame) : Datum<2, 2>(otherFrame) {
    }

    inline Frame3d::Frame3d(const Datum<3, 3>& otherFrame) : Datum<3, 3>(otherFrame) {
    }
}
