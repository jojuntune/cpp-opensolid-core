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

#include <OpenSolid/Core/ParametricCurve/ParametricCurveBase.declarations.hpp>

#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/ParametricCurve.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class ParametricCurveBase
        {
        private:
            ParametricExpression<iNumDimensions, 1> _expression;
            Interval _domain;
            Box<iNumDimensions> _bounds;
        protected:
            ParametricCurveBase();

            ParametricCurveBase(const ParametricCurveBase<iNumDimensions>& other);

            ParametricCurveBase(ParametricCurveBase<iNumDimensions>&& other);

            ParametricCurveBase(
                const ParametricExpression<iNumDimensions, 1>& expression,
                Interval domain
            );
        public:
            const ParametricExpression<iNumDimensions, 1>&
            expression() const;

            Interval
            domain() const;

            const Box<iNumDimensions>&
            bounds() const;

            Point<iNumDimensions>
            evaluate(double parameterValue) const;

            Box<iNumDimensions>
            evaluateBounds(Interval parameterBounds) const;

            Point<iNumDimensions>
            startPoint() const;

            Point<iNumDimensions>
            endPoint() const;

            ParametricCurve<iNumDimensions>
            reversed() const;

            ParametricExpression<iNumDimensions, 1>
            tangentVector() const;

            ParametricExpression<iNumDimensions, 1>
            normalVector() const;

            ParametricExpression<iNumDimensions, 1>
            binormalVector() const;

            ParametricExpression<1, 1>
            curvature() const;
        };
    }
}
