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

#include "Datum/declarations.hpp"
#include "Datum/DatumBase.hpp"

namespace opensolid
{   
    //DatumBase(
    //    const Matrix<double, iNumDimensions, 1>& originPoint,
    //    const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
    //);
    //    
    //DatumBase(const DatumBase<iNumDimensions, iNumAxes>& other);
    //    
    //template <int iOtherNumDimensions, int iOtherNumAxes>
    //DatumBase(const DatumBase<iOtherNumDimensions, iOtherNumAxes>& other);
    //    
    //Datum<iNumDimensions, iNumAxes>& operator=(const Datum<iNumDimensions, iNumAxes>& other);
    //    
    //template <int iOtherNumDimensions, int iOtherNumAxes>
    //Datum<iNumDimensions, iNumAxes>& operator=(const Datum<iOtherNumDimensions, iOtherNumAxes>& other);

    // Axis2d, Axis3d
    template <int iNumDimensions>
    class Datum<iNumDimensions, 1> : public DatumBase<iNumDimensions, 1>
    {
    public:
        static Datum<iNumDimensions, 1> ThroughPoints(
            const Matrix<double, iNumDimensions, 1>& originPoint,
            const Matrix<double, iNumDimensions, 1>& axisPoint
        );
    };

    // Plane3d
    template <>
    class Datum<3, 2> : public DatumBase<3, 2>
    {
    public:
        static Datum<3, 2> FromPointAndNormal(
            const Vector3d& originPoint,
            const Vector3d& normalVector
        );

        static Datum<3, 2> ThroughPoints(
            const Vector3d& originPoint,
            const Vector3d& xAxisPoint,
            const Vector3d& planePoint
        );

        static Datum<3, 2> Midplane(
            const Vector3d& pointBelow,
            const Vector3d& pointAbove
        );

        static Datum<3, 2> Midplane(
            const Datum<3, 2> planeBelow,
            const Datum<3, 2> planeAbove
        );

        static Datum<3, 2> ThroughAxisAndPoint(
            const Datum<3, 1>& axis,
            const Vector3d& point
        );

        static Datum<3, 2> ThroughAxis(
            const Datum<3, 1>& axis
        );
    };

    // Frame2d
    template <>
    class Datum<2, 2> : public DatumBase<2, 2>
    {
    public:
        static Datum<2, 2> FromPoints(
            const Vector2d& originPoint,
            const Vector2d& xAxisPoint
        );
    };

    // Frame3d
    template <>
    class Datum<3, 3> : public DatumBase<3, 3>
    {
    public:
        static Datum<3, 2> FromPoints(
            const Vector3d& originPoint,
            const Vector3d& xAxisPoint,
            const Vector3d& xyPlanePoint
        );
    };
}