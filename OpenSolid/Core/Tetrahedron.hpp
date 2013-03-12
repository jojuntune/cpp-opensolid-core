/*************************************************************************************
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

#include <OpenSolid/Core/Simplex.hpp>

#include <OpenSolid/Core/Simplex/declarations.hpp>

namespace opensolid
{
    class Tetrahedron3d : public Simplex<3, 4>
    {
    public:
        Tetrahedron3d();

        Tetrahedron3d(const Simplex<3, 4>& otherTetrahedron);

        Tetrahedron3d(
            const Vector3d& firstVertex,
            const Vector3d& secondVertex,
            const Vector3d& thirdVertex,
            const Vector3d& fourthVertex
        );

        static Tetrahedron3d Unit();
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct Bounds<Tetrahedron3d> : public Bounds<Simplex<3, 4>>
    {
    };

    template <int iNumTransformedDimensions>
    struct Transformed<Tetrahedron3d, iNumTransformedDimensions> :
        public Transformed<Simplex<3, 4>, iNumTransformedDimensions>
    {
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Tetrahedron3d::Tetrahedron3d() {
    }

    inline Tetrahedron3d::Tetrahedron3d(const Simplex<3, 4>& otherTetrahedron) :
        Simplex<3, 4>(otherTetrahedron) {
    }

    inline Tetrahedron3d::Tetrahedron3d(
        const Vector3d& firstVertex,
        const Vector3d& secondVertex,
        const Vector3d& thirdVertex,
        const Vector3d& fourthVertex
    ) {
        Matrix<double, 3, 4> vertices;
        vertices << firstVertex, secondVertex, thirdVertex, fourthVertex;
        *this = Simplex<3, 4>(vertices);
    }

    inline Tetrahedron3d Tetrahedron3d::Unit() {
        return Tetrahedron3d(
            Vector3d::Zero(),
            Vector3d::UnitX(),
            Vector3d::UnitY(),
            Vector3d::UnitZ()
        );
    }
}
