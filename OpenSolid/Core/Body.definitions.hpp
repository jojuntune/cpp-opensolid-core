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
#include <OpenSolid/Core/Set.declarations.hpp>
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
        Body3d(const Set<Geometry<3, 2>>& boundaries);

        OPENSOLID_CORE_EXPORT
        Body3d(const Set<Triangle<3>>& boundaries);

        OPENSOLID_CORE_EXPORT
        Body3d(Interval xInterval, Interval yInterval, Interval zInterval);

        OPENSOLID_CORE_EXPORT explicit
        Body3d(const Box<3>& box);

        OPENSOLID_CORE_EXPORT explicit
        Body3d(const Tetrahedron3d& tetrahedron);

        OPENSOLID_CORE_EXPORT static Body3d
        UnitCube();

        OPENSOLID_CORE_EXPORT static Body3d
        UnitTetrahedron();
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct BoundsFunction<Body3d> :
        public BoundsFunction<Domain<3>>
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

    template <int iTransformedDimensions>
    struct TransformationFunction<Body3d, iTransformedDimensions> :
        public TransformationFunction<Domain<3>, iTransformedDimensions>
    {
    };
}
