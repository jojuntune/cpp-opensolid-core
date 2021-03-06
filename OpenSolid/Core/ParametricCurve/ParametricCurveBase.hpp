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

#include <OpenSolid/Core/ParametricCurve/ParametricCurveBase.definitions.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Parameter.hpp>
#include <OpenSolid/Core/ParametricCurve.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        ParametricCurveBase<iNumDimensions>::ParametricCurveBase() {
        }

        template <int iNumDimensions>
        inline
        ParametricCurveBase<iNumDimensions>::ParametricCurveBase(
            const ParametricCurveBase<iNumDimensions>& other
        ) : _expression(other.expression()),
            _domain(other.domain()),
            _bounds(other.bounds()) {
        }

        template <int iNumDimensions>
        inline
        ParametricCurveBase<iNumDimensions>::ParametricCurveBase(
            ParametricCurveBase<iNumDimensions>&& other
        ) : _expression(std::move(other._expression)),
            _domain(other.domain()),
            _bounds(other.bounds()) {
        }

        template <int iNumDimensions>
        inline
        ParametricCurveBase<iNumDimensions>::ParametricCurveBase(
            const ParametricExpression<Point<iNumDimensions>, double>& expression,
            Interval domain
        ) : _expression(expression),
            _domain(domain),
            _bounds(expression.evaluate(domain)) {
        }

        template <int iNumDimensions>
        inline
        const ParametricExpression<Point<iNumDimensions>, double>&
        ParametricCurveBase<iNumDimensions>::expression() const {
            return _expression;
        }

        template <int iNumDimensions>
        inline
        Interval
        ParametricCurveBase<iNumDimensions>::domain() const {
            return _domain;
        }

        template <int iNumDimensions>
        const Box<iNumDimensions>&
        ParametricCurveBase<iNumDimensions>::bounds() const {
            return _bounds;
        }

        template <int iNumDimensions>
        Point<iNumDimensions>
        ParametricCurveBase<iNumDimensions>::evaluate(double u) const {
            return expression().evaluate(u);
        }

        template <int iNumDimensions>
        Box<iNumDimensions>
        ParametricCurveBase<iNumDimensions>::evaluate(Interval u) const {
            return expression().evaluate(u);
        }

        template <int iNumDimensions>
        std::vector<Point<iNumDimensions>>
        ParametricCurveBase<iNumDimensions>::evaluate(
            const std::vector<double>& parameterValues
        ) const {
            return expression().evaluate(parameterValues);
        }

        template <int iNumDimensions>
        std::vector<Box<iNumDimensions>>
        ParametricCurveBase<iNumDimensions>::evaluate(
            const std::vector<Interval>& parameterValues
        ) const {
            return expression().evaluate(parameterValues);
        }

        template <int iNumDimensions>
        Point<iNumDimensions>
        ParametricCurveBase<iNumDimensions>::startPoint() const {
            return evaluate(domain().lowerBound());
        }

        template <int iNumDimensions>
        Point<iNumDimensions>
        ParametricCurveBase<iNumDimensions>::endPoint() const {
            return evaluate(domain().upperBound());
        }

        template <int iNumDimensions>
        ParametricExpression<UnitVector<iNumDimensions>, double>
        ParametricCurveBase<iNumDimensions>::tangentVector() const {
            return expression().derivative().normalized();
        }
    }
}
