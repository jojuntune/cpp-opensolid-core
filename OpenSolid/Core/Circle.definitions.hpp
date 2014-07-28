/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#include <OpenSolid/Core/Circle.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>
#include <OpenSolid/Core/UnitVector.definitions.hpp>
#include <OpenSolid/Core/WindingDirection.definitions.hpp>

namespace opensolid
{
    template <>
    class Circle<2>
    {
    private:
        Point<2> _centerPoint;
        double _radius;
    public:
        Circle();

        Circle(const Point<2>& centerPoint, double radius);

        OPENSOLID_CORE_EXPORT
        Circle(
            double radius,
            WindingDirection windingDirection,
            const Point<2>& firstPoint,
            const Point<2>& secondPoint
        );

        OPENSOLID_CORE_EXPORT
        Circle(
            const Point<2>& firstPoint,
            const Point<2>& secondPoint,
            const Point<2>& thirdPoint
        );

        const Point<2>&
        centerPoint() const;

        double
        radius() const;

        static Circle<2>
        circumcircle(const Triangle<2>& triangle);
    };

    typedef Circle<2> Circle2d;

    template <>
    class Circle<3>
    {
    private:
        Point<3> _centerPoint;
        UnitVector<3> _normalVector;
        double _radius;
    public:
        Circle();

        Circle(const Point<3>& centerPoint, const UnitVector<3>& normalVector, double radius);

        Circle(const Plane3d& plane, double radius);

        Circle(const Axis<3>& axis, double radius);

        OPENSOLID_CORE_EXPORT
        Circle(
            const UnitVector<3>& normalVector,
            double radius,
            const Point<3>& startPoint,
            const Point<3>& secondPoint
        );

        OPENSOLID_CORE_EXPORT
        Circle(
            const Point<3>& startPoint,
            const Point<3>& secondPoint,
            const Point<3>& thirdPoint
        );

        const Point<3>&
        centerPoint() const;

        const UnitVector<3>&
        normalVector() const;

        double
        radius() const;

        Plane3d
        plane() const;

        Axis<3>
        axis() const;

        static Circle<3>
        circumcircle(const Triangle<3>& triangle);
    };

    typedef Circle<3> Circle3d;
}
