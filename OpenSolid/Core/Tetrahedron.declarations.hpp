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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>

namespace opensolid
{
    class Tetrahedron3d;

    template <>
    struct NumDimensions<Tetrahedron3d>
    {
        static const int Value = 3;
    };

    template <>
    struct BoundsType<Tetrahedron3d>
    {
        typedef Box<3> Type;
    };

    namespace detail
    {
        class TetrahedronEdges;
        class TetrahedronFaces;
    }

    template <>
    struct NumDimensions<detail::TetrahedronEdges>
    {
        static const int Value = 3;
    };

    template <>
    struct ItemType<detail::TetrahedronEdges>
    {
        typedef LineSegment<3> Type;
    };

    template <>
    struct ItemReferenceType<detail::TetrahedronEdges>
    {
        typedef LineSegment<3> Type;
    };

    template <>
    struct ScaledType<detail::TetrahedronEdges>
    {
        typedef detail::TetrahedronEdges Type;
    };

    template <>
    struct TranslatedType<detail::TetrahedronEdges>
    {
        typedef detail::TetrahedronEdges Type;
    };

    template <int iNumResultDimensions>
    struct TransformedType<detail::TetrahedronEdges, iNumResultDimensions> :
        public TransformedType<SpatialCollection<detail::TetrahedronEdges>, iNumResultDimensions>
    {
    };

    template <>
    struct TransformedType<detail::TetrahedronEdges, 3>
    {
        typedef detail::TetrahedronEdges Type;
    };

    template <int iNumResultDimensions>
    struct MorphedType<detail::TetrahedronEdges, iNumResultDimensions> :
        public MorphedType<SpatialCollection<detail::TetrahedronEdges>, iNumResultDimensions>
    {
    };

    template <>
    struct MorphedType<detail::TetrahedronEdges, 3>
    {
        typedef detail::TetrahedronEdges Type;
    };

    template <>
    struct BoundsType<detail::TetrahedronEdges>
    {
        typedef Box<3> Type;
    };

    template <>
    struct NumDimensions<detail::TetrahedronFaces>
    {
        static const int Value = 3;
    };

    template <>
    struct ItemType<detail::TetrahedronFaces>
    {
        typedef Triangle<3> Type;
    };

    template <>
    struct ItemReferenceType<detail::TetrahedronFaces>
    {
        typedef Triangle<3> Type;
    };

    template <>
    struct ScaledType<detail::TetrahedronFaces>
    {
        typedef detail::TetrahedronFaces Type;
    };

    template <>
    struct TranslatedType<detail::TetrahedronFaces>
    {
        typedef detail::TetrahedronFaces Type;
    };

    template <int iNumResultDimensions>
    struct TransformedType<detail::TetrahedronFaces, iNumResultDimensions> :
        public TransformedType<SpatialCollection<detail::TetrahedronFaces>, iNumResultDimensions>
    {
    };

    template <>
    struct TransformedType<detail::TetrahedronFaces, 3>
    {
        typedef detail::TetrahedronFaces Type;
    };

    template <int iNumResultDimensions>
    struct MorphedType<detail::TetrahedronFaces, iNumResultDimensions> :
        public MorphedType<SpatialCollection<detail::TetrahedronFaces>, iNumResultDimensions>
    {
    };

    template <>
    struct MorphedType<detail::TetrahedronFaces, 3>
    {
        typedef detail::TetrahedronFaces Type;
    };

    template <>
    struct BoundsType<detail::TetrahedronFaces>
    {
        typedef Box<3> Type;
    };
}
