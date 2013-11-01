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

#include <OpenSolid/Core/Body.declarations.hpp>

#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Domain.definitions.hpp>
#include <OpenSolid/Core/Geometry.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/SpatialSet.declarations.hpp>
#include <OpenSolid/Core/Tetrahedron.declarations.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>

namespace opensolid
{
    class Body3d :
        public Domain<3>
    {
    public:
        OPENSOLID_CORE_EXPORT
        Body3d();

        OPENSOLID_CORE_EXPORT
        Body3d(const Domain<3>& domain);

        OPENSOLID_CORE_EXPORT
        Body3d(const SpatialSet<Geometry<3, 2>>& boundaries);

        OPENSOLID_CORE_EXPORT
        Body3d(const SpatialSet<Triangle<3>>& boundaries);

        OPENSOLID_CORE_EXPORT
        Body3d(const Box<3>& box);

        OPENSOLID_CORE_EXPORT
        Body3d(const Tetrahedron3d& tetrahedron);
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct NumDimensions<Body3d> :
        public NumDimensions<Domain<3>>
    {
    };

    template <>
    struct TransformedType<Body3d, 3> :
        public TransformedType<Domain<3>, 3>
    {
    };

    template <>
    struct MorphedType<Body3d, 3> :
        public MorphedType<Domain<3>, 3>
    {
    };

    template <>
    struct ScalingFunction<Body3d> :
        public ScalingFunction<Domain<3>>
    {
    };

    template <>
    struct TranslationFunction<Body3d> :
        public TranslationFunction<Domain<3>>
    {
    };

    template <int iNumResultDimensions>
    struct TransformationFunction<Body3d, iNumResultDimensions> :
        public TransformationFunction<Domain<3>, iNumResultDimensions>
    {
    };

    template <>
    struct MorphingFunction<Body3d, 3> :
        public MorphingFunction<Domain<3>, 3>
    {
    };

    template <>
    struct BoundsType<Body3d> :
        public BoundsType<Domain<3>>
    {
    };
}
