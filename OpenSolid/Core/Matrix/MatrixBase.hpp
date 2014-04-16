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
        template <class TScalar, int iRows, int iCols>
        inline
        MatrixBase<TScalar, iRows, iCols>::MatrixBase() :
            _data() {
        }

        template <class TScalar, int iRows, int iCols>
        inline
        MatrixBase<TScalar, iRows, iCols>::MatrixBase(int size) :
            _data() {

            static_assert(
                iRows == 1 || iCols == 1,
                "Only row or column matrices can be initialized with a single size"
            );

            assert((iRows == 1 && size == iCols) || (iCols == 1 && size == iRows));
        }

        template <class TScalar, int iRows, int iCols>
        inline
        MatrixBase<TScalar, iRows, iCols>::MatrixBase(int rows, int cols) :
            _data() {

            assert(rows == iRows);
            assert(cols == iCols);
        }

        template <class TScalar, int iRows, int iCols>
        inline
        const TScalar*
        MatrixBase<TScalar, iRows, iCols>::data() const {
            return _data;
        }

        template <class TScalar, int iRows, int iCols>
        inline
        TScalar*
        MatrixBase<TScalar, iRows, iCols>::data() {
            return _data;
        }

        template <class TScalar, int iRows, int iCols>
        inline
        int
        MatrixBase<TScalar, iRows, iCols>::rows() const {
            return iRows;
        }

        template <class TScalar, int iRows, int iCols>
        inline
        int
        MatrixBase<TScalar, iRows, iCols>::cols() const {
            return iCols;
        }

        template <class TScalar, int iRows, int iCols>
        inline
        int
        MatrixBase<TScalar, iRows, iCols>::size() const {
            return iRows * iCols;
        }

        template <class TScalar, int iRows, int iCols>
        inline
        int
        MatrixBase<TScalar, iRows, iCols>::colStride() const {
            return iRows;
        }

        template <class TScalar, int iRows>
        inline
        MatrixBase<TScalar, iRows, -1>::MatrixBase(int cols) :
            _data(std::size_t(iRows * cols)),
            _cols(cols) {

            static_assert(
                iRows == 1,
                "Only row or column matrices can be initialized with a single size"
            );

            assert(cols > 0);
        }

        template <class TScalar, int iRows>
        inline
        MatrixBase<TScalar, iRows, -1>::MatrixBase(int rows, int cols) :
            _data(std::size_t(iRows * cols)),
            _cols(cols) {

            assert(rows == iRows);
            assert(cols > 0);
        }

        template <class TScalar, int iRows>
        inline
        const TScalar*
        MatrixBase<TScalar, iRows, -1>::data() const {
            return _data.data();
        }

        template <class TScalar, int iRows>
        inline
        TScalar*
        MatrixBase<TScalar, iRows, -1>::data() {
            return _data.data();
        }

        template <class TScalar, int iRows>
        inline
        int
        MatrixBase<TScalar, iRows, -1>::rows() const {
            return iRows;
        }

        template <class TScalar, int iRows>
        inline
        int
        MatrixBase<TScalar, iRows, -1>::cols() const {
            return _cols;
        }

        template <class TScalar, int iRows>
        inline
        int
        MatrixBase<TScalar, iRows, -1>::size() const {
            return int(_data.size());
        }

        template <class TScalar, int iRows>
        inline
        int
        MatrixBase<TScalar, iRows, -1>::colStride() const {
            return iRows;
        }

        template <class TScalar, int iCols>
        inline
        MatrixBase<TScalar, -1, iCols>::MatrixBase(int rows) :
            _data(std::size_t(rows * iCols)),
            _rows(rows) {

            static_assert(
                iCols == 1,
                "Only row or column matrices can be initialized with a single size"
            );

            assert(rows > 0);
        }

        template <class TScalar, int iCols>
        inline
        MatrixBase<TScalar, -1, iCols>::MatrixBase(int rows, int cols) :
            _data(std::size_t(rows * iCols)),
            _rows(rows) {

            assert(rows > 0);
            assert(cols == iCols);
        }

        template <class TScalar, int iCols>
        inline
        const TScalar*
        MatrixBase<TScalar, -1, iCols>::data() const {
            return _data.data();
        }

        template <class TScalar, int iCols>
        inline
        TScalar*
        MatrixBase<TScalar, -1, iCols>::data() {
            return _data.data();
        }

        template <class TScalar, int iCols>
        inline
        int
        MatrixBase<TScalar, -1, iCols>::rows() const {
            return _rows;
        }

        template <class TScalar, int iCols>
        inline
        int
        MatrixBase<TScalar, -1, iCols>::cols() const {
            return iCols;
        }

        template <class TScalar, int iCols>
        inline
        int
        MatrixBase<TScalar, -1, iCols>::size() const {
            return int(_data.size());
        }

        template <class TScalar, int iCols>
        inline
        int
        MatrixBase<TScalar, -1, iCols>::colStride() const {
            return _rows;
        }

        template <class TScalar>
        inline
        MatrixBase<TScalar, -1, -1>::MatrixBase(int rows, int cols) :
            _data(std::size_t(rows * cols)),
            _rows(rows),
            _cols(cols) {

            assert(rows > 0);
            assert(cols > 0);
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
        MatrixBase<TScalar, -1, -1>::rows() const {
            return _rows;
        }

        template <class TScalar>
        inline
        int
        MatrixBase<TScalar, -1, -1>::cols() const {
            return _cols;
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
        MatrixBase<TScalar, -1, -1>::colStride() const {
            return _rows;
        }
    }
}

// Restore Visual Studio warning state
#ifdef _MSC_VER
#pragma warning(pop)
#endif
