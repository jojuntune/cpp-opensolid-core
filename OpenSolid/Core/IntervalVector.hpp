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

#include <OpenSolid/Core/IntervalVector.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Vector.hpp>
#include <OpenSolid/Core/Vector/IntervalVectorBase.hpp>

namespace opensolid
{
    inline
    IntervalVector1d::IntervalVector() :
        IntervalVectorBase<1>(Interval::Empty()) {
    }

    inline
    IntervalVector1d::IntervalVector1d(Interval value) :
        IntervalVectorBase<1>(value) {
    }

    inline
    IntervalVector1d::IntervalVector1d(const Vector1d& vector) :
        IntervalVectorBase<1>(vector.value()) {
    }

    inline
    const Interval
    IntervalVector1d::value() const {
        return component(0);
    }

    inline
    const Interval
    IntervalVector1d::x() const {
        return component(0);
    }

    inline
    const Interval
    IntervalVector1d::squaredNorm() const {
        return value().squared();
    }

    inline
    const Interval
    IntervalVector1d::norm() const {
        return abs(value());
    }

    inline
    const IntervalVector1d
    IntervalVector1d::normalized() const {
        if (value().lower() > Zero()) {
            return IntervalVector1d(1.0);
        } else if (value().upper() < Zero()) {
            return IntervalVector1d(-1.0);
        } else {
            return IntervalVector1d(Interval(-1.0, 1.0));
        }
    }

    inline
    const Interval
    IntervalVector1d::dot(const Vector1d& vector) const {
        return value() * vector.value();
    }

    inline
    const Interval
    IntervalVector1d::dot(const IntervalVector& other) const {
        return value() * other.value();
    }

    inline
    const IntervalVector
    IntervalVector1d::hull(const IntervalVector& other) const {
        return IntervalVector1d(value().hull(other.value()));
    }

    inline
    const IntervalVector
    IntervalVector1d::hull(const Vector1d& vector) const {
        return IntervalVector1d(value().hull(vector.value()));
    }

    inline
    const IntervalVector
    IntervalVector1d::Unit() {
        return IntervalVector1d(Interval::Unit());
    }

    inline
    const IntervalVector
    IntervalVector1d::Empty() {
        return IntervalVector1d(Interval::Empty());
    }

    inline
    const IntervalVector
    IntervalVector1d::Whole() {
        return IntervalVector1d(Interval::Whole());
    }

    inline
    IntervalVector2d::IntervalVector() :
        IntervalVectorBase<2>(Interval::Empty(), Interval::Empty()) {
    }

    inline
    IntervalVector2d::IntervalVector(Interval x, Interval y) :
        IntervalVectorBase<2>(x, y) {
    }

    inline
    IntervalVector2d::IntervalVector(const Vector2d& vector) :
        IntervalVectorBase<2>(vector.component(0), vector.component(1)) {
    }

    inline
    const Interval
    IntervalVector2d::x() const {
        return component(0);
    }

    inline
    const Interval
    IntervalVector2d::y() const {
        return component(1);
    }

    inline
    const Interval
    IntervalVector2d::squaredNorm() const {
        return component(0).squared() + component(1).squared();
    }

    inline
    const Interval
    IntervalVector2d::norm() const {
        return sqrt(squaredNorm());
    }

    inline
    const IntervalVector2d
    IntervalVector2d::normalized() const {
        return (*this) / norm();
    }

    inline
    const Interval
    IntervalVector2d::dot(const Vector2d& vector) const {
        return component(0) * vector.component(0) +
            component(1) * vector.component(1);
    }

    inline
    const Interval
    IntervalVector2d::dot(const IntervalVector2d& other) const {
        return component(0) * other.component(0) +
            component(1) * other.component(1);
    }

    inline
    const IntervalVector2d
    IntervalVector2d::hull(const IntervalVector2d& other) const {
        return IntervalVector2d(
            component(0).hull(other.component(0)),
            component(1).hull(other.component(1))
        );
    }

    inline
    const IntervalVector2d
    IntervalVector2d::hull(const Vector2d& vector) const {
        return IntervalVector2d(
            component(0).hull(vector.component(0)),
            component(1).hull(vector.component(1))
        );
    }

    inline
    const IntervalVector2d
    IntervalVector2d::Unit() {
        return IntervalVector2d(Interval::Unit(), Interval::Unit());
    }

    inline
    const IntervalVector2d
    IntervalVector2d::Empty() {
        return IntervalVector2d(Interval::Empty(), Interval::Empty());
    }

    inline
    const IntervalVector2d
    IntervalVector2d::Whole() {
        return IntervalVector2d(Interval::Whole(), Interval::Whole());
    }

    inline
    IntervalVector3d::IntervalVector() :
        IntervalVectorBase(Interval::Empty(), Interval::Empty(), Interval::Empty()) {
    }

    inline
    IntervalVector3d::IntervalVector(Interval x, Interval y, Interval z) :
        IntervalVectorBase<3>(x, y, z) {

    }

    inline
    IntervalVector3d::IntervalVector(const Vector3d& vector) :
        IntervalVectorBase(vector.component(0), vector.component(1), vector.component(2)) {
    }

    inline
    const Interval
    IntervalVector3d::x() const {
        return component(0);
    }

    inline
    const Interval
    IntervalVector3d::y() const {
        return component(1);
    }

    inline
    const Interval
    IntervalVector3d::z() const {
        return component(2);
    }

    inline
    const Interval
    IntervalVector3d::squaredNorm() const {
        return component(0).squared() + component(1).squared() + component(2).squared();
    }

    inline
    const Interval
    IntervalVector3d::norm() const {
        return sqrt(squaredNorm());
    }

    inline
    const IntervalVector3d
    IntervalVector3d::normalized() const {
        return (*this) / norm();
    }

    inline
    const Interval
    IntervalVector3d::dot(const Vector3d& vector) const {
        return component(0) * vector.component(0) +
            component(1) * vector.component(1) +
            component(2) * vector.component(2);
    }

    inline
    const Interval
    IntervalVector3d::dot(const IntervalVector3d& other) const {
        return component(0) * other.component(0) +
            component(1) * other.component(1) +
            component(2) * other.component(2);
    }

    inline
    const IntervalVector3d
    IntervalVector3d::hull(const IntervalVector3d& other) const {
        return IntervalVector2d(
            component(0).hull(other.component(0)),
            component(1).hull(other.component(1)),
            component(2).hull(other.component(2))
        );
    }

    inline
    const IntervalVector3d
    IntervalVector3d::hull(const Vector3d& vector) const {
        return IntervalVector2d(
            component(0).hull(vector.component(0)),
            component(1).hull(vector.component(1)),
            component(2).hull(vector.component(2))
        );
    }

    inline
    const IntervalVector3d
    IntervalVector3d::cross(const Vector3d& vector) const {
        return IntervalVector3d(
            y() * vector.z() - z() * vector.y(),
            z() * vector.x() - x() * vector.z(),
            x() * vector.y() - y() * vector.x()
        );
    }

    inline
    const IntervalVector3d
    IntervalVector3d::cross(const IntervalVector3d& other) const {
        return IntervalVector3d(
            y() * other.z() - z() * other.y(),
            z() * other.x() - x() * other.z(),
            x() * other.y() - y() * other.x()
        );
    }

    inline
    const IntervalVector3d
    IntervalVector3d::Unit() {
        return IntervalVector2d(Interval::Unit(), Interval::Unit(), Interval::Unit());
    }

    inline
    const IntervalVector3d
    IntervalVector3d::Empty() {
        return IntervalVector2d(Interval::Empty(), Interval::Empty(), Interval::Empty());
    }

    inline
    const IntervalVector3d
    IntervalVector3d::Whole() {
        return IntervalVector3d(Interval::Whole(), Interval::Whole(), Interval::Whole());
    }

    inline
    const IntervalVector1d
    operator*(Interval scale, const Vector1d& vector) {
        return IntervalVector1d(scale * vector.x());
    }

    inline
    const IntervalVector2d
    operator*(Interval scale, const Vector2d& vector) {
        return IntervalVector2d(scale * vector.x(), scale * vector.y());
    }

    inline
    const IntervalVector3d
    operator*(Interval scale, const Vector3d& vector) {
        return IntervalVector3d(scale * vector.x(), scale * vector.y(), scale * vector.z());
    }

    inline
    const IntervalVector1d
    operator*(double scale, const IntervalVector1d& intervalVector) {
        return IntervalVector1d(scale * intervalVector.value());
    }

    inline
    const IntervalVector2d
    operator*(double scale, const IntervalVector2d& intervalVector) {
        return IntervalVector2d(scale * intervalVector.x(), scale * intervalVector.y());
    }

    inline
    const IntervalVector3d
    operator*(double scale, const IntervalVector3d& intervalVector) {
        return IntervalVector3d(
            scale * intervalVector.x(),
            scale * intervalVector.y(),
            scale * intervalVector.z()
        );
    }

    inline
    const IntervalVector1d
    operator*(Interval scale, const IntervalVector1d& intervalVector) {
        return IntervalVector1d(scale * intervalVector.value());
    }

    inline
    const IntervalVector2d
    operator*(Interval scale, const IntervalVector2d& intervalVector) {
        return IntervalVector2d(scale * intervalVector.x(), scale * intervalVector.y());
    }

    inline
    const IntervalVector3d
    operator*(Interval scale, const IntervalVector3d& intervalVector) {
        return IntervalVector3d(
            scale * intervalVector.x(),
            scale * intervalVector.y(),
            scale * intervalVector.z()
        );
    }

    inline
    const IntervalVector1d
    operator*(const Vector1d& vector, Interval scale) {
        return IntervalVector1d(scale * intervalVector.value());
    }

    inline
    const IntervalVector2d
    operator*(const Vector2d& vector, Interval scale) {
        return IntervalVector2d(scale * intervalVector.x(), scale * intervalVector.y());
    }

    inline
    const IntervalVector3d
    operator*(const Vector3d& vector, Interval scale) {
        return IntervalVector3d(
            scale * intervalVector.x(),
            scale * intervalVector.y(),
            scale * intervalVector.z()
        );
    }

    inline
    const IntervalVector1d
    operator*(const IntervalVector1d& intervalVector, double scale) {
        return IntervalVector1d(scale * intervalVector.value());
    }

    inline
    const IntervalVector2d
    operator*(const IntervalVector2d& intervalVector, double scale) {
        return IntervalVector2d(scale * intervalVector.x(), scale * intervalVector.y());
    }

    inline
    const IntervalVector3d
    operator*(const IntervalVector3d& intervalVector, double scale) {
        return IntervalVector3d(
            scale * intervalVector.x(),
            scale * intervalVector.y(),
            scale * intervalVector.z()
        );
    }

    inline
    const IntervalVector1d
    operator*(const IntervalVector1d& intervalVector, Interval scale) {
        return IntervalVector1d(scale * intervalVector.value());
    }

    inline
    const IntervalVector2d
    operator*(const IntervalVector2d& intervalVector, Interval scale) {
        return IntervalVector2d(scale * intervalVector.x(), scale * intervalVector.y());
    }

    inline
    const IntervalVector3d
    operator*(const IntervalVector3d& intervalVector, Interval scale) {
        return IntervalVector3d(
            scale * intervalVector.x(),
            scale * intervalVector.y(),
            scale * intervalVector.z()
        );
    }

    inline
    const IntervalVector1d
    operator/(const Vector1d& vector, Interval divisor) {
        return IntervalVector1d(vector.value() / divisor);
    }

    inline
    const IntervalVector2d
    operator/(const Vector2d& vector, Interval divisor) {
        return IntervalVector2d(vector.x() / divisor, vector.y() / divisor);
    }

    inline
    const IntervalVector3d
    operator/(const Vector3d& vector, Interval divisor) {
        return IntervalVector3d(vector.x() / divisor, vector.y() / divisor, vector.z() / divisor);
    }

    inline
    const IntervalVector1d
    operator/(const IntervalVector1d& intervalVector, double divisor) {
        return IntervalVector1d(intervalVector.value() / divisor);
    }

    inline
    const IntervalVector2d
    operator/(const IntervalVector2d& intervalVector, double divisor) {
        return IntervalVector2d(intervalVector.x() / divisor, intervalVector.y() / divisor);
    }

    inline
    const IntervalVector3d
    operator/(const IntervalVector3d& intervalVector, double divisor) {
        return IntervalVector3d(
            intervalVector.x() / divisor,
            intervalVector.y() / divisor,
            intervalVector.z() / divisor
        );
    }

    inline
    const IntervalVector1d
    operator/(const IntervalVector1d& intervalVector, Interval divisor) {
        return IntervalVector1d(intervalVector.value() / divisor);
    }

    inline
    const IntervalVector2d
    operator/(const IntervalVector2d& intervalVector, Interval divisor) {
        return IntervalVector2d(intervalVector.x() / divisor, intervalVector.y() / divisor);
    }

    inline
    const IntervalVector3d
    operator/(const IntervalVector3d& intervalVector, Interval divisor) {
        return IntervalVector3d(
            intervalVector.x() / divisor,
            intervalVector.y() / divisor,
            intervalVector.z() / divisor
        );
    }

    inline
    const IntervalVector1d
    operator+(const Vector1d& vector, const IntervalVector1d& intervalVector) {
        return IntervalVector1d(vector.value() + intervalVector.value());
    }

    inline
    const IntervalVector1d
    operator+(const IntervalVector1d& intervalVector, const Vector1d& vector) {
        return IntervalVector1d(intervalVector.value() + vector.value());
    }

    inline
    const IntervalVector1d
    operator+(
        const IntervalVector1d& firstIntervalVector,
        const IntervalVector1d& secondIntervalVector
    ) {
        return IntervalVector1d(firstIntervalVector.value() + secondIntervalVector.value());
    }

    inline
    const IntervalVector2d
    operator+(const Vector2d& vector, const IntervalVector2d& intervalVector) {
        return IntervalVector2d(
            vector.x() + intervalVector.x(),
            vector.y() + intervalVector.y()
        );
    }

    inline
    const IntervalVector2d
    operator+(const IntervalVector2d& intervalVector, const Vector2d& vector) {
        return IntervalVector2d(
            intervalVector.x() + vector.x(),
            intervalVector.y() + vector.y()
        );
    }

    inline
    const IntervalVector2d
    operator+(
        const IntervalVector2d& firstIntervalVector,
        const IntervalVector2d& secondIntervalVector
    ) {
        return IntervalVector2d(
            firstIntervalVector.x() + secondIntervalVector.x(),
            firstIntervalVector.y() + secondIntervalVector.y()
        );
    }

    inline
    const IntervalVector3d
    operator+(const Vector3d& vector, const IntervalVector3d& intervalVector) {
        return IntervalVector3d(
            vector.x() + intervalVector.x(),
            vector.y() + intervalVector.y(),
            vector.z() + intervalVector.z()
        );
    }

    inline
    const IntervalVector3d
    operator+(const IntervalVector3d& intervalVector, const Vector3d& vector) {
        return IntervalVector3d(
            intervalVector.x() + vector.x(),
            intervalVector.y() + vector.y(),
            intervalVector.z() + vector.z()
        );
    }

    inline
    const IntervalVector3d
    operator+(
        const IntervalVector3d& firstIntervalVector,
        const IntervalVector3d& secondIntervalVector
    ) {
        return IntervalVector3d(
            firstIntervalVector.x() + secondIntervalVector.x(),
            firstIntervalVector.y() + secondIntervalVector.y(),
            firstIntervalVector.z() + secondIntervalVector.z()
        );
    }

    inline
    const IntervalVector1d
    operator-(const Vector1d& vector, const IntervalVector1d& intervalVector) {
        return IntervalVector1d(vector.value() - intervalVector.value());
    }

    inline
    const IntervalVector1d
    operator-(const IntervalVector1d& intervalVector, const Vector1d& vector) {
        return IntervalVector1d(intervalVector.value() - vector.value());
    }

    inline
    const IntervalVector1d
    operator-(
        const IntervalVector1d& firstIntervalVector,
        const IntervalVector1d& secondIntervalVector
    ) {
        return IntervalVector1d(firstIntervalVector.value() - secondIntervalVector.value());
    }

    inline
    const IntervalVector2d
    operator-(const Vector2d& vector, const IntervalVector2d& intervalVector) {
        return IntervalVector2d(
            vector.x() - intervalVector.x(),
            vector.y() - intervalVector.y()
        );
    }

    inline
    const IntervalVector2d
    operator-(const IntervalVector2d& intervalVector, const Vector2d& vector) {
        return IntervalVector2d(
            intervalVector.x() - vector.x(),
            intervalVector.y() - vector.y()
        );
    }

    inline
    const IntervalVector2d
    operator-(
        const IntervalVector2d& firstIntervalVector,
        const IntervalVector2d& secondIntervalVector
    ) {
        return IntervalVector2d(
            firstIntervalVector.x() - secondIntervalVector.x(),
            firstIntervalVector.y() - secondIntervalVector.y()
        );
    }

    inline
    const IntervalVector3d
    operator-(const Vector3d& vector, const IntervalVector3d& intervalVector) {
        return IntervalVector3d(
            vector.x() - intervalVector.x(),
            vector.y() - intervalVector.y(),
            vector.z() - intervalVector.z()
        );
    }

    inline
    const IntervalVector3d
    operator-(const IntervalVector3d& intervalVector, const Vector3d& vector) {
        return IntervalVector3d(
            intervalVector.x() - vector.x(),
            intervalVector.y() - vector.y(),
            intervalVector.z() - vector.z()
        );
    }

    inline
    const IntervalVector3d
    operator-(
        const IntervalVector3d& firstIntervalVector,
        const IntervalVector3d& secondIntervalVector
    ) {
        return IntervalVector3d(
            firstIntervalVector.x() - secondIntervalVector.x(),
            firstIntervalVector.y() - secondIntervalVector.y(),
            firstIntervalVector.z() - secondIntervalVector.z()
        );
    }

    template <int iNumDimensions>
    inline
    const IntervalVector<iNumDimensions>&
    BoundsFunction<IntervalVector<iNumDimensions>>::operator()(
        const IntervalVector<iNumDimensions>& intervalVector
    ) const {
        return intervalVector;
    }
}
