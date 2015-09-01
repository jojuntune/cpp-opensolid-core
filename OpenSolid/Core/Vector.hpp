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
#include <OpenSolid/Core/Vector/IntervalVectorVertices.hpp>

#include <cstdlib>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumDimensions>
        inline
        const Vector<TScalar, iNumDimensions>&
        VectorCommon<TScalar, iNumDimensions>::derived() const {
            return static_cast<const Vector<TScalar, iNumDimensions>&>(*this);
        }

        template <class TScalar, int iNumDimensions>
        inline
        VectorCommon<TScalar, iNumDimensions>::VectorCommon() {
        }

        template <class TScalar, int iNumDimensions>
        inline
        VectorCommon<TScalar, iNumDimensions>::VectorCommon(TScalar x, TScalar y) :
            CartesianBase<TScalar, iNumDimensions>(x, y) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        VectorCommon<TScalar, iNumDimensions>::VectorCommon(TScalar x, TScalar y, TScalar z) :
            CartesianBase<TScalar, iNumDimensions>(x, y, z) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        VectorCommon<TScalar, iNumDimensions>::VectorCommon(
            const Matrix<TScalar, iNumDimensions, 1>& components
        ) : CartesianBase<TScalar, iNumDimensions>(components) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar
        VectorCommon<TScalar, iNumDimensions>::squaredNorm() const {
            return this->components().cwiseSquared().sum();
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar
        VectorCommon<TScalar, iNumDimensions>::norm() const {
            return opensolid::sqrt(squaredNorm());
        }

        template <class TScalar, int iNumDimensions>
        inline
        bool
        VectorCommon<TScalar, iNumDimensions>::isZero(double precision) const {
            return squaredNorm() <= precision * precision;
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar
        VectorCommon<TScalar, iNumDimensions>::dot(
            const Vector<double, iNumDimensions>& other
        ) const {
            return this->components().cwiseProduct(other.components()).sum();
        }

        template <class TScalar, int iNumDimensions>
        inline
        Interval
        VectorCommon<TScalar, iNumDimensions>::dot(
            const Vector<Interval, iNumDimensions>& other
        ) const {
            return this->components().cwiseProduct(other.components()).sum();
        }

        template <class TScalar, int iNumDimensions> template <class TOtherScalar>
        inline
        Vector<Interval, iNumDimensions>
        VectorCommon<TScalar, iNumDimensions>::hull(
            const Vector<TOtherScalar, iNumDimensions>& other
        ) const {
            return Vector<Interval, iNumDimensions>(
                this->components().cwiseHull(other.components())
            );
        }

        template <class TScalar, int iNumDimensions> template <class TOtherScalar>
        inline
        Vector<Interval, iNumDimensions>
        VectorCommon<TScalar, iNumDimensions>::intersection(
            const Vector<TOtherScalar, iNumDimensions>& other
        ) const {
            return Vector<Interval, iNumDimensions>(
                this->components().cwiseIntersection(other.components())
            );
        }

        template <class TScalar, int iNumDimensions>
        inline
        Vector<TScalar, iNumDimensions>
        VectorCommon<TScalar, iNumDimensions>::ZERO() {
            return Vector<TScalar, iNumDimensions>(Matrix<TScalar, iNumDimensions, 1>::ZERO());
        }

        template <class TScalar, int iNumDimensions>
        inline
        Vector<TScalar, iNumDimensions>
        VectorCommon<TScalar, iNumDimensions>::random() {
            return Vector<TScalar, iNumDimensions>(Matrix<TScalar, iNumDimensions, 1>::random());
        }

        template <int iNumDimensions>
        inline
        const Vector<Interval, iNumDimensions>&
        IntervalVectorCommon<iNumDimensions>::derived() const {
            return static_cast<const Vector<Interval, iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        IntervalVectorCommon<iNumDimensions>::IntervalVectorCommon() {
        }

        template <int iNumDimensions>
        inline
        IntervalVectorCommon<iNumDimensions>::IntervalVectorCommon(Interval x, Interval y) :
            VectorCommon<Interval, iNumDimensions>(x, y) {
        }

        template <int iNumDimensions>
        inline
        IntervalVectorCommon<iNumDimensions>::IntervalVectorCommon(
            Interval x,
            Interval y,
            Interval z
        ) : VectorCommon<Interval, iNumDimensions>(x, y, z) {
        }

        template <int iNumDimensions>
        inline
        IntervalVectorCommon<iNumDimensions>::IntervalVectorCommon(
            const Matrix<Interval, iNumDimensions, 1>& components
        ) : VectorCommon<Interval, iNumDimensions>(components) {
        }

        template <int iNumDimensions>
        inline
        Vector<Interval, iNumDimensions>
        IntervalVectorCommon<iNumDimensions>::normalized() const {
            Interval norm = this->norm();
            if (norm == opensolid::Zero()) {
                assert(false);
                return Vector<Interval, iNumDimensions>(
                    Matrix<Interval, iNumDimensions, 1>::constant(Interval::EMPTY())
                );
            }
            return Vector<Interval, iNumDimensions>((1.0 / norm) * this->components());
        }

        template <int iNumDimensions>
        inline
        bool
        IntervalVectorCommon<iNumDimensions>::isEmpty() const {
            return this->components().any(
                [] (Interval component) -> bool {
                    return component.isEmpty();
                }
            );
        }

        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        IntervalVectorCommon<iNumDimensions>::minVertex() const {
            return Vector<double, iNumDimensions>(this->components().cwiseLowerBound());
        }
        
        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        IntervalVectorCommon<iNumDimensions>::maxVertex() const {
            return Vector<double, iNumDimensions>(this->components().cwiseUpperBound());
        }

        template <>
        inline
        Vector<double, 2>
        IntervalVectorCommon<2>::vertex(int index) const {
            assert(index >= 0 && index < 4);
            return Vector<double, 2>(
                index & 1 ? this->component(0).upperBound() : this->component(0).lowerBound(),
                index & 2 ? this->component(1).upperBound() : this->component(1).lowerBound()
            );
        }

        template <>
        inline
        Vector<double, 3>
        IntervalVectorCommon<3>::vertex(int index) const {
            assert(index >= 0 && index < 8);
            return Vector<double, 3>(
                index & 1 ? this->component(0).upperBound() : this->component(0).lowerBound(),
                index & 2 ? this->component(1).upperBound() : this->component(1).lowerBound(),
                index & 4 ? this->component(2).upperBound() : this->component(2).lowerBound()
            );
        }

        template <int iNumDimensions>
        inline
        IntervalVectorVertices<iNumDimensions>
        IntervalVectorCommon<iNumDimensions>::vertices() const {
            return IntervalVectorVertices<iNumDimensions>(derived());
        }
        
        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        IntervalVectorCommon<iNumDimensions>::centroid() const {
            return Vector<double, iNumDimensions>(this->components().cwiseMedian());
        }
        
        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        IntervalVectorCommon<iNumDimensions>::randomVector() const {
            return Vector<double, iNumDimensions>(
                this->components().map(
                    [] (Interval component) -> double {
                        return component.randomValue();
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        IntervalVectorCommon<iNumDimensions>::diagonalVector() const {
            return Vector<double, iNumDimensions>(this->components().cwiseWidth());
        }

        template <int iNumDimensions>
        inline
        bool
        IntervalVectorCommon<iNumDimensions>::overlaps(
            const Vector<Interval, iNumDimensions>& other,
            double precision
        ) const {
            return this->components().binaryAll(
                other.components(),
                [precision] (Interval component, Interval otherComponent) -> bool {
                    return component.overlaps(otherComponent, precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        bool
        IntervalVectorCommon<iNumDimensions>::strictlyOverlaps(
            const Vector<Interval, iNumDimensions>& other,
            double precision
        ) const {
            return this->components().binaryAll(
                other.components(),
                [precision] (Interval component, Interval otherComponent) -> bool {
                    return component.strictlyOverlaps(otherComponent, precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        bool
        IntervalVectorCommon<iNumDimensions>::contains(
            const Vector<double, iNumDimensions>& other,
            double precision
        ) const {
            return this->components().binaryAll(
                other.components(),
                [precision] (Interval component, double otherComponent) -> bool {
                    return component.contains(otherComponent, precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        bool
        IntervalVectorCommon<iNumDimensions>::strictlyContains(
            const Vector<double, iNumDimensions>& other,
            double precision
        ) const {
            return this->components().binaryAll(
                other.components(),
                [precision] (Interval component, double otherComponent) -> bool {
                    return component.strictlyContains(otherComponent, precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        bool
        IntervalVectorCommon<iNumDimensions>::contains(
            const Vector<Interval, iNumDimensions>& other,
            double precision
        ) const {
            return this->components().binaryAll(
                other.components(),
                [precision] (Interval component, Interval otherComponent) -> bool {
                    return component.contains(otherComponent, precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        bool
        IntervalVectorCommon<iNumDimensions>::strictlyContains(
            const Vector<Interval, iNumDimensions>& other,
            double precision
        ) const {
            return this->components().binaryAll(
                other.components(),
                [precision] (Interval component, Interval otherComponent) -> bool {
                    return component.strictlyContains(otherComponent, precision);
                }
            );
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorCommon<iNumDimensions>::operator*=(double scale) {
            this->components() *= scale;
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorCommon<iNumDimensions>::operator*=(Interval scale) {
            this->components() *= scale;
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorCommon<iNumDimensions>::operator/=(double divisor) {
            this->components() /= divisor;
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorCommon<iNumDimensions>::operator/=(Interval divisor) {
            this->components() /= divisor;
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorCommon<iNumDimensions>::operator+=(
            const Vector<double, iNumDimensions>& other
        ) {
            this->components() += other.components();
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorCommon<iNumDimensions>::operator+=(
            const Vector<Interval, iNumDimensions>& other
        ) {
            this->components() += other.components();
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorCommon<iNumDimensions>::operator-=(
            const Vector<double, iNumDimensions>& other
        ) {
            this->components() -= other.components();
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorCommon<iNumDimensions>::operator-=(
            const Vector<Interval, iNumDimensions>& other
        ) {
            this->components() -= other.components();
        }
    }

    inline
    Vector2d::Vector() {
    }

    inline
    Vector2d::Vector(double x, double y) :
        detail::VectorCommon<double, 2>(x, y) {
    }

    inline
    Vector2d::Vector(const ColumnMatrix2d& components) :
        detail::VectorCommon<double, 2>(components) {
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
        detail::VectorCommon<double, 3>(x, y, z) {
    }

    inline
    Vector3d::Vector(const ColumnMatrix3d& components) :
        detail::VectorCommon<double, 3>(components) {
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
        detail::IntervalVectorCommon<2>() {
    }

    inline
    IntervalVector2d::Vector(Interval x, Interval y) :
        detail::IntervalVectorCommon<2>(x, y) {
    }

    inline
    IntervalVector2d::Vector(const IntervalColumnMatrix2d& components) :
        detail::IntervalVectorCommon<2>(components) {
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
        detail::IntervalVectorCommon<3>() {
    }

    inline
    IntervalVector3d::Vector(Interval x, Interval y, Interval z) :
        detail::IntervalVectorCommon<3>(x, y, z) {
    }

    inline
    IntervalVector3d::Vector(const IntervalColumnMatrix3d& components) :
        detail::IntervalVectorCommon<3>(components) {
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
