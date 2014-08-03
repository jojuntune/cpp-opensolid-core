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

#include <OpenSolid/Core/ParametricArea.declarations.hpp>

#include <OpenSolid/Core/BoundedArea.definitions.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    template <>
    struct BoundsType<ParametricArea2d>
    {
        typedef Box<2> Type;
    };

    template <>
    struct NumDimensions<ParametricArea2d>
    {
        static const int Value = 2;
    };

    template <>
    struct MorphedType<ParametricArea2d, ParametricExpression<Point<2>, Point<2>>>
    {
        typedef ParametricArea2d Type;
    };

    class ParametricArea2d :
        public Transformable<ParametricArea2d>
    {
    private:
        ParametricExpression<Point<2>, Point<2>> _expression;
        BoundedArea2d _domain;
        Box<2> _bounds;
    public:
        ParametricArea2d();

        ParametricArea2d(const ParametricArea2d& other);

        ParametricArea2d(ParametricArea2d&& other);

        ParametricArea2d(
            const ParametricExpression<Point<2>, Point<2>>& expression,
            const BoundedArea2d& domain
        );

        const ParametricExpression<Point<2>, Point<2>>&
        expression() const;

        const BoundedArea2d&
        domain() const;

        const Box<2>&
        bounds() const;

        Point<2>
        evaluate(const Point<2>& parameterValue) const;

        Box<2>
        evaluate(const Box<2>& parameterBounds) const;
    };
    
    template <>
    struct ScalingFunction<ParametricArea2d>
    {
        ParametricArea2d
        operator()(
            const ParametricArea2d& parametricArea,
            const Point<2>& originPoint,
            double scale
        ) const;
    };

    template <>
    struct TranslationFunction<ParametricArea2d>
    {
        ParametricArea2d
        operator()(const ParametricArea2d& parametricArea, const Vector<double, 2>& vector) const;
    };

    template <>
    struct TransformationFunction<ParametricArea2d, 2>
    {
        ParametricArea2d
        operator()(
            const ParametricArea2d& parametricArea,
            const Point<2>& originPoint,
            const Matrix<double, 2, 2>& transformationMatrix,
            const Point<2>& destinationPoint
        ) const;
    };

    template <>
    struct MorphingFunction<ParametricArea2d, ParametricExpression<Point<2>, Point<2>>>
    {
        ParametricArea2d
        operator()(
            const ParametricArea2d& parametricArea,
            const ParametricExpression<Point<2>, Point<2>>& morphingExpression
        ) const;
    };
}
