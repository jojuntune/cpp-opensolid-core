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

#include <OpenSolid/Core/Quaternion.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

namespace opensolid
{
    inline
    Quaternion3d::Quaternion3d() {
        _components(3) = 1.0;
    }

    inline
    Quaternion3d::Quaternion3d(const Matrix<double, 4, 1>& components) :
        _components(components) {

        assert(components.cwiseSquared().sum() - 1.0 == Zero());
    }

    inline
    Quaternion3d::Quaternion3d(double x, double y, double z, double w) {
        assert(x * x + y * y + z * z + w * w - 1.0 == Zero());
        _components(0) = x;
        _components(1) = y;
        _components(2) = z;
        _components(3) = w;
    }

    inline
    Quaternion3d::Quaternion3d(const UnitVector3d& unitVector, double angle) {
        double halfAngle = 0.5 * angle;
        double sinHalfAngle = sin(halfAngle);
        _components(0) = unitVector.x() * sinHalfAngle;
        _components(1) = unitVector.y() * sinHalfAngle;
        _components(2) = unitVector.z() * sinHalfAngle;
        _components(3) = cos(halfAngle);
    }

    inline
    const Matrix<double, 4, 1>&
    Quaternion3d::components() const {
        return _components;
    }

    inline
    double
    Quaternion3d::x() const {
        return _components(0);
    }

    inline
    double
    Quaternion3d::y() const {
        return _components(1);
    }

    inline
    double
    Quaternion3d::z() const {
        return _components(2);
    }

    inline
    double
    Quaternion3d::w() const {
        return _components(3);
    }

    inline
    UnitVector3d
    Quaternion3d::unitVector() const {
        Vector3d vector(x(), y(), z());
        if (vector.isZero()) {
            return UnitVector3d();
        } else {
            return vector.normalized();
        }
    }

    inline
    double
    Quaternion3d::angle() const {
        return 2 * atan2(sqrt(x() * x() + y() * y() + z() * z()), w());
    }

    inline
    double
    Quaternion3d::dot(const Quaternion3d& other) const {
        return components().cwiseProduct(other.components()).sum();
    }

    inline
    const Quaternion3d
    Quaternion3d::inverse() const {
        return Quaternion3d(-x(), -y(), -z(), w());
    }

    inline
    const Matrix3d
    Quaternion3d::rotationMatrix() const {
        double wx = w() * x();
        double wy = w() * y();
        double wz = w() * z();
        double xx = x() * x();
        double xy = x() * y();
        double xz = x() * z();
        double yy = y() * y();
        double yz = y() * z();
        double zz = z() * z();

        Matrix3d result;
        result(0, 0) = 1 - 2 * (yy + zz);
        result(1, 0) = 2 * (xy + wz);
        result(2, 0) = 2 * (xz - wy);
        result(0, 1) = 2 * (xy - wz);
        result(1, 1) = 1 - 2 * (xx + zz);
        result(2, 1) = 2 * (yz + wx);
        result(0, 2) = 2 * (xz + wy);
        result(1, 2) = 2 * (yz - wx);
        result(2, 2) = 1 - 2 * (xx + yy);
        return result;
    }

    inline
    Quaternion3d
    Quaternion3d::operator*(const Quaternion3d& other) const {
        double x1 = x();
        double y1 = y();
        double z1 = z();
        double w1 = w();
        double x2 = other.x();
        double y2 = other.y();
        double z2 = other.z();
        double w2 = other.w();

        double x = w2 * x1 + w1 * x2 + y1 * z2 - z1 * y2;
        double y = w2 * y1 + w1 * y2 + z1 * x2 - x1 * z2;
        double z = w2 * z1 + w1 * z2 + x1 * y2 - y1 * x2;
        double w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
        double inverseNorm = 1.0 / sqrt(x * x + y * y + z * z + w * w);
        assert(inverseNorm - 1.0 == Zero()); // Should be very close to normalized already

        return Quaternion3d(x * inverseNorm, y * inverseNorm, z * inverseNorm, w * inverseNorm);
    }

    inline
    const Quaternion3d
    Quaternion3d::Identity() {
        Matrix<double, 4, 1> identityComponents;
        identityComponents(3) = 1.0;
        return Quaternion3d(identityComponents);
    }
}
