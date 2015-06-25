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

#include <OpenSolid/Core/UnitVector.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Quaternion.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    inline
    UnitVector2d::UnitVector() :
        Vector2d() {
    }

    inline
    UnitVector2d::UnitVector(double x, double y) :
        Vector2d(x, y) {

        assert(sqrt(x * x + y * y) - 1.0 == opensolid::Zero());
    }

    inline
    UnitVector2d::UnitVector(const ColumnMatrix2d& components) :
        Vector2d(components) {

        assert(sqrt(components.cwiseSquared().sum()) - 1.0 == opensolid::Zero());
    }

    inline
    double
    UnitVector2d::norm() const {
        return 1.0;
    }

    inline
    double
    UnitVector2d::squaredNorm() const {
        return 1.0;
    }

    inline
    UnitVector2d
    UnitVector2d::normalized() const {
        return *this;
    }

    inline
    UnitVector2d
    UnitVector2d::unitOrthogonal() const {
        return UnitVector2d(-y(), x());
    }

    inline
    UnitVector2d
    UnitVector2d::rotatedBy(double angle) const {
        return rotatedBy(Quaternion2d(angle).rotationMatrix());
    }

    inline
    UnitVector2d
    UnitVector2d::rotatedBy(const Matrix2d& rotationMatrix) const {
        return UnitVector2d(rotationMatrix * components());
    }

    inline
    UnitVector2d
    UnitVector2d::toLocalIn(const Frame2d& frame) const {
        return UnitVector2d(frame.basisMatrix().transposeProduct(components()));
    }

    inline
    UnitVector2d
    UnitVector2d::toGlobalFrom(const Frame2d& frame) const {
        return UnitVector2d(frame.basisMatrix() * components());
    }

    inline
    UnitVector3d
    UnitVector2d::toGlobalFrom(const Plane3d& plane) const {
        return UnitVector3d(plane.basisMatrix() * components());
    }

    inline
    UnitVector2d
    UnitVector2d::mirroredAlong(const UnitVector2d& mirrorDirection) const {
        return UnitVector2d(
            (*this - 2 * this->dot(mirrorDirection) * mirrorDirection).components()
        );
    }

    inline
    UnitVector2d
    UnitVector2d::mirroredAbout(const Axis2d& axis) const {
        return mirroredAlong(axis.normalVector());
    }

    inline
    UnitVector3d::UnitVector() :
        Vector3d() {
    }

    inline
    UnitVector3d::UnitVector(double x, double y, double z) :
        Vector3d(x, y, z) {

        assert(sqrt(x * x + y * y + z * z) - 1.0 == opensolid::Zero());
    }

    inline
    UnitVector3d::UnitVector(const ColumnMatrix3d& components) :
        Vector3d(components) {

        assert(sqrt(components.cwiseSquared().sum()) - 1.0 == opensolid::Zero());
    }

    inline
    double
    UnitVector3d::norm() const {
        return 1.0;
    }

    inline
    double
    UnitVector3d::squaredNorm() const {
        return 1.0;
    }

    inline
    UnitVector3d
    UnitVector3d::normalized() const {
        return *this;
    }

    inline
    UnitVector3d
    UnitVector3d::rotatedBy(const Matrix3d& rotationMatrix) const {
        return UnitVector3d(rotationMatrix * components());
    }

    inline
    UnitVector3d
    UnitVector3d::toLocalIn(const Frame3d& frame) const {
        return UnitVector3d(frame.basisMatrix().transposeProduct(components()));
    }

    inline
    UnitVector3d
    UnitVector3d::toGlobalFrom(const Frame3d& frame) const {
        return UnitVector3d(frame.basisMatrix() * components());
    }

    inline
    UnitVector3d
    UnitVector3d::mirroredAlong(const UnitVector3d& mirrorDirection) const {
        return UnitVector3d(
            (*this - 2 * this->dot(mirrorDirection) * mirrorDirection).components()
        );
    }

    inline
    UnitVector3d
    UnitVector3d::mirroredAbout(const Plane3d& plane) const {
        return mirroredAlong(plane.normalVector());
    }

    inline
    UnitVector2d
    operator-(const UnitVector2d& unitVector) {
        return UnitVector2d(-unitVector.x(), -unitVector.y());
    }

    inline
    UnitVector3d
    operator-(const UnitVector3d& unitVector) {
        return UnitVector3d(-unitVector.x(), -unitVector.y(), -unitVector.z());
    }
}
