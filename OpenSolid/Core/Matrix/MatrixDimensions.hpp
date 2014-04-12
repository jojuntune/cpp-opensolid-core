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

#include <OpenSolid/Core/Matrix/MatrixDimensions.definitions.hpp>

#include <cassert>

namespace opensolid
{
    namespace detail
    {
        template <int iRows, int iCols>
        inline
        MatrixDimensions<iRows, iCols>::MatrixDimensions() {
        }

        template <int iRows, int iCols>
        inline
        MatrixDimensions<iRows, iCols>::MatrixDimensions(int size) {
            static_assert(
                iRows == 1 || iCols == 1,
                "Only row or column matrices can be initialized with a single size"
            );
            assert((iRows == 1 && size == iCols) || (iCols == 1 && size == iRows));
        }

        template <int iRows, int iCols>
        inline
        MatrixDimensions<iRows, iCols>::MatrixDimensions(int rows, int cols) {
            assert(rows == iRows);
            assert(cols == iCols);
        }

        template <int iRows, int iCols>
        inline
        int
        MatrixDimensions<iRows, iCols>::rows() const {
            return iRows;
        }

        template <int iRows, int iCols>
        inline
        int
        MatrixDimensions<iRows, iCols>::cols() const {
            return iCols;
        }

        template <int iRows, int iCols>
        inline
        int
        MatrixDimensions<iRows, iCols>::size() const {
            return iRows * iCols;
        }

        template <int iRows>
        inline
        MatrixDimensions<iRows, -1>::MatrixDimensions(int cols) :
            _cols(cols),
            _size(iRows * cols) {

            static_assert(
                iRows == 1,
                "Only row or column matrices can be initialized with a single size"
            );
            assert(cols > 0);
        }

        template <int iRows>
        inline
        MatrixDimensions<iRows, -1>::MatrixDimensions(int rows, int cols) :
            _cols(cols),
            _size(iRows * cols) {

            assert(rows == iRows);
            assert(cols > 0);
        }

        template <int iRows>
        inline
        int
        MatrixDimensions<iRows, -1>::rows() const {
            return iRows;
        }

        template <int iRows>
        inline
        int
        MatrixDimensions<iRows, -1>::cols() const {
            return _cols;
        }

        template <int iRows>
        inline
        int
        MatrixDimensions<iRows, -1>::size() const {
            return _size;
        }

        template <int iCols>
        inline
        MatrixDimensions<-1, iCols>::MatrixDimensions(int rows) :
            _rows(rows),
            _size(rows * iCols) {

            static_assert(
                iCols == 1,
                "Only row or column matrices can be initialized with a single size"
            );
            assert(rows > 0);
        }

        template <int iCols>
        inline
        MatrixDimensions<-1, iCols>::MatrixDimensions(int rows, int cols) :
            _rows(rows),
            _size(rows * iCols) {

            assert(rows > 0);
            assert(cols == iCols);
        }

        template <int iCols>
        inline
        int
        MatrixDimensions<-1, iCols>::rows() const {
            return _rows;
        }

        template <int iCols>
        inline
        int
        MatrixDimensions<-1, iCols>::cols() const {
            return iCols;
        }

        template <int iCols>
        inline
        int
        MatrixDimensions<-1, iCols>::size() const {
            return _size;
        }

        inline
        MatrixDimensions<-1, -1>::MatrixDimensions(int rows, int cols) :
            _rows(rows),
            _cols(cols),
            _size(rows * cols) {

            assert(rows > 0);
            assert(cols > 0);
        }

        inline
        int
        MatrixDimensions<-1, -1>::rows() const {
            return _rows;
        }

        inline
        int
        MatrixDimensions<-1, -1>::cols() const {
            return _cols;
        }

        inline
        int
        MatrixDimensions<-1, -1>::size() const {
            return _size;
        }

    }
}
