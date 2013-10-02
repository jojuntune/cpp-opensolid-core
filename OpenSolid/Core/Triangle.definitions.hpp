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

#include <OpenSolid/Core/Triangle.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Simplex.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <>
    class Triangle<2> :
        public Simplex<2, 3>
    {
    public:
        Triangle();

        Triangle(const Simplex<2, 3>& otherTriangle);

        Triangle(
            const Point2d& firstVertex,
            const Point2d& secondVertex,
            const Point2d& thirdVertex
        );
    };

    typedef Triangle<2> Triangle2d;

    template <>
    class Triangle<3> :
        public Simplex<3, 3>
    {
    public:
        Triangle();

        Triangle(const Simplex<3, 3>& otherTriangle);

        Triangle(
            const Point3d& firstVertex,
            const Point3d& secondVertex,
            const Point3d& thirdVertex
        );
    };

    typedef Triangle<3> Triangle3d;
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct NumDimensions<Triangle<iNumDimensions>> :
        public NumDimensions<Simplex<iNumDimensions, 3>>
    {
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct ChangeDimensions<Triangle<iNumDimensions>, iNumResultDimensions> :
        public ChangeDimensions<Simplex<iNumDimensions, 3>, iNumResultDimensions>
    {
    };

    template <int iNumDimensions>
    struct ScalingFunction<Triangle<iNumDimensions>> :
        public ScalingFunction<Simplex<iNumDimensions, 3>>
    {
    };

    template <int iNumDimensions>
    struct TranslationFunction<Triangle<iNumDimensions>> :
        public TranslationFunction<Simplex<iNumDimensions, 3>>
    {
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<Triangle<iNumDimensions>, iNumResultDimensions> :
        public TransformationFunction<Simplex<iNumDimensions, 3>, iNumResultDimensions>
    {
    };

    template <int iNumDimensions>
    struct BoundsType<Triangle<iNumDimensions>> :
        public BoundsType<Simplex<iNumDimensions, 3>>
    {
    };
}
