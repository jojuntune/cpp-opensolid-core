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

#include <OpenSolid/Core/Simplex/TetrahedronEdges.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/LineSegment.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/IndexIterator.declarations.hpp>
#include <OpenSolid/Core/Tetrahedron.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <>
    struct BoundsType<detail::TetrahedronEdges>
    {
        typedef Box<3> Type;
    };

    template <>
    struct NumDimensions<detail::TetrahedronEdges>
    {
        static const int Value = 3;
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
    struct ItemType<detail::TetrahedronEdges>
    {
        typedef LineSegment<3> Type;
    };

    template <>
    struct ItemReferenceType<detail::TetrahedronEdges>
    {
        typedef LineSegment<3> Type;
    };

    namespace detail
    {
        class TetrahedronEdges :
            public SpatialCollection<TetrahedronEdges>
        {
        private:
            Tetrahedron3d _tetrahedron;
        public:
            TetrahedronEdges(const Tetrahedron3d& tetrahedron);

            const Tetrahedron3d&
            tetrahedron() const;

            IndexIterator<TetrahedronEdges>
            begin() const;

            IndexIterator<TetrahedronEdges>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            Box<3>
            bounds() const;

            LineSegment<3>
            operator[](std::int64_t index) const;
        };
    }

    template <>
    struct ScalingFunction<detail::TetrahedronEdges>
    {
        OPENSOLID_CORE_EXPORT
        detail::TetrahedronEdges
        operator()(
            const detail::TetrahedronEdges& tetrahedronEdges,
            double scale
        ) const;
    };

    template <>
    struct TranslationFunction<detail::TetrahedronEdges>
    {
        OPENSOLID_CORE_EXPORT
        detail::TetrahedronEdges
        operator()(
            const detail::TetrahedronEdges& tetrahedronEdges,
            const Vector3d& vector
        ) const;
    };

    template <int iNumResultDimensions>
    struct TransformationFunction<detail::TetrahedronEdges, iNumResultDimensions> :
        public TransformationFunction<
            SpatialCollection<detail::TetrahedronEdges>,
            iNumResultDimensions
        >
    {
    };

    template <>
    struct TransformationFunction<detail::TetrahedronEdges, 3>
    {
        OPENSOLID_CORE_EXPORT
        detail::TetrahedronEdges
        operator()(
            const detail::TetrahedronEdges& tetrahedronEdges,
            const Matrix3d& matrix
        ) const;
    };

    template <int iNumResultDimensions>
    struct MorphingFunction<detail::TetrahedronEdges, iNumResultDimensions> :
        public MorphingFunction<
            SpatialCollection<detail::TetrahedronEdges>,
            iNumResultDimensions
        >
    {
    };

    template <>
    struct MorphingFunction<detail::TetrahedronEdges, 3>
    {
        OPENSOLID_CORE_EXPORT
        detail::TetrahedronEdges
        operator()(
            const detail::TetrahedronEdges& tetrahedronEdges,
            const ParametricExpression<3, 3>& morphingExpression
        ) const;
    };
}
