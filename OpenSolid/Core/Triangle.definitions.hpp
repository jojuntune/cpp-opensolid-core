/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Simplex/TriangleBase.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<Triangle<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };
    
    template <int iNumDimensions>
    struct NumDimensions<Triangle<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<Triangle<iNumDimensions>, iNumResultDimensions>
    {
        typedef Triangle<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<Triangle<iNumDimensions>, iNumResultDimensions>
    {
        typedef Triangle<iNumResultDimensions> Type;
    };

    template <>
    class Triangle<1> :
        public detail::TriangleBase<1>,
        public Convertible<Triangle<1>>,
        public Transformable<Triangle<1>>
    {
    public:
        Triangle();

        Triangle(
            const Point<1>& firstVertex,
            const Point<1>& secondVertex,
            const Point<1>& thirdVertex
        );
    };

    typedef Triangle<1> Triangle1d;

    template <>
    class Triangle<2> :
        public detail::TriangleBase<2>,
        public Convertible<Triangle<2>>,
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

        bool
        contains(const Point<2>& point, double precision = 1e-12) const;

        bool
        strictlyContains(const Point<2>& point, double precision = 1e-12) const;

        OPENSOLID_CORE_EXPORT
        static Triangle<2>
        Unit();
    };

    typedef Triangle<2> Triangle2d;

    template <>
    class Triangle<3> :
        public detail::TriangleBase<3>,
        public Convertible<Triangle<3>>,
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
        UnitVector<3>
        normalVector() const;

        OPENSOLID_CORE_EXPORT
        Plane3d
        plane() const;
        
        OPENSOLID_CORE_EXPORT
        bool
        contains(const Point<3>& point, double precision = 1e-12) const;
    };

    typedef Triangle<3> Triangle3d;

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

    template <int iNumDimensions>
    struct ScalingFunction<Triangle<iNumDimensions>>
    {
        Triangle<iNumDimensions>
        operator()(const Triangle<iNumDimensions>& triangle, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Triangle<iNumDimensions>>
    {
        Triangle<iNumDimensions>
        operator()(
            const Triangle<iNumDimensions>& triangle,
            const Vector<double, iNumDimensions>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<Triangle<iNumDimensions>, iNumResultDimensions>
    {
        Triangle<iNumResultDimensions>
        operator()(
            const Triangle<iNumDimensions>& triangle,
            const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix
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
}
