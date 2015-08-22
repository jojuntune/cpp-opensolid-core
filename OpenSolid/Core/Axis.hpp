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

#include <OpenSolid/Core/Axis.definitions.hpp>

#include <OpenSolid/Core/AxisPlaneIntersection3d.hpp>
#include <OpenSolid/Core/AxisTriangleIntersection3d.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/FrameBase.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.definitions.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    inline
    Axis2d::Axis() :
        FrameBase<2, 1>(Point2d::origin(), ColumnMatrix2d::zero()) {
    }

    inline
    Axis2d::Axis(
        const Point2d& originPoint,
        const UnitVector2d& directionVector
    ) : FrameBase<2, 1>(originPoint, directionVector.components()) {
    }
    
    inline
    UnitVector2d
    Axis2d::directionVector() const {
        return UnitVector2d(basisMatrix());
    }

    inline
    UnitVector2d
    Axis2d::normalVector() const {
        return directionVector().unitOrthogonal();
    }

    inline
    Axis2d
    Axis2d::flipped() const {
        return Axis2d(originPoint(), -directionVector());
    }

    inline
    Axis2d
    Axis2d::normalAxis() const {
        return Axis2d(originPoint(), normalVector());
    }

    inline
    Axis2d
    Axis2d::scaledAbout(const Point2d& point, double scale) const {
        return Axis2d(
            originPoint().scaledAbout(point, scale),
            scale >= 0.0 ? directionVector() : -directionVector()
        );
    }

    inline
    Axis2d
    Axis2d::rotatedAbout(const Point2d& point, const Matrix2d& rotationMatrix) const {
        return Axis2d(
            originPoint().rotatedAbout(point, rotationMatrix),
            directionVector().rotatedBy(rotationMatrix)
        );
    }

    inline
    Axis2d
    Axis2d::translatedBy(const Vector2d& vector) const {
        return Axis2d(originPoint().translatedBy(vector), directionVector());
    }

    inline
    Axis2d
    Axis2d::toLocalIn(const Frame2d& frame) const {
        return Axis2d(originPoint().toLocalIn(frame), directionVector().toLocalIn(frame));
    }

    inline
    Axis2d
    Axis2d::toGlobalFrom(const Frame2d& frame) const {
        return Axis2d(originPoint().toGlobalFrom(frame), directionVector().toGlobalFrom(frame));
    }

    inline
    Axis3d
    Axis2d::toGlobalFrom(const Plane3d& plane) const {
        return Axis3d(originPoint().toGlobalFrom(plane), directionVector().toGlobalFrom(plane));
    }

    inline
    Axis2d
    Axis2d::mirroredAbout(const Point2d& point, const UnitVector2d& directionVector) const {
        return Axis2d(
            originPoint().mirroredAbout(point, directionVector),
            this->directionVector().mirroredAlong(directionVector)
        );
    }

    inline
    Axis2d
    Axis2d::x() {
        return Axis2d(Point2d::origin(), Vector2d::unitX());
    }

    inline
    Axis2d
    Axis2d::y() {
        return Axis2d(Point2d::origin(), Vector2d::unitY());
    }

    inline
    Axis3d::Axis() :
        FrameBase<3, 1>(Point3d::origin(), ColumnMatrix3d::zero()) {
    }

    inline
    Axis3d::Axis(
        const Point3d& originPoint,
        const UnitVector3d& directionVector
    ) : FrameBase<3, 1>(originPoint, directionVector.components()) {
    }
    
    inline
    UnitVector3d
    Axis3d::directionVector() const {
        return UnitVector3d(basisMatrix());
    }

    inline
    Axis3d
    Axis3d::flipped() const {
        return Axis3d(originPoint(), -directionVector());
    }

    inline
    Plane3d
    Axis3d::normalPlane() const {
        return Plane3d(originPoint(), directionVector());
    }
    
    inline
    bool
    Axis3d::contains(const Point3d& point, double precision) const {
        return point.squaredDistanceTo(*this) == Zero(precision * precision);
    }

    inline
    Intersection<Axis3d, Plane3d>
    Axis3d::intersection(const Plane3d& plane, double precision) const {
        return Intersection<Axis3d, Plane3d>(*this, plane, precision);
    }

    inline
    Intersection<Axis3d, Triangle3d>
    Axis3d::intersection(const Triangle3d& triangle, double precision) const {
        return Intersection<Axis3d, Triangle3d>(*this, triangle, precision);
    }

    inline
    Axis3d
    Axis3d::scaledAbout(const Point3d& point, double scale) const {
        return Axis3d(
            originPoint().scaledAbout(point, scale),
            scale >= 0.0 ? directionVector() : -directionVector()
        );
    }

    inline
    Axis3d
    Axis3d::rotatedAbout(const Point3d& point, const Matrix3d& rotationMatrix) const {
        return Axis3d(
            originPoint().rotatedAbout(point, rotationMatrix),
            directionVector().rotatedBy(rotationMatrix)
        );
    }

    inline
    Axis3d
    Axis3d::translatedBy(const Vector3d& vector) const {
        return Axis3d(originPoint().translatedBy(vector), directionVector());
    }

    inline
    Axis3d
    Axis3d::toLocalIn(const Frame3d& frame) const {
        return Axis3d(originPoint().toLocalIn(frame), directionVector().toLocalIn(frame));
    }

    inline
    Axis3d
    Axis3d::toGlobalFrom(const Frame3d& frame) const {
        return Axis3d(originPoint().toGlobalFrom(frame), directionVector().toGlobalFrom(frame));
    }

    inline
    Axis3d
    Axis3d::mirroredAbout(const Point3d& point, const UnitVector3d& directionVector) const {
        return Axis3d(
            originPoint().mirroredAbout(point, directionVector),
            this->directionVector().mirroredAlong(directionVector)
        );
    }

    inline
    Axis3d
    Axis3d::x() {
        return Axis3d(Point3d::origin(), Vector3d::unitX());
    }

    inline
    Axis3d
    Axis3d::y() {
        return Axis3d(Point3d::origin(), Vector3d::unitY());
    }

    inline
    Axis3d
    Axis3d::z() {
        return Axis3d(Point3d::origin(), Vector3d::unitZ());
    }
}
