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

#include <OpenSolid/Core/Scaling.definitions.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformation.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    inline
    Scaling<iNumDimensions>::Scaling(const Point<iNumDimensions>& point, double scale) :
        _point(point),
        _scale(scale) {

        if (scale < 0.0) {
            throw Error(new PlaceholderError());
        }
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>&
    Scaling<iNumDimensions>::point() const {
        return _point;
    }

    template <int iNumDimensions>
    inline
    double
    Scaling<iNumDimensions>::scale() const {
        return _scale;
    }

    template <int iNumDimensions>
    inline
    Handedness
    Scaling<iNumDimensions>::transform(Handedness handedness) const {
        return handedness;
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    Scaling<iNumDimensions>::transform(const Point<iNumDimensions>& point) const {
        return this->point() + scale() * (point - this->point());
    }

    template <int iNumDimensions> template <class TParameter>
    inline
    ParametricExpression<Point<iNumDimensions>, TParameter>
    Scaling<iNumDimensions>::transform(
        const ParametricExpression<Point<iNumDimensions>, TParameter>& expression
    ) const {
        return this->point() + scale() * (expression - this->point());
    }

    template <int iNumDimensions>
    inline
    Vector<double, iNumDimensions>
    Scaling<iNumDimensions>::transform(const Vector<double, iNumDimensions>& vector) const {
        return scale() * vector;
    }

    template <int iNumDimensions> template <class TParameter>
    inline
    ParametricExpression<Vector<double, iNumDimensions>, TParameter>
    Scaling<iNumDimensions>::transform(
        const ParametricExpression<Vector<double, iNumDimensions>, TParameter>& expression
    ) const {
        return scale() * expression;
    }

    template <int iNumDimensions>
    inline
    UnitVector<iNumDimensions>
    Scaling<iNumDimensions>::transform(const UnitVector<iNumDimensions>& unitVector) const {
        return unitVector;
    }

    template <int iNumDimensions> template <class TParameter>
    inline
    ParametricExpression<UnitVector<iNumDimensions>, TParameter>
    Scaling<iNumDimensions>::transform(
        const ParametricExpression<UnitVector<iNumDimensions>, TParameter>& expression
    ) const {
        return expression;
    }
}
