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
#include <OpenSolid/Core/Curve.declarations.hpp>
#include <OpenSolid/Core/Datum.declarations.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class CurveConstructors;

    template <>
    class CurveConstructors<2>
    {
    public:
        enum WindingDirection {Clockwise, Counterclockwise};

        OPENSOLID_CORE_EXPORT static Curve<2>
        Arc(
            const Point<2>& centerPoint,
            double radius,
            double startAngle,
            double endAngle
        );
        
        OPENSOLID_CORE_EXPORT static Curve<2>
        ArcFromCenterAndEndpoints(
            const Point<2>& centerPoint,
            WindingDirection direction,
            const Point<2>& startPoint,
            const Point<2>& endPoint
        );

        OPENSOLID_CORE_EXPORT static Curve<2>
        ArcFromThreePoints(
            const Point<2>& startPoint,
            const Point<2>& innerPoint,
            const Point<2>& endPoint
        );

        OPENSOLID_CORE_EXPORT static Curve<2>
        Circle(const Point<2>& centerPoint, double radius);
    };

    template <>
    class CurveConstructors<3>
    {
    public:
        OPENSOLID_CORE_EXPORT static Curve<3>
        ArcOnPlane(const Plane3d& plane, double radius, double startAngle, double endAngle);

        OPENSOLID_CORE_EXPORT static Curve<3>
        ArcFromAxisAndEndpoints(
            const Axis<3>& axis,
            const Point<3>& startPoint,
            const Point<3>& endPoint
        );

        OPENSOLID_CORE_EXPORT static Curve<3>
        ArcFromThreePoints(
            const Point<3>& startPoint,
            const Point<3>& innerPoint,
            const Point<3>& endPoint
        );

        OPENSOLID_CORE_EXPORT static Curve<3>
        CircleAboutAxis(const Axis<3>& axis, double radius);

        OPENSOLID_CORE_EXPORT static Curve<3>
        CircleOnPlane(const Plane3d& plane, double radius);
        
        OPENSOLID_CORE_EXPORT static Curve<3>
        HelixFromDatum(const Datum<3, 3>& datum, double numTurns);

        OPENSOLID_CORE_EXPORT static Curve<3>
        HelixFromFrame(const Frame<3>& frame, double radius, double pitch, double numTurns);

        OPENSOLID_CORE_EXPORT static Curve<3>
        HelixAboutAxis(
            const Axis<3>& axis,
            const Point<3>& startPoint,
            double pitch,
            double numTurns
        );

        OPENSOLID_CORE_EXPORT static Curve<3>
        HelixBetweenPoints(
            const Point<3>& startBasePoint,
            const Point<3>& endBasePoint,
            double radius,
            double numTurns
        );
    };
}
