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

#include <OpenSolid/Core/ParametricExpression/ExpressionConstructors.definitions.hpp>

#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/Eigen.hpp>
#include <OpenSolid/Core/ParametricExpression/IdentityExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ParameterExpression.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    ZeroExpressionConstructor<iNumDimensions, iNumParameters>::Zero() {
        return new ConstantExpression(ColumnMatrixXd::Zero(iNumDimensions), iNumParameters);
    }

    template <int iNumDimensions, int iNumParameters>
    ParametricExpression<iNumDimensions, iNumParameters>
    ConstantExpressionConstructor<iNumDimensions, iNumParameters>::Constant(
        const Matrix<double, iNumDimensions, 1>& value
    ) {
        ColumnMatrixXd columnMatrixXd = detail::constMap(value);
        return new ConstantExpression(columnMatrixXd, iNumParameters);
    }

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ConstantExpressionConstructor<1, iNumParameters>::Constant(double value) {
        return new ConstantExpression(value, iNumParameters);
    }

    template <int iNumDimensions>
    ParametricExpression<iNumDimensions, iNumDimensions>
    IdentityExpressionConstructor<iNumDimensions, iNumDimensions>::Identity() {
        return new IdentityExpression(iNumDimensions);
    }

    template <int iNumParameters>
    ParametricExpression<1, iNumParameters>
    ParameterExpressionConstructor<1, iNumParameters>::Parameter(std::int64_t parameterIndex) {
        if (parameterIndex < 0 || parameterIndex >= iNumParameters) {
            assert(false);
            return ParametricExpression<1, iNumParameters>();
        }
        return new ParameterExpression(iNumParameters, parameterIndex);
    }

    inline
    ParametricExpression<1, 1>
    NamedParameterExpressionConstructors<1, 1>::t() {
        return new ParameterExpression(1, 0);
    }

    inline
    ParametricExpression<1, 2>
    NamedParameterExpressionConstructors<1, 2>::u() {
        return new ParameterExpression(2, 0);
    }

    inline
    ParametricExpression<1, 2>
    NamedParameterExpressionConstructors<1, 2>::v() {
        return new ParameterExpression(2, 1);
    }

    template <int iNumParameters>
    ParametricExpression<2, iNumParameters>
    FromComponentsExpressionConstructors<2, iNumParameters>::FromComponents(
        const ParametricExpression<1, iNumParameters>& x,
        const ParametricExpression<1, iNumParameters>& y
    ) {
        return x.concatenated(y);
    }

    template <int iNumParameters>
    ParametricExpression<2, iNumParameters>
    FromComponentsExpressionConstructors<2, iNumParameters>::FromComponents(
        const ParametricExpression<1, iNumParameters>& x,
        double y
    ) {
        ParametricExpression<1, iNumParameters> yExpression(
            new ConstantExpression(y, iNumParameters)
        );
        return x.concatenated(yExpression);
    }

    template <int iNumParameters>
    ParametricExpression<2, iNumParameters>
    FromComponentsExpressionConstructors<2, iNumParameters>::FromComponents(
        double x,
        const ParametricExpression<1, iNumParameters>& y
    ) {
        ParametricExpression<1, iNumParameters> xExpression(
            new ConstantExpression(x, iNumParameters)
        );
        return xExpression.concatenated(y);
    }

    template <int iNumParameters>
    ParametricExpression<3, iNumParameters>
    FromComponentsExpressionConstructors<3, iNumParameters>::FromComponents(
        const ParametricExpression<1, iNumParameters>& x,
        const ParametricExpression<1, iNumParameters>& y,
        const ParametricExpression<1, iNumParameters>& z
    ) {
        return x.concatenated(y).concatenated(z);
    }

    template <int iNumParameters>
    ParametricExpression<3, iNumParameters>
    FromComponentsExpressionConstructors<3, iNumParameters>::FromComponents(
        const ParametricExpression<1, iNumParameters>& x,
        const ParametricExpression<1, iNumParameters>& y,
        double z
    ) {
        ParametricExpression<1, iNumParameters> zExpression(
            new ConstantExpression(z, iNumParameters)
        );
        return x.concatenated(y).concatenated(zExpression);
    }
    
    template <int iNumParameters>
    ParametricExpression<3, iNumParameters>
    FromComponentsExpressionConstructors<3, iNumParameters>::FromComponents(
        const ParametricExpression<1, iNumParameters>& x,
        double y,
        const ParametricExpression<1, iNumParameters>& z
    ) {
        ParametricExpression<1, iNumParameters> yExpression(
            new ConstantExpression(y, iNumParameters)
        );
        return x.concatenated(yExpression).concatenated(z);
    }
    
    template <int iNumParameters>
    ParametricExpression<3, iNumParameters>
    FromComponentsExpressionConstructors<3, iNumParameters>::FromComponents(
        double x,
        const ParametricExpression<1, iNumParameters>& y,
        const ParametricExpression<1, iNumParameters>& z
    ) {
        ParametricExpression<1, iNumParameters> xExpression(
            new ConstantExpression(x, iNumParameters)
        );
        return xExpression.concatenated(y).concatenated(z);
    }
    
    template <int iNumParameters>
    ParametricExpression<3, iNumParameters>
    FromComponentsExpressionConstructors<3, iNumParameters>::FromComponents(
        const ParametricExpression<1, iNumParameters>& x,
        double y,
        double z
    ) {
        ParametricExpression<1, iNumParameters> yExpression(
            new ConstantExpression(y, iNumParameters)
        );
        ParametricExpression<1, iNumParameters> zExpression(
            new ConstantExpression(z, iNumParameters)
        );
        return x.concatenated(yExpression).concatenated(zExpression);
    }
    
    template <int iNumParameters>
    ParametricExpression<3, iNumParameters>
    FromComponentsExpressionConstructors<3, iNumParameters>::FromComponents(
        double x,
        const ParametricExpression<1, iNumParameters>& y,
        double z
    ) {
        ParametricExpression<1, iNumParameters> xExpression(
            new ConstantExpression(x, iNumParameters)
        );
        ParametricExpression<1, iNumParameters> zExpression(
            new ConstantExpression(z, iNumParameters)
        );
        return xExpression.concatenated(y).concatenated(zExpression);
    }
    
    template <int iNumParameters>
    ParametricExpression<3, iNumParameters>
    FromComponentsExpressionConstructors<3, iNumParameters>::FromComponents(
        double x,
        double y,
        const ParametricExpression<1, iNumParameters>& z
    ) {
        ParametricExpression<1, iNumParameters> xExpression(
            new ConstantExpression(x, iNumParameters)
        );
        ParametricExpression<1, iNumParameters> yExpression(
            new ConstantExpression(y, iNumParameters)
        );
        return xExpression.concatenated(yExpression).concatenated(z);
    }
}
