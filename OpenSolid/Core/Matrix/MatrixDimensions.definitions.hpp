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

#include <OpenSolid/Core/Matrix/MatrixDimensions.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iRows, int iCols>
        class MatrixDimensions
        {
        public:
            static_assert(iRows > 0, "Matrices must have at least one row");
            static_assert(iCols > 0, "Matrices must have at least one column");

            MatrixDimensions();

            MatrixDimensions(int size);

            MatrixDimensions(int rows, int cols);

            int
            rows() const;

            int
            cols() const;

            int
            size() const;
        };

        template <int iRows>
        class MatrixDimensions<iRows, -1>
        {
        private:
            int _cols;
            int _size;
        public:
            static_assert(iRows > 0, "Matrices must have at least one row");

            MatrixDimensions(int cols);

            MatrixDimensions(int rows, int cols);

            int
            rows() const;

            int
            cols() const;

            int
            size() const;
        };

        template <int iCols>
        class MatrixDimensions<-1, iCols>
        {
        private:
            int _rows;
            int _size;
        public:
            static_assert(iCols > 0, "Matrices must have at least one column");

            MatrixDimensions(int rows);

            MatrixDimensions(int rows, int cols);

            int
            rows() const;

            int
            cols() const;

            int
            size() const;
        };

        template <>
        class MatrixDimensions<-1, -1>
        {
        private:
            int _rows;
            int _cols;
            int _size;
        public:
            MatrixDimensions(int rows, int cols);

            int
            rows() const;

            int
            cols() const;

            int
            size() const;
        };
    }
}
