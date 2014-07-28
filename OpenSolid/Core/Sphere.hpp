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

#include <OpenSolid/Core/Sphere.definitions.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Circle.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    inline
    Sphere3d::Sphere3d() :
        _radius(0.0) {
    }
    
    inline
    Sphere3d::Sphere3d(const Point3d& centerPoint, double radius) :
        _centerPoint(centerPoint),
        _radius(radius) {

        assert(radius >= Zero());
    }

    inline
    const Point3d&
    Sphere3d::centerPoint() const {
        return _centerPoint;
    }

    inline
    double
    Sphere3d::radius() const {
        return _radius;
    }

    inline
    double
    Sphere3d::volume() const {
        return (4.0 / 3.0) * M_PI * radius() * radius() * radius();
    }

    inline
    double
    Sphere3d::surfaceArea() const {
        return 4.0 * M_PI * radius() * radius();
    }

    inline
    const Box3d
    Sphere3d::bounds() const {
        return Box3d(
            Interval(centerPoint().x() - radius(), centerPoint().x() + radius()),
            Interval(centerPoint().y() - radius(), centerPoint().y() + radius()),
            Interval(centerPoint().z() - radius(), centerPoint().z() + radius())
        );
    }
    
    inline
    bool
    EqualityFunction<Sphere3d>::operator()(
        const Sphere3d& firstSphere,
        const Sphere3d& secondSphere,
        double precision
    ) const {
        return (
            equalityFunction(firstSphere.centerPoint(), secondSphere.centerPoint(), precision) &&
            equalityFunction(firstSphere.radius(), secondSphere.radius(), precision)
        );
    }

    inline
    Sphere3d
    ScalingFunction<Sphere3d>::operator()(
        const Sphere3d& sphere,
        const Point3d& originPoint,
        double scale
    ) const {
        return Sphere3d(scaled(sphere.centerPoint(), originPoint, scale), scale * sphere.radius());
    }

    inline
    Sphere3d
    TranslationFunction<Sphere3d>::operator()(
        const Sphere3d& sphere,
        const Vector3d& vector
    ) const {
        return Sphere3d(translated(sphere.centerPoint(), vector), sphere.radius());
    }

    inline
    Sphere3d
    RotationFunction<Sphere3d>::operator()(
        const Sphere3d& sphere,
        const Point3d& originPoint,
        const Matrix3d& rotationMatrix
    ) const {
        return Sphere3d(
            rotated(sphere.centerPoint(), originPoint, transformationMatrix),
            sphere.radius()
        );
    }

    inline
    Sphere3d
    MirrorFunction<Sphere3d>::operator()(
        const Sphere3d& sphere,
        const Point3d& originPoint,
        const UnitVector3d& normalVector
    ) const {
        return Sphere3d(mirrored(sphere.centerPoint(), originPoint, normalVector), sphere.radius());
    }

    inline
    LineSegment3d
    ProjectionFunction<Sphere3d, Axis3d>::operator()(
        const Sphere3d& sphere,
        const Axis3d& axis
    ) const {
        Point3d projectedCenter = sphere.centerPoint().projectedOnto(axis);
        return LineSegment3d(
            projectedCenter - sphere.radius() * axis.directionVector(),
            projectedCenter + sphere.radius() * axis.directionVector()
        );
    }

    inline
    Circle3d
    ProjectionFunction<Sphere3d, Plane3d>::operator()(
        const Sphere3d& sphere,
        const Plane3d& plane
    ) const {
        return Circle3d(
            sphere.centerPoint().projectedOnto(plane),
            plane.normalVector(),
            sphere.radius()
        );
    }
}
