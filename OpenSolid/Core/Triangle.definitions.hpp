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

#include <OpenSolid/Core/Triangle.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/IndexIterator.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class TriangleVertices :
            public SpatialCollection<TriangleVertices<iNumDimensions>>
        {
        private:
            Triangle<iNumDimensions> _triangle;
        public:
            TriangleVertices(const Triangle<iNumDimensions>& triangle);

            const Triangle<iNumDimensions>&
            triangle() const;

            IndexIterator<TriangleVertices<iNumDimensions>>
            begin() const;

            IndexIterator<TriangleVertices<iNumDimensions>>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            Box<iNumDimensions>
            bounds() const;

            const Point<iNumDimensions>&
            operator[](std::int64_t index) const;
        };

        template <int iNumDimensions>
        class TriangleEdges :
            public SpatialCollection<TriangleEdges<iNumDimensions>>
        {
        private:
            Triangle<iNumDimensions> _triangle;
        public:
            TriangleEdges(const Triangle<iNumDimensions>& triangle);

            const Triangle<iNumDimensions>&
            triangle() const;

            IndexIterator<TriangleEdges<iNumDimensions>>
            begin() const;

            IndexIterator<TriangleEdges<iNumDimensions>>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            Box<iNumDimensions>
            bounds() const;

            LineSegment<iNumDimensions>
            operator[](std::int64_t index) const;
        };

        template <int iNumDimensions>
        class TriangleBase
        {
        private:
            Point<iNumDimensions> _vertices[3];

            const Triangle<iNumDimensions>&
            derived() const;
        protected:
            TriangleBase();

            TriangleBase(
                const Point<iNumDimensions>& firstVertex,
                const Point<iNumDimensions>& secondVertex,
                const Point<iNumDimensions>& thirdVertex
            );
        public:
            const Point<iNumDimensions>&
            vertex(int index) const;

            Point<iNumDimensions>&
            vertex(int index);

            TriangleVertices<iNumDimensions>
            vertices() const;

            Point<iNumDimensions>
            centroid() const;

            LineSegment<iNumDimensions>
            edge(int oppositeIndex) const;

            TriangleEdges<iNumDimensions>
            edges() const;

            CoordinateSystem<iNumDimensions, 2>
            coordinateSystem() const;

            Box<iNumDimensions>
            bounds() const;

            bool
            operator==(const Triangle<iNumDimensions>& other) const;
        };
    }

    template <>
    class Triangle<2> :
        public detail::TriangleBase<2>,
        public Transformable<Triangle<2>>
    {
    public:
        Triangle();

        Triangle(
            const Point<2>& firstVertex,
            const Point<2>& secondVertex,
            const Point<2>& thirdVertex
        );

        OPENSOLID_CORE_EXPORT
        double
        area() const;

        OPENSOLID_CORE_EXPORT
        static Triangle<2>
        Unit();
    };

    typedef Triangle<2> Triangle2d;

    template <>
    class Triangle<3> :
        public detail::TriangleBase<3>,
        public Transformable<Triangle<3>>
    {
    public:
        Triangle();

        Triangle(
            const Point<3>& firstVertex,
            const Point<3>& secondVertex,
            const Point<3>& thirdVertex
        );

        OPENSOLID_CORE_EXPORT
        double
        area() const;

        OPENSOLID_CORE_EXPORT
        Vector3d
        normalVector() const;

        OPENSOLID_CORE_EXPORT
        Plane3d
        plane() const;
    };

    typedef Triangle<3> Triangle3d;
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct NumDimensions<detail::TriangleVertices<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions>
    struct ItemType<detail::TriangleVertices<iNumDimensions>>
    {
        typedef Point<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ItemReferenceType<detail::TriangleVertices<iNumDimensions>>
    {
        typedef const Point<iNumDimensions>& Type;
    };

    template <int iNumDimensions>
    struct ScaledType<detail::TriangleVertices<iNumDimensions>>
    {
        typedef detail::TriangleVertices<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct TranslatedType<detail::TriangleVertices<iNumDimensions>>
    {
        typedef detail::TriangleVertices<iNumDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<detail::TriangleVertices<iNumDimensions>, iNumResultDimensions>
    {
        typedef detail::TriangleVertices<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<detail::TriangleVertices<iNumDimensions>, iNumResultDimensions>
    {
        typedef detail::TriangleVertices<iNumResultDimensions> Type;
    };

    template <int iNumDimensions>
    struct ScalingFunction<detail::TriangleVertices<iNumDimensions>>
    {
        detail::TriangleVertices<iNumDimensions>
        operator()(
            const detail::TriangleVertices<iNumDimensions>& triangleVertices,
            double scale
        ) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<detail::TriangleVertices<iNumDimensions>>
    {
        template <class TVector>
        detail::TriangleVertices<iNumDimensions>
        operator()(
            const detail::TriangleVertices<iNumDimensions>& triangleVertices,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<detail::TriangleVertices<iNumDimensions>, iNumResultDimensions>
    {
        template <class TMatrix>
        detail::TriangleVertices<iNumResultDimensions>
        operator()(
            const detail::TriangleVertices<iNumDimensions>& triangleVertices,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<detail::TriangleVertices<iNumDimensions>, iNumResultDimensions>
    {
        detail::TriangleVertices<iNumResultDimensions>
        operator()(
            const detail::TriangleVertices<iNumDimensions>& triangleVertices,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };

    template <int iNumDimensions>
    struct BoundsType<detail::TriangleVertices<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<detail::TriangleEdges<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions>
    struct ItemType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef LineSegment<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ItemReferenceType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef LineSegment<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ScaledType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef detail::TriangleEdges<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct TranslatedType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef detail::TriangleEdges<iNumDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<detail::TriangleEdges<iNumDimensions>, iNumResultDimensions>
    {
        typedef detail::TriangleEdges<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<detail::TriangleEdges<iNumDimensions>, iNumResultDimensions>
    {
        typedef detail::TriangleEdges<iNumResultDimensions> Type;
    };

    template <int iNumDimensions>
    struct ScalingFunction<detail::TriangleEdges<iNumDimensions>>
    {
        detail::TriangleEdges<iNumDimensions>
        operator()(
            const detail::TriangleEdges<iNumDimensions>& triangleEdges,
            double scale
        ) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<detail::TriangleEdges<iNumDimensions>>
    {
        template <class TVector>
        detail::TriangleEdges<iNumDimensions>
        operator()(
            const detail::TriangleEdges<iNumDimensions>& triangleEdges,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<detail::TriangleEdges<iNumDimensions>, iNumResultDimensions>
    {
        template <class TMatrix>
        detail::TriangleEdges<iNumResultDimensions>
        operator()(
            const detail::TriangleEdges<iNumDimensions>& triangleEdges,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<detail::TriangleEdges<iNumDimensions>, iNumResultDimensions>
    {
        detail::TriangleEdges<iNumResultDimensions>
        operator()(
            const detail::TriangleEdges<iNumDimensions>& triangleEdges,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };

    template <int iNumDimensions>
    struct BoundsType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ScalingFunction<Triangle<iNumDimensions>>
    {
        Triangle<iNumDimensions>
        operator()(const Triangle<iNumDimensions>& triangle, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Triangle<iNumDimensions>>
    {
        template <class TVector>
        Triangle<iNumDimensions>
        operator()(
            const Triangle<iNumDimensions>& triangle,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<Triangle<iNumDimensions>, iNumResultDimensions>
    {
        template <class TMatrix>
        Triangle<iNumResultDimensions>
        operator()(
            const Triangle<iNumDimensions>& triangle,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<Triangle<iNumDimensions>, iNumResultDimensions>
    {
        Triangle<iNumResultDimensions>
        operator()(
            const Triangle<iNumDimensions>& triangle,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };

    template <int iNumDimensions>
    struct EqualityFunction<Triangle<iNumDimensions>>
    {
        bool
        operator()(
            const Triangle<iNumDimensions>& firstTriangle,
            const Triangle<iNumDimensions>& secondTriangle,
            double precision
        ) const;
    };
}
