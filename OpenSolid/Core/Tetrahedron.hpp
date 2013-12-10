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

#include <OpenSolid/Core/Tetrahedron.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/SpatialCollection/SimplexVertices.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    inline
    Tetrahedron3d::Tetrahedron3d() {
    }

    inline
    Tetrahedron3d::Tetrahedron3d(
        const Point3d& firstVertex,
        const Point3d& secondVertex,
        const Point3d& thirdVertex,
        const Point3d& fourthVertex
    ) {
        _vertices[0] = firstVertex;
        _vertices[1] = secondVertex;
        _vertices[2] = thirdVertex;
        _vertices[3] = fourthVertex;
    }

    inline
    const Point<3>&
    Tetrahedron3d::vertex(int index) const {
        assert(index >= 0 && index < 4);
        return _vertices[index];
    }

    inline
    Point<3>&
    Tetrahedron3d::vertex(int index) {
        assert(index >= 0 && index < 4);
        return _vertices[index];
    }

    inline
    detail::SimplexVertices<Tetrahedron3d, 4>
    Tetrahedron3d::vertices() const {
        return detail::SimplexVertices<Tetrahedron3d, 4>(*this);
    }

    inline
    Box<3>
    Tetrahedron3d::bounds() const {
        return vertex(0).hull(vertex(1)).hull(vertex(2)).hull(vertex(3));
    }

    inline
    bool
    Tetrahedron3d::operator==(const Tetrahedron3d& other) const {
        return vertex(0) == other.vertex(0) &&
            vertex(1) == other.vertex(1) &&
            vertex(2) == other.vertex(2) &&
            vertex(3) == other.vertex(3);
    }

    inline
    bool
    EqualityFunction<Tetrahedron3d>::operator()(
        const Tetrahedron3d& firstTetrahedron,
        const Tetrahedron3d& secondTetrahedron,
        double precision
    ) const {
        return detail::equals(firstTetrahedron.vertex(0), secondTetrahedron.vertex(0), precision) &&
            detail::equals(firstTetrahedron.vertex(1), secondTetrahedron.vertex(1), precision) &&
            detail::equals(firstTetrahedron.vertex(2), secondTetrahedron.vertex(2), precision) &&
            detail::equals(firstTetrahedron.vertex(3), secondTetrahedron.vertex(3), precision);
    }
}
