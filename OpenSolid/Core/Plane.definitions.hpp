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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Plane.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Datum.definitions.hpp>

namespace opensolid
{
    class Plane3d :
        public Datum<3, 2>
    {
    public:
        OPENSOLID_CORE_EXPORT
        Plane3d();

        Plane3d(const Datum<3, 2>& other);

        OPENSOLID_CORE_EXPORT
        Plane3d(const Point<3>& originPoint, const Vector3d& xVector, const Vector3d& xyVector);

        OPENSOLID_CORE_EXPORT static Plane3d
        FromPointAndNormal(const Point<3>& originPoint, const Vector3d& normalVector);

        OPENSOLID_CORE_EXPORT static Plane3d
        ThroughPoints(const Point<3>& originPoint, const Point<3>& xPoint, const Point<3>& xyPoint);

        OPENSOLID_CORE_EXPORT static Plane3d
        Midplane(const Point<3>& pointBelow, const Point<3>& pointAbove);

        OPENSOLID_CORE_EXPORT static Plane3d
        Midplane(const Plane3d planeBelow, const Plane3d planeAbove);

        OPENSOLID_CORE_EXPORT static Plane3d
        ThroughAxisAndPoint(const Axis<3>& axis, const Point<3>& point);

        OPENSOLID_CORE_EXPORT static Plane3d
        ThroughAxis(const Axis<3>& axis);

        OPENSOLID_CORE_EXPORT static Plane3d
        XY(const Point<3>& originPoint = Point<3>::Origin());

        OPENSOLID_CORE_EXPORT static Plane3d
        XZ(const Point<3>& originPoint = Point<3>::Origin());
        
        OPENSOLID_CORE_EXPORT static Plane3d
        YX(const Point<3>& originPoint = Point<3>::Origin());

        OPENSOLID_CORE_EXPORT static Plane3d
        YZ(const Point<3>& originPoint = Point<3>::Origin());

        OPENSOLID_CORE_EXPORT static Plane3d
        ZX(const Point<3>& originPoint = Point<3>::Origin());
        
        OPENSOLID_CORE_EXPORT static Plane3d
        ZY(const Point<3>& originPoint = Point<3>::Origin());

        OPENSOLID_CORE_EXPORT static Plane3d
        FromBasisVectors(
            const Point<3>& originPoint,
            const Vector3d& xBasisVector,
            const Vector3d& yBasisVector
        );

        OPENSOLID_CORE_EXPORT static Plane3d
        FromBasisMatrix(const Point<3>& originPoint, const Matrix<double, 3, 2>& basisMatrix);
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct ScalingFunction<Plane3d> :
        public ScalingFunction<Datum<3, 2>>
    {
    };

    template <>
    struct TranslationFunction<Plane3d> :
        public TranslationFunction<Datum<3, 2>>
    {
    };

    template <int iNumTransformedDimensions>
    struct TransformationFunction<Plane3d, iNumTransformedDimensions> :
        public TransformationFunction<Datum<3, 2>, iNumTransformedDimensions>
    {
    };
}
