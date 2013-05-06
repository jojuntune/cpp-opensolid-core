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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/LineSegment.definitions.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Simplex.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    inline
    LineSegment<iNumDimensions>::LineSegment() {
    }

    template <int iNumDimensions>
    inline
    LineSegment<iNumDimensions>::LineSegment(const Simplex<iNumDimensions, 2>& other) :
        Simplex<iNumDimensions, 2>(other) {
    }

    template <int iNumDimensions>
    inline
    LineSegment<iNumDimensions>::LineSegment(
        const Point<iNumDimensions>& firstVertex,
        const Point<iNumDimensions>& secondVertex
    ) {
        Matrix<double, iNumDimensions, 2> vertices;
        vertices.col(0) = firstVertex.vector();
        vertices.col(1) = secondVertex.vector();
        *this = Simplex<iNumDimensions, 2>(vertices);
    }

    inline
    LineSegment<1>::LineSegment() {
    }

    inline
    LineSegment<1>::LineSegment(const Simplex<1, 2>& other) :
        Simplex<1, 2>(other) {
    }

    inline
    LineSegment<1>::LineSegment(double startPoint, double endPoint) :
        Simplex<1, 2>(RowVector2d(startPoint, endPoint)) {
    }

    inline double
    LineSegment<1>::startPoint() const {
        return vertices()(0);
    }

    inline double
    LineSegment<1>::endPoint() const {
        return vertices()(1);
    }

    inline LineSegment<1>
    LineSegment<1>::Unit() {
        return LineSegment<1>(0.0, 1.0);
    }
}
