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

#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricExpression.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions, int iNumParameters>
        class ZeroExpressionConstructor
        {
        public:
            static ParametricExpression<iNumDimensions, iNumParameters>
            zero();
        };

        template <int iNumDimensions, int iNumParameters>
        class ConstantExpressionConstructor
        {
        public:
            static ParametricExpression<iNumDimensions, iNumParameters>
            constant(const Matrix<double, iNumDimensions, 1>& columnMatrix);
        };

        template <int iNumParameters>
        class ConstantExpressionConstructor<1, iNumParameters>
        {
        public:
            static ParametricExpression<1, iNumParameters>
            constant(double value);
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
            identity();
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
            fromComponents(
                const ParametricExpression<1, iNumParameters>& x,
                const ParametricExpression<1, iNumParameters>& y
            );

            static ParametricExpression<2, iNumParameters>
            fromComponents(
                const ParametricExpression<1, iNumParameters>& x,
                double y
            );

            static ParametricExpression<2, iNumParameters>
            fromComponents(
                double x,
                const ParametricExpression<1, iNumParameters>& y
            );
        };

        template <int iNumParameters>
        class FromComponentsExpressionConstructors<3, iNumParameters>
        {
        public:
            static ParametricExpression<3, iNumParameters>
            fromComponents(
                const ParametricExpression<1, iNumParameters>& x,
                const ParametricExpression<1, iNumParameters>& y,
                const ParametricExpression<1, iNumParameters>& z
            );

            static ParametricExpression<3, iNumParameters>
            fromComponents(
                const ParametricExpression<1, iNumParameters>& x,
                const ParametricExpression<1, iNumParameters>& y,
                double z
            );
            
            static ParametricExpression<3, iNumParameters>
            fromComponents(
                const ParametricExpression<1, iNumParameters>& x,
                double y,
                const ParametricExpression<1, iNumParameters>& z
            );
            
            static ParametricExpression<3, iNumParameters>
            fromComponents(
                double x,
                const ParametricExpression<1, iNumParameters>& y,
                const ParametricExpression<1, iNumParameters>& z
            );
            
            static ParametricExpression<3, iNumParameters>
            fromComponents(
                const ParametricExpression<1, iNumParameters>& x,
                double y,
                double z
            );
            
            static ParametricExpression<3, iNumParameters>
            fromComponents(
                double x,
                const ParametricExpression<1, iNumParameters>& y,
                double z
            );
            
            static ParametricExpression<3, iNumParameters>
            fromComponents(
                double x,
                double y,
                const ParametricExpression<1, iNumParameters>& z
            );
        };

        template <int iNumDimensions, int iNumParameters>
        class ExpressionConstructors :
            public ZeroExpressionConstructor<iNumDimensions, iNumParameters>,
            public ConstantExpressionConstructor<iNumDimensions, iNumParameters>,
            public IdentityExpressionConstructor<iNumDimensions, iNumParameters>,
            public FromComponentsExpressionConstructors<iNumDimensions, iNumParameters>
        {
        };
    }
}
