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

#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/Cartesian/CartesianBase.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Frame.definitions.hpp>
#include <OpenSolid/Core/Quaternion.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector/DoubleVectorBase.hpp>
#include <OpenSolid/Core/Vector/IntervalVectorBase.hpp>

#include <cstdlib>

namespace opensolid
{
    inline
    Vector2d::Vector() :
        detail::DoubleVectorBase<2>() {
    }

    inline
    Vector2d::Vector(double x, double y) :
        detail::DoubleVectorBase<2>(x, y) {
    }

    inline
    Vector2d::Vector(const ColumnMatrix2d& components) :
        detail::DoubleVectorBase<2>(components) {
    }

    inline
    UnitVector2d
    Vector2d::unitOrthogonal() const {
        if (isZero()) {
            assert(false);
            return UnitVector2d();
        } else {
            return Vector2d(-y(), x()).normalized();
        }
    }

    inline
    Vector2d
    Vector2d::rotatedBy(double angle) const {
        return rotatedBy(Quaternion2d(angle).rotationMatrix());
    }

    inline
    Vector3d
    Vector2d::toGlobalFrom(const Plane3d& plane) const {
        return Vector3d(plane.basisMatrix() * components());
    }

    inline
    UnitVector2d
    Vector2d::unit(int index) {
        switch (index) {
            case 0: return UnitVector2d(1.0, 0.0);
            case 1: return UnitVector2d(0.0, 1.0);
            default: throw Error(new PlaceholderError());
        }
    }

    inline
    UnitVector2d
    Vector2d::unitX() {
        return UnitVector2d(1.0, 0.0);
    }

    inline
    UnitVector2d
    Vector2d::unitY() {
        return UnitVector2d(0.0, 1.0);
    }

    inline
    Vector3d::Vector() :
        detail::DoubleVectorBase<3>() {
    }

    inline
    Vector3d::Vector(double x, double y, double z) :
        detail::DoubleVectorBase<3>(x, y, z) {
    }

    inline
    Vector3d::Vector(const ColumnMatrix3d& components) :
        detail::DoubleVectorBase<3>(components) {
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
    Vector3d
    Vector3d::rotatedAbout(const UnitVector3d& directionVector, double angle) const {
        return rotatedBy(Quaternion3d(directionVector, angle).rotationMatrix());
    }

    inline
    Vector2d
    Vector3d::toLocalIn(const Plane3d& plane) const {
        return Vector2d(plane.basisMatrix().transposeProduct(components()));
    }

    inline
    Vector3d
    Vector3d::projectedOnto(const Plane3d& plane) const {
        return *this - this->dot(plane.normalVector()) * plane.normalVector();
    }

    inline
    UnitVector3d
    Vector3d::unit(int index) {
        switch (index) {
            case 0: return UnitVector3d(1.0, 0.0, 0.0);
            case 1: return UnitVector3d(0.0, 1.0, 0.0);
            case 2: return UnitVector3d(0.0, 0.0, 1.0);
            default: throw Error(new PlaceholderError());
        }
    }

    inline
    UnitVector3d
    Vector3d::unitX() {
        return UnitVector3d(1.0, 0.0, 0.0);
    }

    inline
    UnitVector3d
    Vector3d::unitY() {
        return UnitVector3d(0.0, 1.0, 0.0);
    }

    inline
    UnitVector3d
    Vector3d::unitZ() {
        return UnitVector3d(0.0, 0.0, 1.0);
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

    template <int iNumDimensions>
    inline
    Vector<Interval, iNumDimensions>
    BoundsFunction<Vector<double, iNumDimensions>>::operator()(
        const Vector<double, iNumDimensions>& vector
    ) const {
        return Vector<Interval, iNumDimensions>(
            vector.components().map(
                [] (double component) {
                    return Interval(component);
                }
            )
        );
    }

    template <int iNumDimensions>
    inline
    const Vector<Interval, iNumDimensions>&
    BoundsFunction<Vector<Interval, iNumDimensions>>::operator()(
        const Vector<Interval, iNumDimensions>& vector
    ) const {
        return vector;
    }
}
