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

#include <OpenSolid/Core/Axis.declarations.hpp>

#include <OpenSolid/Core/Datum.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>

namespace opensolid
{
    template <>
    class Axis<2> : public Datum<2, 1>
    {
    public:
        OPENSOLID_CORE_EXPORT
        Axis();

        Axis(const Datum<2, 1>& otherAxis);

        OPENSOLID_CORE_EXPORT
        Axis(const Point2d& originPoint, const Vector2d& directionVector);

        OPENSOLID_CORE_EXPORT static Axis<2>
        X(const Point2d& originPoint = Point2d::Origin());
        
        OPENSOLID_CORE_EXPORT static Axis<2>
        Y(const Point2d& originPoint = Point2d::Origin());

        OPENSOLID_CORE_EXPORT static Axis<2>
        FromBasisVector(const Point2d& originPoint, const Vector2d& basisVector);
    };

    typedef Axis<2> Axis2d;

    template <>
    class Axis<3> : public Datum<3, 1>
    {
    public:
        OPENSOLID_CORE_EXPORT
        Axis();

        Axis(const Datum<3, 1>& otherAxis);

        OPENSOLID_CORE_EXPORT
        Axis(const Point3d& originPoint, const Vector3d& directionVector);

        OPENSOLID_CORE_EXPORT static Axis<3>
        X(const Point3d& originPoint = Point3d::Origin());
        
        OPENSOLID_CORE_EXPORT static Axis<3>
        Y(const Point3d& originPoint = Point3d::Origin());
        
        OPENSOLID_CORE_EXPORT static Axis<3>
        Z(const Point3d& originPoint = Point3d::Origin());

        OPENSOLID_CORE_EXPORT static Axis<3>
        FromBasisVector(const Point3d& originPoint, const Vector3d& basisVector);
    };

    typedef Axis<3> Axis3d;
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct ScalingFunction<Axis<iNumDimensions>> :
        public ScalingFunction<Datum<iNumDimensions, 1>>
    {
    };

    template <int iNumDimensions>
    struct TranslationFunction<Axis<iNumDimensions>> :
        public TranslationFunction<Datum<iNumDimensions, 1>>
    {
    };

    template <int iNumDimensions, int iTransformedDimensions>
    struct TransformationFunction<Axis<iNumDimensions>, iTransformedDimensions> :
        public TransformationFunction<Datum<iNumDimensions, 1>, iTransformedDimensions>
    {
    };
}
