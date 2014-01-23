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

#include <OpenSolid/Core/Matrix/MatrixFromColumnsFactory.definitions.hpp>

#include <OpenSolid/Core/Matrix.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumRows>
        const typename MatrixType<TScalar, iNumRows, 2>::Type
        MatrixFromColumnsFactory<TScalar, iNumRows, 2>::FromColumns(
            const typename MatrixType<TScalar, iNumRows, 1>::Type& firstColumn,
            const typename MatrixType<TScalar, iNumRows, 1>::Type& secondColumn
        ) {
            typename MatrixType<TScalar, iNumRows, 2>::Type result;
            for (std::int64_t rowIndex = 0; rowIndex < iNumColumns; ++rowIndex) {
                result(rowIndex, 0) = firstColumn(rowIndex);
                result(rowIndex, 1) = secondColumn(rowIndex);
            }
            return result;
        }

        template <class TScalar, int iNumRows>
        const typename MatrixType<TScalar, iNumRows, 3>::Type
        MatrixFromColumnsFactory<TScalar, iNumRows, 3>::FromColumns(
            const typename MatrixType<TScalar, iNumRows, 1>::Type& firstColumn,
            const typename MatrixType<TScalar, iNumRows, 1>::Type& secondColumn,
            const typename MatrixType<TScalar, iNumRows, 1>::Type& thirdColumn
        ) {
            typename MatrixType<TScalar, iNumRows, 3>::Type result;
            for (std::int64_t rowIndex = 0; rowIndex < iNumColumns; ++rowIndex) {
                result(rowIndex, 0) = firstColumn(rowIndex);
                result(rowIndex, 1) = secondColumn(rowIndex);
                result(rowIndex, 2) = thirdColumn(rowIndex);
            }
            return result;
        }
    }
}
