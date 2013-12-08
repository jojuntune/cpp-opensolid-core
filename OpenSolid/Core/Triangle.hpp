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

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialCollection.hpp>
#include <OpenSolid/Core/SpatialCollection/IndexIterator.hpp>
#include <OpenSolid/Core/SpatialCollection/SimplexVertices.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        TriangleEdges<iNumDimensions>::TriangleEdges(const Triangle<iNumDimensions>& triangle) :
            _triangle(triangle) {
        }

        template <int iNumDimensions>
        inline
        const Triangle<iNumDimensions>&
        TriangleEdges<iNumDimensions>::triangle() const {
            return _triangle;
        }

        template <int iNumDimensions>
        inline
        IndexIterator<TriangleEdges<iNumDimensions>>
        TriangleEdges<iNumDimensions>::begin() const {
            return IndexIterator<TriangleEdges<iNumDimensions>>::Begin(this);
        }

        template <int iNumDimensions>
        inline
        IndexIterator<TriangleEdges<iNumDimensions>>
        TriangleEdges<iNumDimensions>::end() const {
            return IndexIterator<TriangleEdges<iNumDimensions>>::End(this);
        }

        template <int iNumDimensions>
        inline
        bool
        TriangleEdges<iNumDimensions>::isEmpty() const {
            return false;
        }

        template <int iNumDimensions>
        inline
        std::int64_t
        TriangleEdges<iNumDimensions>::size() const {
            return 3;
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        TriangleEdges<iNumDimensions>::bounds() const {
            return triangle().bounds();
        }

        template <int iNumDimensions>
        inline
        LineSegment<iNumDimensions>
        TriangleEdges<iNumDimensions>::operator[](std::int64_t index) const {
            return triangle().edge(index);
        }

        template <int iNumDimensions>
        const Triangle<iNumDimensions>&
        TriangleBase<iNumDimensions>::derived() const {
            return static_cast<const Triangle<iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        TriangleBase<iNumDimensions>::TriangleBase() {
        }

        template <int iNumDimensions>
        inline
        TriangleBase<iNumDimensions>::TriangleBase(
            const Point<iNumDimensions>& firstVertex,
            const Point<iNumDimensions>& secondVertex,
            const Point<iNumDimensions>& thirdVertex
        ) {
            _vertices[0] = firstVertex;
            _vertices[1] = secondVertex;
            _vertices[2] = thirdVertex;
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        TriangleBase<iNumDimensions>::vertex(int index) const {
            assert(index >= 0 && index < 3);
            return _vertices[index];
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>&
        TriangleBase<iNumDimensions>::vertex(int index) {
            assert(index >= 0 && index < 3);
            return _vertices[index];
        }

        template <int iNumDimensions>
        SimplexVertices<Triangle<iNumDimensions>, 3>
        TriangleBase<iNumDimensions>::vertices() const {
            return SimplexVertices<Triangle<iNumDimensions>, 3>(derived());
        }

        template <int iNumDimensions>
        Point<iNumDimensions>
        TriangleBase<iNumDimensions>::centroid() const {
            return Point<iNumDimensions>(
                (vertex(0).vector() + vertex(1).vector() + vertex(2).vector()) / 3.0
            );
        }

        template <int iNumDimensions>
        inline
        LineSegment<iNumDimensions>
        TriangleBase<iNumDimensions>::edge(int oppositeIndex) const {
            assert(oppositeIndex >= 0 && oppositeIndex < 3);
            return LineSegment<iNumDimensions>(
                vertex((oppositeIndex + 1) % 3),
                vertex((oppositeIndex + 2) % 3)
            );
        }

        template <int iNumDimensions>
        TriangleEdges<iNumDimensions>
        TriangleBase<iNumDimensions>::edges() const {
            return TriangleEdges<iNumDimensions>(derived());
        }

        template <int iNumDimensions>
        CoordinateSystem<iNumDimensions, 2>
        TriangleBase<iNumDimensions>::coordinateSystem() const {
            return CoordinateSystem<iNumDimensions, 2>(
                vertex(0),
                vertex(1) - vertex(0),
                vertex(2) - vertex(0)
            );
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        TriangleBase<iNumDimensions>::bounds() const {
            return vertex(0).hull(vertex(1)).hull(vertex(2));
        }

        template <int iNumDimensions>
        inline
        bool
        TriangleBase<iNumDimensions>::operator==(const Triangle<iNumDimensions>& other) const {
            return vertex(0) == other.vertex(0) &&
                vertex(1) == other.vertex(1) &&
                vertex(2) == other.vertex(2);
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
    inline
    detail::TriangleEdges<iNumDimensions>
    ScalingFunction<detail::TriangleEdges<iNumDimensions>>::operator()(
        const detail::TriangleEdges<iNumDimensions>& triangleEdges,
        double scale
    ) const {
        return detail::scaled(triangleEdges.triangle(), scale).edges();
    }

    template <int iNumDimensions> template <class TVector>
    inline
    detail::TriangleEdges<iNumDimensions>
    TranslationFunction<detail::TriangleEdges<iNumDimensions>>::operator()(
        const detail::TriangleEdges<iNumDimensions>& triangleEdges,
        const EigenBase<TVector>& vector
    ) const {
        return detail::translated(triangleEdges.triangle(), vector.derived()).edges();
    }

    template <int iNumDimensions, int iNumResultDimensions> template <class TMatrix>
    inline
    detail::TriangleEdges<iNumResultDimensions>
    TransformationFunction<detail::TriangleEdges<iNumDimensions>, iNumResultDimensions>::operator()(
        const detail::TriangleEdges<iNumDimensions>& triangleEdges,
        const EigenBase<TMatrix>& matrix
    ) const {
        return detail::transformed(triangleEdges.triangle(), matrix.derived()).edges();
    }

    template <int iNumDimensions, int iNumResultDimensions>
    inline
    detail::TriangleEdges<iNumResultDimensions>
    MorphingFunction<detail::TriangleEdges<iNumDimensions>, iNumResultDimensions>::operator()(
        const detail::TriangleEdges<iNumDimensions>& triangleEdges,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return detail::morphed(triangleEdges.triangle(), morphingExpression).edges();
    }

    template <int iNumDimensions>
    Triangle<iNumDimensions>
    ScalingFunction<Triangle<iNumDimensions>>::operator()(
        const Triangle<iNumDimensions>& triangle,
        double scale
    ) const {
        return Triangle<iNumDimensions>(
            detail::scaled(triangle.vertex(0), scale),
            detail::scaled(triangle.vertex(1), scale),
            detail::scaled(triangle.vertex(2), scale)
        );
    }

    template <int iNumDimensions> template <class TVector>
    Triangle<iNumDimensions>
    TranslationFunction<Triangle<iNumDimensions>>::operator()(
        const Triangle<iNumDimensions>& triangle,
        const EigenBase<TVector>& vector
    ) const {
        return Triangle<iNumDimensions>(
            detail::translated(triangle.vertex(0), vector.derived()),
            detail::translated(triangle.vertex(1), vector.derived()),
            detail::translated(triangle.vertex(2), vector.derived())
        );
    }

    template <int iNumDimensions, int iNumResultDimensions> template <class TMatrix>
    Triangle<iNumResultDimensions>
    TransformationFunction<Triangle<iNumDimensions>, iNumResultDimensions>::operator()(
        const Triangle<iNumDimensions>& triangle,
        const EigenBase<TMatrix>& matrix
    ) const {
        return Triangle<iNumResultDimensions>(
            detail::transformed(triangle.vertex(0), matrix.derived()),
            detail::transformed(triangle.vertex(1), matrix.derived()),
            detail::transformed(triangle.vertex(2), matrix.derived())
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    Triangle<iNumResultDimensions>
    MorphingFunction<Triangle<iNumDimensions>, iNumResultDimensions>::operator()(
        const Triangle<iNumDimensions>& triangle,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return Triangle<iNumResultDimensions>(
            detail::morphed(triangle.vertex(0), morphingExpression),
            detail::morphed(triangle.vertex(1), morphingExpression),
            detail::morphed(triangle.vertex(2), morphingExpression)
        );
    }

    template <int iNumDimensions>
    bool
    EqualityFunction<Triangle<iNumDimensions>>::operator()(
        const Triangle<iNumDimensions>& firstTriangle,
        const Triangle<iNumDimensions>& secondTriangle,
        double precision
    ) const {
        return detail::equals(firstTriangle.vertex(0), secondTriangle.vertex(0), precision) &&
            detail::equals(firstTriangle.vertex(1), secondTriangle.vertex(1), precision) &&
            detail::equals(firstTriangle.vertex(2), secondTriangle.vertex(2), precision);
    }
}
