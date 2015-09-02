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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/LineSegmentPlaneIntersection3d.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        const LineSegment<iNumDimensions>&
        LineSegmentCommon<iNumDimensions>::derived() const {
            return static_cast<const LineSegment<iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        LineSegmentCommon<iNumDimensions>::LineSegmentCommon() {
        }

        template <int iNumDimensions>
        inline
        LineSegmentCommon<iNumDimensions>::LineSegmentCommon(
            const Point<iNumDimensions>& startVertex,
            const Point<iNumDimensions>& endVertex
        ) {
            _vertices[0] = startVertex;
            _vertices[1] = endVertex;
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        LineSegmentCommon<iNumDimensions>::startVertex() const {
            return _vertices[0];
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        LineSegmentCommon<iNumDimensions>::endVertex() const {
            return _vertices[1];
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        LineSegmentCommon<iNumDimensions>::vertex(int index) const {
            assert(index == 0 || index == 1);
            return _vertices[index];
        }

        template <int iNumDimensions>
        inline
        SimplexVertices<LineSegment<iNumDimensions>, 2>
        LineSegmentCommon<iNumDimensions>::vertices() const {
            return SimplexVertices<LineSegment<iNumDimensions>, 2>(derived());
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        LineSegmentCommon<iNumDimensions>::centroid() const {
            return startVertex() + 0.5 * vector();
        }

        template <int iNumDimensions>
        inline
        double
        LineSegmentCommon<iNumDimensions>::length() const {
            return vector().norm();
        }

        template <int iNumDimensions>
        inline
        double
        LineSegmentCommon<iNumDimensions>::squaredLength() const {
            return vector().squaredNorm();
        }

        template<int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        LineSegmentCommon<iNumDimensions>::vector() const {
            return endVertex() - startVertex();
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        LineSegmentCommon<iNumDimensions>::bounds() const {
            return startVertex().hull(endVertex());
        }
    }

    inline
    LineSegment2d::LineSegment() {
    }

    inline
    LineSegment2d::LineSegment(const Point2d& startVertex, const Point2d& endVertex) :
        detail::LineSegmentCommon<2>(startVertex, endVertex),
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    LineSegment2d::LineSegment(
        const Point2d& startVertex,
        const Point2d& endVertex,
        Handedness handedness
    ) : detail::LineSegmentCommon<2>(startVertex, endVertex),
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
    bool
    LineSegment2d::operator==(const LineSegment2d& other) const {
        return (
            startVertex() == other.startVertex() &&
            endVertex() == other.endVertex() &&
            handedness() == other.handedness()
        );
    }

    inline
    bool
    LineSegment2d::equals(const LineSegment2d& other, double precision) const {
        return (
            startVertex().equals(other.startVertex(), precision) &&
            endVertex().equals(other.endVertex(), precision) &&
            handedness() == other.handedness()
        );
    }

    inline
    LineSegment3d::LineSegment() {
    }

    inline
    LineSegment3d::LineSegment(const Point3d& startVertex, const Point3d& endVertex) :
        detail::LineSegmentCommon<3>(startVertex, endVertex) {
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

    inline
    bool
    LineSegment3d::operator==(const LineSegment3d& other) const {
        return startVertex() == other.startVertex() && endVertex() == other.endVertex();
    }

    inline
    bool
    LineSegment3d::equals(const LineSegment3d& other, double precision) const {
        return (
            startVertex().equals(other.startVertex(), precision) &&
            endVertex().equals(other.endVertex(), precision)
        );
    }
}
