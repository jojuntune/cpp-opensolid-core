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

#include <OpenSolid/Core/MatrixView.definitions.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Matrix/MatrixInterface.hpp>

namespace opensolid
{
    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::MatrixView(TScalar* sourcePtr) :
        _data(sourcePtr),
        _numRows(iNumRows),
        _numColumns(iNumColumns),
        _size(iNumRows * iNumColumns),
        _columnStride(iColumnStride) {

        static_assert(iNumRows > 0, "Number of rows must be provided");
        static_assert(iNumColumns > 0, "Number of columns must be provided");
        static_assert(iColumnStride >= 0, "Column stride must be provided");
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::MatrixView(
        TScalar* sourcePtr,
        int size
    ) : _data(sourcePtr),
        _numRows(iNumRows == 1 ? 1 : size),
        _numColumns(iNumColumns == 1 ? 1 : size),
        _size(size),
        _columnStride(iColumnStride) {

        static_assert(
            iNumRows == 1 || iNumColumns == 1,
            "Only row or column matrix views can be initialized with a single size"
        );
        static_assert(iColumnStride >= 0, "Column stride must be provided");

        assert(
            (iNumRows == 1 && (size == iNumColumns || iNumColumns == -1)) ||
            (iNumColumns == 1 && (size == iNumRows || iNumRows == -1))
        );

        assert(size > 0);
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::MatrixView(
        TScalar* sourcePtr,
        int numRows,
        int numColumns
    ) : _data(sourcePtr),
        _numRows(numRows),
        _numColumns(numColumns),
        _size(numRows * numColumns),
        _columnStride(iColumnStride) {

        static_assert(iColumnStride >= 0, "Column stride must be provided");

        assert(numRows == iNumRows || iNumRows == -1);
        assert(numColumns == iNumColumns || iNumColumns == -1);

        assert(numRows > 0);
        assert(numColumns > 0);
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::MatrixView(
        TScalar* sourcePtr,
        int numRows,
        int numColumns,
        int columnStride
    ) : _data(sourcePtr),
        _numRows(numRows),
        _numColumns(numColumns),
        _size(numRows * numColumns),
        _columnStride(columnStride) {

        assert(numRows == iNumRows || iNumRows == -1);
        assert(numColumns == iNumColumns || iNumColumns == -1);
        assert(columnStride == iColumnStride || iColumnStride == -1);

        assert(numRows > 0);
        assert(numColumns > 0);
        assert(columnStride >= 0);
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    template <int iOtherRows, int iOtherCols, int iOtherColStride>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::MatrixView(
        const MatrixView<TScalar, iOtherRows, iOtherCols, iOtherColStride>& other
    ) : _data(other.data()),
        _numRows(other.numRows()),
        _numColumns(other.numColumns()),
        _size(other.size()),
        _columnStride(other.columnStride()) {

        detail::CheckCompatibleSizes<iNumRows, iOtherRows> staticRowCheck;
        detail::CheckCompatibleSizes<iNumColumns, iOtherCols> staticColCheck;
        detail::CheckCompatibleSizes<iColumnStride, iOtherColStride> staticColStrideCheck;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    void
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::operator=(
        const MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>& other
    ) {
        this->assign(other);
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    template <class TOtherDerived>
    inline
    void
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::operator=(
        const detail::MatrixInterface<TOtherDerived>& other
    ) {
        this->assign(other);
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    const TScalar*
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::data() const {
        return _data;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    TScalar*
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::data() {
        return _data;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    int
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::numRows() const {
        return _numRows;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    int
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::numColumns() const {
        return _numColumns;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    int
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::size() const {
        return _size;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    inline
    int
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>::columnStride() const {
        return _columnStride;
    }
}
