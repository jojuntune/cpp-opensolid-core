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

// Public headers
#include <OpenSolid/Core/Simplex.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class Triangle;

    template <>
    class Triangle<2> : public Simplex<2, 3>
    {
    public:
        Triangle(const Simplex<2, 3>& otherTriangle);

        Triangle(
            const Vector2d& firstVertex,
            const Vector2d& secondVertex,
            const Vector2d& thirdVertex
        );

        static Triangle<2> Unit();
    };

    typedef Triangle<2> Triangle2d;

    template <>
    class Triangle<3> : public Simplex<3, 3>
    {
    public:
        Triangle(const Simplex<3, 3>& otherTriangle);

        Triangle(
            const Vector3d& firstVertex,
            const Vector3d& secondVertex,
            const Vector3d& thirdVertex
        );
    };

    typedef Triangle<3> Triangle3d;
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct Bounds<Triangle<iNumDimensions>> : public Bounds<Simplex<iNumDimensions, 3>>
    {
    };

    template <int iNumDimensions, int iNumTransformedDimensions>
    struct Transformed<Triangle<iNumDimensions>, iNumTransformedDimensions> :
        public Transformed<Simplex<iNumDimensions, 3>, iNumTransformedDimensions>
    {
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline Triangle<2>::Triangle(const Simplex<2, 3>& otherTriangle) :
        Simplex<2, 3>(otherTriangle) {
    }

    inline Triangle<2>::Triangle(
        const Vector2d& firstVertex,
        const Vector2d& secondVertex,
        const Vector2d& thirdVertex
    ) {
        Matrix<double, 2, 3> vertices;
        vertices << firstVertex, secondVertex, thirdVertex;
        *this = Simplex<2, 3>(vertices);
    }

    inline Triangle<3>::Triangle(const Simplex<3, 3>& otherTriangle) :
        Simplex<3, 3>(otherTriangle) {
    }

    inline Triangle<2> Triangle<2>::Unit() {
        return Triangle<2>(Vector2d::Zero(), Vector2d::UnitX(), Vector2d::UnitY());
    }

    inline Triangle<3>::Triangle(
        const Vector3d& firstVertex,
        const Vector3d& secondVertex,
        const Vector3d& thirdVertex
    ) {
        Matrix3d vertices;
        vertices << firstVertex, secondVertex, thirdVertex;
        *this = Simplex<3, 3>(vertices);
    }
}
