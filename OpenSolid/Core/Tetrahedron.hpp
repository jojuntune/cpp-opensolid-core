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

#include <OpenSolid/Core/Simplex.hpp>

namespace opensolid
{
    class Tetrahedron3d :
        public Simplex<3, 4>
    {
    public:
        Tetrahedron3d();

        Tetrahedron3d(const Simplex<3, 4>& otherTetrahedron);

        Tetrahedron3d(
            const Point3d& firstVertex,
            const Point3d& secondVertex,
            const Point3d& thirdVertex,
            const Point3d& fourthVertex
        );

        static Tetrahedron3d
        Unit();
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct ScalingFunction<Tetrahedron3d> :
        public ScalingFunction<Simplex<3, 4>>
    {
    };

    template <>
    struct TranslationFunction<Tetrahedron3d> :
        public TranslationFunction<Simplex<3, 4>>
    {
    };

    template <int iNumTransformedDimensions>
    struct TransformationFunction<Tetrahedron3d, iNumTransformedDimensions> :
        public TransformationFunction<Simplex<3, 4>, iNumTransformedDimensions>
    {
    };

    template <>
    struct BoundsFunction<Tetrahedron3d> :
        public BoundsFunction<Simplex<3, 4>>
    {
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline
    Tetrahedron3d::Tetrahedron3d() {
    }

    inline
    Tetrahedron3d::Tetrahedron3d(const Simplex<3, 4>& otherTetrahedron) :
        Simplex<3, 4>(otherTetrahedron) {
    }

    inline
    Tetrahedron3d::Tetrahedron3d(
        const Point3d& firstVertex,
        const Point3d& secondVertex,
        const Point3d& thirdVertex,
        const Point3d& fourthVertex
    ) {
        Matrix<double, 3, 4> vertices;
        vertices.col(0) = firstVertex.vector();
        vertices.col(1) = secondVertex.vector();
        vertices.col(2) = thirdVertex.vector();
        vertices.col(3) = fourthVertex.vector();
        *this = Simplex<3, 4>(vertices);
    }

    inline Tetrahedron3d
    Tetrahedron3d::Unit() {
        return Tetrahedron3d(
            Point3d::Origin(),
            Point3d(1, 0, 0),
            Point3d(0, 1, 0),
            Point3d(0, 0, 1)
        );
    }
}
