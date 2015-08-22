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

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/LineSegmentPlaneIntersection3d.hpp>
#include <OpenSolid/Core/Simplex/LineSegmentBase.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    inline
    LineSegment2d::LineSegment() :
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    LineSegment2d::LineSegment(const Point2d& startVertex, const Point2d& endVertex) :
        detail::LineSegmentBase<2>(startVertex, endVertex),
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    LineSegment2d::LineSegment(
        const Point2d& startVertex,
        const Point2d& endVertex,
        Handedness handedness
    ) : detail::LineSegmentBase<2>(startVertex, endVertex),
        _handedness(handedness) {
    }

    inline
    Handedness
    LineSegment2d::handedness() const {
        return _handedness;
    }

    inline
    UnitVector2d
    LineSegment2d::normalVector() const {
        return handedness().sign() * vector().unitOrthogonal();
    }

    inline
    Axis2d
    LineSegment2d::axis() const {
        return Axis2d(startVertex(), vector().normalized(), handedness());
    }

    template <class TTransformation>
    inline
    LineSegment2d
    LineSegment2d::transformedBy(const TTransformation& transformation) const {
        return LineSegment2d(
            startVertex().transformedBy(transformation),
            endVertex().transformedBy(transformation),
            handedness().transformedBy(transformation)
        );
    }

    inline
    LineSegment3d
    LineSegment2d::placedOnto(const Plane3d& plane) const {
        return LineSegment3d(startVertex().placedOnto(plane), endVertex().placedOnto(plane));
    }

    inline
    LineSegment3d::LineSegment() {
    }

    inline
    LineSegment3d::LineSegment(const Point3d& startVertex, const Point3d& endVertex) :
        detail::LineSegmentBase<3>(startVertex, endVertex) {
    }

    inline
    UnitVector3d
    LineSegment3d::normalVector() const {
        return vector().unitOrthogonal();
    }

    inline
    Axis3d
    LineSegment3d::axis() const {
        return Axis3d(startVertex(), vector().normalized());
    }

    inline
    Intersection<LineSegment3d, Plane3d>
    LineSegment3d::intersection(const Plane3d& plane, double precision) const {
        return Intersection<LineSegment3d, Plane3d>(*this, plane, precision);
    }

    template <class TTransformation>
    inline
    LineSegment3d
    LineSegment3d::transformedBy(const TTransformation& transformation) const {
        return LineSegment3d(
            startVertex().transformedBy(transformation),
            endVertex().transformedBy(transformation)
        );
    }

    inline
    LineSegment2d
    LineSegment3d::projectedInto(const Plane3d& plane) const {
        return LineSegment2d(startVertex().projectedInto(plane), endVertex().projectedInto(plane));
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
