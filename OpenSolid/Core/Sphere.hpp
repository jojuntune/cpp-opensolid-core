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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Circle.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>
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
    Box3d
    Sphere3d::bounds() const {
        return Box3d(
            Interval(centerPoint().x() - radius(), centerPoint().x() + radius()),
            Interval(centerPoint().y() - radius(), centerPoint().y() + radius()),
            Interval(centerPoint().z() - radius(), centerPoint().z() + radius())
        );
    }

    template <class TTransformation>
    inline
    Sphere3d
    Sphere3d::transformedBy(const TTransformation& transformation) const {
        return Sphere3d(
            centerPoint().transformedBy(transformation),
            transformation.scale() * radius()
        );
    }

    inline
    LineSegment3d
    Sphere3d::projectedOnto(const Axis3d& axis) const {
        Point3d projectedCenter = centerPoint().projectedOnto(axis);
        return LineSegment3d(
            projectedCenter - radius() * axis.directionVector(),
            projectedCenter + radius() * axis.directionVector()
        );
    }

    inline
    Circle3d
    Sphere3d::projectedOnto(const Plane3d& plane) const {
        return Circle3d(centerPoint().projectedOnto(plane), plane.normalVector(), radius());
    }

    inline
    Circle2d
    Sphere3d::projectedInto(const Plane3d& plane) const {
        return Circle2d(centerPoint().projectedInto(plane), radius());
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
}
