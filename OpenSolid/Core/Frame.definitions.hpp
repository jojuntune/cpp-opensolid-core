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

#include <OpenSolid/Core/Frame.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Datum.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>

namespace opensolid
{
    class Frame2d : public Datum<2, 2>
    {
    public:
        OPENSOLID_CORE_EXPORT
        Frame2d();

        Frame2d(const Datum<2, 2>& other);

        OPENSOLID_CORE_EXPORT explicit
        Frame2d(const Point2d& originPoint);

        OPENSOLID_CORE_EXPORT
        Frame2d(
            const Point2d& originPoint,
            const Vector2d& xVector,
            const Vector2d& xyVector
        );
        

        OPENSOLID_CORE_EXPORT static Frame2d
        XY();

        OPENSOLID_CORE_EXPORT static Frame2d
        XY(const Point2d& originPoint);

        OPENSOLID_CORE_EXPORT static Frame2d
        FromXAxis(const Axis<2>& xAxis);

        OPENSOLID_CORE_EXPORT static Frame2d
        FromYAxis(const Axis<2>& yAxis);

        OPENSOLID_CORE_EXPORT static Frame2d
        FromBasisVectors(
            const Point<2>& originPoint,
            const Vector2d& xBasisVector,
            const Vector2d& yBasisVector
        );
        
        OPENSOLID_CORE_EXPORT static Frame2d 
        FromBasisMatrix(const Point<2>& originPoint, const Matrix2d& basisMatrix);
    };

    
    class Frame3d : public Datum<3, 3>
    {
    public:
        OPENSOLID_CORE_EXPORT
        Frame3d();
        
        Frame3d(const Datum<3, 3>& other);

        OPENSOLID_CORE_EXPORT explicit
        Frame3d(const Point<3>& originPoint);
        
        OPENSOLID_CORE_EXPORT
        Frame3d(
            const Point<3>& originPoint,
            const Vector3d& xVector,
            const Vector3d& xyVector,
            const Vector3d& xyzVector
        );

        OPENSOLID_CORE_EXPORT static Frame3d
        XYZ();
        
        OPENSOLID_CORE_EXPORT static Frame3d
        XYZ(const Point<3>& originPoint);

        OPENSOLID_CORE_EXPORT static Frame3d
        FromXYPlane(const Plane3d& xyPlane);

        OPENSOLID_CORE_EXPORT static Frame3d
        FromXZPlane(const Plane3d& xzPlane);

        OPENSOLID_CORE_EXPORT static Frame3d
        FromYXPlane(const Plane3d& yxPlane);
        
        OPENSOLID_CORE_EXPORT static Frame3d
        FromYZPlane(const Plane3d& yzPlane);
        
        OPENSOLID_CORE_EXPORT static Frame3d
        FromZXPlane(const Plane3d& zxPlane);
        
        OPENSOLID_CORE_EXPORT static Frame3d
        FromZYPlane(const Plane3d& zyPlane);

        OPENSOLID_CORE_EXPORT static Frame3d
        FromBasisVectors(
            const Point<3>& originPoint,
            const Vector3d& xBasisVector,
            const Vector3d& yBasisVector,
            const Vector3d& zBasisVector
        );
        
        OPENSOLID_CORE_EXPORT static Frame3d
        FromBasisMatrix(const Point<3>& originPoint, const Matrix3d& basisMatrix);
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct ScalingFunction<Frame<iNumDimensions>> :
        public ScalingFunction<Datum<iNumDimensions, iNumDimensions>>
    {
    };

    template <int iNumDimensions>
    struct TranslationFunction<Frame<iNumDimensions>> :
        public TranslationFunction<Datum<iNumDimensions, iNumDimensions>>
    {
    };

    template <int iNumDimensions, int iTransformedDimensions>
    struct TransformationFunction<Frame<iNumDimensions>, iTransformedDimensions> :
        public TransformationFunction<Datum<iNumDimensions, iNumDimensions>, iTransformedDimensions>
    {
    };
}
