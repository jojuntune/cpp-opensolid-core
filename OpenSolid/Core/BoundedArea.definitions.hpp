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

#include <OpenSolid/Core/BoundedArea.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/ParametricCurve.definitions.hpp>
#include <OpenSolid/Core/SpatialSet.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    template <>
    struct BoundsType<BoundedArea2d>
    {
        typedef Box<2> Type;
    };

    template <>
    struct NumDimensions<BoundedArea2d>
    {
        static const int Value = 2;
    };

    class BoundedArea2d :
        public Transformable<BoundedArea2d>
    {
    private:
        SpatialSet<ParametricCurve2d> _boundaries;
    public:
        OPENSOLID_CORE_EXPORT
        BoundedArea2d();

        OPENSOLID_CORE_EXPORT
        BoundedArea2d(const BoundedArea2d& other);

        OPENSOLID_CORE_EXPORT
        BoundedArea2d(BoundedArea2d&& other);

        OPENSOLID_CORE_EXPORT
        BoundedArea2d(const SpatialSet<ParametricCurve2d>& boundaries);

        OPENSOLID_CORE_EXPORT
        BoundedArea2d(SpatialSet<ParametricCurve2d>&& boundaries);

        const SpatialSet<ParametricCurve2d>&
        boundaries() const;

        bool
        isEmpty() const;

        const Box<2>
        bounds() const;
    };
    
    template <>
    struct ScalingFunction<BoundedArea2d>
    {
        OPENSOLID_CORE_EXPORT
        const BoundedArea2d
        operator()(
            const BoundedArea2d& boundedArea,
            const Point<2>& originPoint,
            double scale
        ) const;
    };

    template <>
    struct TranslationFunction<BoundedArea2d>
    {
        OPENSOLID_CORE_EXPORT
        const BoundedArea2d
        operator()(const BoundedArea2d& boundedArea, const Vector<double, 2>& vector) const;
    };

    template <>
    struct TransformationFunction<BoundedArea2d, 2>
    {
        OPENSOLID_CORE_EXPORT
        const BoundedArea2d
        operator()(
            const BoundedArea2d& boundedArea,
            const Point<2>& originPoint,
            const Matrix<double, 2, 2>& transformationMatrix,
            const Point<2>& destinationPoint
        ) const;
    };

    template <>
    struct MorphingFunction<BoundedArea2d, 2>
    {
        OPENSOLID_CORE_EXPORT
        const BoundedArea2d
        operator()(
            const BoundedArea2d& boundedArea,
            const ParametricExpression<2, 2>& morphingExpression
        ) const;
    };
}
