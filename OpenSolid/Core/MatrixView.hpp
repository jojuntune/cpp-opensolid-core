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

#include <OpenSolid/Core/MatrixView.definitions.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Matrix/ColStride.hpp>
#include <OpenSolid/Core/Matrix/MatrixDimensions.hpp>
#include <OpenSolid/Core/Matrix/MatrixInterface.hpp>

namespace opensolid
{
    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    MatrixView<TScalar, iRows, iCols, iColStride>::MatrixView(TScalar* sourcePtr) :
        _data(sourcePtr) {
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    MatrixView<TScalar, iRows, iCols, iColStride>::MatrixView(TScalar* sourcePtr, int size) :
        detail::MatrixDimensions<iRows, iCols>(size),
        _data(sourcePtr) {
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    MatrixView<TScalar, iRows, iCols, iColStride>::MatrixView(
        TScalar* sourcePtr,
        int rows,
        int cols
    ) : detail::MatrixDimensions<iRows, iCols>(rows, cols),
        _data(sourcePtr) {
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    MatrixView<TScalar, iRows, iCols, iColStride>::MatrixView(
        TScalar* sourcePtr,
        int rows,
        int cols,
        int colStride
    ) : detail::MatrixDimensions<iRows, iCols>(rows, cols),
        detail::ColStride<iColStride>(colStride),
        _data(sourcePtr) {
    }

    template <class TScalar, int iRows, int iCols, int iColStride> template <class TOtherDerived>
    inline
    void
    MatrixView<TScalar, iRows, iCols, iColStride>::operator=(
        const detail::MatrixInterface<TOtherDerived>& other
    ) {
        detail::MatrixInterface<MatrixView<TScalar, iRows, iCols, iColStride>>::operator=(other);
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    const TScalar*
    MatrixView<TScalar, iRows, iCols, iColStride>::data() const {
        return _data;
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    TScalar*
    MatrixView<TScalar, iRows, iCols, iColStride>::data() {
        return _data;
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    int
    MatrixView<TScalar, iRows, iCols, iColStride>::rows() const {
        return detail::MatrixDimensions<iRows, iCols>::rows();
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    int
    MatrixView<TScalar, iRows, iCols, iColStride>::cols() const {
        return detail::MatrixDimensions<iRows, iCols>::cols();
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    int
    MatrixView<TScalar, iRows, iCols, iColStride>::size() const {
        return detail::MatrixDimensions<iRows, iCols>::size();
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    int
    MatrixView<TScalar, iRows, iCols, iColStride>::colStride() const {
        return detail::ColStride<iColStride>::colStride();
    }
}
