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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Function/FunctionConstructors.definitions.hpp>

#include <OpenSolid/Core/Function.definitions.hpp>
#include <OpenSolid/Core/FunctionImplementation/LinearFunction.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    ZeroFunctionConstructor<iNumDimensions, iNumParameters>::Zero() {
        return new ConstantFunction(VectorXd::Zero(iNumDimensions), iNumParameters);
    }

    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    ConstantFunctionConstructor<iNumDimensions, iNumParameters>::Constant(
        const Matrix<double, iNumDimensions, 1>& value
    ) {
        return new ConstantFunction(value, iNumParameters);
    }

    template <int iNumParameters>
    Function<1, iNumParameters>
    ConstantFunctionConstructor<1, iNumParameters>::Constant(double value) {
        return new ConstantFunction(value, iNumParameters);
    }

    template <int iNumDimensions>
    Function<iNumDimensions, iNumDimensions>
    IdentityFunctionConstructor<iNumDimensions, iNumDimensions>::Identity() {
        return new IdentityFunction(iNumDimensions);
    }

    template <int iNumParameters>
    Function<1, iNumParameters>
    ParameterFunctionConstructor<1, iNumParameters>::Parameter(int parameterIndex) {
        if (parameterIndex < 0 || parameterIndex >= iNumParameters) {
            assert(false);
            return Function<1, iNumParameters>();
        }
        return new ParameterFunction(iNumParameters, parameterIndex);
    }

    inline Function<1, 1>
    NamedParameterFunctionConstructors<1, 1>::t() {
        return new ParameterFunction(1, 0);
    }

    inline Function<1, 2>
    NamedParameterFunctionConstructors<1, 2>::u() {
        return new ParameterFunction(2, 0);
    }

    inline Function<1, 2>
    NamedParameterFunctionConstructors<1, 2>::v() {
        return new ParameterFunction(2, 1);
    }

    template <int iNumParameters>
    Function<2, iNumParameters>
    FromComponentsFunctionConstructors<2, iNumParameters>::FromComponents(
        const Function<1, iNumParameters>& x,
        const Function<1, iNumParameters>& y
    ) {
        return x.concatenated(y);
    }

    template <int iNumParameters>
    Function<2, iNumParameters>
    FromComponentsFunctionConstructors<2, iNumParameters>::FromComponents(
        const Function<1, iNumParameters>& x,
        double y
    ) {
        Function<1, iNumParameters> yFunction(new ConstantFunction(y, iNumParameters));
        return x.concatenated(yFunction);
    }

    template <int iNumParameters>
    Function<2, iNumParameters>
    FromComponentsFunctionConstructors<2, iNumParameters>::FromComponents(
        double x,
        const Function<1, iNumParameters>& y
    ) {
        Function<1, iNumParameters> xFunction(new ConstantFunction(x, iNumParameters));
        return xFunction.concatenated(y);
    }

    template <int iNumParameters>
    Function<3, iNumParameters>
    FromComponentsFunctionConstructors<3, iNumParameters>::FromComponents(
        const Function<1, iNumParameters>& x,
        const Function<1, iNumParameters>& y,
        const Function<1, iNumParameters>& z
    ) {
        return x.concatenated(y).concatenated(z);
    }

    template <int iNumParameters>
    Function<3, iNumParameters>
    FromComponentsFunctionConstructors<3, iNumParameters>::FromComponents(
        const Function<1, iNumParameters>& x,
        const Function<1, iNumParameters>& y,
        double z
    ) {
        Function<1, iNumParameters> zFunction(new ConstantFunction(z, iNumParameters));
        return x.concatenated(y).concatenated(zFunction);
    }
    
    template <int iNumParameters>
    Function<3, iNumParameters>
    FromComponentsFunctionConstructors<3, iNumParameters>::FromComponents(
        const Function<1, iNumParameters>& x,
        double y,
        const Function<1, iNumParameters>& z
    ) {
        Function<1, iNumParameters> yFunction(new ConstantFunction(y, iNumParameters));
        return x.concatenated(yFunction).concatenated(z);
    }
    
    template <int iNumParameters>
    Function<3, iNumParameters>
    FromComponentsFunctionConstructors<3, iNumParameters>::FromComponents(
        double x,
        const Function<1, iNumParameters>& y,
        const Function<1, iNumParameters>& z
    ) {
        Function<1, iNumParameters> xFunction(new ConstantFunction(x, iNumParameters));
        return xFunction.concatenated(y).concatenated(z);
    }
    
    template <int iNumParameters>
    Function<3, iNumParameters>
    FromComponentsFunctionConstructors<3, iNumParameters>::FromComponents(
        const Function<1, iNumParameters>& x,
        double y,
        double z
    ) {
        Function<1, iNumParameters> yFunction(new ConstantFunction(y, iNumParameters));
        Function<1, iNumParameters> zFunction(new ConstantFunction(z, iNumParameters));
        return x.concatenated(yFunction).concatenated(zFunction);
    }
    
    template <int iNumParameters>
    Function<3, iNumParameters>
    FromComponentsFunctionConstructors<3, iNumParameters>::FromComponents(
        double x,
        const Function<1, iNumParameters>& y,
        double z
    ) {
        Function<1, iNumParameters> xFunction(new ConstantFunction(x, iNumParameters));
        Function<1, iNumParameters> zFunction(new ConstantFunction(z, iNumParameters));
        return xFunction.concatenated(y).concatenated(zFunction);
    }
    
    template <int iNumParameters>
    Function<3, iNumParameters>
    FromComponentsFunctionConstructors<3, iNumParameters>::FromComponents(
        double x,
        double y,
        const Function<1, iNumParameters>& z
    ) {
        Function<1, iNumParameters> xFunction(new ConstantFunction(x, iNumParameters));
        Function<1, iNumParameters> yFunction(new ConstantFunction(y, iNumParameters));
        return xFunction.concatenated(yFunction).concatenated(z);
    }

    template <int iNumDimensions, int iNumParameters>
    Function<iNumDimensions, iNumParameters>
    LinearFunctionConstructors<iNumDimensions, iNumParameters>::Linear(
        const Datum<iNumDimensions, iNumParameters>& datum
    ) {
        return Function<iNumDimensions, iNumParameters>(
            new LinearFunction(datum.originPoint().vector(), datum.basisMatrix())
        );
    }
}
