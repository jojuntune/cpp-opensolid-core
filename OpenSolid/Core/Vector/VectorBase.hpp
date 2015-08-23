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

#include <OpenSolid/Core/Vector/VectorBase.definitions.hpp>

#include <OpenSolid/Core/Cartesian/CartesianBase.hpp>
#include <OpenSolid/Core/Vector.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumDimensions>
        inline
        const Vector<TScalar, iNumDimensions>&
        VectorBase<TScalar, iNumDimensions>::derived() const {
            return static_cast<const Vector<TScalar, iNumDimensions>&>(*this);
        }

        template <class TScalar, int iNumDimensions>
        inline
        VectorBase<TScalar, iNumDimensions>::VectorBase() {
        }

        template <class TScalar, int iNumDimensions>
        inline
        VectorBase<TScalar, iNumDimensions>::VectorBase(TScalar x, TScalar y) :
            CartesianBase<TScalar, iNumDimensions>(x, y) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        VectorBase<TScalar, iNumDimensions>::VectorBase(TScalar x, TScalar y, TScalar z) :
            CartesianBase<TScalar, iNumDimensions>(x, y, z) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        VectorBase<TScalar, iNumDimensions>::VectorBase(
            const Matrix<TScalar, iNumDimensions, 1>& components
        ) : CartesianBase<TScalar, iNumDimensions>(components) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar
        VectorBase<TScalar, iNumDimensions>::squaredNorm() const {
            return this->components().cwiseSquared().sum();
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar
        VectorBase<TScalar, iNumDimensions>::norm() const {
            return opensolid::sqrt(squaredNorm());
        }

        template <class TScalar, int iNumDimensions>
        inline
        bool
        VectorBase<TScalar, iNumDimensions>::isZero(double precision) const {
            return squaredNorm() <= precision * precision;
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar
        VectorBase<TScalar, iNumDimensions>::dot(
            const Vector<double, iNumDimensions>& other
        ) const {
            return this->components().cwiseProduct(other.components()).sum();
        }

        template <class TScalar, int iNumDimensions>
        inline
        Interval
        VectorBase<TScalar, iNumDimensions>::dot(
            const Vector<Interval, iNumDimensions>& other
        ) const {
            return this->components().cwiseProduct(other.components()).sum();
        }

        template <class TScalar, int iNumDimensions> template <class TOtherScalar>
        inline
        Vector<Interval, iNumDimensions>
        VectorBase<TScalar, iNumDimensions>::hull(
            const Vector<TOtherScalar, iNumDimensions>& other
        ) const {
            return Vector<Interval, iNumDimensions>(
                this->components().cwiseHull(other.components())
            );
        }

        template <class TScalar, int iNumDimensions> template <class TOtherScalar>
        inline
        Vector<Interval, iNumDimensions>
        VectorBase<TScalar, iNumDimensions>::intersection(
            const Vector<TOtherScalar, iNumDimensions>& other
        ) const {
            return Vector<Interval, iNumDimensions>(
                this->components().cwiseIntersection(other.components())
            );
        }

        template <class TScalar, int iNumDimensions>
        inline
        Vector<TScalar, iNumDimensions>
        VectorBase<TScalar, iNumDimensions>::ZERO() {
            return Vector<TScalar, iNumDimensions>(Matrix<TScalar, iNumDimensions, 1>::ZERO());
        }

        template <class TScalar, int iNumDimensions>
        inline
        Vector<TScalar, iNumDimensions>
        VectorBase<TScalar, iNumDimensions>::random() {
            return Vector<TScalar, iNumDimensions>(Matrix<TScalar, iNumDimensions, 1>::random());
        }
    }
}
