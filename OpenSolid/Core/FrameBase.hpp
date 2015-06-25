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

#include <OpenSolid/Core/FrameBase.definitions.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Vector.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    inline
    FrameBase<iNumDimensions, iNumAxes>::FrameBase() {
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    FrameBase<iNumDimensions, iNumAxes>::FrameBase(const Point<iNumDimensions>& originPoint) :
        _originPoint(originPoint) {
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    FrameBase<iNumDimensions, iNumAxes>::FrameBase(
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
    ) : _originPoint(originPoint),
        _basisMatrix(basisMatrix) {
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Point<iNumDimensions>&
    FrameBase<iNumDimensions, iNumAxes>::originPoint() const {
        return _originPoint;
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Matrix<double, iNumDimensions, iNumAxes>&
    FrameBase<iNumDimensions, iNumAxes>::basisMatrix() const {
        return _basisMatrix;
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    UnitVector<iNumDimensions>
    FrameBase<iNumDimensions, iNumAxes>::directionVector(int index) const {
        assert(index >= 0 && index < iNumAxes);
        return UnitVector<iNumDimensions>(basisMatrix().column(index));
    }
}
