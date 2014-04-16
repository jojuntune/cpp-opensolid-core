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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/BoundedVolume.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/ParametricSurface.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    BoundedVolume3d::BoundedVolume3d() {
    }

    BoundedVolume3d::BoundedVolume3d(const BoundedVolume3d& other) :
        _boundaries(other.boundaries()) {
    }

    BoundedVolume3d::BoundedVolume3d(BoundedVolume3d&& other) :
        _boundaries(std::move(other.boundaries())) {
    }

    BoundedVolume3d::BoundedVolume3d(const SpatialSet<ParametricSurface3d>& boundaries) :
        _boundaries(boundaries) {
    }

    BoundedVolume3d::BoundedVolume3d(SpatialSet<ParametricSurface3d>&& boundaries) :
        _boundaries(std::move(boundaries)) {
    }

    const BoundedVolume3d
    ScalingFunction<BoundedVolume3d>::operator()(
        const BoundedVolume3d& boundedVolume,
        double scale
    ) const {
        return BoundedVolume3d(
            SpatialSet<ParametricSurface3d>(
                boundedVolume.boundaries().map(
                    [scale] (const ParametricSurface3d& surface) {
                        return scalingFunction(surface, scale);
                    }
                )
            )
        );
    }

    const BoundedVolume3d
    TranslationFunction<BoundedVolume3d>::operator()(
        const BoundedVolume3d& boundedVolume,
        const Vector3d& vector
    ) const {
        return BoundedVolume3d(
            SpatialSet<ParametricSurface3d>(
                boundedVolume.boundaries().map(
                    [&vector] (const ParametricSurface3d& surface) {
                        return translationFunction(surface, vector);
                    }
                )
            )
        );
    }

    const BoundedVolume3d
    TransformationFunction<BoundedVolume3d, 3>::operator()(
        const BoundedVolume3d& boundedVolume,
        const Matrix3x3& matrix
    ) const {
        return BoundedVolume3d(
            SpatialSet<ParametricSurface3d>(
                boundedVolume.boundaries().map(
                    [&matrix] (const ParametricSurface3d& surface) {
                        return transformationFunction(surface, matrix);
                    }
                )
            )
        );
    }

    const BoundedVolume3d
    MorphingFunction<BoundedVolume3d, 3>::operator()(
        const BoundedVolume3d& boundedVolume,
        const ParametricExpression<3, 3>& morphingExpression
    ) const {
        return BoundedVolume3d(
            SpatialSet<ParametricSurface3d>(
                boundedVolume.boundaries().map(
                    [&morphingExpression] (const ParametricSurface3d& surface) {
                        return morphingFunction(surface, morphingExpression);
                    }
                )
            )
        );
    }
}
