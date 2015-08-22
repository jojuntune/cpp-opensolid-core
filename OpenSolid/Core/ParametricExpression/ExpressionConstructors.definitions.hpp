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
#include <OpenSolid/Core/NumDimensions.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TValue, class TParameter>
        class ZeroExpressionConstructor
        {
        public:
            static ParametricExpression<TValue, TParameter>
            zero();
        };

        template <class TValue, class TParameter>
        class ConstantExpressionConstructor;

        template <class TParameter>
        class ConstantExpressionConstructor<double, TParameter>
        {
        public:
            static ParametricExpression<double, TParameter>
            constant(double value);
        };

        template <int iNumDimensions, class TParameter>
        class ConstantExpressionConstructor<Vector<double, iNumDimensions>, TParameter>
        {
        public:
            static ParametricExpression<Vector<double, iNumDimensions>, TParameter>
            constant(const Vector<double, iNumDimensions>& vector);
        };

        template <int iNumDimensions, class TParameter>
        class ConstantExpressionConstructor<UnitVector<iNumDimensions>, TParameter>
        {
        public:
            static ParametricExpression<UnitVector<iNumDimensions>, TParameter>
            constant(const UnitVector<iNumDimensions>& unitVector);
        };

        template <int iNumDimensions, class TParameter>
        class ConstantExpressionConstructor<Point<iNumDimensions>, TParameter>
        {
        public:
            static ParametricExpression<Point<iNumDimensions>, TParameter>
            constant(const Point<iNumDimensions>& point);
        };

        template <class TValue, class TParameter>
        class IdentityExpressionConstructor
        {
        };

        template <class TValue>
        class IdentityExpressionConstructor<TValue, TValue>
        {
        public:
            static ParametricExpression<TValue, TValue>
            identity();
        };

        template <class TValue, int iValueDimension, class TParameter>
        class FromComponentsExpressionConstructors
        {
        };

        template <class TValue, class TParameter>
        class FromComponentsExpressionConstructors<TValue, 2, TParameter>
        {
        public:
            static ParametricExpression<TValue, TParameter>
            fromComponents(
                const ParametricExpression<double, TParameter>& x,
                const ParametricExpression<double, TParameter>& y
            );

            static ParametricExpression<TValue, TParameter>
            fromComponents(
                const ParametricExpression<double, TParameter>& x,
                double y
            );

            static ParametricExpression<TValue, TParameter>
            fromComponents(
                double x,
                const ParametricExpression<double, TParameter>& y
            );
        };

        template <class TValue, class TParameter>
        class FromComponentsExpressionConstructors<TValue, 3, TParameter>
        {
        public:
            static ParametricExpression<TValue, TParameter>
            fromComponents(
                const ParametricExpression<double, TParameter>& x,
                const ParametricExpression<double, TParameter>& y,
                const ParametricExpression<double, TParameter>& z
            );

            static ParametricExpression<TValue, TParameter>
            fromComponents(
                const ParametricExpression<double, TParameter>& x,
                const ParametricExpression<double, TParameter>& y,
                double z
            );
            
            static ParametricExpression<TValue, TParameter>
            fromComponents(
                const ParametricExpression<double, TParameter>& x,
                double y,
                const ParametricExpression<double, TParameter>& z
            );
            
            static ParametricExpression<TValue, TParameter>
            fromComponents(
                double x,
                const ParametricExpression<double, TParameter>& y,
                const ParametricExpression<double, TParameter>& z
            );
            
            static ParametricExpression<TValue, TParameter>
            fromComponents(
                const ParametricExpression<double, TParameter>& x,
                double y,
                double z
            );
            
            static ParametricExpression<TValue, TParameter>
            fromComponents(
                double x,
                const ParametricExpression<double, TParameter>& y,
                double z
            );
            
            static ParametricExpression<TValue, TParameter>
            fromComponents(
                double x,
                double y,
                const ParametricExpression<double, TParameter>& z
            );
        };

        template <class TValue, class TParameter>
        class ExpressionConstructors :
            public ZeroExpressionConstructor<TValue, TParameter>,
            public ConstantExpressionConstructor<TValue, TParameter>,
            public IdentityExpressionConstructor<TValue, TParameter>,
            public FromComponentsExpressionConstructors<
                TValue,
                NumDimensions<TValue>::Value,
                TParameter
            >
        {
        };
    }
}
