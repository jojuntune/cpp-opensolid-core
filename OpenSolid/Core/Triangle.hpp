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

#include <OpenSolid/Core/Triangle.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Simplex/TriangleBase.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    inline
    Triangle1d::Triangle() {
    }

    inline
    Triangle1d::Triangle(
        const Point1d& firstVertex,
        const Point1d& secondVertex,
        const Point1d& thirdVertex
    ) : detail::TriangleBase<1>(firstVertex, secondVertex, thirdVertex) {
    }

    inline
    Triangle2d::Triangle() {
    }

    inline
    Triangle2d::Triangle(
        const Point2d& firstVertex,
        const Point2d& secondVertex,
        const Point2d& thirdVertex
    ) : detail::TriangleBase<2>(firstVertex, secondVertex, thirdVertex) {
    }

    inline
    bool
    Triangle2d::contains(const Point2d& point, double precision) const {
        Point2d localCoordinates = point / coordinateSystem();
        double a = localCoordinates.x();
        double b = localCoordinates.y();
        Zero zero(precision);
        return a >= zero && b >= zero && 1 - a - b >= zero;
    }

    inline
    bool
    Triangle2d::strictlyContains(const Point<2>& point, double precision) const {
        Point2d localCoordinates = point / coordinateSystem();
        double a = localCoordinates.x();
        double b = localCoordinates.y();
        Zero zero(precision);
        return a > zero && b > zero && 1 - a - b > zero;
    }

    inline
    Triangle3d::Triangle() {
    }

    inline
    Triangle3d::Triangle(
        const Point3d& firstVertex,
        const Point3d& secondVertex,
        const Point3d& thirdVertex
    ) : detail::TriangleBase<3>(firstVertex, secondVertex, thirdVertex) {
    }

    template <int iNumDimensions>
    bool
    EqualityFunction<Triangle<iNumDimensions>>::operator()(
        const Triangle<iNumDimensions>& firstTriangle,
        const Triangle<iNumDimensions>& secondTriangle,
        double precision
    ) const {
        return equalityFunction(firstTriangle.vertex(0), secondTriangle.vertex(0), precision) &&
            equalityFunction(firstTriangle.vertex(1), secondTriangle.vertex(1), precision) &&
            equalityFunction(firstTriangle.vertex(2), secondTriangle.vertex(2), precision);
    }

    template <int iNumDimensions>
    Triangle<iNumDimensions>
    ScalingFunction<Triangle<iNumDimensions>>::operator()(
        const Triangle<iNumDimensions>& triangle,
        double scale
    ) const {
        return Triangle<iNumDimensions>(
            scalingFunction(triangle.vertex(0), scale),
            scalingFunction(triangle.vertex(1), scale),
            scalingFunction(triangle.vertex(2), scale)
        );
    }

    template <int iNumDimensions> template <class TVector>
    Triangle<iNumDimensions>
    TranslationFunction<Triangle<iNumDimensions>>::operator()(
        const Triangle<iNumDimensions>& triangle,
        const EigenBase<TVector>& vector
    ) const {
        return Triangle<iNumDimensions>(
            translationFunction(triangle.vertex(0), vector.derived()),
            translationFunction(triangle.vertex(1), vector.derived()),
            translationFunction(triangle.vertex(2), vector.derived())
        );
    }

    template <int iNumDimensions, int iNumResultDimensions> template <class TMatrix>
    Triangle<iNumResultDimensions>
    TransformationFunction<Triangle<iNumDimensions>, iNumResultDimensions>::operator()(
        const Triangle<iNumDimensions>& triangle,
        const EigenBase<TMatrix>& matrix
    ) const {
        return Triangle<iNumResultDimensions>(
            transformationFunction(triangle.vertex(0), matrix.derived()),
            transformationFunction(triangle.vertex(1), matrix.derived()),
            transformationFunction(triangle.vertex(2), matrix.derived())
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    Triangle<iNumResultDimensions>
    MorphingFunction<Triangle<iNumDimensions>, iNumResultDimensions>::operator()(
        const Triangle<iNumDimensions>& triangle,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return Triangle<iNumResultDimensions>(
            morphingFunction(triangle.vertex(0), morphingExpression),
            morphingFunction(triangle.vertex(1), morphingExpression),
            morphingFunction(triangle.vertex(2), morphingExpression)
        );
    }
}
