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

#include <OpenSolid/Core/ParametricCurve/ParametricCurveBase.declarations.hpp>

#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/ParametricCurve.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class ParametricCurveBase :
            public Transformable<ParametricCurve<iNumDimensions>, iNumDimensions>
        {
        private:
            ParametricExpression<Point<iNumDimensions>, double> _expression;
            Interval _domain;
            Box<iNumDimensions> _bounds;
        protected:
            ParametricCurveBase();

            ParametricCurveBase(const ParametricCurveBase<iNumDimensions>& other);

            ParametricCurveBase(ParametricCurveBase<iNumDimensions>&& other);

            ParametricCurveBase(
                const ParametricExpression<Point<iNumDimensions>, double>& expression,
                Interval domain
            );
        public:
            const ParametricExpression<Point<iNumDimensions>, double>&
            expression() const;

            Interval
            domain() const;

            const Box<iNumDimensions>&
            bounds() const;

            Point<iNumDimensions>
            evaluate(double u) const;

            Box<iNumDimensions>
            evaluate(Interval u) const;

            std::vector<Point<iNumDimensions>>
            evaluate(const std::vector<double>& parameterValues) const;

            std::vector<Box<iNumDimensions>>
            evaluate(const std::vector<Interval>& parameterValues) const;

            Point<iNumDimensions>
            startPoint() const;

            Point<iNumDimensions>
            endPoint() const;

            ParametricCurve<iNumDimensions>
            reversed() const;

            ParametricExpression<Vector<double, iNumDimensions>, double>
            tangentVector() const;

            ParametricExpression<Vector<double, iNumDimensions>, double>
            normalVector() const;

            ParametricExpression<Vector<double, iNumDimensions>, double>
            binormalVector() const;

            ParametricExpression<double, double>
            curvature() const;

            ParametricCurve<iNumDimensions>
            scaledAbout(const Point<iNumDimensions>& point, double scale) const;

            ParametricCurve<iNumDimensions>
            rotatedAbout(
                const Point<iNumDimensions>& point,
                const Matrix<double, iNumDimensions, iNumDimensions>& rotationMatrix
            ) const;

            using Transformable<ParametricCurve<iNumDimensions>, iNumDimensions>::rotatedAbout;

            ParametricCurve<iNumDimensions>
            translatedBy(const Vector<double, iNumDimensions>& vector) const;

            ParametricCurve<iNumDimensions>
            toLocalIn(const Frame<iNumDimensions>& frame) const;

            ParametricCurve<iNumDimensions>
            toGlobalFrom(const Frame<iNumDimensions>& frame) const;

            ParametricCurve<iNumDimensions>
            mirroredAbout(
                const Point<iNumDimensions>& point,
                const UnitVector<iNumDimensions>& mirrorDirection
            ) const;

            using Transformable<ParametricCurve<iNumDimensions>, iNumDimensions>::mirroredAbout;
        };
    }
}
