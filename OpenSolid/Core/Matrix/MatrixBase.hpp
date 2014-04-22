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

#include <OpenSolid/Core/Matrix/MatrixBase.definitions.hpp>

#include <OpenSolid/Core/Matrix/MatrixInterface.hpp>

#include <cassert>

// Disable warning C4351 (Visual Studio warning that _data array will in fact be value-initialized
// as specified in the C++ standard; previous versions of Visual Studio did not always
// value-initialize as required)
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4351)
#endif

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        MatrixBase<TScalar, iNumRows, iNumColumns>::MatrixBase() :
            _data() {
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        MatrixBase<TScalar, iNumRows, iNumColumns>::MatrixBase(int size) :
            _data() {

            static_assert(
                iNumRows == 1 || iNumColumns == 1,
                "Only row or column matrices can be initialized with a single size"
            );

            assert(
                (iNumRows == 1 && size == iNumColumns) || (iNumColumns == 1 && size == iNumRows)
            );
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        MatrixBase<TScalar, iNumRows, iNumColumns>::MatrixBase(int numRows, int numColumns) :
            _data() {

            assert(numRows == iNumRows);
            assert(numColumns == iNumColumns);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar*
        MatrixBase<TScalar, iNumRows, iNumColumns>::data() const {
            return _data;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar*
        MatrixBase<TScalar, iNumRows, iNumColumns>::data() {
            return _data;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        int
        MatrixBase<TScalar, iNumRows, iNumColumns>::numRows() const {
            return iNumRows;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        int
        MatrixBase<TScalar, iNumRows, iNumColumns>::numColumns() const {
            return iNumColumns;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        int
        MatrixBase<TScalar, iNumRows, iNumColumns>::size() const {
            return iNumRows * iNumColumns;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        int
        MatrixBase<TScalar, iNumRows, iNumColumns>::columnStride() const {
            return iNumRows;
        }

        template <class TScalar, int iNumRows>
        inline
        MatrixBase<TScalar, iNumRows, -1>::MatrixBase(int numColumns) :
            _data(std::size_t(iNumRows * numColumns)),
            _numColumns(numColumns) {

            static_assert(
                iNumRows == 1,
                "Only row or column matrices can be initialized with a single size"
            );

            assert(numColumns > 0);
        }

        template <class TScalar, int iNumRows>
        inline
        MatrixBase<TScalar, iNumRows, -1>::MatrixBase(int numRows, int numColumns) :
            _data(std::size_t(iNumRows * numColumns)),
            _numColumns(numColumns) {

            assert(numRows == iNumRows);
            assert(numColumns > 0);
        }

        template <class TScalar, int iNumRows>
        inline
        const TScalar*
        MatrixBase<TScalar, iNumRows, -1>::data() const {
            return _data.data();
        }

        template <class TScalar, int iNumRows>
        inline
        TScalar*
        MatrixBase<TScalar, iNumRows, -1>::data() {
            return _data.data();
        }

        template <class TScalar, int iNumRows>
        inline
        int
        MatrixBase<TScalar, iNumRows, -1>::numRows() const {
            return iNumRows;
        }

        template <class TScalar, int iNumRows>
        inline
        int
        MatrixBase<TScalar, iNumRows, -1>::numColumns() const {
            return _numColumns;
        }

        template <class TScalar, int iNumRows>
        inline
        int
        MatrixBase<TScalar, iNumRows, -1>::size() const {
            return int(_data.size());
        }

        template <class TScalar, int iNumRows>
        inline
        int
        MatrixBase<TScalar, iNumRows, -1>::columnStride() const {
            return iNumRows;
        }

        template <class TScalar, int iNumColumns>
        inline
        MatrixBase<TScalar, -1, iNumColumns>::MatrixBase(int numRows) :
            _data(std::size_t(numRows * iNumColumns)),
            _numRows(numRows) {

            static_assert(
                iNumColumns == 1,
                "Only row or column matrices can be initialized with a single size"
            );

            assert(numRows > 0);
        }

        template <class TScalar, int iNumColumns>
        inline
        MatrixBase<TScalar, -1, iNumColumns>::MatrixBase(int numRows, int numColumns) :
            _data(std::size_t(numRows * iNumColumns)),
            _numRows(numRows) {

            assert(numRows > 0);
            assert(numColumns == iNumColumns);
        }

        template <class TScalar, int iNumColumns>
        inline
        const TScalar*
        MatrixBase<TScalar, -1, iNumColumns>::data() const {
            return _data.data();
        }

        template <class TScalar, int iNumColumns>
        inline
        TScalar*
        MatrixBase<TScalar, -1, iNumColumns>::data() {
            return _data.data();
        }

        template <class TScalar, int iNumColumns>
        inline
        int
        MatrixBase<TScalar, -1, iNumColumns>::numRows() const {
            return _numRows;
        }

        template <class TScalar, int iNumColumns>
        inline
        int
        MatrixBase<TScalar, -1, iNumColumns>::numColumns() const {
            return iNumColumns;
        }

        template <class TScalar, int iNumColumns>
        inline
        int
        MatrixBase<TScalar, -1, iNumColumns>::size() const {
            return int(_data.size());
        }

        template <class TScalar, int iNumColumns>
        inline
        int
        MatrixBase<TScalar, -1, iNumColumns>::columnStride() const {
            return _numRows;
        }

        template <class TScalar>
        inline
        MatrixBase<TScalar, -1, -1>::MatrixBase(int numRows, int numColumns) :
            _data(std::size_t(numRows * numColumns)),
            _numRows(numRows),
            _numColumns(numColumns) {

            assert(numRows > 0);
            assert(numColumns > 0);
        }

        template <class TScalar>
        inline
        const TScalar*
        MatrixBase<TScalar, -1, -1>::data() const {
            return _data.data();
        }

        template <class TScalar>
        inline
        TScalar*
        MatrixBase<TScalar, -1, -1>::data() {
            return _data.data();
        }

        template <class TScalar>
        inline
        int
        MatrixBase<TScalar, -1, -1>::numRows() const {
            return _numRows;
        }

        template <class TScalar>
        inline
        int
        MatrixBase<TScalar, -1, -1>::numColumns() const {
            return _numColumns;
        }

        template <class TScalar>
        inline
        int
        MatrixBase<TScalar, -1, -1>::size() const {
            return int(_data.size());
        }

        template <class TScalar>
        inline
        int
        MatrixBase<TScalar, -1, -1>::columnStride() const {
            return _numRows;
        }
    }
}

// Restore Visual Studio warning state
#ifdef _MSC_VER
#pragma warning(pop)
#endif
