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

#include <OpenSolid/Core/Matrix/MatrixDeterminantFunction.declarations.hpp>

#include <OpenSolid/Core/Matrix/MatrixInterface.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <>
        struct MatrixDeterminantFunction<1, 1>
        {
            template <class TDerived>
            typename MatrixTraits<TDerived>::PlainScalarType
            operator()(const MatrixInterface<TDerived>& matrix) const;
        };

        template <>
        struct MatrixDeterminantFunction<2, 2>
        {
            template <class TDerived>
            typename MatrixTraits<TDerived>::PlainScalarType
            operator()(const MatrixInterface<TDerived>& matrix) const;
        };

        template <>
        struct MatrixDeterminantFunction<3, 3>
        {
            template <class TDerived>
            typename MatrixTraits<TDerived>::PlainScalarType
            operator()(const MatrixInterface<TDerived>& matrix) const;
        };

        template <int iNumRows>
        struct MatrixDeterminantFunction<iNumRows, -1> :
            public MatrixDeterminantFunction<iNumRows, iNumRows>
        {
        };

        template <int iNumColumns>
        struct MatrixDeterminantFunction<-1, iNumColumns> :
            public MatrixDeterminantFunction<iNumColumns, iNumColumns>
        {
        };

        template <>
        struct MatrixDeterminantFunction<-1, -1>
        {
            template <class TDerived>
            typename MatrixTraits<TDerived>::PlainScalarType
            operator()(const MatrixInterface<TDerived>& matrix) const;
        };
    }
}
