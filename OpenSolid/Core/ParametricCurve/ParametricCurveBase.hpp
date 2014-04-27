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

#include <OpenSolid/Core/ParametricCurve/ParametricCurveBase.definitions.hpp>

#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Parameter.hpp>
#include <OpenSolid/Core/ParametricCurve.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>

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
            const ParametricExpression<iNumDimensions, 1>& expression,
            Interval domain
        ) : _expression(expression),
            _domain(domain),
            _bounds(expression.evaluate(domain)) {
        }

        template <int iNumDimensions>
        inline
        const ParametricExpression<iNumDimensions, 1>&
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
            return Point<iNumDimensions>(expression().evaluate(u));
        }

        template <int iNumDimensions>
        Box<iNumDimensions>
        ParametricCurveBase<iNumDimensions>::evaluate(Interval u) const {
            return Box<iNumDimensions>(expression().evaluate(u));
        }

        template <int iNumDimensions>
        std::vector<Point<iNumDimensions>>
        ParametricCurveBase<iNumDimensions>::evaluate(
            const std::vector<double>& parameterValues
        ) const {
            std::vector<Matrix<double, iNumDimensions, 1>> temp =
                expression().evaluate(parameterValues);
            std::vector<Point<iNumDimensions>> results(parameterValues.size());
            std::transform(
                temp.begin(),
                temp.end(),
                results.begin(),
                [] (const Matrix<double, iNumDimensions, 1>& components) -> Point<iNumDimensions> {
                    return Point<iNumDimensions>(components);
                }
            );
            return results;
        }

        template <int iNumDimensions>
        std::vector<Box<iNumDimensions>>
        ParametricCurveBase<iNumDimensions>::evaluate(
            const std::vector<Interval>& parameterValues
        ) const {
            std::vector<Matrix<Interval, iNumDimensions, 1>> temp =
                expression().evaluate(parameterValues);
            std::vector<Box<iNumDimensions>> results(parameterValues.size());
            std::transform(
                temp.begin(),
                temp.end(),
                results.begin(),
                [] (const Matrix<Interval, iNumDimensions, 1>& components) -> Box<iNumDimensions> {
                    return Box<iNumDimensions>(components);
                }
            );
            return results;
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
        ParametricCurve<iNumDimensions>
        ParametricCurveBase<iNumDimensions>::reversed() const {
            ParametricExpression<1, 1> reversedParameter =
                domain().upperBound() + domain().lowerBound() - Parameter1d();
            return ParametricCurve<iNumDimensions>(
                expression().composed(reversedParameter),
                domain()
            );
        }

        template <int iNumDimensions>
        ParametricExpression<iNumDimensions, 1>
        ParametricCurveBase<iNumDimensions>::tangentVector() const {
            return expression().derivative().normalized();
        }

        template <int iNumDimensions>
        ParametricExpression<iNumDimensions, 1>
        ParametricCurveBase<iNumDimensions>::normalVector() const {
            return tangentVector().derivative().normalized();
        }

        template <int iNumDimensions>
        ParametricExpression<iNumDimensions, 1>
        ParametricCurveBase<iNumDimensions>::binormalVector() const {
            return tangentVector().cross(normalVector());
        }

        template <int iNumDimensions>
        ParametricExpression<1, 1>
        ParametricCurveBase<iNumDimensions>::curvature() const {
            return tangentVector().derivative().norm() / expression().derivative().norm();
        }
    }
}
