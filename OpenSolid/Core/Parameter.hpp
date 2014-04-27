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

#include <OpenSolid/Core/Parameter.definitions.hpp>

#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ParameterExpression.hpp>

namespace opensolid
{
    namespace detail
    {
        inline
        ExpressionImplementationPtr
        parameterExpression(int numParameters, int parameterIndex) {
            if (parameterIndex >= 0 && parameterIndex < numParameters) {
                return ExpressionImplementationPtr(
                    new ParameterExpression(numParameters, parameterIndex)
                );
            } else {
                assert(false);
                return ExpressionImplementationPtr(
                    new ConstantExpression(0.0, numParameters)
                );
            }
        }
    }

    template <int iNumParameters>
    inline
    Parameter<iNumParameters>::Parameter(int parameterIndex) :
        ParametricExpression<1, iNumParameters>(
            detail::parameterExpression(iNumParameters, parameterIndex)
        ),
        _parameterIndex(parameterIndex) {
    }

    template <int iNumParameters>
    inline
    int
    Parameter<iNumParameters>::parameterIndex() const {
        return _parameterIndex;
    }

    inline
    Parameter<1>::Parameter() :
        ParametricExpression<1, 1>(new ParameterExpression(1, 0)) {
    }

    inline
    Parameter<1>::Parameter(int parameterIndex) :
        ParametricExpression<1, 1>(detail::parameterExpression(1, parameterIndex)) {
    }

    inline
    int
    Parameter<1>::parameterIndex() const {
        return 0;
    }
}
