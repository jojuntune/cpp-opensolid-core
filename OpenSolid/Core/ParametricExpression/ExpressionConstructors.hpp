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

#include <OpenSolid/Core/ParametricExpression/ExpressionConstructors.definitions.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ConstantExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/IdentityExpression.hpp>
#include <OpenSolid/Core/ParametricExpression/ParameterExpression.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        ZeroExpressionConstructor<TValue, TParameter>::zero() {
            return new ConstantExpression(
                ColumnMatrixXd::zero(NumDimensions<TValue>::Value),
                NumDimensions<TParameter>::Value
            );
        }

        template <class TParameter>
        ParametricExpression<double, TParameter>
        ConstantExpressionConstructor<double, TParameter>::constant(double value) {
            return new ConstantExpression(
                ColumnMatrixXd::constant(1, value),
                NumDimensions<TParameter>::Value
            );
        }

        template <int iNumDimensions, class TParameter>
        ParametricExpression<Vector<double, iNumDimensions>, TParameter>
        ConstantExpressionConstructor<Vector<double, iNumDimensions>, TParameter>::constant(
            const Vector<double, iNumDimensions>& vector
        ) {
            return new ConstantExpression(vector.components(), NumDimensions<TParameter>::Value);
        }

        template <int iNumDimensions, class TParameter>
        ParametricExpression<Point<iNumDimensions>, TParameter>
        ConstantExpressionConstructor<Point<iNumDimensions>, TParameter>::constant(
            const Point<iNumDimensions>& point
        ) {
            return new ConstantExpression(point.components(), NumDimensions<TParameter>::Value);
        }

        template <class TValue>
        ParametricExpression<TValue, TValue>
        IdentityExpressionConstructor<TValue, TValue>::identity() {
            return new IdentityExpression(NumDimensions<TValue>::Value);
        }

        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        FromComponentsExpressionConstructors<TValue, 2, TParameter>::fromComponents(
            const ParametricExpression<double, TParameter>& x,
            const ParametricExpression<double, TParameter>& y
        ) {
            return x.implementation()->concatenated(y.implementation());
        }

        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        FromComponentsExpressionConstructors<TValue, 2, TParameter>::fromComponents(
            const ParametricExpression<double, TParameter>& x,
            double y
        ) {
            ExpressionImplementationPtr yImplementation(
                new ConstantExpression(y, NumDimensions<TParameter>::Value)
            );
            return x.implementation()->concatenated(yImplementation);
        }

        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        FromComponentsExpressionConstructors<TValue, 2, TParameter>::fromComponents(
            double x,
            const ParametricExpression<double, TParameter>& y
        ) {
            ExpressionImplementationPtr xImplementation(
                new ConstantExpression(x, NumDimensions<TParameter>::Value)
            );
            return xExpression.implementation()->concatenated(yImplementation);
        }

        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        FromComponentsExpressionConstructors<TValue, 3, TParameter>::fromComponents(
            const ParametricExpression<double, TParameter>& x,
            const ParametricExpression<double, TParameter>& y,
            const ParametricExpression<double, TParameter>& z
        ) {
            return x.implementation()->concatenated(y.implementation())->concatenated(
                z.implementation()
            );
        }

        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        FromComponentsExpressionConstructors<TValue, 3, TParameter>::fromComponents(
            const ParametricExpression<double, TParameter>& x,
            const ParametricExpression<double, TParameter>& y,
            double z
        ) {
            ExpressionImplementationPtr zImplementation(
                new ConstantExpression(z, NumDimensions<TParameter>::Value)
            );
            return x.implementation()->concatenated(y.implementation())->concatenated(
                zImplementation
            );
        }
        
        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        FromComponentsExpressionConstructors<TValue, 3, TParameter>::fromComponents(
            const ParametricExpression<double, TParameter>& x,
            double y,
            const ParametricExpression<double, TParameter>& z
        ) {
            ExpressionImplementationPtr yImplementation(
                new ConstantExpression(y, NumDimensions<TParameter>::Value)
            );
            return x.implementation()->concatenated(yImplementation)->concatenated(
                z.implementation()
            );
        }
        
        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        FromComponentsExpressionConstructors<TValue, 3, TParameter>::fromComponents(
            double x,
            const ParametricExpression<double, TParameter>& y,
            const ParametricExpression<double, TParameter>& z
        ) {
            ExpressionImplementationPtr xImplementation(
                new ConstantExpression(x, NumDimensions<TParameter>::Value)
            );
            return xImplementation->concatenated(y.implementation())->concatenated(
                z.implementation()
            );
        }
        
        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        FromComponentsExpressionConstructors<TValue, 3, TParameter>::fromComponents(
            const ParametricExpression<double, TParameter>& x,
            double y,
            double z
        ) {
            ExpressionImplementationPtr yImplementation(
                new ConstantExpression(y, NumDimensions<TParameter>::Value)
            );
            ExpressionImplementationPtr zImplementation(
                new ConstantExpression(z, NumDimensions<TParameter>::Value)
            );
            return x.implementation()->concatenated(yImplementation)->concatenated(zImplementation);
        }
        
        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        FromComponentsExpressionConstructors<TValue, 3, TParameter>::fromComponents(
            double x,
            const ParametricExpression<double, TParameter>& y,
            double z
        ) {
            ExpressionImplementationPtr xImplementation(
                new ConstantExpression(x, NumDimensions<TParameter>::Value)
            );
            ExpressionImplementationPtr zImplementation(
                new ConstantExpression(z, NumDimensions<TParameter>::Value)
            );
            return xImplementation->concatenated(y.implementation())->concatenated(zImplementation);
        }
        
        template <class TValue, class TParameter>
        ParametricExpression<TValue, TParameter>
        FromComponentsExpressionConstructors<TValue, 3, TParameter>::fromComponents(
            double x,
            double y,
            const ParametricExpression<double, TParameter>& z
        ) {
            ExpressionImplementationPtr xImplementation(
                new ConstantExpression(x, NumDimensions<TParameter>::Value)
            );
            ExpressionImplementationPtr yImplementation(
                new ConstantExpression(y, NumDimensions<TParameter>::Value)
            );
            return xImplementation->concatenated(yImplementation)->concatenated(z.implementation());
        }
    }
}
