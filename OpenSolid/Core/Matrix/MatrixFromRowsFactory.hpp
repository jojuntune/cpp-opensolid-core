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

#include <OpenSolid/Core/Matrix/MatrixFromRowsFactory.definitions.hpp>

#include <OpenSolid/Core/Matrix.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumColumns>
        const typename MatrixType<TScalar, 2, iNumColumns>::Type
        MatrixFromRowsFactory<TScalar, 2, iNumColumns>::FromRows(
            const typename MatrixType<TScalar, 1, iNumColumns>::Type& firstRow,
            const typename MatrixType<TScalar, 1, iNumColumns>::Type& secondRow
        ) {
            typename MatrixType<TScalar, 2, iNumColumns>::Type result;
            for (std::int64_t columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
                result(0, columnIndex) = firstRow(columnIndex);
                result(1, columnIndex) = secondRow(columnIndex);
            }
            return result;
        }

        template <class TScalar, int iNumColumns>
        const typename MatrixType<TScalar, 3, iNumColumns>::Type
        MatrixFromRowsFactory<TScalar, 3, iNumColumns>::FromRows(
            const typename MatrixType<TScalar, 1, iNumColumns>::Type& firstRow,
            const typename MatrixType<TScalar, 1, iNumColumns>::Type& secondRow,
            const typename MatrixType<TScalar, 1, iNumColumns>::Type& thirdRow
        ) {
            typename MatrixType<TScalar, 3, iNumColumns>::Type result;
            for (std::int64_t columnIndex = 0; columnIndex < iNumColumns; ++columnIndex) {
                result(0, columnIndex) = firstRow(columnIndex);
                result(1, columnIndex) = secondRow(columnIndex);
                result(2, columnIndex) = thirdRow(columnIndex);
            }
            return result;
        }
    }
}
