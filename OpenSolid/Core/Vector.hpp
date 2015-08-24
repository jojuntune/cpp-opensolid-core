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

#include <OpenSolid/Core/Vector.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/Cartesian/CartesianBase.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector/IntervalVectorBase.hpp>
#include <OpenSolid/Core/Vector/VectorBase.hpp>

#include <cstdlib>

namespace opensolid
{
    inline
    Vector2d::Vector() {
    }

    inline
    Vector2d::Vector(double x, double y) :
        detail::VectorBase<double, 2>(x, y) {
    }

    inline
    Vector2d::Vector(const ColumnMatrix2d& components) :
        detail::VectorBase<double, 2>(components) {
    }

    inline
    bool
    Vector2d::operator==(const Vector2d& other) const {
        return x() == other.x() && y() == other.y();
    }

    inline
    bool
    Vector2d::operator!=(const Vector2d& other) const {
        return x() != other.x() || y() != other.y();
    }

    inline
    bool
    Vector2d::equals(const Vector2d& other, double precision) const {
        return (*this - other).isZero(precision);
    }

    inline
    IntervalVector2d
    Vector2d::bounds() const {
        return IntervalVector2d(
            this->components().map(
                [] (double component) {
                    return Interval(component);
                }
            )
        );
    }

    inline
    UnitVector2d
    Vector2d::normalized() const {
        double norm = this->norm();
        if (norm == 0.0) {
            return UnitVector2d();
        } else {
            return UnitVector2d(components() / norm);
        }
    }

    inline
    UnitVector2d
    Vector2d::unitOrthogonal() const {
        return Vector2d(-y(), x()).normalized();
    }

    template <class TTransformation>
    inline
    Vector2d
    Vector2d::transformedBy(const TTransformation& transformation) const {
        return transformation.transform(*this);
    }

    inline
    Vector2d
    Vector2d::projectedOnto(const Axis2d& axis) const {
        return dot(axis.directionVector()) * axis.directionVector();
    }

    inline
    Vector3d
    Vector2d::placedOnto(const Plane3d& plane) const {
        return x() * plane.xDirectionVector() + y() * plane.yDirectionVector();
    }

    inline
    Vector2d
    Vector2d::ZERO() {
        return Vector2d(0.0, 0.0);
    }

    inline
    Vector3d::Vector() {
    }

    inline
    Vector3d::Vector(double x, double y, double z) :
        detail::VectorBase<double, 3>(x, y, z) {
    }

    inline
    Vector3d::Vector(const ColumnMatrix3d& components) :
        detail::VectorBase<double, 3>(components) {
    }

    inline
    bool
    Vector3d::operator==(const Vector3d& other) const {
        return x() == other.x() && y() == other.y() && z() == other.z();
    }

    inline
    bool
    Vector3d::operator!=(const Vector3d& other) const {
        return x() != other.x() || y() != other.y() || z() != other.z();
    }

    inline
    bool
    Vector3d::equals(const Vector3d& other, double precision) const {
        return (*this - other).isZero(precision);
    }

    inline
    IntervalVector3d
    Vector3d::bounds() const {
        return IntervalVector3d(
            this->components().map(
                [] (double component) {
                    return Interval(component);
                }
            )
        );
    }

    inline
    Vector3d
    Vector3d::cross(const Vector3d& other) const {
        return Vector3d(
            y() * other.z() - z() * other.y(),
            z() * other.x() - x() * other.z(),
            x() * other.y() - y() * other.x()
        );
    }

    inline
    IntervalVector3d
    Vector3d::cross(const IntervalVector3d& other) const {
        return IntervalVector3d(
            y() * other.z() - z() * other.y(),
            z() * other.x() - x() * other.z(),
            x() * other.y() - y() * other.x()
        );
    }

    inline
    UnitVector3d
    Vector3d::normalized() const {
        double norm = this->norm();
        if (norm == 0.0) {
            return UnitVector3d();
        } else {
            return UnitVector3d(components() / norm);
        }
    }

    template <class TTransformation>
    inline
    Vector3d
    Vector3d::transformedBy(const TTransformation& transformation) const {
        return transformation.transform(*this);
    }

    inline
    Vector3d
    Vector3d::projectedOnto(const Axis3d& axis) const {
        return dot(axis.directionVector()) * axis.directionVector();
    }

    inline
    Vector3d
    Vector3d::projectedOnto(const Plane3d& plane) const {
        return *this - this->dot(plane.normalVector()) * plane.normalVector();
    }

    inline
    Vector2d
    Vector3d::projectedInto(const Plane3d& plane) const {
        return Vector2d(dot(plane.xDirectionVector()), dot(plane.yDirectionVector()));
    }

    inline
    Vector3d
    Vector3d::ZERO() {
        return Vector3d(0.0, 0.0, 0.0);
    }

    inline
    IntervalVector2d::Vector() :
        detail::IntervalVectorBase<2>() {
    }

    inline
    IntervalVector2d::Vector(Interval x, Interval y) :
        detail::IntervalVectorBase<2>(x, y) {
    }

    inline
    IntervalVector2d::Vector(const IntervalColumnMatrix2d& components) :
        detail::IntervalVectorBase<2>(components) {
    }

    inline
    bool
    IntervalVector2d::operator==(const IntervalVector2d& other) const {
        return x() == other.x() && y() == other.y();
    }

    inline
    bool
    IntervalVector2d::operator!=(const IntervalVector2d& other) const {
        return x() != other.x() || y() != other.y();
    }

    inline
    const IntervalVector2d&
    IntervalVector2d::bounds() const {
        return *this;
    }

    inline
    IntervalVector2d
    IntervalVector2d::WHOLE() {
        return IntervalVector2d(Interval::WHOLE(), Interval::WHOLE());
    }

    inline
    IntervalVector2d
    IntervalVector2d::EMPTY() {
        return IntervalVector2d(Interval::EMPTY(), Interval::EMPTY());
    }

    inline
    IntervalVector2d
    IntervalVector2d::UNIT() {
        return IntervalVector2d(Interval::UNIT(), Interval::UNIT());
    }

    inline
    IntervalVector3d::Vector() :
        detail::IntervalVectorBase<3>() {
    }

    inline
    IntervalVector3d::Vector(Interval x, Interval y, Interval z) :
        detail::IntervalVectorBase<3>(x, y, z) {
    }

    inline
    IntervalVector3d::Vector(const IntervalColumnMatrix3d& components) :
        detail::IntervalVectorBase<3>(components) {
    }

    inline
    bool
    IntervalVector3d::operator==(const IntervalVector3d& other) const {
        return x() == other.x() && y() == other.y() && z() == other.z();
    }

    inline
    bool
    IntervalVector3d::operator!=(const IntervalVector3d& other) const {
        return x() != other.x() || y() != other.y() || z() != other.z();
    }

    inline
    const IntervalVector3d&
    IntervalVector3d::bounds() const {
        return *this;
    }

    inline
    IntervalVector3d
    IntervalVector3d::cross(const Vector3d& vector) const {
        return IntervalVector3d(
            y() * vector.z() - z() * vector.y(),
            z() * vector.x() - x() * vector.z(),
            x() * vector.y() - y() * vector.x()
        );
    }

    inline
    IntervalVector3d
    IntervalVector3d::cross(const IntervalVector3d& other) const {
        return IntervalVector3d(
            y() * other.z() - z() * other.y(),
            z() * other.x() - x() * other.z(),
            x() * other.y() - y() * other.x()
        );
    }

    inline
    IntervalVector3d
    IntervalVector3d::WHOLE() {
        return IntervalVector3d(Interval::WHOLE(), Interval::WHOLE(), Interval::WHOLE());
    }

    inline
    IntervalVector3d
    IntervalVector3d::EMPTY() {
        return IntervalVector3d(Interval::EMPTY(), Interval::EMPTY(), Interval::EMPTY());
    }

    inline
    IntervalVector3d
    IntervalVector3d::UNIT() {
        return IntervalVector3d(Interval::UNIT(), Interval::UNIT(), Interval::UNIT());
    }

    template <class TScalar, int iNumDimensions>
    Vector<TScalar, iNumDimensions>
    operator*(double scale, const Vector<TScalar, iNumDimensions>& vector) {
        return Vector<TScalar, iNumDimensions>(scale * vector.components());
    }

    template <class TScalar, int iNumDimensions>
    Vector<Interval, iNumDimensions>
    operator*(Interval scale, const Vector<TScalar, iNumDimensions>& vector) {
        return Vector<Interval, iNumDimensions>(scale * vector.components());
    }

    template <class TScalar, int iNumDimensions>
    Vector<TScalar, iNumDimensions>
    operator*(const Vector<TScalar, iNumDimensions>& vector, double scale) {
        return Vector<TScalar, iNumDimensions>(vector.components() * scale);
    }

    template <class TScalar, int iNumDimensions>
    Vector<Interval, iNumDimensions>
    operator*(const Vector<TScalar, iNumDimensions>& vector, Interval scale) {
        return Vector<Interval, iNumDimensions>(vector.components() * scale);
    }

    template <class TScalar, int iNumDimensions>
    Vector<TScalar, iNumDimensions>
    operator/(const Vector<TScalar, iNumDimensions>& vector, double divisor) {
        return Vector<TScalar, iNumDimensions>(vector.components() / divisor);
    }

    template <class TScalar, int iNumDimensions>
    Vector<Interval, iNumDimensions>
    operator/(const Vector<TScalar, iNumDimensions>& vector, Interval divisor) {
        return Vector<Interval, iNumDimensions>(vector.components() / divisor);
    }

    template <class TScalar, int iNumDimensions>
    Vector<TScalar, iNumDimensions>
    operator-(const Vector<TScalar, iNumDimensions>& vector) {
        return Vector<TScalar, iNumDimensions>(-vector.components());
    }

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    Vector<decltype(TFirstScalar() + TSecondScalar()), iNumDimensions>
    operator+(
        const Vector<TFirstScalar, iNumDimensions>& firstVector,
        const Vector<TSecondScalar, iNumDimensions>& secondVector
    ) {
        return Vector<decltype(TFirstScalar() + TSecondScalar()), iNumDimensions>(
            firstVector.components() + secondVector.components()
        );
    }

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    Vector<decltype(TFirstScalar() - TSecondScalar()), iNumDimensions>
    operator-(
        const Vector<TFirstScalar, iNumDimensions>& firstVector,
        const Vector<TSecondScalar, iNumDimensions>& secondVector
    ) {
        return Vector<decltype(TFirstScalar() - TSecondScalar()), iNumDimensions>(
            firstVector.components() - secondVector.components()
        );
    }

    template <int iNumDimensions>
    inline
    bool
    EqualityFunction<Vector<double, iNumDimensions>>::operator()(
        const Vector<double, iNumDimensions>& firstVector,
        const Vector<double, iNumDimensions>& secondVector,
        double precision
    ) const {
        return (firstVector - secondVector).isZero(precision);
    }
}
