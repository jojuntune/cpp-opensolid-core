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

#include <OpenSolid/Core/ParametricCurve.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/BoundsType.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricCurve/ParametricCurveBase.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Triangle.hpp>

namespace opensolid
{
    inline
    ParametricCurve<2>::ParametricCurve() {
    }

    inline
    ParametricCurve<2>::ParametricCurve(const ParametricCurve<2>& other) :
        ParametricCurveBase<2>(other) {
    }

    inline
    ParametricCurve<2>::ParametricCurve(ParametricCurve<2>&& other) :
        ParametricCurveBase<2>(std::move(other)) {
    }

    inline
    ParametricCurve<2>::ParametricCurve(
        const ParametricExpression<2, 1>& expression,
        Interval domain
    ) : ParametricCurveBase<2>(expression, domain) {
    }

    inline
    ParametricCurve<3>::ParametricCurve() {
    }

    inline
    ParametricCurve<3>::ParametricCurve(const ParametricCurve<3>& other) :
        ParametricCurveBase<3>(other) {
    }

    inline
    ParametricCurve<3>::ParametricCurve(ParametricCurve<3>&& other) :
        ParametricCurveBase<3>(std::move(other)) {
    }

    inline
    ParametricCurve<3>::ParametricCurve(
        const ParametricExpression<3, 1>& expression,
        Interval domain
    ) : ParametricCurveBase<3>(expression, domain) {
    }

    template <int iNumDimensions>
    ParametricCurve<iNumDimensions>
    ScalingFunction<ParametricCurve<iNumDimensions>>::operator()(
        const ParametricCurve<iNumDimensions>& curve,
        double scale
    ) const {
        return ParametricCurve<iNumDimensions>(scale * curve.expression(), curve.domain());
    }

    template <int iNumDimensions> template <class TVector>
    ParametricCurve<iNumDimensions>
    TranslationFunction<ParametricCurve<iNumDimensions>>::operator()(
        const ParametricCurve<iNumDimensions>& curve,
        const EigenBase<TVector>& vector
    ) const {
        return ParametricCurve<iNumDimensions>(
            curve.expression() + vector.derived(),
            curve.domain()
        );
    }

    template <int iNumDimensions, int iNumResultDimensions> template <class TMatrix>
    ParametricCurve<iNumResultDimensions>
    TransformationFunction<ParametricCurve<iNumDimensions>, iNumResultDimensions>::operator()(
        const ParametricCurve<iNumDimensions>& curve,
        const EigenBase<TMatrix>& matrix
    ) const {
        return ParametricCurve<iNumResultDimensions>(
            matrix.derived() * curve.expression(),
            curve.domain()
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    ParametricCurve<iNumResultDimensions>
    MorphingFunction<ParametricCurve<iNumDimensions>, iNumResultDimensions>::operator()(
        const ParametricCurve<iNumDimensions>& curve,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return ParametricCurve<iNumResultDimensions>(
            morphingExpression.composed(curve.expression()),
            curve.domain()
        );
    }
}
