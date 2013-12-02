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
