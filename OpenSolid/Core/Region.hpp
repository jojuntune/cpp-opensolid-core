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

#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Triangle.hpp>

namespace opensolid
{
    class Region2d : public Domain<2>
    {
    public:
        OPENSOLID_CORE_EXPORT
        Region2d();

        OPENSOLID_CORE_EXPORT
        Region2d(const Domain<2>& domain);

        OPENSOLID_CORE_EXPORT
        Region2d(const Set<Geometry<2, 1>>& boundaries);

        OPENSOLID_CORE_EXPORT
        Region2d(const Set<LineSegment2d>& boundaries);

        OPENSOLID_CORE_EXPORT
        Region2d(Interval xInterval, Interval yInterval);

        OPENSOLID_CORE_EXPORT explicit
        Region2d(const Box2d& box);

        OPENSOLID_CORE_EXPORT explicit
        Region2d(const Triangle2d& triangle);

        OPENSOLID_CORE_EXPORT static Region2d
        UnitSquare();

        OPENSOLID_CORE_EXPORT static Region2d
        UnitTriangle();
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct BoundsFunction<Region2d> :
        public BoundsFunction<Domain<2>>
    {
    };

    struct ScalingFunction<Region2d> :
        public ScalingFunction<Domain<2>>
    {
    };

    struct TranslationFunction<Region2d> :
        public TranslationFunction<Domain<2>>
    {
    };

    template <int iNumTransformedDimensions>
    struct TransformationFunction<Region2d, iNumTransformedDimensions> :
        public TransformationFunction<Domain<2>, iNumTransformedDimensions>
    {
    };
}

////////// Implementation //////////

namespace opensolid
{
}
