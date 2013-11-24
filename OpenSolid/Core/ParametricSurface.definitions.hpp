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

#include <OpenSolid/Core/ParametricSurface.declarations.hpp>

#include <OpenSolid/Core/BoundedArea.definitions.hpp>
#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    class ParametricSurface3d :
        public Transformable<ParametricSurface3d>
    {
    private:
        ParametricExpression<3, 2> _expression;
        BoundedArea2d _domain;
        Box<3> _bounds;
    public:
        ParametricSurface3d();

        ParametricSurface3d(const ParametricSurface3d& other);

        ParametricSurface3d(ParametricSurface3d&& other);

        ParametricSurface3d(
            const ParametricExpression<3, 2>& expression,
            const BoundedArea2d& domain
        );

        const ParametricExpression<3, 2>&
        expression() const;

        const BoundedArea2d&
        domain() const;

        const Box<3>&
        bounds() const;

        Point<3>
        evaluate(double u, double v) const;

        Box<3>
        evaluate(Interval u, Interval v) const;

        ParametricExpression<3, 2>
        normalVector() const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct ScalingFunction<ParametricSurface3d>
    {
        ParametricSurface3d
        operator()(const ParametricSurface3d& surface, double scale) const;
    };

    template <>
    struct TranslationFunction<ParametricSurface3d>
    {
        ParametricSurface3d
        operator()(const ParametricSurface3d& surface, const Vector3d& vector) const;
    };

    template <>
    struct TransformationFunction<ParametricSurface3d, 3>
    {
        ParametricSurface3d
        operator()(const ParametricSurface3d& surface, const Matrix3d& matrix) const;
    };

    template <>
    struct MorphingFunction<ParametricSurface3d, 3>
    {
        ParametricSurface3d
        operator()(
            const ParametricSurface3d& surface,
            const ParametricExpression<3, 3>& morphingExpression
        ) const;
    };
}
