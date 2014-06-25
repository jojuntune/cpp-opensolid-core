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

namespace opensolid
{
    template <class TMatrix>
    struct MatrixTraits;

    namespace detail
    {
        template <class TDerived>
        class MatrixInterface;

        template <class TUnaryFunction, class TScalar>
        struct MappedScalarType;

        template <class TBinaryFunction, class TFirstScalar, class TSecondScalar>
        struct PairwiseMappedScalarType;

        template <class TUnaryFunction, class TMatrix>
        struct MappedMatrixType;

        template <class TBinaryFunction, class TFirstMatrix, class TSecondMatrix>
        struct PairwiseMappedMatrixType;

        template <int iFirstSize, int iSecondSize>
        struct CheckCompatibleSizes;

        template <int iFirstRows, int iSecondRows>
        struct CheckCompatibleRows;

        template <int iFirstCols, int iSecondCols>
        struct CheckCompatibleCols;

        template <class TFirstMatrix, class TSecondMatrix>
        struct CheckCompatibleMatrices;

        template <int iFirstSize, int iSecondSize>
        struct CommonSize;

        template <class TFirstMatrix, class TSecondMatrix>
        struct CommonRows;

        template <class TFirstMatrix, class TSecondMatrix>
        struct CommonCols;

        template <class TFirst, class TSecond>
        struct CommonScalar;
    }
}
