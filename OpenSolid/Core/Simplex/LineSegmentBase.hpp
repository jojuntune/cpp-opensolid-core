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

#include <OpenSolid/Core/Simplex/LineSegmentBase.definitions.hpp>

#include <OpenSolid/Core/Axis.definitions.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Frame.definitions.hpp>
#include <OpenSolid/Core/LineSegment.definitions.hpp>
#include <OpenSolid/Core/Matrix.hpp>
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
        LineSegmentBase<iNumDimensions>::derived() const {
            return static_cast<const LineSegment<iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        LineSegmentBase<iNumDimensions>::LineSegmentBase() {
        }

        template <int iNumDimensions>
        inline
        LineSegmentBase<iNumDimensions>::LineSegmentBase(
            const Point<iNumDimensions>& startVertex,
            const Point<iNumDimensions>& endVertex
        ) {
            _vertices[0] = startVertex;
            _vertices[1] = endVertex;
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        LineSegmentBase<iNumDimensions>::startVertex() const {
            return _vertices[0];
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        LineSegmentBase<iNumDimensions>::endVertex() const {
            return _vertices[1];
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        LineSegmentBase<iNumDimensions>::vertex(int index) const {
            assert(index == 0 || index == 1);
            return _vertices[index];
        }

        template <int iNumDimensions>
        inline
        SimplexVertices<LineSegment<iNumDimensions>, 2>
        LineSegmentBase<iNumDimensions>::vertices() const {
            return SimplexVertices<LineSegment<iNumDimensions>, 2>(derived());
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        LineSegmentBase<iNumDimensions>::centroid() const {
            return startVertex() + 0.5 * vector();
        }

        template <int iNumDimensions>
        inline
        double
        LineSegmentBase<iNumDimensions>::length() const {
            return vector().norm();
        }

        template <int iNumDimensions>
        inline
        double
        LineSegmentBase<iNumDimensions>::squaredLength() const {
            return vector().squaredNorm();
        }

        template<int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        LineSegmentBase<iNumDimensions>::vector() const {
            return endVertex() - startVertex();
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        LineSegmentBase<iNumDimensions>::bounds() const {
            return startVertex().hull(endVertex());
        }

        template <int iNumDimensions>
        inline
        bool
        LineSegmentBase<iNumDimensions>::operator==(
            const LineSegment<iNumDimensions>& other
        ) const {
            return startVertex() == other.startVertex() && endVertex() == other.endVertex();
        }
    }
}
