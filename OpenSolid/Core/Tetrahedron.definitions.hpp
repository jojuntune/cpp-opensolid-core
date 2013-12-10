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

#include <OpenSolid/Core/Tetrahedron.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/SimplexVertices.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>

namespace opensolid
{
    class Tetrahedron3d :
        public Transformable<Tetrahedron3d>
    {
    private:
        Point<3> _vertices[4];
    public:
        Tetrahedron3d();

        Tetrahedron3d(
            const Point<3>& firstVertex,
            const Point<3>& secondVertex,
            const Point<3>& thirdVertex,
            const Point<3>& fourthVertex
        );

        const Point<3>&
        vertex(int index) const;

        Point<3>&
        vertex(int index);

        detail::SimplexVertices<Tetrahedron3d, 4>
        vertices() const;

        OPENSOLID_CORE_EXPORT
        LineSegment<3>
        edge(int index) const;

        detail::TetrahedronEdges
        edges() const;

        OPENSOLID_CORE_EXPORT
        Triangle<3>
        face(int oppositeIndex) const;

        detail::TetrahedronFaces
        faces() const;

        OPENSOLID_CORE_EXPORT
        double
        volume() const;

        OPENSOLID_CORE_EXPORT
        Point<3>
        centroid() const;

        OPENSOLID_CORE_EXPORT
        CoordinateSystem<3, 3>
        coordinateSystem() const;

        Box<3>
        bounds() const;

        bool
        operator==(const Tetrahedron3d& other) const;

        OPENSOLID_CORE_EXPORT
        static Tetrahedron3d
        Unit();
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
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct ScalingFunction<Tetrahedron3d>
    {
        OPENSOLID_CORE_EXPORT
        Tetrahedron3d
        operator()(const Tetrahedron3d& tetrahedron, double scale) const;
    };

    template <>
    struct TranslationFunction<Tetrahedron3d>
    {
        OPENSOLID_CORE_EXPORT
        Tetrahedron3d
        operator()(const Tetrahedron3d& tetrahedron, const Vector3d& vector) const;
    };

    template <>
    struct TransformationFunction<Tetrahedron3d, 3>
    {
        OPENSOLID_CORE_EXPORT
        Tetrahedron3d
        operator()(const Tetrahedron3d& tetrahedron, const Matrix3d& matrix) const;
    };

    template <>
    struct MorphingFunction<Tetrahedron3d, 3>
    {
        OPENSOLID_CORE_EXPORT
        Tetrahedron3d
        operator()(
            const Tetrahedron3d& tetrahedron,
            const ParametricExpression<3, 3>& morphingExpression
        ) const;
    };

    template <>
    struct EqualityFunction<Tetrahedron3d>
    {
        bool
        operator()(
            const Tetrahedron3d& firstTetrahedron,
            const Tetrahedron3d& secondTetrahedron,
            double precision
        ) const;
    };

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
