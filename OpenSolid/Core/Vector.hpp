/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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

#include <OpenSolid/Core/Vector.definitions.hpp>

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/IntervalVector.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector/VectorBase.hpp>

#include <cstdlib>

namespace opensolid
{
    inline
    Vector1d::Vector() :
        VectorBase<1>(0.0) {
    }

    inline
    Vector1d::Vector(double x) :
        VectorBase<1>(x) {
    }

    inline
    const double
    Vector1d::value() const {
        return component(0);
    }

    inline
    const double
    Vector1d::x() const {
        return value();
    }

    inline
    const double
    Vector1d::squaredNorm() const {
        return value() * value();
    }

    inline
    const double
    Vector1d::norm() const {
        return abs(value());
    }

    inline
    const UnitVector1d
    Vector1d::normalized() const {
        double value = this->value();
        if (value == Zero()) {
            assert(false);
            return UnitVector();
        }
        return UnitVector(value > 0.0 ? 1.0 : -1.0);
    }

    inline
    const double
    Vector1d::dot(const Vector1d& other) const {
        return value() * other.value();
    }

    inline
    const Interval
    Vector1d::dot(const IntervalVector1d& intervalVector) const {
        return value() * intervalVector.value();
    }

    inline
    const double
    Vector1d::minComponent() const {
        return value();
    }

    inline
    const double
    Vector1d::minComponent(std::int64_t& index) const {
        index = 0;
        return value();
    }

    inline
    const double
    Vector1d::maxComponent() const {
        return value();
    }

    inline
    const double
    Vector1d::maxComponent(std::int64_t& index) const {
        index = 0;
        return value();
    }

    inline
    const IntervalVector1d
    Vector1d::hull(const Vector1d& other) const {
        return IntervalVector1d(Interval::Hull(value(), other.value()));
    }

    inline
    const IntervalVector1d
    Vector1d::hull(const IntervalVector1d& intervalVector) const {
        return IntervalVector1d(intervalVector.value().hull(value()));
    }

    inline
    const bool
    Vector1d::operator==(const Vector1d& other) const {
        return value() == other.value();
    }

    inline
    const Vector1d
    Vector1d::Zero() {
        return Vector1d(0.0);
    }

    inline
    const Vector1d
    Vector1d::Random() {
        return Vector1d(-1.0 + 2.0 * double(rand()) / RAND_MAX);
    }

    inline
    Vector2d::Vector() :
        VectorBase<2>(0.0, 0.0) {
    }

    inline
    Vector2d::Vector(double x, double y) :
        VectorBase<2>(x, y) {
    }

    inline
    const double
    Vector2d::x() const {
        return component(0);
    }

    inline
    const double
    Vector2d::y() const {
        return component(1);
    }

    inline
    const double
    Vector2d::squaredNorm() const {
        return x() * x() + y() * y();
    }

    inline
    const double
    Vector2d::norm() const {
        return sqrt(squaredNorm());
    }

    inline
    const UnitVector2d
    Vector2d::normalized() const {
        double norm = this->norm();
        if (norm == Zero()) {
            assert(false);
            return UnitVector2d();
        }
        return UnitVector2d((1.0 / norm) * (*this));
    }

    inline
    const double
    Vector2d::dot(const Vector2d& other) const {
        return x() * other.x() + y() * other.y();
    }

    inline
    const Interval
    Vector2d::dot(const IntervalVector2d& intervalVector) const {
        return x() * intervalVector.x() + y() * intervalVector.y();
    }

    inline
    const double
    Vector2d::minComponent() const {
        if (x() <= y()) {
            return x();
        } else {
            return y();
        }
    }

    inline
    const double
    Vector2d::minComponent(std::int64_t& index) const {
        if (x() <= y()) {
            index = 0;
            return x();
        } else {
            index = 1;
            return y();
        }
    }

    inline
    const double
    Vector2d::maxComponent() const {
        if (x() >= y()) {
            return x();
        } else {
            return y();
        }
    }

    inline
    const double
    Vector2d::maxComponent(std::int64_t& index) const {
        if (x() >= y()) {
            index = 0;
            return x();
        } else {
            index = 1;
            return y();
        }
    }

    inline
    const IntervalVector2d
    Vector2d::hull(const Vector2d& other) const {
        return IntervalVector2d(
            Interval::Hull(x(), other.x()),
            Interval::Hull(y(), other.y())
        );
    }

    inline
    const IntervalVector2d
    Vector2d::hull(const IntervalVector2d& intervalVector) const {
        return IntervalVector2d(
            intervalVector.x().hull(x()),
            intervalVector.y().hull(y())
        );
    }

    inline
    const bool
    Vector2d::operator==(const Vector2d& other) const {
        return x() == other.x() && y() == other.y();
    }

    inline
    const UnitVector2d
    Vector2d::unitOrthogonal() const {
        return Vector2d(-y(), x()).normalized();
    }

    inline
    const Vector2d
    Vector2d::Zero() {
        return Vector2d(0.0, 0.0);
    }

    inline
    const Vector2d
    Vector2d::Random() {
        return Vector2d(
            -1.0 + 2.0 * double(rand()) / RAND_MAX,
            -1.0 + 2.0 * double(rand()) / RAND_MAX
        );
    }

    inline
    Vector3d::Vector() :
        VectorBase<3>(0.0, 0.0, 0.0) {
    }

    inline
    Vector3d::Vector(double x, double y, double z) :
        VectorBase<3>(x, y, z) {
    }

    inline
    const double
    Vector3d::x() const {
        return component(0);
    }

    inline
    const double
    Vector3d::y() const {
        return component(1);
    }

    inline
    const double
    Vector3d::z() const {
        return component(2);
    }

    inline
    const double
    Vector3d::squaredNorm() const {
        return x() * x() + y() * y() + z() * z();
    }

    inline
    const double
    Vector3d::norm() const {
        return sqrt(squaredNorm());
    }

    inline
    const UnitVector3d
    Vector3d::normalized() const {
        double norm = this->norm();
        if (norm == Zero()) {
            assert(false);
            return UnitVector3d();
        }
        return UnitVector3d((1.0 / norm) * (*this));
    }

    inline
    const double
    Vector3d::dot(const Vector3d& other) const {
        return x() * other.x() + y() * other.y() + z() * other.z();
    }

    inline
    const Interval
    Vector3d::dot(const IntervalVector3d& intervalVector) const {
        return x() * intervalVector.x() + y() * intervalVector.y() + z() * intervalVector.z();
    }

    inline
    const double
    Vector3d::minComponent() const {
        if (x() <= y()) {
            if (x() <= z()) {
                return x();
            } else {
                return z();
            }
        } else {
            if (y() <= z()) {
                return y();
            } else {
                return z();
            }
        }
    }

    inline
    const double
    Vector3d::minComponent(std::int64_t& index) const {
        if (x() <= y()) {
            if (x() <= z()) {
                index = 0;
                return x();
            } else {
                index = 2;
                return z();
            }
        } else {
            if (y() <= z()) {
                index = 1;
                return y();
            } else {
                index = 2;
                return z();
            }
        }
    }

    inline
    const double
    Vector3d::maxComponent() const {
        if (x() >= y()) {
            if (x() >= z()) {
                return x();
            } else {
                return z();
            }
        } else {
            if (y() >= z()) {
                return y();
            } else {
                return z();
            }
        }
    }

    inline
    const double
    Vector3d::maxComponent(std::int64_t& index) const {
        if (x() >= y()) {
            if (x() >= z()) {
                index = 0;
                return x();
            } else {
                index = 2;
                return z();
            }
        } else {
            if (y() >= z()) {
                index = 1;
                return y();
            } else {
                index = 2;
                return z();
            }
        }
    }

    inline
    const IntervalVector3d
    Vector3d::hull(const Vector3d& other) const {
        return IntervalVector3d(
            Interval::Hull(x(), other.x()),
            Interval::Hull(y(), other.y()),
            Interval::Hull(z(), other.z())
        );
    }

    inline
    const IntervalVector3d
    Vector3d::hull(const IntervalVector3d& intervalVector) const {
        return IntervalVector3d(
            intervalVector.x().hull(x()),
            intervalVector.y().hull(y()),
            intervalVector.z().hull(z())
        );
    }

    inline
    const bool
    Vector3d::operator==(const Vector3d& other) const {
        return x() == other.x() && y() == other.y() && z() == other.z();
    }

    inline
    const Vector3d
    Vector3d::cross(const Vector3d& other) const {
        return Vector3d(
            y() * other.z() - z() * other.y(),
            z() * other.x() - x() * other.z(),
            x() * other.y() - y() * other.x()
        );
    }

    inline
    const IntervalVector3d
    Vector3d::cross(const IntervalVector3d& intervalVector) const {
        return IntervalVector3d(
            y() * other.z() - z() * other.y(),
            z() * other.x() - x() * other.z(),
            x() * other.y() - y() * other.x()
        );
    }

    inline
    const UnitVector3d
    Vector3d::unitOrthogonal() const {
        if (*this == Zero()) {
            assert(false);
            return UnitVector3d();
        } else {
            if (x() <= y()) {
                if (x() <= z()) {
                    return UnitVector3d::X().cross(*this).normalized();
                } else {
                    return UnitVector3d::Z().cross(*this).normalized();
                }
            } else {
                if (y() <= z()) {
                    return UnitVector3d::Y().cross(*this).normalized();
                } else {
                    return UnitVector3d::Z().cross(*this).normalized();
                }
            }
        }
    }

    inline
    const Vector3d
    Vector3d::Zero() {
        return Vector3d(0.0, 0.0, 0.0);
    }

    inline
    const Vector3d
    Vector3d::Random() {
        return Vector3d(
            -1.0 + 2.0 * double(rand()) / RAND_MAX,
            -1.0 + 2.0 * double(rand()) / RAND_MAX,
            -1.0 + 2.0 * double(rand()) / RAND_MAX
        );
    }

    inline
    const bool
    operator==(const Vector1d& vector, Zero zero) {
        return vector.x() == zero;
    }

    inline
    const bool
    operator==(const Vector2d& vector, Zero zero) {
        return vector.x() == zero && vector.y() == zero;
    }

    inline
    const bool
    operator==(const Vector3d& vector, Zero zero) {
        return vector.x() == zero && vector.y() == zero && vector.z() == zero;
    }

    inline
    const bool
    operator!=(const Vector1d& vector, Zero zero) {
        return !(vector == zero);
    }

    inline
    const bool
    operator!=(const Vector2d& vector, Zero zero) {
        return !(vector == zero);
    }

    inline
    const bool
    operator!=(const Vector3d& vector, Zero zero) {
        return !(vector == zero);
    }

    inline
    const Vector1d
    operator*(double scale, const Vector1d& vector) {
        return Vector1d(scale * vector.x());
    }

    inline
    const Vector2d
    operator*(double scale, const Vector2d& vector) {
        return Vector2d(scale * vector.x(), scale * vector.y());
    }

    inline
    const Vector3d
    operator*(double scale, const Vector3d& vector) {
        return Vector3d(scale * vector.x(), scale * vector.y(), scale * vector.z());
    }

    inline
    const Vector1d
    operator*(const Vector1d& vector, double scale) {
        return Vector1d(scale * vector.x());
    }

    inline
    const Vector2d
    operator*(const Vector2d& vector, double scale) {
        return Vector2d(scale * vector.x(), scale * vector.y());
    }

    inline
    const Vector3d
    operator*(const Vector3d& vector, double scale) {
        return Vector3d(scale * vector.x(), scale * vector.y(), scale * vector.z());
    }

    inline
    const Vector1d
    operator/(const Vector1d& vector, double divisor) {
        if (divisor == Zero()) {
            assert(false);
            return Vector1d();
        }
        return Vector1d(vector.x() / divisor);
    }

    inline
    const Vector2d
    operator/(const Vector2d& vector, double divisor) {
        if (divisor == Zero()) {
            assert(false);
            return Vector2d();
        }
        return (1.0 / divisor) * vector;
    }

    inline
    const Vector3d
    operator/(const Vector3d& vector, double divisor) {
        if (divisor == Zero()) {
            assert(false);
            return Vector3d();
        }
        return (1.0 / divisor) * vector;
    }

    inline
    const Vector1d
    operator+(const Vector1d& firstVector, const Vector1d& secondVector) {
        return Vector1d(firstVector.x() + secondVector.x());
    }

    inline
    const Vector2d
    operator+(const Vector2d& firstVector, const Vector2d& secondVector) {
        return Vector2d(
            firstVector.x() + secondVector.x(),
            firstVector.y() + secondVector.y()
        );
    }

    inline
    const Vector3d
    operator+(const Vector3d& firstVector, const Vector3d& secondVector) {
        return Vector3d(
            firstVector.x() + secondVector.x(),
            firstVector.y() + secondVector.y(),
            firstVector.z() + secondVector.z()
        );
    }

    inline
    const Vector1d
    operator-(const Vector1d& firstVector, const Vector1d& secondVector) {
        return Vector1d(firstVector.x() - secondVector.x());
    }

    inline
    const Vector2d
    operator-(const Vector2d& firstVector, const Vector2d& secondVector) {
        return Vector2d(
            firstVector.x() - secondVector.x(),
            firstVector.y() - secondVector.y()
        );
    }

    inline
    const Vector3d
    operator-(const Vector3d& firstVector, const Vector3d& secondVector) {
        return Vector3d(
            firstVector.x() - secondVector.x(),
            firstVector.y() - secondVector.y(),
            firstVector.z() - secondVector.z()
        );
    }

    template <int iNumDimensions>
    inline
    const bool
    EqualityFunction<Vector<iNumDimensions>>::operator()(
        const Vector<iNumDimensions>& firstVector,
        const Vector<iNumDimensions>& secondVector,
        double precision
    ) const {
        return firstVector - secondVector == Zero(precision);
    }

    template <int iNumDimensions>
    inline
    const IntervalVector<iNumDimensions>
    BoundsFunction<Vector<iNumDimensions>>::operator()(const Vector<iNumDimensions>& vector) const {
        return IntervalVector<iNumDimensions>(vector);
    }
}
