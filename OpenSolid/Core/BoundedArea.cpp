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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/BoundedArea.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/ParametricCurve.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    BoundedArea2d::BoundedArea2d() {
    }

    BoundedArea2d::BoundedArea2d(const BoundedArea2d& other) :
        _boundaries(other.boundaries()) {
    }

    BoundedArea2d::BoundedArea2d(BoundedArea2d&& other) :
        _boundaries(std::move(other.boundaries())) {
    }

    BoundedArea2d::BoundedArea2d(const SpatialSet<ParametricCurve2d>& boundaries) :
        _boundaries(boundaries) {
    }

    BoundedArea2d::BoundedArea2d(SpatialSet<ParametricCurve2d>&& boundaries) :
        _boundaries(std::move(boundaries)) {
    }

    const BoundedArea2d
    ScalingFunction<BoundedArea2d>::operator()(
        const BoundedArea2d& boundedArea,
        double scale
    ) const {
        return BoundedArea2d(
            SpatialSet<ParametricCurve2d>(
                boundedArea.boundaries().map(
                    [scale] (const ParametricCurve2d& curve) {
                        return scalingFunction(curve, scale);
                    }
                )
            )
        );
    }

    const BoundedArea2d
    TranslationFunction<BoundedArea2d>::operator()(
        const BoundedArea2d& boundedArea,
        const Vector2d& vector
    ) const {
        return BoundedArea2d(
            SpatialSet<ParametricCurve2d>(
                boundedArea.boundaries().map(
                    [&vector] (const ParametricCurve2d& curve) {
                        return translationFunction(curve, vector);
                    }
                )
            )
        );
    }

    const BoundedArea2d
    TransformationFunction<BoundedArea2d, 2>::operator()(
        const BoundedArea2d& boundedArea,
        const Matrix2d& matrix
    ) const {
        return BoundedArea2d(
            SpatialSet<ParametricCurve2d>(
                boundedArea.boundaries().map(
                    [&matrix] (const ParametricCurve2d& curve) {
                        return transformationFunction(curve, matrix);
                    }
                )
            )
        );
    }

    const BoundedArea2d
    MorphingFunction<BoundedArea2d, 2>::operator()(
        const BoundedArea2d& boundedArea,
        const ParametricExpression<2, 2>& morphingExpression
    ) const {
        return BoundedArea2d(
            SpatialSet<ParametricCurve2d>(
                boundedArea.boundaries().map(
                    [&morphingExpression] (const ParametricCurve2d& curve) {
                        return morphingFunction(curve, morphingExpression);
                    }
                )
            )
        );
    }
}
