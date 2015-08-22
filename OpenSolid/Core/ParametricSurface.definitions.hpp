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

#include <OpenSolid/Core/ParametricSurface.declarations.hpp>

#include <OpenSolid/Core/BoundedArea.definitions.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/Handedness.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricArea.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>

namespace opensolid
{
    template <>
    struct BoundsType<ParametricSurface3d>
    {
        typedef Box<3> Type;
    };

    template <>
    struct NumDimensions<ParametricSurface3d>
    {
        static const int Value = 3;
    };

    class ParametricSurface3d :
        public Transformable<ParametricSurface3d, Point<3>>
    {
    private:
        ParametricExpression<Point<3>, Point<2>> _expression;
        BoundedArea2d _domain;
        Handedness _handedness;
        Box<3> _bounds;
    public:
        OPENSOLID_CORE_EXPORT
        ParametricSurface3d();

        OPENSOLID_CORE_EXPORT
        ParametricSurface3d(const ParametricSurface3d& other);

        OPENSOLID_CORE_EXPORT
        ParametricSurface3d(ParametricSurface3d&& other);

        OPENSOLID_CORE_EXPORT
        ParametricSurface3d(
            const ParametricExpression<Point<3>, Point<2>>& expression,
            const BoundedArea2d& domain
        );

        OPENSOLID_CORE_EXPORT
        ParametricSurface3d(
            const ParametricExpression<Point<3>, Point<2>>& expression,
            const BoundedArea2d& domain,
            Handedness handedness
        );

        const ParametricExpression<Point<3>, Point<2>>&
        expression() const;

        const BoundedArea2d&
        domain() const;

        Handedness
        handedness() const;

        const Box<3>&
        bounds() const;

        OPENSOLID_CORE_EXPORT
        Point<3>
        evaluate(const Point<2>& parameterValues) const;

        OPENSOLID_CORE_EXPORT
        Box<3>
        evaluate(const Box<2>& parameterBounds) const;

        OPENSOLID_CORE_EXPORT
        ParametricExpression<UnitVector<3>, Point<2>>
        normalVector() const;

        template <class TTransformation>
        ParametricSurface3d
        transformedBy(const TTransformation& transformation) const;

        OPENSOLID_CORE_EXPORT
        ParametricArea2d
        projectedInto(const Plane3d& plane) const;

        OPENSOLID_CORE_EXPORT
        ParametricSurface3d
        projectedOnto(const Plane3d& plane) const;
    };
}
