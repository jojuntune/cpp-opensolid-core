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

#include <OpenSolid/Core/Vector/DoubleVectorBase.declarations.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/UnitVector.definitions.hpp>
#include <OpenSolid/Core/Vector.definitions.hpp>
#include <OpenSolid/Core/Vector/VectorBase.hpp>

#include <limits>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        const Vector<double, iNumDimensions>&
        DoubleVectorBase<iNumDimensions>::derived() const {
            return static_cast<const Vector<double, iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        DoubleVectorBase<iNumDimensions>::DoubleVectorBase() {
        }

        template <int iNumDimensions>
        inline
        DoubleVectorBase<iNumDimensions>::DoubleVectorBase(double x, double y) :
            VectorBase<double, iNumDimensions>(x, y) {
        }

        template <int iNumDimensions>
        inline
        DoubleVectorBase<iNumDimensions>::DoubleVectorBase(double x, double y, double z) :
            VectorBase<double, iNumDimensions>(x, y, z) {
        }

        template <int iNumDimensions>
        inline
        DoubleVectorBase<iNumDimensions>::DoubleVectorBase(
            const Matrix<double, iNumDimensions, 1>& components
        ) : VectorBase<double, iNumDimensions>(components) {
        }

        template <int iNumDimensions>
        inline
        UnitVector<iNumDimensions>
        DoubleVectorBase<iNumDimensions>::normalized() const {
            double norm = this->norm();
            if (norm == opensolid::Zero()) {
                assert(false);
                return UnitVector<iNumDimensions>();
            }
            return UnitVector<iNumDimensions>((1.0 / norm) * this->components());
        }

        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        DoubleVectorBase<iNumDimensions>::rotatedBy(
            const Matrix<double, iNumDimensions, iNumDimensions>& rotationMatrix
        ) const {
            return Vector<double, iNumDimensions>(rotationMatrix * this->components());
        }

        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        DoubleVectorBase<iNumDimensions>::toLocalIn(const Frame<iNumDimensions>& frame) const {
            return Vector<double, iNumDimensions>(
                frame.basisMatrix().transposeProduct(this->components())
            );
        }

        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        DoubleVectorBase<iNumDimensions>::toGlobalFrom(const Frame<iNumDimensions>& frame) const {
            return Vector<double, iNumDimensions>(frame.basisMatrix() * this->components());
        }

        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        DoubleVectorBase<iNumDimensions>::projectedOnto(const Axis<iNumDimensions>& axis) const {
            return this->dot(axis.directionVector()) * axis.directionVector();
        }

        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        DoubleVectorBase<iNumDimensions>::mirroredAlong(
            const UnitVector<iNumDimensions>& mirrorDirection
        ) const {
            return derived() - 2.0 * this->dot(mirrorDirection) * mirrorDirection;
        }

        template <int iNumDimensions>
        inline
        bool
        DoubleVectorBase<iNumDimensions>::operator==(
            const Vector<double, iNumDimensions>& other
        ) const {
            return this->components() == other.components();
        }

        template <int iNumDimensions>
        inline
        bool
        DoubleVectorBase<iNumDimensions>::operator!=(
            const Vector<double, iNumDimensions>& other
        ) const {
            return this->components() != other.components();
        }

        template <int iNumDimensions>
        inline
        void
        DoubleVectorBase<iNumDimensions>::operator*=(double scale) {
            this->components() *= scale;
        }

        template <int iNumDimensions>
        inline
        void
        DoubleVectorBase<iNumDimensions>::operator/=(double divisor) {
            this->components() /= divisor;
        }

        template <int iNumDimensions>
        inline
        void
        DoubleVectorBase<iNumDimensions>::operator+=(const Vector<double, iNumDimensions>& other) {
            this->components() += other.components();
        }

        template <int iNumDimensions>
        inline
        void
        DoubleVectorBase<iNumDimensions>::operator-=(const Vector<double, iNumDimensions>& other) {
            this->components() -= other.components();
        }
    }
}
