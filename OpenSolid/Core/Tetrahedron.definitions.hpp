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

#include <OpenSolid/Core/Simplex.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>

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
    struct NumDimensions<Tetrahedron3d> :
        public NumDimensions<Simplex<3, 4>>
    {
    };

    template <int iNumResultDimensions>
    struct ChangeDimensions<Tetrahedron3d, iNumResultDimensions> :
        public ChangeDimensions<Simplex<3, 4>, iNumResultDimensions>
    {
    };

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

    template <int iNumResultDimensions>
    struct TransformationFunction<Tetrahedron3d, iNumResultDimensions> :
        public TransformationFunction<Simplex<3, 4>, iNumResultDimensions>
    {
    };

    template <>
    struct BoundsType<Tetrahedron3d> :
        public BoundsType<Simplex<3, 4>>
    {
    };
}
