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
#include <OpenSolid/Core/Matrix/MatrixInterface.hpp>

namespace opensolid
{
    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    MatrixView<TScalar, iRows, iCols, iColStride>::MatrixView(TScalar* sourcePtr) :
        _data(sourcePtr),
        _rows(iRows),
        _cols(iCols),
        _size(iRows * iCols),
        _colStride(iColStride) {

        static_assert(iRows > 0, "Number of rows must be provided");
        static_assert(iCols > 0, "Number of columns must be provided");
        static_assert(iColStride >= 0, "Column stride must be provided");
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    MatrixView<TScalar, iRows, iCols, iColStride>::MatrixView(TScalar* sourcePtr, int size) :
        _data(sourcePtr),
        _rows(iRows == 1 ? 1 : size),
        _cols(iCols == 1 ? 1 : size),
        _size(size),
        _colStride(iColStride) {

        static_assert(
            iRows == 1 || iCols == 1,
            "Only row or column matrix views can be initialized with a single size"
        );
        static_assert(iColStride >= 0, "Column stride must be provided");

        assert(
            (iRows == 1 && (size == iCols || iCols == -1)) ||
            (iCols == 1 && (size == iRows || iRows == -1))
        );

        assert(size > 0);
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    MatrixView<TScalar, iRows, iCols, iColStride>::MatrixView(
        TScalar* sourcePtr,
        int rows,
        int cols
    ) : _data(sourcePtr),
        _rows(rows),
        _cols(cols),
        _size(rows * cols),
        _colStride(iColStride) {

        static_assert(iColStride >= 0, "Column stride must be provided");

        assert(rows == iRows || iRows == -1);
        assert(cols == iCols || iCols == -1);

        assert(rows > 0);
        assert(cols > 0);
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    MatrixView<TScalar, iRows, iCols, iColStride>::MatrixView(
        TScalar* sourcePtr,
        int rows,
        int cols,
        int colStride
    ) : _data(sourcePtr),
        _rows(rows),
        _cols(cols),
        _size(rows * cols),
        _colStride(colStride) {

        assert(rows == iRows || iRows == -1);
        assert(cols == iCols || iCols == -1);
        assert(colStride == iColStride || iColStride == -1);

        assert(rows > 0);
        assert(cols > 0);
        assert(colStride >= 0);
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    template <int iOtherRows, int iOtherCols, int iOtherColStride>
    inline
    MatrixView<TScalar, iRows, iCols, iColStride>::MatrixView(
        const MatrixView<TScalar, iOtherRows, iOtherCols, iOtherColStride>& other
    ) : _data(other.data()),
        _rows(other.rows()),
        _cols(other.cols()),
        _size(other.size()),
        _colStride(other.colStride()) {

        detail::CheckCompatibleSizes<iRows, iOtherRows> staticRowCheck;
        detail::CheckCompatibleSizes<iCols, iOtherCols> staticColCheck;
        detail::CheckCompatibleSizes<iColStride, iOtherColStride> staticColStrideCheck;
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
        return _rows;
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    int
    MatrixView<TScalar, iRows, iCols, iColStride>::cols() const {
        return _cols;
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    int
    MatrixView<TScalar, iRows, iCols, iColStride>::size() const {
        return _size;
    }

    template <class TScalar, int iRows, int iCols, int iColStride>
    inline
    int
    MatrixView<TScalar, iRows, iCols, iColStride>::colStride() const {
        return _colStride;
    }
}
