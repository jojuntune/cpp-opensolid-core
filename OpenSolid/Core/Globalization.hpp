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

#include <OpenSolid/Core/Globalization.definitions.hpp>

#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Transformation.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    Globalization<iNumDimensions>::Globalization(const Frame<iNumDimensions>& frame) :
        _frame(frame) {
    }

    template <int iNumDimensions>
    inline
    const Frame<iNumDimensions>&
    Globalization<iNumDimensions>::frame() const {
        return _frame;
    }

    template <int iNumDimensions>
    inline
    double
    Globalization<iNumDimensions>::scale() const {
        return 1.0;
    }

    template <int iNumDimensions>
    inline
    Handedness
    Globalization<iNumDimensions>::transform(Handedness handedness) const {
        return frame().handedness() * handedness;
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    Globalization<iNumDimensions>::transform(const Point<iNumDimensions>& point) const {
        return (
            frame().originPoint() +
            Vector<double, iNumDimensions>(frame().basisMatrix() * point.components())
        );
    }

    template <int iNumDimensions> template <class TParameter>
    inline
    ParametricExpression<Point<iNumDimensions>, TParameter>
    Globalization<iNumDimensions>::transform(
        const ParametricExpression<Point<iNumDimensions>, TParameter>& expression
    ) const {
        return (
            frame().originPoint().components() + frame().basisMatrix() * expression.implementation()
        );
    }

    template <int iNumDimensions>
    inline
    Vector<double, iNumDimensions>
    Globalization<iNumDimensions>::transform(const Vector<double, iNumDimensions>& vector) const {
        return Vector<double, iNumDimensions>(frame().basisMatrix() * vector.components());
    }

    template <int iNumDimensions> template <class TParameter>
    inline
    ParametricExpression<Vector<double, iNumDimensions>, TParameter>
    Globalization<iNumDimensions>::transform(
        const ParametricExpression<Vector<double, iNumDimensions>, TParameter>& expression
    ) const {
        return frame().basisMatrix() * expression.implementation();
    }

    template <int iNumDimensions>
    inline
    UnitVector<iNumDimensions>
    Globalization<iNumDimensions>::transform(const UnitVector<iNumDimensions>& unitVector) const {
        return UnitVector<iNumDimensions>(frame().basisMatrix() * unitVector.components());
    }

    template <int iNumDimensions> template <class TParameter>
    inline
    ParametricExpression<UnitVector<iNumDimensions>, TParameter>
    Globalization<iNumDimensions>::transform(
        const ParametricExpression<UnitVector<iNumDimensions>, TParameter>& expression
    ) const {
        return frame().basisMatrix() * expression.implementation();
    }
}
