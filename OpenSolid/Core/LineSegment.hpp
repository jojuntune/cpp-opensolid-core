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

#include <OpenSolid/Core/LineSegment.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/LineSegmentPlaneIntersection3d.hpp>
#include <OpenSolid/Core/Simplex/LineSegmentBase.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    inline
    LineSegment2d::LineSegment() {
    }

    inline
    LineSegment2d::LineSegment(const Point2d& startVertex, const Point2d& endVertex) :
        detail::LineSegmentBase<2>(startVertex, endVertex) {
    }

    inline
    LineSegment3d
    LineSegment2d::toGlobalFrom(const Plane3d& plane) const {
        return LineSegment3d(startVertex().toGlobalFrom(plane), endVertex().toGlobalFrom(plane));
    }

    inline
    LineSegment3d::LineSegment() {
    }

    inline
    LineSegment3d::LineSegment(const Point3d& startVertex, const Point3d& endVertex) :
        detail::LineSegmentBase<3>(startVertex, endVertex) {
    }

    inline
    Intersection<LineSegment3d, Plane3d>
    LineSegment3d::intersection(const Plane3d& plane, double precision) const {
        return Intersection<LineSegment3d, Plane3d>(*this, plane, precision);
    }

    inline
    LineSegment2d
    LineSegment3d::toLocalIn(const Plane3d& plane) const {
        return LineSegment2d(startVertex().toLocalIn(plane), endVertex().toLocalIn(plane));
    }

    inline
    LineSegment3d
    LineSegment3d::projectedOnto(const Plane3d& plane) const {
        return LineSegment3d(startVertex().projectedOnto(plane), endVertex().projectedOnto(plane));
    }

    template <int iNumDimensions>
    inline
    bool
    EqualityFunction<LineSegment<iNumDimensions>>::operator()(
        const LineSegment<iNumDimensions>& firstLineSegment,
        const LineSegment<iNumDimensions>& secondLineSegment,
        double precision
    ) const {
        return equalityFunction(
            firstLineSegment.startVertex(),
            secondLineSegment.startVertex(),
            precision
        ) && equalityFunction(
            firstLineSegment.endVertex(),
            secondLineSegment.endVertex(),
            precision
        );
    }
}
