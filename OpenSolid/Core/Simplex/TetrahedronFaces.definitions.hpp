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

#include <OpenSolid/Core/Simplex/TetrahedronFaces.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/IndexIterator.declarations.hpp>
#include <OpenSolid/Core/Tetrahedron.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>
#include <OpenSolid/Core/Triangle.definitions.hpp>

namespace opensolid
{
    template <>
    struct BoundsType<detail::TetrahedronFaces>
    {
        typedef Box<3> Type;
    };

    template <>
    struct NumDimensions<detail::TetrahedronFaces>
    {
        static const int Value = 3;
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
    struct ItemType<detail::TetrahedronFaces>
    {
        typedef Triangle<3> Type;
    };

    template <>
    struct ItemReferenceType<detail::TetrahedronFaces>
    {
        typedef Triangle<3> Type;
    };

    namespace detail
    {
        class TetrahedronFaces :
            public SpatialCollection<TetrahedronFaces>
        {
        private:
            Tetrahedron3d _tetrahedron;
        public:
            TetrahedronFaces(const Tetrahedron3d& tetrahedron);

            const Tetrahedron3d&
            tetrahedron() const;

            IndexIterator<TetrahedronFaces>
            begin() const;

            IndexIterator<TetrahedronFaces>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            Box<3>
            bounds() const;

            Triangle<3>
            operator[](std::int64_t index) const;
        };
    }

    template <>
    struct ScalingFunction<detail::TetrahedronFaces>
    {
        OPENSOLID_CORE_EXPORT
        detail::TetrahedronFaces
        operator()(
            const detail::TetrahedronFaces& tetrahedronFaces,
            double scale
        ) const;
    };

    template <>
    struct TranslationFunction<detail::TetrahedronFaces>
    {
        OPENSOLID_CORE_EXPORT
        detail::TetrahedronFaces
        operator()(
            const detail::TetrahedronFaces& tetrahedronFaces,
            const Vector3d& vector
        ) const;
    };

    template <int iNumResultDimensions>
    struct TransformationFunction<detail::TetrahedronFaces, iNumResultDimensions> :
        public TransformationFunction<
            SpatialCollection<detail::TetrahedronFaces>,
            iNumResultDimensions
        >
    {
    };

    template <>
    struct TransformationFunction<detail::TetrahedronFaces, 3>
    {
        OPENSOLID_CORE_EXPORT
        detail::TetrahedronFaces
        operator()(
            const detail::TetrahedronFaces& tetrahedronFaces,
            const Matrix3d& matrix
        ) const;
    };

    template <int iNumResultDimensions>
    struct MorphingFunction<detail::TetrahedronFaces, iNumResultDimensions> :
        public MorphingFunction<
            SpatialCollection<detail::TetrahedronFaces>,
            iNumResultDimensions
        >
    {
    };

    template <>
    struct MorphingFunction<detail::TetrahedronFaces, 3>
    {
        OPENSOLID_CORE_EXPORT
        detail::TetrahedronFaces
        operator()(
            const detail::TetrahedronFaces& tetrahedronFaces,
            const ParametricExpression<3, 3>& morphingExpression
        ) const;
    };
}
