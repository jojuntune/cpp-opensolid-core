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

#include <OpenSolid/Core/Vector/IntervalVectorBase.definitions.hpp>

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/IntervalVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    inline
    IntervalVectorBase<iNumDimensions>::IntervalVectorBase(Interval x) {
        static_assert(iNumDimensions == 1, "One-argument constructor only for 1D vectors");
        _components[0] = x;
    }

    template <int iNumDimensions>
    inline
    IntervalVectorBase<iNumDimensions>::IntervalVectorBase(Interval x, Interval y) {
        static_assert(iNumDimensions == 1, "Two-argument constructor only for 2D vectors");
        _components[0] = x;
        _components[1] = y;
    }

    template <int iNumDimensions>
    inline
    IntervalVectorBase<iNumDimensions>::IntervalVectorBase(Interval x, Interval y, Interval z) {
        static_assert(iNumDimensions == 1, "Three-argument constructor only for 3D vectors");
        _components[0] = x;
        _components[1] = y;
        _components[2] = z;
    }

    template <int iNumDimensions>
    inline
    const Interval*
    IntervalVectorBase<iNumDimensions>::data() const {
        return _components;
    }

    template <int iNumDimensions>
    inline
    const Interval
    IntervalVectorBase<iNumDimensions>::component(std::int64_t index) const {
        assert(index >= 0 && index < iNumDimensions);
        return _components[index];
    }

    template <int iNumDimensions>
    inline
    const Interval
    IntervalVectorBase<iNumDimensions>::operator()(std::int64_t index) const {
        return component(index);
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<1>::squaredNorm() const {
        return component(0).squared();
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<2>::squaredNorm() const {
        return component(0).squared() + component(1).squared();
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<3>::squaredNorm() const {
        return component(0).squared() + component(1).squared() + component(2).squared();
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<1>::norm() const {
        return abs(component(0));
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<2>::norm() const {
        return sqrt(squaredNorm());
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<3>::norm() const {
        return sqrt(squaredNorm());
    }

    template <int iNumDimensions>
    inline
    const IntervalVector<iNumDimensions>
    IntervalVectorBase<iNumDimensions>::normalized() const {
        return IntervalVector<iNumDimensions>(*this / norm());
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<1>::dot(const Vector<1>& vector) const {
        return component(0) * vector.component(0);
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<2>::dot(const Vector<2>& vector) const {
        return component(0) * vector.component(0) +
            component(1) * vector.component(1);
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<3>::dot(const Vector<3>& vector) const {
        return component(0) * vector.component(0) +
            component(1) * vector.component(1) +
            component(2) * vector.component(2);
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<1>::dot(const IntervalVector<1>& other) const {
        return component(0) * other.component(0);
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<2>::dot(const IntervalVector<2>& other) const {
        return component(0) * other.component(0) +
            component(1) * other.component(1);
    }

    template <>
    inline
    const Interval
    IntervalVectorBase<3>::dot(const IntervalVector<3>& other) const {
        return component(0) * other.component(0) +
            component(1) * other.component(1) +
            component(2) * other.component(1);
    }
}
