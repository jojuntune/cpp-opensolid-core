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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/ParametricCurve.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialSet.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

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
        const Point2d& originPoint,
        double scale
    ) const {
        return BoundedArea2d(
            SpatialSet<ParametricCurve2d>(
                boundedArea.boundaries().map(
                    [&originPoint, scale] (const ParametricCurve2d& curve) {
                        return scaled(curve, originPoint, scale);
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
                        return translated(curve, vector);
                    }
                )
            )
        );
    }

    const BoundedArea2d
    TransformationFunction<BoundedArea2d, 2>::operator()(
        const BoundedArea2d& boundedArea,
        const Point2d& originPoint,
        const Matrix2d& transformationMatrix,
        const Point2d& destinationPoint
    ) const {
        return BoundedArea2d(
            SpatialSet<ParametricCurve2d>(
                boundedArea.boundaries().map(
                    [&] (const ParametricCurve2d& curve) {
                        return transformed(
                            curve,
                            originPoint,
                            transformationMatrix,
                            destinationPoint
                        );
                    }
                )
            )
        );
    }

    const BoundedArea2d
    MorphingFunction<BoundedArea2d, ParametricExpression<Point2d, Point2d>>::operator()(
        const BoundedArea2d& boundedArea,
        const ParametricExpression<Point2d, Point2d>& morphingExpression
    ) const {
        return BoundedArea2d(
            SpatialSet<ParametricCurve2d>(
                boundedArea.boundaries().map(
                    [&morphingExpression] (const ParametricCurve2d& curve) {
                        return morphed(curve, morphingExpression);
                    }
                )
            )
        );
    }

    BoundedArea2d
    MirrorFunction<BoundedArea2d>::operator()(
        const BoundedArea2d& boundedArea,
        const Point2d& originPoint,
        const UnitVector2d& normalVector
    ) const {
        return BoundedArea2d(
            SpatialSet<ParametricCurve2d>(
                boundedArea.boundaries().map(
                    [&originPoint, &normalVector] (const ParametricCurve2d& curve) {
                        return mirrored(curve, originPoint, normalVector);
                    }
                )
            )
        );
    }

    BoundedArea2d
    ProjectionFunction<BoundedArea2d, Axis<2>>::operator()(
        const BoundedArea2d& boundedArea,
        const Axis2d& axis
    ) const {
        return BoundedArea2d(
            SpatialSet<ParametricCurve2d>(
                boundedArea.boundaries().map(
                    [&axis] (const ParametricCurve2d& curve) {
                        return projected(curve, axis);
                    }
                )
            )
        );
    }
}
