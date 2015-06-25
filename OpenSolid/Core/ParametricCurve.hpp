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

#include <OpenSolid/Core/ParametricCurve.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricCurve/ParametricCurveBase.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

namespace opensolid
{
    inline
    ParametricCurve2d::ParametricCurve() {
    }

    inline
    ParametricCurve2d::ParametricCurve(const ParametricCurve2d& other) :
        ParametricCurveBase<2>(other) {
    }

    inline
    ParametricCurve2d::ParametricCurve(ParametricCurve2d&& other) :
        ParametricCurveBase<2>(std::move(other)) {
    }

    inline
    ParametricCurve2d::ParametricCurve(
        const ParametricExpression<Point2d, double>& expression,
        Interval domain
    ) : ParametricCurveBase<2>(expression, domain) {
    }

    inline
    ParametricCurve3d::ParametricCurve() {
    }

    inline
    ParametricCurve3d::ParametricCurve(const ParametricCurve3d& other) :
        ParametricCurveBase<3>(other) {
    }

    inline
    ParametricCurve3d::ParametricCurve(ParametricCurve3d&& other) :
        ParametricCurveBase<3>(std::move(other)) {
    }

    inline
    ParametricCurve3d::ParametricCurve(
        const ParametricExpression<Point3d, double>& expression,
        Interval domain
    ) : ParametricCurveBase<3>(expression, domain) {
    }
}
