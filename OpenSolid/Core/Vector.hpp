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
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector/DoubleVectorBase.hpp>
#include <OpenSolid/Core/Vector/IntervalVectorBase.hpp>

#include <cstdlib>

namespace opensolid
{
    inline
    Vector1d::Vector() :
        detail::DoubleVectorBase<1>() {
    }

    inline
    Vector1d::Vector(double value) :
        detail::DoubleVectorBase<1>(value) {
    }

    inline
    Vector1d::Vector(const Matrix1d& components) :
        detail::DoubleVectorBase<1>(components) {
    }

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
    const UnitVector2d
    Vector2d::unitOrthogonal() const {
        if (isZero()) {
            assert(false);
            return UnitVector2d();
        } else {
            return Vector2d(-y(), x()).normalized();
        }
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
    Vector3d::cross(const IntervalVector3d& other) const {
        return IntervalVector3d(
            y() * other.z() - z() * other.y(),
            z() * other.x() - x() * other.z(),
            x() * other.y() - y() * other.x()
        );
    }

    inline
    const UnitVector3d
    Vector3d::unitOrthogonal() const {
        if (isZero()) {
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
    IntervalVector1d::Vector() :
        detail::IntervalVectorBase<1>() {
    }

    inline
    IntervalVector1d::Vector(Interval value) :
        detail::IntervalVectorBase<1>(value) {
    }

    inline
    IntervalVector1d::Vector(const IntervalMatrix1d& components) :
        detail::IntervalVectorBase<1>(components) {
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

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    const Vector<decltype(TFirstScalar() * TSecondScalar()), iNumDimensions>
    operator*(TFirstScalar scale, const Vector<TSecondScalar, iNumDimensions>& vector) {
        typedef decltype(TFirstScalar() * TSecondScalar()) ResultScalarType;
        return Vector<ResultScalarType, iNumDimensions>(
            vector.components().map(
                [scale] (TSecondScalar component) -> ResultScalarType {
                    return scale * component;
                }
            )
        );
    }

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    const Vector<decltype(TFirstScalar() * TSecondScalar()), iNumDimensions>
    operator*(const Vector<TFirstScalar, iNumDimensions>& vector, TSecondScalar scale) {
        typedef decltype(TFirstScalar() * TSecondScalar()) ResultScalarType;
        return Vector<ResultScalarType, iNumDimensions>(
            vector.components().map(
                [scale] (TFirstScalar component) -> ResultScalarType {
                    return component * scale;
                }
            )
        );
    }

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    const Vector<decltype(TFirstScalar() / TSecondScalar()), iNumDimensions>
    operator/(const Vector<TFirstScalar, iNumDimensions>& vector, TSecondScalar divisor) {
        typedef decltype(TFirstScalar() / TSecondScalar()) ResultScalarType;
        return Vector<ResultScalarType, iNumDimensions>(
            vector.components().map(
                [divisor] (TFirstScalar component) -> ResultScalarType {
                    return component / divisor;
                }
            )
        );
    }

    template <class TScalar, int iNumDimensions>
    const Vector<TScalar, iNumDimensions>
    operator-(const Vector<TScalar, iNumDimensions>& vector) {
        return Vector<TScalar, iNumDimensions>(
            vector.components().map(
                [] (TScalar component) -> TScalar {
                    return -component;
                }
            )
        );
    }

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    const Vector<decltype(TFirstScalar() + TSecondScalar()), iNumDimensions>
    operator+(
        const Vector<TFirstScalar, iNumDimensions>& firstVector,
        const Vector<TSecondScalar, iNumDimensions>& secondVector
    ) {
        typedef decltype(TFirstScalar() + TSecondScalar()) ResultScalarType;
        return Vector<ResultScalarType, iNumDimensions>(
            firstVector.components().binaryMap(
                secondVector.components(),
                [] (
                    TFirstScalar firstComponent,
                    TSecondScalar secondComponent
                ) -> ResultScalarType {
                    return firstComponent + secondComponent;
                }
            )
        );
    }

    template <class TFirstScalar, class TSecondScalar, int iNumDimensions>
    const Vector<decltype(TFirstScalar() - TSecondScalar()), iNumDimensions>
    operator-(
        const Vector<TFirstScalar, iNumDimensions>& firstVector,
        const Vector<TSecondScalar, iNumDimensions>& secondVector
    ) {
        typedef decltype(TFirstScalar() - TSecondScalar()) ResultScalarType;
        return Vector<ResultScalarType, iNumDimensions>(
            firstVector.components().binaryMap(
                secondVector.components(),
                [] (
                    TFirstScalar firstComponent,
                    TSecondScalar secondComponent
                ) -> ResultScalarType {
                    return firstComponent - secondComponent;
                }
            )
        );
    }

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Vector<double, iNumDimensions>& vector) {
        stream << "Vector" << iNumDimensions << "d";
        stream << "(";
        for (int index = 0; index < iNumDimensions; ++index) {
            stream << vector.component(index);
            if (index < iNumDimensions - 1) {
                stream << ",";
            }
        }
        stream << ")";
        return stream;
    }

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Vector<Interval, iNumDimensions>& vector) {
        stream << "IntervalVector" << iNumDimensions << "d";
        stream << "(";
        for (int index = 0; index < iNumDimensions; ++index) {
            stream << vector.component(index);
            if (index < iNumDimensions - 1) {
                stream << ",";
            }
        }
        stream << ")";
        return stream;
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
    const Vector<Interval, iNumDimensions>
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

    template <class TScalar, int iNumDimensions>
    inline
    const Vector<TScalar, iNumDimensions>
    ScalingFunction<Vector<TScalar, iNumDimensions>>::operator()(
        const Vector<TScalar, iNumDimensions>& vector,
        double scale
    ) const {
        return scale * vector;
    }

    template <class TScalar, int iNumDimensions>
    inline
    const Vector<TScalar, iNumDimensions>&
    TranslationFunction<Vector<TScalar, iNumDimensions>>::operator()(
        const Vector<TScalar, iNumDimensions>& vector,
        const Vector<double, iNumDimensions>& translationVector
    ) const {
        return vector;
    }

    template <class TScalar, int iNumDimensions, int iNumResultDimensions>
    inline
    const Vector<TScalar, iNumResultDimensions>
    TransformationFunction<Vector<TScalar, iNumDimensions>, iNumResultDimensions>::operator()(
        const Vector<TScalar, iNumDimensions>& vector,
        const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix
    ) const {
        return Vector<TScalar, iNumResultDimensions>(matrix * vector.components());
    }
}
