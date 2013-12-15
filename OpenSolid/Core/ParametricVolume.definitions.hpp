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

#include <OpenSolid/Core/ParametricVolume.declarations.hpp>

#include <OpenSolid/Core/BoundedVolume.definitions.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

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
        public Transformable<ParametricVolume3d>
    {
    private:
        ParametricExpression<3, 3> _expression;
        BoundedVolume3d _domain;
        Box<3> _bounds;
    public:
        ParametricVolume3d();

        ParametricVolume3d(const ParametricVolume3d& other);

        ParametricVolume3d(ParametricVolume3d&& other);

        ParametricVolume3d(
            const ParametricExpression<3, 3>& expression,
            const BoundedVolume3d& domain
        );

        const ParametricExpression<3, 3>&
        expression() const;

        const BoundedVolume3d&
        domain() const;

        const Box<3>&
        bounds() const;

        Point<3>
        evaluate(double u, double v, double w) const;

        Box<3>
        evaluateBounds(Interval u, Interval v, Interval w) const;
    };

    template <>
    struct ScalingFunction<ParametricVolume3d>
    {
        ParametricVolume3d
        operator()(const ParametricVolume3d& parametricVolume, double scale) const;
    };

    template <>
    struct TranslationFunction<ParametricVolume3d>
    {
        ParametricVolume3d
        operator()(const ParametricVolume3d& parametricVolume, const Vector3d& vector) const;
    };

    template <>
    struct TransformationFunction<ParametricVolume3d, 3>
    {
        ParametricVolume3d
        operator()(const ParametricVolume3d& parametricVolume, const Matrix3d& matrix) const;
    };

    template <>
    struct MorphingFunction<ParametricVolume3d, 3>
    {
        ParametricVolume3d
        operator()(
            const ParametricVolume3d& parametricVolume,
            const ParametricExpression<3, 3>& morphingExpression
        ) const;
    };
}
