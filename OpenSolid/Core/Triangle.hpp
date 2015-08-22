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

#include <OpenSolid/Core/Triangle.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Simplex/TriangleBase.hpp>
#include <OpenSolid/Core/Transformable.hpp>

#include <utility>

namespace opensolid
{
    namespace detail
    {
        inline
        double
        crossProduct2d(const Point2d& p0, const Point2d& p1, const Point2d& p2) {
            double a1 = p1.x() - p0.x();
            double a2 = p1.y() - p0.y();
            double b1 = p2.x() - p0.x();
            double b2 = p2.y() - p0.y();
            return a1 * b2 - a2 * b1;
        }
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
    double
    Triangle2d::area() const {
        return 0.5 * detail::crossProduct2d(vertex(0), vertex(1), vertex(2));
    }

    inline
    Triangle3d
    Triangle2d::toGlobalFrom(const Plane3d& plane) const {
        return Triangle3d(
            vertex(0).toGlobalFrom(plane),
            vertex(1).toGlobalFrom(plane),
            vertex(2).toGlobalFrom(plane)
        );
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

    inline
    Triangle2d
    Triangle3d::toLocalIn(const Plane3d& plane) const {
        return Triangle2d(
            vertex(0).toLocalIn(plane),
            vertex(1).toLocalIn(plane),
            vertex(2).toLocalIn(plane)
        );
    }

    inline
    Triangle3d
    Triangle3d::projectedOnto(const Plane3d& plane) const {
        return Triangle3d(
            vertex(0).projectedOnto(plane),
            vertex(1).projectedOnto(plane),
            vertex(2).projectedOnto(plane)
        );
    }

    template <int iNumDimensions>
    bool
    EqualityFunction<Triangle<iNumDimensions>>::operator()(
        const Triangle<iNumDimensions>& firstTriangle,
        const Triangle<iNumDimensions>& secondTriangle,
        double precision
    ) const {
        return (
            equalityFunction(firstTriangle.vertex(0), secondTriangle.vertex(0), precision) &&
            equalityFunction(firstTriangle.vertex(1), secondTriangle.vertex(1), precision) &&
            equalityFunction(firstTriangle.vertex(2), secondTriangle.vertex(2), precision)
        );
    }
}
