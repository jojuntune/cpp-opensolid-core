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

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Sign.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    inline
    const Vector2d&
    UnitVector2d::asVector() const {
        static_assert(
            sizeof(UnitVector2d) == sizeof(Vector2d),
            "Unexpected size mismatch between UnitVector2d and Vector2d"
        );
        return reinterpret_cast<const Vector2d&>(*this);
    }

    inline
    UnitVector2d::UnitVector() {
    }

    inline
    UnitVector2d::UnitVector(int index) :
        Cartesian<double, 2>(int(index == 0), int(index == 1)) {
    }

    inline
    UnitVector2d::UnitVector(double x, double y) :
        Cartesian<double, 2>(x, y) {

        assert(isZero() || sqrt(x * x + y * y) - 1.0 == opensolid::Zero());
    }

    inline
    UnitVector2d::UnitVector(const ColumnMatrix2d& components) :
        Cartesian<double, 2>(components) {

        assert(isZero() || sqrt(x() * x() + y() * y()) - 1.0 == opensolid::Zero());
    }

    inline
    UnitVector2d::operator const Vector2d&() const {
        return asVector();
    }

    inline
    bool
    UnitVector2d::operator==(const Vector2d& vector) const {
        return asVector() == vector;
    }

    inline
    bool
    UnitVector2d::operator!=(const Vector2d& vector) const {
        return asVector() != vector;
    }

    inline
    bool
    UnitVector2d::equals(const Vector2d& vector, double precision) const {
        return asVector().equals(vector, precision);
    }

    inline
    IntervalVector2d
    UnitVector2d::bounds() const {
        return asVector().bounds();
    }

    inline
    bool
    UnitVector2d::isZero() const {
        return x() == 0.0 && y() == 0.0;
    }

    inline
    double
    UnitVector2d::dot(const Vector2d& vector) const {
        return asVector().dot(vector);
    }

    inline
    UnitVector2d
    UnitVector2d::unitOrthogonal() const {
        return UnitVector2d(-y(), x());
    }

    template <class TTransformation>
    inline
    UnitVector2d
    UnitVector2d::transformedBy(const TTransformation& transformation) const {
        return transformation.transform(*this);
    }

    inline    
    Vector2d
    UnitVector2d::projectedOnto(const Axis2d& axis) const {
        return asVector().projectedOnto(axis);
    }

    inline
    UnitVector3d
    UnitVector2d::placedOnto(const Plane3d& plane) const {
        return UnitVector3d(plane.basisMatrix() * components());
    }

    inline
    UnitVector2d
    UnitVector2d::X() {
        return UnitVector2d(1.0, 0.0);
    }

    inline
    UnitVector2d
    UnitVector2d::Y() {
        return UnitVector2d(0.0, 1.0);
    }

    inline
    const Vector3d&
    UnitVector3d::asVector() const {
        static_assert(
            sizeof(UnitVector3d) == sizeof(Vector3d),
            "Unexpected size mismatch between UnitVector3d and Vector3d"
        );
        return reinterpret_cast<const Vector3d&>(*this);
    }

    inline
    UnitVector3d::UnitVector() {
    }

    inline
    UnitVector3d::UnitVector(int index) :
        Cartesian<double, 3>(int(index == 0), int(index == 1), int(index == 2)) {
    }

    inline
    UnitVector3d::UnitVector(double x, double y, double z) :
        Cartesian<double, 3>(x, y, z) {

        assert(isZero() || sqrt(x * x + y * y + z * z) - 1.0 == opensolid::Zero());
    }

    inline
    UnitVector3d::UnitVector(const ColumnMatrix3d& components) :
        Cartesian<double, 3>(components) {

        assert(isZero() || sqrt(x() * x() + y() * y() + z() * z()) - 1.0 == opensolid::Zero());
    }

    inline
    UnitVector3d::operator const Vector3d&() const {
        return asVector();
    }

    inline
    bool
    UnitVector3d::operator==(const Vector3d& vector) const {
        return asVector() == vector;
    }

    inline
    bool
    UnitVector3d::operator!=(const Vector3d& vector) const {
        return asVector() != vector;
    }

    inline
    bool
    UnitVector3d::equals(const Vector3d& vector, double precision) const {
        return asVector().equals(vector, precision);
    }

    inline
    IntervalVector3d
    UnitVector3d::bounds() const {
        return asVector().bounds();
    }

    inline
    bool
    UnitVector3d::isZero() const {
        return x() == 0.0 && y() == 0.0 && z() == 0.0;
    }

    inline
    double
    UnitVector3d::dot(const Vector3d& vector) const {
        return asVector().dot(vector);
    }

    inline
    Vector3d
    UnitVector3d::cross(const Vector3d& vector) const {
        return asVector().cross(vector);
    }

    inline
    UnitVector3d
    UnitVector3d::unitOrthogonal() const {
        return asVector().unitOrthogonal();
    }

    template <class TTransformation>
    inline
    UnitVector3d
    UnitVector3d::transformedBy(const TTransformation& transformation) const {
        return transformation.transform(*this);
    }

    inline
    Vector3d
    UnitVector3d::projectedOnto(const Axis<3>& axis) const {
        return asVector().projectedOnto(axis);
    }

    inline
    Vector3d
    UnitVector3d::projectedOnto(const Plane3d& plane) const {
        return asVector().projectedOnto(plane);
    }

    inline
    Vector2d
    UnitVector3d::projectedInto(const Plane3d& plane) const {
        return asVector().projectedInto(plane);
    }

    inline
    UnitVector3d
    UnitVector3d::X() {
        return UnitVector3d(1.0, 0.0, 0.0);
    }

    inline
    UnitVector3d
    UnitVector3d::Y() {
        return UnitVector3d(0.0, 1.0, 0.0);
    }

    inline
    UnitVector3d
    UnitVector3d::Z() {
        return UnitVector3d(0.0, 0.0, 1.0);
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

    inline
    UnitVector2d
    operator*(Sign sign, const UnitVector2d& unitVector) {
        return UnitVector2d(sign.value() * unitVector.components());
    }

    inline
    UnitVector2d
    operator*(const UnitVector2d& unitVector, Sign sign) {
        return UnitVector2d(unitVector.components() * sign.value());
    }

    inline
    UnitVector3d
    operator*(Sign sign, const UnitVector3d& unitVector) {
        return UnitVector3d(sign.value() * unitVector.components());
    }

    inline
    UnitVector3d
    operator*(const UnitVector3d& unitVector, Sign sign) {
        return UnitVector3d(unitVector.components() * sign.value());
    }

    inline
    Vector2d
    operator*(double scale, const UnitVector2d& unitVector) {
        return scale * static_cast<const Vector2d&>(unitVector);
    }

    inline
    IntervalVector2d
    operator*(Interval scale, const UnitVector2d& unitVector) {
        return scale * static_cast<const Vector2d&>(unitVector);
    }

    inline
    Vector2d
    operator*(const UnitVector2d& unitVector, double scale) {
        return static_cast<const Vector2d&>(unitVector) * scale;
    }

    inline
    IntervalVector2d
    operator*(const UnitVector2d& unitVector, Interval scale) {
        return static_cast<const Vector2d&>(unitVector) * scale;
    }

    inline
    Vector3d
    operator*(double scale, const UnitVector3d& unitVector) {
        return scale * static_cast<const Vector3d&>(unitVector);
    }

    inline
    IntervalVector3d
    operator*(Interval scale, const UnitVector3d& unitVector) {
        return scale * static_cast<const Vector3d&>(unitVector);
    }

    inline
    Vector3d
    operator*(const UnitVector3d& unitVector, double scale) {
        return static_cast<const Vector3d&>(unitVector) * scale;
    }

    inline
    IntervalVector3d
    operator*(const UnitVector3d& unitVector, Interval scale) {
        return static_cast<const Vector3d&>(unitVector) * scale;
    }

    inline
    Vector2d
    operator/(const UnitVector2d& unitVector, double scale) {
        return static_cast<const Vector2d&>(unitVector) / scale;
    }

    inline
    IntervalVector2d
    operator/(const UnitVector2d& unitVector, Interval scale) {
        return static_cast<const Vector2d&>(unitVector) / scale;
    }

    inline
    Vector3d
    operator/(const UnitVector3d& unitVector, double scale) {
        return static_cast<const Vector3d&>(unitVector) / scale;
    }

    inline
    IntervalVector3d
    operator/(const UnitVector3d& unitVector, Interval scale) {
        return static_cast<const Vector3d&>(unitVector) / scale;
    }
}
