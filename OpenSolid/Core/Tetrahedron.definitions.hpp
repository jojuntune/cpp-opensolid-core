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

#include <OpenSolid/Core/Tetrahedron.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/Handedness.definitions.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/LazyCollection.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.declarations.hpp>
#include <OpenSolid/Core/Simplex/TetrahedronEdges.declarations.hpp>
#include <OpenSolid/Core/Simplex/TetrahedronFaces.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    template <>
    struct BoundsType<Tetrahedron3d>
    {
        typedef Box<3> Type;
    };

    template <>
    struct NumDimensions<Tetrahedron3d>
    {
        static const int Value = 3;
    };

    class Tetrahedron3d :
        public Convertible<Tetrahedron3d>,
        public Transformable<Tetrahedron3d, Point<3>>
    {
    private:
        Point<3> _vertices[4];
        Handedness _handedness;
    public:
        Tetrahedron3d();

        Tetrahedron3d(
            const Point<3>& firstVertex,
            const Point<3>& secondVertex,
            const Point<3>& thirdVertex,
            const Point<3>& fourthVertex
        );

        Tetrahedron3d(
            const Point<3>& firstVertex,
            const Point<3>& secondVertex,
            const Point<3>& thirdVertex,
            const Point<3>& fourthVertex,
            Handedness handedness
        );

        const Point<3>&
        vertex(int index) const;

        Point<3>&
        vertex(int index);

        Handedness
        handedness() const;

        detail::SimplexVertices<Tetrahedron3d, 4>
        vertices() const;

        OPENSOLID_CORE_EXPORT
        LineSegment<3>
        edge(int index) const;

        detail::TetrahedronEdges
        edges() const;

        OPENSOLID_CORE_EXPORT
        Triangle<3>
        face(int oppositeIndex) const;

        detail::TetrahedronFaces
        faces() const;

        OPENSOLID_CORE_EXPORT
        double
        volume() const;

        OPENSOLID_CORE_EXPORT
        Point<3>
        centroid() const;

        OPENSOLID_CORE_EXPORT
        bool
        contains(const Point<3>& point, double precision = 1e-12) const;

        Box<3>
        bounds() const;

        bool
        equals(const Tetrahedron3d& other, double precision = 1e-12) const;

        bool
        operator==(const Tetrahedron3d& other) const;

        template <class TTransformation>
        Tetrahedron3d
        transformedBy(const TTransformation& transformation) const;

        OPENSOLID_CORE_EXPORT
        static const Tetrahedron3d&
        UNIT();
    };
}
