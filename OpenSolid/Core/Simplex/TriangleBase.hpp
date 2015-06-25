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

#include <OpenSolid/Core/Simplex/TriangleBase.definitions.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.hpp>
#include <OpenSolid/Core/Simplex/TriangleEdges.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Triangle.definitions.hpp>
#include <OpenSolid/Core/Vector.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
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
        SimplexVertices<Triangle<iNumDimensions>, 3>
        TriangleBase<iNumDimensions>::vertices() const {
            return SimplexVertices<Triangle<iNumDimensions>, 3>(derived());
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        TriangleBase<iNumDimensions>::centroid() const {
            return vertex(0) + ((vertex(1) - vertex(0)) + (vertex(2) - vertex(0))) / 3.0;
        }

        template <int iNumDimensions>
        inline
        LineSegment<iNumDimensions>
        TriangleBase<iNumDimensions>::edge(int oppositeIndex) const {
            assert(oppositeIndex >= 0 && oppositeIndex < 3);
            return LineSegment<iNumDimensions>(
                vertex((oppositeIndex + 2) % 3),
                vertex((oppositeIndex + 1) % 3)
            );
        }

        template <int iNumDimensions>
        inline
        TriangleEdges<iNumDimensions>
        TriangleBase<iNumDimensions>::edges() const {
            return TriangleEdges<iNumDimensions>(derived());
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        TriangleBase<iNumDimensions>::bounds() const {
            return vertex(0).hull(vertex(1)).hull(vertex(2));
        }

        template <int iNumDimensions>
        inline
        Triangle<iNumDimensions>
        TriangleBase<iNumDimensions>::scaledAbout(
            const Point<iNumDimensions>& point,
            double scale
        ) const {
            return Triangle<iNumDimensions>(
                vertex(0).scaledAbout(point, scale),
                vertex(1).scaledAbout(point, scale),
                vertex(2).scaledAbout(point, scale)
            );
        }

        template <int iNumDimensions>
        inline
        Triangle<iNumDimensions>
        TriangleBase<iNumDimensions>::rotatedAbout(
            const Point<iNumDimensions>& point,
            const Matrix<double, iNumDimensions, iNumDimensions>& rotationMatrix
        ) const {
            return Triangle<iNumDimensions>(
                vertex(0).rotatedAbout(point, rotationMatrix),
                vertex(1).rotatedAbout(point, rotationMatrix),
                vertex(2).rotatedAbout(point, rotationMatrix)
            );
        }

        template <int iNumDimensions>
        inline
        Triangle<iNumDimensions>
        TriangleBase<iNumDimensions>::translatedBy(
            const Vector<double, iNumDimensions>& vector
        ) const {
            return Triangle<iNumDimensions>(
                vertex(0).translatedBy(vector),
                vertex(1).translatedBy(vector),
                vertex(2).translatedBy(vector)
            );
        }

        template <int iNumDimensions>
        inline
        Triangle<iNumDimensions>
        TriangleBase<iNumDimensions>::toLocalIn(const Frame<iNumDimensions>& frame) const {
            return Triangle<iNumDimensions>(
                vertex(0).toLocalIn(frame),
                vertex(1).toLocalIn(frame),
                vertex(2).toLocalIn(frame)
            );
        }

        template <int iNumDimensions>
        inline
        Triangle<iNumDimensions>
        TriangleBase<iNumDimensions>::toGlobalFrom(const Frame<iNumDimensions>& frame) const {
            return Triangle<iNumDimensions>(
                vertex(0).toGlobalFrom(frame),
                vertex(1).toGlobalFrom(frame),
                vertex(2).toGlobalFrom(frame)
            );
        }

        template <int iNumDimensions>
        inline
        Triangle<iNumDimensions>
        TriangleBase<iNumDimensions>::mirroredAbout(
            const Point<iNumDimensions>& point,
            const UnitVector<iNumDimensions>& mirrorDirection
        ) const {
            return Triangle<iNumDimensions>(
                vertex(0).mirroredAbout(point, mirrorDirection),
                vertex(1).mirroredAbout(point, mirrorDirection),
                vertex(2).mirroredAbout(point, mirrorDirection)
            );
        }

        template <int iNumDimensions>
        inline
        bool
        TriangleBase<iNumDimensions>::operator==(const Triangle<iNumDimensions>& other) const {
            return (
                vertex(0) == other.vertex(0) &&
                vertex(1) == other.vertex(1) &&
                vertex(2) == other.vertex(2)
            );
        }
    }
}
