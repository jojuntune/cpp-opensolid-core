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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Plane.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/CoordinateSystem.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>

namespace opensolid
{
    class Plane3d
    {
    private:
        Point<3> _originPoint;
        Vector3d _normalVector;
    public:
        OPENSOLID_CORE_EXPORT
        Plane3d();

        OPENSOLID_CORE_EXPORT
        Plane3d(const Point<3>& originPoint, const Vector3d& normalVector);

        OPENSOLID_CORE_EXPORT
        static Plane3d
        ThroughPoints(
            const Point<3>& firstPoint,
            const Point<3>& secondPoint,
            const Point<3>& thirdPoint
        );

        OPENSOLID_CORE_EXPORT
        static Plane3d
        Midplane(const Point<3>& pointBelow, const Point<3>& pointAbove);

        OPENSOLID_CORE_EXPORT
        static Plane3d
        Midplane(const Plane3d planeBelow, const Plane3d planeAbove);

        OPENSOLID_CORE_EXPORT
        static Plane3d
        ThroughAxisAndPoint(const Axis<3>& axis, const Point<3>& point);

        OPENSOLID_CORE_EXPORT
        static Plane3d
        ThroughAxis(const Axis<3>& axis);

        OPENSOLID_CORE_EXPORT
        static Plane3d
        XY();

        OPENSOLID_CORE_EXPORT
        static Plane3d
        XZ();
        
        OPENSOLID_CORE_EXPORT
        static Plane3d
        YX();

        OPENSOLID_CORE_EXPORT
        static Plane3d
        YZ();

        OPENSOLID_CORE_EXPORT
        static Plane3d
        ZX();
        
        OPENSOLID_CORE_EXPORT
        static Plane3d
        ZY();

        const Point<3>&
        originPoint() const;

        const Vector3d&
        normalVector() const;

        OPENSOLID_CORE_EXPORT
        Plane3d
        offsetBy(double distance) const;

        OPENSOLID_CORE_EXPORT
        Plane3d
        flipped() const;

        OPENSOLID_CORE_EXPORT
        Axis<3>
        normalAxis() const;

        OPENSOLID_CORE_EXPORT
        PlanarCoordinateSystem3d
        coordinateSystem() const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct NumDimensions<Plane3d>
    {
        static const int Value = 3;
    };

    template <>
    struct ScalingFunction<Plane3d>
    {
        OPENSOLID_CORE_EXPORT
        Plane3d
        operator()(const Plane3d& plane, double scale) const;
    };

    template <>
    struct TranslationFunction<Plane3d>
    {
        template <class TVector>
        Plane3d
        operator()(const Plane3d& plane, const EigenBase<TVector>& vector) const;
    };

    template <>
    struct TransformationFunction<Plane3d, 3>
    {
        template <class TMatrix>
        Plane3d
        operator()(const Plane3d& plane, const EigenBase<TMatrix>& matrix) const;
    };

    template <>
    struct MorphingFunction<Plane3d, 3>
    {
        OPENSOLID_CORE_EXPORT
        Plane3d
        operator()(
            const Plane3d& plane,
            const ParametricExpression<3, 3>& morphingExpression
        ) const;
    };
}
