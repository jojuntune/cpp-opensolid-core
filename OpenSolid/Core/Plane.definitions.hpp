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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Plane.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/FrameBase.definitions.hpp>
#include <OpenSolid/Core/Handedness.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.definitions.hpp>

namespace opensolid
{
    template <>
    struct NumDimensions<Plane3d>
    {
        static const int Value = 3;
    };

    class Plane3d :
        public Convertible<Plane3d>,
        public Transformable<Plane3d, Point<3>>,
        public FrameBase<3, 2>
    {
    private:
        UnitVector<3> _normalVector;
        Handedness _handedness;
    public:
        OPENSOLID_CORE_EXPORT
        Plane3d();

        OPENSOLID_CORE_EXPORT
        Plane3d(
            const Point<3>& originPoint,
            const UnitVector<3>& xDirectionVector,
            const UnitVector<3>& yDirectionVector
        );

        OPENSOLID_CORE_EXPORT
        Plane3d(const Point<3>& originPoint, const UnitVector<3>& normalVector);

        OPENSOLID_CORE_EXPORT
        Plane3d(
            const Point<3>& originPoint,
            const UnitVector<3>& xDirectionVector,
            const UnitVector<3>& yDirectionVector,
            const UnitVector<3>& normalVector
        );

        OPENSOLID_CORE_EXPORT
        Plane3d(
            const Point<3>& originPoint,
            const UnitVector<3>& xDirectionVector,
            const UnitVector<3>& yDirectionVector,
            Handedness handedness
        );

        OPENSOLID_CORE_EXPORT
        Plane3d(
            const Point<3>& originPoint,
            const UnitVector<3>& xDirectionVector,
            const UnitVector<3>& yDirectionVector,
            const UnitVector<3>& normalVector,
            Handedness handedness
        );

        OPENSOLID_CORE_EXPORT
        static Plane3d
        throughPoints(
            const Point<3>& firstPoint,
            const Point<3>& secondPoint,
            const Point<3>& thirdPoint
        );

        OPENSOLID_CORE_EXPORT
        static Plane3d
        midplane(const Point<3>& pointBelow, const Point<3>& pointAbove);

        OPENSOLID_CORE_EXPORT
        static Plane3d
        midplane(const Plane3d& planeBelow, const Plane3d& planeAbove);

        OPENSOLID_CORE_EXPORT
        static Plane3d
        throughAxisAndPoint(const Axis<3>& axis, const Point<3>& point);

        OPENSOLID_CORE_EXPORT
        static Plane3d
        throughAxis(const Axis<3>& axis);

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

        UnitVector<3>
        xDirectionVector() const;

        UnitVector<3>
        yDirectionVector() const;

        const UnitVector<3>&
        normalVector() const;

        Handedness
        handedness() const;

        OPENSOLID_CORE_EXPORT
        Plane3d
        offsetBy(double distance) const;

        OPENSOLID_CORE_EXPORT
        Plane3d
        flipped() const;

        OPENSOLID_CORE_EXPORT
        Axis<3>
        normalAxis() const;

        template <class TTransformation>
        Plane3d
        transformedBy(const TTransformation& transformation) const;

        OPENSOLID_CORE_EXPORT
        ParametricExpression<Point<3>, Point<2>>
        expression() const;
    };
}
