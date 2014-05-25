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

#include <OpenSolid/Core/Vector/IntervalVectorBase.definitions.hpp>

#include <OpenSolid/Core/Vector.definitions.hpp>
#include <OpenSolid/Core/Vector/IntervalVectorVertices.hpp>
#include <OpenSolid/Core/Vector/VectorBase.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        const Vector<Interval, iNumDimensions>&
        IntervalVectorBase<iNumDimensions>::derived() const {
            return static_cast<const Vector<Interval, iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        IntervalVectorBase<iNumDimensions>::IntervalVectorBase() {
        }

        template <int iNumDimensions>
        inline
        IntervalVectorBase<iNumDimensions>::IntervalVectorBase(Interval value) :
            VectorBase<Interval, iNumDimensions>(value) {
        }

        template <int iNumDimensions>
        inline
        IntervalVectorBase<iNumDimensions>::IntervalVectorBase(Interval x, Interval y) :
            VectorBase<Interval, iNumDimensions>(x, y) {
        }

        template <int iNumDimensions>
        inline
        IntervalVectorBase<iNumDimensions>::IntervalVectorBase(Interval x, Interval y, Interval z) :
            VectorBase<Interval, iNumDimensions>(x, y, z) {
        }

        template <int iNumDimensions>
        inline
        IntervalVectorBase<iNumDimensions>::IntervalVectorBase(
            const Matrix<Interval, iNumDimensions, 1>& components
        ) : VectorBase<Interval, iNumDimensions>(components) {
        }

        template <int iNumDimensions>
        inline
        IntervalVectorBase<iNumDimensions>::IntervalVectorBase(const Interval* sourcePtr) :
            VectorBase<Interval, iNumDimensions>(sourcePtr) {
        }

        template <int iNumDimensions>
        inline
        const Vector<Interval, iNumDimensions>
        IntervalVectorBase<iNumDimensions>::normalized() const {
            Interval norm = this->norm();
            if (norm == opensolid::Zero()) {
                assert(false);
                return Vector<Interval, iNumDimensions>(
                    Matrix<Interval, iNumDimensions, 1>::constant(Interval::Empty())
                );
            }
            return Vector<Interval, iNumDimensions>((1.0 / norm) * this->components());
        }

        template <int iNumDimensions>
        inline
        bool
        IntervalVectorBase<iNumDimensions>::isEmpty() const {
            return this->components().any(
                [] (Interval component) -> bool {
                    return component.isEmpty();
                }
            );
        }

        template <int iNumDimensions>
        inline
        const Vector<double, iNumDimensions>
        IntervalVectorBase<iNumDimensions>::minVertex() const {
            return Vector<double, iNumDimensions>(this->components().cwiseLowerBound());
        }
        
        template <int iNumDimensions>
        inline
        const Vector<double, iNumDimensions>
        IntervalVectorBase<iNumDimensions>::maxVertex() const {
            return Vector<double, iNumDimensions>(this->components().cwiseUpperBound());
        }

        template <>
        inline
        const Vector<double, 1>
        IntervalVectorBase<1>::vertex(int index) const {
            assert(index >= 0 && index < 2);
            return Vector<double, 1>(
                index == 0 ? this->value().lowerBound() : this->value().upperBound()
            );
        }

        template <>
        inline
        const Vector<double, 2>
        IntervalVectorBase<2>::vertex(int index) const {
            assert(index >= 0 && index < 4);
            return Vector<double, 2>(
                index & 1 ? this->component(0).upperBound() : this->component(0).lowerBound(),
                index & 2 ? this->component(1).upperBound() : this->component(1).lowerBound()
            );
        }

        template <>
        inline
        const Vector<double, 3>
        IntervalVectorBase<3>::vertex(int index) const {
            assert(index >= 0 && index < 8);
            return Vector<double, 3>(
                index & 1 ? this->component(0).upperBound() : this->component(0).lowerBound(),
                index & 2 ? this->component(1).upperBound() : this->component(1).lowerBound(),
                index & 4 ? this->component(2).upperBound() : this->component(2).lowerBound()
            );
        }

        template <int iNumDimensions>
        inline
        const IntervalVectorVertices<iNumDimensions>
        IntervalVectorBase<iNumDimensions>::vertices() const {
            return IntervalVectorVertices<iNumDimensions>(derived());
        }
        
        template <int iNumDimensions>
        inline
        const Vector<double, iNumDimensions>
        IntervalVectorBase<iNumDimensions>::centroid() const {
            return Vector<double, iNumDimensions>(this->components().cwiseMedian());
        }
        
        template <int iNumDimensions>
        inline
        const Vector<double, iNumDimensions>
        IntervalVectorBase<iNumDimensions>::randomVector() const {
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
        const Vector<double, iNumDimensions>
        IntervalVectorBase<iNumDimensions>::diagonalVector() const {
            return Vector<double, iNumDimensions>(this->components().cwiseWidth());
        }

        template <int iNumDimensions>
        inline
        bool
        IntervalVectorBase<iNumDimensions>::overlaps(
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
        IntervalVectorBase<iNumDimensions>::strictlyOverlaps(
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
        IntervalVectorBase<iNumDimensions>::contains(
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
        IntervalVectorBase<iNumDimensions>::strictlyContains(
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
        IntervalVectorBase<iNumDimensions>::contains(
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
        IntervalVectorBase<iNumDimensions>::strictlyContains(
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
        IntervalVectorBase<iNumDimensions>::operator*=(double scale) {
            this->components() *= scale;
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorBase<iNumDimensions>::operator*=(Interval scale) {
            this->components() *= scale;
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorBase<iNumDimensions>::operator/=(double divisor) {
            this->components() /= divisor;
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorBase<iNumDimensions>::operator/=(Interval divisor) {
            this->components() /= divisor;
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorBase<iNumDimensions>::operator+=(
            const Vector<double, iNumDimensions>& other
        ) {
            this->components() += other.components();
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorBase<iNumDimensions>::operator+=(
            const Vector<Interval, iNumDimensions>& other
        ) {
            this->components() += other.components();
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorBase<iNumDimensions>::operator-=(
            const Vector<double, iNumDimensions>& other
        ) {
            this->components() -= other.components();
        }

        template <int iNumDimensions>
        inline
        void
        IntervalVectorBase<iNumDimensions>::operator-=(
            const Vector<Interval, iNumDimensions>& other
        ) {
            this->components() -= other.components();
        }

        template <int iNumDimensions>
        inline
        const Vector<Interval, iNumDimensions>
        IntervalVectorBase<iNumDimensions>::Unit() {
            return Vector<Interval, iNumDimensions>(
                Matrix<Interval, iNumDimensions, 1>::Constant(Interval::Unit())
            );
        }

        template <int iNumDimensions>
        inline
        const Vector<Interval, iNumDimensions>
        IntervalVectorBase<iNumDimensions>::Empty() {
            return Vector<Interval, iNumDimensions>(
                Matrix<Interval, iNumDimensions, 1>::Constant(Interval::Empty())
            );
        }

        template <int iNumDimensions>
        inline
        const Vector<Interval, iNumDimensions>
        IntervalVectorBase<iNumDimensions>::Whole() {
            return Vector<Interval, iNumDimensions>(
                Matrix<Interval, iNumDimensions, 1>::Constant(Interval::Whole())
            );
        }
    }
}
