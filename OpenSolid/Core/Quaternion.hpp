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
    Quaternion2d::Quaternion() :
        _components(1.0, 0.0) {
    }

    inline
    Quaternion2d::Quaternion(const ColumnMatrix2d& components) :
        _components(components) {

        assert(components.cwiseSquared().sum() - 1.0 == Zero());
    }

    inline
    Quaternion2d::Quaternion(double cosAngle, double sinAngle) :
        _components(cosAngle, sinAngle) {

        assert(cosAngle * cosAngle + sinAngle * sinAngle - 1 == Zero());
    }

    inline
    Quaternion2d::Quaternion(double angle) :
        _components(cos(angle), sin(angle)) {
    }

    inline
    const ColumnMatrix2d&
    Quaternion2d::components() const {
        return _components;
    }

    inline
    double
    Quaternion2d::cosAngle() const {
        return components()(0);
    }

    inline
    double
    Quaternion2d::sinAngle() const {
        return components()(1);
    }

    inline
    double
    Quaternion2d::angle() const {
        return atan2(sinAngle(), cosAngle());
    }

    inline
    double
    Quaternion2d::dot(const Quaternion2d& other) const {
        return cosAngle() * other.cosAngle() + sinAngle() * other.sinAngle();
    }

    inline
    const Quaternion2d
    Quaternion2d::inverse() const {
        return Quaternion2d(cosAngle(), -sinAngle());
    }

    inline
    const Matrix2d
    Quaternion2d::rotationMatrix() const {
        return Matrix2d(cosAngle(), sinAngle(), -sinAngle(), cosAngle());
    }

    inline
    const Quaternion2d
    Quaternion2d::operator*(const Quaternion2d& other) const {
        double cosAngle = this->cosAngle() * other.cosAngle() - this->sinAngle() * other.sinAngle();
        double sinAngle = this->sinAngle() * other.cosAngle() + this->cosAngle() * other.sinAngle();
        
        double squaredNorm = cosAngle * cosAngle + sinAngle * sinAngle;
        if (squaredNorm - 1 == Zero()) {
            double inverseNorm = 1.0 / sqrt(squaredNorm);
            return Quaternion2d(cosAngle * inverseNorm, sinAngle * inverseNorm);
        } else {
            assert(false);
            return Quaternion2d();
        }
    }

    inline
    const Quaternion2d
    Quaternion2d::identity() {
        return Quaternion2d(ColumnMatrix2d(1.0, 0.0));
    }

    inline
    Quaternion3d::Quaternion() :
        _components(0.0, 0.0, 0.0, 1.0) {
    }

    inline
    Quaternion3d::Quaternion(const Matrix<double, 4, 1>& components) :
        _components(components) {

        assert(components.cwiseSquared().sum() - 1.0 == Zero());
    }

    inline
    Quaternion3d::Quaternion(double x, double y, double z, double w) :
        _components(x, y, z, w) {

        assert(x * x + y * y + z * z + w * w - 1.0 == Zero());
    }

    inline
    Quaternion3d::Quaternion(const UnitVector3d& unitVector, double angle) {
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

        double squaredNorm = x * x + y * y + z * z + w * w;
        if (squaredNorm - 1 == Zero()) {
            double inverseNorm = 1.0 / sqrt(squaredNorm);
            return Quaternion3d(x * inverseNorm, y * inverseNorm, z * inverseNorm, w * inverseNorm);
        } else {
            assert(false);
            return Quaternion3d();
        }
    }

    inline
    const Quaternion3d
    Quaternion3d::identity() {
        return Quaternion3d(Matrix<double, 4, 1>(0.0, 0.0, 0.0, 1.0));
    }
}
