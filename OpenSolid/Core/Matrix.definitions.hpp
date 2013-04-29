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

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct NumDimensions<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        static const int Value = iRows;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols, int iNumResultDimensions>
    struct ChangeDimensions<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>, iNumResultDimensions>
    {
        typedef Matrix<TScalar, iNumResultDimensions, iCols, iOptions, iNumResultDimensions, iMaxCols> Type;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct ScalingFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
        operator()(
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
            double scale
        ) const;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct TranslationFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        template <class TVector>
        const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>&
        operator()(
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols, int iNumTransformedDimensions>
    struct TransformationFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>, iNumTransformedDimensions>
    {
        template <class TMatrix>
        Matrix<TScalar, iNumTransformedDimensions, iCols, iOptions, iNumTransformedDimensions, iMaxCols>
        operator()(
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct BoundsType<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        typedef Matrix<Interval, iRows, iCols, iOptions, iMaxRows, iMaxCols> Type;
    };

    template <class TScalar, int iRows, int iCols, int iOptions, int iMaxRows, int iMaxCols>
    struct BoundsFunction<Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>>
    {
        typedef typename internal::conditional<
            internal::is_same<TScalar, Interval>::value,
            const Matrix<Interval, iRows, iCols, iOptions, iMaxRows, iMaxCols>&,
            const CwiseUnaryOp<
                internal::scalar_cast_op<TScalar, Interval>,
                const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>
            >
        >::type CastType;

        CastType
        operator()(
            const Matrix<TScalar, iRows, iCols, iOptions, iMaxRows, iMaxCols>& argument
        ) const;
    };
}
