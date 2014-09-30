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

#include <OpenSolid/Core/Sphere.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Circle.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    template <>
    struct BoundsType<Sphere3d>
    {
        typedef Box<3> Type;
    };

    template <>
    struct NumDimensions<Sphere3d>
    {
        static const int Value = 3;
    };

    template <>
    struct ProjectedType<Sphere3d, Axis<3>>
    {
        typedef LineSegment<3> Type;
    };

    template <>
    struct ProjectedType<Sphere3d, Plane3d>
    {
        typedef Circle<3> Type;
    };

    class Sphere3d :
        public Transformable<Sphere3d>,
        public Convertible<Sphere3d>
    {
    private:
        Point<3> _centerPoint;
        double _radius;
    public:
        Sphere3d();
        
        Sphere3d(const Point<3>& centerPoint, double radius);

        const Point<3>&
        centerPoint() const;

        double
        radius() const;

        double
        volume() const;

        double
        surfaceArea() const;

        const Box<3>
        bounds() const;
    };
    
    template <>
    struct EqualityFunction<Sphere3d>
    {
        bool
        operator()(
            const Sphere3d& firstSphere,
            const Sphere3d& secondSphere,
            double precision
        ) const;
    };

    template <>
    struct ScalingFunction<Sphere3d>
    {
        Sphere3d
        operator()(const Sphere3d& sphere, const Point<3>& originPoint, double scale) const;
    };

    template <>
    struct TranslationFunction<Sphere3d>
    {
        Sphere3d
        operator()(const Sphere3d& sphere, const Vector<double, 3>& vector) const;
    };

    template <>
    struct RotationFunction<Sphere3d>
    {
        OPENSOLID_CORE_EXPORT
        Sphere3d
        operator()(
            const Sphere3d& sphere,
            const Point<3>& originPoint,
            const Matrix<double, 3, 3>& rotationMatrix
        ) const;
    };

    template <>
    struct MirrorFunction<Sphere3d>
    {
        Sphere3d
        operator()(
            const Sphere3d& sphere,
            const Point<3>& originPoint,
            const UnitVector<3>& normalVector
        ) const;
    };

    template <>
    struct ProjectionFunction<Sphere3d, Plane3d>
    {
        OPENSOLID_CORE_EXPORT
        Circle<3>
        operator()(const Sphere3d& sphere, const Plane3d& plane) const;
    };

    template <>
    struct ProjectionFunction<Sphere3d, Axis<3>>
    {
        OPENSOLID_CORE_EXPORT
        LineSegment<3>
        operator()(const Sphere3d& sphere, const Axis<3>& axis) const;
    };
}
