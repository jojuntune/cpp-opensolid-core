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

#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Handedness.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.hpp>
#include <OpenSolid/Core/Simplex/TriangleEdges.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

#include <utility>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        const Triangle<iNumDimensions>&
        TriangleCommon<iNumDimensions>::derived() const {
            return static_cast<const Triangle<iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        TriangleCommon<iNumDimensions>::TriangleCommon() :
            _handedness(Handedness::RIGHT_HANDED()) {
        }

        template <int iNumDimensions>
        inline
        TriangleCommon<iNumDimensions>::TriangleCommon(
            const Point<iNumDimensions>& firstVertex,
            const Point<iNumDimensions>& secondVertex,
            const Point<iNumDimensions>& thirdVertex,
            Handedness handedness
        ) : _handedness(handedness) {

            _vertices[0] = firstVertex;
            _vertices[1] = secondVertex;
            _vertices[2] = thirdVertex;
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        TriangleCommon<iNumDimensions>::vertex(int index) const {
            assert(index >= 0 && index < 3);
            return _vertices[index];
        }

        template <int iNumDimensions>
        inline
        Handedness
        TriangleCommon<iNumDimensions>::handedness() const {
            return _handedness;
        }

        template <int iNumDimensions>
        inline
        SimplexVertices<Triangle<iNumDimensions>, 3>
        TriangleCommon<iNumDimensions>::vertices() const {
            return SimplexVertices<Triangle<iNumDimensions>, 3>(derived());
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        TriangleCommon<iNumDimensions>::centroid() const {
            return vertex(0) + ((vertex(1) - vertex(0)) + (vertex(2) - vertex(0))) / 3.0;
        }

        template <int iNumDimensions>
        inline
        TriangleEdges<iNumDimensions>
        TriangleCommon<iNumDimensions>::edges() const {
            return TriangleEdges<iNumDimensions>(derived());
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        TriangleCommon<iNumDimensions>::bounds() const {
            return vertex(0).hull(vertex(1)).hull(vertex(2));
        }

        template <int iNumDimensions> template <class TTransformation>
        inline
        Triangle<iNumDimensions>
        TriangleCommon<iNumDimensions>::transformedBy(const TTransformation& transformation) const {
            return Triangle<iNumDimensions>(
                vertex(0).transformedBy(transformation),
                vertex(1).transformedBy(transformation),
                vertex(2).transformedBy(transformation),
                handedness().transformedBy(transformation)
            );
        }

        template <int iNumDimensions>
        inline
        bool
        TriangleCommon<iNumDimensions>::operator==(const Triangle<iNumDimensions>& other) const {
            return (
                vertex(0) == other.vertex(0) &&
                vertex(1) == other.vertex(1) &&
                vertex(2) == other.vertex(2) &&
                handedness() == other.handedness()
            );
        }

        template <int iNumDimensions>
        bool
        TriangleCommon<iNumDimensions>::equals(
            const Triangle<iNumDimensions>& other,
            double precision
        ) const {
            return (
                vertex(0).equals(other.vertex(0), precision) &&
                vertex(1).equals(other.vertex(1), precision) &&
                vertex(2).equals(other.vertex(2), precision) &&
                handedness() == other.handedness()
            );
        }

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
    ) : detail::TriangleCommon<2>(
            firstVertex,
            secondVertex,
            thirdVertex,
            Handedness::RIGHT_HANDED()
        ) {
    }

    inline
    Triangle2d::Triangle(
        const Point2d& firstVertex,
        const Point2d& secondVertex,
        const Point2d& thirdVertex,
        Handedness handedness
    ) : detail::TriangleCommon<2>(firstVertex, secondVertex, thirdVertex, handedness) {
    }

    inline
    LineSegment2d
    Triangle2d::edge(int oppositeIndex) const {
        assert(oppositeIndex >= 0 && oppositeIndex < 3);
        return LineSegment2d(
            vertex((oppositeIndex + 2) % 3),
            vertex((oppositeIndex + 1) % 3),
            handedness()
        );
    }

    inline
    double
    Triangle2d::area() const {
        return handedness().sign() * 0.5 * detail::crossProduct2d(vertex(0), vertex(1), vertex(2));
    }

    inline
    Triangle3d
    Triangle2d::placedOnto(const Plane3d& plane) const {
        return Triangle3d(
            vertex(0).placedOnto(plane),
            vertex(1).placedOnto(plane),
            vertex(2).placedOnto(plane),
            handedness()
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
    ) : detail::TriangleCommon<3>(
            firstVertex,
            secondVertex,
            thirdVertex,
            Handedness::RIGHT_HANDED()
        ) {
    }

    inline
    Triangle3d::Triangle(
        const Point3d& firstVertex,
        const Point3d& secondVertex,
        const Point3d& thirdVertex,
        Handedness handedness
    ) : detail::TriangleCommon<3>(firstVertex, secondVertex, thirdVertex, handedness) {
    }

    inline
    LineSegment3d
    Triangle3d::edge(int oppositeIndex) const {
        assert(oppositeIndex >= 0 && oppositeIndex < 3);
        return LineSegment3d(
            vertex((oppositeIndex + 2) % 3),
            vertex((oppositeIndex + 1) % 3)
        );
    }

    inline
    Triangle2d
    Triangle3d::projectedInto(const Plane3d& plane) const {
        return Triangle2d(
            vertex(0).projectedInto(plane),
            vertex(1).projectedInto(plane),
            vertex(2).projectedInto(plane),
            handedness() * plane.handedness()
        );
    }

    inline
    Triangle3d
    Triangle3d::projectedOnto(const Plane3d& plane) const {
        return Triangle3d(
            vertex(0).projectedOnto(plane),
            vertex(1).projectedOnto(plane),
            vertex(2).projectedOnto(plane),
            handedness()
        );
    }
}
