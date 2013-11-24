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

#include <OpenSolid/Core/BoundedArea.declarations.hpp>

#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/ParametricCurve.declarations.hpp>
#include <OpenSolid/Core/SpatialSet.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    class BoundedArea2d :
        public Transformable<BoundedArea2d>
    {
    private:
        SpatialSet<ParametricCurve<2>> _boundaries;
    public:
        BoundedArea2d();

        BoundedArea2d(const BoundedArea2d& other);

        BoundedArea2d(BoundedArea2d&& other);

        BoundedArea2d(const SpatialSet<ParametricCurve<2>>& boundaries);

        BoundedArea2d(SpatialSet<ParametricCurve<2>>&& boundaries);

        const SpatialSet<ParametricCurve<2>>&
        boundaries() const;

        bool
        isEmpty() const;

        const Box<2>&
        bounds() const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct ScalingFunction<BoundedArea2d>
    {
        BoundedArea2d
        operator()(const BoundedArea2d& boundedArea, double scale) const;
    };

    template <>
    struct TranslationFunction<BoundedArea2d>
    {
        BoundedArea2d
        operator()(const BoundedArea2d& boundedArea, const Vector2d& vector) const;
    };

    template <>
    struct TransformationFunction<BoundedArea2d, 2>
    {
        BoundedArea2d
        operator()(const BoundedArea2d& boundedArea, const Matrix2d& matrix) const;
    };

    template <>
    struct MorphingFunction<BoundedArea2d, 2>
    {
        BoundedArea2d
        operator()(
            const BoundedArea2d& boundedArea,
            const ParametricExpression<2, 2>& morphingExpression
        ) const;
    };
}
