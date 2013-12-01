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
#include <OpenSolid/Core/Transformable.definitions.hpp>

namespace opensolid
{
    template <>
    class Triangle<2> :
        public Transformable<Triangle<2>>
    {
    private:
        Point<2> _vertices[3];
    public:
        Triangle();

        Triangle(
            const Point<2>& firstVertex,
            const Point<2>& secondVertex,
            const Point<2>& thirdVertex
        );

        const Point<2>&
        vertex(int index) const;

        Point<2>&
        vertex(int index);

        OPENSOLID_CORE_EXPORT
        double
        area() const;

        OPENSOLID_CORE_EXPORT
        Point<2>
        centroid() const;

        LineSegment<2>
        edge(int oppositeIndex) const;

        OPENSOLID_CORE_EXPORT
        CoordinateSystem<2, 2>
        coordinateSystem() const;

        Box<2>
        bounds() const;

        bool
        operator==(const Triangle<2>& other) const;

        OPENSOLID_CORE_EXPORT
        static Triangle<2>
        Unit();
    };

    typedef Triangle<2> Triangle2d;

    template <>
    class Triangle<3> :
        public Transformable<Triangle<3>>
    {
    private:
        Point<3> _vertices[3];
    public:
        Triangle();

        Triangle(
            const Point<3>& firstVertex,
            const Point<3>& secondVertex,
            const Point<3>& thirdVertex
        );

        const Point<3>&
        vertex(int index) const;

        Point<3>&
        vertex(int index);

        OPENSOLID_CORE_EXPORT
        double
        area() const;

        OPENSOLID_CORE_EXPORT
        Point<3>
        centroid() const;

        OPENSOLID_CORE_EXPORT
        Vector3d
        normalVector() const;

        LineSegment<3>
        edge(int oppositeIndex) const;

        OPENSOLID_CORE_EXPORT
        CoordinateSystem<3, 2>
        coordinateSystem() const;

        OPENSOLID_CORE_EXPORT
        Plane3d
        plane() const;

        Box<3>
        bounds() const;

        bool
        operator==(const Triangle<3>& other) const;
    };

    typedef Triangle<3> Triangle3d;
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TransformedType<Triangle2d, 3>
    {
        typedef Triangle3d Type;
    };

    template <>
    struct TransformedType<Triangle3d, 2>
    {
        typedef Triangle2d Type;
    };

    template <>
    struct MorphedType<Triangle2d, 3>
    {
        typedef Triangle3d Type;
    };

    template <>
    struct MorphedType<Triangle3d, 2>
    {
        typedef Triangle2d Type;
    };

    template <>
    struct ScalingFunction<Triangle2d>
    {
        OPENSOLID_CORE_EXPORT
        Triangle2d
        operator()(const Triangle2d& triangle, double scale) const;
    };

    template <>
    struct ScalingFunction<Triangle3d>
    {
        OPENSOLID_CORE_EXPORT
        Triangle3d
        operator()(const Triangle3d& triangle, double scale) const;
    };

    template <>
    struct TranslationFunction<Triangle2d>
    {
        OPENSOLID_CORE_EXPORT
        Triangle2d
        operator()(const Triangle2d& triangle, const Vector2d& vector) const;
    };

    template <>
    struct TranslationFunction<Triangle3d>
    {
        OPENSOLID_CORE_EXPORT
        Triangle3d
        operator()(const Triangle3d& triangle, const Vector3d& vector) const;
    };

    template <>
    struct TransformationFunction<Triangle2d, 2>
    {
        OPENSOLID_CORE_EXPORT
        Triangle2d
        operator()(const Triangle2d& triangle, const Matrix2d& matrix) const;
    };

    template <>
    struct TransformationFunction<Triangle2d, 3>
    {
        OPENSOLID_CORE_EXPORT
        Triangle3d
        operator()(
            const Triangle2d& triangle,
            const Matrix<double, 3, 2>& matrix
        ) const;
    };

    template <>
    struct TransformationFunction<Triangle3d, 3>
    {
        OPENSOLID_CORE_EXPORT
        Triangle3d
        operator()(const Triangle3d& triangle, const Matrix3d& matrix) const;
    };

    template <>
    struct TransformationFunction<Triangle3d, 2>
    {
        OPENSOLID_CORE_EXPORT
        Triangle2d
        operator()(
            const Triangle3d& triangle,
            const Matrix<double, 2, 3>& matrix
        ) const;
    };

    namespace detail
    {
        OPENSOLID_CORE_EXPORT
        Triangle2d
        morphed(
            const Triangle2d& triangle,
            const ParametricExpression<2, 2>& morphingExpression
        );

        OPENSOLID_CORE_EXPORT
        Triangle3d
        morphed(
            const Triangle2d& triangle,
            const ParametricExpression<3, 2>& morphingExpression
        );

        OPENSOLID_CORE_EXPORT
        Triangle3d
        morphed(
            const Triangle3d& triangle,
            const ParametricExpression<3, 3>& morphingExpression
        );

        OPENSOLID_CORE_EXPORT
        Triangle2d
        morphed(
            const Triangle3d& triangle,
            const ParametricExpression<2, 3>& morphingExpression
        );
    }

    template <>
    class TolerantComparator<Triangle2d>
    {
    private:
        double _precision;
    public:
        OPENSOLID_CORE_EXPORT
        TolerantComparator(double precision);

        OPENSOLID_CORE_EXPORT
        bool
        operator()(const Triangle2d& firstTriangle, const Triangle2d& secondTriangle) const;
    };

    template <>
    class TolerantComparator<Triangle3d>
    {
    private:
        double _precision;
    public:
        OPENSOLID_CORE_EXPORT
        TolerantComparator(double precision);

        OPENSOLID_CORE_EXPORT
        bool
        operator()(const Triangle3d& firstTriangle, const Triangle3d& secondTriangle) const;
    };
}
