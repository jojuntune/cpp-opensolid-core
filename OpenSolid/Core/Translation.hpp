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

#include <OpenSolid/Core/Translation.definitions.hpp>

#include <OpenSolid/Core/Transformation.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    inline
    Translation<iNumDimensions>::Translation(const Vector<double, iNumDimensions>& vector) :
        _vector(vector) {
    }

    template <int iNumDimensions>
    inline
    const Vector<double, iNumDimensions>&
    Translation<iNumDimensions>::vector() const {
        return _vector;
    }

    template <int iNumDimensions>
    inline
    double
    Translation<iNumDimensions>::scale() const {
        return 1.0;
    }

    template <int iNumDimensions>
    inline
    Handedness
    Translation<iNumDimensions>::transform(Handedness handedness) const {
        return handedness;
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    Translation<iNumDimensions>::transform(const Point<iNumDimensions>& point) const {
        return point + vector();
    }

    template <int iNumDimensions> template <class TParameter>
    inline
    ParametricExpression<Point<iNumDimensions>, TParameter>
    Translation<iNumDimensions>::transform(
        const ParametricExpression<Point<iNumDimensions>, TParameter>& expression
    ) const {
        return expression + vector();
    }

    template <int iNumDimensions>
    inline
    const Vector<double, iNumDimensions>&
    Translation<iNumDimensions>::transform(const Vector<double, iNumDimensions>& vector) const {
        return vector;
    }

    template <int iNumDimensions> template <class TParameter>
    inline
    ParametricExpression<Vector<double, iNumDimensions>, TParameter>
    Translation<iNumDimensions>::transform(
        const ParametricExpression<Vector<double, iNumDimensions>, TParameter>& expression
    ) const {
        return expression;
    }

    template <int iNumDimensions>
    inline
    const UnitVector<iNumDimensions>&
    Translation<iNumDimensions>::transform(const UnitVector<iNumDimensions>& unitVector) const {
        return unitVector;
    }

    template <int iNumDimensions> template <class TParameter>
    inline
    ParametricExpression<UnitVector<iNumDimensions>, TParameter>
    Translation<iNumDimensions>::transform(
        const ParametricExpression<UnitVector<iNumDimensions>, TParameter>& expression
    ) const {
        return expression;
    }
}
