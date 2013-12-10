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

#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    class ZeroExpressionConstructor
    {
    public:
        static ParametricExpression<iNumDimensions, iNumParameters>
        Zero();
    };

    template <int iNumDimensions, int iNumParameters>
    class ConstantExpressionConstructor
    {
    public:
        static ParametricExpression<iNumDimensions, iNumParameters>
        Constant(const Matrix<double, iNumDimensions, 1>& value);
    };

    template <int iNumParameters>
    class ConstantExpressionConstructor<1, iNumParameters>
    {
    public:
        static ParametricExpression<1, iNumParameters>
        Constant(double value);
    };

    template <int iNumDimensions, int iNumParameters>
    class IdentityExpressionConstructor
    {
    };

    template <int iNumDimensions>
    class IdentityExpressionConstructor<iNumDimensions, iNumDimensions>
    {
    public:
        static ParametricExpression<iNumDimensions, iNumDimensions>
        Identity();
    };

    template <int iNumDimensions, int iNumParameters>
    class ParameterExpressionConstructor
    {
    };

    template <int iNumParameters>
    class ParameterExpressionConstructor<1, iNumParameters>
    {
    public:
        static ParametricExpression<1, iNumParameters>
        Parameter(int parameterIndex);
    };

    template <int iNumDimensions, int iNumParameters>
    class NamedParameterExpressionConstructors
    {
    };

    template <>
    class NamedParameterExpressionConstructors<1, 1>
    {
    public:
        static ParametricExpression<1, 1>
        t();
    };

    template <>
    class NamedParameterExpressionConstructors<1, 2>
    {
    public:
        static ParametricExpression<1, 2>
        u();

        static ParametricExpression<1, 2>
        v();
    };

    template <int iNumDimensions, int iNumParameters>
    class FromComponentsExpressionConstructors
    {
    };

    template <int iNumParameters>
    class FromComponentsExpressionConstructors<2, iNumParameters>
    {
    public:
        static ParametricExpression<2, iNumParameters>
        FromComponents(
            const ParametricExpression<1, iNumParameters>& x,
            const ParametricExpression<1, iNumParameters>& y
        );

        static ParametricExpression<2, iNumParameters>
        FromComponents(
            const ParametricExpression<1, iNumParameters>& x,
            double y
        );

        static ParametricExpression<2, iNumParameters>
        FromComponents(
            double x,
            const ParametricExpression<1, iNumParameters>& y
        );
    };

    template <int iNumParameters>
    class FromComponentsExpressionConstructors<3, iNumParameters>
    {
    public:
        static ParametricExpression<3, iNumParameters>
        FromComponents(
            const ParametricExpression<1, iNumParameters>& x,
            const ParametricExpression<1, iNumParameters>& y,
            const ParametricExpression<1, iNumParameters>& z
        );

        static ParametricExpression<3, iNumParameters>
        FromComponents(
            const ParametricExpression<1, iNumParameters>& x,
            const ParametricExpression<1, iNumParameters>& y,
            double z
        );
        
        static ParametricExpression<3, iNumParameters>
        FromComponents(
            const ParametricExpression<1, iNumParameters>& x,
            double y,
            const ParametricExpression<1, iNumParameters>& z
        );
        
        static ParametricExpression<3, iNumParameters>
        FromComponents(
            double x,
            const ParametricExpression<1, iNumParameters>& y,
            const ParametricExpression<1, iNumParameters>& z
        );
        
        static ParametricExpression<3, iNumParameters>
        FromComponents(
            const ParametricExpression<1, iNumParameters>& x,
            double y,
            double z
        );
        
        static ParametricExpression<3, iNumParameters>
        FromComponents(
            double x,
            const ParametricExpression<1, iNumParameters>& y,
            double z
        );
        
        static ParametricExpression<3, iNumParameters>
        FromComponents(
            double x,
            double y,
            const ParametricExpression<1, iNumParameters>& z
        );
    };

    template <int iNumDimensions, int iNumParameters>
    class LinearExpressionConstructors
    {
    public:
        static ParametricExpression<iNumDimensions, iNumParameters>
        Linear(const CoordinateSystem<iNumDimensions, iNumParameters>& coordinateSystem);
    };

    template <int iNumDimensions, int iNumParameters>
    class ExpressionConstructors :
        public ZeroExpressionConstructor<iNumDimensions, iNumParameters>,
        public ConstantExpressionConstructor<iNumDimensions, iNumParameters>,
        public IdentityExpressionConstructor<iNumDimensions, iNumParameters>,
        public ParameterExpressionConstructor<iNumDimensions, iNumParameters>,
        public NamedParameterExpressionConstructors<iNumDimensions, iNumParameters>,
        public FromComponentsExpressionConstructors<iNumDimensions, iNumParameters>,
        public LinearExpressionConstructors<iNumDimensions, iNumParameters>
    {
    };
}
