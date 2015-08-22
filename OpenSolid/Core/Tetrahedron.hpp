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

#include <OpenSolid/Core/Tetrahedron.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Handedness.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.hpp>
#include <OpenSolid/Core/Simplex/TetrahedronEdges.hpp>
#include <OpenSolid/Core/Simplex/TetrahedronFaces.hpp>
#include <OpenSolid/Core/LazyCollection.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    inline
    Tetrahedron3d::Tetrahedron3d() :
    _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    Tetrahedron3d::Tetrahedron3d(
        const Point3d& firstVertex,
        const Point3d& secondVertex,
        const Point3d& thirdVertex,
        const Point3d& fourthVertex
    ) : _handedness(Handedness::RIGHT_HANDED()) {

        _vertices[0] = firstVertex;
        _vertices[1] = secondVertex;
        _vertices[2] = thirdVertex;
        _vertices[3] = fourthVertex;
    }

    inline
    Tetrahedron3d::Tetrahedron3d(
        const Point3d& firstVertex,
        const Point3d& secondVertex,
        const Point3d& thirdVertex,
        const Point3d& fourthVertex,
        Handedness handedness
    ) : _handedness(handedness) {

        _vertices[0] = firstVertex;
        _vertices[1] = secondVertex;
        _vertices[2] = thirdVertex;
        _vertices[3] = fourthVertex;
    }

    inline
    const Point3d&
    Tetrahedron3d::vertex(int index) const {
        assert(index >= 0 && index < 4);
        return _vertices[index];
    }

    inline
    Point3d&
    Tetrahedron3d::vertex(int index) {
        assert(index >= 0 && index < 4);
        return _vertices[index];
    }

    inline
    Handedness
    Tetrahedron3d::handedness() const {
        return _handedness;
    }

    inline
    detail::SimplexVertices<Tetrahedron3d, 4>
    Tetrahedron3d::vertices() const {
        return detail::SimplexVertices<Tetrahedron3d, 4>(*this);
    }

    inline
    detail::TetrahedronEdges
    Tetrahedron3d::edges() const {
        return detail::TetrahedronEdges(*this);
    }

    inline
    detail::TetrahedronFaces
    Tetrahedron3d::faces() const {
        return detail::TetrahedronFaces(*this);
    }

    inline
    Box3d
    Tetrahedron3d::bounds() const {
        return vertex(0).hull(vertex(1)).hull(vertex(2)).hull(vertex(3));
    }

    inline
    bool
    Tetrahedron3d::operator==(const Tetrahedron3d& other) const {
        return (
            vertex(0) == other.vertex(0) &&
            vertex(1) == other.vertex(1) &&
            vertex(2) == other.vertex(2) &&
            vertex(3) == other.vertex(3) &&
            handedness() == other.handedness()
        );
    }

    template <class TTransformation>
    Tetrahedron3d
    Tetrahedron3d::transformedBy(const TTransformation& transformation) const {
        return Tetrahedron3d(
            vertex(0).transformedBy(transformation),
            vertex(1).transformedBy(transformation),
            vertex(2).transformedBy(transformation),
            vertex(3).transformedBy(transformation),
            handedness().transformedBy(transformation)
        );
    }

    inline
    bool
    EqualityFunction<Tetrahedron3d>::operator()(
        const Tetrahedron3d& firstTetrahedron,
        const Tetrahedron3d& secondTetrahedron,
        double precision
    ) const {
        return (
            equalityFunction(firstTetrahedron.vertex(0), secondTetrahedron.vertex(0), precision) &&
            equalityFunction(firstTetrahedron.vertex(1), secondTetrahedron.vertex(1), precision) &&
            equalityFunction(firstTetrahedron.vertex(2), secondTetrahedron.vertex(2), precision) &&
            equalityFunction(firstTetrahedron.vertex(3), secondTetrahedron.vertex(3), precision) &&
            firstTetrahedron.handedness() == secondTetrahedron.handedness()
        );
    }
}
