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

#include <OpenSolid/Core/BoundedVolume.declarations.hpp>

#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/ParametricSurface.definitions.hpp>
#include <OpenSolid/Core/SpatialSet.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    class BoundedVolume3d :
        public Transformable<BoundedVolume3d>
    {
    private:
        SpatialSet<ParametricSurface3d> _boundaries;
    public:
        BoundedVolume3d();

        BoundedVolume3d(const BoundedVolume3d& other);

        BoundedVolume3d(BoundedVolume3d&& other);

        BoundedVolume3d(const SpatialSet<ParametricSurface3d>& boundaries);

        BoundedVolume3d(SpatialSet<ParametricSurface3d>&& boundaries);

        const SpatialSet<ParametricSurface3d>&
        boundaries() const;

        bool
        isEmpty() const;

        Box<3>
        bounds() const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct ScalingFunction<BoundedVolume3d>
    {
        BoundedVolume3d
        operator()(const BoundedVolume3d& boundedVolume, double scale) const;
    };

    template <>
    struct TranslationFunction<BoundedVolume3d>
    {
        BoundedVolume3d
        operator()(const BoundedVolume3d& boundedVolume, const Vector3d& vector) const;
    };

    template <>
    struct TransformationFunction<BoundedVolume3d, 3>
    {
        BoundedVolume3d
        operator()(const BoundedVolume3d& boundedVolume, const Matrix3d& matrix) const;
    };

    namespace detail
    {
        BoundedVolume3d
        morphed(
            const BoundedVolume3d& boundedVolume,
            const ParametricExpression<3, 3>& morphingExpression
        );
    }
}
