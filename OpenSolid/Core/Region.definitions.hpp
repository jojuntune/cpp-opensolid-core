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

#include <OpenSolid/Core/Region.declarations.hpp>

#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Domain.definitions.hpp>
#include <OpenSolid/Core/Geometry.declarations.hpp>
#include <OpenSolid/Core/Interval.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Set.declarations.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>

namespace opensolid
{
    class Region2d :
        public Domain<2>
    {
    public:
        OPENSOLID_CORE_EXPORT
        Region2d();

        OPENSOLID_CORE_EXPORT
        Region2d(const Domain<2>& domain);

        OPENSOLID_CORE_EXPORT
        Region2d(const Set<Geometry<2, 1>>& boundaries);

        OPENSOLID_CORE_EXPORT
        Region2d(const Box<2>& box);

        OPENSOLID_CORE_EXPORT
        Region2d(const Triangle<2>& triangle);

        OPENSOLID_CORE_EXPORT static Region2d
        Disk(const Point<2>& centerPoint, double radius);
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct NumDimensions<Region2d> :
        public NumDimensions<Domain<2>>
    {
    };

    template <>
    struct ChangeDimensions<Region2d, 2> :
        public ChangeDimensions<Domain<2>, 2>
    {
    };

    template <>
    struct ScalingFunction<Region2d> :
        public ScalingFunction<Domain<2>>
    {
    };

    template <>
    struct TranslationFunction<Region2d> :
        public TranslationFunction<Domain<2>>
    {
    };

    template <int iNumResultDimensions>
    struct TransformationFunction<Region2d, iNumResultDimensions> :
        public TransformationFunction<Domain<2>, iNumResultDimensions>
    {
    };

    template <>
    struct MorphingFunction<Region2d, 2> :
        public MorphingFunction<Domain<2>, 2>
    {
    };

    template <>
    struct BoundsType<Region2d> :
        public BoundsType<Domain<2>>
    {
    };
}
