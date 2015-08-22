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
#include <OpenSolid/Core/BoundsFunction.hpp>
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
    Circle2d
    Circle2d::scaledAbout(const Point2d& point, double scale) const {
        return Circle2d(centerPoint().scaledAbout(point, scale), scale * radius());
    }

    inline
    Circle2d
    Circle2d::rotatedAbout(const Point2d& point, const Matrix2d& rotationMatrix) const {
        return Circle2d(centerPoint().rotatedAbout(point, rotationMatrix), radius());
    }

    inline
    Circle2d
    Circle2d::translatedBy(const Vector2d& vector) {
        return Circle2d(centerPoint().translatedBy(vector), radius());
    }

    inline
    Circle2d
    Circle2d::toLocalIn(const Frame2d& frame) const {
        return Circle2d(centerPoint().toLocalIn(frame), radius());
    }

    inline
    Circle2d
    Circle2d::toGlobalFrom(const Frame2d& frame) const {
        return Circle2d(centerPoint().toGlobalFrom(frame), radius());
    }

    inline
    Circle3d
    Circle2d::toGlobalFrom(const Plane3d& plane) const {
        return Circle3d(centerPoint().toGlobalFrom(plane), plane.normalVector(), radius());
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
    Circle2d::mirroredAbout(const Point2d& point, const UnitVector2d& mirrorDirection) const {
        return Circle2d(centerPoint().mirroredAbout(point, mirrorDirection), radius());
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
    Axis3d
    Circle3d::axis() const {
        return Axis3d(centerPoint(), normalVector());
    }

    inline
    Plane3d
    Circle3d::plane() const {
        return Plane3d(centerPoint(), normalVector());
    }

    inline
    Circle3d
    Circle3d::scaledAbout(const Point3d& point, double scale) const {
        return Circle3d(centerPoint().scaledAbout(point, scale), normalVector(), scale * radius());
    }

    inline
    Circle3d
    Circle3d::rotatedAbout(const Point3d& point, const Matrix3d& rotationMatrix) const {
        return Circle3d(
            centerPoint().rotatedAbout(point, rotationMatrix),
            normalVector().rotatedBy(rotationMatrix),
            radius()
        );
    }

    inline
    Circle3d
    Circle3d::translatedBy(const Vector3d& vector) {
        return Circle3d(centerPoint().translatedBy(vector), normalVector(), radius());
    }

    inline
    Circle3d
    Circle3d::toLocalIn(const Frame3d& frame) const {
        return Circle3d(
            centerPoint().toLocalIn(frame),
            normalVector().toLocalIn(frame),
            radius()
        );
    }

    inline
    Circle3d
    Circle3d::toGlobalFrom(const Frame3d& frame) const {
        return Circle3d(
            centerPoint().toGlobalFrom(frame),
            normalVector().toGlobalFrom(frame),
            radius()
        );
    }

    inline
    Circle3d
    Circle3d::mirroredAbout(const Point3d& point, const UnitVector3d& mirrorDirection) const {
        return Circle3d(
            centerPoint().mirroredAbout(point, mirrorDirection),
            normalVector().mirroredAlong(mirrorDirection),
            radius()
        );
    }

    inline
    Circle3d
    Circle3d::circumcircle(const Triangle3d& triangle) {
        return Circle3d(triangle.vertex(0), triangle.vertex(1), triangle.vertex(2));
    }
}
