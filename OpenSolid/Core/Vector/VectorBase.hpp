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

#include <OpenSolid/Core/Vector/VectorBase.definitions.hpp>

#include <OpenSolid/Core/IntervalVector.hpp>
#include <OpenSolid/Core/Vector.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    inline
    VectorBase<iNumDimensions>::VectorBase(double x) {
        static_assert(iNumDimensions == 1, "One-argument constructor only for 1D vectors");
        _components[0] = x;
    }

    template <int iNumDimensions>
    inline
    VectorBase<iNumDimensions>::VectorBase(double x, double y) {
        static_assert(iNumDimensions == 1, "Two-argument constructor only for 2D vectors");
        _components[0] = x;
        _components[1] = y;
    }

    template <int iNumDimensions>
    inline
    VectorBase<iNumDimensions>::VectorBase(double x, double y, double z) {
        static_assert(iNumDimensions == 1, "Three-argument constructor only for 3D vectors");
        _components[0] = x;
        _components[1] = y;
        _components[2] = z;
    }

    template <int iNumDimensions>
    inline
    const double*
    VectorBase<iNumDimensions>::data() const {
        return _components;
    }

    template <int iNumDimensions>
    inline
    const double
    VectorBase<iNumDimensions>::component(std::int64_t index) const {
        assert(index >= 0 && index < iNumDimensions);
        return _components[index];
    }

    template <int iNumDimensions>
    inline
    const double
    VectorBase<iNumDimensions>::operator()(std::int64_t index) const {
        return component(index);
    }
}
