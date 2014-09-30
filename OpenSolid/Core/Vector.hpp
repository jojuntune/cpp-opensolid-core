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
    const UnitVector1d
    Vector1d::unit(int index) {
        if (index == 0) {
            return UnitVector1d(1.0);
        } else {
            throw Error(new PlaceholderError());
        }
    }

    inline
    const UnitVector1d
    Vector1d::unitX() {
        return UnitVector1d(1.0);
    }

    inline
    const UnitVector1d
    Vector1d::unitRandom() {
        return UnitVector1d(rand() > RAND_MAX / 2 ? 1.0 : -1.0);
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
    const UnitVector2d
    Vector2d::unit(int index) {
        switch (index) {
            case 0: return UnitVector2d(1.0, 0.0);
            case 1: return UnitVector2d(0.0, 1.0);
            default: throw Error(new PlaceholderError());
        }
    }

    inline
    const UnitVector2d
    Vector2d::unitX() {
        return UnitVector2d(1.0, 0.0);
    }

    inline
    const UnitVector2d
    Vector2d::unitY() {
        return UnitVector2d(0.0, 1.0);
    }

    inline
    const UnitVector2d
    Vector2d::unitRandom() {
        while (true) {
            Vector2d candidate(
                -1.0 + 2.0 * double(rand()) / RAND_MAX,
                -1.0 + 2.0 * double(rand()) / RAND_MAX
            );
            double candidateSquaredNorm = candidate.squaredNorm();
            if (candidateSquaredNorm >= 0.25 && candidateSquaredNorm <= 1.0) {
                return UnitVector2d((candidate / sqrt(candidateSquaredNorm)).components());
            }
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
            double absX = abs(x());
            double absY = abs(y());
            double absZ = abs(z());
            if (absX <= absY) {
                if (absX <= absZ) {
                    return Vector3d::unitX().cross(*this).normalized();
                } else {
                    return Vector3d::unitZ().cross(*this).normalized();
                }
            } else {
                if (absY <= absZ) {
                    return Vector3d::unitY().cross(*this).normalized();
                } else {
                    return Vector3d::unitZ().cross(*this).normalized();
                }
            }
        }
    }

    inline
    const UnitVector3d
    Vector3d::unit(int index) {
        switch (index) {
            case 0: return UnitVector3d(1.0, 0.0, 0.0);
            case 1: return UnitVector3d(0.0, 1.0, 0.0);
            case 2: return UnitVector3d(0.0, 0.0, 1.0);
            default: throw Error(new PlaceholderError());
        }
    }

    inline
    const UnitVector3d
    Vector3d::unitX() {
        return UnitVector3d(1.0, 0.0, 0.0);
    }

    inline
    const UnitVector3d
    Vector3d::unitY() {
        return UnitVector3d(0.0, 1.0, 0.0);
    }

    inline
    const UnitVector3d
    Vector3d::unitZ() {
        return UnitVector3d(0.0, 0.0, 1.0);
    }

    inline
    const UnitVector3d
    Vector3d::unitRandom() {
        while (true) {
            Vector3d candidate(
                -1.0 + 2.0 * double(rand()) / RAND_MAX,
                -1.0 + 2.0 * double(rand()) / RAND_MAX,
                -1.0 + 2.0 * double(rand()) / RAND_MAX
            );
            double candidateSquaredNorm = candidate.squaredNorm();
            if (candidateSquaredNorm >= 0.25 && candidateSquaredNorm <= 1.0) {
                return UnitVector3d((candidate / sqrt(candidateSquaredNorm)).components());
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

    template <class TScalar, int iNumDimensions>
    const Vector<TScalar, iNumDimensions>
    operator*(double scale, const Vector<TScalar, iNumDimensions>& vector) {
        return Vector<TScalar, iNumDimensions>(
            vector.components().map(
                [scale] (TScalar component) -> TScalar {
                    return scale * component;
                }
            )
        );
    }

    template <class TScalar, int iNumDimensions>
    const Vector<Interval, iNumDimensions>
    operator*(Interval scale, const Vector<TScalar, iNumDimensions>& vector) {
        return Vector<Interval, iNumDimensions>(
            vector.components().map(
                [scale] (TScalar component) -> Interval {
                    return scale * component;
                }
            )
        );
    }

    template <class TScalar, int iNumDimensions>
    const Vector<TScalar, iNumDimensions>
    operator*(const Vector<TScalar, iNumDimensions>& vector, double scale) {
        return Vector<TScalar, iNumDimensions>(
            vector.components().map(
                [scale] (TScalar component) -> TScalar {
                    return component * scale;
                }
            )
        );
    }

    template <class TScalar, int iNumDimensions>
    const Vector<Interval, iNumDimensions>
    operator*(const Vector<TScalar, iNumDimensions>& vector, Interval scale) {
        return Vector<Interval, iNumDimensions>(
            vector.components().map(
                [scale] (TScalar component) -> Interval {
                    return component * scale;
                }
            )
        );
    }

    template <class TScalar, int iNumDimensions>
    const Vector<TScalar, iNumDimensions>
    operator/(const Vector<TScalar, iNumDimensions>& vector, double divisor) {
        return Vector<TScalar, iNumDimensions>(
            vector.components().map(
                [divisor] (TScalar component) -> TScalar {
                    return component / divisor;
                }
            )
        );
    }

    template <class TScalar, int iNumDimensions>
    const Vector<Interval, iNumDimensions>
    operator/(const Vector<TScalar, iNumDimensions>& vector, Interval divisor) {
        return Vector<Interval, iNumDimensions>(
            vector.components().map(
                [divisor] (TScalar component) -> Interval {
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
        const Point<iNumDimensions>& originPoint,
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
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumResultDimensions, iNumDimensions>& transformationMatrix,
        const Point<iNumResultDimensions>& destinationPoint
    ) const {
        return Vector<TScalar, iNumResultDimensions>(transformationMatrix * vector.components());
    }
}
