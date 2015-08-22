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

#include <OpenSolid/Core/ParametricVolume.declarations.hpp>

#include <OpenSolid/Core/BoundedVolume.definitions.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Handedness.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>

namespace opensolid
{
    template <>
    struct BoundsType<ParametricVolume3d>
    {
        typedef Box<3> Type;
    };

    template <>
    struct NumDimensions<ParametricVolume3d>
    {
        static const int Value = 3;
    };

    class ParametricVolume3d :
        public Transformable<ParametricVolume3d, Point<3>>
    {
    private:
        ParametricExpression<Point<3>, Point<3>> _expression;
        BoundedVolume3d _domain;
        Handedness _handedness;
        Box<3> _bounds;
    public:
        OPENSOLID_CORE_EXPORT
        ParametricVolume3d();

        OPENSOLID_CORE_EXPORT
        ParametricVolume3d(const ParametricVolume3d& other);

        OPENSOLID_CORE_EXPORT
        ParametricVolume3d(ParametricVolume3d&& other);

        OPENSOLID_CORE_EXPORT
        ParametricVolume3d(
            const ParametricExpression<Point<3>, Point<3>>& expression,
            const BoundedVolume3d& domain
        );

        OPENSOLID_CORE_EXPORT
        ParametricVolume3d(
            const ParametricExpression<Point<3>, Point<3>>& expression,
            const BoundedVolume3d& domain,
            Handedness handedness
        );

        const ParametricExpression<Point<3>, Point<3>>&
        expression() const;

        const BoundedVolume3d&
        domain() const;

        Handedness
        handedness() const;

        const Box<3>&
        bounds() const;

        OPENSOLID_CORE_EXPORT
        Point<3>
        evaluate(const Point<3>& parameterValues) const;

        OPENSOLID_CORE_EXPORT
        Box<3>
        evaluate(const Box<3>& parameterBounds) const;

        template <class TTransformation>
        ParametricVolume3d
        transformedBy(const TTransformation& transformation) const;
    };
}
