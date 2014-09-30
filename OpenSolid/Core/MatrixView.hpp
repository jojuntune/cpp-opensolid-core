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
    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::MatrixView(
        TScalar* sourcePtr
    ) : _data(sourcePtr),
        _numRows(iNumRows),
        _numColumns(iNumColumns),
        _numComponents(iNumRows * iNumColumns),
        _columnStrideInBytes(iColumnStrideInBytes) {

        static_assert(iNumRows > 0, "Number of rows must be provided");
        static_assert(iNumColumns > 0, "Number of columns must be provided");
        static_assert(iColumnStrideInBytes >= 0, "Column stride must be provided");
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::MatrixView(
        TScalar* sourcePtr,
        int numComponents
    ) : _data(sourcePtr),
        _numRows(iNumRows == 1 ? 1 : numComponents),
        _numColumns(iNumColumns == 1 ? 1 : numComponents),
        _numComponents(numComponents),
        _columnStrideInBytes(iColumnStrideInBytes) {

        static_assert(
            iNumRows == 1 || iNumColumns == 1,
            "Only row or column matrix views can be initialized with a single number of components"
        );
        static_assert(iColumnStrideInBytes >= 0, "Column stride must be provided");

        assert(
            (iNumRows == 1 && (numComponents == iNumColumns || iNumColumns == -1)) ||
            (iNumColumns == 1 && (numComponents == iNumRows || iNumRows == -1))
        );

        assert(numComponents > 0);
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::MatrixView(
        TScalar* sourcePtr,
        int numRows,
        int numColumns
    ) : _data(sourcePtr),
        _numRows(numRows),
        _numColumns(numColumns),
        _numComponents(numRows * numColumns),
        _columnStrideInBytes(iColumnStrideInBytes) {

        static_assert(iColumnStrideInBytes >= 0, "Column stride must be provided");

        assert(numRows == iNumRows || iNumRows == -1);
        assert(numColumns == iNumColumns || iNumColumns == -1);

        assert(numRows > 0);
        assert(numColumns > 0);
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::MatrixView(
        TScalar* sourcePtr,
        int numRows,
        int numColumns,
        int columnStrideInBytes
    ) : _data(sourcePtr),
        _numRows(numRows),
        _numColumns(numColumns),
        _numComponents(numRows * numColumns),
        _columnStrideInBytes(columnStrideInBytes) {

        assert(numRows == iNumRows || iNumRows == -1);
        assert(numColumns == iNumColumns || iNumColumns == -1);
        assert(columnStrideInBytes == iColumnStrideInBytes || iColumnStrideInBytes == -1);

        assert(numRows >= 0);
        assert(numColumns >= 0);
        assert(columnStrideInBytes >= 0);
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    template <class TOtherScalar, int iOtherRows, int iOtherColumns, int iOtherColumnStrideInBytes>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::MatrixView(
        const MatrixView<TOtherScalar, iOtherRows, iOtherColumns, iOtherColumnStrideInBytes>& other
    ) : _data(other.data()),
        _numRows(other.numRows()),
        _numColumns(other.numColumns()),
        _numComponents(other.numComponents()),
        _columnStrideInBytes(other.columnStrideInBytes()) {

        detail::CheckCompatibleSizes<iNumRows, iOtherRows>();
        detail::CheckCompatibleSizes<iNumColumns, iOtherColumns>();
        detail::CheckCompatibleSizes<iColumnStrideInBytes, iOtherColumnStrideInBytes>();
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    template <class TOtherScalar, int iOtherRows, int iOtherColumns, int iOtherColumnStrideInBytes>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::MatrixView(
        MatrixView<TOtherScalar, iOtherRows, iOtherColumns, iOtherColumnStrideInBytes>& other
    ) : _data(other.data()),
        _numRows(other.numRows()),
        _numColumns(other.numColumns()),
        _numComponents(other.numComponents()),
        _columnStrideInBytes(other.columnStrideInBytes()) {

        detail::CheckCompatibleSizes<iNumRows, iOtherRows>();
        detail::CheckCompatibleSizes<iNumColumns, iOtherColumns>();
        detail::CheckCompatibleSizes<iColumnStrideInBytes, iOtherColumnStrideInBytes>();
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    template <class TOtherScalar, int iOtherRows, int iOtherColumns, int iOtherColumnStrideInBytes>
    inline
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::MatrixView(
        MatrixView<TOtherScalar, iOtherRows, iOtherColumns, iOtherColumnStrideInBytes>&& other
    ) : _data(other.data()),
        _numRows(other.numRows()),
        _numColumns(other.numColumns()),
        _numComponents(other.numComponents()),
        _columnStrideInBytes(other.columnStrideInBytes()) {

        detail::CheckCompatibleSizes<iNumRows, iOtherRows>();
        detail::CheckCompatibleSizes<iNumColumns, iOtherColumns>();
        detail::CheckCompatibleSizes<iColumnStrideInBytes, iOtherColumnStrideInBytes>();
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    void
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::operator=(
        const MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>& other
    ) {
        this->assign(other);
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    template <class TOtherDerived>
    inline
    void
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::operator=(
        const detail::MatrixInterface<TOtherDerived>& other
    ) {
        this->assign(other);
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    const TScalar*
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::data() const {
        return _data;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    TScalar*
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::data() {
        return _data;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    int
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::numRows() const {
        return _numRows;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    int
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::numColumns() const {
        return _numColumns;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    int
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::numComponents() const {
        return _numComponents;
    }

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStrideInBytes>
    inline
    int
    MatrixView<TScalar, iNumRows, iNumColumns, iColumnStrideInBytes>::columnStrideInBytes() const {
        return _columnStrideInBytes;
    }
}
