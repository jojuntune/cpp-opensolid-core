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

#include <OpenSolid/Core/Circle.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Triangle.definitions.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    inline
    Circle2d::Circle() :
        _radius(0.0) {
    }

    inline
    Circle2d::Circle(const Point2d& centerPoint, double radius) :
        _centerPoint(centerPoint),
        _radius(radius) {

        assert(radius >= Zero());
    }

    inline
    const Point2d&
    Circle2d::centerPoint() const {
        return _centerPoint;
    }

    inline
    double
    Circle2d::radius() const {
        return _radius;
    }

    inline
    Box2d
    Circle2d::bounds() const {
        return Box2d(
            Interval(centerPoint().x() - radius(), centerPoint().x() + radius()),
            Interval(centerPoint().y() - radius(), centerPoint().y() + radius())
        );
    }

    template <class TTransformation>
    inline
    Circle2d
    Circle2d::transformedBy(const TTransformation& transformation) const {
        return Circle2d(
            centerPoint().transformedBy(transformation),
            transformation.scale() * radius()
        );
    }

    inline
    Circle3d
    Circle2d::placedOnto(const Plane3d& plane) const {
        return Circle3d(centerPoint().placedOnto(plane), plane.normalVector(), radius());
    }

    inline
    LineSegment2d
    Circle2d::projectedOnto(const Axis2d& axis) const {
        Point2d projectedCenter = centerPoint().projectedOnto(axis);
        Vector2d offset = radius() * axis.directionVector();
        return LineSegment2d(projectedCenter - offset, projectedCenter + offset);
    }

    inline
    Circle2d
    Circle2d::circumcircle(const Triangle2d& triangle) {
        return Circle2d(triangle.vertex(0), triangle.vertex(1), triangle.vertex(2));
    }

    inline
    Circle3d::Circle() :
        _radius(0.0) {
    }

    inline
    Circle3d::Circle(
        const Point3d& centerPoint,
        const UnitVector3d& normalVector,
        double radius
    ) : _centerPoint(centerPoint),
        _normalVector(normalVector),
        _radius(radius) {

        assert(radius >= Zero());
    }

    inline
    Circle3d::Circle(const Axis3d& axis, double radius) :
        _centerPoint(axis.originPoint()),
        _normalVector(axis.directionVector()),
        _radius(radius) {

        assert(radius >= Zero());
    }

    inline
    Circle3d::Circle(const Plane3d& plane, double radius) :
        _centerPoint(plane.originPoint()),
        _normalVector(plane.normalVector()),
        _radius(radius) {

        assert(radius >= Zero());
    }

    inline
    const Point3d&
    Circle3d::centerPoint() const {
        return _centerPoint;
    }

    inline
    const UnitVector3d&
    Circle3d::normalVector() const {
        return _normalVector;
    }

    inline
    double
    Circle3d::radius() const {
        return _radius;
    }

    inline
    Plane3d
    Circle3d::plane() const {
        return Plane3d(centerPoint(), normalVector());
    }

    inline
    Axis3d
    Circle3d::axis() const {
        return Axis3d(centerPoint(), normalVector());
    }

    template <class TTransformation>
    inline
    Circle3d
    Circle3d::transformedBy(const TTransformation& transformation) const {
        return Circle3d(
            centerPoint().transformedBy(transformation),
            normalVector().transformedBy(transformation),
            transformation.scale() * radius()
        );
    }

    inline
    Circle3d
    Circle3d::circumcircle(const Triangle3d& triangle) {
        return Circle3d(triangle.vertex(0), triangle.vertex(1), triangle.vertex(2));
    }
}
