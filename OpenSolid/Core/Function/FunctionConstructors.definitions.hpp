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

#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Function.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumParameters>
    class ZeroFunctionConstructor
    {
    public:
        static Function<iNumDimensions, iNumParameters>
        Zero();
    };

    template <int iNumDimensions, int iNumParameters>
    class ConstantFunctionConstructor
    {
    public:
        static Function<iNumDimensions, iNumParameters>
        Constant(const Matrix<double, iNumDimensions, 1>& value);
    };

    template <int iNumParameters>
    class ConstantFunctionConstructor<1, iNumParameters>
    {
    public:
        static Function<1, iNumParameters>
        Constant(double value);
    };

    template <int iNumDimensions, int iNumParameters>
    class IdentityFunctionConstructor
    {
    };

    template <int iNumDimensions>
    class IdentityFunctionConstructor<iNumDimensions, iNumDimensions>
    {
    public:
        static Function<iNumDimensions, iNumDimensions>
        Identity();
    };

    template <int iNumDimensions, int iNumParameters>
    class ParameterFunctionConstructor
    {
    };

    template <int iNumParameters>
    class ParameterFunctionConstructor<1, iNumParameters>
    {
    public:
        static Function<1, iNumParameters>
        Parameter(int parameterIndex);
    };

    template <int iNumDimensions, int iNumParameters>
    class NamedParameterFunctionConstructors
    {
    };

    template <>
    class NamedParameterFunctionConstructors<1, 1>
    {
    public:
        static Function<1, 1>
        t();
    };

    template <>
    class NamedParameterFunctionConstructors<1, 2>
    {
    public:
        static Function<1, 2>
        u();

        static Function<1, 2>
        v();
    };

    template <int iNumDimensions, int iNumParameters>
    class FromComponentsFunctionConstructors
    {
    };

    template <int iNumParameters>
    class FromComponentsFunctionConstructors<2, iNumParameters>
    {
    public:
        static Function<2, iNumParameters>
        FromComponents(
            const Function<1, iNumParameters>& x,
            const Function<1, iNumParameters>& y
        );

        static Function<2, iNumParameters>
        FromComponents(
            const Function<1, iNumParameters>& x,
            double y
        );

        static Function<2, iNumParameters>
        FromComponents(
            double x,
            const Function<1, iNumParameters>& y
        );
    };

    template <int iNumParameters>
    class FromComponentsFunctionConstructors<3, iNumParameters>
    {
    public:
        static Function<3, iNumParameters>
        FromComponents(
            const Function<1, iNumParameters>& x,
            const Function<1, iNumParameters>& y,
            const Function<1, iNumParameters>& z
        );

        static Function<3, iNumParameters>
        FromComponents(
            const Function<1, iNumParameters>& x,
            const Function<1, iNumParameters>& y,
            double z
        );
        
        static Function<3, iNumParameters>
        FromComponents(
            const Function<1, iNumParameters>& x,
            double y,
            const Function<1, iNumParameters>& z
        );
        
        static Function<3, iNumParameters>
        FromComponents(
            double x,
            const Function<1, iNumParameters>& y,
            const Function<1, iNumParameters>& z
        );
        
        static Function<3, iNumParameters>
        FromComponents(
            const Function<1, iNumParameters>& x,
            double y,
            double z
        );
        
        static Function<3, iNumParameters>
        FromComponents(
            double x,
            const Function<1, iNumParameters>& y,
            double z
        );
        
        static Function<3, iNumParameters>
        FromComponents(
            double x,
            double y,
            const Function<1, iNumParameters>& z
        );
    };

    template <int iNumDimensions, int iNumParameters>
    class LinearFunctionConstructors
    {
    public:
        static Function<iNumDimensions, iNumParameters>
        Linear(const CoordinateSystem<iNumDimensions, iNumParameters>& coordinateSystem);
    };

    template <int iNumDimensions, int iNumParameters>
    class FunctionConstructors :
        public ZeroFunctionConstructor<iNumDimensions, iNumParameters>,
        public ConstantFunctionConstructor<iNumDimensions, iNumParameters>,
        public IdentityFunctionConstructor<iNumDimensions, iNumParameters>,
        public ParameterFunctionConstructor<iNumDimensions, iNumParameters>,
        public NamedParameterFunctionConstructors<iNumDimensions, iNumParameters>,
        public FromComponentsFunctionConstructors<iNumDimensions, iNumParameters>,
        public LinearFunctionConstructors<iNumDimensions, iNumParameters>
    {
    };
}
